#ifndef BOOST_METAPARSE_V1_FOLDL1_HPP
#define BOOST_METAPARSE_V1_FOLDL1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldl.hpp>

#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class ForwardOp>
      struct foldl1
      {
        typedef foldl1 type;
      
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<typename P::template apply<S, Pos> >,
            P,
            foldl<P, State, ForwardOp>
          >::type::template apply<S, Pos>
        {};
      };
    }
  }
}

#endif


/* foldl1.hpp
TKr7APhC/ElFZ9zyFBM5MN2iykvABg+fz6jltJAV/uwEw7PLFrf0mSKaLJOJcrqoBsOV7+kkTwt7yih3jLh8WKCBDZrKpcXlN7GlSP/UAvSjbSkHVjcJ0E+DAH1UrNL0Afp/Sm0qHRJTbXrHzXt2GL/j3oMt+o7yT5r/jj7/m++oHBzzO+pHsu8ILQIXJGTzx6S9z/6ip72gMxjowP5yTnvbMskqBOR1L6iv4yguf4T0CAweiodbt5a3hOh2HRyD6CL+tB2h9R5PocaD600mtd7ferI98Hp/q3VXVhuuvKq78qruSnhUvlzgw15uN4JvJzTczc7lyCv8JxT2R/KcB9JM/rZbnGmMnJk+Vt13en/h7zgrT6bw+2Wqb90qh9/+XclqrAA/Yha+dKv88JXwqeU6AVz47LW41vN/VokXUWGsbnc2ec6xUDzRoywwZLXRHOpqfQsqXn3MxONdqznBsRejj8xYtHrRKrXQSbPdtibV4ihwkkqdFNM4Mn+prC+qMR7raOBFoPXR0adRxTSo5C/k/3yMQhgSwcRB5BOaQ1p2DvePX3MVLyoS2Cz84+e6VHpYN5zXtnbR0eSKsnM07cPKZfK3IwLe/TGH6zjCGzqRGnyJdsWx+GMwNTQEdygZexmIF6wCRJ+0F/KpKlw1cSjpUncOm3jkRvguUZxEQTv2NZmM11TIB36notJV8N0VtKqiExjWt4G2x9Jm
*/