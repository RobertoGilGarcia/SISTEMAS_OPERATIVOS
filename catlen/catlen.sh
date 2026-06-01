#!/bin/sh

usage() {
    echo "usage: ./photocol.sh [dest_dir] [dir1] [dir2]..." >&2
    exit 1
}

if [ $# -lt 2 ]; then
    usage
fi

DEST=$1
shift

for SRC in "$@"; do
    if [ ! -d "$SRC" ]; then
        if [ -e "$SRC" ]; then
            SRC=$(cd "$SRC" && pwd)
        else
            echo "error: '$SRC' no es un directorio válido." >&2
            exit 1
        fi
    fi
done

if [ -e "$DEST" ] && [ ! -d "$DEST" ]; then
    echo "error: '$DEST' no es un directorio válido." >&2
    exit 1
fi

if [ -d "$DEST" ]; then
    rm -rf -- "$DEST" || exit 1
fi
mkdir -p "$DEST" || exit 1

TMPFILES=$(mktemp) || exit 1

for SRC in "$@"; do
    find "$SRC" -type f \( \
        -iname '*.jpg' -o -iname '*.jpeg' -o \
        -iname '*.PNG' -o -iname '*.TIFF' -o \
        -iname '*.JPG' -o -iname '*.JPEG' \
    \) -print >> "$TMPFILES"
done

while read -r FILEPATH; do
    [ -n "$FILEPATH" ] || continue

    EXT=$(echo "$FILEPATH" | sed 's/.*\(\.[^.]*\)$/\1/' | tr '[A-Z]' '[a-z]')
    FILENAME=$(echo "$FILEPATH" | sed 's/.*\///' | sed 's/\.[^.]*$//')

    case "$EXT" in
        .jpg|.jpeg) NEWEXT=".jpg" ;;
        .png)       NEWEXT=".png" ;;
        .tiff)      NEWEXT=".tiff" ;;
        *)          continue ;;
    esac

    DIRNAME=$(echo "$FILEPATH" | sed 's/\/[^\/]*$//')
    DIRNAME_CLEAN=$(echo "$DIRNAME" | sed 's/.*\///' | sed 's/ /-/g')

    BASENAME=$(echo "$FILENAME" | tr '[A-Z]' '[a-z]' | sed 's/ /-/g')

    NEWNAME="${DIRNAME_CLEAN}_${BASENAME}${NEWEXT}"
    DESTPATH="$DEST/$NEWNAME"

    DESTDIR=$(dirname "$DESTPATH")
    mkdir -p "$DESTDIR" || exit 1

    if [ -e "$DESTPATH" ]; then
        echo "error: colisión de nombre: $NEWNAME" >&2
        rm -rf -- "$DEST" 2>/dev/null
        mkdir -p "$DEST" 2>/dev/null
        rm -f "$TMPFILES"
        exit 1
    fi

    if ! cp "$FILEPATH" "$DESTPATH"; then
        echo "error: no se pudo copiar '$FILEPATH'" >&2
        rm -rf -- "$DEST" 2>/dev/null
        mkdir -p "$DEST" 2>/dev/null
        rm -f "$TMPFILES"
        exit 1
    fi

done < "$TMPFILES"

rm -f "$TMPFILES"

TMPMETA=$(mktemp) || exit 1
TOTAL=0
: > "$TMPMETA"

for F in "$DEST"/*; do
    [ -f "$F" ] || continue

    NAME=$(echo "$F" | sed 's/.*\///')
    SIZE=$(wc -c < "$F")
    echo "$NAME $SIZE" >> "$TMPMETA"
    TOTAL=$(( TOTAL + SIZE ))
done

sort -k2,2n "$TMPMETA" > "$DEST/metadata.txt"
echo "TOTAL:  $TOTAL bytes" >> "$DEST/metadata.txt"

rm -f "$TMPMETA"

exit 0
