/**
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * This file is part of openstreetmap-cgimap (https://github.com/zerebubuth/openstreetmap-cgimap/).
 *
 * Copyright (C) 2009-2025 by the openstreetmap-cgimap developer community.
 * For a full list of authors see the git log.
 */

#ifndef ROUTES_HPP
#define ROUTES_HPP

#include "cgimap/handler.hpp"

// internal implementation of the routes
struct router;
struct request;

/**
 * encapsulates routing (URL to handler mapping) information, similar in
 * intent, if not form, to rails' routes.rb.
 */
class routes {
public:
  routes();
  ~routes();

  routes(const routes &) = delete;
  routes& operator=(const routes &) = delete;
  routes(routes &&) = delete;
  routes& operator=(routes &&) = delete;

  /**
   * returns the handler which matches a request, or throws a 404 error.
   */
  std::unique_ptr<handler> operator()(request &req) const;

private:
  std::unique_ptr<router> get_default_router();
  std::unique_ptr<router> get_experimental_router();

  // common prefix of all routes
  const std::string_view common_prefix;

  // object which actually does the routing.
  const std::unique_ptr<router> r;

#ifdef ENABLE_API07
  // common prefix of API 0.7 routes.
  const std::string experimental_prefix;

  // and an API 0.7 router object
  const std::unique_ptr<router> r_experimental;
#endif /* ENABLE_API07 */
};

#endif /* ROUTES_HPP */
