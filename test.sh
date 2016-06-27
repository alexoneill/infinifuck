#!/bin/bash
# test.sh
# aoneill - 06/25/16

function init() {
  make clean
  make
  if [[ "$?" != "0" ]]; then
    echo "error: Could not make executable!"
    return 1
  fi

  echo "Testing parsing..."
  ./tests/support/outputTests.sh "./infinifuck" "./tests/parse-scripts/" \
    "./tests/parse-outputs/" "--parse-only"
  [[ "$?" != "0" ]] && return 1
  echo "Passed!"

  echo "Testing scripts..."
  ./tests/support/outputTests.sh "./infinifuck" "./tests/stdout-scripts/" \
    "./tests/stdout-outputs/" ""
  [[ "$?" != "0" ]] && return 1
  echo "Passed!"
}

# Execute init (passing arguments) if we are not sourced
EXEC=$(test "${BASH_SOURCE[0]}" != "${0}"; echo $?)
[[ "$EXEC" == "1" ]] && init $@
