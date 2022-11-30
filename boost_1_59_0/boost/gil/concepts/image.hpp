//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_CONCEPTS_IMAGE_HPP
#define BOOST_GIL_CONCEPTS_IMAGE_HPP

#include <boost/gil/concepts/basic.hpp>
#include <boost/gil/concepts/concept_check.hpp>
#include <boost/gil/concepts/fwd.hpp>
#include <boost/gil/concepts/image_view.hpp>
#include <boost/gil/concepts/point.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <type_traits>

#if defined(BOOST_CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic ignored "-Wunused-local-typedefs"
#endif

#if defined(BOOST_GCC) && (BOOST_GCC >= 40900)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#endif

namespace boost { namespace gil {

/// \ingroup ImageConcept
/// \brief N-dimensional container of values
///
/// \code
/// concept RandomAccessNDImageConcept<typename Image> : Regular<Image>
/// {
///     typename view_t; where MutableRandomAccessNDImageViewConcept<view_t>;
///     typename const_view_t = view_t::const_t;
///     typename point_t      = view_t::point_t;
///     typename value_type   = view_t::value_type;
///     typename allocator_type;
///
///     Image::Image(point_t dims, std::size_t alignment=1);
///     Image::Image(point_t dims, value_type fill_value, std::size_t alignment);
///
///     void Image::recreate(point_t new_dims, std::size_t alignment=1);
///     void Image::recreate(point_t new_dims, value_type fill_value, std::size_t alignment);
///
///     const point_t&        Image::dimensions() const;
///     const const_view_t&   const_view(const Image&);
///     const view_t&         view(Image&);
/// };
/// \endcode
template <typename Image>
struct RandomAccessNDImageConcept
{
    void constraints()
    {
        gil_function_requires<Regular<Image>>();

        using view_t = typename Image::view_t;
        gil_function_requires<MutableRandomAccessNDImageViewConcept<view_t>>();

        using const_view_t = typename Image::const_view_t;
        using pixel_t = typename Image::value_type;
        using point_t = typename Image::point_t;
        gil_function_requires<PointNDConcept<point_t>>();

        const_view_t cv = const_view(image);
        ignore_unused_variable_warning(cv);
        view_t v = view(image);
        ignore_unused_variable_warning(v);

        pixel_t fill_value;
        point_t pt = image.dimensions();
        Image image1(pt);
        Image image2(pt, 1);
        Image image3(pt, fill_value, 1);
        image.recreate(pt);
        image.recreate(pt, 1);
        image.recreate(pt, fill_value, 1);
    }
    Image image;
};


/// \ingroup ImageConcept
/// \brief 2-dimensional container of values
///
/// \code
/// concept RandomAccess2DImageConcept<RandomAccessNDImageConcept Image>
/// {
///     typename x_coord_t = const_view_t::x_coord_t;
///     typename y_coord_t = const_view_t::y_coord_t;
///
///     Image::Image(x_coord_t width, y_coord_t height, std::size_t alignment=1);
///     Image::Image(x_coord_t width, y_coord_t height, value_type fill_value, std::size_t alignment);
///
///     x_coord_t Image::width() const;
///     y_coord_t Image::height() const;
///
///     void Image::recreate(x_coord_t width, y_coord_t height, std::size_t alignment=1);
///     void Image::recreate(x_coord_t width, y_coord_t height, value_type fill_value, std::size_t alignment);
/// };
/// \endcode
template <typename Image>
struct RandomAccess2DImageConcept
{
    void constraints()
    {
        gil_function_requires<RandomAccessNDImageConcept<Image>>();
        using x_coord_t = typename Image::x_coord_t;
        using y_coord_t = typename Image::y_coord_t;
        using value_t = typename Image::value_type;

        gil_function_requires<MutableRandomAccess2DImageViewConcept<typename Image::view_t>>();

        x_coord_t w=image.width();
        y_coord_t h=image.height();
        value_t fill_value;
        Image im1(w,h);
        Image im2(w,h,1);
        Image im3(w,h,fill_value,1);
        image.recreate(w,h);
        image.recreate(w,h,1);
        image.recreate(w,h,fill_value,1);
    }
    Image image;
};

/// \ingroup ImageConcept
/// \brief 2-dimensional image whose value type models PixelValueConcept
///
/// \code
/// concept ImageConcept<RandomAccess2DImageConcept Image>
/// {
///     where MutableImageViewConcept<view_t>;
///     typename coord_t  = view_t::coord_t;
/// };
/// \endcode
template <typename Image>
struct ImageConcept
{
    void constraints()
    {
        gil_function_requires<RandomAccess2DImageConcept<Image>>();
        gil_function_requires<MutableImageViewConcept<typename Image::view_t>>();
        using coord_t = typename Image::coord_t;
        static_assert(num_channels<Image>::value == mp11::mp_size<typename color_space_type<Image>::type>::value, "");

        static_assert(std::is_same<coord_t, typename Image::x_coord_t>::value, "");
        static_assert(std::is_same<coord_t, typename Image::y_coord_t>::value, "");
    }
    Image image;
};

}} // namespace boost::gil

#if defined(BOOST_CLANG)
#pragma clang diagnostic pop
#endif

#if defined(BOOST_GCC) && (BOOST_GCC >= 40900)
#pragma GCC diagnostic pop
#endif

#endif

/* image.hpp
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
*/