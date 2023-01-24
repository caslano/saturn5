//
// Copyright 2009 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_PNM_DETAIL_IS_ALLOWED_HPP
#define BOOST_GIL_EXTENSION_IO_PNM_DETAIL_IS_ALLOWED_HPP

#include <boost/gil/extension/io/pnm/tags.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

template< typename View >
bool is_allowed( const image_read_info< pnm_tag >& info
               , std::true_type   // is read_and_no_convert
               )
{
    pnm_image_type::type asc_type = is_read_supported< typename get_pixel_type< View >::type
                                                     , pnm_tag
                                                     >::_asc_type;

    pnm_image_type::type bin_type = is_read_supported< typename get_pixel_type< View >::type
                                                     , pnm_tag
                                                     >::_bin_type;
    if( info._type == pnm_image_type::mono_asc_t::value )
    {
        // ascii mono images are read gray8_image_t
        return (  asc_type == pnm_image_type::gray_asc_t::value );
    }


    return (  asc_type == info._type
           || bin_type == info._type
           );
}

template< typename View >
bool is_allowed( const image_read_info< pnm_tag >& /* info */
               , std::false_type  // is read_and_convert
               )
{
    return true;
}

} // namespace detail
} // namespace gil
} // namespace boost

#endif

/* is_allowed.hpp
3Tt5crc31H07q/uR/7K6r3frvonWPQN1v5zUvY/V/YpA3Qud654O1L21te6J1rpXYZU3uHXfTOtu7oLKHyWVz7HKX+nvq+BnnEd8e5nbbEJCTjdhJqJQSUuoMBBZffTDWAzsqh+TgcqFcIqq5dQGQhBfCUGYSdWGEVde/1FIVq3RmhMC/vUQMORXX2Dwb6DwjWQQfu1DAWACV25ivqVrs2qdQLuQ022QVyIkbnFQSG3BerjZJ8/m6vndzfpowSuZ90rScqq76yYqM4Imz97hvbP1RCsPH7ggHu6MLcfDsVgkDwuxKB4mYp14+A9RPLzq22GeU9DPQ2I0J6/6QBT8L3SEX/twG+ePdoDc1QZ5dWsfFc+DobiIbtrpddOdO70zHW/hW/oJPxG9fD/t4JfrpzIf2U99fFQ/KXynfvqbWFQ/fSMWwfc/jHXsp1+Lgn9zZ/iXRcEf6Ay/LQp+vDN8Lgqe7wz/l1FydrazXH40Cv7JzvCvjoAv39dBNPe2QV5PRLP4zDPPJEbXhUUUz61euIjOeCLqvv+GPf14QD5HNALY3GWWTD0XD04Mcjm9z71VRB51PDgfxqn15TwXb9THZGVlXC+XvWl9M6mZzXFZs7TmmA+m4foDKayO4M0JWcnZmObc9yywGL6kBAXJHm1zLIlHwvCzGM3ZXbmSIeI1BIaMuyHsjQqGbfwTU9/BGSG+IEMwKgGMqqESjCrD
*/