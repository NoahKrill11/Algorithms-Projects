// You need to complete this program for a part of your first project.
//nlk34
// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>

// 'BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"
bool isPrime(BigUnsigned);
void checkPrime(BigUnsigned &);
void writeToFile(std::ofstream &,const BigUnsigned &, const BigUnsigned &);
BigUnsigned findCoPrime(BigUnsigned,BigUnsigned);

int main(){
	/* The library throws 'const char *' error messages when things go
	 * wrong.  It's a good idea to catch them using a 'try' block like this
	 * one.  Your C++ compiler might need a command-line option to compile
	 * code that uses exceptions. */
	try {
      srand(time(0));
      std::ofstream outfile("p_q.txt");
      std::ofstream e_nfile("e_n.txt");
      std::ofstream d_nfile("d_n.txt");
      std::cout << "a couple of test cases for 3460:435/535 Algorithms!!!\n";
      BigUnsigned P = BigUnsigned(1);
      for (int i=0;i<160;i++) {
         P = P*10 +rand();
        }
        checkPrime(P);
        std::cout << "my big1 !!!\n";
        std::cout << P << std::endl;
        BigUnsigned Q = BigUnsigned(1);
        for (int i=0;i<160;i++) {
         Q = Q*10 +rand();
        }
        checkPrime(Q);
        std::cout << "my big2 !!!\n";
        std::cout << Q<< std::endl;
        writeToFile(outfile,P,Q);
       
        std::cout << "my big3 = big1*big2 !!!\n";
        BigUnsigned N = P*Q;
        std::cout <<N<< std::endl;
        /*
        std::cout << "my big3/big2 !!!\n";
        std::cout <<N/Q << std::endl;
        */
        
        BigUnsigned PhiN = ((P-1)*(Q-1));
        
        BigUnsigned BigE = BigUnsigned(rand() % 999 + 100);
        

        BigE=findCoPrime(BigE,PhiN);
        
        BigUnsigned BigD = modinv(BigE, PhiN);
    
    	writeToFile(e_nfile, BigE, N);
    	
    	writeToFile(d_nfile, BigD, N);
    	   
    	   
	} catch(char const* err) {
		std::cout << "The library threw an exception:\n"
			<< err << std::endl;
	}

	return 0;
}
//Takes large generated number and determines if it is prime or not
bool isPrime(BigUnsigned big1)
{
for (BigUnsigned i = 1; i < 50; i++)
   {
      if(modexp(i, big1-1, big1) != 1)
        return false;
   }
   return true;
}
//Takes the not prime number and adds a value to it and calls the
//is prime function to test if the number is prime
void checkPrime(BigUnsigned & big)
{
    while (!isPrime(big))
    {
        big+=101;
        isPrime(big);
    }
}
//This writes the numbers generated onto a file for later use
void writeToFile(std::ofstream &outfile,const BigUnsigned &num, const BigUnsigned &num2)
{
	outfile << num <<std::endl;
	outfile << num2;
}
BigUnsigned findCoPrime(BigUnsigned BigE ,BigUnsigned PhiN)
{
    while(true)
       {
           //if e is not a co prime, add one and check again
           if(gcd(BigE,PhiN)!=1)
               BigE +=1;
           //if e is a co prime, return e
           if(gcd(BigE,PhiN) == 1)
               return BigE;
       }
}
