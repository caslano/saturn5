#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_SKIP_SEQ_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_SKIP_SEQ_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/get_result.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        struct skip_seq
        {
        private:
          template <class ParsingResult, class NewResultValue>
          struct change_result :
            accept<
              NewResultValue,
              typename get_remaining<ParsingResult>::type,
              typename get_position<ParsingResult>::type
            >
          {};
        
          template <class Result, class P>
          struct apply_unchecked :
            boost::mpl::eval_if<
              typename is_error<
                typename P::template apply<
                  typename get_remaining<Result>::type,
                  typename get_position<Result>::type
                >
              >::type,
              typename P::template apply<
                typename get_remaining<Result>::type,
                typename get_position<Result>::type
              >,
              change_result<
                typename P::template apply<
                  typename get_remaining<Result>::type,
                  typename get_position<Result>::type
                >,
                typename get_result<Result>::type
              >
            >
          {};
          
        public:
          template <class Result, class P>
          struct apply :
            boost::mpl::eval_if<
              is_error<Result>,
              Result,
              apply_unchecked<Result, P>
            >
          {};
        };
      }
    }
  }
}

#endif


/* skip_seq.hpp
+KW8n2yir0D7ohcNRa6TdVIeGDQQiHXnIwF7zt9tToDrU8+bUSXP28kLtXlzyTqKw0CdCSOYctH5XuBJPLfPtacg92z+WA/ux3Y+wYfjkN9o7z6Eb5HkXckz47p17MbY/722Uddbd55t8Wyvvq8HH+3zZkQg6D/ZgYcx9pf68LqZ9mgo9XjB4Ajm43xnvOaK9yxNzvqJqYkMHAmJff7JeP0bbUyvMCdnsXDNkJXDevQd67xxIAzpw3pZQzp00yf236s9ej5m3O4LQproATDFOrspWWcH99plxrAvOzD3Tv5bMQwvt5/X24Uv5bqcNfrY2djnurrM083dPf1dSCs00Lvfe9fqOyGN4M7ve/H+X4nMJxNi4ezpP4jhiBu3OM3lf+H5oeWqWLMwre+K6eWVvK7rFmp21Efn6W/pW7uSddkvgn3Y2lDJnSrgAujYG+85w4EF8v0121+7+vBmNOx4VOe5+9sYjqU3CfvTrkNjajB/fwhouON8i0+DrRqsvdBel29b/UXufzYkkPUbw+iQxHzfnugn7KZjxagmbYsp50euHtoJ2xf6fobqevi5WltbTjHj2uQdup2udfNvdqpWHA7nzTnqvnIR2sJ8KENUMBbwAbudDgn84T7cs8keGcDrFYwF70s+nMy+xu0b2fO4PBpw+Y4nTpVJ3ceFMNxlTMOb973ZpQGc45NnxbY8cEA3mkfx/Dpqy6ZMYbMxcnJ8dJ/0btWuefp6WtfoaE/XgJF+U3Easj3dv7UnmHcvQFtvvUNrZAPfSGUvRtkPUXaKKHspyhae0NpyxQlc9nrCu5vAe5NS9nZJbwZzG75SpS/9Cxvln0IwVaQjcKLmmD6zvkaznd3dODBBrr698QEfTg8kzhVvfFC16JLA3/PHymbLFzG+hA82aFthXfVhO4cpaIzrfNCd26DZwv4A9HKsbGZfdkd/T+fBrt3Zrn0Hsjv7xH31DetjHK53o9+vWhHzvngUdmDDdsFvi2wX/6817LQLHGe9fAJlJsakPloalmedoTnx20/ZKDqgEQ91r+/1JvpucVien0JZDvdWYi0l7X0GMNyTObDkTYT1HFO1d7c54ozmpH78sgsvVHLuu6jfdOHY8YBzrBy9ny3n3Fe9sfHt85s8OLWUtPN1D+61FK29n6wH3p1bW+4E//XHaT3+ksqWirJbqWxTC8rSrtFoP9fi0euefuM1CnatW8osVoZhncm8+Pb1mhh2u+1vXNWxU/7uwmj58pidcE+j9y1s56G+rn4vP8WdfLi3Z50IuKBPV2Vc/y6A85gTWIz13d36NJQ8Z0514d5QMt5pHt5IA7zZDj8umjwnzfX7zfshf6/othm8S92m9S363+79nXv3JrpkmcMToeVq9A6H3j+MUvRRGX+77/eNUaRdvwA4gqFsTvgVV7ptsEoUfKwJ5BK+J73Ox2E7Sm3HOHqlvr8CFwmCifEKWGjmbUG4ehrk+Hm6uidmwMeFk/h2oYzt6EJufwuXwzFacPaiswAzJQZicRDb3RRv9YnwPPQcVQ+cLcYRtcoI2Wqy/0ZpaP2/jNtp8p3Gis2cqb0tMRNapWpd4+tFgd3Vi75/BLbUMbPfUNlelJ14cmtLpy1rUt6FUijvlwXtPRS0zwLtJ5h4+CbPpOO4ia4PTk3U8fxleLZ4ZdDGKNoYRxsLTBtUdiGVFVO3e6yWq6LhoG+XL9TutKtox1bPohJCoU11pDaRd8tl4NDeYnAMRlNnOcsPUuuqcnh9IIdjJOvLTGwolT2cyl5jylLJoZLX232z1y75TdAOamTLExcn++bjqWysUjkyCT+i1JNPtTD6AGWqUpN5cQlWqCDrtdgPniXrkIkn97qns5w=
*/