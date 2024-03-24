#include <iostream>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

/*std::string remove_spaces(std::string s){
        std::string result = "";
        for (int i = 0; i < s.size(); ++i){
                if (s[i] != ' ' && s[i] != '\n'){
                        result += s[i];
                }
        }
        return result;
}

bool is_digit(std::string s){
        if (s.size() == 0) return false;
        for (int i = 0; i < s.size(); ++i){
                if (s[i] != '0' && s[i] != '1' && s[i] != '2' && s[i] != '3' && s[i] != '4' && s[i] != '5' && s[i] != '6' && s[i] != '7' && s[i] != '8' && s[i] != '9' && s[i] != '.'){
                        return false;
                }
        }
        return true;
}*/

int main(){
        auto dirIter = std::filesystem::directory_iterator("DATA");
        int file_count = 0;
        for (auto& entry : dirIter){
                if (entry.is_regular_file()){
                        ++file_count;
                }
        }
        int CASE_COUNT = file_count / 2;

        double TIME_LIMIT;
        int scores[CASE_COUNT];

        std::ifstream config_file("DATA\\config.txt");
        config_file >> TIME_LIMIT;
        int KILL_TIME_LIMIT;
        config_file >> KILL_TIME_LIMIT;
        int achievable_score = 0;
        for (int i = 0; i < CASE_COUNT; ++i){
                config_file >> scores[i];
                achievable_score += scores[i];
        }

        // measured in seconds

        //std::string sub_ofile_name = "submission_output.out";
        std::cout << "Time Limit: " << TIME_LIMIT << "s" << " | "<< "Absolute Time Limit: " << KILL_TIME_LIMIT << "s" << "\n";
        std::cout << "\n";

        int final_score = 0;

        int compile_result = std::system("g++ submission.cpp -o submission 2> NUL");
        if (compile_result != 0){
                std::cerr << "Compilation error\n";
                std::cout << "\n" << "Score: " << final_score << "/" << achievable_score << "\n";
                return 1;
        }

        for (int i = 0; i < CASE_COUNT; ++i){
                std::cout << "Case " << i+1 << ": ";

                //std::string timed_command = ".\\scripts\\timer.bat \"submission.exe < " + IFILE + " > " + sub_ofile_name + " \" > time.out";

                std::system(("type DATA\\" + std::to_string(i) + ".in > input.temp").c_str());
                std::system(("type DATA\\" + std::to_string(i) + ".out > output.temp").c_str());
                
                int start_r = std::system("start \"\" /b cmd /c \"scripts\\timed_command.bat\" ");
                //int ping_r = std::system(("ping 127.0.0.1 -n " + KILL_TIME_LIMIT + " -w 1000 > NUL").c_str());
                int ping_r = std::system(("timeout /nobreak /T " + std::to_string(KILL_TIME_LIMIT) + " > NUL").c_str());
                int kill_r = std::system("tasklist | find \"submission.exe\" > NUL && taskkill /f /im submission.exe > NUL 2> NUL");
        

                double time;
                std::ifstream time_file("time.temp");
                time_file >> time;
                time_file.close();

                if (kill_r == 0){
                        std::cout << "TLEK - " << "0/" << scores[i] << " - " << ">" << KILL_TIME_LIMIT << "s\n";
                        continue;
                }

                if (!time){
                        std::cout << "WA   - ";
                        std::cout << "0/" << scores[i] << " -  ";
                        std::cout << std::setprecision(4) << (double)time << "s\n";
                        continue;
                }
                if (time > TIME_LIMIT){
                        std::cout << "TLE  - " << "0/" << scores[i] << " -  " << time << "s" << " > " << TIME_LIMIT << "s\n";
                        continue;
                }

                std::string line;
                std::string sline;
                std::ifstream answers("output.temp");
                std::ifstream sub_o("sub_output.temp");

                bool WA = false;
                while (getline(answers, line)){
                        if (!getline(sub_o, sline)){
                                WA = true;
                                break;
                        }
                        if (sline != line){
                                WA = true;
                                break;
                        }
                }
                sub_o.close();
                answers.close();
                

                if (WA){
                        std::cout << "WA   - ";
                        std::cout << "0/" << scores[i] << " -  ";
                        std::cout << std::setprecision(4) << (double)time << "s\n";
                } else { 
                        std::cout << "AC   - ";
                        std::cout << scores[i] << "/" << scores[i] << " -  ";
                        std::cout << std::setprecision(4) << (double)time << "s\n";
                        final_score += scores[i];
                }
        }
        fs::remove("input.temp");
        fs::remove("output.temp");
        fs::remove("time.temp");
        fs::remove("sub_output.temp");

        std::cout << "\n" << "Score: " << final_score << "/" << achievable_score << "\n";

        std::cout << "Press any key 3 times to exit\n";
        std::system("timeout -1");
        std::system("timeout -1");
        std::system("timeout -1");
        
        return 0;
}