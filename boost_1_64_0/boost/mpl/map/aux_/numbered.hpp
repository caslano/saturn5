
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
vzvzn5l7Z5HBrLcxfU5fZrz3nnPPPffOnHPPPafyVfmqfFW+Kl+Vr8rXf/jrD6r/37Tx/95QPQNQJPWY/lgb+2AVpTJT01r/75dnzHIYA1Da7l3fN7Wr39eyq9/72NXv66ie1WeqQ6WpQO5ty71s1f36CNKXlslSOtt4gltJ96NYxds2nmCptBeo7/2rxxNU9yE/Jvf6l0o+PC7tIIG1rPngkAc+qLtOO8ji2r9/O4jmfr/kx04ipeme+2zkR23N+Iqy/9r84ba6dXzFU6b95V7OHdp71xEe0udS7l3fRujalPwxtxPlTou33WrnXv917l0HaspIF7aRO80cVx+J64iT5wnmcCzCncRlyDJYpi10O86IxuY4/SX/O/OPyjYm52Vyq9F2//xIVVfjKVa8bcn5OJH/f21OLsZTdNEW5Xo8zj+ZPn/u1ZVvfXgo+9J9dYr82lX/ecTNa7u6WeNN/ulp0/brtej4iyHPsCy6frdxupKH/r1tWqU6ub7LdZ+mBE2/6tHSpjUW6+Hd2BbjMAQTcQAm4ShMxgRMwXTU42ycgstxKr6A0/BlTMeDmImH0YCfYTZ+izn4Hebi92jEXzAPr+F0rEa687EW3oO34r1YD+/D1jgT++Asy3MM/B0o17elst8tVXPg1Jf9bij73RhbYAB2xttxKDbBKAzEaGyGE7AFpmFLzMU2+DAG4XPYVvKhA36MnfAr7IynMASvYhf0kP7gXtgV/bAbBmJ32b8e2AbvxFDsiT2xF4ZhGMZgbxyH4TgJ+2EK9sd0HIDZOBBn4yB8DAfj4zhEPTeetIX6EubZzWV3vIptuXBZrp6L5WZWcLzRDf9hY472+D8Yd7TBmMqxRyvSJvqfPPZo7BL6PxBWE3YuqWxfrXxVvm7W6/ev/yelZcVnpugn//b+/0r9fxf1/xC7+ffzsDZm4yPK/X8vU12r/9BRyozp8SMjBg5yo/+3l2/hLc6fm2aObGt9dygLT09Mt9Z3zytzixupj0nddgHxK3sbn5iXb+oHL33Cn+cmaW5izhT1uHOP8mOHxaz9xJW4yLJ4csxUn51oTo/uMZkvIETqmPOkvr9F+o2/QpjLMuHVTPttit6Qo5+clu9OnwfV8+FYRz3nAQ94a/rye/KZ6rl7P/RQPpP9cpEH1vp7oKe0haieZUjR57BFbX19iNShJ8r+jZf9C6xuv3+m6rPbfeF/z31UH584SUx9KZd1UUn/WlX6c/MmW49PwL857TKugkMZLbWVUbeOoVJmdTVsZVZ9TAO8nB9TXU1Nnvxbj+nCMD5TZYy0pVD3qngd1kXd3EXbS8XbIly0mbioO7t6hsBVm4mrurzrtpRCU1tB7uZ1H5w4P+jEkaLno37M+WCspR+KXJPlWh1o1w+lq9Rdu6EfdsfG2ANbYi/sgmE4EnvjWOyLaRiO92I/nIv98VEciM/gIFyPg3EjDsU3cRh+jKPxM4zGr3EMnsaxeAtpHIfVMRZ9cDw2xAnYHO/GdhiHoTgJh2MCRmEyxmEKZqEes3Gy1E1X6OTaLdf0QOUY4gIp8GmSP5lYF7OwEWZjc8zFMDRiNOZhLE7HOMxHPd6DGXgvzseZuAxn4Qq8HzfhbHwFH5D0perk2osTJX01MU7SN1fSN1/S9wjWxwXYFBdiD1yE/XExDsclGINLcTzaxjOUa6VcQwNV4xmqx4DYKPFtkvx4CZvjZuyIr2J3fA3DcQsOxW2YhtvRgEX4CL6O6/AN3Ig78GXchdtxN+7GN/E4voUncS+exn34E+6XNp13sC4eQJnvlYxT5aPdfK8rZL+ekv1aiZ1wFXbB1ZJvT2MMPiP5tgYpX+U+WyBtC+o2BVN7QvBSb2k=
*/