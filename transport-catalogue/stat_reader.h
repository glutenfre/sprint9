#pragma once

#include "transport_catalogue.h"

#include <string_view>

namespace T_catalogue {

namespace output {

void F(TransportCatalogue& my_trans_cat, std::string_view s_v);

void BusX(TransportCatalogue& my_trans_cat, std::string_view s_v);
void StopX(TransportCatalogue& my_trans_cat, std::string_view s_v);

}//namespace output
}//namespace Transport_catalogue
