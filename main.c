#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "smart_ledger.h"
#include "finance_ops.h"
#include "ui.h"        // 現在有這個檔案了，所以不會報錯
#include "storage.h"   // 現在有這個檔案了，所以不會報錯

// 全域變數實體化
Transaction ledger[100];
int count = 0;

int main() {
    // 1. 程式啟動載入資料
    load_data("data.csv");
    
    int choice;
    
    // 主選單迴圈
    do {
        system("cls"); // 清除畫面
        show_welcome_message();
        
        // 顯示目前概況
        double balance = calculate_balance(ledger, count);
        printf("Current Balance: ");
        if(balance >= 0) set_color(10); // Green
        else set_color(12); // Red
        printf("$%.2f\n", balance);
        set_color(7);
        
        print_separator();
        printf("1. Add Income\n");
        printf("2. Add Expense\n");
        printf("3. View All Records\n");
        printf("4. Sort by Amount (High -> Low)\n");
        printf("0. Save & Exit\n");
        print_separator();
        printf("Please select an option: ");
        
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n');
            choice = -1;
        }

        switch(choice) {
            case 1: 
            case 2: 
                if (count >= 100) {
                    show_alert("Error", "Memory full!");
                    break;
                }
                ledger[count].id = count + 1;
                ledger[count].type = (choice == 1) ? 1 : 0;
                
                printf("Enter Date (YYYY-MM-DD): ");
                scanf("%s", ledger[count].date);
                printf("Enter Amount: ");
                scanf("%lf", &ledger[count].amount);
                printf("Enter Note: ");
                scanf("%s", ledger[count].note);
                
                count++;
                show_alert("Success", "Record added!");
                break;

            case 3: 
                printf("\nID\tDate\t\tType\tAmount\tNote\n");
                print_separator();
                for(int i=0; i<count; i++) {
                    if(ledger[i].type == 1) set_color(10);
                    else set_color(12);
                    printf("%d\t%s\t%s\t%.0f\t%s\n", 
                        ledger[i].id, ledger[i].date, 
                        (ledger[i].type==1) ? "Income" : "Expense", 
                        ledger[i].amount, ledger[i].note);
                }
                set_color(7);
                system("pause");
                break;
                
            case 4: 
                sort_by_amount(ledger, count);
                show_alert("Done", "Sorted by amount.");
                break;

            case 0:
                save_data("data.csv");
                show_alert("Bye", "Data saved.");
                break;
                
            default:
                printf("Invalid option.\n");
                system("pause");
        }
    } while (choice != 0);

    return 0;
}