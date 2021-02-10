/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_KEY_OF_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_KEY_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/detail/cpp03/value_of_impl.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct key_of_impl;

    template <>
    struct key_of_impl<map_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                value_of_impl<map_iterator_tag>::
                    template apply<It>::type::first_type
            type;
        };
    };
}}}

#endif

/* key_of_impl.hpp
2IkVu6MClHT8VVCnmk+l4VtFNGYedYhLFJUjofUW68RMRa2WGGZVjUg/OhB1L1ALTC3SDuTUMj1fUYBTVdSnasV3rumTq7Fsk6PbJvgV24na+bIhldALZhmGXu8pL4BnfjXsoWx/cNkkete268NFi4w3KtlfgKknG5Y13UmpJK63bY1azsS66ZXLGuvEqTuDb4re+pXR21Idot2QkQE9Oe/0mmR6NR25hiM97QUgVrwox6QFzks8fcDJTRSfWhOTRAdtVWUeO8xUhV6hcNLGfeLuE781XA/fCtCriVbnA4IrsPQxSopPUvYkDE7ucSLCmSfMi1ocXMPHviArEx4zHm3TUvansmRloZzjXFp0gRdvL+EojqjAeffNcRfXOzjCoWqFJ4SCL9hjkEjeLbOvYxGVR5x6ryxLWA5bL1urnlqe0iCKclqU3smBoTxODal9c3AIsOaSj3B2cMhSHE63XDZ1ddsaz2qcGxKcPZ3h1RKR71SsyS81kQ0JRT7E1TXukDOtlpxpwdFJTfLk/Hgr3Jg/ZCGY1rA+ANSo9G/cKFWmcFAThZJnm811JkQW/iMjiCPpPv6LneyrOC7fg+D/Mrqf68M6TzvvSEOrdyH5WPMzydIHNXYB4TyoO76Dvt0jedmF4V64rbC2i0PX
*/