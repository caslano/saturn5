#ifndef BOOST_METAPARSE_V1_CPP11_NTH_OF_C_HPP
#define BOOST_METAPARSE_V1_CPP11_NTH_OF_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/impl/nth_of_c.hpp>

#include <boost/metaparse/v1/fail.hpp>
#include <boost/metaparse/v1/error/index_out_of_range.hpp>

#include <type_traits>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <int N, class... Ps>
      struct nth_of_c
      {
        typedef nth_of_c type;

        template <class S, class Pos>
        struct apply :
          std::conditional<
            (0 <= N && N < sizeof...(Ps)),
            impl::nth_of_c<N, S, Pos, Ps...>,
            typename fail<error::index_out_of_range<0, sizeof...(Ps) - 1, N>>
              ::template apply<S, Pos>
          >::type
        {};
      };

      template <int N>
      struct nth_of_c<N> : fail<error::index_out_of_range<0, -1, N>> {};
    }
  }
}

#endif


/* nth_of_c.hpp
PV+HB/YG1Ev3YreeGh5DQdyVviA+bPQWuffXhHGX4z2PcGb3xJOe/NkiRL8Am+NztD/jAROkhKgyJUQtxtPASNKgu/4IHde1V80xxee+ommrUB2RxP7KouNDpaAbVEhO/6WDoVLKykxlgZFaAxfY7UAVljbWkRwbK1Z25z8SrbufIBhYMRFQgIgc0l31MFwQhPI85+mRhqPu1oUO7+o0i90S64+GyEiD3d1afZJ3dS+4hEF2g4hF3eZZZdVddfzqWHiv0JedvXAov/mmiyT7TcSKXA/PxE6Cp86EpvCpagc3Fmv11Oohu/TmrZaR5vIPFBMlfwQ22MZ9nxITsuHU2p836Wp+ezSsyaeENVnkXVuOTDquH6uOeetcm0BjTfpZUmru/NEGXezDjyAjKHZ6P7HTQ7FUpKrrrGazn4Z6e5YeiwGbNXMvwNDT3mQNDaA6Jok52HukVPMsbTYI54gjPOkSXN1SXF1kUjy0ezHCA7fseVayqUW+l5WdCFrkrOCc0r5gAd92u01wW6/YrBbD11K1K2eiI85uch0IOJNQa3qmwNeX51sNx4C4j6ZqLz6TXA6USQ6y6kxzypGyTLgyPaEZh2y6dyX7VQ00+0UO4EQ9nw89e9qb0ZUqi5UJ2g3t+NnI3lTkSiXGFLk+E2X0N3MNR4joJY5g1OuEgzTUz1+7CR2GLVR3PGFQ9C4Siy3PxokFzg4zV9zyB8GX
*/