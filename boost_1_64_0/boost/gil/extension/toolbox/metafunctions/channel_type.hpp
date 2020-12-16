//
// Copyright 2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_CHANNEL_TYPE_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_CHANNEL_TYPE_HPP

#include <boost/gil/extension/toolbox/dynamic_images.hpp>
#include <boost/gil/extension/toolbox/metafunctions/get_num_bits.hpp>
#include <boost/gil/extension/toolbox/metafunctions/is_homogeneous.hpp>

#include <boost/gil/bit_aligned_pixel_reference.hpp>
#include <boost/gil/channel.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <boost/utility/enable_if.hpp> // boost::lazy_enable_if

namespace boost{ namespace gil {

/// channel_type metafunction
/// \brief Generates the channel type for

template <typename B, typename C, typename L, bool M>
struct gen_chan_ref
{
    using type = packed_dynamic_channel_reference
        <
            B,
            mp11::mp_at_c<C, 0>::value,
            M
        >;
};

//! This implementation works for bit_algined_pixel_reference
//! with a homogeneous channel layout.
//! The result type will be a packed_dynamic_channel_reference, since the
//! offset info will be missing.

// bit_aligned_pixel_reference
template <typename B, typename C, typename L, bool M>
struct channel_type< bit_aligned_pixel_reference<B,C,L,M> >
    : lazy_enable_if< is_homogeneous< bit_aligned_pixel_reference< B, C, L, M > >
                    , gen_chan_ref< B, C, L, M >
                    > {};

template <typename B, typename C, typename L, bool M>
struct channel_type<const bit_aligned_pixel_reference<B,C,L,M> >
    : lazy_enable_if< is_homogeneous< bit_aligned_pixel_reference< B, C, L, M > >
                    , gen_chan_ref< B, C, L, M >
                    > {};

template <typename B, typename C, typename L>
struct gen_chan_ref_p
{
    using type = packed_dynamic_channel_reference
        <
            B,
            get_num_bits<mp11::mp_at_c<C, 0>>::value,
            true
        >;
};

// packed_pixel
template < typename BitField
         , typename ChannelRefs
         , typename Layout
         >
struct channel_type< packed_pixel< BitField
                                 , ChannelRefs
                                 , Layout
                                 >
                   > : lazy_enable_if< is_homogeneous< packed_pixel< BitField
                                                                   , ChannelRefs
                                                                   , Layout
                                                                   >
                                                     >
                                     , gen_chan_ref_p< BitField
                                                     , ChannelRefs
                                                     , Layout
                                                     >
                                     > {};

template <typename B, typename C, typename L>
struct channel_type< const packed_pixel< B, C, L > >
    : lazy_enable_if< is_homogeneous<packed_pixel< B, C, L > >
                    , gen_chan_ref_p< B, C, L >
                    >
{};

template<>
struct channel_type< any_image_pixel_t >
{
    using type = any_image_channel_t;
};

} // namespace gil
} // namespace boost

#endif

/* channel_type.hpp
6guxkwVN3BmOv1Tijz3Nk/JJ5L8T+atKe74b16Q+yMOUwqZiThyL0W6J5P/I0vwRZBrt0FPqz3tkv5ul+93tCKL9K0SkprktN5WFZKSDbukh2YYpft0lxaLKhccVYRsiLN5OCgzHUqAlSocsWzH2Y5XwX6b4O1r4nwH+nLFzHL5hlJCEIXaeV1hlOT8jZYXJsPaQ3rFoWXC3HYKAyQskIG77bS6HKKaaPwml6YbSAPgzgMaBqgZr8lzLkOYIwVIwxkFbIh4xvDUEus7wMxrp8eNzZNelrF2tTgWgFUuFHj4k3ZNAdTJX0dJvy3T/uvQ2G1Jx5GtJFvN6WKCj00M/oezBhQ+iGxDHtXAUPGy2vu4FYje4SUIZOeUwI1P9x1Xq9A9VkdOd1cpCtUS4nvafb5OWdVJyfNg2qcv5W1GXzttJCfsjrPO1O7ZCapbwXcF+Gg6Qh5csHQexnEt/AdZgDNmfNmpcn6+9BiJ57R0MFOuOv1Xsp0+7qoIrRNnokZPgaIgGoTrhlP7f7JQz4LMpOaWptOrRROQIeCsRVW33/YFKvASVvoHaKDgAAwgYB4BIW+FchBNZdmt+BPGh99QYa7F/zxDSJ4ZFidvHNU2yWFhTsqD8BZF1ADKBzwrDI7pylANOrbPBalJCVn+MO3eCViQ7Fb3dN0qNW2GTmY7Mg7W7Zs8DK20x/S7zLX7QI3eg+cdlqn6/g0D7j63oBQ8s1FDYrYtgQVMrlpq7JGUrtIq19ns05XymfJ8pY5EyzX88UAu/uDc8e9wp7mbc9u/D71iQ56bCfQi3GW4/3HA8OhzHrxO/9eBawLWHS4brCXc33KNwY+Fmw22GM0wD5wSlLA6uEdwVcJ3gkuHuhlsLtxxuONxYuC1wU+DegdsDdwjuLJxNT40nP4IKTVbhz/niqFMtGOasBgk3kOm3LPiSMaBGUUQ1YbxuHWwCi+Vt23evPqqnwkL1W+GxF7JueVEthfyeGcGIDYQv1eziRY8L9nE9lp7pqedPLjhntgjJ9zjjU/cjA+5GQKh+mxoRKk+UU1Qt8CPl9LupPZlQ/UFgs7YkYKJxRmqzI3gpGYiKEi+FZOC58vetZdQu8QfN1YkBMk4tzKX39+oMbc77oxbl0CEiXItYpnCzFAiWHFWyQEewtBVIrNh5X8CY0OeRZEzp1Jzrq2U35Aiqng6xjMDRMo7hti1FCE1U1P4OT3r+eKcs7jv0ehCk0nTu75vD9zZqn9x5i9qL/1y3liQtCoT2rPvcX/aWv7WjXPlZTssK7SLE1IJqxNsQ0WqguryxNdolZ20eIQrR4KLFH0l4OWG+gzTfDla+y0ol3/7IF9XjYR0PDFEBVDavWqAp6Y3nDT66VnNPcitn2JWKoICzOLdUSbuvbhMsjZ3lDenNx+O2FpLHKzRmt11WY1Lu7ACZBMGJinWmVMHt00E3M79u5ddrqu8N6+xlwk3NdVbFS7ONeDn4TNNtPGOm+muZIolQyvXrchRxUroUMZtFnCTo454EyHwilQ2OZJt8tVuuLW2seNR/zCh9NPqN9D8NP6Pm75RkN0j//yXnfMjXQVSdhsUVUhdFggRCIVtE9+TfWGZ27hfs1bmvA3sQGnyXiQgq5E8T0/2DLy6DenH501mi/xE3AFXCkTbKUsBR9rG8BuwQDV4NsfPhB6S8/k78noLbL5BDHgl3q2av6KK08UwOQae8tKK8tJV5aeuL0jZFMItmz6rmrgZjcQYp4Wb3PPozP8WJvJ46dl6Ud/3mnZ7qnzohBsxE6ZHFeEV4bISlXyNtlKreKAUgsEb4/+BjkYKfmx7hWOM11leMJbfs1hrrVPAF01S97sDTZMZz61d0YDC/nCM=
*/