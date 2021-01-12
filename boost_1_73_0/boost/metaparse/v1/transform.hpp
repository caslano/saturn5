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
0cznBbyCl3MWr+JVvJGz+Smv5UbO5Te8jrtJzzzW5o0cwZuYxZs5hrfwPN7KaVzIObyDN/NOPsG7uJKL+Abv5ireE7VbvUN4Phael6XwIKH9Dx/rV169ZF7Gg5jPQ/g7pnIWp/BK3s6ruYizuYRz+DKv5wbOC+333MDWvJFtOZ9deRNj68kLeQt/xwWcxVv5Lu/g17yTFXa0njyK97An7+MJvJ95fISX8VHeyMf5Rz7BFVzM
*/