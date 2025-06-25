#!/bin/bash

PROJECT_DIR="$1"

REQUIRED_ROOT_FILES=("main.cpp")
for file in "${REQUIRED_ROOT_FILES[@]}"; do
    if [ ! -f "$PROJECT_DIR/$file" ]; then
        echo "::error::Файл '$file' отсутствует в корне проекта"
        exit 1
    fi
done

REQUIRED_SUBDIRS=("src")
for dir in "${REQUIRED_SUBDIRS[@]}"; do
    if [ ! -d "$PROJECT_DIR/$dir" ]; then
        echo "::error::Папка '$dir' отсутствует"
        exit 1
    fi
done

check_dir_content() {
    local dir="$1"
    while IFS= read -r -d '' file; do
        ext="${file##*.}"
        if [[ "$ext" != "cpp" && "$ext" != "hpp" && ! -d "$file" ]]; then
            echo "::error::Найден запрещённый файл '$file' в папке '$dir'"
            exit 1
        fi
    done < <(find "$PROJECT_DIR/$dir" -type f -print0)
}

check_dir_content "src"
check_dir_content "test"

echo "Всё в порядке, структура проекта в норме."
exit 0
