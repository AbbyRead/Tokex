#!/bin/bash

# Default values
convert_spaces=true

# Parse command-line options
while getopts ":z" opt; do
    case $opt in
        z) convert_spaces=false ;;
        \?) echo "Invalid option: -$OPTARG" >&2
            exit 1 ;;
    esac
done

# Shift the processed options out of the argument list
shift $((OPTIND-1))

# Use awk to add "0" to words with an odd number of letters
awk 'BEGIN { RS = "" } {
    gsub(/[,!?]/, " ");  # Replace punctuation with spaces
    words = split($0, arr, /[ \n]/);
    output = "";
    for (i = 1; i <= words; i++) {
        word = arr[i];
        if (word ~ /^[a-zA-Z]+$/) {  # Only consider words with letters
            if (length(word) % 2 == 1) {
                word = word "0"
            }
        }
        output = output word (i == words ? "" : " ");
    }
    printf "%s%s", output, (RT == "\n" ? RT : "");
}' | \
# Replace specified characters
while IFS= read -r -n 1 char; do
    case "$char" in
        [Aa]) printf "A" ;;
        [Ii]) printf "1" ;;
        [Uu]) printf "2" ;;
        [Ee]) printf "E" ;;
        [Oo]) printf "6" ;;
        [Pp]) printf "B" ;;
        [Tt]) printf "D" ;;
        [Kk]) printf "C" ;;
        [Mm]) printf "8" ;;
        [Nn]) printf "9" ;;
        [Ll]) printf "7" ;;
        [Ss]) printf "5" ;;
        [Jj]) printf "4" ;;
        [Ww]) printf "3" ;;
         $'') printf "0F" ;;
        $'\n') printf "0FF0" ;;
        " ") if [ "$convert_spaces" = true ]; then printf "__"; else printf "00"; fi ;;
        *) printf "%s" "$char" ;;
    esac
done
