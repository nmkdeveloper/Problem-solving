/*Nhóm, vành, trường

Nhân ma trận: nhân, cộng
(S, +, x):
   Cộng: vị nhóm giao hoán:
      + Kết hợp
      + Tồn tại phần từ đơn vị: 0
      + Giao hoán
   Nhân: nữa nhóm:
      + Kết hợp
      + Phần tử đơn vị: 1
   Phần phối của phép nhân đối với phép cộng
   Triệt tiêu: a x 0 = 0 x a = 0
*/
#include <bits/stdc++.h>

using namespace std;

#define BASE 1000000000000000000LL
#define maxK 22
#define fto(i, a, b) for (int i = a; i <= b; ++i)

long long n, k;

struct BigInt {
   long long p, r;
   BigInt(long long _p = 0, long long _r = 0): p(_p), r(_r) {}
   static BigInt from_ll(long long x) {
      return BigInt(x/BASE, x%BASE);
   }
   static BigInt inf() {
      return BigInt(2LL*BASE + 7LL, 0);
   }
   bool is_inf() {
      return p >= 2LL*BASE + 7LL;
   }
   bool operator < (const BigInt o) const {
      if (p != o.p) return p < o.p;
      return r < o.r;
   }
   BigInt operator + (BigInt o) {
      long long p_s = p + o.p;
      long long r_s = r + o.r;
      if (r_s >= BASE) {
         p_s += 1;
         r_s -= BASE;
      }
      return BigInt(p_s, r_s);
   }
   void print() {
      if (p == 0) {
         cout << r;
      } else {
         cout << p;
         string s = to_string(r);
         while (s.size() < 18) s = "0" + s;
         cout << s;
      }
   }
};

struct Matrix {
   BigInt mat[maxK][maxK];
   
   static Matrix init_identity() {
      Matrix res;
      fto(i, 1, k) {
         fto(j, 1, k) {
            if (i == j) res.mat[i][j] = BigInt(0LL, 0LL);
            else res.mat[i][j] = BigInt::inf();
         }
      }
      return res;
   }
   
   static Matrix init_infinity() {
      Matrix res;
      fto(i, 1, k) {
         fto(j, 1, k) {
            if (i == -1) res.mat[i][j] = BigInt(0LL, 0LL);
            else res.mat[i][j] = BigInt::inf();
         }
      }
      return res;
   }
   
   Matrix operator * (Matrix o) {
      Matrix res = Matrix::init_infinity();
      fto(i, 1, k) {
         fto(p, 1, k) {
            if (mat[i][p].is_inf()) continue;
            fto(j, 1, k) {
               if (o.mat[p][j].is_inf()) continue;
               BigInt s = mat[i][p] + o.mat[p][j];
               res.mat[i][j] = min(res.mat[i][j], s);
            }
         }
      }
      return res;
   }
   
   Matrix pow(long long p) {
      Matrix res = Matrix::init_identity();
      Matrix base = *this;
      while (p > 0) {
         if (p & 1) res = res*base;
         base = base*base;
         p >>= 1;
      }
      return res;
   }
};

int main() {
   cin >> n >> k;
   Matrix A;
   fto(i, 1, k) {
      fto(j, 1, k) {
         long long tmp; cin >> tmp;
         A.mat[i][j] = BigInt::from_ll(tmp);
      }
   }
   if (n == 1) {
      cout << "0\n";
      return 0;
   }
   A = A.pow(n-1);
   BigInt ans = BigInt::inf();
   fto(u, 1, k) {
      if (A.mat[u][1] < ans) {
         ans = A.mat[u][1];
      }
   }
   ans.print();
   cout << "\n";
   return 0;
}

