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
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
*/