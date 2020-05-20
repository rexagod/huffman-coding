# Huffman Coding
A C++ compression and decompression program based on Huffman Coding.

## Group Members
1. Pranshu Srivastava - 9917103250 - F8
2. Subhradip Mukherjee - 9917103234 - F7
3. Prashant Dixit - 9917103209 - F7
4. Karan Dev Tyagi - 9917103081 - F3

## Introduction
The following code uses Huffman coding algorithm which encodes any text file. Normal encoding converts evey character into 8 bits regardless of the frequency of the character appearing in it, but the logic behind Huffman coding is it encodes according to the frequency of characters i.e. the character having max frequency require very less bits for representation and character having less frequency take more bits. Since the max frequency character are more prominent and represented with less number of bits so overall encoding size decreases, hence acting as compressor as well.

## Implementation Details
The programs can compress and decompress text file consisting of 128 ASCII characters.

## Compression
- Open input file, count and store the frequencies of different characters;
- Construct Priority Queue and then Huffman Tree;
- Calculate Huffman Encode Table;
- Encode the file, store Huffman Encode Table and encoded to the desired file.

## Decompression
- Open file, recreate Huffman Tree based on Huffman Encode Table;
- Decode the file based on the tree and store it to the desired file.
