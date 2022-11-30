//
// Copyright 2013 Christian Henning and Juan V. Puertos
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_IMAGE_TYPES_SUBCHROMA_IMAGE_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_IMAGE_TYPES_SUBCHROMA_IMAGE_HPP

#include <boost/gil/dynamic_step.hpp>
#include <boost/gil/image.hpp>
#include <boost/gil/image_view.hpp>
#include <boost/gil/point.hpp>
#include <boost/gil/virtual_locator.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <cstddef>
#include <memory>
#include <type_traits>

namespace boost { namespace gil {

namespace detail {

template< int J, int A, int B>
struct scaling_factors
{
    static_assert(std::integral_constant<int, J>::value == 4, "");

    static_assert(
        std::integral_constant<int, A>::value == 4 ||
        std::integral_constant<int, A>::value == 2 ||
        std::integral_constant<int, A>::value == 1,
        "");

    static_assert(
        std::integral_constant<int, B>::value == 4 ||
        std::integral_constant<int, B>::value == 2 ||
        std::integral_constant<int, B>::value == 1 ||
        std::integral_constant<int, B>::value == 0,
        "");

    static constexpr int ss_X =
        std::integral_constant<int, J>::value / std::integral_constant<int, A>::value;

    static constexpr int ss_Y =
        mp11::mp_if_c
        <
            std::integral_constant<int, B>::value == 0,
            std::integral_constant<int, 2>,
            mp11::mp_if_c
            <
                std::integral_constant<int, A>::value == std::integral_constant<int, B>::value,
                std::integral_constant<int, 1>,
                std::integral_constant<int, 4>
            >
        >::value;
};

} // namespace detail

////////////////////////////////////////////////////////////////////////////////////////
/// \class subchroma_image_deref_fn
/// \ingroup PixelLocatorModel PixelBasedModel
/// \brief Used for virtual_2D_locator
///
////////////////////////////////////////////////////////////////////////////////////////
template< typename Locator
        , typename Factors
        >
struct subchroma_image_deref_fn
{
    using plane_locator_t = gray8_view_t::locator;

    using const_t = subchroma_image_deref_fn<Locator, Factors>;
    using value_type = typename Locator::value_type;
    using reference = value_type;
    using const_reference = value_type;
    using argument_type = point_t;
    using result_type = reference;

    static const bool is_mutable = false;

    /// default constructor
    subchroma_image_deref_fn() {}

    /// constructor
    subchroma_image_deref_fn( const plane_locator_t& y_locator
                            , const plane_locator_t& v_locator
                            , const plane_locator_t& u_locator
                             )
    : _y_locator( y_locator )
    , _v_locator( v_locator )
    , _u_locator( u_locator )
    {}

    /// operator()
    result_type operator()( const point_t& p ) const
    {
        using scaling_factors_t = detail::scaling_factors
            <
                mp11::mp_at_c<Factors, 0>::value,
                mp11::mp_at_c<Factors, 1>::value,
                mp11::mp_at_c<Factors, 2>::value
            >;

        plane_locator_t y = _y_locator.xy_at( p );
        plane_locator_t v = _v_locator.xy_at( p.x / scaling_factors_t::ss_X, p.y / scaling_factors_t::ss_X );
        plane_locator_t u = _u_locator.xy_at( p.x / scaling_factors_t::ss_X, p.y / scaling_factors_t::ss_X );

        return value_type( at_c< 0 >( *y )
                         , at_c< 0 >( *v )
                         , at_c< 0 >( *u )
                         );
    }

    ///
    const plane_locator_t& y_locator() const { return _y_locator; }
    const plane_locator_t& v_locator() const { return _v_locator; }
    const plane_locator_t& u_locator() const { return _u_locator; }

private:

    plane_locator_t _y_locator;
    plane_locator_t _v_locator;
    plane_locator_t _u_locator;
};


////////////////////////////////////////////////////////////////////////////////////////
/// \class subchroma_image_locator_type
/// \ingroup PixelLocatorModel PixelBasedModel
/// \brief
///
////////////////////////////////////////////////////////////////////////////////////////
template< typename Locator
        , typename Factors
        >
struct subchroma_image_locator
{
    using type = virtual_2d_locator
        <
            subchroma_image_deref_fn<Locator, Factors>, // Deref
            false // IsTransposed
        >;
};

/////////////////////////////
//  PixelBasedConcept
/////////////////////////////

template < typename Locator, typename Factors >
struct channel_type< subchroma_image_locator< Locator, Factors > >
    : public channel_type< typename subchroma_image_locator< Locator, Factors >::type > {};

template < typename Locator, typename Factors >
struct color_space_type< subchroma_image_locator< Locator, Factors > >
    : public color_space_type< typename subchroma_image_locator< Locator, Factors >::type > {};

template < typename Locator, typename Factors >
struct channel_mapping_type< subchroma_image_locator< Locator, Factors > >
    : public channel_mapping_type< typename subchroma_image_locator< Locator, Factors >::type > {};

template < typename Locator, typename Factors >
struct is_planar< subchroma_image_locator< Locator, Factors > >
    : public is_planar< typename subchroma_image_locator< Locator, Factors >::type > {};

/////////////////////////////
//  HasDynamicXStepTypeConcept
/////////////////////////////

template < typename Locator, typename Factors >
struct dynamic_x_step_type< subchroma_image_locator< Locator, Factors > >
{
    using type = typename subchroma_image_locator<Locator, Factors>::type;
};

/////////////////////////////
//  HasDynamicYStepTypeConcept
/////////////////////////////

template < typename Locator, typename Factors >
struct dynamic_y_step_type< subchroma_image_locator< Locator, Factors > >
{
    using type = typename subchroma_image_locator<Locator, Factors>::type;
};

/////////////////////////////
//  HasTransposedTypeConcept
/////////////////////////////

template < typename Locator, typename Factors >
struct transposed_type< subchroma_image_locator< Locator, Factors > >
{
    using type = typename subchroma_image_locator<Locator, Factors>::type;
};

//////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
/// \class subchroma_image_view
/// \ingroup ImageViewModel PixelBasedModel
/// \brief A lightweight object that interprets a subchroma image.
///
////////////////////////////////////////////////////////////////////////////////////////
template
<
    typename Locator,
    typename Factors = mp11::mp_list_c<int, 4, 4, 4>
>
class subchroma_image_view : public image_view<Locator>
{
public:

    using locator = Locator;
    using deref_fn_t = typename locator::deref_fn_t;
    using plane_locator_t = typename deref_fn_t::plane_locator_t;


    using const_t = subchroma_image_view<Locator, Factors>;

    using plane_view_t = image_view<plane_locator_t>;

    /// default constructor
    subchroma_image_view()
    : image_view< Locator >()
    {}

    /// constructor
    subchroma_image_view( const point_t& y_dimensions
                        , const point_t& v_dimensions
                        , const point_t& u_dimensions
                        , const Locator& locator
                        )
    : image_view< Locator >( y_dimensions, locator )
    , _y_dimensions( y_dimensions )
    , _v_dimensions( v_dimensions )
    , _u_dimensions( u_dimensions )
    {}

    /// copy constructor
    template< typename Subchroma_View >
    subchroma_image_view( const Subchroma_View& v )
    : image_view< locator >( v )
    {}

    const point_t& v_ssfactors() const { return point_t( get_deref_fn().vx_ssfactor(), get_deref_fn().vx_ssfactor() ); }
    const point_t& u_ssfactors() const { return point_t( get_deref_fn().ux_ssfactor(), get_deref_fn().ux_ssfactor() ); }

    const point_t& y_dimension() const { return _y_dimensions; }
    const point_t& v_dimension() const { return _v_dimensions; }
    const point_t& u_dimension() const { return _u_dimensions; }

    const plane_locator_t& y_plane() const { return get_deref_fn().y_locator(); }
    const plane_locator_t& v_plane() const { return get_deref_fn().v_locator(); }
    const plane_locator_t& u_plane() const { return get_deref_fn().u_locator(); }

    const plane_view_t y_plane_view() const { return plane_view_t( _y_dimensions, y_plane() ); }
    const plane_view_t v_plane_view() const { return plane_view_t( _v_dimensions, v_plane() ); }
    const plane_view_t u_plane_view() const { return plane_view_t( _u_dimensions, u_plane() ); }


private:

    const deref_fn_t& get_deref_fn() const { return this->pixels().deref_fn(); }

private:

    point_t _y_dimensions;
    point_t _v_dimensions;
    point_t _u_dimensions;
};


/////////////////////////////
//  PixelBasedConcept
/////////////////////////////

template < typename Locator, typename Factors >
struct channel_type< subchroma_image_view< Locator, Factors > >
    : public channel_type< Locator > {};

template < typename Locator, typename Factors >
struct color_space_type< subchroma_image_view< Locator, Factors > >
    : public color_space_type< Locator > {};

template < typename Locator, typename Factors >
struct channel_mapping_type< subchroma_image_view< Locator, Factors > >
     : public channel_mapping_type< Locator > {};

template < typename Locator, typename Factors >
struct is_planar< subchroma_image_view< Locator, Factors > >
    : public is_planar< Locator > {};

/////////////////////////////
//  HasDynamicXStepTypeConcept
/////////////////////////////

template < typename Locator, typename Factors >
struct dynamic_x_step_type< subchroma_image_view< Locator, Factors > >
{
    using type = image_view<typename dynamic_x_step_type<Locator>::type>;
};

/////////////////////////////
//  HasDynamicYStepTypeConcept
/////////////////////////////

template < typename Locator, typename Factors >
struct dynamic_y_step_type< subchroma_image_view< Locator, Factors > >
{
    using type = image_view<typename dynamic_y_step_type<Locator>::type>;
};

/////////////////////////////
//  HasTransposedTypeConcept
/////////////////////////////

template < typename Locator, typename Factors >
struct transposed_type< subchroma_image_view< Locator, Factors > >
{
    using type = image_view<typename transposed_type<Locator>::type>;
};

////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup ImageModel PixelBasedModel
/// \brief container interface over image view. Models ImageConcept, PixelBasedConcept
///
/// A subchroma image holds a bunch of planes which don't need to have the same resolution.
///
////////////////////////////////////////////////////////////////////////////////////////
template
<
    typename Pixel,
    typename Factors = mp11::mp_list_c<int, 4, 4, 4>,
    typename Allocator = std::allocator<unsigned char>
>
class subchroma_image : public detail::scaling_factors
    <
        mp11::mp_at_c<Factors, 0>::value,
        mp11::mp_at_c<Factors, 1>::value,
        mp11::mp_at_c<Factors, 2>::value
    >
{

private:
    using parent_t = detail::scaling_factors
        <
            mp11::mp_at_c<Factors, 0>::value,
            mp11::mp_at_c<Factors, 1>::value,
            mp11::mp_at_c<Factors, 2>::value
        >;

public:

    using channel_t = typename channel_type<Pixel>::type;
    using pixel_t = pixel<channel_t, gray_layout_t>;

    using plane_image_t = image<pixel_t, false, Allocator>;

    using plane_view_t = typename plane_image_t::view_t;
    using plane_const_view_t = typename plane_image_t::const_view_t;
    using plane_locator_t = typename plane_view_t::locator;

    using pixel_view_t = typename view_type_from_pixel<Pixel>::type;
    using pixel_locator_t = typename pixel_view_t::locator;

    using locator_t = typename subchroma_image_locator
        <
            pixel_locator_t,
            Factors
        >::type;

    using x_coord_t = typename plane_image_t::coord_t;
    using y_coord_t = typename plane_image_t::coord_t;

    using view_t = subchroma_image_view<locator_t, Factors>;
    using const_view_t = typename view_t::const_t;


    /// constructor
    subchroma_image( const x_coord_t y_width
                   , const y_coord_t y_height
                   )
    : _y_plane(        y_width,        y_height, 0, Allocator() )
    , _v_plane( y_width / parent_t::ss_X, y_height / parent_t::ss_Y, 0, Allocator() )
    , _u_plane( y_width / parent_t::ss_X, y_height / parent_t::ss_Y, 0, Allocator() )
    {
        init();
    }

public:

    view_t _view;

private:

    void init()
    {
        using defer_fn_t = subchroma_image_deref_fn<pixel_locator_t, Factors>;

        defer_fn_t deref_fn( view( _y_plane ).xy_at( 0, 0 )
                           , view( _v_plane ).xy_at( 0, 0 )
                           , view( _u_plane ).xy_at( 0, 0 )
                           );

        // init a virtual_2d_locator
        locator_t locator( point_t( 0, 0 ) // p
                         , point_t( 1, 1 ) // step
                         , deref_fn
                         );

        _view = view_t( _y_plane.dimensions()
                      , _v_plane.dimensions()
                      , _u_plane.dimensions()
                      , locator
                      );
    }


private:

    plane_image_t _y_plane;
    plane_image_t _v_plane;
    plane_image_t _u_plane;
};


/////////////////////////////
//  PixelBasedConcept
/////////////////////////////

template < typename Pixel, typename Factors, typename Alloc >
struct channel_type< subchroma_image< Pixel, Factors, Alloc > >
    : channel_type< Pixel > {};

template < typename Pixel, typename Factors, typename Alloc >
struct color_space_type< subchroma_image< Pixel, Factors, Alloc > >
    : color_space_type< Pixel > {};

template < typename Pixel, typename Factors, typename Alloc >
struct channel_mapping_type<  subchroma_image< Pixel, Factors, Alloc > >
    : channel_mapping_type< Pixel > {};

template < typename Pixel, typename Factors, typename Alloc >
struct is_planar< subchroma_image< Pixel, Factors, Alloc > >
    : std::integral_constant<bool, false>
{};


/////////////////////////////////////////////////////////////////////////////////////////
/// \name view, const_view
/// \brief Get an image view from an subchroma_image
/// \ingroup ImageModel
/// \brief Returns the non-constant-pixel view of an image
/////////////////////////////////////////////////////////////////////////////////////////
template< typename Pixel
        , typename Factors
        >
inline
const typename subchroma_image< Pixel, Factors >::view_t& view( subchroma_image< Pixel, Factors >& img )
{
    return img._view;
}

template< typename Pixel
        , typename Factors
        >
inline
const typename subchroma_image< Pixel, Factors >::const_view_t const_view( subchroma_image< Pixel, Factors >& img )
{
    return static_cast< const typename subchroma_image< Pixel, Factors >::const_view_t>( img._view );
}

/////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup ImageViewSTLAlgorithmsFillPixels
/// \brief std::fill for subchroma_image views
/////////////////////////////////////////////////////////////////////////////////////////
template< typename Locator
        , typename Factors
        , typename Pixel
        >
void fill_pixels( const subchroma_image_view< Locator, Factors >& view
                , const Pixel&                                    value
                )
{
    using channel_t = typename subchroma_image
        <
            Pixel,
            Factors
        >::plane_view_t::value_type;

    fill_pixels( view.y_plane_view(), channel_t( at_c< 0 >( value )));
    fill_pixels( view.v_plane_view(), channel_t( at_c< 1 >( value )));
    fill_pixels( view.u_plane_view(), channel_t( at_c< 2 >( value )));
}

/////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup ImageViewConstructors
/// \brief Creates a subchroma view from a raw memory
/////////////////////////////////////////////////////////////////////////////////////////
template< typename Pixel
        , typename Factors
        >
typename subchroma_image< Pixel
                        , Factors
                        >::view_t subchroma_view( std::size_t    y_width
                                                , std::size_t    y_height
                                                , unsigned char* y_base
                                                )
{
    using scaling_factors_t = detail::scaling_factors
        <
            mp11::mp_at_c<Factors, 0>::type::value,
            mp11::mp_at_c<Factors, 1>::type::value,
            mp11::mp_at_c<Factors, 2>::type::value
        >;

    std::size_t y_channel_size = 1;
    std::size_t u_channel_size = 1;

    unsigned char* u_base = y_base + ( y_width  * y_height * y_channel_size );
    unsigned char* v_base = u_base + ( y_width  / scaling_factors_t::ss_X )
                                   * u_channel_size;

    using plane_view_t = typename subchroma_image<Pixel, Factors>::plane_view_t;
    using plane_value_t = typename plane_view_t::value_type;

    plane_view_t y_plane = interleaved_view( y_width
                                           , y_height
                                           , (plane_value_t*) y_base // pixels
                                           , y_width                 // rowsize_in_bytes
                                           );

    plane_view_t v_plane = interleaved_view( y_width  / scaling_factors_t::ss_X
                                           , y_height / scaling_factors_t::ss_Y
                                           , (plane_value_t*) v_base // pixels
                                           , y_width                 // rowsize_in_bytes
                                           );

    plane_view_t u_plane = interleaved_view( y_width  / scaling_factors_t::ss_X
                                           , y_height / scaling_factors_t::ss_Y
                                           , (plane_value_t*) u_base // pixels
                                           , y_width                 // rowsize_in_bytes
                                           );

    using defer_fn_t = subchroma_image_deref_fn
        <
            typename subchroma_image<Pixel, Factors>::pixel_locator_t,
            Factors
        >;

    defer_fn_t deref_fn( y_plane.xy_at( 0, 0 )
                       , v_plane.xy_at( 0, 0 )
                       , u_plane.xy_at( 0, 0 )
                       );


    using locator_t = typename subchroma_image<Pixel, Factors>::locator_t;

    locator_t locator( point_t( 0, 0 ) // p
                     , point_t( 1, 1 ) // step
                     , deref_fn
                     );

    using view_t = typename subchroma_image<Pixel, Factors>::view_t;

    return view_t( point_t(                           y_width,                           y_height )
                 , point_t( y_width / scaling_factors_t::ss_X, y_height / scaling_factors_t::ss_Y )
                 , point_t( y_width / scaling_factors_t::ss_X, y_height / scaling_factors_t::ss_Y )
                 , locator
                 );
}

} // namespace gil
} // namespace boost

#endif

/* subchroma_image.hpp
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
*/