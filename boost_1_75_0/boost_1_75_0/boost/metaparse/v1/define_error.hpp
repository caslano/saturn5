#ifndef BOOST_METAPARSE_V1_DEFINE_ERROR_HPP
#define BOOST_METAPARSE_V1_DEFINE_ERROR_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>

#ifdef BOOST_METAPARSE_V1_DEFINE_ERROR
#  error BOOST_METAPARSE_V1_DEFINE_ERROR already defined
#endif
#define BOOST_METAPARSE_V1_DEFINE_ERROR(name, msg) \
  struct name \
  { \
    typedef name type; \
    static std::string get_value() \
    { \
      return msg; \
    } \
  }

#endif


/* define_error.hpp
N7WO6t/+20lLC1o9jLw/un/7nXOFLyhXGCeZEPgNEwGIhttSxfRcTM855IPU39+xiXrugeDUGu7jr+E+fgjuay3qEFD82RXkdYB4t/Z05SgXtaEiynpQDPXxZzy+Xgvw80GJztx9gLVL9oNEEB2/aZDu3aFusazrUKgyNGmfgexBuJ+d+6vVkDRqd2iniR5EEa/wbo9Qy30Ho+K/T1liuQpEqN/xPyzGUD8mY/4A59B1EI/1DwMoqcw3qVZBFFdOcG5yhB8j/PhdMa95FnutCi/6n65VM6H6Mdeq/vv/Y2s1/Y/TrpXvRNO1GnDCsFZt/DHXakyQ1mYkPw7lx/7B067VttT/6VrFRa2V7TRrNfi7/2NrVfb7adfq+eNN1yp83LBWk++NuVYvzqW1eZofn+BHae5p1yqlx3+2Vn2bXSsIojl9gLOe/n3zf2ydko+fnv4djUH/jhrpX0Fs+vcQp3/8GOHH7x46Pf274H+6p5qJlY5N//b9H1ur6UdPT/8aY9C/RiP9uzs2/ZvN6R8/DuXH/rM1ezH2NRCKwc5ummLgBK3HoBtc8puF6wbDm+gGBft0usED8SjnR9qSfsAAEUNFCJ4yB0S/lnbUr4UJdnsLu6q6Q7+7dN2vSLqDWmS5hWz2ulrZ13LtGnwLHbQPcHvJ3ZaO3oVaT3hsLXzEtVj0xqhXM1060GY9RmIMY9j0IRb18HNNegPYCGQT
*/