#ifndef BOOST_METAPARSE_V1_RETURN__HPP
#define BOOST_METAPARSE_V1_RETURN__HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/get_result.hpp>


#include <iostream>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class C>
      struct return_
      {
        typedef return_ type;
        
        template <class S, class Pos>
        struct apply : accept<C, S, Pos> {};
      };
    }
  }
}

#endif


/* return_.hpp
hfzpu53589ikpDokScPzkoZnT9p2fo1PyK9NCftIDfNowXkry3uFmZuenqZ7kzB+POfGxhesTsHfzDuhzwnFF4enD1HucJzOSRLK/iXvq+vkzVTTZ5nmwwmb1x0ZroBhlNaVYdzozDHF+oVINw2Mi/dHIUVReeSi5Sy0nEuNu2ViQv398AxsTPbEov1/cUhHv1BW9dAw/VMJz67KhWdX80Ts/MAfRYrYQ8yK+iWwentzMhvz
*/