
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
G20oHyOTRk4J+N4QP3fCXkjjuq986lmKUTdUOVIdmHrSk6r1ZlJt5n7Cu8fsYZZGsD3Clor9zss4nYFtOiGKxT0yjgdTHp7pZfS34jjNQfALvQYYXwJ8wwkSNTHp4J/2H3P4s72GDzVRl8X7RxFjFCuxuQqt03ykmFS3FuKxxj1FPepwLk4UXHHXy3HJzCsbgrlht4ypYFQFB83C2HyHQ5J/+6omapi27pXF3S0Jx/98g+zQrVoSMYd08pRBETkkkXmB81j3MMLepbZhTJdzQDsiy13cqDCet1Iskjdp/ngJ8iGvDu4/7XEjawXK0EJSdHbcdUYhtzJ9aaKz8WQMyl9+IZEVecC2fSrTH8T/0YK9nuIUKCwsy4efv6x3CiyrRXeMbKOvLA0HAB6TOlYcdfYLrm8aCGS7oWkJQ4wTZeDf/32ChOLuL7rkURjCDyyu4iEBjGHNqxIWITE/So0xpWhGAWfvKOnE5jYzemodjKZhzO52968zjorOrn6rs5IbLq1QGqVYKW0IsS4sLENfMBIriuPgMBCmMCWNKWOAxOJ5QQFHgP3JMRI18w==
*/