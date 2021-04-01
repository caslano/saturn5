#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_IS_NONE_C_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_IS_NONE_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/impl/is_none_c_impl.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <char... Cs>
        struct is_none_c
        {
          typedef is_none_c type;

          template <class C>
          struct apply : is_none_c_impl<C::type::value, Cs...> {};
        };
      }
    }
  }
}

#endif


/* is_none_c.hpp
b6PGr12LJzHJXsNgZsMBaKsss+WSzow8b6hKAoS5hohoTIFTbptbArU/baVfDJTaiLRCdD2RLUX/OEy0A/JTUliLguTH1LRbewx9Gx9GW1/xl2swXaJNGW3xqPzy8oRd9ILZ7UPpvoulWBY8SG1mm+YqfzDUsDyd7OrsEWFiBPh/6QKeAHP3MlBBRRQIgRs/kUy3Jl+/YUxfIOkyyLRkkO0f+jnodTcvTdQ3RqoqFscw+vAHLs9tef3thEvYXVHNHVLN1vjb43Vp8fOMSg9FcdkHkq0lBVQj570qwg7Dv5AylwkOMcbBS599Iy6j56zorF9WlQ8+OuHOkRfXZW6OzwdO07WFf/K5Vs0AQfl+2Sju3wGLjOwoKUcoYHSXvwsnHaOfONp4k9eENx7TVhlBTXtX3TaFt1hmsQoJnKHDpVlUCpzhD5Z/l7z9/wSYIHCLfBHCxLnNeb5o/W2p36wRaTZIW3AgdqxVg+eVQ2PrsPKPcEbHbWC7kMc6VW883YtFsyGEVrPbYEGMbrV1U7NZFyAPol3erbTEL9X9TvD+s/iyhclTVM6OeP1srA==
*/