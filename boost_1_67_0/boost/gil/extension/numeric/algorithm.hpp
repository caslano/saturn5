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
    SrcView src_view,
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
    SrcView src_view,
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
    SrcView src_view,
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
    SrcView src_view,
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