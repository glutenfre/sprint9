// напишите решение с нуля
// код сохраните в свой git-репозиторий

#include "stat_reader.h"
#include "transport_catalogue.h"

#include <iostream>
#include <iomanip>
#include <string>

namespace T_catalogue {

namespace output {

void F(TransportCatalogue& my_trans_cat, std::string_view s_v) {
    if (s_v.substr(0, 3) == "Bus") {
        T_catalogue::output::BusX(my_trans_cat, s_v);
    }
    else if (s_v.substr(0, 4) == "Stop") {
        T_catalogue::output::StopX(my_trans_cat, s_v);
    }
}

void BusX(TransportCatalogue& my_trans_cat, std::string_view s_v) {
    s_v.remove_prefix(4);
    auto bus_name_to_find = s_v;

    if (!(my_trans_cat.IsEmpty(bus_name_to_find))) {
        std::cout << "Bus " << bus_name_to_find << ": not found" << std::endl;
    }
    else {
        std::cout << "Bus " << bus_name_to_find << ": "
            << my_trans_cat.FindBus(bus_name_to_find).path_stops.size()
            << " stops on route, "
            << my_trans_cat.GetBusData(bus_name_to_find).unique_stops
            << " unique stops, " << std::setprecision(6)
            << my_trans_cat.GetBusData(bus_name_to_find).route_length
            << " route length, " << std::setprecision(6)
            << my_trans_cat.GetBusData(bus_name_to_find).curvation
            << " curvature"
            << std::endl;
    }
}

void StopX(TransportCatalogue& my_trans_cat, std::string_view s_v) {
    s_v.remove_prefix(5);

    if (my_trans_cat.StopExist(s_v)) {
        std::set<std::string_view> perm_set = my_trans_cat.GetStopData(s_v);//не нравится, что создала целый вектор вместо просто вызова этой функции
        if (perm_set.empty()) {
            std::cout << "Stop " << s_v << ": no buses" << std::endl;
        }
        else {
            std::cout << "Stop " << s_v << ": buses";
            for (const std::string_view s : perm_set) {
                std::cout << " " << s;
            }
            std::cout << std::endl;
        }
    }
    else {
        std::cout << "Stop " << s_v << ": not found" << std::endl;
    }

}
}//namespace output
}//namespace Transport_catalogue
