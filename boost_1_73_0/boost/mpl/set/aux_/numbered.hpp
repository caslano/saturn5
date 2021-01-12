
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

#if defined(BOOST_PP_IS_ITERATING)

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

#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/cat.hpp>

#define i_ BOOST_PP_FRAME_ITERATION(1)

#   define AUX778076_SET_TAIL(set, i_, T) \
    typename BOOST_PP_CAT(set,i_)< \
          BOOST_PP_ENUM_PARAMS(i_, T) \
        >::item_                           \
    /**/

#if i_ > 0
template<
      BOOST_PP_ENUM_PARAMS(i_, typename T)
    >
struct BOOST_PP_CAT(set,i_)
    : s_item<
          BOOST_PP_CAT(T,BOOST_PP_DEC(i_))
        , AUX778076_SET_TAIL(set,BOOST_PP_DEC(i_),T)
        >
{
    typedef BOOST_PP_CAT(set,i_) type;
};
#endif

#   undef AUX778076_SET_TAIL

#undef i_

#endif // BOOST_PP_IS_ITERATING

/* numbered.hpp
1yyXV8650Bg2PEPt8f31gnwMa6x6+luYT0+G7HvPi0MyzexRAt75Id5wz2L74SU5edXD2M8sQ3yaWfV1eERuOtkE8apoJg8NNLDDgpz07L7ushCP/0TP0umRIZ7wTLMnz8IQn+4W/LIK8mbmI6/1298iK48IgM+X44pQ/uHI5PEV+3yV62lBlVVZASqo17nIo3bWHKM4bk7UUBQQrRi12MtTw1DajJlQUIyST+WFxvSamPLy
*/