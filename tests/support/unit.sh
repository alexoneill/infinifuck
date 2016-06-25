#!/bin/bash
# unit.sh
# aoneill - 06/25/16

function assertEqual() {
  if [[ "$#" != "2" ]]; then
    echo "error: Incorrect number of arguments for assertEqual"
    return 1
  fi

  if [[ "$1" != "$2" ]]; then
    return 1
  fi

  return 0
}

function assertEquals() {
  assertEqual $@
  return $?
}

function assertEmpty() {
  if [[ "$#" != "1" ]]; then
    echo "error: Incorrect number of arguments for assertEmpty"
    return 1
  fi

  assertEqual "$1" ""
  return $?
}

function assertFilesEqual() {
  if [[ "$#" != "2" ]]; then
    echo "error: Incorrect number of arguments for assertFilesEqual"
    return 1
  fi

  if ! [[ -f "$1" && -f "$2" ]]; then
    echo "error: Arguments for assertFilesEqual are not files!"
    return 1
  fi

  assertEmpty "$(diff "$1" "$2")"
  return $?
}
