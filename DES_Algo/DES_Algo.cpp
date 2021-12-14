
#include <iostream>
#include "string.h"
#include <string>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
using namespace std;


#ifdef __GNUC__
#define __rdtsc __builtin_ia32_rdtsc
#else
#include <intrin.h>
#endif

typedef unsigned long long u64;

u64 key_generated[17];

int permuted_Choice1[56] = { 57, 49, 41, 33, 25, 17, 9,
                      1, 58, 50, 42, 34, 26, 18,
                      10, 2, 59, 51, 43, 35, 27,
                      19, 11, 3, 60, 52, 44, 36,
                      63, 55, 47, 39, 31, 23, 15,
                      7, 62, 54, 46, 38, 30, 22,
                      14, 6, 61, 53, 45, 37, 29,
                      21, 13, 5, 28, 20, 12, 4 };

int permuted_Choice2[48] = { 14, 17, 11, 24, 1, 5,
                     3, 28, 15, 6, 21, 10,
                     23, 19, 12, 4, 26, 8,
                     16, 7, 27, 20, 13, 2,
                     41, 52, 31, 37, 47, 55,
                     30, 40, 51, 45, 33, 48,
                     44, 49, 39, 56, 34, 53,
                     46, 42, 50, 36, 29, 32 };



int initial_perm[64] = { 58, 50, 42, 34, 26, 18, 10, 2,
                       60, 52, 44, 36, 28, 20, 12, 4,
                       62, 54, 46, 38, 30, 22, 14, 6,
                       64, 56, 48, 40, 32, 24, 16, 8,
                       57, 49, 41, 33, 25, 17, 9, 1,
                       59, 51, 43, 35, 27, 19, 11, 3,
                       61, 53, 45, 37, 29, 21, 13, 5,
                       63, 55, 47, 39, 31, 23, 15, 7 };


int inverse_initial_perm[64] = { 40, 8, 48, 16, 56, 24, 64, 32,
                       39, 7, 47, 15, 55, 23, 63, 31,
                       38, 6, 46, 14, 54, 22, 62, 30,
                       37, 5, 45, 13, 53, 21, 61, 29,
                       36, 4, 44, 12, 52, 20, 60, 28,
                       35, 3, 43, 11, 51, 19, 59, 27,
                       34, 2, 42, 10, 50, 18, 58, 26,
                       33, 1, 41, 9, 49, 17, 57, 25 };

int permutation[32] = { 16, 7, 20, 21,
                    29, 12, 28, 17,
                    1, 15, 23, 26,
                    5, 18, 31, 10,
                    2, 8, 24, 14,
                    32, 27, 3, 9,
                    19, 13, 30, 6,
                    22, 11, 4, 25 };

int expansion_perm[48] = { 32, 1, 2, 3, 4, 5, 4, 5,
               6, 7, 8, 9, 8, 9, 10, 11,
               12, 13, 12, 13, 14, 15, 16, 17,
               16, 17, 18, 19, 20, 21, 20, 21,
               22, 23, 24, 25, 24, 25, 26, 27,
               28, 29, 28, 29, 30, 31, 32, 1 };

int S_box1[64] = { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
                       0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
                       4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
                       15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 };

int S_box2[64] = { 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
                      3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
                      0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
                      13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 };

int S_box3[64] = { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
                      13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
                      13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
                      1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 };

int S_box4[64] = { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
                      13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
                      10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
                      3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 };


int S_box5[64] = { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
                      14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
                      4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
                      11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 };



int S_box6[64] = { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
                      10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
                      9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
                      4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 };


int S_box7[64] = { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
                      13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
                      1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
                      6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 };


int S_box8[64] = { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
                      1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
                      7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
                      2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 };

int left_shift_table[16] = { 1, 1, 2, 2,
                          2, 2, 2, 2,
                          1, 2, 2, 2,
                          2, 2, 2, 1 };



u64 permutation_choice1(u64 key)
{

    u64 out = 0;
    for (int i = 0; i < 56; i++) {
        out |= ((key >> (64 - permuted_Choice1[i])) & 1) << 56 - (i + 1);


    }

    return out;
}

u64 permutation_choice2(u64 key_after_shift)
{

    u64 out = 0;
    for (int i = 0; i < 48; i++) {
        out |= ((key_after_shift >> (56 - permuted_Choice2[i])) & 1) << 48 - (i + 1);
    }
    return out;
}

u64 Initial_permutation_txt(u64 plain_txt) {
    u64 out = 0;
    for (int i = 0; i < 64; i++) {
        out |= ((plain_txt >> (64 - initial_perm[i])) & 1) << 64 - (i + 1);
    }
    return out;

}
unsigned int permutation_txt(unsigned int out_sBox)
{
    unsigned int out = 0;
    for (int i = 0; i < 32; i++) {
        out |= ((out_sBox >> (32 - permutation[i])) & 1) << 32 - (i + 1);
    }
    return out;
}

u64 inversePermutation(u64 after_swap) {
    u64 out = 0;
    for (int i = 0; i < 64; i++) {
        out |= ((after_swap >> (64 - inverse_initial_perm[i])) & 1) << 64 - (i + 1);
    }
    return out;

}


u64 Expansion_plainText(u64 right_plain_text) {

    u64 out = 0;
    for (int i = 0; i < 48; i++) {
        out |= ((right_plain_text >> (32 - expansion_perm[i])) & 1) << 48 - (i + 1);

    }
    return out;

}

u64 rotate_left(u64 key, int round_no) {


    u64 left = (key >> 28) & 0xFFFFFFF;
    u64 right = key & 0xFFFFFFF;

    left = ((left << left_shift_table[round_no - 1]) & 0x000000000FFFFFFF) | (left >> 28 - left_shift_table[round_no - 1]);
    right = ((right << left_shift_table[round_no - 1]) & 0x000000000FFFFFFF) | (right >> 28 - left_shift_table[round_no - 1]);

    u64 result = (left << 28) | right;
    return result;
}

void generate_keys(u64 key_permuted1) {
    int permuted_Choice2[48] = { 14, 17, 11, 24, 1, 5,
                         3, 28, 15, 6, 21, 10,
                         23, 19, 12, 4, 26, 8,
                         16, 7, 27, 20, 13, 2,
                         41, 52, 31, 37, 47, 55,
                         30, 40, 51, 45, 33, 48,
                         44, 49, 39, 56, 34, 53,
                         46, 42, 50, 36, 29, 32 };
    u64 key_after_shift[17];
    key_after_shift[0] = key_permuted1; //this is the key after permuted choice1

    for (int i = 1; i < 17; i++) {
        key_after_shift[i] = rotate_left(key_after_shift[i - 1], i); 
        key_generated[i] = permutation_choice2(key_after_shift[i]);
       
    }


}


unsigned int s_box(u64 input_to_box, int* S_box) {

    //unsigned int s_box(u64 input_to_box, int count) {
    unsigned int column = (input_to_box >> 1) & 0xF;
    unsigned int row = (input_to_box & 1) | ((input_to_box >> 4) & 2);
    unsigned int out_in_box;

    out_in_box = S_box[column + row * 16];

    return out_in_box;

}


u64 Round(u64 key, u64 plain_txt, int round_no) {

    unsigned int left_plain_text = (plain_txt >> 32) & (0xFFFFFFFF); //make sure of this int 
    unsigned int right_plain_text = plain_txt & 0xFFFFFFFF;

    u64 plain_text_after_Expan = Expansion_plainText(right_plain_text);
    u64 plain_txt_before_sBOX = (plain_text_after_Expan & 0xFFFFFFFFFFFF) ^ (key & 0xFFFFFFFFFFFF);

    unsigned int six_1 = (plain_txt_before_sBOX >> 42) & 0x3F;
    unsigned int six_2 = (plain_txt_before_sBOX >> 36) & 0x3F;
    unsigned int six_3 = (plain_txt_before_sBOX >> 30) & 0x3F;
    unsigned int six_4 = (plain_txt_before_sBOX >> 24) & 0x3F;
    unsigned int six_5 = (plain_txt_before_sBOX >> 18) & 0x3F;
    unsigned int six_6 = (plain_txt_before_sBOX >> 12) & 0x3F;
    unsigned int six_7 = (plain_txt_before_sBOX >> 6) & 0x3F;
    unsigned int six_8 = (plain_txt_before_sBOX) & 0x3F;

    unsigned int result_sBox1 = s_box(six_1, S_box1);
    unsigned int result_sBox2 = s_box(six_2, S_box2);
    unsigned int result_sBox3 = s_box(six_3, S_box3);
    unsigned int result_sBox4 = s_box(six_4, S_box4);
    unsigned int result_sBox5 = s_box(six_5, S_box5);
    unsigned int result_sBox6 = s_box(six_6, S_box6);
    unsigned int result_sBox7 = s_box(six_7, S_box7);
    unsigned int result_sBox8 = s_box(six_8, S_box8);


    unsigned int ordered_1 = (result_sBox1 << 28) & 0xF0000000;
    unsigned int ordered_2 = (result_sBox2 << 24) & 0x0F000000;
    unsigned int ordered_3 = (result_sBox3 << 20) & 0x00F00000;
    unsigned int ordered_4 = (result_sBox4 << 16) & 0x000F0000;
    unsigned int ordered_5 = (result_sBox5 << 12) & 0x0000F000;
    unsigned int ordered_6 = (result_sBox6 << 8) & 0x00000F00;
    unsigned int ordered_7 = (result_sBox7 << 4) & 0x000000F0;
    unsigned int ordered_8 = (result_sBox8) & 0x0000000F;

    unsigned int final_Result_sBox = ordered_1 | ordered_2 | ordered_3 | ordered_4 | ordered_5 | ordered_6 | ordered_7 | ordered_8;


    unsigned int permuted_txt = permutation_txt(final_Result_sBox);

    u64 end_round_right = ((u64)(permuted_txt ^ left_plain_text)) & 0x00000000FFFFFFFF;

    u64 plain_txt_next_round = (((u64)right_plain_text) << 32) | end_round_right;

    return plain_txt_next_round;


}


int main(int argc, char* argv[]) {
    string input_user;
    string plain_text_in;
    string key_in;

    input_user = argv[1]; //encrypt or decrypt
    plain_text_in = argv[2];
    key_in = argv[3];
  
    u64 plain_text_in_long = stoull(plain_text_in, NULL, 16);
    u64 key_in_long = stoull(key_in, NULL, 16);


    u64 key_permuted1 = permutation_choice1(key_in_long);
    
    generate_keys(key_permuted1);

    u64 plain_txt_after_initial = Initial_permutation_txt(plain_text_in_long);

    u64 plain_txt_round = plain_txt_after_initial;

    long long t1 = __rdtsc();

    if (input_user == "encrypt") {
        for (int i = 1; i < 17; i++) {
            plain_txt_round = Round(key_generated[i], plain_txt_round, i);
            
        }
    }

    else if (input_user == "decrypt") {
        for (int i = 1; i < 17; i++) {
            plain_txt_round = Round(key_generated[17 - i], plain_txt_round, i);
           
        }



    }
    /*SWAPPING*/

    u64 new_right = (plain_txt_round >> 32) & 0x00000000FFFFFFFF;
    u64 new_left = (plain_txt_round << 32) & 0xFFFFFFFF00000000;

    u64 swap_result = new_right | new_left;

    u64 final_output = inversePermutation(swap_result);

    long long t2 = __rdtsc();

    if (input_user == "encrypt") {
        printf("cipher: %016llX\n", final_output);
    }

    else if (input_user == "decrypt") {
        printf("plain: %016llX\n", final_output);
    }
    cout << "cycles: " << t2 - t1 << endl;


}