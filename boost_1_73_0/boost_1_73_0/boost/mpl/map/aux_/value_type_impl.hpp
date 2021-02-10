
#ifndef BOOST_MPL_MAP_AUX_VALUE_TYPE_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_VALUE_TYPE_IMPL_HPP_INCLUDED

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

#include <boost/mpl/value_type_fwd.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost {
namespace mpl {

template<>
struct value_type_impl< aux::map_tag >
{
    template< typename Map, typename T > struct apply
        : second<T>
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_VALUE_TYPE_IMPL_HPP_INCLUDED

/* value_type_impl.hpp
7h9+oqC47Ksc7O5qrGae4O9D8QtpsXeoIggRB14V5xmYSe92WIUaCC+DrD83QYeS9OllYTFzOfzU+FguXpn0VelL34hmzk3gx+ZJ/oy7B3wAcMOSBwWvAMHNCxyvybRprnkRby+4qQD2thUvMODAzTjjyCuxz3mGP5RRXn1A6rG1BRf7Iq/yIE9h9no9GY+1pfYMwZnTQW0bf+vhPckO+jsCf45Aw0yoWh9bxtwYMwzNbAUPeGKw8QuW8fNCd/79rxUO8HwxXbyxhrX3LqjSrTXS/U/8P1BLAwQKAAAACAAtZ0pSbXRgv/wBAAA7AwAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDgyNFVUBQABtkgkYJ2TX2/aMBTF3y3xHa5aVd00hZCMboN5qCENkC0QKIaBpmkyiSkpcczyp1326eeYDNbXvcTx9fUv5xw7OGdZHtCM9RCOkq2Qw56VzyINsx5yx9YUza25px5gLcgI/OppovuB/e59u4Owfm7H+pGALtElzFn6xFIti0KGcMoOcSkbMlUMeNhDCrb6S3Om3lrxnQlxbYs48KYuhqtJHDwaRmAuS+vrwAiHD50ZX+4CvizdoTFc/d4Xs8cl98isGC8Ov8jM6YPVapngf3lJDAQ/xCxn
*/