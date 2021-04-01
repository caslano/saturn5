#ifndef BOOST_METAPARSE_V1_LIT_HPP
#define BOOST_METAPARSE_V1_LIT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/lit_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class C>
      struct lit : lit_c<C::type::value> {};
    }
  }
}

#endif


/* lit.hpp
idRSNO3sR4QHKvXbBCTFHTahib9+kPcg/FMw4pVEcPRDj+TR6q7FmJDoiNuTSj7SH9a+/cwSOUU/cfTH6lMgNcCelVobWpcndv5RUY7byK0iwvVhhnRgXzvZD3+XyQcrxIb4CfPo5foXfWqetXMg2FgjQpaQL1NyaEpNy3G6gaxJGujxrX5UwVRkzNFw1UjUhSkq6sceMF1hZ2kbbBHr9N4MfK8N+BMEzgUkllrgyY359uK4b89Zb5PchX8Gw0klRVIdoC/4+PgNpfYfW+OLuesqMlfcaBJYh3WCUJBtodke4NyD1ZQ1BVQbIbjWuaXheclmMirLmHvpBQGkaAWFuwHnlGT4g9OfW6YmUd6UwmqBPU/dg9f2k7Cfp044qHYv50VI+DpEr9PNg55+vw7BrJTiTl3FYOnIhf1aK/Lq4YMZ2HHGnbrZQfSIS8P5hEmyNlEcldgtcM+Ax/zvm1XPP0+tgbVmwUbY3MUVkHD/slxRTptR2R1zyxPGMV/4iAT+aS42zvQyVxLmUINhHQ4CobK/CgzZeLLHhRa5h6Ru/ex9s8CbMTHDGkHzDA==
*/