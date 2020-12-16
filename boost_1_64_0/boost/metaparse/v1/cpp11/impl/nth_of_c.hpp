#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_NTH_OF_C_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_NTH_OF_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/impl/nth_of_c_skip_remaining.hpp>

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/get_result.hpp>

#include <type_traits>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <int N, class S, class Pos, class... Ps>
        struct nth_of_c;

        template <int N, class S, class Pos, class P, class... Ps>
        struct nth_of_c<N, S, Pos, P, Ps...>
        {
        private:
          template <class NextResult>
          struct apply_unchecked :
            nth_of_c<
              N - 1,
              typename get_remaining<NextResult>::type,
              typename get_position<NextResult>::type,
              Ps...
            >
          {};

        public:
          typedef
            typename std::conditional<
              is_error<typename P::template apply<S, Pos>>::type::value,
              typename P::template apply<S, Pos>,
              apply_unchecked<typename P::template apply<S, Pos>>
            >::type::type
            type;
        };

        template <class P, class S, class Pos, class... Ps>
        struct nth_of_c<0, S, Pos, P, Ps...>
        {
        private:
          template <class NextResult>
          struct apply_unchecked :
            nth_of_c_skip_remaining<
              typename get_result<NextResult>::type,
              typename get_remaining<NextResult>::type,
              typename get_position<NextResult>::type,
              Ps...
            >
          {};

        public:
          typedef
            typename std::conditional<
              is_error<typename P::template apply<S, Pos>>::type::value,
              typename P::template apply<S, Pos>,
              apply_unchecked<typename P::template apply<S, Pos>>
            >::type::type
            type;
        };
      }
    }
  }
}

#endif


/* nth_of_c.hpp
j/rCtTI+z//ru94vvMckd/TERbYs9vc2uWCFv594zX+W/+4gHjE6/viFjK9e/MFf8v7kRXl/6kLet/srOyb1HTy0/y8T/NUecRz8y0AyeioX8O2PGZg48tcrx58XeeF5Ud9fzCv/JZ9fzIefXXjmwJkL82j+b+Hiv8abuJ3OXWSnHy6cP/livvjbnuIFrGenpEHJFx5rdOHzs7/YqPmIlNFuM453pn59B/OPv/TG/sEI1YoX+o0/Xdxv/Df8/A/j49/I1fhcz/+qQTKeIxG58GyS4n/pb/yqOUKjv+5pxfz7L7XilIueRXHhuRL/kLf+g7iPnztLo4xz//+////3///+/9////s3/iu2LxLWlIuFLKui4dqPQuj2cyzsfjKEfQNjoeOeEF7aEgmZD9kTczQWypSO2KMRDRsviYZ8KdHwtd+//H0klOkX8x7lSLjr00i49wn7ODZ7B96P0ZC9fHxTjfo/ayRUHqqK2uspf6n2gT7nuXiNo6FBzkhY9GAk5PxAj/muSJh2znNzv/fOmlWxcPdVkdAwIYTWT1vD6+gd1xujYc7d0bD052i48o/R8Np9sXB4iJ7W7GiYmObhQPNiod4J9chO70pLxEV5omHUbRhkvHe7JoewtW80dKxCW4+IhXL1YqFOHs8Tm+5a46Nh/SP636WiYbdx7njd+2J3x8LTZyJh7OJo+P6MsVahf76OhrtaRcPKH/Cyvz3bPhZWnYyFB0t4NvcYd7E+FQlHfsL8P4awulks7N2lz/FBLKxlp0ZLYqF2pWiYtTMamlWleB+KhZLHvFz5enta50XC6k9jYdmaaOj8kd9PezZVYXa+LBZuS4yEH+fGwqirQnjss2iYPy4WRk+PhtPr1B53xsLkFZHwzAeuXyASTm2KhuMtIuH5qGforoiGdSU9d3czW7WPhvoHPI9+ezRsfiIWrqtNGz2gNvs+Fgo794IDnvO43ruhk6PhMv4c+X4Ia6+wh/RICB8v9d5qL9X/YX0sXO2+urHzouHVpdEw+in3NsSi4Sd2fcU51u2Lhjuec322XP14LMzP7NlsOfQfx0ZD62yR0ODzSGhmX8Bvn+Xfbu5r5qdxcT+/Lx7Ku5foXCQM6RYJm2uIs+LePdvdc9ad/+dlsfB6Vc+VfSYSrjviiZm/iYSfeoSwZ0k07NOZP1RW72gM/XQ0GnIMF59i8bJs0fD0o7HQrGAszN4lrt8I4eVD3ofu37sPx0KNJiF8sNse6Ut14t5RT0XZ5OpouNv5uxvTk+mRcNUfvJvYmPdtj4VpZUNIfSsSXk+LhDfejoaZQ8X3hGioN8Vd2oXF7n4++sR7uX7reVNs/vbgSDhDAU3PR/OIkevfi4XPJ0fCo+Lgucdioe3D/PKj5291iIQe4uBdMXXFV56ntSGELT0iIfGmSOg8hG/aeaZFEhs2FouF7bkdGQtvvBUNwyu616ON+0QeIf6qsA9f91keCxP3ewvenEjoKWc+yuQ5vZFouLmUHpnxtZkQCVv+EMIcmvLMpdHQZIR+xXzjXqNOfFHMnpC7zdm8TTS8MVHc+WzUrEjI0sme3nyxUOkha06PRMI6vlh9Nzsa81G2vy+3fLvXPTmPRkKnG8Wl/EyfHsL7g6z8TTIOtkp5wH13A+SVOTceTJ+18AaKguLynmgo/kk0fCEer20mr+RXjWV8JU4PHhSDD0fCnH7WsF4Iod9T7LrYms8k++eGec7f76OhfYVIaHd/LOx6PYSmd0RC3xvdbz41Fl5tGgldSsO030TDuScioYnzf2weO/lrbL1IuKFYNJwRQ93YvutEvb8WsXCn3Nohxl77OhaSckXC1hUhdIQxW/aJsS9jockWT33dEwk=
*/