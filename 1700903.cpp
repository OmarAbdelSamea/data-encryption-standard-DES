#include <string>
#include <iostream>
#include <sstream>
#include <bitset>
#include <algorithm>

std::string hex_to_binary(std::string hex_string)
{
    std::stringstream strs;
    strs << std::hex << hex_string;
    unsigned long long num;
    strs >> num;
    std::bitset<64> bit_set_obj(num);
    return bit_set_obj.to_string();
}

std::string discard_bits_64_to_56(std::string key_64_binary)
{

    std::cout << *(key_64_binary.begin() + 7) << '\n';
    std::string key_56_binary;
    // for (size_t i = 1; i < 9; i++)
    // {
    //     key_64_binary.erase(key_64_binary.begin() + (7 * i));
    // }
    for (size_t i = 0, j = 0; i < key_64_binary.length(); i++, j++)
    {
        if ((i + 1) % 8 == 0 && i != 0)
        {
            j--;
            continue;
        }

        key_56_binary[j] = key_64_binary[i];
    }

    return key_56_binary;
}

std::string initial_permutation(std::string plain_text_binary)
{
    int initial_perm[64] = {58, 50, 42, 34, 26, 18, 10, 2,
                            60, 52, 44, 36, 28, 20, 12, 4,
                            62, 54, 46, 38, 30, 22, 14, 6,
                            64, 56, 48, 40, 32, 24, 16, 8,
                            57, 49, 41, 33, 25, 17, 9, 1,
                            59, 51, 43, 35, 27, 19, 11, 3,
                            61, 53, 45, 37, 29, 21, 13, 5,
                            63, 55, 47, 39, 31, 23, 15, 7};

    std::string permuted_text_binary = "";
    for (size_t i = 0; i < plain_text_binary.length(); i++)
        permuted_text_binary.push_back(plain_text_binary[initial_perm[i] - 1]);

    return permuted_text_binary;
}

std::string shift_left_reversal(std::string str, int shift_amount)
{
    std::reverse(str.begin(), str.begin() + shift_amount);
    std::reverse(str.begin() + shift_amount, str.end());
    std::reverse(str.begin(), str.end());

    return str;
}

std::string key_transformation(std::string key_56_bit, int round_number)
{
    int shift_amount;
    if (round_number == 1 || round_number == 2 || round_number == 9 || round_number == 16)
        shift_amount = 1;
    else
        shift_amount = 2;

    std::string key_28_left = key_56_bit.substr(0, key_56_bit.length()/2);
    std::string key_28_right = key_56_bit.substr(key_56_bit.length()/2);

    shift_left_reversal(key_28_left, shift_amount);
    shift_left_reversal(key_28_right, shift_amount);

}

int main(int argc, char *argv[])
{
    // std::string operation = argv[1], data = argv[2], key = argv[3];
    std::string operation = "encrypt", data = "123", key = "1233445A6D788381";
    std::string key_64_bits = hex_to_binary(key);
    // std::string key_56_bits = discard_bits_64_to_56(key_64_bits);

    return 0;
}