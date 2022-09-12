from curses.ascii import isalpha

def count_letters(text):
    number_of_letters = 0
    for character in text:
        if (isalpha(character)):
            number_of_letters += 1
    
    return number_of_letters

def count_words(text):
    number_of_words = 1
    for character in text:
        if (character == " "):
            number_of_words += 1
    
    return number_of_words

def count_sentences(text):
    number_of_sentences = 0
    for character in text:
        if (character == "." or character == "!" or character == "?"):
            number_of_sentences += 1
    
    return number_of_sentences

def main():
    text = str(input("Please input text: "))

    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)
    index = round(0.0588 * ((letters / words) * 100.0) - (0.296 * ((sentences / words) * 100.0)) - 15.8)

    if (index > 16):
        print("Grade 16+")
    elif (index < 1):
        print("Before Grade 1")
    else:
        print("Grade:", index)

main()