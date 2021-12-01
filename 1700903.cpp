#include <string>
#include <iostream>
#include <algorithm>
#ifdef __GNUC__
#define __rdtsc __builtin_ia32_rdtsc
#else
#include <intrin.h>
#endif

typedef unsigned long long u64;

u64 hex_to_binary(std::string hex_string)
{
    return stoull(hex_string, nullptr, 16);
}

u64 permute(u64 str_binary, u64 permutation[], int old_size, int new_size)
{
    u64 permuted_binary = 0;
    for (int i = 0; i < new_size; i++)
        permuted_binary |= (str_binary >> (old_size - permutation[i]) & 1) << new_size - (i + 1);

    return permuted_binary;
}

u64 permute_init(u64 plain_text_binary)
{
    u64 initial_permutation[64] = {58, 50, 42, 34, 26, 18, 10, 2,
                                   60, 52, 44, 36, 28, 20, 12, 4,
                                   62, 54, 46, 38, 30, 22, 14, 6,
                                   64, 56, 48, 40, 32, 24, 16, 8,
                                   57, 49, 41, 33, 25, 17, 9, 1,
                                   59, 51, 43, 35, 27, 19, 11, 3,
                                   61, 53, 45, 37, 29, 21, 13, 5,
                                   63, 55, 47, 39, 31, 23, 15, 7};

    return permute(plain_text_binary, initial_permutation, 64, 64);
}

u64 permute_choice_1(u64 key_64_bit)
{
    u64 choice_1_permutation[56] = {57, 49, 41, 33, 25, 17, 9,
                                    1, 58, 50, 42, 34, 26, 18,
                                    10, 2, 59, 51, 43, 35, 27,
                                    19, 11, 3, 60, 52, 44, 36,
                                    63, 55, 47, 39, 31, 23, 15,
                                    7, 62, 54, 46, 38, 30, 22,
                                    14, 6, 61, 53, 45, 37, 29,
                                    21, 13, 5, 28, 20, 12, 4};

    return permute(key_64_bit, choice_1_permutation, 64, 56);
}

u64 permute_choice_2(u64 key_64_bit)
{
    u64 choice_2_permutation[48] = {14, 17, 11, 24, 1, 5,
                                    3, 28, 15, 6, 21, 10,
                                    23, 19, 12, 4, 26, 8,
                                    16, 7, 27, 20, 13, 2,
                                    41, 52, 31, 37, 47, 55,
                                    30, 40, 51, 45, 33, 48,
                                    44, 49, 39, 56, 34, 53,
                                    46, 42, 50, 36, 29, 32};

    return permute(key_64_bit, choice_2_permutation, 56, 48);
}

u64 shift_left_circular_28_bits(u64 str, int shift_amount)
{
    return ((str << shift_amount) | (str >> (28 - shift_amount))) & 0x0fffffff;
}

u64 text_expand_48_bits(u64 right_plain_text)
{
    u64 expansion_permutation[48] = {32, 1, 2, 3, 4, 5, 4, 5,
                                     6, 7, 8, 9, 8, 9, 10, 11,
                                     12, 13, 12, 13, 14, 15, 16, 17,
                                     16, 17, 18, 19, 20, 21, 20, 21,
                                     22, 23, 24, 25, 24, 25, 26, 27,
                                     28, 29, 28, 29, 30, 31, 32, 1};

    return permute(right_plain_text, expansion_permutation, 32, 48);
}

u64 s_box(u64 key_rpt_xor_res)
{

    u64 s_box_permutation[] = {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
                               0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
                               4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
                               15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13,
                               15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
                               3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
                               0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
                               13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9,
                               10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
                               13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
                               13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
                               1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12,
                               7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
                               13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
                               10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
                               3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14,
                               2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
                               14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
                               4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
                               11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3,
                               12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
                               10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
                               9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
                               4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13,
                               4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
                               13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
                               1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
                               6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12,
                               13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
                               1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
                               7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
                               2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11};

    u64 s_box_output = 0;
    for (int i = 0; i < 8; i++)
    {
        u64 *box_index = s_box_permutation + i * 64;
        u64 idx = key_rpt_xor_res >> (7 - i) * 6 & 0x3F;
        idx = idx >> 1 & 15 | (idx & 1) << 4 | idx & 0x20;
        s_box_output |= box_index[idx] << (7 - i) * 4;
    }
    return s_box_output;
}

u64 after_s_box_permute(u64 s_box_output)
{
    u64 permutation[32] = {16, 7, 20, 21,
                           29, 12, 28, 17,
                           1, 15, 23, 26,
                           5, 18, 31, 10,
                           2, 8, 24, 14,
                           32, 27, 3, 9,
                           19, 13, 30, 6,
                           22, 11, 4, 25};

    return permute(s_box_output, permutation, 32, 32);
}

u64 permute_final(u64 str)
{
    u64 final_perm[64] = {40, 8, 48, 16, 56, 24, 64, 32,
                          39, 7, 47, 15, 55, 23, 63, 31,
                          38, 6, 46, 14, 54, 22, 62, 30,
                          37, 5, 45, 13, 53, 21, 61, 29,
                          36, 4, 44, 12, 52, 20, 60, 28,
                          35, 3, 43, 11, 51, 19, 59, 27,
                          34, 2, 42, 10, 50, 18, 58, 26,
                          33, 1, 41, 9, 49, 17, 57, 25};

    return permute(str, final_perm, 64, 64);
}

u64 encrypt(std::string data_in, u64 keys_binary[])
{
    u64 data = hex_to_binary(data_in);
    data = permute_init(data);
    u64 data_left = (data >> 32) & 0xFFFFFFFF;
    u64 data_right = data & 0xFFFFFFFF;

    for (size_t i = 0; i < 16; i++)
    {
        u64 data_right_expanded = text_expand_48_bits(data_right);

        u64 key_rpt_xor_res = keys_binary[i] ^ data_right_expanded;
        u64 s_box_result = s_box(key_rpt_xor_res);
        u64 s_box_permutation = after_s_box_permute(s_box_result);
        data_left = s_box_permutation ^ data_left;
        if (i != 15)
        {
            u64 temp = data_left;
            data_left = data_right;
            data_right = temp;
        }
    }

    u64 cipher = permute_final((data_left << 32) | data_right);
    return cipher;
}
int main(int argc, char *argv[])
{

    int shift_table[16] = {1, 1, 2, 2,
                           2, 2, 2, 2,
                           1, 2, 2, 2,
                           2, 2, 2, 1};

    std::string operation = argv[1], data = argv[2], key = argv[3];
    u64 key_64_bits = hex_to_binary(key);
    u64 key_56_bits = permute_choice_1(key_64_bits);
    u64 key_28_left = (key_56_bits >> 28) & 0x0FFFFFFF;
    u64 key_28_right = key_56_bits & 0x0FFFFFFF;

    u64 round_keys_binary[16] = {0};
    for (int i = 0; i < 16; i++)
    {
        key_28_left = shift_left_circular_28_bits(key_28_left, shift_table[i]);
        key_28_right = shift_left_circular_28_bits(key_28_right, shift_table[i]);

        u64 key_48_bit = permute_choice_2((key_28_left << 28) | key_28_right);
        round_keys_binary[i] = key_48_bit;
    }

    if (operation == "encrypt")
    {
        long long t1 = __rdtsc();
        u64 cipher = encrypt(data, round_keys_binary);
        long long t2 = __rdtsc();
        printf("Cipher: %016llX\nCycles: %lld\n", cipher, t2 - t1);
    }

    if (operation == "decrypt")
    {
        std::reverse(round_keys_binary, round_keys_binary + 16);
        long long t1 = __rdtsc();
        u64 text = encrypt(data, round_keys_binary);
        long long t2 = __rdtsc();
        printf("Plain: %016llX\nCycles: %lld\n", text,  t2 - t1);
    }

    return 0;
}