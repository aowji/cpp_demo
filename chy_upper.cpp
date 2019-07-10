#include <string>
#include <stdexcept>
#include <functional>
#include <iostream>
#include <fstream>
#include <vector>
#include <Windows.h>


#define ZHENG u8"整"
std::vector<std::string> num = { u8"零", u8"壹", u8"贰", u8"叁", u8"肆", u8"伍", u8"陆", u8"柒", u8"捌", u8"玖" };
std::vector<std::string> unit = { u8"仟", u8"佰", u8"拾", u8"亿", u8"仟", u8"佰", u8"拾", u8"万", u8"仟", u8"佰", u8"拾", u8"元", u8"角", u8"分" };
uint8_t mode[14] = {0,0,0,1, 0,0,0,1, 0,0,0,3, 2,2};

std::string upper(double number){
    if(number >= 100000000000){
        throw std::logic_error(u8"超出1000亿");
    }

    uint8_t numeric[14];
    auto int_part = (uint64_t)number;
    auto decimal = (uint8_t)((number - int_part) * 100);
    numeric[13] = decimal % 10;
    numeric[12] = decimal / 10;
    auto tmp_int = int_part;
    for(int i = 11; i >= 0; i--){
        numeric[i] = tmp_int % 10;
        tmp_int = tmp_int / 10;
    }


    std::string str = "";
    bool zero_flag = false;
    for(int i = 0; i < 14; i++){
        auto m = mode[i];
        if(m == 0){
            // 默认
            if(numeric[i] != 0){
                if(zero_flag){
                    str += num[0];
                    zero_flag = false;
                }
				str += num[numeric[i]];
				str += unit[i];
            } else if(str.length() != 0){
                zero_flag = true;
            }
        }
        else if(m == 1){
            // 亿，万
            if(numeric[i] != 0){
                if(zero_flag){
                    str += num[0];
                    zero_flag = false;
                }
				str += num[numeric[i]];
				str += unit[i];
            } else {
                int x = numeric[i - 3] * 1000 + numeric[i - 2] * 100 + numeric[i - 1];
                if(x > 0){
                    str += unit[i];
                }
            }
            zero_flag = false;
        }
        else if(m == 2){
            // 角分
            if(numeric[i] != 0){
				str += num[numeric[i]];
				str += unit[i];
            }
        }
        else if(m == 3){
            // 元
            if(numeric[i] != 0){
                if(zero_flag){
                    str += num[0];
                    zero_flag = false;
                }
				str += num[numeric[i]];
				str += unit[i];
            }
            else{
                if(int_part > 0){
                    str += unit[i];
                }
            }
        }
    }

    if(decimal == 0 && int_part > 0){
        str += ZHENG;
    }

    return str;
}


int main(int argc, char **argv){
    if(argc == 2){
        double num = std::stod(argv[1]);
        auto str = upper(num);

		setlocale(LC_ALL, "en_US.utf8");
        std::mbstate_t state = std::mbstate_t();
		const char* mbstr = str.c_str();
        std::size_t len = 1 + std::mbsrtowcs(NULL, &mbstr, 0, &state);
        std::vector<wchar_t> wstr(len);
        std::mbsrtowcs(&wstr[0], &mbstr, wstr.size(), &state);

        std::wcout << &wstr[0] << std::endl;
    }
	return 0;
}


