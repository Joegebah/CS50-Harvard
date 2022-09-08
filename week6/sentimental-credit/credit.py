import re

def main():
    credit_card_is_valid = False
    while not credit_card_is_valid:
        individual_digit_of_product_sum = 0
        sum_of_not_multiplier = 0
        credit_card_number = int(input("please enter your credit card number:  "))
        credit_card_number_copy = credit_card_number
        credit_card_number_copy = int(credit_card_number_copy / 10)
    
        while True:
            if ((credit_card_number_copy  % 10) * 2) < 10 :
                individual_digit_of_product_sum = individual_digit_of_product_sum + (credit_card_number_copy % 10) * 2
            else: 
                individual_digit_of_product_sum = individual_digit_of_product_sum + (((credit_card_number_copy % 10) * 2) % 10) + int((((credit_card_number_copy % 10) * 2) / 10)) % 10

            if not credit_card_number_copy >= 0 or not (int(credit_card_number_copy) / 10) >= 10:
                break

            credit_card_number_copy = int(credit_card_number_copy / 100)

        credit_card_number_copy = credit_card_number

        while True:
            sum_of_not_multiplier = sum_of_not_multiplier + (credit_card_number_copy % 10)
            credit_card_number_copy = int(credit_card_number_copy / 100)

            if not (credit_card_number_copy > 0 or (int(credit_card_number_copy / 100)) > 10):
                break

        check = sum_of_not_multiplier + individual_digit_of_product_sum
        check_is_valid = (check % 10) == 0
        credit_card_number = str(credit_card_number)

        if check_is_valid:
            if (len(credit_card_number) == 15):
                is_amex = re.findall("^34", credit_card_number) or re.findall("^37", credit_card_number)
                if is_amex:
                    print("AMEX")
                    credit_card_is_valid = True
                else:
                    print("Unknown credit id, ")

            elif (len(credit_card_number) == 16):
                is_master = re.findall("^51", credit_card_number) or re.findall("^52", credit_card_number) or re.findall("^53", credit_card_number) or re.findall("^54", credit_card_number) or re.findall("^55", credit_card_number)
                is_visa = re.findall("^4", credit_card_number)
                if is_master:
                    print("MASTER")
                    credit_card_is_valid = True
                elif is_visa:
                    print("VISA")
                    credit_card_is_valid = True
                else:
                    print("Unknown credit id, ")

            elif (len(credit_card_number) == 13 or len(credit_card_number) == 14):
                is_visa = re.findall("^4", credit_card_number)
                if is_visa:
                    print("VISA")
                    credit_card_is_valid = True
                else:
                    print("Unknown credit id, ")
                    
        else:
            print("INVALID")

main()
