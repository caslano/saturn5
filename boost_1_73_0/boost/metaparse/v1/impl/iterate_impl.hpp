#ifndef BOOST_METAPARSE_V1_IMPL_ITERATE_IMPL_HPP
#define BOOST_METAPARSE_V1_IMPL_ITERATE_IMPL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/impl/iterate_impl_unchecked.hpp>
#include <boost/metaparse/v1/return_.hpp>
#include <boost/metaparse/v1/is_error.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <int N, class P, class Accum>
        struct iterate_impl
        {
          typedef iterate_impl type;
          
          template <class S, class Pos>
          struct apply :
            boost::mpl::eval_if<
              typename is_error<typename P::template apply<S, Pos> >::type,
              typename P::template apply<S, Pos>,
              iterate_impl_unchecked<N, P, Accum, S, Pos>
            >
          {};
        };
        
        template <class P, class Accum>
        struct iterate_impl<0, P, Accum> : return_<Accum> {};
      }
    }
  }
}

#endif


/* iterate_impl.hpp
Wyq/M25NRkco4w456AcnReahTW6b91fpac3c0pIHR+WcYpfuGYQSxC9KWuMOwSR9C62SPHiUbIiunEr+D2Xa9Elkebcbfvf5df0Q8ShbVPAz3hFJYEtxbULdFWE/M0dra5mpTKs+kx6oe1aM9uuGXHcQspM4YK52PpZoeIZCTVuWhwW/JJGynUh5R5LW+KzGOMZlZ92GRNmWNZ64eu8nKoi+swzz9We+XRhXfYlWBot1+ajr
*/