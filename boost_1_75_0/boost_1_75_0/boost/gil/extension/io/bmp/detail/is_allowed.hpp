//
// Copyright 2009 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_BMP_DETAIL_IS_ALLOWED_HPP
#define BOOST_GIL_EXTENSION_IO_BMP_DETAIL_IS_ALLOWED_HPP

#include <boost/gil/extension/io/bmp/tags.hpp>
#include <boost/gil/channel.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

template< typename View >
bool is_allowed( const image_read_info< bmp_tag >& info
               , std::true_type   // is read_and_no_convert
               )
{
    bmp_bits_per_pixel::type src_bits_per_pixel = 0;

    switch( info._bits_per_pixel )
    {
        case 1:
        case 4:
        case 8:
        {
            if(  info._header_size == bmp_header_size::_win32_info_size
              && info._compression != bmp_compression::_rle8
              && info._compression != bmp_compression::_rle4
              )
            {
                src_bits_per_pixel = 32;
            }
            else
            {
                src_bits_per_pixel = 24;
            }

            break;
        }

        case 15:
        case 16:
        {
            src_bits_per_pixel = 24;

            break;
        }

        case 24:
        case 32:
        {
            src_bits_per_pixel = info._bits_per_pixel;

            break;
        }
        default:
        {
            io_error( "Pixel size not supported." );
        }
    }

    using channel_t = typename channel_traits<typename element_type<typename View::value_type>::type>::value_type;
    bmp_bits_per_pixel::type dst_bits_per_pixel = detail::unsigned_integral_num_bits< channel_t >::value
                                                * num_channels< View >::value;

    return ( dst_bits_per_pixel == src_bits_per_pixel );
}

template< typename View >
bool is_allowed( const image_read_info< bmp_tag >& /* info */
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
YRg6AphvxQPDInTHsN+qubGF4BtoY539KVGc/HiP4JGOSFuR4Td4OEiQ5Xlw7rv9RVVzqyx50CSAmY2wny2K6wq2lo/t9nTolW4p1JPcMq6zVURleFRKGjK2RBqUkhlZiW3xCmKaw/+w/veT4ShCPHNcOaLVfTd3MWstuuL2P2wHyaldq4cWig7j/D5VuiULHbqxTEpiWuH9S9pUw07iosJYy7dD4vy7tZS9ku5xA0BUb8x0tXDquwqlGkC0WjhIadEwQKLjIEa3gDHEwYUyDupsLnJuWvDGt4R/AtCZTW84lKwSkWrw5zJ7Hias7kex3IfB2ZhP6qEdyPqwW8cSbHaXlqqou2vVmXbYasrD09EWEWIPpRUqn6Rj1IMQ1HsrYeiQVpvuoEyUruzFFswrf0w3utB+Wj6xci2LZRaU6NRQAW3I5MJQENzEsJQWis9vnXiMa+S0PNoPyUxJZg+XVso8mHY+FRiyr+HsizwG4dxT0DAQYV0InHf7rZhGhwIg09WD3WY4J4T4+MBFNEA1PRnPQCdlytyeq426PlxviThqPVmTq0QB/6CaQQuufXpkurBbn0UREJlyECKvuvMlxWoT068rQCb0l+xzcTkGdpNqy0G90HydqhMYpbmvF/jaYimb8pGuo/odZ4DSpF2mLohsOkig+DkeT66C61emBOHm3ncrQcLBv5GaTHD1e6GKEZr/hEtd3m9OF7N1
*/