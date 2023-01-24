
#ifndef BOOST_MPL_TAG_HPP_INCLUDED
#define BOOST_MPL_TAG_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/has_tag.hpp>
#include <boost/mpl/aux_/config/eti.hpp>

namespace boost { namespace mpl {

namespace aux {
template< typename T > struct tag_impl
{
    typedef typename T::tag type;
};
}

template< typename T, typename Default = void_ > struct tag
#if !defined(BOOST_MPL_CFG_MSVC_ETI_BUG)
    : if_< 
          aux::has_tag<T>
        , aux::tag_impl<T>
        , Default
        >::type
{
#else
{
    typedef typename eval_if< 
          aux::has_tag<T>
        , aux::tag_impl<T>
        , Default
        >::type type;

#endif
};

}}

#endif // BOOST_MPL_TAG_HPP_INCLUDED

/* tag.hpp
kc4xFS7Sm0sB7VwleImv3b5Omy4ZWkWHoWqXgenqLisrDABSp/a75VPBszay8wmdt9eJ9QmaCxbGLtVMIbGUjL7GphD04+NbsBhL6ayxE19zUNuoL2c1FXpudFW7j4fjWgWG3S3GK7Yv7naAwCNyeyivJ+lmYPW73YrQ/cjlFyLwhmlIJZIJzEZOIDVkKQ7zJUItCT6Ggs1ZfU/E4wTg5OBb8d6Ddv302tArXtKou9uHfIvOn37wKcLDMNsZfMhAotu0+upnZP7qIWWRe/z6FPOkIirCtfIWpK909sQGvONwNS727O8g74jzy4oQ6nDgdAp7MKS/gBcz3xG9NKO/QBQSX0dCFl+HDoivw9CDmh+E0HayL4XDX3o8xI9gGOEv/ZCAZvVXRayHyHMKp4fFt42wVbHXAXCQEDT4bAyN9pO9MgDPayR3zpB4YaZjKzxu5Ls8nT1gCB0AXOE4duMd2/xmLM2y+c3hd9NK2xnv6o2f8LtgJVgg9B2otO2M4cxhGeXMIa0s+M51NjPvLxYQeW4/7r8sIMVITrYCltfWon66x6PJm59xNePRXj1aksVJvAP7Yb8YXnSI2coAPK3lu/fkKbUusFEDs/aDdZ+zXB8QuSukNuhCxL0ZImKE6/4Kccix9rqh9P/Dx7A3TM/ApK65fJ6NzxgZaYrc7vf5VQaG18qyRoPHaXZrSYqN9n6FH6tPFJ75BhduS4hd
*/