
#ifndef BOOST_MPL_DEQUE_HPP_INCLUDED
#define BOOST_MPL_DEQUE_HPP_INCLUDED

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
#   include <boost/mpl/limits/vector.hpp>
#   include <boost/mpl/aux_/na.hpp>
#   include <boost/mpl/aux_/config/preprocessor.hpp>

#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>
#   include <boost/preprocessor/stringize.hpp>

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_DEQUE_HEADER \
    BOOST_PP_CAT(vector, BOOST_MPL_LIMIT_VECTOR_SIZE).hpp \
    /**/
#else
#   define AUX778076_DEQUE_HEADER \
    BOOST_PP_CAT(vector, BOOST_MPL_LIMIT_VECTOR_SIZE)##.hpp \
    /**/
#endif

#   include BOOST_PP_STRINGIZE(boost/mpl/vector/AUX778076_DEQUE_HEADER)
#   undef AUX778076_DEQUE_HEADER
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER deque.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/vector.hpp>

#   define AUX778076_SEQUENCE_NAME deque
#   define AUX778076_SEQUENCE_BASE_NAME vector
#   define AUX778076_SEQUENCE_LIMIT BOOST_MPL_LIMIT_VECTOR_SIZE
#   include <boost/mpl/aux_/sequence_wrapper.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_DEQUE_HPP_INCLUDED

/* deque.hpp
NCNhlC3jp0PGL1s0zEx3Zi/CRtTaR1ylR9P4Zp9pWaO0YrsgYuKFA6Fn6czeiLLAeusgrUnPwfYjGVY2Qop3QjNqVMbbslWq2JkW86HZtYnuUKY29/6iE82JTWreabTMQ6q3Nuw05WptlpIelj0p1v7xGXHQq0ApW1BvYpFAwjcvAocsNyVc/TByKRXRM5KFqemnomt8NkV58FwkcsZgEmMF4W3Mc/fE1eX3VUQTu0rOF+VvY4nDmA3wDmiHCwbKebiUQoBkA8uF765bJk8/ygotTla9YnOrnHM8vLTTP7FWZdCFtMaITcKD5QpiWag/ek3k1332ShWgOs75mGD79aQm0Sc3tw77OMQrQT87vE91c+FlgojSm9ZZZ8Xa0pjHy8pCR4uien6ytQiwipNDgQNGHNQyxOXT/Lqrwzzc9LMvajFYJ3QTbOQd4/O64rc0+sUwd6EgGpNDo2DT31CSGf6OP9oPEvie8B7RM75ixrnfO6HQzpSW545KExeX7Z7nblDbw4/fXXw+33K0GrJ224JN3ftwM2I2T/zc67Tky5Oh2KfE99PniGEk8KmOC5lDNz7bR/vbKKs4T0qTrBbZmnxPes5DNtx4OtL42V5Pd4B549Td4rlgK7X8V7Vzv7vaH5qnTq3oTbYkZCi1ZmczR/f1tFH1OXa/aHkH28dn/RDuF1iOCO+zhyBhvsyhuW2F7DXvYE3H4blnkYcP
*/