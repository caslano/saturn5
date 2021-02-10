#ifndef BOOST_METAPARSE_V1_CPP98_REPEATED_ONE_OF1_HPP
#define BOOST_METAPARSE_V1_CPP98_REPEATED_ONE_OF1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/limit_one_of_size.hpp>
#include <boost/metaparse/v1/cpp98/impl/one_of.hpp>
#include <boost/metaparse/v1/repeated1.hpp>

#include <boost/mpl/vector.hpp>

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
          BOOST_METAPARSE_LIMIT_ONE_OF_SIZE,
          class P,
          boost::mpl::na
        )
      >
      struct repeated_one_of1 :
        repeated1<
          impl::one_of<
            boost::mpl::vector<
              BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_ONE_OF_SIZE, P)
            >
          >
        >
      {};
    }
  }
}

#endif


/* repeated_one_of1.hpp
lM3zfNkt8DzLmSn39gMLyL22YYOez6xxRWW3TInrGSV6G3bDbmCN/kDCUBXIlMemPpGg0FH33mL8ZQxfswwWP9h3HVFCvsc7yB7g1R3oxziD8b28f5Akef6Vs0djsIl8pe0Wg4T3E8GzJ2cj2sh/ot3GUsK39otFEytnJZjaBWSMb5zjxNZnKzGwdJBPddWe7yFNtyFJ6NCnrIyxoQPnLSird9jjw3KxzuEvegd1F34HQ484tq3BguSi14MybrfTtpgyXkCaAucl6gI9pJ/6Kc82KbTpUojRnJJelnLUxi4Xq1yMJ5MJYV1M6XUg72p6Q19tTtCWC3oTKSaWCO2sodQB3hEtpKF0MWXq0GnJovEuOuPqKesK6zLgPKeEzV2IEj6hJOw3NYc/bimdyPe+FqO32Wr9snhNholJuBW3Cft/ocllivmpoWugm6aujG5HKP7w4/FI8/M7Tt5DYxOWsKxdlLhSK3EpRVyv9T9QSwMECgAAAAgALWdKUvZ6DBhGAgAAdgQAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMzM0VVQFAAG2SCRgzVRtb9owEP5uKf/hlIovE8wE2KRGIVJVqrZaVxCk3cfJTQ5iNdhR7NDx73d2SEHaH9iXxPfie557
*/