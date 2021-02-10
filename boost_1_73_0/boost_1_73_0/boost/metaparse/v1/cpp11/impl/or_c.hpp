#ifndef BOOST_METAPARSE_V1_CPP11_OR_C_HPP
#define BOOST_METAPARSE_V1_CPP11_OR_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/bool.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <bool... Bs>
        struct or_c;

        template <>
        struct or_c<> : boost::mpl::false_ {};

        template <bool... Bs>
        struct or_c<true, Bs...> : boost::mpl::true_ {};

        template <bool... Bs>
        struct or_c<false, Bs...> : or_c<Bs...> {};
      }
    }
  }
}

#endif


/* or_c.hpp
L43eXxlsNFvcGcx7nI3gwqgd3WA/b2887aKHhI7VsFiHv4ZfUEsDBAoAAAAIAC1nSlJAdkL/ygEAAPkCAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTMxN1VUBQABtkgkYG1SXU/jMBB8t5T/sCriBWGctD24WlEkxPWAO6BVm+PdJJsmIrGj2C3k398m6QcPSJHjtWdnx7MbOrQuURYjFhY6M/R7x/bDNKmN2EMcL/sF7ucx47xBa8odslCcMKEY0tgZO4M1NjtsuC1SAjVYly0BUuXUwCWCqwDGvg+Lv+yXcigh3uIl+DN4MTu6CHwIpnI6kwS5f47ZQCeh08htH4hMvSN7UnTwbNIiKzDdswQT+LPVHT2xjGXgH1jmsdpIGI0Df/yDp8kNn8ym1+Pp7OeI3SYJ1o6vlN6glfDWUiV2Z7RD7fgT6o3LJVx3JxoTVxgtISmNxSMmbmvs9H06kbuqZL+3Wrc8R0WqWrT0McYzYzj5NPgQir0vvWF3ZdHRDIYlfUCQ4akRy52rKeEQhlpVODgJH4XL4WtHhrswMVWldBqdugX4qaq6xCu6kudd8nKximm3WMePS+hqSCG+BYlgEtwQ95GUtnuNvfpXbIqshe5hoDKHDbgc+25Briy8IWoY
*/