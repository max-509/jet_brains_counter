#!/bin/bash

if [ "$#" -lt 1 ]; then
    echo "Usage: $0 [path/to/genmc]"
    exit 0
fi

path_to_genmc=${1}

${path_to_genmc} -program-entry-function=serial_test test.c
${path_to_genmc} -program-entry-function=concurrent_inc_test test.c
${path_to_genmc} -program-entry-function=concurrent_inc_and_get_test test.c
