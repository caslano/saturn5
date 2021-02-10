
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
KXG+kBEKtXazUO1cM1HwS2zvtmIfI4mP/XvTdG4oiF+S3Jt7zj3nJkyj0qlQ6BKWV/PabK+4/qhlplwS3noT4hcoJHD81CTh8TQgfhQnZp2Z6HYa3M+ChBNGdyhGWyLSIR1IUL6jdFSeIWESV8XaFGRCi4FLDmFwcgqjgPs30BtF3jiB3nOCWMHzNRaoMev39wzdppzRDd4S+0WOld4QpzYwJcq2c0leipUBfIfAKlFiawisC3Agsz2gRKXEAqH3w1HfYGgLApbWZSmqrKUdUnpwEyc8nAwPGr5JPOX0cnAOziN0W+7G1tGoEAu1ddIF5w3ejJ6hwlSiBmcI/7HZQf/CGVNbNea48W0n8oAyn6+hmRaIuUYJeonQvC8shYKXZrD7alnrfcLeba2hWMla12lduMQ7Ph6A7028qzAK+dNekziBKB6Hd1YAtAJs/hSSIAp8DkapTZzBn87t/Xlrxp4vGtJ4xpun3bVndKuJ7v7kF1BLAwQKAAAACAAtZ0pSP6XxKaEBAADZAgAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDgxNlVUBQABtkgkYIVSX2vbMBB/F+Q7HC2lyYZRk25lBGHwPCc1pLUXK6ODvmj2pTGzrSCp7fLtJ8luwgZjT9Kd
*/