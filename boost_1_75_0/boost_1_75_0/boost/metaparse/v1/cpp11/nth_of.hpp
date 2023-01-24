#ifndef BOOST_METAPARSE_V1_CPP11_NTH_OF_HPP
#define BOOST_METAPARSE_V1_CPP11_NTH_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/nth_of_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class K, class... Ps>
      struct nth_of : nth_of_c<K::type::value, Ps...> {};
    }
  }
}

#endif


/* nth_of.hpp
PkgVjwExVma20nAuBwih8p4x545jFovp/8Ne04g0nssvTYbTrJeT8uQou30IHcX+1DoCFDbdqq37tTugKu+OA6pV+7E/AeqWeQioy+8mQF03TwCqVXu/f3yG/xugWk1ArXrdZjEmnOtdg8DyUcIQlbnLLAYSrI94UHfVLiRvHuh4Uj+cI6fCKf81DohrZjYm2DDi9BANLBf/K4EeitzlFIa2j9kTruJLtG0v0LaD8E+DxdLyd/nUyUBwMk6+MMWidYxje2HV4HjOoIOw0UrHsUOlQcUE8a/Tq0AMh8awUSQSsRHMMBZErBaDfPRNIB/wQoWxbbBaTRn9+MgIOqm6poiTgRhxDlhlqGpUIDrSwI8rf2H8EAV1PKStZqryaPxcKbSzuwN6vyI1qe7Ln+G+Yt+xz+3lIoyByUv6PxNQitJdY6KNMUTXTxW0HQCmu6bXW0nRsd0A6A4BFlaHT7jbSLlT3C2H0kkXmG6pg41kRiclJDOiYIRWahAvdku5k5KvI3NMwSRAqP0iwxIeFnuNw6JqHiZgCroPhexoPTG98GG+I46fmqkHyU/KyyQCQwkTP+uymMaCLMNYINIZD+9jwv5tG8P+21QD1oYN8MUX4zbA7j7pR2rY/sM+6dvJQsRpI+CJrPxN2pRjXFiSfMId+MrWe6xxfV1zzfFycCQr7kwD4YAui2lj8MxqTNLDZQaid2WZOTM6Xkg0XKGB
*/