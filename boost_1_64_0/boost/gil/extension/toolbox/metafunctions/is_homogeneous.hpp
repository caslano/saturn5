//
// Copyright 2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_IS_HOMOGENEOUS_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_IS_HOMOGENEOUS_HPP

#include <boost/gil/pixel.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <type_traits>

namespace boost{ namespace gil {

/// is_homogeneous metafunctions
/// \brief Determines if a pixel types are homogeneous.

template<typename C,typename CMP, int Next, int Last>
struct is_homogeneous_impl;

template<typename C, typename CMP, int Last>
struct is_homogeneous_impl<C, CMP, Last, Last> : std::true_type {};

template<typename C, typename CMP, int Next, int Last>
struct is_homogeneous_impl
    : mp11::mp_and
        <
            is_homogeneous_impl<C, CMP, Next + 1, Last>,
            std::is_same<CMP, mp11::mp_at_c<C, Next>>
        >
{};

template <typename P>
struct is_homogeneous : std::false_type {};

// pixel
template <typename C, typename L>
struct is_homogeneous<pixel<C, L>> : std::true_type {};

template <typename C, typename L >
struct is_homogeneous<pixel<C, L> const> : std::true_type {};

template <typename C, typename L>
struct is_homogeneous<pixel<C, L>&> : std::true_type {};

template <typename C, typename L>
struct is_homogeneous<pixel<C, L> const&> : std::true_type {};

// planar pixel reference
template <typename Channel, typename ColorSpace>
struct is_homogeneous<planar_pixel_reference<Channel, ColorSpace>> : std::true_type {};

template <typename Channel, typename ColorSpace>
struct is_homogeneous<planar_pixel_reference<Channel, ColorSpace> const> : std::true_type {};

template<typename C, typename CMP, int I, int Last>
struct is_homogeneous_impl_p {};

// for packed_pixel
template <typename B, typename C, typename L>
struct is_homogeneous<packed_pixel<B, C, L>>
    : is_homogeneous_impl_p
    <
        C,
        mp11::mp_at_c<C, 0>,
        1,
        mp11::mp_size<C>::value
    > {};

template< typename B
        , typename C
        , typename L
        >
struct is_homogeneous<packed_pixel<B, C, L> const>
    : is_homogeneous_impl_p
    <
        C,
        mp11::mp_at_c<C, 0>,
        1,
        mp11::mp_size<C>::value
    > {};

// for bit_aligned_pixel_reference
template <typename B, typename C, typename L, bool M>
struct is_homogeneous<bit_aligned_pixel_reference<B, C, L, M>>
    : is_homogeneous_impl<C, mp11::mp_at_c<C, 0>, 1, mp11::mp_size<C>::value>
{};

template <typename B, typename C, typename L, bool M>
struct is_homogeneous<const bit_aligned_pixel_reference<B, C, L, M> >
    : is_homogeneous_impl<C, mp11::mp_at_c<C, 0>, 1, mp11::mp_size<C>::value>
{};

}} // namespace boost::gil

#endif

/* is_homogeneous.hpp
tRpXKo/SKzqW0xL0wuWmDO1YyctswvjGr9z/uWIU4TtYn+SRX3EIXU57c+uxONRitFBRelLZmKkZfpRBaEPUvR+reF76Qq9ZfW3CfGvo+2J7yGlS22Tucmva/JYmG0B+Vkc0ui2x9JncdqmTMNeptc3KrwmTBfQDL3XkoiRsnP7SCmbaXqF7gmgoCv4Oo2nvMXlAg6h71uv59/TnLFao00H/efAYjOtvV/+SrhpeivBUf+cf3Iv3JYyo73H/nSebZVbiRggMtkLlHvrBkjWGP+Ir+7Lxj0SNdnSO1TahMbNSF96u73l+4OCDyVUsgDbYSlFwQoGm3Hw90LzIpu2DGCTP5ffpR2vufKr+6VN9Zxh3BxY/FneoZiXYuCOJzB12pH5mBqMW4zTxw/dWGWmF8Eu7jIlWwltRxtDypD/GfIFpQYyP9tKATXPsxedEDCVU5BNN72VfhrXvymEJ/an87dZ5aeeyikM8RYb4Zh3iTxinVIG9OUPruhQCZnJHYK4PzuHghi7OwVZ/TL1Oi+Nl/nzC8Lh/QMcU01ZmO55aL8WpFRF8pCbsByozBnNIno0W4StYF55p9EST3/wRRXaO0ywEZHxlGPM6bV7HaMguhvhRmPDmnaiHmYrrq2NZRfo1eCFu/0Q2zhpe3bXi8YTLSuvXc3vBo6ToFPAkAAiWtrHv5MG/yZrTxA+YWTjX7qXnS/Ta+gkGb5VLdNX3DqtsA5de2PZntO2Hmty/KYUpRoeiV1qeCMmhyPkh2b+8WH18LXJPWiB2MC9xT6KRPnkF8nU0z9hR8FL/EPxYNSPDhU4FWo+QGs1hdHbAb83URHMO5xN9DTcR34jXNFbSCS7xBxCIeeEmQHnzY/E55wv51JJFIitcYkhjLBGOW9GgiTzkCBJsZX7D9Z67J0KDNc0Gfql8vUflcfojrqIaInh1M/uX+9edSqOLX6JtmpPc5zmlyd6K33T/kTR/ia+Brqce0qqfDC+oh0GMnAHjbHyxRfw1bGnyJpGOD3/uL3zvZT3YViTGyt1kCcaRRJOX343mvYXWd7mm37Dlg/sDSagMyctvrfpP778FUn7OwaMcrhs+tXj4jak+V7xYJj5dRGV485q5HNTy5Yvh6f5jlfQraCSHwcBKalWHhW+WEuvPVaQP1pRhE/dOoypXFMI5B6OsqffdSrX/gHhmDBDg9NITHdJJbzL3aw5/WylsHuCsMgswVKEJuynKM6ZB16aX4Vd6Ki+5DrxuT2mwZqetRS4nPhoAnH9zWc7pq9wvbICfcsw/kWkiFTQSx+HuEQ7yyf8Dv8Inj+wOJUh2WcjOHEJGrEiyNErchoQqFemh8O80SSASSb5DkuBQ2v9TYALxuCw8Q5VCOFXxmDWz5XOsxvyMybd+jOTXADjIwrkCwEIAxQL7HAT+mJN8ZVNq4pLzbSo0B4ENrmHOOfDddk2uhZDsdgxojYBgFE0C5SSfuoTxKY5dR7F+AKwUrBlKxDwT+/XwVvWRHPxKK2AXpg6a53a4YXDj4RxR8ueMEPdv/iLL50u8xbW683v7jH1/A9XFSM7PnOSbWcZUTuazvr+QCtdctOObrN+UUdIPSFJpdhNOVkowUWroTtwQuXlJ54OBvkDFVjpBJ/T3yqk/vZwNq8IU/jdHz1S7eF15KT+DU4d/NaWY3L46lbT0pSS2zv5jXYB8bZAPmAjJzdANpvM2vkYetlk+vNiYA+NEH1+0kM07bp0E6xGPTHMvgIKatb9K4S/FY6U5IZer0UmxpTknnNnVJzfzhgo7bg1GFuyOEiJJqAg6+H7GtLosdSEt3HF8BvWoUPah3E9BR52BgODe9DYn0/PAXV+Ymde5pSwI//bouao=
*/