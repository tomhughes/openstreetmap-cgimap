/**
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * This file is part of openstreetmap-cgimap (https://github.com/zerebubuth/openstreetmap-cgimap/).
 *
 * Copyright (C) 2009-2025 by the openstreetmap-cgimap developer community.
 * For a full list of authors see the git log.
 */

#ifndef TEXT_RESPONDER_HPP
#define TEXT_RESPONDER_HPP

#include "cgimap/handler.hpp"
#include "cgimap/mime_types.hpp"

#include <string>
#include <chrono>
#include <vector>

/**
 * utility class - use this as a base class when the derived class is going to
 * respond with a text response
 */
class text_responder : public responder {
public:
  // construct, passing the mime type down to the responder.
  // optional bounds are stored at this level, but available to derived classes.
  explicit text_responder(mime::type);

  ~text_responder() override = default;

  // lists the standard types that OSM format can respond in
  std::vector<mime::type> types_available() const override;

  void write(output_formatter& f,
             const std::string &generator,
             const std::chrono::system_clock::time_point &now) override;

protected:
  std::string output_text;
};

#endif /* TEXT_RESPONDER_HPP */
