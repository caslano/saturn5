#ifndef BOOST_METAPARSE_V1_ITERATE_HPP
#define BOOST_METAPARSE_V1_ITERATE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/iterate_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class N>
      struct iterate : iterate_c<P, N::type::value> {};
    }
  }
}

#endif


/* iterate.hpp
QXk7sAnPZQd2Zhd2YU+mcgx7cxwv4gT24TT252wO5Xxm8TFm8wleyk95GXfwcv7EUdxHuUYzv0+k4BwsOCdL7hNpiuVQgbfzSN7BYzmVtXgnG/IutuAM9udMDuF9nMJZvJv3803O4SrO5RrO42ecz01cwPz9R3COwt0ief9RSz2OYh3WYF12ZX1ew4a8kY14CxtzCpvxAbbgIrbk42zFZ9mGy9iW29heZM4v2JdVMdEyKMd1
*/