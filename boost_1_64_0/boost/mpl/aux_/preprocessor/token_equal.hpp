
#ifndef BOOST_MPL_AUX_PREPROCESSOR_TOKEN_EQUAL_HPP_INCLUDED
#define BOOST_MPL_AUX_PREPROCESSOR_TOKEN_EQUAL_HPP_INCLUDED

// Copyright Paul Mensonides 2003
// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/preprocessor/is_seq.hpp>

#include <boost/preprocessor/if.hpp>
#include <boost/preprocessor/logical/bitand.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/cat.hpp>

// compares tokens 'a' and 'b' for equality:
//
//   #define BOOST_MPL_PP_TOKEN_EQUAL_apple(x) x
//   #define BOOST_MPL_PP_TOKEN_EQUAL_orange(x) x
//
//   BOOST_PP_ASSERT( BOOST_PP_NOT( BOOST_MPL_PP_TOKEN_EQUAL(apple, abc) ) )
//   BOOST_PP_ASSERT( BOOST_PP_NOT( BOOST_MPL_PP_TOKEN_EQUAL(abc, apple) ) )
//   BOOST_PP_ASSERT( BOOST_PP_NOT( BOOST_MPL_PP_TOKEN_EQUAL(apple, orange) ) )
//   BOOST_PP_ASSERT( BOOST_MPL_PP_TOKEN_EQUAL(apple, apple) )
//   BOOST_PP_ASSERT( BOOST_MPL_PP_TOKEN_EQUAL(orange, orange) )

#define BOOST_MPL_PP_TOKEN_EQUAL(a, b) \
    BOOST_PP_IIF( \
        BOOST_PP_BITAND( \
              BOOST_MPL_PP_IS_SEQ( BOOST_PP_CAT(BOOST_MPL_PP_TOKEN_EQUAL_, a)((unused)) ) \
            , BOOST_MPL_PP_IS_SEQ( BOOST_PP_CAT(BOOST_MPL_PP_TOKEN_EQUAL_, b)((unused)) ) \
            ) \
        , BOOST_MPL_PP_TOKEN_EQUAL_I \
        , 0 BOOST_PP_TUPLE_EAT(2) \
        )(a, b) \
/**/

#define BOOST_MPL_PP_TOKEN_EQUAL_I(a, b) \
    BOOST_PP_COMPL(BOOST_MPL_PP_IS_SEQ( \
        BOOST_MPL_PP_TOKEN_EQUAL_ ## a( \
            BOOST_MPL_PP_TOKEN_EQUAL_ ## b \
            )((unused)) \
        )) \
/**/

#endif // BOOST_MPL_AUX_PREPROCESSOR_TOKEN_EQUAL_HPP_INCLUDED

/* token_equal.hpp
XKU+juT/x+3k5ETJV5yAFXAiVsNJ6I6LsSEuxX64DBNxBc7ElTgPV+FqXI2b8R38ANfgA1yHT3G9PAN+F0vge1gON6A7bkRP3ITeuBn98QPsgztxIH6Iw3E3zsM9uBWT8Th+hL/iXqQu6z7GKrgPG+J+bI8HcBAexPH4Ca7AT/Fj/Ay/w0P4EA9jcfLuc6yCR9AHv0B/PIYx+CXOwOO4EU/gEfwKL+PX+ABPotLm6BRWxtPoi2ewH57FkfgNLsBvcTuew6/wO7yB32MByv08lsYLWAd/wPZ4CQdhCo7HH3El/oR78Wf8BlPxPl7Gouy/rmBF/AXr4zXsir9iFF7HaXgD1+NN/ARv4UW8jY8xDV3zsT/C6ngXG+N9DMAHqMffcA4+xM2YjkfxEabiY1RuzP6O5fAJNsan2An/gQNRZ0cbUMyFizE37kI7PIn2eAPzYP783JvHqpgPW6EDhmB+1GNBnIjtcQZ2wLnYEZOxC/4N/fAydseb6I/2bHc9MS/2wkLYG+thX3wd+2FL7I+9MBAjcCDGYxCOwxCciKFo6KvNXu5pyL2OdP4zW9mO5QJkJL9zxUSsjKOwJo7GBvgWNsE5GIxzcRzOx4W4AFfiQtyMb2MyLsJPcDEq2/FSLIfL0B2XY0NcgU1xJfrjKuyJqzEQ1+CbuAGn4Eache/jWtyMB3ALnset+BC3YXG2x+1YBXegD+7EHrgLh+GHOAt340bcg0cwGS/jR/gb7kXKWrcPK+N+bIp/w754ABPxIC7CT/A9/BT34iH8Bg/jXfwclTaER7AGHsXW+AWG4DF8E7/EVXgct+MJ/Ay/xkt4En/Hv6NLHvYTWA9PYxc8g0PxLE7Bb3Atfouf4Dm8hN/hU/weC7M9nscKeBGb4A/YGy9hAqbgXPwRN+NPeBR/xlRMReW66jKWwytYF3/B5ngNB+CvOAqv49t4Az/Am/gV3sJreBvzsD2mYSW8g154F9vgfQzBBzgOf8Nl+BD3YDqexkd4Bx9j7vzsJ7A4PkUP/Ad2wj8wAnX2HN8xF67F3LgL7fAI5sGfMS/+gfmwNNufAzbE/NgDC+AgLIiJWAgXYmHcgUXwBDrhNSyK+bhXVgxd8RWsicWxDZbAEHTBceiKy7AkfoSl8BiWwe8xBFMxFH/FMFRuMISjC0ZgE4zEVhiFAzEGgzEWIzAO56EeV2ACvovD8QCOxDOYiD/gKPwVx+BtHIuG661cck9O7tWl859K/L8yKsMkJV04Gd1wClbDOVgX56E/zsdhuBAn4ts4HRfhYlyM63AJbsKleBOX4wNcgcp100osjKuwBK7GavgO1sA16I7rsSNuwHjcifPwQ1yMe3ApJuN7uBcP4D48i/vxHh7ER/gJOirnEVgOD2E1PIxeeAR98KjkW5JO7rHhfLlOLYSmZ0lf8js7PI6ueALL41fohV/ja3gS/fDv2AtPYSSexng8g1PxLM7Gb3Aufivp8NbJ/TdsJumwx1qSjgLS1rMQVsPC2BiLYEafhzJ/iMyv7vPwqfRhayfz28v8ebAL5sUBmA+5tjC0U6vMBuVLGEgYQ1hOSCacI9wnOL9N/28EP4KesJiwj5BCoI3bM9vH2S8q8F/fBq6M0q7tJbWB+yv773Ml730J4YQ5hGRCCkG3mHZwBF/CQEISYTVh32JbGzjbYBtsg22wDbbBNtgG22AbbMO/rf0/XeUpzf//XN9/SvvwE8V18g0rBnlmWMlO+mxBQxu22qY2OESr03xbz0IfLYXcVd+wYtxPxumj5bntntT9iwRbaPN0QdPvyg1N/3JXn/MNrBR1myj1d8/izPujC4o070MsmPEs3ymj/diOOvLepLd5P39+8txraV4=
*/