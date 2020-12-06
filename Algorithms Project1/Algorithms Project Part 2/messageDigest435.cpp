

#include <string.h>
#include <iostream>
#include <fstream>
#include "sha256.h"
#include "BigIntegerLibrary.hh"

 
int main(int argc, char *argv[])
{
   //Second part of your project starts here
    if ((argc != 4 && argc != 3) || (argv[1][0]!='s' && argv[1][0]!='v'))
      std::cout << "wrong format! should be \"a.exe s filename\"\n";
   else {
      std::string filename = argv[2];
      //read the file
      std::streampos begin,end;
      std::ifstream myfile (filename.c_str(), std::ios::binary);
      begin = myfile.tellg();
      myfile.seekg (0, std::ios::end);
      end = myfile.tellg();
      std::streampos size = end-begin;
      
      myfile.seekg (0, std::ios::beg);
      char * memblock = new char[size];
      myfile.read (memblock, size); //read file; it's saved in the char array memblock
      myfile.close();
      
      std::string copyOFfile = filename+".Copy";
      std::ofstream myfile2 (copyOFfile.c_str(), std::ios::binary);
      myfile2.write (memblock, size); //write to a file
      myfile2.close();
      
      std::cout<<memblock;
        
      if (argv[1][0]=='s') {
         std::cout << "\n"<<"Need to sign the doc.\n";
         // Create sha256 hash of message
         std::string content_hash = sha256(memblock);
         // Convert hash from base 16 to base 10
         BigUnsignedInABase hash(content_hash, 16);
         // Assign to a standard BigUnsigned
         BigUnsigned hash_converted = hash;
         // Open d_n file and store each value in a string
         std::ifstream dn_file;
         dn_file.open("d_n.txt");
         std::string d_str, n_str;
         dn_file >> d_str;
         dn_file >> n_str;
         dn_file.close();
         // Convert d and n to BigUnsigned
         BigUnsigned d = stringToBigUnsigned(d_str);
         BigUnsigned n = stringToBigUnsigned(n_str);
         // Decrypt hash base 10 of message
         BigUnsigned signature = modexp(hash_converted, d, n);
         // Store signature
         std::ofstream sig_file;
         sig_file.open(filename+".signature");
         sig_file << signature << std::endl;
         sig_file.close();
      }
      else {
          std::cout << "\n"<<"Need to verify the doc.\n";
         // Contains signature file name
         std::string signed_file = argv[2];
         // Create sha256 hash of message
         std::string content_hash = sha256(memblock);
         // Convert hash from base 16 to base 10
         BigUnsignedInABase hash(content_hash, 16);
         // Assign to a standard BigUnsigned
         BigUnsigned hash_converted = hash;
         // Retrieve signature
          std::ifstream sig_file;
          sig_file.open(signed_file);
          std::string signature;
          
          sig_file >> signature;
          BigUnsigned sig_converted = stringToBigUnsigned(signature);
         // Retrieve e and n
         std::ifstream en_file;
         en_file.open("e_n.txt");
         std::string e_str;
         std::string n_str;
         en_file >> e_str;
         en_file >> n_str;
         en_file.close();
         // Convert e and n to BigUnsigned
         BigUnsigned e = stringToBigUnsigned(e_str);
         BigUnsigned n = stringToBigUnsigned(n_str);
         // Encrypt signature
         BigUnsigned encrypted = modexp(sig_converted, e, n);
          
          
          
         if (encrypted == hash_converted)
         {
            std::cout << "The document is authentic!\n";
         }
         else
         {
            std::cout << "The document has been modified!\n";
         }
        }
      delete[] memblock;
    }
    return 0;
}
