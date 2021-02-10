//
// Copyright 2007-2008 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_JPEG_DETAIL_SUPPORTED_TYPES_HPP
#define BOOST_GIL_EXTENSION_IO_JPEG_DETAIL_SUPPORTED_TYPES_HPP

#include <boost/gil/extension/io/jpeg/tags.hpp>

#include <boost/gil/channel.hpp>
#include <boost/gil/color_base.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

// Read support

template< jpeg_color_space::type ColorSpace >
struct jpeg_rw_support_base
{
    static const jpeg_color_space::type _color_space = ColorSpace;
};

template< typename Channel
        , typename ColorSpace
        >
struct jpeg_read_support : read_support_false
                         , jpeg_rw_support_base< JCS_UNKNOWN > {};

template<>
struct jpeg_read_support<uint8_t
                        , rgb_t
                        > : read_support_true
                          , jpeg_rw_support_base< JCS_RGB > {};

template<>
struct jpeg_read_support<uint8_t
                        , cmyk_t
                        > : read_support_true
                          , jpeg_rw_support_base< JCS_CMYK > {};

template<>
struct jpeg_read_support<uint8_t
                        , gray_t
                        > : read_support_true
                          , jpeg_rw_support_base< JCS_GRAYSCALE > {};

// Write support

template< typename Channel
        , typename ColorSpace
        >
struct jpeg_write_support : write_support_false
                          , jpeg_rw_support_base< JCS_UNKNOWN > {};

template<>
struct jpeg_write_support<uint8_t
                         , gray_t
                         > : write_support_true
                          , jpeg_rw_support_base< JCS_GRAYSCALE > {};

template<>
struct jpeg_write_support<uint8_t
                         , rgb_t
                         > : write_support_true
                          , jpeg_rw_support_base< JCS_RGB > {};

template<>
struct jpeg_write_support<uint8_t
                         , cmyk_t
                         > : write_support_true
                          , jpeg_rw_support_base< JCS_CMYK > {};

} // namespace detail

template<typename Pixel>
struct is_read_supported<Pixel, jpeg_tag>
    : std::integral_constant
    <
        bool,
        detail::jpeg_read_support
        <
            typename channel_type<Pixel>::type,
            typename color_space_type<Pixel>::type
        >::is_supported
    >
{
    using parent_t = detail::jpeg_read_support
        <
            typename channel_type<Pixel>::type,
            typename color_space_type<Pixel>::type
        >;

    static const typename jpeg_color_space::type _color_space = parent_t::_color_space;
};

template<typename Pixel>
struct is_write_supported<Pixel, jpeg_tag>
    : std::integral_constant
    <
        bool,
        detail::jpeg_write_support
        <
            typename channel_type<Pixel>::type,
            typename color_space_type<Pixel>::type
        >::is_supported
    >
{};

} // namespace gil
} // namespace boost

#endif

/* supported_types.hpp
aYFg06OAlzCmRvqgFtd0X5RPiVFTvhUomYDkCCkSs701BtIcb+/+hHH9tgcEti1LST/RW0EcnJUHpkzQLU13hW9yUj7kLuNaV7JBUhjIc28S4eXI4iODZtSl1oT8ZLbAujElNf3Y4IRA25uZ2PNrTYLquUXbMH2LmTz1N2e7kyRvew0u4RLeL9BlTMe9oZ4hXX1WBWMtkA1ssVzNrZYVlQhhj+mWonVczeWJ1WDw9rDvpfX8kg8aByIUD2jWH5gUgwnPaG4t7pJTg5hilkM0vwC73ezV72qYwEB+tf7a2SJGkrimRev2JdGcTSeZ8yR9Dx35jAxLQz7YlG5WT323PZqGVCA46ySAZDwvKb1RmH6GMow54gyDJh6BD9QD6xwscX0BMEFxUdbZVtG8awBpH3+ZrK1c/CFIYaNHLjC+FON8kcamQMkQf6GyCzpzGj7p4os7g96wPxjFSG70Y/SyFTy8OMbDb8KH/37RPaKnr0QGgYFWZF2jAZDc2tzMTQ5VmtWecANt8tgm073LWw1zC6mm13sHv7uUv+ul8DCVRqwns1IthuVBObI4RZKjcI0YLYF9xAbY9BzCMOlTYy5xwJFtKzwDdpB+gk2bU5h7ltaqxKdcDiefU3befvRH0pV64I3BYueRrMF1HQe7
*/