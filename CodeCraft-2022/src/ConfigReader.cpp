#include "includes.h"

int get_config(const char *path)
{
    ifstream config_ini(path);

    if (config_ini.is_open())
    {
        int qos_constraint = 0;
        string line;

        getline(config_ini, line);          // 跳过第一行
        line = std::regex_replace(line, std::regex("\r"), ""); // 去掉字符串中的 \r
        getline(config_ini, line);          // 读取第二行配置信息
        line = std::regex_replace(line, std::regex("\r"), ""); // 去掉字符串中的 \r

        char *strs = new char[line.length() + 1];
        strcpy(strs, line.c_str());         // 将 string 转化为 char*
        char *array = strtok(strs, "=");    // 将 char* 转化为数组
        array = strtok(NULL, "=");
        stringstream ss;
        ss.clear();
        ss.str(array);
        ss >> qos_constraint;               // 把字符串转化为整数

        return qos_constraint;
    }
    else
    {
        cout << "Open config.ini failed." << endl;
        exit(-1);
    }
}
