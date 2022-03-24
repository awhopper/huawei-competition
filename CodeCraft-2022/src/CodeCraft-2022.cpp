#include "includes.h"

int main() 
{
    vector<string> customer_name;
    vector<string> site_name;

    vector<vector<int>> v_demand = get_demand("../CodeCraft-2022/data/demand.csv", customer_name);
    // vector<vector<int>> v_demand = get_demand("/data/demand.csv", customer_name);

    vector<vector<int>> v_qos = get_qos("../CodeCraft-2022/data/qos.csv");
    // vector<vector<int>> v_qos = get_qos("/data/qos.csv");

    vector<vector<int>> v_site_bandwidth = get_site_bandwidth("../CodeCraft-2022/data/site_bandwidth.csv", site_name);
    // vector<vector<int>> v_site_bandwidth = get_site_bandwidth("/data/site_bandwidth.csv", site_name);

    int qos_constraint = get_config("../CodeCraft-2022/data/config.ini");
    // int qos_constraint = get_config("/data/config.ini");

    distribute(v_demand, v_site_bandwidth, v_qos, qos_constraint, customer_name, site_name);

    return 0;
}
