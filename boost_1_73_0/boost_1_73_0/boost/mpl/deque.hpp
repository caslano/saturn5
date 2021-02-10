
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
OKq+oeJmrwJiZzmHLJLyYPD/uE/ghLjXU+Yduf0ZAN2FEprMm5u4gnyVRkUSnwL2jxgsaGblVy30uol9fwx62m8s3MdlzjTcgctBc9lUSRXBZvcfce2J2SfP48kVMeEB1iUtuGI6atSxdroaZIciQUFM/Z6m0Uy0t7UgTYlx4SSsF7UjWt3DDv5aIn2Pq8235ePnr99azoodTO9Mf1KzhOzyxtcbuyh5lf/BeMDIyn1euT/QotPZ2wA6zTmdn6wsVKlxUZlddbPpcozEzIMTnz3SHWSB79qkz+hvsh4AAhP5JsY8Tl8gM+ja8xN+iT3bu/RT19/HlYximCEJ987V1Fu5ACx8z6UGfGft1uA8G53vopn0fObfKcM+t8LK1Mxo7NYzJO1ps0brrcW/tOfjfWTUAxQ6jS4gN4lyDg77WgvEMvNcw7fKb/BY3FD98CJEiV4Axc2QjmUOWj/muPV5HtzFKOhOEyULzAfZWUfmDdnUW0w5TyqZEYFVgsel1MTeRwEo9YNSs0F3QMN+VdWO+Y+pZmre3dw/3KL+5zQUQqOL0+22d7bezmnC4hOwna0UJI114mQqW9mdx/ORn3G8hkFdNS+3uu0Q4i3A83HYRXvD9gSp+PvL/fLN/I1XyEb4MsqRXpfzZ9FezU6H
*/