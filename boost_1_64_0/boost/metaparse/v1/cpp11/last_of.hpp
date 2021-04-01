#ifndef BOOST_METAPARSE_V1_CPP11_LAST_OF_HPP
#define BOOST_METAPARSE_V1_CPP11_LAST_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/impl/nth_of_c.hpp>

#include <boost/metaparse/v1/fail.hpp>
#include <boost/metaparse/v1/error/index_out_of_range.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class... Ps>
      struct last_of
      {
        typedef last_of type;

        template <class S, class Pos>
        struct apply : impl::nth_of_c<sizeof...(Ps) - 1, S, Pos, Ps...> {};
      };

      template <>
      struct last_of<> : fail<error::index_out_of_range<0, -1, 0>> {};
    }
  }
}

#endif


/* last_of.hpp
ZLuJWrWNyUKBq4oDig+4TxdO2WOen2q3VULE7O6WLEWALXSP4ROWaH5nQY8ufPeI5mKY7fw1J4MxLm6LrrikjgHljbbsGFFJusH4RXS5I47nMw04UwdAMAxNB3qrbhe/w4H+/C35BphAbAwzwA8hpacExcy0WeidLpLzgICO0MrK/yPHbMNspxhhjtOsIv5rj2OdbRgXl3v+sERm+TPcotKmip0B5tRxpsWt70otJU6GtAlk2Qr1C11iXP6NbQwvbtrQVoSyrUot3kTHNghrpP4owhzY32WyzhF3v+nhoJ9ZMbJ/XVAS4dL6b8od6m7N4vRlSlPPyU0sBebd4azWAhorN5a2Dmixes3FtvSbefIT1CUfJfN39JbpBZkfnRyv+vs/bLIZUihJYAa+QsELVJYWWLPpuV6yOVCu/eUh5NB2T9obHayBOJcmDaXk3TK901x7mOLNNCn5FpmKzM1jqC20G+d3KBZvr/vf89xuCJMVA3V4II2B16yxeuPg6XdpCNtEYff/LMk3+RC+ghF5QNg7VbbHUehDvv2Pn7++u36hV2NxTGPXQRPE/Q==
*/