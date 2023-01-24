
#ifndef BOOST_MPL_MAP_AUX_KEY_TYPE_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_KEY_TYPE_IMPL_HPP_INCLUDED

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

#include <boost/mpl/key_type_fwd.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost {
namespace mpl {

template<>
struct key_type_impl< aux::map_tag >
{
    template< typename Map, typename T > struct apply
        : first<T>
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_KEY_TYPE_IMPL_HPP_INCLUDED

/* key_type_impl.hpp
EQrHe/S4Vby7fiS4pXlU/NfwWF3p38Jj4X8Jj23bMBBR60AmezIW7pfBsvvx61h21p82b9Wl9/8k7TfmyM26PKi3u2fz6ipktaYVCK/2jg2pWeTksSN51JRLO0S8erHfDNTbskyk+7O06ykx7BJ+SdvN+nmP4C9tN/2SNtsd9W/77UAUO47fpZ3ubhe4hIhvWYI8RkEITmF+9mwFEY7cPIlfd8hjFEziZ6T3f0n7XUFeXFK8LAX5L2nnc185Xv8u7efTD+G/pF0DAP5J2um/pP3c+E1qkylzdrhgKqGJSvXqL2krOvDWaHwaN3f0/CXtOJdHubSmPo9e0dQlCRMVjwNLc4J0+RO7TPnfi2PHriMjWtwx7qpVUUJcFvIWCTETU0O55Qx3mRp9su7KVdyf3sNOAn8vjllc+J7tvjMGIGdhS7SeUcvxc4Y+CnrnkcLmVd5VCGk43i9pI+Q6GXuUvT8eRz87BXwxOEu8nfVGLKzTrhA3v3hQtS0r1BaehJI6RsohlE6gWMx7CMSm5U7buWPuWdGSk8ofzmxMy1r5DsC+IWTPH9afIgUu0/G8Hulu5mHwXilJ4JcD2rfdwhJer3i0Ur1hbbhEw0SJs0fzi0P3YAdd8Hk/5R1myFzmVmE2JpzIYDUSUR8NpTe/c+iuG9c+qlhEYPtvHawX7ofN0MEzb0PNbxS5qxSx4XQIBf/1qBVsLwfbq41yGfD5
*/