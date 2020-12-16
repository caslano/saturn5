
#ifndef BOOST_MPL_VECTOR_VECTOR10_C_HPP_INCLUDED
#define BOOST_MPL_VECTOR_VECTOR10_C_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/vector/vector0_c.hpp>
#   include <boost/mpl/vector/vector10.hpp>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER vector10_c.hpp
#   include <boost/mpl/vector/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/aux_/config/typeof.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   include <boost/preprocessor/iterate.hpp>

namespace boost { namespace mpl {

#   define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(1, 10, <boost/mpl/vector/aux_/numbered_c.hpp>))
#   include BOOST_PP_ITERATE()

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

#endif // BOOST_MPL_VECTOR_VECTOR10_C_HPP_INCLUDED

/* vector10_c.hpp
llty5Gm/d76TlWe/l+l9u/c2VtuO8pcmbzXQvOiGHPX2Bv2otX7/cX30O3jGT4ebz7tCHDTR/DH5k+IR+mPwgYw/VXmAx6U/eAjGwz16lJnuS5SP8bF85RD9xC2uQ2v9rOcdx1LzxM3L6o59YzzyMcv8PZ0j9rtsUIhf6z6WHzWOEyuTd6cdxj3P73Y6i0cf1M7qn2eXeo4dR9GVoT3Kgndj/MYryj/wPLof1WOV6z+rr5z/wF/LL81XL8/lPe7/DPQ6/cfM206Rd52unb0mOK+MJ+73OCnym13UD7nGW9XL/dDLtJcrX/S0cvc7eaF+8jML3A/yGhmveLiql34Iv+9E/VzjouYNrVLeM+cpB+aVFlkfC85XMvuh/u2f7bj0X78y7nvQPL2B+tOlT/r3I8r5cec3Q33mOGpelgceAF7m3np56JO1J3vdr5PUr2u0F8Z/qpeZ391CXBF9j3e+POQS9XtMnDHR84reZf7wlazfp/KRH4kfyf+kXeZDfRfX8wz1xw7X/0z9783qwciv5hzQju2nRfdHkJfB+L1HI/ku7UCt+qmdflei6499oZ25QT3PJ8k37nM96Zd9l2/qwXgYh3i43zzt6Yv6VYvEQ7meD/3DqbuMH0X3Rz2uf3oe/bMOYf0h9AZlJ+PK+8SXo6nn3l/X90Pt8FLxEnEF2ocHpd115uc9H/FZ4uj6MA4w6QpxyefiBuSCedbKZx0N6pnPbcrlFv0z40M9lmknPzK+G/i5SexDsfvWSz+L+BFlD+PeF7RR3ngP+65fervn55zoHhXl9xP3U/2y5hn9pn369Uvle1Jtb5hxzP7mc0b3abyqXgZv0N/yCH+1CN8L+LMOyMel2vWZ7ufjQX4n/QxxHOKv0j3yrZH9e1098AElvwsmzo3yD/eZD7Fau3uqegE+hP7lDZPJh6HdOvevyHicdqpOfFk1wnN3lvI2xXOEfqWfVY6H+fD/6eK0N+Xn8TMoo98FQa5p5xZ5qG+8P8l873pwPPXub4pyvkr/Netx4+vgbPrZbz7QL8QpP+p3qGdqR8tP6wf3hwdifvnO+ynjdtrN/DTtH/cBU1+uv4795T35/Qp/h62LfmReXN6MuAzjX2T9e+q7nuK5fymH5+tf/Tqs736HdvMU8cv2sL4m4JNbIK+u5xbzXXPLeR++S7l7Tj16pfqjUf9YfZpNPfNLiH4HkXp+R01c87q4Gr6Isk9QTz9r3GfzOA9VGS9Yqp44bryD93hulzjZ87o8uh+5UL24gnru204J+V3y2ajfqf58QrzEujA/+DTa3049935o58lHZPycZ+aP/NAf+U20d5H++Mvys8muzwuuy0j1/2T9Rfe3XP6y8N/a754h713K99iUWb7nPU3pqTzPuRAXvRX3XhvXRTlfViy+Mh891tE81FTPT41xb+MJNXwPQ3+sG/XEqVg3cXRzVsijzFBf5j0Q1DNexsU8i41vXaA/u0e9bF7P4XHO4xHv/Rmnv9ggzlks/2V+VoVxx3r94N7Tja/H5GF7Gae/knuD4KXVw8F3RuxzySrxnc93X6beWmK8ZJC4/Lf6f0vFsT2Ud/VaeoXxv4B/e5px/dbzvFWc0kf8d41+pnlPhfqbzfs8X9rD2lr1aPCdWwby+1f5ju3On3sZmTc8KPNOVF+zX4zrDc9pBvXgQMc/JNV7LpxfhXhvrPgSvpn3crV7Zfo5Hc0b1r6suc17ca4SX+8yDwP+jHYSjGc+Ja88x3yiN9S/5uFkum8FJ8yDnWI8ZqW8FOeb8Q81vj9PfR/Fddd6rlr5/F7qufdD3HCT/kyqfuJc8YJ8dHVbeT38Gdp3n9K0U3Wej/Kh6sM+8qYHXA94UEo=
*/