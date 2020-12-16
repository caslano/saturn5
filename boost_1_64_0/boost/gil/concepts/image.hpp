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
/4i5Otfk9FnRWafV+P7S85304kd/t9Orv7/sfCe9/O6kV+ukrzo/Mm6UucSixxLYSfz5J6Pzq94o1o3Df3SiEzJeff6/VR6+7eB5/l5EtnuHtolcDRmZbB77F/lkWuuFb8Y3p8WpgRDhNb+/kNqeS1OHVDoh1cGAyjcxzke5PNATDZfrlvD9ik+6HL7IrHsDfrZq7o0tiru7Ofk+l166eyP+wsGIdR1hHD9a1CQO9CAnDvjNtuJwyW4c9N0/ukTGwXzyna/NSylXEigN4x3E8f0f+PaQ8qbKV4g3jk8pzOrH9+b5nAdG92PaG3cL/SNVrau5JDBI5KrDmFEPJlGVdRHXYtTPRk/Mc7yfrdt8TfcF+uXl96Dv0L+O/j5t82vL+J197dK1Tt/k9+i++aC1Tt/kd9k3JV+mX/Jl+iVfpt/mu+mnb2jRN9kn5bQq78xd1sBl59MnkqhftPtjvPHi5U1z7Nfj8357buYYf4K4My+jC3P9IDnRcxnlHRFcZ/7inHFMcJw5a8qkuxhw6pUxPeernGOdQl0mwKH9YN9V27GhIOi9Bv12uebu8Ll6qe17py9P4SisvyiTesGjAh7zR2JlYn91anJCLfSk3GGXj7Pgqvy1pWLC8MZ8Hqpsb7WOtGqWuNuleRM+D9oObHXTtjDqi9Pg6LWoqeyqCX+lxEpQ7zDy+hT8uO2h3LQ9EHfbg+e2h3Lz9jDttofyAtpDOaI9mPbt/Um1b10m0D/4Rrb/3c4u96J9fTdPA2tlGOO5aT+/1uscX7+dVLNhqRbsJgRH29Uip9RX6svEsTwK+9msLmPTz0zbqUXqwHYlKv+fDzX5OePHzzbpN8a4Di/aJxKF+3IH4/HBREYt1PI6fDxI/8PWIQdaq0OZwXMFsxEvphPFrWqhprLCXx7Or5AWyjvcKA/N/t+Xp/ZqOpR91x/nqnVRFqj4ut+L14NzE9Zth3yOvlPgL7jRNESbv0jzjkTxWOGke5067uNzy5VJ8nWymxFH8IPzTGrRpJaa+jzSKWBxLyiUfeUD1X0z+9hOtCNObYtd6Ni+6tyZBY7t/t743WmPy5vl8yCsk/7eeIilCoMa1Prad4EFkHrxUGN6TX2amNpNF8ZM/DSNU2OqrBqi1HJvIVbwd6gSOU1AeqFXqroxo/7w5OS4rzv+CmEQCZb30D21LspOo+X+KUzPYPAKKiMWcinWl3urCqMFdxu7XAz6lte0wzx4/2R1tH0DcHwfv/DC9lIJJumtm++7QQH3fSjlxFtsOego/5acC42+RjnRQ1Cgf96bfj3BbTY+XHqpPZKE70mqcPr93Qp9+1H/hP9M4OinkIO3U1S3GD8Y+F4O7AfKS2RFvJW1bin4zpjK9wQVNqd9AfHyXWFwF7AG7zR1p/gLW+ebOHAXC2HmX1eTf5Xiz7+uJv+M4s9vq2D5tC0Hf147gi7L+blC99Lvnoswjh2GaR5fAc788xTbXcdK8P8NW9OlZt2zauHh1ulVDt/sX82w0bYnYWv/tuS6diWxXjlwO/CoP7A9o1Lw3dYfGOZGjekgKEOhQ+k4kS688Ylm6GpU6l0zW6dy+W6KuS9wcmH8sAXgh/awpmHdVu9NmzDH5g3D9fA09afIMM3VcbV/M72A/aCLxB5Kcv4yZn85Lwb+wvLNMFfNG4b5Zrp+r8LMXzfcZ3hCy4L4si7Z91YuQth/q4z1/SahhyALwzN792JYHcOev78BSl5R7jnUU5qoT/iIPeGMcw4h6IlZmMAvo6y4zen3la/gaNll8gxqTdsi3aShT19m1heH/+Lsa9bHMNupE1X4j95Eo+35r7YtHAczMKKgtmvh+U5PckSZQ6IaI0Y7TZuWvDo=
*/