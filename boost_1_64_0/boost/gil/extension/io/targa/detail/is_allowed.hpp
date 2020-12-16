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
B4+hUPwxw2DsQAyu4Mpaslm/2r9Ls240+fw7fdWZ01MwBz33FSzeErt1XY5S4KCF8ILsD/HMNJdqx9L8cq8loG4KLFqG3JX4rcFPMUX8xp9S72nif/5beT3yGsavQ66vdLN++EIfdUGoMZ0PjotG5y841SqMp8Dy8Or5MxP5mxpcTn3X/IEY5COCRLxZc01OLu8vN/TdS5HNzlaW4psoFS+9LUG8rHbBsUBXaJJWkE6JbkLAhYqzUayv7cYgac93apA+7QHIMYzDDiUOnrkY252A4VNjU5ygqhca63UNtSDFe/dqqFnN5w0IC5zn38VybhljuTLjDmsiZ1yWGf7naLOCKWSHvQLnEyLE4WU8A+6zf9nRxGuf7jVQGHnqw4xeAk97nJdKH6F4bMBXz7BDU6Vh99VqXkDFxsUxi14HCjFhKRus67EYuve8TdEoX22tl7bsRCxD5RHUA0u5NdLUFUt5wYd2E5fRCL9PP/9fLYf9ZBTrAW8OfteJemeE3PFA3fl352e6NmziLehSmq+rCXNyNEpvWhoK+cbRcZaw4SzsLjmp2X4qkwGLqGIyARi5xjpn91LCc6ecImKqWRkw9MvfYhrDqOr5Axmfhc6TVKC+fjRm61ISACbwO5VI4v9d9LA6i4D4boWtX0FTsLDtW1LjVnDNnYDvrFAUGoEtyl4Uyr4V2WEKguMBUP678SqdstWfGseR7apw0v73BXgB5Fv/DBmtfJMEk3tu9mPkM6Q68r1aaL+kYDuQXj1edMac3/QVc1mPA15yybv/LN3ecajpsK6LRhq5R6+DaT1+mBmtp0UminGISivpcXjmOsylvM8SJevqu+oT9OlWdiYBFcrr/dXtxdF/GnMu6AemdGrj5BuSb1+8yWGXlrT+uS6p24qi4EJ91KYCSHeVdxN/0sVr1G3NNUbk+mXPMxz5k7WCp8aOHXv1fNG1CHVTkUg075T9ruF+X7kmMU9+g/ttlv0W16jftTOj9bR4GMVaCZ0f850zeT+inmfoR6/RMM3bEk+dnrd7Q/acz3VV6TQn0FlF6cCdWMt9p2m4f6Z6gCbgoe78XuevmmmRfjs7McLFa84ssKErLEEotMnWYC/R3f0tOhhhov1F1HDTBsWWLKujgiL3S5dIT/wOGUzWD7vEvSW113b9F71CIMvq5ArjUYGHK9W6LVzl2Jt6lSquEgAsYgAaHWFNRxXdsQL9xmHrVDqmGPhN+69L/tQn+nnqA9zLGtrIsIgFwJZWpgY6wOtQNpJ57EV3pK3OCziFbNfDE9vFF2/w0NHvMwxZwqd3ZlyWauNaQgN9aiQP9MTLMoBz8nWYs66MjMXeTwduDWC4qw61WN9jnP0GI+ukl19HvTpyJrGHvfP/1L+oT4y9WZrWamiStsCMVMaIM6/LpQl6FInDY38whLMNxj1DFL/OSn8T7XvG6/vMl1+XNs2ykScsXDqMoeyPkK0W/2fqGtynmPyxEa9Xv9dPsswKmDmS0L/O7napg0ziPs2WHdAvseDsPyZhJ8DUIrkR8Jv44+vi/xfjb/uf8Kf/L/jBulbyUMU/P2L0YsAbZnmazGg/adBg+OQfJvuva1pBhoXOP31krIkjo/Q1cS4WljTGG6X5M2klfhHyQBDKmVPmaWGfWx26I2vHfTGT9xwIVEvToz3N5taEb5IVpUd4z9vpKhn5eHZzKW05BAhF87nXwsuuTXaaZ7EoTY/yNJfLsSZyOcYTsKx/MdG8qUep9Y+lvqIotAHZzrwJc8fMKJ5rT16F2fl+MTsrsREU1NmGqQb3y4ydg/xUOrk74zUzFfFdF5R/UrectrKHGuUeLn+pbjkeIr1+fd/VUHlWqmhdv/JYKgw=
*/