def get_dollars():
    while True:
        try:
            dollars = float(input("Change owed: "))
            if (dollars > 0):
                break
        except ValueError:
            print("Thats not a float!")

    return dollars
        
def calculate_quarters(dollars):
    return int((dollars * 100.0) / 25.0)

def calculate_dimes(dollars):
    return int((dollars * 100.0) / 10.0)

def calculate_nickels(dollars):
    return int((dollars * 100.0) / 5.0)

def calculate_pennies(dollars):
    return int(dollars * 100)

def main():
    dollars = get_dollars()

    quarters = calculate_quarters(dollars)
    dollars = (dollars * 100.0 - quarters * 25.0) / 100.0

    dimes = calculate_dimes(dollars)
    dollars = (dollars * 100.0 - dimes * 10.0) / 100.0

    nickels = calculate_nickels(dollars)
    dollars = (dollars * 100.0 - nickels * 5.0) / 100.0

    pennies = calculate_pennies(dollars)
    dollars = (dollars * 100.0 - pennies) / 100.0

    coins = quarters + dimes + nickels + pennies
    coins = int(coins)

    print(coins)
    print("\n", end="")

main()
