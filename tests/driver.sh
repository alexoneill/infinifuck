#!/bin/bash
# test.sh
# aoneill - 06/25/16

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

function init() {
  prog="$1"

  make clean
  make
  if [[ "$?" != "0" ]]; then
    echo "error: Could not make executable!"
    return 1
  fi
    
  printf "=%.0s" $(seq 40)
  echo ""

  index=0
  flags=("--parse-only"  " "  " ")
  hasFailed=0
  for dir in $(find "$DIR/scripts/" -mindepth 1 -maxdepth 1 -type d); do
    dir="$(basename "$dir")"
    echo "Testing $dir..."
    $DIR/support/outputTests.sh "$prog" "./tests/scripts/$dir/" \
      "./tests/outputs/$dir/" "${flags[$index]}"
    if [[ "$?" != "0" ]]; then
      hasFailed=$((hasFailed+1))
    else
      echo "Passed!"
    fi
    
    index=$((index+1))
    printf "=%.0s" $(seq 40)
    echo ""
  done
}

# Execute init (passing arguments) if we are not sourced
EXEC=$(test "${BASH_SOURCE[0]}" != "${0}"; echo $?)
[[ "$EXEC" == "1" ]] && init $@
