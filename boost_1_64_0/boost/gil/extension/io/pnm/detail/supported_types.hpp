//
// Copyright 2008 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_PNM_DETAIL_SUPPORTED_TYPES_HPP
#define BOOST_GIL_EXTENSION_IO_PNM_DETAIL_SUPPORTED_TYPES_HPP

#include <boost/gil/extension/io/pnm/tags.hpp>

#include <boost/gil/channel.hpp>
#include <boost/gil/color_base.hpp>
#include <boost/gil/io/base.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

// Read Support

template< pnm_image_type::type ASCII_Type
        , pnm_image_type::type Binary_Type
        >
struct pnm_rw_support_base
{
    static const pnm_image_type::type _asc_type = ASCII_Type;
    static const pnm_image_type::type _bin_type = Binary_Type;
};

template< typename Channel
        , typename ColorSpace
        >
struct pnm_read_support : read_support_false
                        , pnm_rw_support_base< 0
                                             , 0
                                             > {};

template< typename BitField, bool Mutable >
struct pnm_read_support< packed_dynamic_channel_reference< BitField
                                                         , 1
                                                         , Mutable
                                                         >
                       , gray_t
                       > : read_support_true
                         , pnm_rw_support_base< pnm_image_type::mono_asc_t::value
                                              , pnm_image_type::mono_bin_t::value
                                              > {};

template<>
struct pnm_read_support<uint8_t
                       , gray_t
                       > : read_support_true
                         , pnm_rw_support_base< pnm_image_type::gray_asc_t::value
                                              , pnm_image_type::gray_bin_t::value
                                              > {};


template<>
struct pnm_read_support<uint8_t
                       , rgb_t
                       > : read_support_true
                         , pnm_rw_support_base< pnm_image_type::color_asc_t::value
                                              , pnm_image_type::color_bin_t::value
                                              > {};

// Write support

template< typename Channel
        , typename ColorSpace
        >
struct pnm_write_support : write_support_false
{};

template< typename BitField, bool Mutable >
struct pnm_write_support< packed_dynamic_channel_reference< BitField
                                                          , 1
                                                          , Mutable
                                                          >
                        , gray_t
                        > : write_support_true
                          , pnm_rw_support_base< pnm_image_type::mono_asc_t::value
                                               , pnm_image_type::mono_bin_t::value
                                               > {};


template<>
struct pnm_write_support<uint8_t
                        , gray_t
                        > : write_support_true
                          , pnm_rw_support_base< pnm_image_type::gray_asc_t::value
                                               , pnm_image_type::gray_bin_t::value
                                               > {};


template<>
struct pnm_write_support<uint8_t
                        , rgb_t
                        > : write_support_true
                          , pnm_rw_support_base< pnm_image_type::color_asc_t::value
                                               , pnm_image_type::color_bin_t::value
                                               > {};

} // namespace detail

template<typename Pixel>
struct is_read_supported<Pixel, pnm_tag>
    : std::integral_constant
    <
        bool,
        detail::pnm_read_support
        <
            typename channel_type<Pixel>::type,
            typename color_space_type<Pixel>::type
        >::is_supported
    >
{
    using parent_t = detail::pnm_read_support
        <
            typename channel_type<Pixel>::type,
            typename color_space_type<Pixel>::type
        >;

    static const pnm_image_type::type _asc_type = parent_t::_asc_type;
    static const pnm_image_type::type _bin_type = parent_t::_bin_type;
};

template<typename Pixel>
struct is_write_supported<Pixel, pnm_tag>
    : std::integral_constant
    <
        bool,
        detail::pnm_write_support
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
A4vdZ8Z820QGmzIsksntYmC584jFHhhNmcjedAHzyAuYIwdgG233eS8lMvzO+D/g2n17T37SGtfwCImJskhOHxR5bGKRp0/B3D4Fc20dmMfWgbm2juTaOjCPrQNzbR2Ya+vAPLYOzLVrYK4NA/PYMDDXhoG5NgzMY8PAXBsG5tomMI9tAnNtE5grV2CuXBls7gDlymNfODvV12RiVI5/8ZrjG5q7R6ijUVFx5arY1O838MxAP3gQzJU1MI+sgbmyZrFn4OsgvwqV3/MO5spksUcmiz0yWeyRyWKPTBZ7ZLLYI5Ngrkxa7CVdZ3dOVtgbhu8Eg7nyXOzO0wp721PGex7sAw/2oZHxI8ozWHxMhB2psFFjovFdo54tNNiFCisDuxesSWFLDPZJhR1mMN2Ozxnsiwo72ZTxNYO5+lvs0d9iV38V9s0xUR+sU/mdabCjDObor8XO9vB9x2CzFPYjU+d9FXaN4TvGYI49AHPtgeIz+U0QMNdG6GdN/1l50XbD8M0aoN1oXdnQ2xmcn+/s6/bbirE7aFsxIXtOIsNwPmrjgPgR0ed1o3c3Juby9XX6OD3z+BSPXZnisStgrl2x2K30UZz13MkC5rEhUzw2BMy1IWCuDQHz2BAw14aAuTYEzGNDwFw7YLGfe9pxp4O58x+Yqz9grv6AefQHzJ3rLHaPU66rP2CuvIO58g7myrbiuxTsk5RRoMq4T5fryrt5tnaA8m73cMwfwY3QvIvNNkhbV/rjoX492DdLD9LyfT91S+pMopt/l6fzMj66nzd8Qy3DOqtf3eqnwqZPHiT/Q+inz5FHiUevSjx6BebqlcUeNfND08wM9viYaByfjoF59K/Es64Gc9fVFvutKeMxVcYzBhs+C8yju2Cu7oK5ugvm0V0wV3fBXN0F8+gumKu7FnvB1PkEU2dHny32iuE72PC5ulvi0V0wV3fBXN0F8/iuYK4+W+yPpi5LJ4J51uQlnjU5mKv3FnvT5DdC9ct6gxUo7B2D1ZhyXZtR4rEZYO56Hsy1I2Ce9TyYG5sEc+0I2EbMm329be0sxtK/nrV8p3fe/FNoAwLVXs6JdZSaGyeC20fD7aD8fK2defg+tHw9XUStLYt52xobFt/hytH0FynaxCG6FrzOsRqayeNj8gjf2OwO44qBSbHz9yZjRdpS5MobfoElal8XvQyWbOsIr8FqTGXuQ94C3qresii6V9/alPUdorHWpjU283FkKmG6M7qTf3IOn13GNC6nPdoSNtP+/PzmnvHsB/rjD/6OYv8mWkK9B8hvoib6Hclcfu49aQ3sdPjJJZqifCOXFx/JaWfxQHl7+JOJQZ8v+USmLprTfE+hP54uXhtvo5XB+8cpSddhW8Wb4uvcndzaFLLwqA3qBnKh4siDM8/0tOJmppxxt3ejWD63Xb2SXp9uD4+pmpW54WCN4ee2ef0upKDXWbQQzJn3pnrmPTB3PgNz51EwT/wIzLVFYK6NAduImGHaxrSs6ww/uEy3ePYKvraDjRkpvSiw/Rm+/qOy0Hfm57ZtmsdHAHP7CsztKzDPPA/mzvNg7jwP5pnnwdx5Hsyd58E88zyYO8+DufM8mGeeB3PneTB3ngfzzPNg7jwP5s7zYJ55Hsyd58HceR7MnedVuaMZ92/gAx5gMHdvDMz1B8DcuR/M4wOCuf4AmOsPgKm9tnupyyMJMM9e2zTP3A/mxt7BXH8AzOMPgLk6aLEdx0Z1+bGSq10Mdp3BnD0+i00wfIfa/JROG2zORuq0+WUGSa3q7er2+A8/0/6DjaPvMdbM9zzJedIVwe1qhIKtPZxo9N44DsFOnN1fm2Rp5moabjhdw7zPTwfehbXFJ3jXH3A=
*/