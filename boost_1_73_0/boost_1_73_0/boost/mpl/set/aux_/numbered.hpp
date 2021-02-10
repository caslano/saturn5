
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
X+spaqOdlrqMYBoncXC0Iu//WEjgF5Wu0IsK4PFpnnYvdsBztidlh//2H1BLAwQKAAAACAAtZ0pSfjmwxJwBAACYAgAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDg2NlVUBQABtkgkYE1Sy27bMBC8E9A/LBLkFBhM68YtBEaIYdSJUSNSbNltjzS1itSIpEFSDpSvL/Xw46IVd3ZnZ7hkDq0T3GJEWKly7cM7Nh/aZDYiSZyMyXq6XnYfmG7SZ1jGT4sXsprPvnwff2vj/Z2PjJ67GO2JyDW5hjWaA5qRLTMkzOC+anyB7ZJCZhG55PyZLP/2Q25h++elEvK+2P3eTAYka1NvDw8e3TzNP8U4Owj5ekTF1+0/Ibd3cBv/gqV+KxXYWgi0Nq8rr+liJsu44xGZGy1DkPhotcSPAg0GJNUh5PwdH5UeMgHZ6axp42gUEIBG18aCLZXwcOUBRns6Rgd7ne9ZVaJyg2/RHU7GI7LX+/FJU0SAKS6xv2+oOu28doXvKQV3pVa+gvYlwISWkqusJwkpvXmO1+kiCW/a7iRepfTHZAKjGmpPH1oUBp2fdWrzv4OcTugWTZk30HoAnjs04AdD+yqg4BZ2iAqubKHdFWGHrtZT7I12WugqIrNpMg0u
*/