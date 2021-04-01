#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_NTH_OF_C_IMPL_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_NTH_OF_C_IMPL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/impl/skip_seq.hpp>

#include <boost/mpl/front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/fold.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <int N, class Seq>
        struct nth_of_c_impl
        {
        private:
          template <class NextResult>
          struct apply_unchecked :
            nth_of_c_impl<
              N - 1,
              typename boost::mpl::pop_front<Seq>::type
            >::template apply<
              typename get_remaining<NextResult>::type,
              typename get_position<NextResult>::type
            >
          {};
        public:
          typedef nth_of_c_impl type;
          
          template <class S, class Pos>
          struct apply :
            boost::mpl::eval_if<
              typename is_error<
                typename boost::mpl::front<Seq>::type::template apply<S, Pos>
              >::type,
              typename boost::mpl::front<Seq>::type::template apply<S, Pos>,
              apply_unchecked<
                typename boost::mpl::front<Seq>::type::template apply<S, Pos>
              >
            >
          {};
        };
        
        template <class Seq>
        struct nth_of_c_impl<0, Seq>
        {
          typedef nth_of_c_impl type;
          
          template <class S, class Pos>
          struct apply :
            boost::mpl::fold<
              typename boost::mpl::pop_front<Seq>::type,
              typename boost::mpl::front<Seq>::type::template apply<
                S,
                Pos
              >::type,
              skip_seq
            >
          {};
        };
      }
    }
  }
}

#endif


/* nth_of_c_impl.hpp
/mbZcbSMgc/2bPcrC8ZXOSzxvGm8LQ1CpYuX0ZEcidfs21G593Yw/QfL+t30p/WJFeejxp5Dnl1NzUen0VuNO12tQU7yoJUmyIWnl2ZXDSjftKXZG/hBMZ2gJOFriGKJH3Akq9r15Yx9MDiAMwfugBjU+yfwe1Bwqknd3r2fWYVBpjyYhGfnQHFiGvwRfOKbvmYJxWDCP5GMQxPZeDru7Kw4Vr4uQnVlRo5H3ixTEFQeBSY7G2F4BjY62DZxOH3UHEQcUCE5b4GOLSaI0N2d7RsSOCCGeuxaZ47yFa3nTpEMvs+TQphGpMzPs2k7wjBtMaFNMzbtrNUNDpCdtzwmBXYMVlBB20o/7ysY20kkAlpzPZGUZJH0GKQzxeaDnTCLGV5M3iFUwiVOO1CfxyKYH5YMBWLHS1J6sun91m34r66KWBiSzKlV+Xzrjq767v8cprrbwAxGhbIYV97JocekqchArcw7KKOsCmhzlNvpZWG7LUkrrHNCsw5NLlbZ4Ay3pVPZnhOeJCNqBDUHtm7Kza1yxZX2BP50+A28PC3R5SA0GtNQGN6HN7IwwQ==
*/