#include <iostream>
#include <bits/stdc++.h>
using namespace std;
// Solution to http://www.spoj.com/problems/PRIME1/
// SieveOfEratosthenes

// Takes the min and max inclusive
void sieve(int a, int b) {
	bool prime[b+1];
	memset(prime, true, sizeof(prime));
	for(int p=2; p<=b; p++ ) {
		if (prime[p] != false){
			if (p>=a) {cout<<p<<'\n';}
			for (int i=2*p; i<=b; i+=p) {
				prime[i] = false;
			}
		}
	}
}

void simpleSieve(int limit, vector<int> &prime, int a)
{
    // Create a boolean array "mark[0..n-1]" and initialize
    // all entries of it as true. A value in mark[p] will
    // finally be false if 'p' is Not a prime, else true.
    bool mark[limit+1];
    memset(mark, true, sizeof(mark));

    for (int p=2; p*p<limit; p++)
    {
        // If p is not changed, then it is a prime
        if (mark[p] == true)
        {
            // Update all multiples of p
            for (int i=p*2; i<limit; i+=p)
                mark[i] = false;
        }
    }

    // Print all prime numbers and store them in prime
    for (int p=2; p<limit; p++)
    {
        if (mark[p] == true)
        {
            prime.push_back(p);
            if(p>=a)
            cout << p << "\n";
        }
    }
}

// Prints all prime numbers smaller than 'n'
void segmentedSieve(int n, int a)
{
    // Compute all primes smaller than or equal
    // to square root of n using simple sieve
    int limit = floor(sqrt(n))+1;
    vector<int> prime;
    simpleSieve(limit, prime);

    // Divide the range [0..n-1] in different segments
    // We have chosen segment size as sqrt(n).
    int low  = limit;
    if (limit < a) low = a;
    int high = low + limit;

    // While all segments of range [0..n-1] are not processed,
    // process one segment at a time
    while (low < n)
    {
        // To mark primes in current range. A value in mark[i]
        // will finally be false if 'i-low' is Not a prime,
        // else true.
        bool mark[limit+1];
        memset(mark, true, sizeof(mark));

        // Use the found primes by simpleSieve() to find
        // primes in current range
        for (int i = 0; i < prime.size(); i++)
        {
            // Find the minimum number in [low..high] that is
            // a multiple of prime[i] (divisible by prime[i])
            // For example, if low is 31 and prime[i] is 3,
            // we start with 33.
            int loLim = floor(low/prime[i]) * prime[i];
            if (loLim < low)
                loLim += prime[i];

            /*  Mark multiples of prime[i] in [low..high]:
                We are marking j - low for j, i.e. each number
                in range [low, high] is mapped to [0, high-low]
                so if range is [50, 100]  marking 50 corresponds
                to marking 0, marking 51 corresponds to 1 and
                so on. In this way we need to allocate space only
                for range  */
            for (int j=loLim; j<high; j+=prime[i])
                mark[j-low] = false;
        }

        // Numbers which are not marked as false are prime
        for (int i = low; i<high; i++)
            if (mark[i - low] == true)
                cout << i << "\n";

        // Update low and high for next segment
        low  = low + limit;
        high = high + limit;
        if (high >= n) high = n;
    }
}

bool isPrime(int n)
{
    // Corner cases
    if (n <= 1)  return false;
    if (n <= 3)  return true;

    // This is checked so that we can skip
    // middle five numbers in below loop
    if (n%2 == 0 || n%3 == 0) return false;

    for (int i=5; i*i<=n; i=i+6)
        if (n%i == 0 || n%(i+2) == 0)
           return false;

    return true;
}

int main() {
	int c;
	int a; int b;
	cin>>c;
	for (int i=0; i<c; i++) {
		cin>>a>>b;
		// if(a<=3){
		// 	if(a<2) a=2;
		// 	while(a<=3 && a<=b){
		// 		cout<<a<<'\n';
		// 		a++;
		// 	}
		// }
		// if (a == b) continue;
		segmentedSieve(a,b);
		// a = a - a%6 + 6;
		// for (int j=a; j-1<=b; j+=6) {
		// 	if(isPrime(j-1)) {
		// 		cout<<j-1<<'\n';
		// 	}
		// 	if(isPrime(j+1) && j+1<=b) {
		// 		cout<<j+1<<'\n';
		// 	}
		// }
	}
	return 0;
}