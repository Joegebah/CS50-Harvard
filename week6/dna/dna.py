import csv
import sys

def main():
    not_valid_input = len(sys.argv) != 3
    if (not_valid_input):
        sys.exit("Usage: python3 dna.py INPUTFILE.csv INPUTFILE.txt")

    dna_database = []
    list_counter = 0
    counts = {}

    with open(sys.argv[1], "r") as database_file:
        database_reader = csv.DictReader(database_file)
        for persons_dna in database_reader:
            dna_database.append(persons_dna)

    dna_sequence_file = open(sys.argv[2], "r")
    dna_sequence = dna_sequence_file.readline()

    dna_subsequence = database_reader.fieldnames
    for STR_longest_match_sub_sequence in dna_subsequence[1:]:
        counts[STR_longest_match_sub_sequence] = longest_match(dna_sequence, STR_longest_match_sub_sequence)

    for dna_database_profile in dna_database:
        dna_database_profile_wo_name = dict(list(dna_database_profile.items())[1:])
        for key in dna_database_profile_wo_name:
            dna_database_profile_wo_name[key] = int(dna_database_profile_wo_name[key])

        if (counts == dna_database_profile_wo_name):
            print(dna_database_profile["name"])
            break

        list_has_reached_end = list_counter == len(dna_database) - 1
        if (list_has_reached_end):
            print("No Match") 
            break     

        list_counter += 1   

    return

def longest_match(sequence, subsequence):
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)
    for i in range(sequence_length):
        count = 0
        while True:
            start = i + count * subsequence_length
            end = start + subsequence_length
            if sequence[start:end] == subsequence:
                count += 1
            else:
                break

        longest_run = max(longest_run, count)

    return longest_run

main()
