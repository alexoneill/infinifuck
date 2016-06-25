#!/bin/bash
# test.sh
# aoneill - 06/25/16

function init() {
  tmp=$(mktemp)
  make 2>&1 > "$tmp"
  if [[ "$?" != "0" ]]; then
    echo "error: Could not make executable!"
    cat "$tmp"
    rm "$tmp"
    return 1
  fi
  rm "$tmp"

  echo "Testing parsing..."
  ./tests/support/parseTests.sh "./infinifuck" "--parse-only" \
    "./tests/scripts/" "./tests/parse-outputs/"
  [[ "$?" != "0" ]] && return 1
  echo "Passed!"
}

# Execute init (passing arguments) if we are not sourced
EXEC=$(test "${BASH_SOURCE[0]}" != "${0}"; echo $?)
[[ "$EXEC" == "1" ]] && init $@
