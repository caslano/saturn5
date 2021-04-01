/*
 [auto_generated]
 boost/numeric/odeint/config.hpp

 [begin_description]
 Sets configurations for odeint and used libraries. Should be included before any other odeint library
 [end_description]

 Copyright 2011-2012 Mario Mulansky
 Copyright 2011-2012 Karsten Ahnert

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_CONFIG_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_CONFIG_HPP_INCLUDED


//increase macro variable to allow rk78 scheme
#ifndef FUSION_MAX_VECTOR_SIZE
#define FUSION_MAX_VECTOR_SIZE 15
#endif


/*
 * the following definitions are only required if fusion vectors are used as state types
 * in the rk78 scheme
 * they should be defined by the user if required, see e.g. libs/numeric/examples/harmonic_oscillator_units.cpp
 */
#ifndef BOOST_FUSION_INVOKE_MAX_ARITY
#define BOOST_FUSION_INVOKE_MAX_ARITY 15
#endif

#ifndef BOOST_RESULT_OF_NUM_ARGS
#define BOOST_RESULT_OF_NUM_ARGS 15
#endif





#include <boost/config.hpp>

#if __cplusplus >= 201103L
#define BOOST_NUMERIC_ODEINT_CXX11 1
#endif




#endif // BOOST_NUMERIC_ODEINT_CONFIG_HPP_INCLUDED

/* config.hpp
nxSNsyK/Q95hGS2UshMBfIib3LTiFYvVTcSqe0RTFQWN2dxgH0kdjVP0Br1Z4btv2y8vdERWx2gVy5pzbOb2V3zd34XGnw9FgYUxV0vTd44ieWJNIPAqWTw0YmRqjdSWKO6OTBwQismg7x5+1XlKBcZAAyshyuFNw/ejLiNaJEdtla0h8X2ZjdeGATy9omiXxLTONjI7I0wSzqyjCJhtN7rnp+iuYVKJFF9DMHrZhecr+uJsiAWPeI96j7++RkzFwdEYPjeyyjuSktX8jzynwkeKxFgBd26TPnStaPHDBJXQtzxpYeqzoA0OIVaIIhAeyFRsuTF52neLa9v5jfPDenskQ4rGWf9/EOAsvGyycvYZjJnNYGSsQsrI4JfS6+eMPtY1Qein1DaUxsb/xFQmj2rdFW12WKzvLq+Ih4gcIO625+Uz4qauouldCo1tL6h9Y4YQxpm5PJ66fZhFBeKKtYEdnYusuMzDBREnS5g9eRCgvgobwv4tRq84DF7HwwmWx20ZlywdNx+yWfawe+bRynOD7rUoID7mSyi57VLQI3YLB+uM+qiYY+qMRA==
*/