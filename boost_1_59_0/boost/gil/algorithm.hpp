//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_ALGORITHM_HPP
#define BOOST_GIL_ALGORITHM_HPP

#include <boost/gil/bit_aligned_pixel_iterator.hpp>
#include <boost/gil/color_base_algorithm.hpp>
#include <boost/gil/concepts.hpp>
#include <boost/gil/image_view.hpp>
#include <boost/gil/image_view_factory.hpp>
#include <boost/gil/detail/mp11.hpp>
#include <boost/gil/detail/type_traits.hpp>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <iterator>
#include <memory>
#include <type_traits>
#include <typeinfo>

namespace boost { namespace gil {

//forward declarations
template <typename ChannelPtr, typename ColorSpace>
struct planar_pixel_iterator;
template <typename Iterator>
class memory_based_step_iterator;
template <typename StepIterator>
class memory_based_2d_locator;

// a tag denoting incompatible arguments
struct error_t {};

/// \defgroup ImageViewSTLAlgorithms STL-like Algorithms
/// \ingroup ImageViewAlgorithm
/// \brief Image view-equivalents of STL algorithms
///
/// Image views provide 1D iteration of their pixels via \p begin() and \p end() methods,
/// which makes it possible to use STL algorithms with them. However, using nested loops
/// over X and Y is in many cases more efficient. The algorithms in this section resemble
/// STL algorithms, but they abstract away the nested loops and take views (as opposed to ranges) as input.
///
/// Most algorithms check whether the image views are 1D-traversable. A 1D-traversable image view has no gaps
/// at the end of the rows. In other words, if an x_iterator of that view is advanced past the last pixel in a row
/// it will move to the first pixel of the next row. When image views are 1D-traversable, the algorithms use
/// a single loop and run more efficiently. If one or more of the input views are not 1D-traversable, the algorithms
/// fall-back to an X-loop nested inside a Y-loop.
///
/// The algorithms typically delegate the work to their corresponding STL algorithms. For example, \p copy_pixels calls
/// \p std::copy either for each row, or, when the images are 1D-traversable, once for all pixels.
///
/// In addition, overloads are sometimes provided for the STL algorithms. For example, std::copy for planar iterators
/// is overloaded to perform \p std::copy for each of the planes. \p std::copy over bitwise-copiable pixels results in
/// std::copy over unsigned char, which STL typically implements via \p memmove.
///
/// As a result \p copy_pixels may result in a single call to \p memmove for interleaved 1D-traversable views,
/// or one per each plane of planar 1D-traversable views, or one per each row of interleaved non-1D-traversable images, etc.

/// \defgroup STLOptimizations  Performance overloads of STL algorithms
/// \ingroup ImageViewAlgorithm
/// \brief overloads of STL algorithms allowing more efficient implementation when used with GIL constructs

/// \brief A generic binary operation on views
/// \ingroup ImageViewSTLAlgorithms
///
/// Use this class as a convenience superclass when defining an operation for any image views.
/// Many operations have different behavior when the two views are compatible. This class checks
/// for compatibility and invokes apply_compatible(V1,V2) or apply_incompatible(V1,V2) of the subclass.
/// You must provide apply_compatible(V1,V2) method in your subclass, but apply_incompatible(V1,V2)
/// is not required and the default throws std::bad_cast.
template <typename Derived, typename Result=void>
struct binary_operation_obj
{
    using result_type = Result;

    template <typename V1, typename V2> BOOST_FORCEINLINE
    result_type operator()(const std::pair<const V1*,const V2*>& p) const {
        return apply(*p.first, *p.second, typename views_are_compatible<V1,V2>::type());
    }

    template <typename V1, typename V2> BOOST_FORCEINLINE
    result_type operator()(const V1& v1, const V2& v2) const {
        return apply(v1, v2, typename views_are_compatible<V1,V2>::type());
    }

    result_type operator()(const error_t&) const { throw std::bad_cast(); }
private:

    // dispatch from apply overload to a function with distinct name
    template <typename V1, typename V2>
    BOOST_FORCEINLINE
    result_type apply(V1 const& v1, V2 const& v2, std::false_type) const
    {
        return ((const Derived*)this)->apply_incompatible(v1, v2);
    }

    // dispatch from apply overload to a function with distinct name
    template <typename V1, typename V2>
    BOOST_FORCEINLINE
    result_type apply(V1 const& v1, V2 const& v2, std::true_type) const
    {
        return ((const Derived*)this)->apply_compatible(v1, v2);
    }

    // function with distinct name - it can be overloaded by subclasses
    template <typename V1, typename V2>
    BOOST_FORCEINLINE
    result_type apply_incompatible(V1 const& /*v1*/, V2 const& /*v2*/) const
    {
        throw std::bad_cast();
    }
};

}}  // namespace boost::gil

//////////////////////////////////////////////////////////////////////////////////////
// std::copy and gil::copy_pixels
//////////////////////////////////////////////////////////////////////////////////////

/// \defgroup ImageViewSTLAlgorithmsCopyPixels copy_pixels
/// \ingroup ImageViewSTLAlgorithms
/// \brief std::copy for image views

namespace std {

/// \ingroup STLOptimizations
/// \brief Copy when both src and dst are interleaved and of the same type can be just memmove
template<typename T, typename CS>
BOOST_FORCEINLINE
auto copy(
    boost::gil::pixel<T, CS>* first,
    boost::gil::pixel<T, CS>* last,
    boost::gil::pixel<T, CS>* dst)
    ->  boost::gil::pixel<T, CS>*
{
    auto p = std::copy((unsigned char*)first, (unsigned char*)last, (unsigned char*)dst);
    return reinterpret_cast<boost::gil::pixel<T, CS>*>(p);
}

/// \ingroup STLOptimizations
/// \brief Copy when both src and dst are interleaved and of the same type can be just memmove
template<typename T, typename CS>
BOOST_FORCEINLINE boost::gil::pixel<T,CS>*
copy(const boost::gil::pixel<T,CS>* first, const boost::gil::pixel<T,CS>* last,
     boost::gil::pixel<T,CS>* dst) {
    return (boost::gil::pixel<T,CS>*)std::copy((unsigned char*)first,(unsigned char*)last, (unsigned char*)dst);
}
} // namespace std

namespace boost { namespace gil {
namespace detail {
template <typename I, typename O> struct copy_fn {
    BOOST_FORCEINLINE I operator()(I first, I last, O dst) const { return std::copy(first,last,dst); }
};
} // namespace detail
} }  // namespace boost::gil

namespace std {
/// \ingroup STLOptimizations
/// \brief Copy when both src and dst are planar pointers is copy for each channel
template<typename CS, typename IC1, typename IC2> BOOST_FORCEINLINE
boost::gil::planar_pixel_iterator<IC2,CS> copy(boost::gil::planar_pixel_iterator<IC1,CS> first, boost::gil::planar_pixel_iterator<IC1,CS> last, boost::gil::planar_pixel_iterator<IC2,CS> dst) {
    boost::gil::gil_function_requires<boost::gil::ChannelsCompatibleConcept<typename std::iterator_traits<IC1>::value_type,typename std::iterator_traits<IC2>::value_type>>();
    static_for_each(first,last,dst,boost::gil::detail::copy_fn<IC1,IC2>());
    return dst+(last-first);
}
} // namespace std

namespace boost { namespace gil {
namespace detail {
/// Does a copy-n. If the inputs contain image iterators, performs a copy at each row using the row iterators
/// \ingroup CopyPixels
template <typename I, typename O>
struct copier_n {
    BOOST_FORCEINLINE void operator()(I src, typename std::iterator_traits<I>::difference_type n, O dst) const { std::copy(src,src+n, dst); }
};

/// Source range is delimited by image iterators
template <typename IL, typename O>  // IL Models ConstPixelLocatorConcept, O Models PixelIteratorConcept
struct copier_n<iterator_from_2d<IL>,O> {
    using diff_t = typename std::iterator_traits<iterator_from_2d<IL>>::difference_type;
    BOOST_FORCEINLINE void operator()(iterator_from_2d<IL> src, diff_t n, O dst) const {
        gil_function_requires<PixelLocatorConcept<IL>>();
        gil_function_requires<MutablePixelIteratorConcept<O>>();
        while (n>0) {
            diff_t l=src.width()-src.x_pos();
            diff_t numToCopy=(n<l ? n:l);
            detail::copy_n(src.x(), numToCopy, dst);
            dst+=numToCopy;
            src+=numToCopy;
            n-=numToCopy;
        }
    }
};

/// Destination range is delimited by image iterators
template <typename I, typename OL> // I Models ConstPixelIteratorConcept, OL Models PixelLocatorConcept
struct copier_n<I,iterator_from_2d<OL>> {
    using diff_t = typename std::iterator_traits<I>::difference_type;
    BOOST_FORCEINLINE void operator()(I src, diff_t n, iterator_from_2d<OL> dst) const {
        gil_function_requires<PixelIteratorConcept<I>>();
        gil_function_requires<MutablePixelLocatorConcept<OL>>();
        while (n>0) {
            diff_t l=dst.width()-dst.x_pos();
            diff_t numToCopy=(n<l ? n:l);
            detail::copy_n(src, numToCopy, dst.x());
            dst+=numToCopy;
            src+=numToCopy;
            n-=numToCopy;
        }
    }
};

/// Both source and destination ranges are delimited by image iterators
template <typename IL, typename OL>
struct copier_n<iterator_from_2d<IL>,iterator_from_2d<OL>> {
   using diff_t = typename iterator_from_2d<IL>::difference_type;
   BOOST_FORCEINLINE void operator()(iterator_from_2d<IL> src, diff_t n, iterator_from_2d<OL> dst) const {
        gil_function_requires<PixelLocatorConcept<IL>>();
        gil_function_requires<MutablePixelLocatorConcept<OL>>();
        if (src.x_pos()!=dst.x_pos() || src.width()!=dst.width()) {
            while(n-->0) {
                *dst++=*src++;
            }
        }
        while (n>0) {
            diff_t l=dst.width()-dst.x_pos();
            diff_t numToCopy=(n<l ? n : l);
            detail::copy_n(src.x(), numToCopy, dst.x());
            dst+=numToCopy;
            src+=numToCopy;
            n-=numToCopy;
        }
    }
};

template <typename SrcIterator, typename DstIterator>
BOOST_FORCEINLINE DstIterator copy_with_2d_iterators(SrcIterator first, SrcIterator last, DstIterator dst) {
    using src_x_iterator = typename SrcIterator::x_iterator;
    using dst_x_iterator = typename DstIterator::x_iterator;

    typename SrcIterator::difference_type n = last - first;

    if (first.is_1d_traversable()) {
        if (dst.is_1d_traversable())
            copier_n<src_x_iterator,dst_x_iterator>()(first.x(),n, dst.x());
        else
            copier_n<src_x_iterator,DstIterator >()(first.x(),n, dst);
    } else {
        if (dst.is_1d_traversable())
            copier_n<SrcIterator,dst_x_iterator>()(first,n, dst.x());
        else
            copier_n<SrcIterator,DstIterator>()(first,n,dst);
    }
    return dst+n;
}
} // namespace detail
} }  // namespace boost::gil

namespace std {
/// \ingroup STLOptimizations
/// \brief  std::copy(I1,I1,I2) with I1 and I2 being a iterator_from_2d
template <typename IL, typename OL>
BOOST_FORCEINLINE boost::gil::iterator_from_2d<OL> copy1(boost::gil::iterator_from_2d<IL> first, boost::gil::iterator_from_2d<IL> last, boost::gil::iterator_from_2d<OL> dst) {
    return boost::gil::detail::copy_with_2d_iterators(first,last,dst);
}
} // namespace std

namespace boost { namespace gil {
/// \ingroup ImageViewSTLAlgorithmsCopyPixels
/// \brief std::copy for image views
template <typename View1, typename View2> BOOST_FORCEINLINE
void copy_pixels(const View1& src, const View2& dst)
{
    BOOST_ASSERT(src.dimensions() == dst.dimensions());
    detail::copy_with_2d_iterators(src.begin(),src.end(),dst.begin());
}

//////////////////////////////////////////////////////////////////////////////////////
// copy_and_convert_pixels
//////////////////////////////////////////////////////////////////////////////////////

/// \defgroup ImageViewSTLAlgorithmsCopyAndConvertPixels copy_and_convert_pixels
/// \ingroup ImageViewSTLAlgorithms
/// \brief copies src view into dst view, color converting if necessary.
///
/// Versions taking static and runtime views are provided. Versions taking user-defined color convered are provided.

namespace detail {
template <typename CC>
class copy_and_convert_pixels_fn : public binary_operation_obj<copy_and_convert_pixels_fn<CC>>
{
private:
    CC _cc;
public:
    using result_type = typename binary_operation_obj<copy_and_convert_pixels_fn<default_color_converter>>::result_type;
    copy_and_convert_pixels_fn() {}
    copy_and_convert_pixels_fn(CC cc_in) : _cc(cc_in) {}
   // when the two color spaces are incompatible, a color conversion is performed
    template <typename V1, typename V2> BOOST_FORCEINLINE
    result_type apply_incompatible(const V1& src, const V2& dst) const {
        copy_pixels(color_converted_view<typename V2::value_type>(src,_cc),dst);
    }

    // If the two color spaces are compatible, copy_and_convert is just copy
    template <typename V1, typename V2> BOOST_FORCEINLINE
    result_type apply_compatible(const V1& src, const V2& dst) const {
         copy_pixels(src,dst);
    }
};
} // namespace detail

/// \ingroup ImageViewSTLAlgorithmsCopyAndConvertPixels
template <typename V1, typename V2,typename CC>
BOOST_FORCEINLINE
void copy_and_convert_pixels(const V1& src, const V2& dst,CC cc) {
    detail::copy_and_convert_pixels_fn<CC> ccp(cc);
    ccp(src,dst);
}

struct default_color_converter;

/// \ingroup ImageViewSTLAlgorithmsCopyAndConvertPixels
template <typename View1, typename View2>
BOOST_FORCEINLINE
void copy_and_convert_pixels(const View1& src, const View2& dst) {
    detail::copy_and_convert_pixels_fn<default_color_converter> ccp;
    ccp(src,dst);
}
} }  // namespace boost::gil

//////////////////////////////////////////////////////////////////////////////////////
// std::fill and gil::fill_pixels
//////////////////////////////////////////////////////////////////////////////////////

/// \defgroup ImageViewSTLAlgorithmsFillPixels fill_pixels
/// \ingroup ImageViewSTLAlgorithms
/// \brief std::fill for image views

namespace std {
/// \ingroup STLOptimizations
/// \brief std::fill(I,I,V) with I being a iterator_from_2d
///
/// Invoked when one calls std::fill(I,I,V) with I being a iterator_from_2d (which is
/// a 1D iterator over the pixels in an image). For contiguous images (i.e. images that have
/// no alignment gap at the end of each row) it is more efficient to use the underlying
/// pixel iterator that does not check for the end of rows. For non-contiguous images fill
/// resolves to fill of each row using the underlying pixel iterator, which is still faster
template <typename IL, typename V>
void fill(boost::gil::iterator_from_2d<IL> first, boost::gil::iterator_from_2d<IL> last, const V& val) {
    boost::gil::gil_function_requires<boost::gil::MutablePixelLocatorConcept<IL>>();
    if (first.is_1d_traversable()) {
        std::fill(first.x(), last.x(), val);
    } else {
        // fill row by row
        std::ptrdiff_t n=last-first;
        while (n>0) {
            std::ptrdiff_t numToDo=std::min<const std::ptrdiff_t>(n,(std::ptrdiff_t)(first.width()-first.x_pos()));
            std::fill_n(first.x(), numToDo, val);
            first+=numToDo;
            n-=numToDo;
        }
    }
}
} // namespace std

namespace boost { namespace gil {

namespace detail {

/// struct to do std::fill
struct std_fill_t {
    template <typename It, typename P>
    void operator()(It first, It last, const P& p_in) {
        std::fill(first,last,p_in);
    }
};

/// std::fill for planar iterators
template <typename It, typename P>
BOOST_FORCEINLINE
void fill_aux(It first, It last, P const& p, std::true_type)
{
    static_for_each(first, last, p, std_fill_t());
}

/// std::fill for interleaved iterators
template <typename It, typename P>
BOOST_FORCEINLINE
void fill_aux(It first, It last, P const& p, std::false_type)
{
    std::fill(first, last, p);
}

} // namespace detail

/// \ingroup ImageViewSTLAlgorithmsFillPixels
/// \brief std::fill for image views
template <typename View, typename Value>
BOOST_FORCEINLINE
void fill_pixels(View const& view, Value const& value)
{
    if (view.is_1d_traversable())
    {
        detail::fill_aux(
            view.begin().x(), view.end().x(), value, is_planar<View>());
    }
    else
    {
        for (std::ptrdiff_t y = 0; y < view.height(); ++y)
            detail::fill_aux(
                view.row_begin(y), view.row_end(y), value, is_planar<View>());
    }
}

//////////////////////////////////////////////////////////////////////////////////////
// destruct_pixels
//////////////////////////////////////////////////////////////////////////////////////

/// \defgroup ImageViewSTLAlgorithmsDestructPixels destruct_pixels
/// \ingroup ImageViewSTLAlgorithms
/// \brief invokes the destructor on every pixel of an image view

namespace detail {
template <typename Iterator>
BOOST_FORCEINLINE
void destruct_range_impl(Iterator first, Iterator last,
    typename std::enable_if
    <
        mp11::mp_and
        <
            std::is_pointer<Iterator>,
            mp11::mp_not
            <
                detail::is_trivially_destructible<typename std::iterator_traits<Iterator>::value_type>
            >
        >::value
    >::type* /*ptr*/ = 0)
{
    while (first != last)
    {
        first->~value_t();
        ++first;
    }
}

template <typename Iterator>
BOOST_FORCEINLINE
void destruct_range_impl(Iterator /*first*/, Iterator /*last*/,
    typename std::enable_if
    <
        mp11::mp_or
        <
            mp11::mp_not<std::is_pointer<Iterator>>,
            detail::is_trivially_destructible<typename std::iterator_traits<Iterator>::value_type>
        >::value
    >::type* /* ptr */ = nullptr)
{
}

template <typename Iterator>
BOOST_FORCEINLINE
void destruct_range(Iterator first, Iterator last)
{
    destruct_range_impl(first, last);
}

struct std_destruct_t
{
    template <typename Iterator>
    void operator()(Iterator first, Iterator last) const
    {
        destruct_range(first,last);
    }
};

/// destruct for planar iterators
template <typename It>
BOOST_FORCEINLINE
void destruct_aux(It first, It last, std::true_type)
{
    static_for_each(first,last,std_destruct_t());
}

/// destruct for interleaved iterators
template <typename It>
BOOST_FORCEINLINE
void destruct_aux(It first, It last, std::false_type)
{
    destruct_range(first,last);
}

} // namespace detail

/// \ingroup ImageViewSTLAlgorithmsDestructPixels
/// \brief Invokes the in-place destructor on every pixel of the view
template <typename View>
BOOST_FORCEINLINE
void destruct_pixels(View const& view)
{
    if (view.is_1d_traversable())
    {
        detail::destruct_aux(
            view.begin().x(), view.end().x(), is_planar<View>());
    }
    else
    {
        for (std::ptrdiff_t y = 0; y < view.height(); ++y)
            detail::destruct_aux(
                view.row_begin(y), view.row_end(y), is_planar<View>());
    }
}

//////////////////////////////////////////////////////////////////////////////////////
// uninitialized_fill_pixels
//////////////////////////////////////////////////////////////////////////////////////

/// \defgroup ImageViewSTLAlgorithmsUninitializedFillPixels uninitialized_fill_pixels
/// \ingroup ImageViewSTLAlgorithms
/// \brief std::uninitialized_fill for image views

namespace detail {

/// std::uninitialized_fill for planar iterators
/// If an exception is thrown destructs any in-place copy-constructed objects
template <typename It, typename P>
BOOST_FORCEINLINE
void uninitialized_fill_aux(It first, It last, P const& p, std::true_type)
{
    std::size_t channel = 0;
    try
    {
        using pixel_t = typename std::iterator_traits<It>::value_type;
        while (channel < num_channels<pixel_t>::value)
        {
            std::uninitialized_fill(
                dynamic_at_c(first,channel),
                dynamic_at_c(last,channel),
                dynamic_at_c(p,channel));

            ++channel;
        }
    }
    catch (...)
    {
        for (std::size_t c = 0; c < channel; ++c)
            destruct_range(dynamic_at_c(first, c), dynamic_at_c(last, c));
        throw;
    }
}

/// std::uninitialized_fill for interleaved iterators
/// If an exception is thrown destructs any in-place copy-constructed objects
template <typename It, typename P>
BOOST_FORCEINLINE
void uninitialized_fill_aux(It first, It last, P const& p, std::false_type)
{
    std::uninitialized_fill(first,last,p);
}

} // namespace detail

/// \ingroup ImageViewSTLAlgorithmsUninitializedFillPixels
/// \brief std::uninitialized_fill for image views.
/// Does not support planar heterogeneous views.
/// If an exception is thrown destructs any in-place copy-constructed pixels
template <typename View, typename Value>
void uninitialized_fill_pixels(const View& view, const Value& val) {
    if (view.is_1d_traversable())
        detail::uninitialized_fill_aux(view.begin().x(), view.end().x(),
                                       val,is_planar<View>());
    else {
        typename View::y_coord_t y = 0;
        try {
            for (y=0; y<view.height(); ++y)
                detail::uninitialized_fill_aux(view.row_begin(y),view.row_end(y),
                                               val,is_planar<View>());
        } catch(...) {
            for (typename View::y_coord_t y0=0; y0<y; ++y0)
                detail::destruct_aux(view.row_begin(y0),view.row_end(y0), is_planar<View>());
            throw;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////
// default_construct_pixels
//////////////////////////////////////////////////////////////////////////////////////

/// \defgroup ImageViewSTLAlgorithmsDefaultConstructPixels default_construct_pixels
/// \ingroup ImageViewSTLAlgorithms
/// \brief invokes the default constructor on every pixel of an image view

namespace detail {
template <typename It> BOOST_FORCEINLINE
void default_construct_range_impl(It first, It last, std::true_type)
{
    It first1 = first;
    try
    {
        using value_t = typename std::iterator_traits<It>::value_type;
        while (first != last)
        {
            new (first) value_t();
            ++first;
        }
    }
    catch (...)
    {
        destruct_range(first1, first);
        throw;
    }
}

template <typename It>
BOOST_FORCEINLINE
void default_construct_range_impl(It, It, std::false_type) {}

template <typename It>
BOOST_FORCEINLINE
void default_construct_range(It first, It last)
{
    default_construct_range_impl(first, last, typename std::is_pointer<It>::type());
}

/// uninitialized_default_construct for planar iterators
template <typename It>
BOOST_FORCEINLINE
void default_construct_aux(It first, It last, std::true_type)
{
    std::size_t channel = 0;
    try
    {
        using pixel_t = typename std::iterator_traits<It>::value_type;
        while (channel < num_channels<pixel_t>::value)
        {
            default_construct_range(dynamic_at_c(first, channel), dynamic_at_c(last, channel));
            ++channel;
        }
    }
    catch (...)
    {
        for (std::size_t c = 0; c < channel; ++c)
            destruct_range(dynamic_at_c(first, c), dynamic_at_c(last, c));
        throw;
    }
}

/// uninitialized_default_construct for interleaved iterators
template <typename It>
BOOST_FORCEINLINE
void default_construct_aux(It first, It last, std::false_type)
{
    default_construct_range(first, last);
}

template <typename View, bool IsPlanar>
struct has_trivial_pixel_constructor
    : detail::is_trivially_default_constructible<typename View::value_type>
{};

template <typename View>
struct has_trivial_pixel_constructor<View, true>
    : detail::is_trivially_default_constructible<typename channel_type<View>::type>
{};

template<typename View, bool IsTriviallyConstructible>
BOOST_FORCEINLINE
void default_construct_pixels_impl(
    View const& view,
    std::enable_if<!IsTriviallyConstructible>* /*ptr*/ = nullptr)
{
    if (view.is_1d_traversable())
    {
        detail::default_construct_aux(
            view.begin().x(), view.end().x(), is_planar<View>());
    }
    else
    {
        typename View::y_coord_t y = 0;
        try
        {
            for( y = 0; y < view.height(); ++y )
                detail::default_construct_aux(
                    view.row_begin(y), view.row_end(y), is_planar<View>());
        }
        catch(...)
        {
            for (typename View::y_coord_t y0 = 0; y0 < y; ++y0 )
                detail::destruct_aux(
                    view.row_begin(y0), view.row_end(y0), is_planar<View>());

            throw;
        }
    }
}

} // namespace detail

/// \ingroup ImageViewSTLAlgorithmsDefaultConstructPixels
/// \brief Invokes the in-place default constructor on every pixel of the (uninitialized) view.
/// Does not support planar heterogeneous views.
/// If an exception is thrown destructs any in-place default-constructed pixels
template <typename View>
void default_construct_pixels(View const& view)
{
    detail::default_construct_pixels_impl
        <
            View,
            detail::has_trivial_pixel_constructor
            <
                View,
                is_planar<View>::value
            >::value
        >(view);
}

//////////////////////////////////////////////////////////////////////////////////////
// uninitialized_copy_pixels
//////////////////////////////////////////////////////////////////////////////////////

/// \defgroup ImageViewSTLAlgorithmsUninitializedCopyPixels uninitialized_copy_pixels
/// \ingroup ImageViewSTLAlgorithms
/// \brief std::uninitialized_copy for image views

namespace detail {

/// std::uninitialized_copy for pairs of planar iterators
template <typename It1, typename It2>
BOOST_FORCEINLINE
void uninitialized_copy_aux(It1 first1, It1 last1, It2 first2, std::true_type)
{
    std::size_t channel=0;
    try {
        using pixel_t = typename std::iterator_traits<It1>::value_type;
        while (channel < num_channels<pixel_t>::value)
        {
            std::uninitialized_copy(
                dynamic_at_c(first1, channel),
                dynamic_at_c(last1, channel),
                dynamic_at_c(first2, channel));
            ++channel;
        }
    }
    catch (...)
    {
        It2 last2 = first2;
        std::advance(last2, std::distance(first1, last1));
        for (std::size_t c = 0; c < channel; ++c)
            destruct_range(dynamic_at_c(first2, c), dynamic_at_c(last2, c));
        throw;
    }
}

/// std::uninitialized_copy for interleaved or mixed iterators
template <typename It1, typename It2>
BOOST_FORCEINLINE
void uninitialized_copy_aux(It1 first1, It1 last1, It2 first2, std::false_type)
{
    std::uninitialized_copy(first1, last1, first2);
}
} // namespace detail

/// \ingroup ImageViewSTLAlgorithmsUninitializedCopyPixels
/// \brief std::uninitialized_copy for image views.
/// Does not support planar heterogeneous views.
/// If an exception is thrown destructs any in-place copy-constructed objects
template <typename View1, typename View2>
void uninitialized_copy_pixels(View1 const& view1, View2 const& view2)
{
    using is_planar = std::integral_constant<bool, is_planar<View1>::value && is_planar<View2>::value>;
    BOOST_ASSERT(view1.dimensions() == view2.dimensions());

    if (view1.is_1d_traversable() && view2.is_1d_traversable())
    {
        detail::uninitialized_copy_aux(
            view1.begin().x(), view1.end().x(), view2.begin().x(), is_planar());
    }
    else
    {
        typename View1::y_coord_t y = 0;
        try
        {
            for (y = 0; y < view1.height(); ++y)
                detail::uninitialized_copy_aux(
                    view1.row_begin(y), view1.row_end(y), view2.row_begin(y), is_planar());
        }
        catch(...)
        {
            for (typename View1::y_coord_t y0 = 0; y0 < y; ++y0)
                detail::destruct_aux(view2.row_begin(y0), view2.row_end(y0), is_planar());
            throw;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////
// for_each_pixel
//////////////////////////////////////////////////////////////////////////////////////

/// \defgroup ImageViewSTLAlgorithmsForEachPixel for_each_pixel
/// \ingroup ImageViewSTLAlgorithms
/// \brief std::for_each for image views
///
/// For contiguous images (i.e. images that have no alignment gap at the end of each row) it is
/// more efficient to use the underlying pixel iterator that does not check for the end of rows.
/// For non-contiguous images for_each_pixel resolves to for_each of each row using the underlying
/// pixel iterator, which is still faster

/// \ingroup ImageViewSTLAlgorithmsForEachPixel
template <typename View, typename F>
F for_each_pixel(View const& view, F fun)
{
    if (view.is_1d_traversable())
    {
        return std::for_each(view.begin().x(), view.end().x(), fun);
    }
    else
    {
        for (std::ptrdiff_t y = 0; y < view.height(); ++y)
            std::for_each(view.row_begin(y), view.row_end(y), fun);
        return fun;
    }
}

/// \defgroup ImageViewSTLAlgorithmsForEachPixelPosition for_each_pixel_position
/// \ingroup ImageViewSTLAlgorithms
/// \brief adobe::for_each_position for image views (passes locators, instead of pixel references, to the function object)

/// \ingroup ImageViewSTLAlgorithmsForEachPixelPosition
template <typename View, typename F>
F for_each_pixel_position(View const& view, F fun)
{
    typename View::xy_locator loc = view.xy_at(0, 0);
    for (std::ptrdiff_t y = 0; y < view.height(); ++y)
    {
        for (std::ptrdiff_t x = 0; x < view.width(); ++x, ++loc.x())
            fun(loc);
        loc.x() -= view.width(); ++loc.y();
    }
    return fun;
}

//////////////////////////////////////////////////////////////////////////////////////
// generate_pixels
//////////////////////////////////////////////////////////////////////////////////////

/// \defgroup ImageViewSTLAlgorithmsGeneratePixels generate_pixels
/// \ingroup ImageViewSTLAlgorithms
/// \brief std::generate for image views

/// \ingroup ImageViewSTLAlgorithmsGeneratePixels
/// \brief std::generate for image views
template <typename View, typename F>
void generate_pixels(View const& view, F fun)
{
    if (view.is_1d_traversable())
    {
        std::generate(view.begin().x(), view.end().x(), fun);
    }
    else
    {
        for (std::ptrdiff_t y = 0; y < view.height(); ++y)
            std::generate(view.row_begin(y), view.row_end(y), fun);
    }
}

//////////////////////////////////////////////////////////////////////////////////////
// std::equal and gil::equal_pixels for GIL constructs
//////////////////////////////////////////////////////////////////////////////////////

/// \defgroup ImageViewSTLAlgorithmsEqualPixels equal_pixels
/// \ingroup ImageViewSTLAlgorithms
/// \brief std::equal for image views

template <typename I1, typename I2>
BOOST_FORCEINLINE
bool equal_n(I1 i1, std::ptrdiff_t n, I2 i2);

namespace detail {

template <typename I1, typename I2>
struct equal_n_fn
{
    BOOST_FORCEINLINE
    bool operator()(I1 i1, std::ptrdiff_t n, I2 i2) const
    {
        return std::equal(i1, i1 + n, i2);
    }
};

/// Equal when both ranges are interleaved and of the same type.
/// GIL pixels are bitwise comparable, so memcmp is used. User-defined pixels that are not bitwise comparable need to provide an overload
template<typename T, typename CS>
struct equal_n_fn<pixel<T, CS> const*, pixel<T, CS> const*>
{
    BOOST_FORCEINLINE
    bool operator()(pixel<T, CS> const* i1, std::ptrdiff_t n, pixel<T, CS> const* i2) const
    {
        return memcmp(i1, i2, n * sizeof(pixel<T, CS>)) == 0;
    }
};

template<typename T, typename CS>
struct equal_n_fn<pixel<T, CS>*, pixel<T, CS>*>
    : equal_n_fn<pixel<T, CS> const*, pixel<T, CS> const*>
{};

/// EqualPixels
/// Equal when both ranges are planar pointers of the same type. memcmp is invoked for each channel plane
///  User-defined channels that are not bitwise comparable need to provide an overload
template<typename IC, typename CS>
struct equal_n_fn<planar_pixel_iterator<IC, CS>, planar_pixel_iterator<IC, CS>>
{
    BOOST_FORCEINLINE
    bool operator()(planar_pixel_iterator<IC, CS> const i1, std::ptrdiff_t n, planar_pixel_iterator<IC, CS> const i2) const
    {
        // FIXME: ptrdiff_t vs size_t
        constexpr std::ptrdiff_t byte_size = n * sizeof(typename std::iterator_traits<IC>::value_type);
        for (std::ptrdiff_t i = 0; i < mp11::mp_size<CS>::value; ++i)
        {
            if (memcmp(dynamic_at_c(i1, i), dynamic_at_c(i2, i), byte_size) != 0)
                return false;
        }
        return true;
    }
};

/// Source range is delimited by image iterators
/// \tparam Loc Models ConstPixelLocatorConcept
/// \tparam It Models PixelIteratorConcept
template <typename Loc, typename It>
struct equal_n_fn<boost::gil::iterator_from_2d<Loc>, It>
{
    BOOST_FORCEINLINE
    bool operator()(boost::gil::iterator_from_2d<Loc> i1, std::ptrdiff_t n, It i2) const
    {
        gil_function_requires<boost::gil::PixelLocatorConcept<Loc>>();
        gil_function_requires<boost::gil::PixelIteratorConcept<It>>();
        while (n > 0)
        {
            std::ptrdiff_t const num = std::min<std::ptrdiff_t>(n, i1.width() - i1.x_pos());
            if (!equal_n(i1.x(), num, i2))
                return false;
            i1 += num;
            i2 += num;
            n -= num;
        }
        return true;
    }
};

/// Destination range is delimited by image iterators
/// \tparam It Models PixelIteratorConcept
/// \tparam Loc Models PixelLocatorConcept
template <typename It, typename Loc>
struct equal_n_fn<It, boost::gil::iterator_from_2d<Loc>>
{
    BOOST_FORCEINLINE
    bool operator()(It i1, std::ptrdiff_t n, boost::gil::iterator_from_2d<Loc> i2) const
    {
        gil_function_requires<boost::gil::PixelIteratorConcept<It>>();
        gil_function_requires<boost::gil::PixelLocatorConcept<Loc>>();
        while (n > 0)
        {
            std::ptrdiff_t const num = std::min<std::ptrdiff_t>(n, i2.width() - i2.x_pos());
            if (!equal_n(i1, num, i2.x()))
                return false;
            i1 += num;
            i2 += num;
            n -= num;
        }
        return true;
    }
};

/// Both source and destination ranges are delimited by image iterators
template <typename Loc1, typename Loc2>
struct equal_n_fn<boost::gil::iterator_from_2d<Loc1>,boost::gil::iterator_from_2d<Loc2>> {
   BOOST_FORCEINLINE bool operator()(boost::gil::iterator_from_2d<Loc1> i1, std::ptrdiff_t n, boost::gil::iterator_from_2d<Loc2> i2) const {
        gil_function_requires<boost::gil::PixelLocatorConcept<Loc1>>();
        gil_function_requires<boost::gil::PixelLocatorConcept<Loc2>>();
        if (i1.x_pos()!=i2.x_pos() || i1.width()!=i2.width()) {
            while(n-->0) {
                if (*i1++!=*i2++) return false;
            }
        }
        while (n>0) {
            std::ptrdiff_t num=std::min<const std::ptrdiff_t>(n,i2.width()-i2.x_pos());
            if (!equal_n(i1.x(), num, i2.x()))
                return false;
            i1+=num;
            i2+=num;
            n-=num;
        }
        return true;
    }
};
} // namespace detail

template <typename I1, typename I2> BOOST_FORCEINLINE
bool equal_n(I1 i1, std::ptrdiff_t n, I2 i2) {
    return detail::equal_n_fn<I1,I2>()(i1,n,i2);
}
} }  // namespace boost::gil

namespace std {
/// \ingroup STLOptimizations
/// \brief  std::equal(I1,I1,I2) with I1 and I2 being a iterator_from_2d
///
/// Invoked when one calls std::equal(I1,I1,I2) with I1 and I2 being a iterator_from_2d (which is
/// a 1D iterator over the pixels in an image). Attempts to demote the source and destination
/// iterators to simpler/faster types if the corresponding range is contiguous.
/// For contiguous images (i.e. images that have
/// no alignment gap at the end of each row) it is more efficient to use the underlying
/// pixel iterator that does not check for the end of rows. If the underlying pixel iterator
/// happens to be a fundamental planar/interleaved pointer, the call may further resolve
/// to memcmp. Otherwise it resolves to copying each row using the underlying pixel iterator
template <typename Loc1, typename Loc2> BOOST_FORCEINLINE
bool equal(boost::gil::iterator_from_2d<Loc1> first, boost::gil::iterator_from_2d<Loc1> last, boost::gil::iterator_from_2d<Loc2> first2) {
    boost::gil::gil_function_requires<boost::gil::PixelLocatorConcept<Loc1>>();
    boost::gil::gil_function_requires<boost::gil::PixelLocatorConcept<Loc2>>();
    std::ptrdiff_t n=last-first;
    if (first.is_1d_traversable()) {
        if (first2.is_1d_traversable())
            return boost::gil::detail::equal_n_fn<typename Loc1::x_iterator,typename Loc2::x_iterator>()(first.x(),n, first2.x());
        else
            return boost::gil::detail::equal_n_fn<typename Loc1::x_iterator,boost::gil::iterator_from_2d<Loc2>>()(first.x(),n, first2);
    } else {
        if (first2.is_1d_traversable())
            return boost::gil::detail::equal_n_fn<boost::gil::iterator_from_2d<Loc1>,typename Loc2::x_iterator>()(first,n, first2.x());
        else
            return boost::gil::detail::equal_n_fn<boost::gil::iterator_from_2d<Loc1>,boost::gil::iterator_from_2d<Loc2>>()(first,n,first2);
    }
}
} // namespace std

namespace boost { namespace gil {
/// \ingroup ImageViewSTLAlgorithmsEqualPixels
/// \brief std::equal for image views
template <typename View1, typename View2> BOOST_FORCEINLINE
bool equal_pixels(const View1& v1, const View2& v2) {
    BOOST_ASSERT(v1.dimensions() == v2.dimensions());
    return std::equal(v1.begin(),v1.end(),v2.begin()); // std::equal has overloads with GIL iterators for optimal performance
}

//////////////////////////////////////////////////////////////////////////////////////
///
/// transform_pixels
///
//////////////////////////////////////////////////////////////////////////////////////

/// \defgroup ImageViewSTLAlgorithmsTransformPixels transform_pixels
/// \ingroup ImageViewSTLAlgorithms
/// \brief std::transform for image views

/// \ingroup ImageViewSTLAlgorithmsTransformPixels
/// \brief std::transform for image views
template <typename View1, typename View2, typename F> BOOST_FORCEINLINE
F transform_pixels(const View1& src,const View2& dst, F fun) {
    BOOST_ASSERT(src.dimensions() == dst.dimensions());
    for (std::ptrdiff_t y=0; y<src.height(); ++y) {
        typename View1::x_iterator srcIt=src.row_begin(y);
        typename View2::x_iterator dstIt=dst.row_begin(y);
        for (std::ptrdiff_t x=0; x<src.width(); ++x)
            dstIt[x]=fun(srcIt[x]);
    }
    return fun;
}

/// \ingroup ImageViewSTLAlgorithmsTransformPixels
/// \brief transform_pixels with two sources
template <typename View1, typename View2, typename View3, typename F> BOOST_FORCEINLINE
F transform_pixels(const View1& src1, const View2& src2,const View3& dst, F fun) {
    for (std::ptrdiff_t y=0; y<dst.height(); ++y) {
        typename View1::x_iterator srcIt1=src1.row_begin(y);
        typename View2::x_iterator srcIt2=src2.row_begin(y);
        typename View3::x_iterator dstIt=dst.row_begin(y);
        for (std::ptrdiff_t x=0; x<dst.width(); ++x)
            dstIt[x]=fun(srcIt1[x],srcIt2[x]);
    }
    return fun;
}

/// \defgroup ImageViewSTLAlgorithmsTransformPixelPositions transform_pixel_positions
/// \ingroup ImageViewSTLAlgorithms
/// \brief adobe::transform_positions for image views (passes locators, instead of pixel references, to the function object)

/// \ingroup ImageViewSTLAlgorithmsTransformPixelPositions
/// \brief Like transform_pixels but passes to the function object pixel locators instead of pixel references
template <typename View1, typename View2, typename F> BOOST_FORCEINLINE
F transform_pixel_positions(const View1& src,const View2& dst, F fun) {
    BOOST_ASSERT(src.dimensions() == dst.dimensions());
    typename View1::xy_locator loc=src.xy_at(0,0);
    for (std::ptrdiff_t y=0; y<src.height(); ++y) {
        typename View2::x_iterator dstIt=dst.row_begin(y);
        for (std::ptrdiff_t x=0; x<src.width(); ++x, ++loc.x())
            dstIt[x]=fun(loc);
        loc.x()-=src.width(); ++loc.y();
    }
    return fun;
}

/// \ingroup ImageViewSTLAlgorithmsTransformPixelPositions
/// \brief transform_pixel_positions with two sources
template <typename View1, typename View2, typename View3, typename F> BOOST_FORCEINLINE
F transform_pixel_positions(const View1& src1,const View2& src2,const View3& dst, F fun) {
    BOOST_ASSERT(src1.dimensions() == dst.dimensions());
    BOOST_ASSERT(src2.dimensions() == dst.dimensions());
    typename View1::xy_locator loc1=src1.xy_at(0,0);
    typename View2::xy_locator loc2=src2.xy_at(0,0);
    for (std::ptrdiff_t y=0; y<src1.height(); ++y) {
        typename View3::x_iterator dstIt=dst.row_begin(y);
        for (std::ptrdiff_t x=0; x<src1.width(); ++x, ++loc1.x(), ++loc2.x())
            dstIt[x]=fun(loc1,loc2);
        loc1.x()-=src1.width(); ++loc1.y();
        loc2.x()-=src2.width(); ++loc2.y();
    }
    return fun;
}
} }  // namespace boost::gil

#endif

/* algorithm.hpp
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
*/