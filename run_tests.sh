#!/usr/bin/env bash

BIN="./a.out"
TEST_DIR="./tests"
TMP_OUT="$TEST_DIR/tmp_output.txt"

if [ ! -x "$BIN" ]; then
  echo "Исполняемый файл '$BIN' не найден или не исполняем. Соберите программу, например: gcc ... -o a.out"
  exit 1
fi

normalize_actual() {
  local infile="$1"
  sed 's/\r$//' "$infile" \
    | grep -v -E '^[[:space:]]*\+----1' \
    | sed -E 's/^[[:space:]]*>+[[:space:]]*//' \
    | sed -E 's/^[[:space:]]+//' \
    | sed -E 's/[[:space:]]+$//' \
    | awk 'NF{line=$0} END{ if(length(line)) print line; else print "" }'
}

canonicalize_with_expected() {
  local actual="$1"
  local expect="$2"

  if [ -z "$actual" ]; then
    echo ""
    return
  fi

  if echo "$expect" | grep -q -E '[eE]'; then
    if ! echo "$actual" | grep -q -E '[eE]'; then
      actual="${actual}E+0"
    fi
  fi

  if echo "$actual" | grep -q -E '[eE]'; then
    local mant exp
    mant=$(echo "$actual" | sed -E 's/^([+-]?[0-9]+\.[0-9]+)([eE].*)$/\1/')
    exp=$(echo "$actual"  | sed -E 's/^([+-]?[0-9]+\.[0-9]+)([eE].*)$/\2/')
    if [ -z "$mant" ] || [ -z "$exp" ]; then
      echo "$actual"
      return
    fi
    mant=$(echo "$mant" | sed -E 's/0+$//; s/\.$/.0/')
    echo "${mant}${exp}"
    return
  fi

  echo "$actual"
}


run_category() {
  local category="$1"
  local dir="$TEST_DIR/$category"
  local total=0
  local passed=0

  echo -e "\n=== Тесты: $category ==="

  for infile in "$dir"/input_*.txt; do
    [ -f "$infile" ] || continue
    total=$((total + 1))
    num=$(basename "$infile" | grep -oE '[0-9]+' )
    outfile="$dir/output_${num}.txt"

    cat "$infile" | "$BIN" > "$TMP_OUT" 2>/dev/null

    raw_actual=$(cat "$TMP_OUT")
    real_out=$(normalize_actual "$TMP_OUT")
    expect_raw=$(tr -d '\r' < "$outfile" | sed -E 's/^[[:space:]]+//; s/[[:space:]]+$//')

    real_can=$(canonicalize_with_expected "$real_out" "$expect_raw")
    expect_can=$(canonicalize_with_expected "$expect_raw" "$expect_raw")

    if [ "$real_can" = "$expect_can" ]; then
      echo "Тест #$num — OK"
      passed=$((passed + 1))
    else
      echo "Тест #$num — FAIL"
      echo "   Ввод:"
      sed 's/^/   > /' "$infile"
      echo "   Ожидалось: '$expect_raw'"
      echo "   Получено: '$real_can'"
      echo "   -- Полный  вывод программы (для отладки):"
      printf '%s\n' "$raw_actual" | sed 's/^/      /'
    fi
  done

  echo "=== Результат категории $category: $passed / $total пройдено ==="
}

rm -f "$TMP_OUT"
run_category "positive"
run_category "negative"
rm -f "$TMP_OUT"
