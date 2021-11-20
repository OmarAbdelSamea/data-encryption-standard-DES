#include <string>
#include <iostream>
#include <sstream>
#include <bitset>
#include <algorithm>
#include <vector>

std::string hex_to_binary(std::string hex_string)
{
    std::stringstream strs;
    strs << std::hex << hex_string;
    unsigned long long num;
    strs >> num;
    std::bitset<64> bit_set_obj(num);
    return bit_set_obj.to_string();
}

std::string binary_to_hex(std::string binary_string)
{
    std::stringstream ss;
    ss << std::hex << std::stoull(binary_string, NULL, 2);
    std::string s = ss.str();
    std::transform(s.begin(), s.end(), s.begin(), std::ptr_fun<int, int>(std::toupper));
    return s;
}

std::string permutate(std::string str_binary, int permutation[], int new_size)
{
    std::string permuted_str_binary;
    for (size_t i = 0; i < new_size; i++)
        permuted_str_binary.push_back(str_binary[permutation[i] - 1]);

    return permuted_str_binary;
}

std::string permutate_init(std::string plain_text_binary)
{
    int initial_permutation[64] = {58, 50, 42, 34, 26, 18, 10, 2,
                                   60, 52, 44, 36, 28, 20, 12, 4,
                                   62, 54, 46, 38, 30, 22, 14, 6,
                                   64, 56, 48, 40, 32, 24, 16, 8,
                                   57, 49, 41, 33, 25, 17, 9, 1,
                                   59, 51, 43, 35, 27, 19, 11, 3,
                                   61, 53, 45, 37, 29, 21, 13, 5,
                                   63, 55, 47, 39, 31, 23, 15, 7};

    return permutate(plain_text_binary, initial_permutation, 64);
}

std::string permutate_choice_1(std::string key_64_bit)
{
    int choice_1_permutation[56] = {57, 49, 41, 33, 25, 17, 9,
                                    1, 58, 50, 42, 34, 26, 18,
                                    10, 2, 59, 51, 43, 35, 27,
                                    19, 11, 3, 60, 52, 44, 36,
                                    63, 55, 47, 39, 31, 23, 15,
                                    7, 62, 54, 46, 38, 30, 22,
                                    14, 6, 61, 53, 45, 37, 29,
                                    21, 13, 5, 28, 20, 12, 4};

    return permutate(key_64_bit, choice_1_permutation, 56);
}

std::string permutate_choice_2(std::string key_64_bit)
{
    int choice_2_permutation[48] = {14, 17, 11, 24, 1, 5,
                                    3, 28, 15, 6, 21, 10,
                                    23, 19, 12, 4, 26, 8,
                                    16, 7, 27, 20, 13, 2,
                                    41, 52, 31, 37, 47, 55,
                                    30, 40, 51, 45, 33, 48,
                                    44, 49, 39, 56, 34, 53,
                                    46, 42, 50, 36, 29, 32};

    return permutate(key_64_bit, choice_2_permutation, 48);
}

std::string shift_left_reversal(std::string str, int shift_amount)
{
    std::reverse(str.begin(), str.begin() + shift_amount);
    std::reverse(str.begin() + shift_amount, str.end());
    std::reverse(str.begin(), str.end());

    return str;
}

std::string key_compress_48_bit(std::string key_56_bit, int shift_amount)
{
    shift_left_reversal(key_56_bit, shift_amount);
    shift_left_reversal(key_56_bit, shift_amount);

    return permutate_choice_2(key_56_bit + key_56_bit);
}

std::string text_expand_48_bits(std::string right_plain_text)
{
    int expansion_permutation[48] = {32, 1, 2, 3, 4, 5, 4, 5,
                                     6, 7, 8, 9, 8, 9, 10, 11,
                                     12, 13, 12, 13, 14, 15, 16, 17,
                                     16, 17, 18, 19, 20, 21, 20, 21,
                                     22, 23, 24, 25, 24, 25, 26, 27,
                                     28, 29, 28, 29, 30, 31, 32, 1};

    return permutate(right_plain_text, expansion_permutation, 48);
}

std::string xor_48_binary(std::string num_1, std::string num_2)
{
    std::bitset<48> num_1_binary(num_1), num_2_binary(num_2);
    std::bitset<48> result = num_1_binary ^ num_2_binary;
    return result.to_string();
}

std::string xor_32_binary(std::string num_1, std::string num_2)
{
    std::bitset<32> num_1_binary(num_1), num_2_binary(num_2);
    std::bitset<32> result = num_1_binary ^ num_2_binary;
    return result.to_string();
}

std::string s_box(std::string key_rpt_xor_res)
{

    int s_box_permutation[8][4][16] = {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
                                        0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
                                        4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
                                        15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
                                       {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
                                        3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
                                        0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
                                        13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},
                                       {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
                                        13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
                                        13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
                                        1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
                                       {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
                                        13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
                                        10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
                                        3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},
                                       {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
                                        14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
                                        4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
                                        11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},
                                       {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
                                        10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
                                        9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
                                        4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},
                                       {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
                                        13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
                                        1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
                                        6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
                                       {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
                                        1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
                                        7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
                                        2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}};
    std::string s_box_output = "";
    for (int i = 0; i < 8; i++)
    {
        int row = 2 * int(key_rpt_xor_res[i * 6] - '0') + int(key_rpt_xor_res[i * 6 + 5] - '0');
        int col = 8 * int(key_rpt_xor_res[i * 6 + 1] - '0') + 4 * int(key_rpt_xor_res[i * 6 + 2] - '0') + 2 * int(key_rpt_xor_res[i * 6 + 3] - '0') + int(key_rpt_xor_res[i * 6 + 4] - '0');
        int val = s_box_permutation[i][row][col];
        std::bitset<4> value_binary(val);
        s_box_output.append(value_binary.to_string());
    }
    return s_box_output;
}

std::string after_s_box_permutate(std::string s_box_output)
{
    int permutation[32] = {16, 7, 20, 21,
                           29, 12, 28, 17,
                           1, 15, 23, 26,
                           5, 18, 31, 10,
                           2, 8, 24, 14,
                           32, 27, 3, 9,
                           19, 13, 30, 6,
                           22, 11, 4, 25};

    return permutate(s_box_output, permutation, 32);
}

std::string permutate_final(std::string str)
{
    int final_perm[64] = {40, 8, 48, 16, 56, 24, 64, 32,
                          39, 7, 47, 15, 55, 23, 63, 31,
                          38, 6, 46, 14, 54, 22, 62, 30,
                          37, 5, 45, 13, 53, 21, 61, 29,
                          36, 4, 44, 12, 52, 20, 60, 28,
                          35, 3, 43, 11, 51, 19, 59, 27,
                          34, 2, 42, 10, 50, 18, 58, 26,
                          33, 1, 41, 9, 49, 17, 57, 25};

    return permutate(str, final_perm, 64);
}

std::string encrypt(std::string data, std::vector<std::string> keys_binary, std::vector<std::string> keys)
{
    data = hex_to_binary(data);
    data = permutate_init(data);

    std::string data_left = data.substr(0, 32);
    std::string data_right = data.substr(32, 32);

    for (size_t i = 0; i < 16; i++)
    {
        std::string data_right_expanded = text_expand_48_bits(data_right);

        std::string key_rpt_xor_res = xor_48_binary(keys_binary[i], data_right_expanded);
        std::string s_box_result = s_box(key_rpt_xor_res);
        std::string s_box_permutation = after_s_box_permutate(s_box_result);
        data_left = xor_32_binary(s_box_permutation, data_left);
        if (i != 15)
        {
            std::swap(data_left, data_right);
        }
    }

    std::string combine = data_left + data_right;
    std::string cipher = permutate_final(combine);
    return cipher;
}
int main(int argc, char *argv[])
{

    int shift_table[16] = {1, 1, 2, 2,
                           2, 2, 2, 2,
                           1, 2, 2, 2,
                           2, 2, 2, 1};

    std::string operation = argv[1], data = argv[2], key = argv[3];
    std::string key_64_bits = hex_to_binary(key);
    std::string key_56_bits = permutate_choice_1(key_64_bits);

    std::string key_28_left = key_56_bits.substr(0, 28);
    std::string key_28_right = key_56_bits.substr(28);

    std::vector<std::string> round_keys_binary; 
    std::vector<std::string> round_keys; 
    for (int i = 0; i < 16; i++)
    {
        key_28_left = shift_left_reversal(key_28_left, shift_table[i]);
        key_28_right = shift_left_reversal(key_28_right, shift_table[i]);
        
        std::string key_48_bit = permutate_choice_2(key_28_left + key_28_right);

        round_keys_binary.push_back(key_48_bit);
        round_keys.push_back(binary_to_hex(key_48_bit));
    }

    if (operation == "encrypt")
    {
        std::string cipher = encrypt(data, round_keys_binary, round_keys);
        std::cout << "cipher: " << binary_to_hex(cipher) << '\n';
    }

    if (operation == "decrypt")
    {
        reverse(round_keys_binary.begin(), round_keys_binary.end());
        reverse(round_keys.begin(), round_keys.end());
        std::string text = encrypt(data, round_keys_binary, round_keys);
        std::cout << "plain: " << binary_to_hex(text) << '\n';
    }

    return 0;
}