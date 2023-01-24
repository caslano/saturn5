
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
52s8nkx39ud159EbkdmZgbeqeb0kLjD2rwOZdENtIMA9NDDjKadUuWRx7Ni8Fq2F/WPJF0Qy6j0MPirhCxluwptvRtjkwx7G1zE0fa06VjucN2g2vulinTP7KIIxFrBr0Vp8VjvgYliVQXcrb5awRJ4cY+E/wfJV2PhtECr3BGqdhSWAS4USidomRmuL6/rbAVYkGmMwePk3vCd+Hb/9hv5ejCy4EZ7Rk96ij+5K5opOhtHno9Jhppt2edY8e570CJtuzHS5Il31oIKOP2GxxZZ58lEMLd+XXJdkwpfRhxEFLQntzt0U9fDrjklHC+4IGuhJewoQTwRN5Occp1zBjKCVcpuhqYExt4GpnjbfSPJgQC0Jd8SIFkvpIrasonBzMsWnc4sBuddOGeQNI7XGgjhR6cIljOmLhfnjI0ISkQaHidyRxormoDQ9eSfuBBKg1Ws+WcVR9Js4c3a5ImnMtvG80bgE+y2JOTljfHIl5n6aj3vVeqtTzyPN2HtoJ0n6vpqQsAgkmMl83bZm9n6GmpMS7TwsCGjbPwXYk2uHhlnS4r1irU0d2n3j1D/R6tzdbCT87VWpfAk5PQi3qMjfuLF7hNlS0SwBbzDH3PxNzphpTvMJ+ijrVMe9RrXIc+czHuZplmtJucyPId6MM7nWmDyRBvldzenvZjA2eXD599jIlipTJgTo84GjXsYa3ylnACgTThqZg2os/IHL
*/