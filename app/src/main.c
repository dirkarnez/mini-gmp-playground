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

/*

#include <stdio.h>
#include "mini-gmp.h"

int main() {
    // 1. 初始化大整數變數
    mpz_t cash_item1, cash_item2, total_cash, tax_rate, tax_amount;
    mpz_init(cash_item1);
    mpz_init(cash_item2);
    mpz_init(total_cash);
    mpz_init(tax_rate);
    mpz_init(tax_amount);

    // 2. 設定現金數值（以「分」為單位，避免小數點誤差）
    // 假設品項 1 為 $5,000,000.50 元 -> 500000050 分
    mpz_set_str(cash_item1, "500000050", 10);
    // 假設品項 2 為 $2,500,000.25 元 -> 250000025 分
    mpz_set_str(cash_item2, "250000025", 10);

    // 3. 現金相加：total_cash = cash_item1 + cash_item2
    mpz_add(total_cash, cash_item1, cash_item2);

    // 4. 計算稅金或手續費（假設稅率為 5%，即乘以 5 再除以 100）
    mpz_set_ui(tax_rate, 5);
    mpz_mul(tax_amount, total_cash, tax_rate);     // tax_amount = total_cash * 5
    mpz_fdiv_q_ui(tax_amount, tax_amount, 100);    // tax_amount = tax_amount / 100

    // 5. 輸出結果 (mini-gmp 不支援 gmp_printf，需轉成字串輸出)
    char *total_str = mpz_get_str(NULL, 10, total_cash);
    char *tax_str = mpz_get_str(NULL, 10, tax_amount);

    printf("總現金金額（分）: %s\n", total_str);
    printf("計算稅金（分）  : %s\n", tax_str);

    // 6. 釋放記憶體
    void (*freefunc)(void *, size_t);
    mp_get_memory_functions(NULL, NULL, &freefunc);
    (*freefunc)(total_str, 0);
    (*freefunc)(tax_str, 0);

    mpz_clears(cash_item1, cash_item2, total_cash, tax_rate, tax_amount, NULL);
    return 0;
}


*/
