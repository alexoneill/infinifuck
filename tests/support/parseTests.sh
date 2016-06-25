#!/bin/bash
# parseTests.sh
# aoneill - 06/25/16

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source "$DIR/unit.sh"

function init() {
  prog="$1"
  if ! [[ -x "$prog" ]]; then
    echo "error: $prog is not an executable!"
    return 1
  fi

  flags="$2"

  inputDir="$3"
  if ! [[ -d "$inputDir" ]]; then
    echo "error: $inputDir is not a directory!"
    return 1
  fi

  outputDir="$4"
  if ! [[ -d "$outputDir" ]]; then
    echo "error: $outputDir is not a directory!"
    return 1
  fi

  hasFailed=0
  results=$(mktemp)
  for file in $(find "$inputDir" -type f); do
    other="$(echo "$file" | sed -e "s|$inputDir|$outputDir|")"
    progOut=$(mktemp)
    $prog $flags $file > "$progOut" 2>/dev/null
    
    assertFilesEqual "$progOut" "$other"
    if [[ "$?" != "0" ]]; then
      echo "Failure: $file" >> "$results"
      hasFailed=$((hasFailed+1))
    else
      echo "Success: $file" >> "$results"
    fi
  done

  cat "$results"
  if [[ "$hasFailed" != "0" ]]; then
    echo "Total failures: $hasFailed"
    return 1
  fi

  return 0
}

# Execute init (passing arguments) if we are not sourced
EXEC=$(test "${BASH_SOURCE[0]}" != "${0}"; echo $?)
[[ "$EXEC" == "1" ]] && init $@
