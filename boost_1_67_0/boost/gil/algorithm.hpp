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