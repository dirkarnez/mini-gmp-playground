#include <stdio.h>
#include "mini-gmp.h"

int main() {
    // 1. Initialize mpz_t variables
    mpz_t price_in_cents;
    mpz_t tax_rate_scaled;
    mpz_t tax_amount;
    mpz_t total_in_cents;
    mpz_t scale_factor;
    mpz_t remainder;

    mpz_init(price_in_cents);
    mpz_init(tax_rate_scaled);
    mpz_init(tax_amount);
    mpz_init(total_in_cents);
    mpz_init(scale_factor);
    mpz_init(remainder);

    // 2. Set values (Example: Item costs $100.50, Tax is 8.25%)
    mpz_set_str(price_in_cents, "10050", 10);     // $100.50 -> 10050 cents
    mpz_set_str(tax_rate_scaled, "825", 10);      // 8.25% -> 825 (scaled by 10000)
    mpz_set_str(scale_factor, "10000", 10);       // Factor to remove tax scaling

    // 3. Calculate Tax: (Price * Tax Rate) / 10000
    mpz_mul(tax_amount, price_in_cents, tax_rate_scaled);
    
    // Use fdiv_q to divide and handle rounding down to the nearest cent
    mpz_fdiv_q(tax_amount, tax_amount, scale_factor);

    // 4. Calculate Total: Price + Tax
    mpz_add(total_in_cents, price_in_cents, tax_amount);

    // 5. Format and Print the Result ($108.79)
    // Separate cents into dollars and remaining cents for display
    mpz_t dollars, cents;
    mpz_init(dollars);
    mpz_init(cents);
    mpz_t hundred;
    mpz_init_set_ui(hundred, 100);

    mpz_fdiv_qr(dollars, cents, total_in_cents, hundred);

    gmp_printf("Subtotal: $%Zd.%02Zd\n", price_in_cents, remainder); // Simplification
    gmp_printf("Total Price: $%Zd.%02Zd\n", dollars, cents);

    // 6. Clean up memory
    mpz_clears(price_in_cents, tax_rate_scaled, tax_amount, 
               total_in_cents, scale_factor, remainder, 
               dollars, cents, hundred, NULL);

    return 0;
}
