//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_NUMERIC_PIXEL_NUMERIC_OPERATIONS_HPP
#define BOOST_GIL_EXTENSION_NUMERIC_PIXEL_NUMERIC_OPERATIONS_HPP

#include <boost/gil/extension/numeric/channel_numeric_operations.hpp>

#include <boost/gil/color_base_algorithm.hpp>
#include <boost/gil/pixel.hpp>

namespace boost { namespace gil {

// Function objects and utilities for pixel-wise numeric operations.
//
// List of currently defined functors:
//   pixel_plus_t (+)
//   pixel_minus_t (-)
//   pixel_multiplies_scalar_t (*)
//   pixel_divides_scalar_t (/)
//   pixel_halves_t (/=2),
//   pixel_zeros_t (=0)
//   pixel_assigns_t (=)

/// \ingroup PixelNumericOperations
/// \brief Performs channel-wise addition of two pixels.
/// \tparam PixelRef1 - models PixelConcept
/// \tparam PixelRef2 - models PixelConcept
/// \tparam PixelResult - models PixelValueConcept
template <typename PixelRef1, typename PixelRef2, typename PixelResult>
struct pixel_plus_t
{
    auto operator()(PixelRef1 const& p1, PixelRef2 const& p2) const -> PixelResult
    {
        PixelResult result;
        static_transform(p1, p2, result,
            channel_plus_t
            <
                typename channel_type<PixelRef1>::type,
                typename channel_type<PixelRef2>::type,
                typename channel_type<PixelResult>::type
            >());
        return result;
    }
};

/// \ingroup PixelNumericOperations
/// \brief Performs channel-wise subtraction of two pixels.
/// \tparam PixelRef1 - models PixelConcept
/// \tparam PixelRef2 - models PixelConcept
/// \tparam PixelResult - models PixelValueConcept
template <typename PixelRef1, typename PixelRef2, typename PixelResult>
struct pixel_minus_t
{
    auto operator()(PixelRef1 const& p1, PixelRef2 const& p2) const -> PixelResult
    {
        PixelResult result;
        static_transform(p1, p2, result,
            channel_minus_t
            <
                typename channel_type<PixelRef1>::type,
                typename channel_type<PixelRef2>::type,
                typename channel_type<PixelResult>::type
            >());
        return result;
    }
};

/// \ingroup PixelNumericOperations
/// \brief Performs channel-wise multiplication of pixel elements by scalar.
/// \tparam PixelRef - models PixelConcept
/// \tparam Scalar - models a scalar type
/// \tparam PixelResult - models PixelValueConcept
template <typename PixelRef, typename Scalar, typename PixelResult>
struct pixel_multiplies_scalar_t
{
    auto operator()(PixelRef const& p, Scalar const& s) const -> PixelResult
    {
        PixelResult result;
        static_transform(p, result,
            std::bind(
                channel_multiplies_scalar_t<typename channel_type<PixelRef>::type,
                Scalar,
                typename channel_type<PixelResult>::type>(),
                std::placeholders::_1, s));
        return result;
    }
};

/// \ingroup PixelNumericOperations
/// \brief Performs channel-wise multiplication of two pixels.
/// \tparam PixelRef1 - models PixelConcept
/// \tparam PixelRef1 - models PixelConcept
/// \tparam PixelResult - models PixelValueConcept
template <typename PixelRef1, typename PixelRef2, typename PixelResult>
struct pixel_multiply_t
{
    auto operator()(PixelRef1 const& p1, PixelRef2 const& p2) const -> PixelResult
    {
        PixelResult result;
        static_transform(p1, p2, result,
            channel_multiplies_t
            <
                typename channel_type<PixelRef1>::type,
                typename channel_type<PixelRef2>::type,
                typename channel_type<PixelResult>::type
            >());
        return result;
    }
};

/// \ingroup PixelNumericOperations
/// \brief Performs channel-wise division of pixel elements by scalar.
/// \tparam PixelRef - models PixelConcept
/// \tparam Scalar - models a scalar type
/// \tparam PixelResult - models PixelValueConcept
template <typename PixelRef, typename Scalar, typename PixelResult>
struct pixel_divides_scalar_t
{
    auto operator()(PixelRef const& p, Scalar const& s) const -> PixelResult
    {
        PixelResult result;
        static_transform(p, result,
            std::bind(channel_divides_scalar_t<typename channel_type<PixelRef>::type,
                Scalar,
                typename channel_type<PixelResult>::type>(),
                std::placeholders::_1, s));
        return result;
    }
};

/// \ingroup PixelNumericOperations
/// \brief Performs channel-wise division of two pixels.
/// \tparam PixelRef1 - models PixelConcept
/// \tparam PixelRef1 - models PixelConcept
/// \tparam PixelResult - models PixelValueConcept
template <typename PixelRef1, typename PixelRef2, typename PixelResult>
struct pixel_divide_t
{
    auto operator()(PixelRef1 const& p1, PixelRef2 const& p2) const -> PixelResult
    {
        PixelResult result;
        static_transform(p1, p2, result,
            channel_divides_t
            <
                typename channel_type<PixelRef1>::type,
                typename channel_type<PixelRef2>::type,
                typename channel_type<PixelResult>::type
            >());
        return result;
    }
};

/// \ingroup PixelNumericOperations
/// \brief Performs channel-wise division by 2
/// \tparam PixelRef - models PixelConcept
template <typename PixelRef>
struct pixel_halves_t
{
    auto operator()(PixelRef& p) const -> PixelRef&
    {
        static_for_each(p, channel_halves_t<typename channel_type<PixelRef>::type>());
        return p;
    }
};

/// \ingroup PixelNumericOperations
/// \brief Sets pixel elements to zero (for whatever zero means)
/// \tparam PixelRef - models PixelConcept
template <typename PixelRef>
struct pixel_zeros_t
{
    auto operator()(PixelRef& p) const -> PixelRef&
    {
        static_for_each(p, channel_zeros_t<typename channel_type<PixelRef>::type>());
        return p;
    }
};

/// \brief Sets pixel elements to zero (for whatever zero means)
/// \tparam Pixel - models PixelConcept
template <typename Pixel>
void zero_channels(Pixel& p)
{
    static_for_each(p, channel_zeros_t<typename channel_type<Pixel>::type>());
}

/// \ingroup PixelNumericOperations
/// \brief Casts and assigns a pixel to another
///
/// A generic implementation for casting and assigning a pixel to another.
/// User should specialize it for better performance.
///
/// \tparam PixelRef - models PixelConcept
/// \tparam PixelResult - models PixelValueConcept
template <typename PixelRef, typename PixelResult>
struct pixel_assigns_t
{
    auto operator()(PixelRef const& src, PixelResult& dst) const -> PixelResult
    {
        static_for_each(src, dst,
            channel_assigns_t
            <
                typename channel_type<PixelRef>::type,
                typename channel_type<PixelResult>::type
            >());
        return dst;
    }
};

}} // namespace boost::gil

#endif

/* pixel_numeric_operations.hpp
hi5sWlrYOnoC7FdLKo+FZqFFn/NE812jKR402oPmBHZ5tO8I+2ldDqvl0lTev9I3Gf5aBxzXrrex+Lb3+MHhqaKGvkAELZDUwzwF8/lo76S+RLiDEd5EBOq/0P/IO8og1MUvR14H+d3GmV8Gm8e8AhX/ciogzTGyEvX+94dCR9k/f/7V3Jy+3srTuy3mnaLLlhqqd25586jLPrTNo8p6nTkG6/UgdDHmaBqo89m/fOstuW8wn5QesU8BsXUHnpgTeXeHlLIeJjXRzry3tr53MQgdOOctqvqHH+GduFM0fzoqxutJqvnzdyAJjzMP3UCrD7j+D8sptmTIR2zpdRLRMUYj3ouIRO1nLZPvoAMjQ8skFVVDA122WQLmZluPvewu7y8faDza1PdflNOw2XfgTQS6hnA7ujgdB+GOwV2CqwCY9HeLC8r90hpD323EuUhrs2SFpXFJxY2P8OEvQMVUZGC7UFtoKKi/Tahx1oUI9bcO1XStwm/WhcjVYhE7ad10fCbqHIne2ZH7g1itITXwLiLjioCUsR3KbPypfaBRcv9VMxtfin2zGFc9zPt8GJ+P9uL4HLbPfx6AwiT/KfwUwxlchJ2DX+i8n88en27u8sjgMnfeqWf8/W399GW5HJdVXdO4PZCxebSHPTZfTbCv96SqinrVRMYOOoFqMhNUk+IcA55OUIM/QcOvBxPs8ftYPVE4QS2XBLnsubucd02JZ/REwSnE9nMfD+znRmm+LgKJB0zBxSRUvwzJ7d9GvHqRirfTwgv9TY6iNhP7ZHfFxpiJrMjlduIws19gsVk1pe8lPyPKCzDgYQ68IZ3yUQSY19/E5uJjfelWn9l2+8+LHaL0UD1zPNXWnIB+N8hxGUc5vH81v3vUNNLH7LqlZoLMd757sDFJcM3L57lXXzWq6TZqhPPSfj1ZX6l7vhM19NyIJyQnkJ/QLVKktpT/a9BzvkgHc3uT5vZLhTaoqtDagMp2sblMRDj3x4ott9oRgLE0ScOLTE3RZE8xXAd9nII2sL7aSrDO5IkyB40qPwe546nYUSkJa+StPTGfzseNWDkO+cZ88v3lsCWB51QR+XXLGMtT78sJVXXklJ9J+ETNsVFoa6uLcQOAlmlOPUavTKvHq1dA272u9n/or458BZvLTIaIKE4i4oSGmqbvSlRqbtSAOb9QHi7xqgkAebxeL72UIALjyYQRvvUSPsT7+T2Qupa2BibY1LcABLKNaP+yutRvABkzQzVHfZijTPhpEMebyEjh8x+WqKLpQ5LRpmsZmVpK5j6SqaVkIkimE/yo1aBHjdOcvFbQSp+m/GMJyhzHOex3cAF0TyQ6HW/D7s6TcH64hXBr4U7B1UR4RgLC4LxwMnnY74lh+hiku5TvPwtLyxP9QQrM81EpyhT8Bovw3mbIxUjNxbPM7MgltjW6UcLi3Yd3fBLJTFAvjLvdOHP/8rCs8nYuDbUlXG0VTCsLu573gJXy7V7VYXpkMYo4k/lqs8TmbEUR02ZVMP0yjQzTRDgnprYXXcEPEM3OnX03LE5tgvHIK63mNGCo+3PSMyZU7pPdUKZUGUKzqqn93ac1+Z9fk4Z4FlCzYrGOl/XvaHlRuisLXV7/8YpHzl5YVe4Awqhhfe+NvP+lqb07mjfUF9tkE8o/MobgUzAwKnqoTL3wtbA4guYjDruEwvTRyn12fo1Egq9pvfAZYpHz6gj30EYQo08tlfuGb2rcx624l19FtaDSdstrXMvC9daQfMOmZVJZ1RkWQv1KjaHmQjdz/VdCfVmMe7XGegNkJrymNTb3bRXhrXxDiyjZYnmuLqzN/+v7TxCxq0HGFa2nbpLFM65dqDUWVfW3CTXEoqo=
*/