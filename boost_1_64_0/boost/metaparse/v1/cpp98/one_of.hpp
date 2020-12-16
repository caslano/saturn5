#ifndef BOOST_METAPARSE_V1_CPP98_ONE_OF_HPP
#define BOOST_METAPARSE_V1_CPP98_ONE_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/impl/one_of.hpp>
#include <boost/metaparse/limit_one_of_size.hpp>

#include <boost/mpl/vector.hpp>

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
          BOOST_METAPARSE_LIMIT_ONE_OF_SIZE,
          class P,
          boost::mpl::na
        )
      >
      struct one_of :
        impl::one_of<
          boost::mpl::vector<
            BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_ONE_OF_SIZE, P)
          >
        >
      {};
    }
  }
}

#endif


/* one_of.hpp
8CF6Eu5U/p1/LCU3sPLoAes0fw0bA+dam+86T13zxBqSwwDf70HrfptUHui2JPTlNR5w4LgwWsrMdw/e4KFe6N/adMXC3OKR1Fkd/3CjsvjfwQud+VG1mvumtajrUuY7IXRYH5zXvBldCqde0j77eZiNv+hPdbsCXowQy41P7UmNX6Q/z8KdOJHONm4G5BePOUfNERd/8HJ569IZ/PUnMLgfHTnktj6paQYG17c34Nf0xrlI+Fldrchdm1nev5s2c9/3ZjGPLqnbMNgDq/8ewFPe89zM1/hL7Frlp49r6p8bwbmy+eIiHFzY3twv9Rszrbb4+C5+Kq0eT/MaK8VuvZ6Qv7tmutnG6d9Frp/MvqLJaw0x7AmLivDtnc2DM4hvR1p8vL5LAWs+C0G66tjHOO3VHG89Z5vZA594cqN5SQiuKGuv6u5IXHwY/Fv07rM/Ne0cPFNMomZ4lYqDzIGtu2lCOiAcRi9To7nE5iecdYwezQen46j/hfDuNj3xiAanK7bsgWv6d7VZRnYc7e9L/+9vqQ8V95owvghtXDY5n/0FLTmbl0uE/+rap9nLLfEdfEHfi3H6q3oNdifWRzfHw66RAX8LAxepkwUbeQHzs3Acuqem153Di9XxRRMYX5xO0odXm5ut8FCf6du5M+CR2t0yltaF4eUOeB7BvvPg1KEnaEc12bgTr1gZbsDJdmprLM8Vrxf92E+N1NfX2WBzS9+Tz4dhMBwO/ybHyZ11tLHWBpdg7m9qafr/n68d8gTPNeTL6dKHq3jyjLi6CU/4BW1xR92+U1dev+yMmfI/dMQpdYGXM9Fdw51prs2k3n4OdS4J1/5whoGrjqrHMUnp6unqpJl135Sf43SMa5zr5qznd7yf3ZzCmWe2x+qxsVxfM3eLp5/h41rYFyUR3lj/v79v62ewxO24ulFLM+D1DHXcviRM3S5u9rVDr13gPTLwSEvPmtE/govBumgm5png1r96aqPn56aanUeHN9XMumnKJGv1U4hc0CA1xpu1vuV9PKO4YYoYJLYvvd+RxlyAi+Pzrb2POo+13wk8dvNd9LhYxeqoTjybmZZWKgvfL8LBqguspxWcqwKPs5p5qrWSi800fGyP62cPhV2b+Bb8/9Ui3Id3lsa3VzHLY02NW9rja/Mv6144OtTcC97pk2/hcA0z5BcXnZPJ6Qv3/LcjHar+do2jn+mb29/B/y10eUHxq2rWmcXM42dzlPeeN6TP9urtb+FWYTPAWkfVkrnBeT5iVF2cXA+f9Q84kzGvcUb2I62U7gd82dI8szbc2w1H6ccRfcROT7zB7byZ3yPvfGylPf7m85u01a9iuAzm7/MxDk8sjy13eO82dTDQ7Nc6k5+i8/XjLPixeq7nPdfBgI/wT/y202yWGojh/5cHZzqNcACNcgJHlaDRI+BDFedxCT9zHlGWz76Fp8Q0TjTzL9f/Xb88b62+esE9+60ay55S6I+M1qhHX+PDBLTDppbm/y304S0+xIypq3pOjiNCvPcyPMmoRp+l1h/uU7MH3zqI13PNrB3EeIJz6uS4Ff63Pcyv68OGo3EiTdToJ7gz2vcSyMm/9NpMnn4NvRzBv/fFY4N5mkbwx72PqadfzAGf6N90qdVbWZ5wE6xqjQfLh/g5PRy62XqnOANZyjPQ1bey0oTideSC+9EfzabBpnlhPEUYLvdMSGn4uVNco8GG/WbneC1TVxikd45Ud+9cnhOCETmjuo96q/lAb/7D82ylBeniJUF+mwHbugc8uwu/C4mZvRTLbB7RJ2CeClsW0X4reYni9DS8H/Oadh1Ls1eW36kBP0ertzoFzOO8Lw3NjAMD8D3XNNj5wkyuJly8in8=
*/