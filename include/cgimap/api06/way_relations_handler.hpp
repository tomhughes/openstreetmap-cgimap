#ifndef API06_WAY_RELATIONS_HANDLER_HPP
#define API06_WAY_RELATIONS_HANDLER_HPP

#include "cgimap/handler.hpp"
#include "cgimap/osm_current_responder.hpp"
#include "cgimap/request.hpp"
#include <string>

namespace api06 {

class way_relations_responder : public osm_current_responder {
public:
  way_relations_responder(mime::type, osm_nwr_id_t, data_selection_ptr &);
  ~way_relations_responder();

private:
  osm_nwr_id_t id;

  bool is_visible();
};

class way_relations_handler : public handler {
public:
  way_relations_handler(request &req, osm_nwr_id_t id);
  ~way_relations_handler();

  std::string log_name() const;
  responder_ptr_t responder(data_selection_ptr &x) const;

private:
  osm_nwr_id_t id;
};

} // namespace api06

#endif /* API06_WAY_RELATIONS_HANDLER_HPP */
