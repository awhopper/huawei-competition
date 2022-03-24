#include "includes.h"

// 直接传参，考虑深拷贝和浅拷贝问题，会造成内存开销（但是我们不希望改变原值，所以就这样用吧）
void distribute(vector<vector<int>> v_demand, vector<vector<int>> v_site_bandwidth,
                vector<vector<int>> v_qos, int qos_constraint,
                vector<string> &customer_name, vector<string> & site_name)
{
    vector<string> result; // 把结果放入 result 容器中

    // 遍历二维 vector v_demand
    for (unsigned int t = 0; t < v_demand.size(); t++) // 遍历 所有时刻，小 t 下标来表示某个时刻
    {
        cout << endl << "demand.csv line number: " << t + 2;

        // 计算 每个时刻 所有的客户节点 的 总需求 和 平均值
        cout << endl << "demand: ";
        for (unsigned int customer_id = 1; customer_id < v_demand[t].size(); customer_id++)
        {
            cout << v_demand[t][customer_id] << ", ";
        }
        cout << endl;

        // 当前占用的带宽`会`立刻在下一个时刻释放，这样才能满足压测
        vector<vector<int>> site_bw_temp = v_site_bandwidth;
        for (unsigned int customer_id = 1; customer_id < v_demand[t].size(); customer_id++)
        {
            string r = ""; // 用于拼接结果字符串，然后输出到 solution.txt

            // 输出格式：customer_ID1:<site_id_1,bandwidth_1>,<site_id_2, bandwidth _2>...
            r = r + customer_name[customer_id] + ":";
            cout << customer_name[customer_id] << ":";

            // 暴力分配（将一个边缘节点的带宽占用完后，我们再使用下一个边缘节点）
            unsigned int site_id = 0;
            while (v_demand[t][customer_id] > 0 && site_id < site_bw_temp.size())
            {
                // 将客户节点的带宽分配给一个或多个边缘节点
                // 如果这个边缘节点的带宽能满足，那么就分配
                if (v_demand[t][customer_id] <= site_bw_temp[site_id][1] 
                            && v_qos[site_id][customer_id] < qos_constraint
                            && v_demand[t][customer_id] != 0)
                {
                    // 边缘节点带宽减少，客户节点带宽减少
                    site_bw_temp[site_id][1] -= v_demand[t][customer_id];
                    
                    // 记录一下分配了多少
                    r = r + "<" + site_name[site_id] + "," + to_string(v_demand[t][customer_id]) + ">";
                    cout << "<" << site_name[site_id] << "," << v_demand[t][customer_id] << ">";

                    v_demand[t][customer_id] = 0;
                    if (site_bw_temp[site_id][1] == 0) // 用光了这个边缘节点的带宽
                    {
                        site_id++;
                    }
                }
                else if (v_demand[t][customer_id] > site_bw_temp[site_id][1] 
                            && v_qos[site_id][customer_id] < qos_constraint 
                            && site_bw_temp[site_id][1] != 0)
                {
                    // 如果这个边缘节点的可用带宽不足了，那么把它剩余的带宽分完
                    v_demand[t][customer_id] -= site_bw_temp[site_id][1];
                    
                    // 记录一下分配了多少
                    r = r + "<" + site_name[site_id] + "," + to_string(site_bw_temp[site_id][1]) + ">,";
                    cout << "<" << site_name[site_id] << "," << site_bw_temp[site_id][1] << ">,";     
                    
                    site_bw_temp[site_id][1] = 0;
                    // 继续找下一个边缘节点能用的带宽
                    site_id++;
                }
                else
                {
                    // 如果 QoS 不满足，直接找下一个节点
                    site_id++;
                }
            }

            result.push_back(r);
            cout << endl;
        }
    }
    
    submit(result);

    return;
}
