#include "api06/way_handler.hpp"
#include "http.hpp"

#include <sstream>

using std::stringstream;
using std::list;

namespace api06 {

way_responder::way_responder(mime::type mt, osm_id_t id_, data_selection &w_)
	: osm_responder(mt, w_), id(id_) {
	list<osm_id_t> ids;

	check_visibility();

	ids.push_back(id);

	sel.select_ways(ids);
}

way_responder::~way_responder() {
}

way_handler::way_handler(FCGX_Request &request, osm_id_t id_) 
	: id(id_) {
}

way_handler::~way_handler() {
}

std::string 
way_handler::log_name() const {
	return "way";
}

responder_ptr_t 
way_handler::responder(data_selection &x) const {
	return responder_ptr_t(new way_responder(mime_type, id, x));
}

void
way_responder::check_visibility() {
	switch (sel.check_way_visibility(id)) {

	case data_selection::non_exist:
		throw http::not_found(""); // TODO: fix error message / throw structure to emit better error message
	
	case data_selection::deleted:
		throw http::gone(); // TODO: fix error message / throw structure to emit better error message
	}
}

} // namespace api06
