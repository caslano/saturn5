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
lZ2kuYTx58QnuQWXxBLvZxSxX99OcmS/zyQ9LhB6vCbs25tNl8OzHb8X+vUBe1tEfBYTnxeo8vbQP9hnQga7OnUUh/65fOVqbgllibhuTqe8+ovldYBzeM1/Sfl+OJOWDYZfbXrq07ityj7tWaSrs+rKjTeV+YpcHad1/ajidfwcyu+csm01mt2C5ezFqSGXGQOkTtrL9v82yUQ0kZOq8aBsp0uJ10cPlftzwb25P5t5lJmdsJ91jl3/wtut+L1ZTch37Ru377wmzUzIdfc+bcdK+Cnz48NyDdtGsXESdrYaj0/oluftHbarS/KJOBrgaD4XS02MyzTLFEMN7K/It1vZOY+j+ztgk0ovu427srCXbWEI2iqUY5uFaV8uw66yMI7Z+oeZP2ZPc/z/Zfb+YovcexX0vsPEguHUenIIra2Q500BODbRRd63qFH2Heg1ya0qHc1Ex5RJC547zVrS0m8Hfp/bs8M0FukYrkIFOIq8Re/pcWxdaCw6HCnsMT1L13VIO1qMn4LXmc/WdR4yMH1PtaF9jq73kNtTBB3BWkPxyTRqWpff8VxoeFq/i2bqeLaFLEwzdfSzULZ2s7de8H90h0rv4652OLEHmQ4F7aYWPCdDI3H4DvXsUWwWC9+zi03QywWCH4502wjO1US4MHDbQ8YTyRhXd9eFzI0m/P42+x4ZBmsne4O2CxOTYGM1fP5HAX+Twdu24eOPBv6WEJfbrP1vtbIm4rGpe8o7gfP3lF+LNLtCwT3cJ4Hvbhc/0tlRNkZC6+2+EN3BIHS5N2SUyLb8s9BYwnT6uRRHAzjcg7DBSQ/nZP6twWlbMNbLaR4KWecZ7chwPn8iuZmRkHNfKJtOJnLQ5niMN0qEzI/pvDysw6kqjdP7R8nEOO0hzYOeaqtob9fcfBiMjQkHcdy208A1A+fvgbMPsMrWtwZHYqlxiTvJpdNdWj4b2Jt5CuRprRpG2eFOQH2i+GwyMqZlYQkaLaGjOxm82qqyw7lsYf+rnfMGWMS0dku4bp9C3tWGB6opk43HBLzPKwd6DEwM4txntCL/9Y5GX8uGpuryfDpwGyQOqaWcoxKnjT2tON/0FFxQ3pzD80SP5eK9/smqymMUtlZNH6OwraryGIXtVeVjFE6Bbq4jGm/SqjT+VOB3VJWY0cJ6eVwqTaPNxNCdpvsfSYf/hzPxAJ9bp+KZh+vDdlY5PPoyUdZdVePIkToG3riPKRdvvbs4PuJi1s4A7z1VbuKJ2Sa12zMB3yvhws/+ILfLeDSTG4pHcwXcbxk3FNGbnQiLUA73kMDpCG9Xhn1V0WR63HbwTlRdW7JfUtXFaUxBZFxuNeWh3f3x3JjE1VZzbAPPudpQznA1JspCr88GbFu1jFfiwRDVYst6th7XqjNm1uvyOBewlrC7fycdzWYnYv54pOu7tRSNFjpT2A/qAL+FYUx2KW2n7m/Ces4KWQW/9nAh/u5i9MLLQOf+usMiFgM/y8f76o040126FAyQ8+3ldex70795ndyN39Int5L8Jivwv6Y6j+b8q0T6Lwuf3hovfQ+lvyNs0/dS+j6R/hJgaih9P8MNL96nHfR8Omvr8Hg+nXXE+wL87/mx8VvxOaATDH02Kv3WFyJNFWBufrCA9m+eK+ohzH7kgPPY6HRp2f1Ib4fXA7t6uVGVWK/w/iOmJHZz1Nt/1LG4fH5Hx/LGGcb7bSIAUcSKtmq4LTTTLjSwjZk49RcXaZsVe5p6XVkL3Txf6KbPnRmKiEhzASoTk+X8e8lUalM+7dIKkLTbiGdfG+qC+ytRsoEhYV89wj5jXvo4pe8l+9xI6Ueczyckz/SYyYTR/SxTHzKGTdcFkKK/ayzsF0c=
*/