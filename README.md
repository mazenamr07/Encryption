# Encryption
This tool was made as an assignment for college.

it's used for encrypting or decrypting messages using various cyphers.
To start using it,
simply choose whether to encrypt or decrypt,
then select a cypher, then put in your message.

## Prerequisites
- **g++ compiler**

## Compilation and execution
1. Create a build directory:
```Bash
mdkir build
cd build
```
2. Run CMake:
```Bash
cmake ..
```
3. Buil the project:
```Bash
make
```
4. Execute the program:
```Bash
./Encryption
```

### List of cyphers available:
+ *** Cypher
+ Polybius Square Cypher, notes:
  + Special characters don't get encrypted
  + This cypher can't encrypt numbers
+ XOR Cypher, outputs:
  + Cyphered message
  + Hexadecimal hash to use for deciphering
+ *** Cypher
