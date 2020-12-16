
#ifndef BOOST_MPL_MAP_AUX_ERASE_KEY_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_ERASE_KEY_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/erase_key_fwd.hpp>
#include <boost/mpl/map/aux_/has_key_impl.hpp>
#include <boost/mpl/map/aux_/item.hpp>
#include <boost/mpl/map/aux_/tag.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/base.hpp>
#include <boost/mpl/eval_if.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

template<>
struct erase_key_impl< aux::map_tag >
{
    template< 
          typename Map
        , typename Key
        > 
    struct apply
        : eval_if< 
              has_key_impl<aux::map_tag>::apply<Map,Key>
            , eval_if< 
                  is_same< Key,typename Map::key_ > 
                , base<Map>
                , identity< m_mask<Key,Map> >
                >
            , identity<Map>
            >
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_ERASE_KEY_IMPL_HPP_INCLUDED

/* erase_key_impl.hpp
K1jyfJvRZbt+/lX3fVc118kizXlQYG3nSVU0+Vl1bVXa9KTIDY1cF23uA05r26pq8sJ5zXV0j6Utq+NroTJth+Q/dZvRfIlXfR91TtMO1ua3NZ3UUOVP9Xt5x+U7ByrD/Bvwh2p/ydrGc/oy5+L5aqa+2IJHWs/pPAftUQ87atMq6wgk3/uw8FbVOvbptJXVW0cO60hVrgtR1nWccPDubDDzLSLcpZR9q+bdpolP3f5k+zDTfBVCpA3sMNs2sRsjbb9/N8L2++9RjvuLjpEL0zG5ln2ArsRRGO24nRMnvBP9h1eq8UKs+Tzju+o8Y7/KdI+ibgflrTmHfLT3H5r2Tdr7C3Xe4xppzEPym6N/nyznovZ8LtHcRxRxPKPYieFKOXIM++7gvpJ0t7lPLGAFymeP3EPsQCXtA8fYpz0nOJusJL8z7XPpfzrB+fTXXONuKO2LHaR9iSbtj9u2K3Mq7U9o0l5J63hPtpP1pCl16Ma0kuOkbiumvWbIA2ttOYcdtQvL5ai0Z71d+N47TtXuXvOurrRLkzZtpokcV8s6EpnXh4V3yzps2yyOTUpIjrc5tzPibNuKNY+3/T5W8/2NeM38Cbbf56u+q+9Zk2tKIY48288gVFLO9bHG/CaPbtG0jYx1+rne0fObQfUMrXke0G2ve7qm4/ZkOeNuTXuy/l728d1GWuQ5is+QaihLfI7enT7sZd9erDLxFTiMb3J64g3EJ8fA3F7tT/XT/b/6jrPjdltlb/+l195qiLHdVnHnlKIrrQaPfr3Dd0dHxm4hDfTabcmYuFIWSxmtsR5NNSautHeqg/HYEBPQD8dicxyH92IiRmASjsLxUs8/Qd2vt8QzTOJR9+ttkHrlNOyA6dgVM3AQTsbBSNGk9H8r5Y9SLpmo6f+2vxQnDsA7cCDWxEHYAMPRvP9Zsp5oB/tfw820XTWxJnphHayFSry1sSfWwcHojSOwHo7C+kg81NNL2aGUKSrxKA8fK1D5+Es892AtvBfrYyC2wFYYjEHYGVtjLwzGQdhG4muLMdgOZ2B7nIMdcAl2xNXYCXMxBLdiZ9yJXfA17IHHMQx/xJ54FXuh0r7tPqyG/bEpDsBWOBDbYzh2wftxIA7FYTgMH8DhOB4jcQ6OwPkYjStxDK7HOHweE/AlHIv7MBHfxCQ8ghPwGCbjKUzBs5iK3+Ek/BHT8BfMwD9wMiplu1PkOPlWkDJFKWtMJDRWjrscp0Ou7Dcexlp4BBvhR3gPHsOOeBzD8BMciJ9iBJ7ERDyDBvwcF+IXuBzP4ir8Etfi1/g+fotfYRF+j+el/vkfeBkvYE228Uesh//EXvgT9sOfcTyWYApexGl4CWfiLzgfL+MmvIJb8Crm4TU0lrlKvDkVpUxRyhpJJ84t2scwnQ/3RzJGO3rhZPTGBzEYM7ETTsVu+DCOwGkYgzNwAmbhJJyJmTgLp+JsnI1zcDHOw8dwPj6PC/BlXIR7cTF+hEvxJC7Ds7gcPZT2ONJubSU2x1XYCtdgB3wcQ3Et9sJ12B/X4xDciKPwSVyKT+NK3IQv4Gbchc/gPnwWD+IWfB+fx7OYh9/iS/gzvowXcYe0Y9uJSruO3dgI92Iz3IctcT/2wddxAL6BwzAfI/EAxuObOBHfwjQ8iI/gO7gOD+FufBdfxyP4Jh7Hr/Fj/B4/xWI8KWP4f4aN8BQ2xjPYHD/HQPwCg7AQ2+NZ7IJfYm/8FidgEU7E73Ey/oDT8B+YjRfwCfwR12Mx/mTKB1IOSh6VfDlQ2loqn0uSL3+RfHkF6+Ov2AR/wxb4B3ZEF1dTe5KKOAFdMR3d8GGshDPxNpyLt+MSrIw5WAXXoDs+hR64A6vhXqyOb6E=
*/