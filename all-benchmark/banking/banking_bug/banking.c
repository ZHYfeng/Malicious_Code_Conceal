#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

typedef struct _Account {
  int amount;
  char *name;
  pthread_mutex_t lock;
} Account;

typedef struct _ManageAccount {
  Account *account;
  int i;
} ManageAccount;

FILE *out = 0;

ManageAccount bank[10];
char *accountName[10] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};

Account ManageAccount_accounts[10];
int ManageAccount_num = 2;    // the number of accounts
int ManageAccount_accNum = 0; // index to insert the next account

//-----------------------------------------------------------------------------
// from Account.java
//-----------------------------------------------------------------------------

// constructor
void Account_constructor(Account *acc, char *nm, int amnt) {
  acc->amount = amnt;
  acc->name = nm;
  pthread_mutex_init(&acc->lock, NULL);
}

// functions (synchronized)
void Account_deposit(Account *acc, int money) {
  pthread_mutex_lock(&acc->lock);
  acc->amount += money;
  pthread_mutex_unlock(&acc->lock);
}

void Account_withdraw(Account *acc, int money) {
  pthread_mutex_lock(&acc->lock);
  acc->amount -= money;
  pthread_mutex_unlock(&acc->lock);
}

void Account_transfer(Account *acc, Account *ac, int mn) {
  pthread_mutex_lock(&acc->lock);
  acc->amount -= mn;
  ac->amount += mn;
  pthread_mutex_unlock(&acc->lock);
  // pthread_mutex_lock(&ac->lock);
  // pthread_mutex_unlock(&ac->lock);
}

void Account_print(Account *acc) {
  pthread_mutex_lock(&acc->lock);
  printf("Account { amount = %d , name = %s }\n", acc->amount, acc->name);
  pthread_mutex_unlock(&acc->lock);
}

//-----------------------------------------------------------------------------
// from ManageAccount.java
//-----------------------------------------------------------------------------

void ManageAccount_constructor(ManageAccount *res, char *name, int amount) {
  res->i = ManageAccount_accNum;
  // ManageAccount_accNum = (ManageAccount_accNum+1)%ManageAccount_num;
  if (ManageAccount_accNum + 1 >= ManageAccount_num)
    ManageAccount_accNum = (ManageAccount_accNum + 1) - ManageAccount_num;
  else
    ManageAccount_accNum = (ManageAccount_accNum + 1);

  res->account = &ManageAccount_accounts[res->i];
  Account_constructor(res->account, name, amount);
}

void *ManageAccount_run(void *data) {
  int k = (int)data;
  ManageAccount *res = &bank[k];

  Account *acc;
  Account_deposit(res->account, 300);
  Account_withdraw(res->account, 100);
  // acc = &ManageAccount_accounts[ (res->i+1)%ManageAccount_num ];
  if ((res->i + 1) >= ManageAccount_num)
    acc = &ManageAccount_accounts[(res->i + 1) - ManageAccount_num];
  else
    acc = &ManageAccount_accounts[(res->i + 1)];

  Account_transfer(res->account, acc, 99);
}

void ManageAccount_printAllAccounts() {
  int j;
  for (j = 0; j < ManageAccount_num; j++) {
    Account *ptr = &ManageAccount_accounts[j];
    if (ptr != NULL) {
      Account_print(&ManageAccount_accounts[j]);
    }
  }
}

//-----------------------------------------------------------------------------
// from Main.java
//-----------------------------------------------------------------------------
int less = 0;
int more = 0; // flags which will indicate the kind of the bug

// little:1, avarage:2, lot:3
int main(int argc, char *argv[]) {

  int error = 0;

  int j, k;
  char *concurrencyLevel = 0;
  pthread_t tid[10];

  /*argc--;

  if (argc > 0) {
    out = fopen(argv[1], "w");
    if (argc == 1) { //the default value = little
      printf("The default value = little\n");
    }
    if (out) fprintf(out, "<Account program,");
    if (argc==2) { // the concurrency is optional
      concurrencyLevel = argv[2];
      if (strcmp(concurrencyLevel,"little")==0) {
        ManageAccount_num = 2;
        printf("concurrency level = little\n");
      }
      else if (strcmp(concurrencyLevel,"average")==0) {
        ManageAccount_num = 5;
        printf("concurrency level = average\n");
      }
      else if (strcmp(concurrencyLevel,"lot")==0) {
        ManageAccount_num = 10;
        printf("concurrency level = lot\n");
      }
      else {//wrong second argument
        printf("The second argument should be one of the following: \n
  little,average or lot\n");
        return 1;
      }

    }
    else {//more than 2 arguments
      if (argc>2) {
        printf("The program can accept only one or two arguments\n");
        return 1;
      }
    }

  }else { //main's parameter is missing
    printf("The output file name is missing\n");
    return 1;
  }*/
  ManageAccount_num = 2;
  printf("The Initial values:\n");

  {
    for (j = 0; j < ManageAccount_num; j++) {
      ManageAccount_constructor(&bank[j], accountName[j], 100);
      Account_print(&ManageAccount_accounts[j]);
    }
  }

  // start the threads
  for (k = 0; k < ManageAccount_num; k++) {
    pthread_create(&tid[k], 0, ManageAccount_run, k);
  }

  // wait until all are finished
  for (k = 0; k < ManageAccount_num; k++) {
    pthread_join(tid[k], 0);
  }

  printf("The final values:\n");

  ManageAccount_printAllAccounts();

  // updating the output file
  // if (out != 0) {
  for (k = 0; k < ManageAccount_num; k++) {
    assert(ManageAccount_accounts[k].amount == 300);
    if (ManageAccount_accounts[k].amount < 300) {
      less = 1;
    } else if (ManageAccount_accounts[k].amount > 300) {
      more = 1;
    }
  }

  // if ((less == 1) && (more == 1))
  //   if (out)
  //     fprintf(out, " There is amount with more than 300 and there is amount "
  //                  "with less than 300, No Lock>\n");
  // if ((less == 0) && (more == 1))
  //   if (out)
  //     fprintf(out, " There is amount with more than 300, No Lock>\n");
  // if ((less == 1) && (more == 0))
  //   if (out)
  //     fprintf(out, " There is amount with less than 300, No Lock>\n");
  // if ((less == 0) && (more == 0))
  //   if (out)
  //     fprintf(out, " All amounts are 300, None>\n");

  // fclose(out);
  // }

  assert(less == 0 && more == 0);

  return 1;
}
