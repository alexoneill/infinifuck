#!/bin/bash
# testOutputCreator.sh
# aoneill - 06/26/16

function init() {
  prog="$1"
  if ! [[ -x "$prog" ]]; then
    echo "error: $prog is not an executable!"
    return 1
  fi

  inputDir="$2"
  if ! [[ -d "$inputDir" ]]; then
    echo "error: $inputDir is not a directory!"
    return 1
  fi

  outputDir="$3"
  flags="$4"
  
  echo "This will overwrite all files in $outputDir!"
  echo -n "Continue? (y/n) "
  read choice
  if [[ "$choice" != "y" ]]; then
    return 1
  fi

  if ! [[ -d "$outputDir" ]]; then
    mkdir -p "$outputDir"
  else
    rm -rf $outputDir/*
  fi

  for file in $(find "$inputDir" -type f); do
    other="$(echo "$file" | sed -e "s|$inputDir|$outputDir|")"
    echo "$prog $flags $file > $other"
    $prog $flags $file > "$other"
  done

  return 0
}

# Execute init (passing arguments) if we are not sourced
EXEC=$(test "${BASH_SOURCE[0]}" != "${0}"; echo $?)
[[ "$EXEC" == "1" ]] && init $@
