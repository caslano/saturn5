#ifndef BOOST_METAPARSE_V1_FOLDR_REJECT_INCOMPLETE1_HPP
#define BOOST_METAPARSE_V1_FOLDR_REJECT_INCOMPLETE1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldr_reject_incomplete.hpp>

#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class BackwardOp>
      struct foldr_reject_incomplete1
      {
        typedef foldr_reject_incomplete1 type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<typename P::template apply<S, Pos> >,
            P,
            foldr_reject_incomplete<P, State, BackwardOp>
          >::type::template apply<S, Pos>
        {};
      };
    }
  }
}

#endif


/* foldr_reject_incomplete1.hpp
NdTkWxwuNwNyU519baazGeUjELu3N7G2EYzwmHDFz2zfgxLWFIY6pzlUOi4XuCqCUqWyKejXTpHLN9uRoiFYH6pvqAuK8UpMw48zAu4pRQP9CmOO0ytM+AzH9WOZTNZIh8KJaChjpGNhfDNSTfizvXuorTV46Kyc6q3QVK08Yr+ll85kLOrVsaMMO6AGLvBXBwNiyJjVVD9N6wyH4jG7AyN7dx97JAjg301QVFWwps6lefTi8+G5rjX4xRaUmlU=
*/