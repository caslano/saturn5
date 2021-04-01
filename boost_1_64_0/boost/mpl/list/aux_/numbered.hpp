
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

// Copyright Peter Dimov 2000-2002
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

#if defined(BOOST_PP_IS_ITERATING)

#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/enum_shifted_params.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/cat.hpp>

#define i BOOST_PP_FRAME_ITERATION(1)

#if i == 1

template<
      BOOST_PP_ENUM_PARAMS(i, typename T)
    >
struct list1
    : l_item<
          long_<1>
        , T0
        , l_end
        >
{
    typedef list1 type;
};

#else

#   define MPL_AUX_LIST_TAIL(list, i, T) \
    BOOST_PP_CAT(list,BOOST_PP_DEC(i))< \
      BOOST_PP_ENUM_SHIFTED_PARAMS(i, T) \
    > \
    /**/
    
template<
      BOOST_PP_ENUM_PARAMS(i, typename T)
    >
struct BOOST_PP_CAT(list,i)
    : l_item<
          long_<i>
        , T0
        , MPL_AUX_LIST_TAIL(list,i,T)
        >
{
    typedef BOOST_PP_CAT(list,i) type;
};

#   undef MPL_AUX_LIST_TAIL

#endif // i == 1

#undef i

#endif // BOOST_PP_IS_ITERATING

/* numbered.hpp
OEGD4FXeE1hiO3g+RNFgPh6+mKR0dmzpI4MLSGekvWpMMjeLZmlhOg9sfUy9If/0dp/xeRfvj1s4i0gFju7argSkrxfCvd7VattgOCcQGJZsXFbgS2JCh/GMuA1kB/p0/TLNMDW7SF1lOk7CyvTOIW8Bdq2Z4OCTSmV85styVON3oShFMM5FvHn7VTVY6COYCmGfTHQ54ALPpE65i3ZDG73uKjqRrV3d0mbqBuPonOzUBb/Gj5dz8z2FU+/a61lC+IM/a3UQ13taEe/2YznOJv966Y/2FL5b1D7hrOFG+satUFRYel59HShZ/0sX8yf3TfjcKNMIn/GQJu1Vs+cewv4J58heu2MFsmsThtgdq7JfOhaoLUNRuLxFCIjRZlr0RwsJqg1/TRYpvA+0C/KPSg1YtQaj3rgntrAEJJJ35szby7M5BW3G+3hjN47VhpNvvMH5ZVDB8sOopAfbsXk7gY/L6z9sd4Qz7NNpiRn47DU6xl/8iRJvRujb/9y6H1AYTflN3zlCZu7Sc7GXHZ0ltPyPMd0nVrZjN/+J5gDjKiXHvBmEfZiyasyruA==
*/