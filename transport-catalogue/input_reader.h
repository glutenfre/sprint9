#pragma once

#include "transport_catalogue.h"

#include <istream>
#include <string>
#include <vector>
#include <string_view>

namespace T_catalogue {

namespace input {

void Work_with(std::istream& input);

void Read(const std::vector< std::string >& input_set);

void ReadStops(TransportCatalogue& my_trans_cat, std::string_view s_v);

void ReadStopsWithDim(TransportCatalogue& my_trans_cat, std::string_view s_v);

void ReadBusses(TransportCatalogue& my_trans_cat, std::string_view s_v);

}//namespace Insert
}//namespace Transport_catalogue
