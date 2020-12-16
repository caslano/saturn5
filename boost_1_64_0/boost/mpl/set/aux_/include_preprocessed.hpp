
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

// Copyright Aleksey Gurtovoy 2001-2006
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/preprocessor.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_HEADER \
    plain/BOOST_MPL_PREPROCESSED_HEADER \
/**/
#else
#   define AUX778076_HEADER \
    BOOST_PP_CAT(plain,/)##BOOST_MPL_PREPROCESSED_HEADER \
/**/
#endif

#if BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(700))
#   define AUX778076_INCLUDE_STRING BOOST_PP_STRINGIZE(boost/mpl/set/aux_/preprocessed/AUX778076_HEADER)
#   include AUX778076_INCLUDE_STRING
#   undef AUX778076_INCLUDE_STRING
#else
#   include BOOST_PP_STRINGIZE(boost/mpl/set/aux_/preprocessed/AUX778076_HEADER)
#endif

#   undef AUX778076_HEADER

#undef BOOST_MPL_PREPROCESSED_HEADER

/* include_preprocessed.hpp
5LIYxzYV8W5xEHvbWFDmwt+FjXF8Pp8LG9JPFxnzVWBfliGOndw3VkFTOS+sRzmpuxH+LWNfPiniMIf5mN5mzP0e940w/NvL+u1DuYCs/0O8cu9yHOXqct0TxpznWKvT8Pld1uUscr5H5v+MhZ9hDS6BPc/6/Y72ZD1S3qJYZ8R1CxkLtuAxu4ixTJk/vQVsqMz/GfNP5WOhvDGfrCtwGXMOZk2rG/PKHGhtY5GfZP4P5US/xsbcYR4Tm8LGMbZ7vzHX99wPHjLmqMbn1ZaIYw7XfQKsK/fxNtBqLueoHeIdl4dYR2gl7wLEGwu9yb50RxyypqMX6oZYK5+xuGOco77QZS2XGwQbt8r8nzHPCT4+XkTdF2T+D9p35PPHBMRbjG1Mgi7VObY3YHcf96u34PMmjm2msfCrnPM5xgKyJmEhNK3O+V0Ku0+xfyvBtsr8H/T7juf6QtBA1iF/DP8e4vx+Bl16cb/fiRxV4z65F7pcZBuHoMEl1uVzY64irMFXqCtrek+B9WG738NuY9b+PHyWe4OfUfdZtnsZOkufzFPM2Gds125b7HqDNShszBVl5jQWkXvJW1HuEueonLFoe85HZdiVflDNmKMbH4O3G/M4+Pxbz5hb1p82Mha6k23cDSbPV++Dz8/xPd2DxjKbsd1HUXc7+9fKmDeV++lTxpyT+Nh6FuXCfJ34POzK86g41H2V6yYa84U4jhfg33nu46nQRd75yTAW2Mp2B6LuAO4vw+CfXAP/1ZhftHoJeRNfxkOXaTxevWpM1wq9jnJyHnwT/knfmAH/CnN7s43Fbee6CxBvG5n/g6bSX1YYcy3iumtRd5Cs/0P/k/UCm+FLlNmnxtyprP3foUsjI9fO/xnzefl4O4i6z7B+xxCb3WDR/B/yUYz7wTeI7U+O4wzieI3bO4e8Pch1f4Ivm/j65TfYWMA+4yVep1x3FjAWzsfsJmOhGvL+r7G42jwelDQWlTGnrLFIW463kjHfUR53bzMWkLU4tWB3IftS15i/OsfREO3JWHKXMbfMAzdD3UHcXnPU/Z01fQS6vFKE2F+gywKu6zXmlevTZ6CLPAPqYMwhz3a6GAumsX8JsHGJz5dJKFeC/UuBz3VZq3SU68TH/gDkQ96HHWrMI/fYIxHvSj62RhvLlHuDccilrBd4BXkTX6bAxllubzrqNuJjKxM5CvHYPgs5nyHzf7Ah69KWwEYe1n45fL6FfV4DXeZxf9lgzLFH3v+FXdFlK/IbkfV/sCvvqe9Ge89zewfgcxdZ/wd2A491X8C/QZzzr9EPjnO830E/uf+Nwu5ptnEROT/A/e9X1JVrkD8Rm4yxtrzL4b+Tx+cbjXlPcB8qZswzh3NZwol3qmX9n7FodR43KhpzdJD1f8bcO/j8URPt1eF+UAdsLueyAdqL577WBGy2rP8zFuzAunhgt428/4t45dnO48Yie1m/J2FD3rNuCzac2XPweSJr1dmY71W20c1YuB33q57Ix5Py/i98WSzzf4jtSY6tP+oe49iGIG8ynzPCWOBmbu9vyJu09zJ0Gcz5DaA92a/gNfjXjse1acacMg/3DvzbzLl8D1qFuL15YLL+frEx1z7W+X3Y9bB/q5HfhXzN9QHikLUBm6CfPJvYgnw04+NtO2w8wvnYhdikvf1g8pzpCHz+nnWOQOcebPck2N/ZxrfQKp01/cFYaKSs/zMWJ89/f0GO5J2pP2BD5jbz2W/kIW7vBvsNdOIxoqj9OuRYLW6/0Y6sQWn7DR3hMawC6u5mVsV+PWX5HFDDfp1buB/cYb/Bb7muG+Uisv4PdmUd9z326y0t6//AZH+GFvYbXiXzf9BA1lG0hg2ZK33afuM=
*/