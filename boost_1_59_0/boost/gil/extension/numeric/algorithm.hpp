//
// Copyright 2005-2007 Adobe Systems Incorporated
// Copyright 2019 Pranam Lashkari <plashkari628@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_NUMERIC_ALGORITHM_HPP
#define BOOST_GIL_EXTENSION_NUMERIC_ALGORITHM_HPP

#include <boost/gil/extension/numeric/pixel_numeric_operations.hpp>

#include <boost/gil/metafunctions.hpp>
#include <boost/gil/pixel_iterator.hpp>
#include <boost/gil/image.hpp>

#include <boost/assert.hpp>

#include <algorithm>
#include <iterator>
#include <numeric>
#include <type_traits>

namespace boost { namespace gil {

/// \brief Reference proxy associated with a type that has a \p "reference" member type alias.
///
/// The reference proxy is the reference type, but with stripped-out C++ reference.
/// Models PixelConcept.
template <typename T>
struct pixel_proxy : std::remove_reference<typename T::reference> {};

/// \brief std::for_each for a pair of iterators
template <typename Iterator1, typename Iterator2, typename BinaryFunction>
BinaryFunction for_each(Iterator1 first1, Iterator1 last1, Iterator2 first2, BinaryFunction f)
{
    while (first1 != last1)
        f(*first1++, *first2++);
    return f;
}

template <typename SrcIterator, typename DstIterator>
inline
auto assign_pixels(SrcIterator src, SrcIterator src_end, DstIterator dst) -> DstIterator
{
    for_each(src, src_end, dst,
        pixel_assigns_t
        <
            typename pixel_proxy<typename std::iterator_traits<SrcIterator>::value_type>::type,
            typename pixel_proxy<typename std::iterator_traits<DstIterator>::value_type>::type
        >());
    return dst + (src_end - src);
}

namespace detail {

template <std::size_t Size>
struct inner_product_k_t
{
    template
    <
        class InputIterator1,
        class InputIterator2,
        class T,
        class BinaryOperation1,
        class BinaryOperation2
    >
    static T apply(
        InputIterator1 first1,
        InputIterator2 first2, T init,
        BinaryOperation1 binary_op1,
        BinaryOperation2 binary_op2)
    {
        init = binary_op1(init, binary_op2(*first1, *first2));
        return inner_product_k_t<Size - 1>::template apply(
            first1 + 1, first2 + 1, init, binary_op1, binary_op2);
    }
};

template <>
struct inner_product_k_t<0>
{
    template
    <
        class InputIterator1,
        class InputIterator2,
        class T,
        class BinaryOperation1,
        class BinaryOperation2
    >
    static T apply(
        InputIterator1 first1,
        InputIterator2 first2,
        T init,
        BinaryOperation1 binary_op1,
        BinaryOperation2 binary_op2)
    {
        return init;
    }
};

} // namespace detail

/// static version of std::inner_product
template
<
    std::size_t Size,
    class InputIterator1,
    class InputIterator2,
    class T,
    class BinaryOperation1,
    class BinaryOperation2
>
BOOST_FORCEINLINE
T inner_product_k(
    InputIterator1 first1,
    InputIterator2 first2,
    T init,
    BinaryOperation1 binary_op1,
    BinaryOperation2 binary_op2)
{
    return detail::inner_product_k_t<Size>::template apply(
        first1, first2, init, binary_op1, binary_op2);
}

/// \brief 1D un-guarded cross-correlation with a variable-size kernel
template
<
    typename PixelAccum,
    typename SrcIterator,
    typename KernelIterator,
    typename Size,
    typename DstIterator
>
inline
auto correlate_pixels_n(
    SrcIterator src_begin,
    SrcIterator src_end,
    KernelIterator kernel_begin,
    Size kernel_size,
    DstIterator dst_begin)
    -> DstIterator
{
    using src_pixel_ref_t = typename pixel_proxy
        <
            typename std::iterator_traits<SrcIterator>::value_type
        >::type;
    using dst_pixel_ref_t = typename pixel_proxy
        <
            typename std::iterator_traits<DstIterator>::value_type
        >::type;
    using kernel_value_t = typename std::iterator_traits<KernelIterator>::value_type;

    PixelAccum accum_zero;
    pixel_zeros_t<PixelAccum>()(accum_zero);
    while (src_begin != src_end)
    {
        pixel_assigns_t<PixelAccum, dst_pixel_ref_t>()(
            std::inner_product(
                src_begin,
                src_begin + kernel_size,
                kernel_begin,
                accum_zero,
                pixel_plus_t<PixelAccum, PixelAccum, PixelAccum>(),
                pixel_multiplies_scalar_t<src_pixel_ref_t, kernel_value_t, PixelAccum>()),
            *dst_begin);

        ++src_begin;
        ++dst_begin;
    }
    return dst_begin;
}

/// \brief 1D un-guarded cross-correlation with a fixed-size kernel
template
<
    std::size_t Size,
    typename PixelAccum,
    typename SrcIterator,
    typename KernelIterator,
    typename DstIterator
>
inline
auto correlate_pixels_k(
    SrcIterator src_begin,
    SrcIterator src_end,
    KernelIterator kernel_begin,
    DstIterator dst_begin)
    -> DstIterator
{
    using src_pixel_ref_t = typename pixel_proxy
        <
            typename std::iterator_traits<SrcIterator>::value_type
        >::type;
    using dst_pixel_ref_t = typename pixel_proxy
        <
            typename std::iterator_traits<DstIterator>::value_type
        >::type;
    using kernel_type = typename std::iterator_traits<KernelIterator>::value_type;

    PixelAccum accum_zero;
    pixel_zeros_t<PixelAccum>()(accum_zero);
    while (src_begin != src_end)
    {
        pixel_assigns_t<PixelAccum, dst_pixel_ref_t>()(
            inner_product_k<Size>(
                src_begin,
                kernel_begin,
                accum_zero,
                pixel_plus_t<PixelAccum, PixelAccum, PixelAccum>(),
                pixel_multiplies_scalar_t<src_pixel_ref_t, kernel_type, PixelAccum>()),
            *dst_begin);

        ++src_begin;
        ++dst_begin;
    }
    return dst_begin;
}

/// \brief destination is set to be product of the source and a scalar
/// \tparam PixelAccum - TODO
/// \tparam SrcView Models ImageViewConcept
/// \tparam DstView Models MutableImageViewConcept
template <typename PixelAccum, typename SrcView, typename Scalar, typename DstView>
inline
void view_multiplies_scalar(SrcView const& src_view, Scalar const& scalar, DstView const& dst_view)
{
    static_assert(std::is_scalar<Scalar>::value, "Scalar is not scalar");
    BOOST_ASSERT(src_view.dimensions() == dst_view.dimensions());
    using src_pixel_ref_t = typename pixel_proxy<typename SrcView::value_type>::type;
    using dst_pixel_ref_t = typename pixel_proxy<typename DstView::value_type>::type;
    using y_coord_t = typename SrcView::y_coord_t;

    y_coord_t const height = src_view.height();
    for (y_coord_t y = 0; y < height; ++y)
    {
        typename SrcView::x_iterator it_src = src_view.row_begin(y);
        typename DstView::x_iterator it_dst = dst_view.row_begin(y);
        typename SrcView::x_iterator it_src_end = src_view.row_end(y);
        while (it_src != it_src_end)
        {
            pixel_assigns_t<PixelAccum, dst_pixel_ref_t>()(
                pixel_multiplies_scalar_t<src_pixel_ref_t, Scalar, PixelAccum>()(*it_src, scalar),
                *it_dst);

            ++it_src;
            ++it_dst;
        }
    }
}


/// \ingroup ImageAlgorithms
/// \brief Boundary options for image boundary extension
enum class boundary_option
{
    output_ignore,  /// do nothing to the output
    output_zero,    /// set the output to zero
    extend_padded,  /// assume the source boundaries to be padded already
    extend_zero,    /// assume the source boundaries to be zero
    extend_constant /// assume the source boundaries to be the boundary value
};

namespace detail
{

template <typename SrcView, typename RltView>
void extend_row_impl(
    SrcView const& src_view,
    RltView result_view,
    std::size_t extend_count,
    boundary_option option)
{
    std::ptrdiff_t extend_count_ = static_cast<std::ptrdiff_t>(extend_count);

    if (option == boundary_option::extend_constant)
    {
        for (std::ptrdiff_t i = 0; i < result_view.height(); i++)
        {
            if(i >= extend_count_ && i < extend_count_ + src_view.height())
            {
                assign_pixels(
                    src_view.row_begin(i - extend_count_),
                    src_view.row_end(i - extend_count_),
                    result_view.row_begin(i)
                );
            }
            else if(i < extend_count_)
            {
                assign_pixels(src_view.row_begin(0), src_view.row_end(0), result_view.row_begin(i));
            }
            else
            {
                assign_pixels(
                    src_view.row_begin(src_view.height() - 1),
                    src_view.row_end(src_view.height() - 1),
                    result_view.row_begin(i)
                );
            }

        }
    }
    else if (option == boundary_option::extend_zero)
    {
        typename SrcView::value_type acc_zero;
        pixel_zeros_t<typename SrcView::value_type>()(acc_zero);

        for (std::ptrdiff_t i = 0; i < result_view.height(); i++)
        {
            if (i >= extend_count_ && i < extend_count_ + src_view.height())
            {
                assign_pixels(
                    src_view.row_begin(i - extend_count_),
                    src_view.row_end(i - extend_count_),
                    result_view.row_begin(i)
                );
            }
            else
            {
                std::fill_n(result_view.row_begin(i), result_view.width(), acc_zero);
            }
        }
    }
    else if (option == boundary_option::extend_padded)
    {
        auto original_view = subimage_view(
            src_view,
            0,
            -extend_count,
            src_view.width(),
            src_view.height() + (2 * extend_count)
        );
        for (std::ptrdiff_t i = 0; i < result_view.height(); i++)
        {
            assign_pixels(
                original_view.row_begin(i),
                original_view.row_end(i),
                result_view.row_begin(i)
            );
        }
    }
    else
    {
        BOOST_ASSERT_MSG(false, "Invalid boundary option");
    }
}

} //namespace detail


/// \brief adds new row at top and bottom.
/// Image padding introduces new pixels around the edges of an image.
/// The border provides space for annotations or acts as a boundary when using advanced filtering techniques.
/// \tparam SrcView Models ImageViewConcept
/// \tparam extend_count number of rows to be added each side
/// \tparam option - TODO
template <typename SrcView>
auto extend_row(
    SrcView const& src_view,
    std::size_t extend_count,
    boundary_option option
) -> typename gil::image<typename SrcView::value_type>
{
    typename gil::image<typename SrcView::value_type>
        result_img(src_view.width(), src_view.height() + (2 * extend_count));

    auto result_view = view(result_img);
    detail::extend_row_impl(src_view, result_view, extend_count, option);
    return result_img;
}


/// \brief adds new column at left and right.
/// Image padding introduces new pixels around the edges of an image.
/// The border provides space for annotations or acts as a boundary when using advanced filtering techniques.
/// \tparam SrcView Models ImageViewConcept
/// \tparam extend_count number of columns to be added each side
/// \tparam option - TODO
template <typename SrcView>
auto extend_col(
    SrcView const& src_view,
    std::size_t extend_count,
    boundary_option option
) -> typename gil::image<typename SrcView::value_type>
{
    auto src_view_rotate = rotated90cw_view(src_view);

    typename gil::image<typename SrcView::value_type>
        result_img(src_view.width() + (2 * extend_count), src_view.height());

    auto result_view = rotated90cw_view(view(result_img));
    detail::extend_row_impl(src_view_rotate, result_view, extend_count, option);
    return result_img;
}

/// \brief adds new row and column at all sides.
/// Image padding introduces new pixels around the edges of an image.
/// The border provides space for annotations or acts as a boundary when using advanced filtering techniques.
/// \tparam SrcView Models ImageViewConcept
/// \tparam extend_count number of rows/column to be added each side
/// \tparam option - TODO
template <typename SrcView>
auto extend_boundary(
    SrcView const& src_view,
    std::size_t extend_count,
    boundary_option option
) -> typename gil::image<typename SrcView::value_type>
{
    if (option == boundary_option::extend_padded)
    {
        typename gil::image<typename SrcView::value_type>
            result_img(src_view.width()+(2 * extend_count), src_view.height()+(2 * extend_count));
        typename gil::image<typename SrcView::value_type>::view_t result_view = view(result_img);

        auto original_view = subimage_view(
            src_view,
            -extend_count,
            -extend_count,
            src_view.width() + (2 * extend_count),
            src_view.height() + (2 * extend_count)
        );

        for (std::ptrdiff_t i = 0; i < result_view.height(); i++)
        {
            assign_pixels(
                original_view.row_begin(i),
                original_view.row_end(i),
                result_view.row_begin(i)
            );
        }

        return result_img;
    }

    auto auxilary_img = extend_col(src_view, extend_count, option);
    return extend_row(view(auxilary_img), extend_count, option);
}

}} // namespace boost::gil

#endif

/* algorithm.hpp
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
*/