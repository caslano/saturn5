
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

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
      typename T
    , BOOST_PP_ENUM_PARAMS(i, T C)
    >
struct list1_c
    : l_item<
          long_<1>
        , integral_c<T,C0>
        , l_end
        >
{
    typedef list1_c type;
    typedef T value_type;
};

#else

#   define MPL_AUX_LIST_C_TAIL(list, i, C) \
    BOOST_PP_CAT(BOOST_PP_CAT(list,BOOST_PP_DEC(i)),_c)<T, \
      BOOST_PP_ENUM_SHIFTED_PARAMS(i, C) \
    > \
    /**/
    
template<
      typename T
    , BOOST_PP_ENUM_PARAMS(i, T C)
    >
struct BOOST_PP_CAT(BOOST_PP_CAT(list,i),_c)
    : l_item<
          long_<i>
        , integral_c<T,C0>
        , MPL_AUX_LIST_C_TAIL(list,i,C)
        >
{
    typedef BOOST_PP_CAT(BOOST_PP_CAT(list,i),_c) type;
    typedef T value_type;
};

#   undef MPL_AUX_LIST_C_TAIL

#endif // i == 1

#undef i

#endif // BOOST_PP_IS_ITERATING

/* numbered_c.hpp
ncaDaTgGzMgtiTbp1RGsP88O/HSxgbcy3KiKCXlk2bViJsfj1kb3Fml5iqD1cXVKWQCR+KUVwaWM7i28BsaZ4jU/YDOh9AivSsfQ6sRSwTnS6/jBMAnVePKx7HMt1TtbLmQZIBDY0qnGTNNrJ3lNtR6BLSaXi0l/KLzP+gS3XVmx0W/pOWrrB52K4eX9G0f4RjAr6TQwuECmCr2VGhln1Yddfxkv4G5CVPgunBmBakyTREuAhQEFED23YnDkDwIx3SDtNuqVLGxUSbnHbfxfSZP5HAdRm6ZiwZk7m33PRN9aqKkP/R77JhS1xgVkXJuwxfFFObJuhK+q0msi6UwPE3MhrjiQNF7vragRUmTzKn67zH5mOy18i3UsEqTp6z1Eib7QANfDlYkRVaHHHhyQDUzPtYgCyttFxANJUrFXvBX/Trpjrwv+mPxY8YtZ5/EurFXrQU1UBghdunYcG2zagrzQWgJfdBxcEtdIamV4sZuzNCO553qb+TvnADU5yK4URqTyU0EamKHpWxOoAlUaFOefpXr5eMrqtckNhAkp5Cy7sjYwNTvtrJJF3w==
*/