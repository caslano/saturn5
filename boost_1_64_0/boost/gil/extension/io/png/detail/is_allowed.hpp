//
// Copyright 2008 Christian Henning, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_PNG_DETAIL_IS_ALLOWED_HPP
#define BOOST_GIL_EXTENSION_IO_PNG_DETAIL_IS_ALLOWED_HPP

#include <boost/gil/extension/io/png/tags.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

template< typename View >
bool is_allowed( const image_read_info< png_tag >& info
               , std::true_type   // is read_and_no_convert
               )
{
    using pixel_t = typename get_pixel_type<View>::type;

    using channel_t = typename channel_traits<typename element_type<pixel_t>::type>::value_type;

    const png_num_channels::type dst_num_channels = num_channels< pixel_t >::value;
    const png_bitdepth::type     dst_bit_depth    = detail::unsigned_integral_num_bits< channel_t >::value;

    return   dst_num_channels == info._num_channels
          && dst_bit_depth    == info._bit_depth;
}

template< typename View >
bool is_allowed( const image_read_info< png_tag >& /* info */
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
i04TGCu23JC0GeAT3Z0Ebyx9DRmYzDyxWx5Efv0Gv/daD3wWYetuxZYAByv7MR5wnDWA01iv4jfthA5eQFb9hF/RQ6ReIn4NPladtchuZEMR4zSGXgaMFNk2BHn4JPSHfdbgQVNW0s9ns0R+Ysy/JnKnOvr7zJnI2hiesVfjgOMO7i1becCQ36GZGOTxD8B3yin4TeiIm5Cb979vbaqQSxG+LhwKftvjP1ei+1sbMuQT7ICdhpyGf1UJn266ir0hYNv+OlN234o//rxHboRPTXyHuHbY2n2xIa4xZRHrqLjIkIdLsBNegK6fY75XYE9ja43BbvkD2bD3cXzph8izcL4hXZC1ibfg11F3SxE+SRG8hZzokGbIGYx3eW9sFT9wnsEeMbphITyzBjoPAb+nL8fORY/1RXbcnQ/PXGDIcuAR2wa5xDzPOtqyS8DLQlOegqZPwH/IBBdfAoNxCezrrgPH3yHLX0ZuVhrS41TuAW1hySFDfr0defeLSc5IcIGeHDyWc0rTsdORhZdiE2YjO/PxWXqCn+aToK856Mm+rLktfudwkReSoNNY/PS66PrRfBUyinsLv4Ge8EfST0ROZGD/DIAP4KMzX6VtIu0y0UPEAWY9wLg3QwfjiS1kQCdboE98cYM1XbULv7QttvCd8Ox2+j0WmMKzQ/FZz7vKZI6mlEM3bQlDXOBFht0tkg89XL8YeDLm/fuxrzzcHXMUNkUrZAlr6LAbOEKvc8FR0VLw8z1+YgE0B8+2x14Ood8+uIG4xSXoYGSUx4+OuBgYLkPvQdMLDoC/TugW9ON660vQp7glCRj+wJzeAR7PfGNIMvGbiT8wx6/Qc0OA1dn0h4+8arwJzLCZk7ADWvH9ObLoHGhzLL5dm3uIEYwjnx9+UTo8XojNuBB4Fn+J3zUYX4m4w75F6Bl4aHoSdDYKn4A4ztXAJjsTexDe/fpk+p2D7MvHR0ZPfHAnz8Dtp4vQiZYv1Il7Xh6BnoHHGSNMeek84gmvkmfkEY9MR4Y2Rp7F/ArOfsR38QGrl8DPKvRkL/z/kZyrfYZ+c7GT0ojxXIQcvAZZDJ3290IvyOlv5sEjjD0Gn/M7y0aZCOwmoDubIGcGGPIsPlnZUvznTOTns8ir3025qC4xiV/Qa9DMPbPoL4140xfoOOzjlvWxjYNG2M8fDX0g65e9jT7Gp1oCLWy9D32E7t2PXZwRxHafgc6Gnx/n/YSN8BBwOocxy5Fl87KRtbPQbeC9HvQx7VJkFfZ47G3IwSRTzseWXfIVdJIGj8H/FcBuHfrb24xzH8iF204BbycBz6uBHbGJLUOJlWDfepAzR6G3p1yOb1bikbcuxpbF/nj4VI/sBxZ/OQa6TICH38P2fAEf+Ats6l884n9ZpDUxgZ5nQuOTGGc2uC4CBzOQx1+LtP0JfG5B1kxGj6MnN2Ff7QX/P+Ww5jHQN7wVbIRfiW8fC71Nx9cPjMNX/BpZPMKQ0ejfJ734TI2Z7xUi8VuIA3WBn1ciSz20Ww4OAtDQSt7Hd2v2NP4KdLcQufEhvvp5txK/gR8WY4udtB6ay4QPl0LPG0wpsGwq+O9H4CyM81sHj/xtALo9C5v3aYu+scsM5PNweB+cPDoaG60bMZAJ4AB7YtBQ6sHf7C+QHzexXvpaRkzsPXw0A1vljhngsh62FjLGhww4/V5iAFeYciLxhaLt0MlW1gI/NAfnHZOIZ+J3XfMjd9jA89cFieP0wce07kq9y5DPkFmr3kc/0L4bOPVi98w6m2c/MvNmYAO/fGLidxBLqMSGHH+3Ke+0xIZG7m08D3iAqy3Qf8uZ0N2vjN+YXIU9sB8Y4/PP4QPkdwI0VwSPLWANN7A=
*/