#pragma once

#include "geo.h"

#include <string>// указываем библиотеки в header
#include <vector>
#include <string_view>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <utility>
#include <functional>


struct Stop {//структура остановки, можно сделать через unordered_map< string, Coordinates xy >
    std::string name;
    Coordinates xy;
};// нужна ; после структуры

struct Bus {
    std::string name;
    std::vector<Stop*> path_stops;
};

struct Bus_data {
    int unique_stops;
    int route_length;
    double curvation;
};

template<>
struct std::hash< std::pair<Stop*, Stop*> > {
    size_t operator()(const std::pair<Stop*, Stop*>& my_pair) const {
        return std::hash<void*>{}(my_pair.first) + std::hash<void*>{}(my_pair.second) * 37;
    }
};

namespace T_catalogue {

class TransportCatalogue {
public:
    void Add_stop(std::string s, double lat, double longy);//добавление остановки
    void Add_bus(std::string_view name, bool is_it_circle, std::vector<std::string_view> stop_names);//добавление маршрута в базу
    void AddBusToStop(std::string_view stop_name, std::string_view bus_name);
    void AddBusToStop(std::string_view stop_name);
    Bus& FindBus(std::string_view bus_name_to_find);//поиск маршрута по имени
    Stop& FindStop(std::string_view stop_name_to_find);//поиск остановки по имени
    Bus_data GetBusData(std::string_view bus_name_to_find);//получение информации о маршруте
    bool IsEmpty(std::string_view bus_name_to_find);//проверяю, существует ли автобус с таким названием
    std::set<std::string_view> GetStopData(std::string_view stop_name_to_find);//поиск массива автобусов остановки по ее имени
    bool StopExist(std::string_view stop_name_to_find);//проверяю, существует ли остановка 
    void AddDim(std::pair<std::string_view, std::string_view > stops_pair, int dimension);
    int FindDim(std::string_view stop1_name_to_find, std::string_view stop2_name_to_find);

private:
    std::deque< Stop > Stops;//здесь хранятся остановки - имя и две координаты
    std::unordered_map< std::string_view, Stop* > Stopname_to_stop; //это массив указателей на остановки - название и указатель на основной дэк
    //здесь должен был быть const Stop*, но я не поняла как это реализовать, если координаты остановок могут меняться 

    std::deque< Bus > Busses;//здесь хранятся автобусы - имя и все остановки
    std::unordered_map< std::string_view, Bus* > Busname_to_bus; //это массив указателей на название и указатель на основной дэк
    //здесь должен был быть const Bus*, но я не поняла как это реализовать, если маршруты могут меняться 

    std::unordered_map< std::string_view, std::set<std::string_view> > Busnames_to_stop;
    //это массив указателей на название остановки и вектор указателей на проезжающие ее автобусы

    std::unordered_map<std::pair<Stop*, Stop*>, int> StopToStopDimention;//контейнер, содержащий пару остановок и расстояние между ними

};
}//namespace Transport_catalogue
