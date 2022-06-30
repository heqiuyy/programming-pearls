#include <unistd.h>

#include <algorithm>
#include <cstdio>
#include <ctime>
#include <functional>
#include <iostream>
#include <random>
using namespace std;
#define BITSPERWORD 32
#define SHIFT 5
#define MASK 0x1F
#define N 100000000
int a[1 + N / BITSPERWORD];
int data[100000000];
int data2[100000000];
void set(long int i) { a[i >> SHIFT] |= (1 << (i & MASK)); }
void clr(long int i) { a[i >> SHIFT] &= ~(1 << (i & MASK)); }
int test(long int i) { return a[i >> SHIFT] & (1 << (i & MASK)); }
clock_t Begin1, End1;
double duration1;

clock_t Begin2, End2;
double duration2;

long tick1 = 0;
long tick2 = 0;

void getrandom() {
  long int random_tick = N;
  long int min = 0, max = N - 1;
  random_device seed;       //硬件生成随机数种子
  ranlux48 engine(seed());  //利用种子生成随机数引擎
  uniform_int_distribution<> distrib(min, max);  //设置随机数范围，并为均匀分布
  long int random;
  long int i = 0;  //随机数
  while (random_tick) {
    random = distrib(engine);  //随机数
    if (!test(random)) {
      set(random);
      data[i] = random;
      i++;
      random_tick--;
    }
  }
}
void paixusort() {
  long int i = 0;
  Begin2 = clock();
  sort(a, a + N, less<int>());
  End2 = clock();
  duration2 = (double)(End2 - Begin2) / CLOCKS_PER_SEC;
  cout << "+++++++++++++++++++++++++++++++" << endl;
  cout << i << endl;
}
void paixu() {
  long int random_tick = N;
  long int i = 0;
  Begin1 = clock();
  while (random_tick) {
    if (test(i)) {
      data2[N - random_tick] = i;
      random_tick--;
    }
    i++;
  }
  End1 = clock();
  duration1 = (double)(End1 - Begin1) / CLOCKS_PER_SEC;
}
int main() {
  cout << "+++++++++++++++++++++++++++++++" << endl;
  cout << "+++++++++++++++++++++++++++++++" << endl;
  cout << "+++++++++++++++++++++++++++++++" << endl;
  cout << "+++++++++++++++++++++++++++++++" << endl;
  cout << "+++++++++++++++++++++++++++++++" << endl;
  sleep(1);
  getrandom();
  cout << "+++++++++++++++++++++++++++++++" << endl;
  cout << "+++++++++++++++++++++++++++++++" << endl;
  cout << "+++++++++++++++++++++++++++++++" << endl;
  cout << "+++++++++++++++++++++++++++++++" << endl;
  cout << "+++++++++++++++++++++++++++++++" << endl;
  sleep(1);
  paixu();
  paixusort();
  cout << "duration : " << tick1 << "    " << tick2 << endl;
  cout << "duration : " << duration1 << endl;
  cout << "duration : " << duration2 << endl;
}