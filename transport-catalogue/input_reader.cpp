// напишите решение с нуля
// код сохраните в свой git-репозиторий

#include "input_reader.h"
#include "stat_reader.h"
#include "transport_catalogue.h"

#include <algorithm>
#include <iostream>
#include <exception>

namespace T_catalogue {

namespace input {

void Work_with(std::istream& input) {

    std::vector< std::string > all_requests;
    std::string s;
    while (std::getline(input, s)) {
        all_requests.push_back(s);
    }

    T_catalogue::input::Read(all_requests);

}

void Read(const std::vector< std::string >& input_set) {
    int k = std::stoi(input_set.front());
    TransportCatalogue my_trans_cat;

    for (int i = 1; i <= k; ++i) {
        const std::string& s = input_set[i];
        if (s.substr(0, 4) == "Stop")
            ReadStops(my_trans_cat, s);
    }//прочитали все остановки 

    for (int i = 1; i <= k; ++i) {
        const std::string& s = input_set[i];
        if (s.substr(0, 4) == "Stop")
            ReadStopsWithDim(my_trans_cat, s);
    }//прочитали расстояния между остановками (еще раз пройтись посоветовали в практикуме)

    for (int i = 1; i <= k; ++i) {
        const std::string& s = input_set[i];
        if (s.substr(0, 3) == "Bus")
            ReadBusses(my_trans_cat, s);
    }
    int m = std::stoi(input_set[k + 1]);
    for (int i = k + 2; i <= m + k + 1; ++i) {
        T_catalogue::output::F(my_trans_cat, input_set[i]);
        //OutputBusX(my_trans_cat, input_set[i]);
    }
}

void ReadStops(TransportCatalogue& my_trans_cat, std::string_view s_v) {
    //string_view примет строку
    s_v.remove_prefix(5);
    auto k = s_v.find(":");
    std::string_view name = s_v.substr(0, k);
    s_v.remove_prefix(k + 2);

    k = s_v.find(",");
    std::string_view lat = s_v.substr(0, k);
    s_v.remove_prefix(k + 2);

    k = s_v.find(",");
    if (k == std::string::npos) {
        k = s_v.back();
    }
    std::string_view longy = s_v.substr(0, k);

    my_trans_cat.Add_stop(std::string(name),
        std::stod(std::string(lat)), std::stod(std::string(longy)));
}

void ReadStopsWithDim(TransportCatalogue& my_trans_cat, std::string_view s_v) {
    s_v.remove_prefix(5);
    auto k = s_v.find(":");
    std::string_view name = s_v.substr(0, k);

    k = s_v.find(",");
    s_v.remove_prefix(k + 2);
    k = s_v.find(",");
    if (k == std::string::npos) {
        s_v.remove_prefix(s_v.size());
    }
    else {
        s_v.remove_prefix(k + 2);
    }

    while (!s_v.empty()) {
        auto k = s_v.find("m");
        std::string_view dimension = s_v.substr(0, k);
        s_v.remove_prefix(k + 5);

        std::string_view sec_stop = s_v;//просто так 
        k = s_v.find(",");
        if (k == std::string::npos) {
            sec_stop = s_v;
            s_v.remove_prefix(s_v.size());
        }
        else {
            sec_stop = s_v.substr(0, k);
            s_v.remove_prefix(k + 2);
        }
        my_trans_cat.AddDim(std::pair(name, sec_stop), std::stoi(std::string(dimension)));

    }
}

void ReadBusses(TransportCatalogue& my_trans_cat, std::string_view s_v) {
    s_v.remove_prefix(4);
    auto k = s_v.find(":");
    std::string_view name = s_v.substr(0, k);
    s_v.remove_prefix(k + 2);

    char type = ' ';
    bool is_it_circle = false;

    if (s_v.find(">") != std::string::npos) {
        type = '>';
        is_it_circle = true;
    }
    else if (s_v.find("-") != std::string::npos) {
        type = '-';
        is_it_circle = false;
    }
    //else throw std::exception("One stop on the route!!! =-0");

    std::vector<std::string_view> stop_names;

    while (!s_v.empty()) {
        std::string_view stop_name;
        k = s_v.find(type);
        if (k == std::string::npos) {
            stop_name = s_v;
            s_v.remove_prefix(s_v.size());
        }
        else {
            stop_name = s_v.substr(0, k - 1);
            s_v.remove_prefix(k + 2);
        }
        stop_names.push_back(stop_name);
    }
    my_trans_cat.Add_bus(name, is_it_circle, stop_names);
}
}//namespace Input
}//namespace Transport_catalogue
