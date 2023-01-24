//
// Copyright 2010 Kenneth Riddile
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_TARGA_DETAIL_IS_ALLOWED_HPP
#define BOOST_GIL_EXTENSION_IO_TARGA_DETAIL_IS_ALLOWED_HPP

#include <boost/gil/extension/io/targa/tags.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

template< typename View >
bool is_allowed( const image_read_info< targa_tag >& info
               , std::true_type   // is read_and_no_convert
               )
{
    targa_depth::type src_bits_per_pixel = 0;

    switch( info._bits_per_pixel )
    {
        case 24:
        case 32:
        {
            src_bits_per_pixel = info._bits_per_pixel;
            break;
        }
        default:
        {
            io_error( "Pixel size not supported." );
            break;
        }
    }

    using channel_t = typename channel_traits<typename element_type<typename View::value_type>::type>::value_type;
    targa_depth::type dst_bits_per_pixel = detail::unsigned_integral_num_bits< channel_t >::value * num_channels< View >::value;

    return ( dst_bits_per_pixel == src_bits_per_pixel );
}

template< typename View >
bool is_allowed( const image_read_info< targa_tag >& /* info */
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
3ygx2F+n8etz8aF+LXJw7rH9LVDSKJ6XHUrL7pawawnR/wfLOz8/4ObiqHlx/W9lPDgqZPgPgurkdKgtbtzwvpYOjg5+nfyWYq7yY8Lj3zrvf1YZD/8OCg33g6OjcRil3vnO/Oq9apuI0drOMOIFyZ3b0Jw8tTrfQuYhW+8mUMqdC1qz9n2hg6t1iif60TxSU7RNSh2c20jucGHyC+8x3vg8rGGvemzFUSyYBkh/PlbXK5U3JTPdmxWbXr2ajdqTn2Ms4BBUGirMGEd/ICWD7G+gJlR9etP/ycLFAKaC8LwlXK2xZpJAhcXLAe5e8cj+4hPs0JSrpUGVQTvFju9vEdAa6O5xY7V99KyFyyLGR1yreL2FiLtajofEi5luGOWbfv1NwBReeDdrH9rJ2dhV/IAM4BTqm5bdFx8tOi3zULcqv20Y0TYt+1C4Ctk2jD40TDjDHodsl4r1RXuxdPT7Y6CG/6lZvb/c7o5Q/CRfhhlf3Z6Yv1IcNWghRl+SQzBcnHvHuLD2WjY6QESf+5sO2u/rDEAkm4vrb2dhAdRZndnwjUcjsstzaHmKWaKvp0RIJfcboWKyCbrYYl6XUMN3/KRYdgH1LoqjcFZzQw8imOYWl/Y82lS9v1NMz9+3m07WKIqjcNuqn7ksFkYkluRwU3lTn0qJRVoVAQTepcTarCoB/XPo4moZfr6i4FreVyUxUPm1/KjdF67ePW8x
*/