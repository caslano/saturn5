/*
 [auto_generated]
 boost/numeric/odeint/external/compute/compute_algebra.hpp

 [begin_description]
 An algebra for Boost.Compute vectors.
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_COMPUTE_COMPUTE_ALGEBRA_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_COMPUTE_COMPUTE_ALGEBRA_HPP_DEFINED

#include <boost/preprocessor/repetition.hpp>
#include <boost/compute.hpp>

namespace boost {
namespace numeric {
namespace odeint {

struct compute_algebra
{

#define BOOST_ODEINT_COMPUTE_STATE_PARAM(z, n, unused)                         \
            StateType ## n &s ## n,

#define BOOST_ODEINT_COMPUTE_ALGEBRA(z, n, unused)                             \
    template< BOOST_PP_ENUM_PARAMS(n, class StateType), class Operation >      \
    static void for_each ## n(                                                 \
            BOOST_PP_REPEAT(n, BOOST_ODEINT_COMPUTE_STATE_PARAM, ~)            \
            Operation op                                                       \
            )                                                                  \
    {                                                                          \
        op( BOOST_PP_ENUM_PARAMS(n, s) );                                      \
    }

BOOST_PP_REPEAT_FROM_TO(3, 9, BOOST_ODEINT_COMPUTE_ALGEBRA, ~)

#undef BOOST_ODEINT_COMPUTE_ALGEBRA
#undef BOOST_ODEINT_COMPUTE_STATE_PARAM

    template < class S >
    static typename S::value_type norm_inf( const S &s ) {
        typedef typename S::value_type value_type;

        BOOST_COMPUTE_FUNCTION(value_type, max_abs, (value_type, value_type),
        {
            return max(_1, fabs(_2));
        });

        return boost::compute::accumulate(s.begin(), s.end(), value_type(), max_abs);
    }
};
} // odeint
} // numeric
} // boost

#endif

/* compute_algebra.hpp
oP2wpySzQQdAgudaNQCB3bLPRKfbpMzPHDtlpUfWkxYTdO2xpFhFr54Sj2WHx3JAYg0Sq4X+ASwPCJadnsxWCVXCEwCGhzU4thpdICzb3ZY2BERi23lnMF01yywm6JxudZHY53D3WGPmLgQpc7tjp8R2QNeZ9Yi0xPZQ/3qbbgt2LUGbrKaytge04migywT666iWMjc7KiUlJc3NdgDi0DPbwfZA12KAv2A7OK7Qe+YOGOHamBFuaNfXNhpmyXKE1UrsO8DPsRd+Zn4FEGbWOr7k3dRbvqRu6tluvRucEuoj83OAEF6uh462xXS0K64jj+UzMZ/4VriohCZUdex0OyKezF+QFJBUHE3YoYdtdVua+JBulVij3mfmHvito7YVe4TxjHYJJNCuz+2izzZ8jx3E2XP8B/rM3E9k4HYc4N3BZBzg3e2QoiOZuVuKjuRWCYcSOsOeqBuE1wLvfy5ZKnHC2HaJ/QGg6N0DdI6TmSeIBBJwFneK2W/jg1rLqYbVsobo3DUC3Ykecfx3Ep3oQ8rpxG2p53PGfnMcQwATpMzfcQq/5PN9BJu3HJFCp1Jtjz1EZVuDz7rDC0rDC8rDweXhyUvhkcsWer4L6O/AH0Hrf5ZItd7DToQO2DywWkM/2mRlsEIkwnxD1krKyFPwiI1T1uIMAPSbpcraXm5HZeWhbm7HZonVVdYlS2xn5dZzAJTKJosEf5SRbW42
*/