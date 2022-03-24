#include "includes.h"

vector<vector<int>> get_site_bandwidth(const char *path, vector<string> &site_name)
{
    string line;            // 用于保存从文件中读取的一行
    stringstream ss;        // 用于将读取的一行转化为整形数字
    int temp;               // 用于暂时存储转化后的数字
    vector<vector<int>> vv; // 用于保存文件的二维 vector

    // 读文件（相对路径是相对与可执行文件）
    ifstream site_bandwidth_csv(path);

    if (site_bandwidth_csv.is_open())
    {
        getline(site_bandwidth_csv, line);             // 读取第一行标题
        line = std::regex_replace(line, std::regex("\r"), ""); // 去掉字符串中的 \r

        while (getline(site_bandwidth_csv, line))      // 读取从第二行开始的数据
        {
            line = std::regex_replace(line, std::regex("\r"), ""); // 去掉字符串中的 \r
            char *strs = new char[line.length() + 1];
            strcpy(strs, line.c_str());         // 将 string 转化为 char*
            char *array = strtok(strs, ",");    // 将 char* 转化为数组

            site_name.push_back(array);         // 读取 site_name 放入 vector

            vector<int> v;
            while (array)
            {
                ss.clear();
                ss.str(array);
                ss >> temp;                     // 把字符串转化为整数
                v.push_back(temp);              // 存储到 queue 中
                array = strtok(NULL, ",");
            }
            vv.push_back(v);
        }

        return vv;
    }
    else
    {
        cout << "Open site_bandwidth.csv failed." << endl;
        exit(-1);
    }

}
