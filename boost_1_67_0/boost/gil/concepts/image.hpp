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