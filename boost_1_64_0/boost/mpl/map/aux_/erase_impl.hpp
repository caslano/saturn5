
#ifndef BOOST_MPL_MAP_AUX_ERASE_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_ERASE_IMPL_HPP_INCLUDED

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

#include <boost/mpl/erase_fwd.hpp>
#include <boost/mpl/map/aux_/erase_key_impl.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct erase_impl< aux::map_tag >
{
    template< 
          typename Map
        , typename Pos
        , typename unused_
        > 
    struct apply
        : erase_key_impl<aux::map_tag>
            ::apply<Map,typename Pos::type::first>
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_ERASE_IMPL_HPP_INCLUDED

/* erase_impl.hpp
wUYV/WIM+vCmQMKdSCZyUvfplPTTLqcLakl/0AUn4FrpQ1KoCs8eSrwoNhoUW1a+E7keNFe5l5OKb0BGMBx9sRNQIhzbFNrU5RQXD30YkurBXQzHVK2aIEPLloSXhnY6oAKq/wbQM5KI3yorAAyguSoIAah0kJzYCiuhLtwhk+iA115s9jtjPh0M3QJ54FhBqtD3frzUqKYz306qwhPOxMEmcsU8p12QBik7uyQLMT3e+m4oRRleI8DXqg19BMQYuBm2YaKYYu7JP3PLrkhJMr199VIOmAz8htOebkncUnW8mzo25bflBCw4+dsJn//FqZHCjZ2W9uz/LY3U1+v03oFi5fSFGqcx4no7MXMrSvBEphim9bs5p1+PS2ioymGKJHd3oFzK20AcQ5l7f7W4fzIASsjG0BUEAduxaIgj0XHfetZkAnQhb+m1y8+r14ItReVSZIWsRNUqi0cKH1W2hUy3Cxg2Q6RRNVwSMozejqS814GbCzg6cAEtCdiy8ezaUj1KKHG6FiQx+j8A4UgcqxwXAT4+GB59+Kf15uowBhYjtMA6G5cc7pFdeA==
*/