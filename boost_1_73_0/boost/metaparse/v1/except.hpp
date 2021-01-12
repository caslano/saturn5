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
1uIWNuDhlazXPIYn8lg2YV02ZX22YFOezJN4CrvyVPZhG17M0ziYHfg8O/JlduFOduOP7Mmala3HrMc0tmc6z+QlTGcGL+ZQ/plZvIaXcy2v4Mf8M5se4XiEJ/E6ns3reT7HM503cAgncDhv5j28hT/yL9zXMfsUduftvIB38mHexcWczjJVHMfwEM7ksbyX9XkfW3AW23E2O3I+/8oFvI8L+TYX8T0+xhJVrcc8kM+yCp9j
*/