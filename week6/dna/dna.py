import csv
import sys
from typing import Sequence

def main():
    not_valid_input = len(sys.argv) != 3
    if (not_valid_input):
        sys.exit("Usage: python3 dna.py INPUTFILE.csv INPUTFILE.txt")

    dna_database = []
    counts = {}
    # TODO: Read database file into a variable
    with open(sys.argv[1], "r") as database_file:
        database_reader = csv.DictReader(database_file)
        for persons_dna in database_reader:
            dna_database.append(persons_dna)
    # TODO: Read DNA sequence file into a variable
    dna_sequence_file = open(sys.argv[2], "r")
    dna_sequence = dna_sequence_file.readline()
    # TODO: Find longest match of each STR in DNA sequence
    dna_subsequence = database_reader.fieldnames
    
    for STR_longest_match in dna_subsequence[1:]:
        counts[STR_longest_match] = longest_match(dna_sequence, STR_longest_match)
    # TODO: Check database for matching profiles

        
    return

def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""
    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)
    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0
        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length
            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1
            # If there is no match in the substring
            else:
                break
        # Update most consecutive matches found
        longest_run = max(longest_run, count)
    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run

main()
