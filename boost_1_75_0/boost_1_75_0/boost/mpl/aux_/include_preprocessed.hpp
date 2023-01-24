
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

// Copyright Aleksey Gurtovoy 2000-2006
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/compiler.hpp>
#include <boost/mpl/aux_/config/preprocessor.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_PREPROCESSED_HEADER \
    BOOST_MPL_CFG_COMPILER_DIR/BOOST_MPL_PREPROCESSED_HEADER \
/**/
#else
#   define AUX778076_PREPROCESSED_HEADER \
    BOOST_PP_CAT(BOOST_MPL_CFG_COMPILER_DIR,/)##BOOST_MPL_PREPROCESSED_HEADER \
/**/
#endif

#if BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(700))
#   define AUX778076_INCLUDE_STRING BOOST_PP_STRINGIZE(boost/mpl/aux_/preprocessed/AUX778076_PREPROCESSED_HEADER)
#   include AUX778076_INCLUDE_STRING
#   undef AUX778076_INCLUDE_STRING
#else
#   include BOOST_PP_STRINGIZE(boost/mpl/aux_/preprocessed/AUX778076_PREPROCESSED_HEADER)
#endif

#   undef AUX778076_PREPROCESSED_HEADER

#undef BOOST_MPL_PREPROCESSED_HEADER

/* include_preprocessed.hpp
TumE59ym7otjmrPdgP/K010O+kpSzxiYY6zKQ3nL7qGTyIAi6tRTDUO6btxP5iqjVrVlXlq50cGWhfmSjG6htEdnJInbyy+0ynKAOz1XRXLrzQP9a5pYYm/Wn9W9/uUooDO6fToB4bWPfCXFSKS6WdvVpE+fSRqlAqhlu3aPXlryZAPLaFphAp77gYEKogg/bzlFhi39UqzYmU+V2n4y8+Zufy0zpjhxoNpZ8X4Fujm/QBq7cIgHZFTNzSViYNIO+cipH9SZ12148tbem6oZLfk26OnIhAKurbeJvX5NOsAGGigmnEzi1P9StAahhfo/3eeYeQ9IC/iZzl+VH7pf9QxfXFFseFi5WI5E7Qc+t4tcnPXRkVfa0XQCN1mZfulFoUzcirTm5tSsej+5V5PyNnFUkfJkCcXk7Jrddqw9426erTz92ZrL0Tb30m6sWIqPyXVJ/Fwo79p1wdpMxh6sizKWf6mrc2lin554drIU6BUpEZCO+PuBIvzdLDnJgeHNewhjiu9XvI8QIq7JhUYN9QLd3R07oo8L2fXuRYb5svQn/88E0RHLiemoER9nqlYu2isC1a6rIqTCP6briNbgafKeE1Ume9BXLktYU9v1yk6q2a3ys80KTxqaltHz5qqz2aXXHS6D++z0pikC16PQBY35N6PBYiHqYOg/JHJcUFEfuSHEGK0TpirffFWGUJa6R44gIrwfwh4aSfzm
*/