
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

#if !defined(BOOST_PP_IS_ITERATING)

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

#else

#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/cat.hpp>

#define i_ BOOST_PP_FRAME_ITERATION(1)

#   define AUX778076_MAP_TAIL(map, i_, P) \
    BOOST_PP_CAT(map,i_)< \
          BOOST_PP_ENUM_PARAMS(i_, P) \
        > \
    /**/


#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template<
      BOOST_PP_ENUM_PARAMS(i_, typename P)
    >
struct BOOST_PP_CAT(map,i_)
    : m_item<
          typename BOOST_PP_CAT(P,BOOST_PP_DEC(i_))::first
        , typename BOOST_PP_CAT(P,BOOST_PP_DEC(i_))::second
        , AUX778076_MAP_TAIL(map,BOOST_PP_DEC(i_),P)
        >
{
    typedef BOOST_PP_CAT(map,i_) type;
};

#else // "brute force" implementation

#   if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< typename Map>
struct m_at<Map,BOOST_PP_DEC(i_)>
{
    typedef typename Map::BOOST_PP_CAT(item,BOOST_PP_DEC(i_)) type;
};

template< typename Key, typename T, typename Base >
struct m_item<i_,Key,T,Base>
    : m_item_<Key,T,Base>
{
    typedef pair<Key,T> BOOST_PP_CAT(item,BOOST_PP_DEC(i_));
};

#   else

template<>
struct m_at_impl<BOOST_PP_DEC(i_)>
{
    template< typename Map > struct result_
    {
        typedef typename Map::BOOST_PP_CAT(item,BOOST_PP_DEC(i_)) type;
    };
};

template<>
struct m_item_impl<i_>
{
    template< typename Key, typename T, typename Base > struct result_
        : m_item_<Key,T,Base>
    {
        typedef pair<Key,T> BOOST_PP_CAT(item,BOOST_PP_DEC(i_));
    };
};

#   endif

template<
      BOOST_PP_ENUM_PARAMS(i_, typename P)
    >
struct BOOST_PP_CAT(map,i_)
    : m_item<
          i_
        , typename BOOST_PP_CAT(P,BOOST_PP_DEC(i_))::first
        , typename BOOST_PP_CAT(P,BOOST_PP_DEC(i_))::second
        , AUX778076_MAP_TAIL(map,BOOST_PP_DEC(i_),P)
        >
{
    typedef BOOST_PP_CAT(map,i_) type;
};

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#   undef AUX778076_MAP_TAIL

#undef i_

#endif // BOOST_PP_IS_ITERATING

/* numbered.hpp
VAUAAbZIJGDNVW2Pm0YQ/o7k/zBNdMqH6wX7fFEqF1sZXs6Qgm0MdkqrKsKwBmxgXV7OJb8+u2ufnWsjVf3W/cDuDs/MzjPzLCgNqZsorMlEUrJyS9m0J92RVnE9kSwHF5KHni0egCvfhJlvO5IiX0GKfPKTXkuvwSPVE6nu6iwmklKRQ94xQC2MURFPpGuIpbGwAxHSmPmWhr4Bt2ejny8dfz3zV4gqsqFSy8LvjzHcfgvXhDFhs84X2jRJDIzeDTBY60k3i66O0wfcJNjxpdt3mJ+L7lFlXgYaifqIxhE9V/XRMNDl+0cXPf5STTA4qjvUHjB02Txd4W+o5mgGaCdqiybL4og1t29QPaDpYOCqGd/HjAj3+1f/E7PxP6shSE0RA5YIHwFP59OFk3oUpBEtNIXB4rUgfytZSi0VdfeLszMGzhfrr+/WVd8N03rYDnf9ffLxT62yndv3D2oR0pmpb62PO3OZR8PlILpfd8Fw3W2m6VM0dMeA/f49zH952deIFoecNCRmWvlGC0ocNuFEeqxoMYKCfKhpQY4pqUhP8ukItuGefCjp2dKTNjTu+Hx315MAOtpWNdRZGbHXOXuhyKdwinyWndCjlmekbM56jMTmIsiJlBXh4ZITs29J2LQVYaIWEvWY8H/w
*/