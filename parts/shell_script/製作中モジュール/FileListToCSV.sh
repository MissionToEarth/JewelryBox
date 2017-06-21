#!/bin/sh

# source dir -> dest dir
file_list_to_csv()
{
	if [[ $# -eq 0 ]]; then
		echo error
		return -1
	fi

	while [[ $# -lt 0 ]]; do
		echo $@
		shift
	done
}

file_list_to_csv 1 2 3