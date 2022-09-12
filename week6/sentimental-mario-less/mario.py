while True:
    input_height = int(input("Please pick a number between 1 and 8:\n"))
    if input_height < 8 and input_height > 0:
        break

iteration_counter = 0
for height_iterator in range(input_height):
    whitespace_counter = input_height - iteration_counter
    while (whitespace_counter >= 0):
        print(" ", end="")
        whitespace_counter -= 1
        
    hash_counter = 0
    while (hash_counter < iteration_counter + 1):
        print("#", end="")
        hash_counter += 1

    iteration_counter += 1
    
    print("")

print("\n")
    