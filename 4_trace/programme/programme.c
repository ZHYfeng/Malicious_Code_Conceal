#include <malloc.h>
#include <math.h>
#include <stdio.h>

#define num_of_thread 4
#define num_of_malicious 4

long long int factorial(long long int n) {
  if (n > 1) {
    return n * factorial(n - 1);
  } else {
    return 1;
  }
}

void swap(long long int *m, long long int *n) {
  long long int temp = *m;
  *m = *n;
  *n = temp;
}

long long int order_of_subsequence;
long long int (*subsequence)[num_of_malicious];
long long int init_subsequence[num_of_malicious];
void permutation_of_subsequence(long long int k, long long int m) {
  long long int i, j;
  if (k == m) {
    for (i = 0; i <= m; i++) {
      subsequence[order_of_subsequence][i] = init_subsequence[i];
    }
    order_of_subsequence++;
  } else {
    for (j = k; j <= m; j++) {
      swap(init_subsequence + j, init_subsequence + k);
      permutation_of_subsequence(k + 1, m);
      swap(init_subsequence + j, init_subsequence + k);
    }
  }
}

long long int order_of_sequence;
long long int (*all_sequence_of_thread)[num_of_malicious * num_of_thread];
long long int (*all_sequence_of_malicious)[num_of_malicious * num_of_thread];
void permutation_of_sequence(long long int *order_of_thread,
                             long long int *sequence_of_malicious,
                             long long int *sequence_of_thread) {
  long long int lang = 0;
  for (long long int i = 0; i < num_of_thread; i++) {
    lang = lang + order_of_thread[i];
  }
  if (lang == num_of_thread * num_of_malicious) {

    for (long long int i = 0; i < num_of_malicious * num_of_thread; i++) {
      all_sequence_of_thread[order_of_sequence][i] = sequence_of_thread[i];
    }
    for (long long int i = 0; i < num_of_malicious * num_of_thread; i++) {
      all_sequence_of_malicious[order_of_sequence][i] =
          sequence_of_malicious[i];
    }
    order_of_sequence++;
  }
  for (long long int i = 0; i < num_of_thread; i++) {
    if (order_of_thread[i] < num_of_malicious) {
      long long int temp_order_of_thread[num_of_thread];
      for (long long int j = 0; j < num_of_thread; j++) {
        temp_order_of_thread[j] = order_of_thread[j];
      }
      temp_order_of_thread[i]++;
      long long int temp_sequence_of_thread[num_of_malicious * num_of_thread];
      for (long long int j = 0; j < num_of_malicious * num_of_thread; j++) {
        temp_sequence_of_thread[j] = sequence_of_thread[j];
      }
      temp_sequence_of_thread[lang] = i;
      long long int
          temp_sequence_of_malicious[num_of_malicious * num_of_thread];
      for (long long int j = 0; j < num_of_malicious * num_of_thread; j++) {
        temp_sequence_of_malicious[j] = sequence_of_malicious[j];
      }
      temp_sequence_of_malicious[lang] = temp_order_of_thread[i];

      permutation_of_sequence(temp_order_of_thread, temp_sequence_of_malicious,
                              temp_sequence_of_thread);
    }
  }
}

long long int main(long long int argc, char *argv[]) {

  //   freopen("input.txt", "r", stdin);
  // freopen("output.txt", "w", stdout);

  order_of_subsequence = 0;
  subsequence = (long long int(*)[num_of_malicious])malloc(
      sizeof(long long int) * num_of_malicious * factorial(num_of_malicious));
  for (long long int i = 0; i < num_of_malicious; i++) {
    init_subsequence[i] = i + 1;
  }
  permutation_of_subsequence(0, num_of_malicious - 1);
  order_of_sequence = 0;
  long long int size = factorial(num_of_malicious * num_of_thread) /
                       pow(factorial(num_of_malicious), num_of_thread);

  all_sequence_of_thread = (long long int(*)[num_of_malicious * num_of_thread])
      malloc(sizeof(long long int) * num_of_malicious * num_of_thread * size);
  all_sequence_of_malicious =
      (long long int(*)[num_of_malicious * num_of_thread]) malloc(
          sizeof(long long int) * num_of_malicious * num_of_thread * size);
  long long int order_of_thread[num_of_thread];
  for (long long int i = 0; i < num_of_thread; i++) {
    order_of_thread[i] = 0;
  }
  long long int sequence_of_thread[num_of_malicious * num_of_thread];
  for (long long int i = 0; i < num_of_malicious * num_of_thread; i++) {
    sequence_of_thread[i] = 0;
  }
  long long int sequence_of_malicious[num_of_malicious * num_of_thread];
  for (long long int i = 0; i < num_of_malicious * num_of_thread; i++) {
    sequence_of_malicious[i] = 0;
  }
  permutation_of_sequence(order_of_thread, sequence_of_malicious,
                          sequence_of_thread);
  long long int count_of_subsequence[order_of_subsequence];
  long long int ishappen;
  for (long long int i = 0; i < order_of_subsequence; i++) {
    count_of_subsequence[i] = 0;
    for (long long int j = 0; j < size; j++) {
      ishappen = 0;
      for (long long int k = 0; k < num_of_malicious * num_of_thread; k++) {
        if (all_sequence_of_malicious[j][k] == subsequence[i][ishappen]) {
          ishappen++;
        }
        if (ishappen == num_of_malicious) {
          count_of_subsequence[i]++;
          break;
        }
      }
    }
  }

  printf("num_of_thread : %d\n", num_of_thread);
  printf("num_of_malicious : %d\n", num_of_malicious);
  for (long long int i = 0; i < order_of_subsequence; i++) {
    for (long long int j = 0; j < num_of_malicious; j++) {
      printf("%lld ", subsequence[i][j]);
    }
    printf(" : %lld", count_of_subsequence[i]);
    printf("\n");
  }
  printf("size : %lld\n", size);
  for (long long int i = 0; i < size; i++) {
    for (long long int j = 0; j < num_of_malicious * num_of_thread; j++) {
      printf("T%lld", all_sequence_of_thread[i][j]);
      printf("M%lld-", all_sequence_of_malicious[i][j]);
    }
    printf("\n");
  }

  return 0;
}