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

    plane_view_t y_plane = interleaved_view( y_width
                                           , y_height
                                           , (typename plane_view_t::value_type*) y_base // pixels
                                           , y_width                            // rowsize_in_bytes
                                           );

    plane_view_t v_plane = interleaved_view( y_width  / scaling_factors_t::ss_X
                                           , y_height / scaling_factors_t::ss_Y
                                           , (typename plane_view_t::value_type*) v_base // pixels
                                           , y_width                            // rowsize_in_bytes
                                           );

    plane_view_t u_plane = interleaved_view( y_width  / scaling_factors_t::ss_X
                                           , y_height / scaling_factors_t::ss_Y
                                           , (typename plane_view_t::value_type*) u_base // pixels
                                           , y_width                            // rowsize_in_bytes
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