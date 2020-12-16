
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
4F5si/uwE36EvXE/9sUDmu2TnEn9D8l56BN0x8Pa814m+YbJekfJekejHL/0JUifvJ3jt7CstydWRi9sgcWwPZbArlgKE7E0jsUy+DqWxfewHC7HivgR+uInWAkvYGW8jFXQdFxIfwAOtHNcVJN6VUdPrIGlsCZWxFpYFZ/D5lgbu2MdfAnr4gCsh/I5KPf8yWPnc7ChlOcn5TWR7d9U2/6Sv6Cd9l8l7b8a8+P72t8/Sb4CdvKtk3zrMR9ukHynSfskH+tCPtNxcsTO700qoBdWwWLYDL2xNZbEF7AU9sTSGIRlMBHL4lgsj5OxAs7AirgCn8Gd6Iu7sQp+g1XxOj6LrsrnBRbF6uiFtbAk1sEaWBdrYT3LGJlyj506k9Ktxsj8WY6DC+iOF7EgXpLtcxnNywmW5ZSys5zmch5pge7YEr3QH0tgKzQvJymT5bSR5QTIctrKctrJctprxuxMkeWMs3OeSZH1WCrrsQyL43IsjyuxPq7G5vg+dsI12BPXYgiuxyjcgImYiqPxA2mX9i5yPxybSz3yYDOpRwupR0v0wlZYG5/HhtgG/TBAO+agLC9Ulqcdc3CaLG+GrNdMLIGzsCzOxio4B+viO9gU38VWOBc74nwcgAvQgAs1n/ce5nvHdj7vf5Xj4TesjL9jC7yN7fEedsX7OBwf4Kv4J74hzxFerIArMBfuwTx4EPPit+iO6ZgPH2J+zKG0haaeweZ7w3bquVHquVXquU3quV3quVPquQsTcQ8m4T6cgh/hEtyPq/BjPIif4Gd4GNPxM/wZP5frkiPojke15yW5R13IznlpnpyX5mMBXKD9vM8k33uSb7HkS9Hky8gkXw/J11Py9VLzyX1a9LGTr54cl/WxFDZAcz5/yedlJ9/bUt40LIrTNeUFL3JczwGSL0jqGazJl5RJvmtyPruOBfAX7edKJvk+l3xHJN9R7feZTPKFSz0jpJ5DtNddmeSbLPmmSL430XQ+kXt0kGjnfDJC9utRWBNHYx18FV/GcRiPSdrfE8vyitipR6zUIw4LI3nl+fhyL03usaVbPR8/TepxAj3xJJbCU/gMnsaG+A2+iN9iH/wOx+H3+Aaew2T8AVfhj7gBf8bP8SIex0t4Aa/gNbyKynF/DT3wuvq7ZLlXJvfQ0q1+lxwo+3E3dMPu6I09sDz2wuewN/phH81+HiPLLWWnHV+Q5XbCEtgZ43NS7p/5lN+ZPvJ5vP8rvzH1UX4z+l/4G1Pr35eGsN0mkpaRDpPSSco3gvKkZqQ+pBjSVNJaUhrpKqlAjvwuVUntSZGkqaRlpH2ks6T7JJ+c+V3qkzqRIknJpFWkg6SzpFukAq75XWqQAkmRpKmkVaSDpHRSrlz5XXxJbUjBpERSMmkt6T/x9ZfE/xOp8jTi/5Xn/xVT+mvdlWPc2FUUT/B7QtQgGaOHv3vz9xL5NX+Xjqw4F9O4f400vx8IlN8PtCa5klrJeDNpU4333gO6deORRIaQIFkSdYl75P138/12txyO7qs7us/s6D7w0xt3xNn71Y7ue78107ic9mXGNI954HU3stGEjadyznZ8X10+P6VdaW/5fqf9/IzXjP9QFhOxJo7EZjgGW+FYnIqnvfK73CHdamI5L88luVmdc13knHqCVEPOodpzpY+cBxdanfvk/CbnNpYp5zDtOSuGVKLYf+Zxnf3KfmW/sl/Zr+xX9iv7lf3Kfv2LvTuBi6LsAzi+4pGKJiqiIiJ4p6ioqIAXJN4XeF8JCIugwK4cijelluaFR96WlpaVlaWVpZlWb1pZWmlar5b1mlpZUVmvmdX7m93/zs4su7Kk1tv77nx6+jrDzjzH3M8884xn8AzO7v9TbvY=
*/