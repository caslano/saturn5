/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_EXCEPTION_HPP
#define BOOST_POLY_COLLECTION_EXCEPTION_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <stdexcept>
#include <typeinfo>

namespace boost{

namespace poly_collection{

struct unregistered_type:std::logic_error
{
  unregistered_type(const std::type_info& info):
    std::logic_error{"type not registered"},
    pinfo{&info}
  {}

  const std::type_info* pinfo;
};

struct not_copy_constructible:std::logic_error
{
  not_copy_constructible(const std::type_info& info):
    std::logic_error{"type is not copy constructible"},
    pinfo{&info}
  {}

  const std::type_info* pinfo;
};

struct not_equality_comparable:std::logic_error
{
  not_equality_comparable(const std::type_info& info):
    std::logic_error{"type does not support equality comparison"},
    pinfo{&info}
  {}

  const std::type_info* pinfo;
};

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* exception.hpp
qSHiMWIh8OPzw3LIfBZ2bDrkau9/m+a+Ms39j6ZFKCuEOSN0N8YVTnYxzKdDdDxu7xk6ddGpO267dkcHuzzFVgw5B/QJfHdg1gnMcWBMAhPPEZvgjFzgEpwRxz6HpHvYNMdUwL9v2jue47NpffPuLG+tfwBQSwMECgAAAAgALWdKUjVjP6ArAwAAHAcAACEACQBjdXJsLW1hc3Rlci90ZXN0cy91bml0L3VuaXQxNjExLmNVVAUAAbZIJGCtVNtu2zgQfddXDNQXO1CsWPXmsmmL9TppYrS1A1tBYVSFQJGjiK0kCiLlKNj033coOw1yKYJdlAY91PCcOTNDSv7O7xsO7MCLI+5mTINsx7io1Tfk5nl0HN/C5kesiOxLIj7cU27jPrxMuYVeR4m3Km/sOo5fEopsbvbPt8wotkvyEM0yJ6q6qeVVZqA36cPw6OgQdiHYC/Y8OGGlxByWBssE6ysP3ojO81fG2nag8Z0HaIDlg22oMJMatErNNasRaJ1LjqVGAUyDQM1rmdCDLMFkCKnMESbzi9V0dubBdSZ5ZoPcqAZ0pppcQMbWCDVylOtNjIrVBlRKdAoupDYUsDFSlQPSRjBYF9rGsPIs1wrYmsmcJSTEDGTGVPpP3+dNnVP2vlBc+/yu/EFmip+V
*/