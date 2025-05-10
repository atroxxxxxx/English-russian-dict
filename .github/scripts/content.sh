#!/bin/bash

PROJECT_DIR="$1"

check_file() {
    local file="$1"
    local line_num=0
    local has_trailing_space=0
    local has_long_line=0
    local has_no_final_newline=0
    local total_lines=0

    total_lines=$(wc -l < "$file")
    if [ "$total_lines" -gt 200 ]; then
        echo "::error::Файл '$file' слишком большой ($total_lines строк, максимум 200)"
        exit 1
    fi

    while IFS= read -r line; do
        line_num=$((line_num + 1))

        if [[ "$line" =~ [[:space:]]+$ ]]; then
            echo "::error::Лишние пробелы в конце строки $line_num файла '$file'"
            has_trailing_space=1
        fi

        if [ "${#line}" -gt 120 ]; then
            echo "::error::Строка $line_num в '$file' слишком длинная (${#line} символов, максимум 120)"
            has_long_line=1
        fi
    done < "$file"

    if [ "$(tail -c 1 "$file" | xxd -p)" != "0a" ]; then
        echo "::error::Файл '$file' должен заканчиваться символом новой строки (LF)"
        has_no_final_newline=1
    fi

    if [ "$has_trailing_space" -eq 1 ] || [ "$has_long_line" -eq 1 ] || [ "$has_no_final_newline" -eq 1 ]; then
        exit 1
    fi
}

check_file "$PROJECT_DIR/main.cpp"
check_file "$PROJECT_DIR/test_main.cpp"

find "$PROJECT_DIR/src" "$PROJECT_DIR/test" -type f \( -name "*.cpp" -o -name "*.hpp" \) | while read -r file; do
    check_file "$file"
done

echo "Проверка завершена. Код соответствует требованиям."
exit 0
