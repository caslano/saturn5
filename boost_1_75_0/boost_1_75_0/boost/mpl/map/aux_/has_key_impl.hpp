
#ifndef BOOST_MPL_MAP_AUX_HAS_KEY_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_HAS_KEY_IMPL_HPP_INCLUDED

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

#include <boost/mpl/has_key_fwd.hpp>
#include <boost/mpl/map/aux_/tag.hpp>
#include <boost/mpl/map/aux_/at_impl.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>

namespace boost { namespace mpl {

template<>
struct has_key_impl< aux::map_tag >
{
    template< typename Map, typename Key > struct apply
#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
        : is_not_void_< 
              typename at_impl<aux::map_tag>
                ::apply<Map,Key>::type
            >
#else
        : bool_< ( x_order_impl<Map,Key>::value > 1 ) >
#endif
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_HAS_KEY_IMPL_HPP_INCLUDED

/* has_key_impl.hpp
bHmOCxEbDC2+hpB7M9/dbMQPrA7Md7cLtfsuRm4X2Hw2BZZ8RZr1CLDNQtbUD+JubUokwClNEKQg5f1LEeJDj2bvVaKDR56lklanA3B0CI/kAZgH1j3QMH9zkjijA4XpvL8Wvk18wBo9H/sMt7Bljcwce1ttUvbgVO8J+3XMTxG21Osbk7DpxaZsfLhj37XAAy0uguESGh11BDsdwYeWdiPGa4agQUis36ntYUwu++K/Xoz+36j9b+JjyyTMg9XHA7cp9cyD9QxraxcSv1NbnLaMU4NRKeb1Q22rZrQF7dlBG0CpduvhQMYuLSV+V1JBY6cDvXIKdfDV5xQizBQSlKU/iGtmsYe+Y/qcZVaCmI3itT56F7H904OnxmN4O+gs+JoALTlo/dSz1c1mb9Sj5pe1ScFrF90Va+1IWjUpoZ6jhaA847mNYjTsjCVy++DLoDzlwXIOOLdX6dQ4IY1WA7s9dZtrAZ+NJO+rFEL2YFVJyi2OntVg+S4MNSz9muMW4jPoAIxzup8+XZecIYyZrWvKlX/Rc1e10nqpr1VhJBasZWWzfbP+YpTeeg3mb7MeVQ3G+0t7jGy4ivxP2FbS6iFMbu3Tx9yb/vk7todv08z7fmFbhA5I5GX0VrCVc4GyzHvsdKZPROxCjEu5DEHekzMyBxQ4/1YI9BSu1oPzjYOJLsp5kJ2dTTIsMFi2TQDUqgPzhHICQmDXnv0e
*/