#ifndef BOOST_METAPARSE_V1_EXCEPT_HPP
#define BOOST_METAPARSE_V1_EXCEPT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/reject.hpp>

#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Result, class ErrorMsg>
      struct except
      {
        typedef except type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<typename P::template apply<S, Pos> >,
            accept<Result, S, Pos>,
            reject<ErrorMsg, Pos>
          >
        {};
      };
    }
  }
}

#endif


/* except.hpp
+xucHcDOQmwjCsXTQVD2gxd+FuYoZjknC7sdxV9hTSA5hb2XwqkKiJXJn02IDqdSc6TcYdsXIe6O9+RzTermfFUMHEXB0HK32wExNJ886rXX6iTji1prOYu8MhFPqSj+mr09fH/CxhM4HcY6btoH86nFKNm1EFP7YQJKXzvkNJhpiOHEyAl49Rl2dWN1PH/ub7rn5qFkuENuvFY8kQeaQgrKap4UJqslS58rjvgv6RG29F4Ji5JZsbZRazYvHG3MBF60uLU4P52d30iqT2LWBJtJcXxcB+JemTNYpTip6pxjZS2KMs5BFS579lEokbg5CTV0aYybbXy3xMhRr4/dm49Z3YNq7UEJN80tqTls0HZ7NF1L1Or9CF+nziVOzKUOYCddyyCa+Nv1nJf/HUlFB4wOphAIsIvjxyMXh2whqaOTGqpzUt2K7cuv2FBKef31DKW4PXkM48e72Wlg2JWKYw378FIe5ctTO7PGx0hcRoOxnDsVIpru2HZCka+aSrzxnCkiyCtpis4GostsNcVr+pPTvu4YL9nKE7iu/zd87SgBhb4CCntgjo1ss093Bnco07IpqWhsPsWcJ9tMIsYbg4EprSk0DlIht0DVUUixv33aAPaQH6pPyVhnD9ZxFOQLfK2PEG9L2jEif0ZZ5OyNFg6NTJJe5nxt4TkXKFpfkGuoVJsn0i6m3qLPOcEm4OjT4Z9MXzt9LxMB+CzS
*/