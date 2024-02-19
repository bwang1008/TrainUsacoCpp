#!/usr/bin/bash

set -euo pipefail

# usage:
# $ ./lint.sh <file_name>
# Example:
# $ ./lint.sh TMCompiler/src/unittesting/unittesting.hpp

# .clang-tidy file generated by
# $ clang-tidy --dump-config --checks=*,-fuchsia-default-arguments-calls,-fuchsia-trailing-return > .clang-tidy

# Note: in zsh, use "noglob clang-tidy" instead of "clang-tidy": see https://stackoverflow.com/questions/62266965/clang-tidy-resolving-no-match-error-when-adding-arguments

# reference: https://www.labri.fr/perso/fleury/posts/programming/using-clang-tidy-and-clang-format.html

# reason for not including specific checks:
# fuchsia-trailing-return: warns about trailing return types, when I want to use it
# fuchsia-default-arguments-calls: forbids calling functions with default arguments

clang-tidy "$1" -config='' -header-filter=.* --quiet -- -std=c++14
