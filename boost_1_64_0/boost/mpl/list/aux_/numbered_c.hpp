
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
/X+S5fX/67r3V+7dI9R7d7lhZxhFBmqKlXjolnCP2s7QkiJ7S3L5Lnspp8Uwh3t30hJpaT/oZ/BSv5cctlD/jfYyC+3fTx5yb9FvILdVp7WOsE2rZp+mfmf9mwXqNPU762/ap6nfVN9on6Z+j9lsnxZmm9bTPk39Xvzb89VpobbvMQ+er//WejN1vL1j20GX74LwP6Vtu9nx/S6mpdmm1VK0TlPfKQhA7bv0Z3+Td+sJfoxfZjyXf5vjeYst3Zhpm+8S081lmC7jFxjXvSfD+ITajOemWMYLGVfSwyIsbTrft5a/4RESqoyflfGT9dz71rHzdnsu2+G5aI/oqj2fq3qWkrezLGm7xpLWBzlvD1ry9p2u6rlestQrbSxb2LBlkypTYoYFFMy9b11wyduDOm/3eePq0b63tGeUY40ce/Ktz/5pFyl9aUs/mDUxGOtgcwzAMAzE4RiMCVgfJ2ADnIkNcQk2xjcd2hv8gM2xFHGFYASGYiq2wQwMw+nYDndiBH6GHfE8dkZv5RED+mAUhuPt2Blj0Ig9cAL2wgXYG5dgX3wC++EzOADfxYH4Psbh9zgIL+EQrM56GYo1cDiG4WiMwjHYG+/ASZiAi3EcrsAkpI2S8jym2Gc2/wvPa/6ufYI6Pq9JqO2pH/UMnsEzeAbP4Bn+24ab//w/hQ4X0tNvxPN/5ft/v7fgWpELYy/p7SLbsvQUS/1ARz+D+r5eQ7kOryhVBeUJZVvyzN9eP2BJmDvforK8QyvfkXlNltuLUJkQI30OFt5tWa4lMfpeB//4e47u9jloeU9R0pcuffatkvQtlz70js7Tpo9kXcf7l47pqkagUw3GNX3o5WRdM53HvBzeAZf3YI9qy5E3H9351pDT91ElngSpJ7pN4mki/QsVaMuDHoZK8q6vpTzM+nf9qXvQ9aWQnTbNCLq0HJK0NJW0NJY8F2jzTC8wJX0Hd1yaGo/u23+NJJ4GhO/Jc4I2z+bc68qzklHaxOjiPSXxpsi2N07K+sxcTbxKrxV/oN8jtazd7LfCcXvLkT790iVtqYSLpC1Wkzbrm8l/PG1V3XgvmXS5VedU0ndanddRuapbKvm7pTe7bqmkdV0l/TbUN5a6pekHtrwZXvnJW5e/3b3UZ6sznyh53ZXzuqiS1y05r7u6dp1TqEHOX3JeS9W1dZV3UbAZlsfmaP3WlJyfsJfMp/3WVLa0Gc5BX5yMdXEKBmMeNsFpmjZYMThLfbdMzi9y3kl1eOdjrCw/Ef1wHPpjErZEI3bCFByF4zEFUzEVJ6AJJ+IkzMClaMLlaFbfqZHzB/pKOrTvsLSX8umAFTBc0tUFq2FXdTlyfsDbdMtx/a0gH5wr5TRPbTMux3Y55qc6tBlvKctpJekIxZrYWsq9DTZG7TtDCZKuRrp0uW677oMLsQEukuVQXnJMpsxlOd6YLMu5XdLTDX2xu6yvHhiIPSWfvbA59sbu2AcHY1+Mx344Dvtr4o2VeNOdxBsr8cZJvIMxCIdgQxyKLXAYtsbh2BdH4EgciUYchak4Gk+Wsn5TaHdt7/+Ldt7/K/WGx1hfhQRff29DKKEfIZWQT9hA2O3vqVf0DJ7heoc/5f4fb+T9/7HFuvt/lm69/+/iZ1D71Wnq4v4/aq72/p9ZLd09FX8fpK0DOOSiDuDMHMuylaX+pXUAZhd1ALF3qen7r6gDOCnp7CXrqIfcD+fby/GG1AEku6gD8LGXx59WB3DK1m5F1s0wybOPNs9KHUBJ75HT7NuEfyTrIkcf7xAXdQJn7lTjvSl1Aj5y371P8vuilH1hvhqvtU6ghP2dlaROQPqJV9udXJJx2/b6O0OQMk7QbZ+S9kuS9kKpM9g=
*/