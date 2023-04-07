/* C program assignment for CCPS393 Winter 2023 offering at Toronto Metropolitan University */

#include <stdio.h>
#include <stdlib.h>

#define MULTIPLIER 5
#define LOWESTPRICE 30
#define HIGHESTPRICE 105

#define NCOIN 5
#define DCOIN 10
#define PCOIN 20

int make_change(int coins_inserted, int price, char user_input)
{

    int change = 0;
    if (user_input == 'E' || user_input == 'e' || user_input == 'R' || user_input == 'r')
    {
        change = coins_inserted;
    }
    else
    {
        change = abs(price - coins_inserted);
    }

    int dcoin_change = change / DCOIN;

    int ncoin_change = (change % DCOIN) / NCOIN;

    printf("    Change given: %d centimes as %d dime(s) and %d nickel(s) \n", change, dcoin_change, ncoin_change);
}

int main(int argc, char *argv[])
{

    if (argc == 2)
    {

        char *a = argv[1];
        int pop_price = atoi(a);

        if (pop_price < LOWESTPRICE || pop_price > HIGHESTPRICE)
        {
            printf("Price must be between %d and %d inclusive.\n", LOWESTPRICE, HIGHESTPRICE);
            return 0;
        }
        else
        {
            if ((pop_price % MULTIPLIER) != 0)
            {
                printf("Price must be a multiple of %d\n", MULTIPLIER);
                return 0;
            }

            printf("You have entered: %d\n", pop_price);

            char user_input;
            char user_abort;
            int user_coin;
            int running_total = 0;

            printf("Hello and welcome to my C Pop Machine!\n");

            while (user_abort != 'E' || user_abort == 'R')
            {

                printf("Pop is %d centimes. \nPlease insert any combination of Nickels [N or n], Dimes [D or d], or Pentes[P or p].\nYou can also press R or r for coin return.\nEnter coin [NDPR]:", pop_price);

                while (running_total < pop_price)
                {

                    scanf("%s", &user_input);

                    if (user_input == 'R' || user_input == 'r')
                    {

                        user_abort = user_input;
                        make_change(running_total, pop_price, user_input);
                        running_total = 0;
                        break;
                    }

                    switch (user_input)
                    {
                    case 'n':
                    case 'N':
                        printf("  Nickel detected\n");
                        user_coin = NCOIN;
                        break;
                    case 'd':
                    case 'D':
                        printf("  Dime detected\n");
                        user_coin = DCOIN;
                        break;
                    case 'p':
                    case 'P':
                        printf("  Pente detected\n");
                        user_coin = PCOIN;
                        break;
                    case 'e':
                    case 'E':
                        user_abort = 'E';
                        make_change(running_total, pop_price, user_input);
                        printf("Shutting down. Goodbye.\n");
                        return 0;
                    default:
                        printf("  Unknown coin rejected.\n");
                        user_coin = 0;
                        break;
                    }

                    running_total += user_coin;

                    printf("    You have inserted a total of %d centimes\n", running_total);

                    if (running_total != pop_price && (pop_price - running_total) > 0)
                    {
                        printf("Please insert %d more centimes\n", pop_price - running_total);
                    }
                }

                // DISPENSE POP AND CHANGE ONCE ENOUGH CHANGE HAS BEEN INSERTED

                if (running_total >= pop_price)
                {

                    printf("Pop has been dispensed! Thank you for your business! Please come again.\n");

                    if (running_total > pop_price)
                    {
                        make_change(running_total, pop_price, user_input);
                    }
                    running_total = 0;
                }
            }

            return 0;
        };
    }
    else
    {
        printf("Please specify a selling price as a command line argument.\nUsage: pop [price]\n");
        return 0;
    }
}