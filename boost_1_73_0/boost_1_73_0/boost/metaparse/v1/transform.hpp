#ifndef BOOST_METAPARSE_V1_TRANSFORM_HPP
#define BOOST_METAPARSE_V1_TRANSFORM_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/unless_error.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class T>
      struct transform
      {
      private:
        template <class S, class Pos>
        struct no_error :
          accept<
            typename T::template apply<
              typename get_result<typename P::template apply<S, Pos> >::type
            >::type,
            get_remaining<typename P::template apply<S, Pos> >,
            get_position<typename P::template apply<S, Pos> >
          >
        {};
      public:
        typedef transform type;
        
        template <class S, class Pos>
        struct apply :
          unless_error<typename P::template apply<S, Pos>, no_error<S, Pos> >
        {};
      };
    }
  }
}

#endif


/* transform.hpp
HrhuF6uHNcgjqXOQaur5Ju6/eD9RN9cgj6Q6Gl6G2U9u/42o3TXII6lOhl/rk/K+rLX5qQZ5JNXZ8NJY8ke9IUS1r0keSXVBKsnzfZ8x1hA1sSZ5JNUVKX8cuTxj9QVELa1JHkl1M7xuHDqzmLXYL9Qkj6RSkUr2fF3GzmhG1I81ySOp7oY/5QVm3JdEpcSQR1I9BPVT/+LFRI2PIY+keiLl9+ahlbey2rsshjyS6oWU33+1/L7GMKIeiyGPpHo=
*/