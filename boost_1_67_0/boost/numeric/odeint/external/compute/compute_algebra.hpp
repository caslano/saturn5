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