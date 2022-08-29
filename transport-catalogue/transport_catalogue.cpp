// напишите решение с нуля
// код сохраните в свой git-репозиторий

#include "transport_catalogue.h"
#include "geo.h"

#include <algorithm>
#include <iostream>

namespace T_catalogue {

void TransportCatalogue::Add_stop(std::string s, double lat, double longy) {
    //Stop stop_to_push = {s, lat, long };
    Stop stop_to_push;
    stop_to_push.name = std::move(s);
    stop_to_push.xy.lat = lat;
    stop_to_push.xy.lng = longy;
    Stops.push_back(stop_to_push);
    Stopname_to_stop[Stops.back().name] = &Stops.back();
    AddBusToStop(Stops.back().name);
}
void TransportCatalogue::Add_bus(std::string_view name, bool is_it_circle, std::vector<std::string_view> stop_names) {
    //здесь очень большая сложность получается 
    //так же не работает с одной остановкой в маршруте - нужно минимум две

    Bus perm_bus;
    perm_bus.name = std::move(name);
    for (int i = 0; i < stop_names.size(); i++) {
        perm_bus.path_stops.push_back(&FindStop(stop_names[i]));
    }
    Busses.push_back(perm_bus);
    Busname_to_bus[Busses.back().name] = &Busses.back();

    for (int i = 0; i < Busses.back().path_stops.size(); i++) {
        AddBusToStop(Busses.back().path_stops[i]->name, Busses.back().name);//не нравится что я добавила еще один цикл вместо того, чтобы делать все в первом
    }

    if (!is_it_circle) {
        for (int i = stop_names.size() - 2; i >= 0; i--) {//идем с предпоследнего эл-та к первому
            FindBus(name).path_stops.push_back(&FindStop(stop_names[i]));
        }
    }

}

void TransportCatalogue::AddBusToStop(std::string_view stop_name, std::string_view bus_name) {
    if (Busnames_to_stop.count(stop_name) == 0) {
        Busnames_to_stop[stop_name];
    }
    Busnames_to_stop.at(stop_name).insert(bus_name);
}

void TransportCatalogue::AddBusToStop(std::string_view stop_name) {
    if (Busnames_to_stop.count(stop_name) == 0) {
        Busnames_to_stop[stop_name];
    }
}

Bus& TransportCatalogue::FindBus(std::string_view bus_name_to_find) {//возвращает ссылку на эл-т
    return *Busname_to_bus.at(bus_name_to_find);
    //я хочу чтобы через результат этой ф-ии можно было менять этот маршрут
}

Stop& TransportCatalogue::FindStop(std::string_view stop_name_to_find) {
    return *Stopname_to_stop.at(stop_name_to_find);
}

Bus_data TransportCatalogue::GetBusData(std::string_view bus_name_to_find) {
    Bus_data res;
    res.route_length = 0;
    res.curvation = 0;
    double perm_curvation = 0;
    Stop* stop_from = FindBus(bus_name_to_find).path_stops.at(0);
    Stop* stop_to = FindBus(bus_name_to_find).path_stops.at(0);// что-то для функции вычисления расстояния

    std::unordered_set<std::string_view> unique_stops;//уникальные остановки - беру от сюда размер контейнера

    for (int i = 0; i < FindBus(bus_name_to_find).path_stops.size(); i++) {
        unique_stops.insert(FindBus(bus_name_to_find).path_stops.at(i)->name);
        if (i > 0) {
            stop_from = stop_to;
        }
        stop_to = FindBus(bus_name_to_find).path_stops.at(i);
        perm_curvation += ComputeDistance(stop_from->xy, stop_to->xy);
        if (StopToStopDimention.count(std::pair(stop_from, stop_to)) > 0) {
            res.route_length += FindDim(stop_from->name, stop_to->name);
        }
        else if (StopToStopDimention.count(std::pair(stop_to, stop_from)) > 0) {
            res.route_length += FindDim(stop_to->name, stop_from->name);
        }
    }

    res.unique_stops = unique_stops.size();
    res.curvation = res.route_length / perm_curvation;

    return res;
}

bool TransportCatalogue::IsEmpty(std::string_view bus_name_to_find) {
    if (Busname_to_bus.count(bus_name_to_find) > 0) {
        return true;
    }
    return false;
}

std::set<std::string_view> TransportCatalogue::GetStopData(std::string_view stop_name_to_find) {
    return Busnames_to_stop.at(stop_name_to_find);
}

bool TransportCatalogue::StopExist(std::string_view stop_name_to_find) {
    if (Busnames_to_stop.count(stop_name_to_find) > 0) {
        return true;
    }
    return false;
}

void TransportCatalogue::AddDim(std::pair<std::string_view, std::string_view > stops_pair, int dimension) {
    StopToStopDimention[std::pair(&FindStop(stops_pair.first), &FindStop(stops_pair.second))] = dimension;
}

int TransportCatalogue::FindDim(std::string_view stop1_name_to_find, std::string_view stop2_name_to_find) {
    /*if (StopToStopDimention.count(std::pair(&FindStop(stop1_name_to_find), &FindStop(stop2_name_to_find))) > 0) {
        return StopToStopDimention.at(std::pair(&FindStop(stop1_name_to_find), &FindStop(stop2_name_to_find)));
    }else {
        return 0;
    }*/
    return StopToStopDimention.at(std::pair(&FindStop(stop1_name_to_find), &FindStop(stop2_name_to_find)));
}

}//namespace Transport_catalogue
