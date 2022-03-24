#pragma once

#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
using namespace std;

vector<vector<int>> get_demand(const char *path, vector<string> &customer_name);
vector<vector<int>> get_qos(const char *path);
vector<vector<int>> get_site_bandwidth(const char *path, vector<string> &site_name);
int get_config(const char *path);
void distribute(vector<vector<int>> v_demand, vector<vector<int>> v_site_bandwidth,
                vector<vector<int>> v_qos, int qos_constraint,
                vector<string> &customer_name, vector<string> & site_name);
void submit(vector<string> result);
