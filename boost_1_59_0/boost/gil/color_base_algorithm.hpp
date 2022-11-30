//
// Copyright 2005-2007 Adobe Systems Incorporated
// Copyright 2019 Mateusz Loskot <mateusz at loskot dot net>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_COLOR_BASE_ALGORITHM_HPP
#define BOOST_GIL_COLOR_BASE_ALGORITHM_HPP

#include <boost/gil/concepts.hpp>
#include <boost/gil/utilities.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <boost/config.hpp>

#include <algorithm>
#include <type_traits>

namespace boost { namespace gil {

///////////////////////////////////////
/// size:   Semantic channel size
///////////////////////////////////////

/**
\defgroup ColorBaseAlgorithmSize size
\ingroup ColorBaseAlgorithm
\brief Returns an integral constant type specifying the number of elements in a color base

Example:
\code
static_assert(size<rgb8_pixel_t>::value == 3, "");
static_assert(size<cmyk8_planar_ptr_t>::value == 4, "");
\endcode
*/

/// \brief Returns an integral constant type specifying the number of elements in a color base
/// \ingroup ColorBaseAlgorithmSize
template <typename ColorBase>
struct size : public mp11::mp_size<typename ColorBase::layout_t::color_space_t> {};

///////////////////////////////////////
/// semantic_at_c:   Semantic channel accessors
///////////////////////////////////////

/**
\defgroup ColorBaseAlgorithmSemanticAtC kth_semantic_element_type, kth_semantic_element_reference_type, kth_semantic_element_const_reference_type, semantic_at_c
\ingroup ColorBaseAlgorithm
\brief Support for accessing the elements of a color base by semantic index

The semantic index of an element is the index of its color in the color space. Semantic indexing allows for proper pairing of elements of color bases
independent on their layout. For example, red is the first semantic element of a color base regardless of whether it has an RGB layout or a BGR layout.
All GIL color base algorithms taking multiple color bases use semantic indexing to access their elements.

Example:
\code
// 16-bit BGR pixel, 4 bits for the blue, 3 bits for the green, 2 bits for the red channel and 7 unused bits
using bgr432_pixel_t = packed_pixel_type<uint16_t, mp11::mp_list_c<unsigned,4,3,2>, bgr_layout_t>::type;

// A reference to its red channel. Although the red channel is the third, its semantic index is 0 in the RGB color space
using red_channel_reference_t = kth_semantic_element_reference_type<bgr432_pixel_t, 0>::type;

// Initialize the pixel to black
bgr432_pixel_t red_pixel(0,0,0);

// Set the red channel to 100%
red_channel_reference_t red_channel = semantic_at_c<0>(red_pixel);
red_channel = channel_traits<red_channel_reference_t>::max_value();

\endcode
*/
/// \brief Specifies the type of the K-th semantic element of a color base
/// \ingroup ColorBaseAlgorithmSemanticAtC
template <typename ColorBase, int K>
struct kth_semantic_element_type
{
    using channel_mapping_t = typename ColorBase::layout_t::channel_mapping_t;
    static_assert(K < mp11::mp_size<channel_mapping_t>::value,
        "K index should be less than size of channel_mapping_t sequence");

    static constexpr int semantic_index = mp11::mp_at_c<channel_mapping_t, K>::type::value;
    using type = typename kth_element_type<ColorBase, semantic_index>::type;
};

/// \brief Specifies the return type of the mutable semantic_at_c<K>(color_base);
/// \ingroup ColorBaseAlgorithmSemanticAtC
template <typename ColorBase, int K>
struct kth_semantic_element_reference_type
{
    using channel_mapping_t = typename ColorBase::layout_t::channel_mapping_t;
    static_assert(K < mp11::mp_size<channel_mapping_t>::value,
        "K index should be less than size of channel_mapping_t sequence");

    static constexpr int semantic_index = mp11::mp_at_c<channel_mapping_t, K>::type::value;
    using type = typename kth_element_reference_type<ColorBase, semantic_index>::type;
    static type get(ColorBase& cb) { return gil::at_c<semantic_index>(cb); }
};

/// \brief Specifies the return type of the constant semantic_at_c<K>(color_base);
/// \ingroup ColorBaseAlgorithmSemanticAtC
template <typename ColorBase, int K>
struct kth_semantic_element_const_reference_type
{
    using channel_mapping_t = typename ColorBase::layout_t::channel_mapping_t;
    static_assert(K < mp11::mp_size<channel_mapping_t>::value,
        "K index should be less than size of channel_mapping_t sequence");

    static constexpr int semantic_index = mp11::mp_at_c<channel_mapping_t, K>::type::value;
    using type = typename kth_element_const_reference_type<ColorBase,semantic_index>::type;
    static type get(const ColorBase& cb) { return gil::at_c<semantic_index>(cb); }
};

/// \brief A mutable accessor to the K-th semantic element of a color base
/// \ingroup ColorBaseAlgorithmSemanticAtC
template <int K, typename ColorBase>
inline
auto semantic_at_c(ColorBase& p)
    -> typename std::enable_if
    <
        !std::is_const<ColorBase>::value,
        typename kth_semantic_element_reference_type<ColorBase, K>::type
    >::type
{
    return kth_semantic_element_reference_type<ColorBase, K>::get(p);
}

/// \brief A constant accessor to the K-th semantic element of a color base
/// \ingroup ColorBaseAlgorithmSemanticAtC
template <int K, typename ColorBase>
inline
auto semantic_at_c(ColorBase const& p)
    -> typename kth_semantic_element_const_reference_type<ColorBase, K>::type
{
    return kth_semantic_element_const_reference_type<ColorBase, K>::get(p);
}

///////////////////////////////////////
/// get_color:   Named channel accessors
///////////////////////////////////////

/**
\defgroup ColorBaseAlgorithmColor color_element_type, color_element_reference_type, color_element_const_reference_type, get_color, contains_color
\ingroup ColorBaseAlgorithm
\brief Support for accessing the elements of a color base by color name

Example: A function that takes a generic pixel containing a red channel and sets it to 100%:

\code
template <typename Pixel>
void set_red_to_max(Pixel& pixel) {
    boost::function_requires<MutablePixelConcept<Pixel> >();
    static_assert(contains_color<Pixel, red_t>::value, "");

    using red_channel_t = typename color_element_type<Pixel, red_t>::type;
    get_color(pixel, red_t()) = channel_traits<red_channel_t>::max_value();
}
\endcode
*/

/// \brief A predicate metafunction determining whether a given color base contains a given color
/// \ingroup ColorBaseAlgorithmColor
template <typename ColorBase, typename Color>
struct contains_color
    : mp11::mp_contains<typename ColorBase::layout_t::color_space_t, Color>
{};

template <typename ColorBase, typename Color>
struct color_index_type : public detail::type_to_index<typename ColorBase::layout_t::color_space_t,Color> {};

/// \brief Specifies the type of the element associated with a given color tag
/// \ingroup ColorBaseAlgorithmColor
template <typename ColorBase, typename Color>
struct color_element_type : public kth_semantic_element_type<ColorBase,color_index_type<ColorBase,Color>::value> {};

/// \brief Specifies the return type of the mutable element accessor by color name, get_color(color_base, Color());
/// \ingroup ColorBaseAlgorithmColor
template <typename ColorBase, typename Color>
struct color_element_reference_type : public kth_semantic_element_reference_type<ColorBase,color_index_type<ColorBase,Color>::value> {};

/// \brief Specifies the return type of the constant element accessor by color name, get_color(color_base, Color());
/// \ingroup ColorBaseAlgorithmColor
template <typename ColorBase, typename Color>
struct color_element_const_reference_type : public kth_semantic_element_const_reference_type<ColorBase,color_index_type<ColorBase,Color>::value> {};

/// \brief Mutable accessor to the element associated with a given color name
/// \ingroup ColorBaseAlgorithmColor
template <typename ColorBase, typename Color>
typename color_element_reference_type<ColorBase,Color>::type get_color(ColorBase& cb, Color=Color()) {
    return color_element_reference_type<ColorBase,Color>::get(cb);
}

/// \brief Constant accessor to the element associated with a given color name
/// \ingroup ColorBaseAlgorithmColor
template <typename ColorBase, typename Color>
typename color_element_const_reference_type<ColorBase,Color>::type get_color(const ColorBase& cb, Color=Color()) {
    return color_element_const_reference_type<ColorBase,Color>::get(cb);
}

///////////////////////////////////////
///
/// element_type, element_reference_type, element_const_reference_type: Support for homogeneous color bases
///
///////////////////////////////////////

/**
\defgroup ColorBaseAlgorithmHomogeneous element_type, element_reference_type, element_const_reference_type
\ingroup ColorBaseAlgorithm
\brief Types for homogeneous color bases

Example:
\code
using element_t = element_type<rgb8c_planar_ptr_t>::type;
static_assert(std::is_same<element_t, const uint8_t*>::value, "");
\endcode
*/
/// \brief Specifies the element type of a homogeneous color base
/// \ingroup ColorBaseAlgorithmHomogeneous
template <typename ColorBase>
struct element_type : public kth_element_type<ColorBase, 0> {};

/// \brief Specifies the return type of the mutable element accessor at_c of a homogeneous color base
/// \ingroup ColorBaseAlgorithmHomogeneous
template <typename ColorBase>
struct element_reference_type : public kth_element_reference_type<ColorBase, 0> {};

/// \brief Specifies the return type of the constant element accessor at_c of a homogeneous color base
/// \ingroup ColorBaseAlgorithmHomogeneous
template <typename ColorBase>
struct element_const_reference_type : public kth_element_const_reference_type<ColorBase, 0> {};


namespace detail {

// compile-time recursion for per-element operations on color bases
template <int N>
struct element_recursion
{

#if defined(BOOST_GCC) && (BOOST_GCC >= 40900)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif

    template <typename P1,typename P2>
    static bool static_equal(const P1& p1, const P2& p2)
    {
        return element_recursion<N-1>::static_equal(p1,p2) &&
               semantic_at_c<N-1>(p1)==semantic_at_c<N-1>(p2);
    }

    template <typename P1,typename P2>
    static void static_copy(const P1& p1, P2& p2)
    {
        element_recursion<N-1>::static_copy(p1,p2);
        semantic_at_c<N-1>(p2)=semantic_at_c<N-1>(p1);
    }

    template <typename P,typename T2>
    static void static_fill(P& p, T2 v)
    {
        element_recursion<N-1>::static_fill(p,v);
        semantic_at_c<N-1>(p)=v;
    }

    template <typename Dst,typename Op>
    static void static_generate(Dst& dst, Op op)
    {
        element_recursion<N-1>::static_generate(dst,op);
        semantic_at_c<N-1>(dst)=op();
    }

#if defined(BOOST_GCC) && (BOOST_GCC >= 40900)
#pragma GCC diagnostic pop
#endif

    //static_for_each with one source
    template <typename P1,typename Op>
    static Op static_for_each(P1& p1, Op op) {
        Op op2(element_recursion<N-1>::static_for_each(p1,op));
        op2(semantic_at_c<N-1>(p1));
        return op2;
    }
    template <typename P1,typename Op>
    static Op static_for_each(const P1& p1, Op op) {
        Op op2(element_recursion<N-1>::static_for_each(p1,op));
        op2(semantic_at_c<N-1>(p1));
        return op2;
    }
    //static_for_each with two sources
    template <typename P1,typename P2,typename Op>
    static Op static_for_each(P1& p1, P2& p2, Op op) {
        Op op2(element_recursion<N-1>::static_for_each(p1,p2,op));
        op2(semantic_at_c<N-1>(p1), semantic_at_c<N-1>(p2));
        return op2;
    }
    template <typename P1,typename P2,typename Op>
    static Op static_for_each(P1& p1, const P2& p2, Op op) {
        Op op2(element_recursion<N-1>::static_for_each(p1,p2,op));
        op2(semantic_at_c<N-1>(p1), semantic_at_c<N-1>(p2));
        return op2;
    }
    template <typename P1,typename P2,typename Op>
    static Op static_for_each(const P1& p1, P2& p2, Op op) {
        Op op2(element_recursion<N-1>::static_for_each(p1,p2,op));
        op2(semantic_at_c<N-1>(p1), semantic_at_c<N-1>(p2));
        return op2;
    }
    template <typename P1,typename P2,typename Op>
    static Op static_for_each(const P1& p1, const P2& p2, Op op) {
        Op op2(element_recursion<N-1>::static_for_each(p1,p2,op));
        op2(semantic_at_c<N-1>(p1), semantic_at_c<N-1>(p2));
        return op2;
    }
    //static_for_each with three sources
    template <typename P1,typename P2,typename P3,typename Op>
    static Op static_for_each(P1& p1, P2& p2, P3& p3, Op op) {
        Op op2(element_recursion<N-1>::static_for_each(p1,p2,p3,op));
        op2(semantic_at_c<N-1>(p1), semantic_at_c<N-1>(p2), semantic_at_c<N-1>(p3));
        return op2;
    }
    template <typename P1,typename P2,typename P3,typename Op>
    static Op static_for_each(P1& p1, P2& p2, const P3& p3, Op op) {
        Op op2(element_recursion<N-1>::static_for_each(p1,p2,p3,op));
        op2(semantic_at_c<N-1>(p1), semantic_at_c<N-1>(p2), semantic_at_c<N-1>(p3));
        return op2;
    }
    template <typename P1,typename P2,typename P3,typename Op>
    static Op static_for_each(P1& p1, const P2& p2, P3& p3, Op op) {
        Op op2(element_recursion<N-1>::static_for_each(p1,p2,p3,op));
        op2(semantic_at_c<N-1>(p1), semantic_at_c<N-1>(p2), semantic_at_c<N-1>(p3));
        return op2;
    }
    template <typename P1,typename P2,typename P3,typename Op>
    static Op static_for_each(P1& p1, const P2& p2, const P3& p3, Op op) {
        Op op2(element_recursion<N-1>::static_for_each(p1,p2,p3,op));
        op2(semantic_at_c<N-1>(p1), semantic_at_c<N-1>(p2), semantic_at_c<N-1>(p3));
        return op2;
    }
    template <typename P1,typename P2,typename P3,typename Op>
    static Op static_for_each(const P1& p1, P2& p2, P3& p3, Op op) {
        Op op2(element_recursion<N-1>::static_for_each(p1,p2,p3,op));
        op2(semantic_at_c<N-1>(p1), semantic_at_c<N-1>(p2), semantic_at_c<N-1>(p3));
        return op2;
    }
    template <typename P1,typename P2,typename P3,typename Op>
    static Op static_for_each(const P1& p1, P2& p2, const P3& p3, Op op) {
        Op op2(element_recursion<N-1>::static_for_each(p1,p2,p3,op));
        op2(semantic_at_c<N-1>(p1), semantic_at_c<N-1>(p2), semantic_at_c<N-1>(p3));
        return op2;
    }
    template <typename P1,typename P2,typename P3,typename Op>
    static Op static_for_each(const P1& p1, const P2& p2, P3& p3, Op op) {
        Op op2(element_recursion<N-1>::static_for_each(p1,p2,p3,op));
        op2(semantic_at_c<N-1>(p1), semantic_at_c<N-1>(p2), semantic_at_c<N-1>(p3));
        return op2;
    }
    template <typename P1,typename P2,typename P3,typename Op>
    static Op static_for_each(const P1& p1, const P2& p2, const P3& p3, Op op) {
        Op op2(element_recursion<N-1>::static_for_each(p1,p2,p3,op));
        op2(semantic_at_c<N-1>(p1), semantic_at_c<N-1>(p2), semantic_at_c<N-1>(p3));
        return op2;
    }
    //static_transform with one source
    template <typename P1,typename Dst,typename Op>
    static Op static_transform(P1& src, Dst& dst, Op op) {
        Op op2(element_recursion<N-1>::static_transform(src,dst,op));
        semantic_at_c<N-1>(dst)=op2(semantic_at_c<N-1>(src));
        return op2;
    }
    template <typename P1,typename Dst,typename Op>
    static Op static_transform(const P1& src, Dst& dst, Op op) {
        Op op2(element_recursion<N-1>::static_transform(src,dst,op));
        semantic_at_c<N-1>(dst)=op2(semantic_at_c<N-1>(src));
        return op2;
    }
    //static_transform with two sources
    template <typename P1,typename P2,typename Dst,typename Op>
    static Op static_transform(P1& src1, P2& src2, Dst& dst, Op op) {
        Op op2(element_recursion<N-1>::static_transform(src1,src2,dst,op));
        semantic_at_c<N-1>(dst)=op2(semantic_at_c<N-1>(src1), semantic_at_c<N-1>(src2));
        return op2;
    }
    template <typename P1,typename P2,typename Dst,typename Op>
    static Op static_transform(P1& src1, const P2& src2, Dst& dst, Op op) {
        Op op2(element_recursion<N-1>::static_transform(src1,src2,dst,op));
        semantic_at_c<N-1>(dst)=op2(semantic_at_c<N-1>(src1), semantic_at_c<N-1>(src2));
        return op2;
    }
    template <typename P1,typename P2,typename Dst,typename Op>
    static Op static_transform(const P1& src1, P2& src2, Dst& dst, Op op) {
        Op op2(element_recursion<N-1>::static_transform(src1,src2,dst,op));
        semantic_at_c<N-1>(dst)=op2(semantic_at_c<N-1>(src1), semantic_at_c<N-1>(src2));
        return op2;
    }
    template <typename P1,typename P2,typename Dst,typename Op>
    static Op static_transform(const P1& src1, const P2& src2, Dst& dst, Op op) {
        Op op2(element_recursion<N-1>::static_transform(src1,src2,dst,op));
        semantic_at_c<N-1>(dst)=op2(semantic_at_c<N-1>(src1), semantic_at_c<N-1>(src2));
        return op2;
    }
};

// Termination condition of the compile-time recursion for element operations on a color base
template<> struct element_recursion<0> {
    //static_equal
    template <typename P1,typename P2>
    static bool static_equal(const P1&, const P2&) { return true; }
    //static_copy
    template <typename P1,typename P2>
    static void static_copy(const P1&, const P2&) {}
    //static_fill
    template <typename P, typename T2>
    static void static_fill(const P&, T2) {}
    //static_generate
    template <typename Dst,typename Op>
    static void static_generate(const Dst&,Op){}
    //static_for_each with one source
    template <typename P1,typename Op>
    static Op static_for_each(const P1&,Op op){return op;}
    //static_for_each with two sources
    template <typename P1,typename P2,typename Op>
    static Op static_for_each(const P1&,const P2&,Op op){return op;}
    //static_for_each with three sources
    template <typename P1,typename P2,typename P3,typename Op>
    static Op static_for_each(const P1&,const P2&,const P3&,Op op){return op;}
    //static_transform with one source
    template <typename P1,typename Dst,typename Op>
    static Op static_transform(const P1&,const Dst&,Op op){return op;}
    //static_transform with two sources
    template <typename P1,typename P2,typename Dst,typename Op>
    static Op static_transform(const P1&,const P2&,const Dst&,Op op){return op;}
};

// std::min and std::max don't have the mutable overloads...
template <typename Q> inline const Q& mutable_min(const Q& x, const Q& y) { return x<y ? x : y; }
template <typename Q> inline       Q& mutable_min(      Q& x,       Q& y) { return x<y ? x : y; }
template <typename Q> inline const Q& mutable_max(const Q& x, const Q& y) { return x<y ? y : x; }
template <typename Q> inline       Q& mutable_max(      Q& x,       Q& y) { return x<y ? y : x; }


// compile-time recursion for min/max element
template <int N>
struct min_max_recur {
    template <typename P> static typename element_const_reference_type<P>::type max_(const P& p) {
        return mutable_max(min_max_recur<N-1>::max_(p),semantic_at_c<N-1>(p));
    }
    template <typename P> static typename element_reference_type<P>::type       max_(      P& p) {
        return mutable_max(min_max_recur<N-1>::max_(p),semantic_at_c<N-1>(p));
    }
    template <typename P> static typename element_const_reference_type<P>::type min_(const P& p) {
        return mutable_min(min_max_recur<N-1>::min_(p),semantic_at_c<N-1>(p));
    }
    template <typename P> static typename element_reference_type<P>::type       min_(      P& p) {
        return mutable_min(min_max_recur<N-1>::min_(p),semantic_at_c<N-1>(p));
    }
};

// termination condition of the compile-time recursion for min/max element
template <>
struct min_max_recur<1> {
    template <typename P> static typename element_const_reference_type<P>::type max_(const P& p) { return semantic_at_c<0>(p); }
    template <typename P> static typename element_reference_type<P>::type       max_(      P& p) { return semantic_at_c<0>(p); }
    template <typename P> static typename element_const_reference_type<P>::type min_(const P& p) { return semantic_at_c<0>(p); }
    template <typename P> static typename element_reference_type<P>::type       min_(      P& p) { return semantic_at_c<0>(p); }
};
}  // namespace detail

/// \defgroup ColorBaseAlgorithmMinMax static_min, static_max
/// \ingroup ColorBaseAlgorithm
/// \brief Equivalents to std::min_element and std::max_element for homogeneous color bases
///
/// Example:
/// \code
/// rgb8_pixel_t pixel(10,20,30);
/// assert(pixel[2] == 30);
/// static_max(pixel) = static_min(pixel);
/// assert(pixel[2] == 10);
/// \endcode
/// \{

template <typename P>
BOOST_FORCEINLINE
typename element_const_reference_type<P>::type static_max(const P& p) { return detail::min_max_recur<size<P>::value>::max_(p); }

template <typename P>
BOOST_FORCEINLINE
typename element_reference_type<P>::type       static_max(      P& p) { return detail::min_max_recur<size<P>::value>::max_(p); }

template <typename P>
BOOST_FORCEINLINE
typename element_const_reference_type<P>::type static_min(const P& p) { return detail::min_max_recur<size<P>::value>::min_(p); }

template <typename P>
BOOST_FORCEINLINE
typename element_reference_type<P>::type       static_min(      P& p) { return detail::min_max_recur<size<P>::value>::min_(p); }
/// \}

/// \defgroup ColorBaseAlgorithmEqual static_equal
/// \ingroup ColorBaseAlgorithm
/// \brief Equivalent to std::equal. Pairs the elements semantically
///
/// Example:
/// \code
/// rgb8_pixel_t rgb_red(255,0,0);
/// bgr8_pixel_t bgr_red(0,0,255);
/// assert(rgb_red[0]==255 && bgr_red[0]==0);
///
/// assert(static_equal(rgb_red,bgr_red));
/// assert(rgb_red==bgr_red);  // operator== invokes static_equal
/// \endcode
/// \{

template <typename P1,typename P2>
BOOST_FORCEINLINE
bool static_equal(const P1& p1, const P2& p2) { return detail::element_recursion<size<P1>::value>::static_equal(p1,p2); }

/// \}

/// \defgroup ColorBaseAlgorithmCopy static_copy
/// \ingroup ColorBaseAlgorithm
/// \brief Equivalent to std::copy. Pairs the elements semantically
///
/// Example:
/// \code
/// rgb8_pixel_t rgb_red(255,0,0);
/// bgr8_pixel_t bgr_red;
/// static_copy(rgb_red, bgr_red);  // same as bgr_red = rgb_red
///
/// assert(rgb_red[0] == 255 && bgr_red[0] == 0);
/// assert(rgb_red == bgr_red);
/// \endcode
/// \{

template <typename Src,typename Dst>
BOOST_FORCEINLINE
void static_copy(const Src& src, Dst& dst)
{
    detail::element_recursion<size<Dst>::value>::static_copy(src, dst);
}

/// \}

/// \defgroup ColorBaseAlgorithmFill static_fill
/// \ingroup ColorBaseAlgorithm
/// \brief Equivalent to std::fill.
///
/// Example:
/// \code
/// rgb8_pixel_t p;
/// static_fill(p, 10);
/// assert(p == rgb8_pixel_t(10,10,10));
/// \endcode
/// \{

template <typename P,typename V>
BOOST_FORCEINLINE
void static_fill(P& p, const V& v)
{
    detail::element_recursion<size<P>::value>::static_fill(p,v);
}

/// \}

/// \defgroup ColorBaseAlgorithmGenerate static_generate
/// \ingroup ColorBaseAlgorithm
/// \brief Equivalent to std::generate.
///
/// Example: Set each channel of a pixel to its semantic index. The channels must be assignable from an integer.
/// \code
/// struct consecutive_fn {
///     int& _current;
///     consecutive_fn(int& start) : _current(start) {}
///     int operator()() { return _current++; }
/// };
/// rgb8_pixel_t p;
/// int start=0;
/// static_generate(p, consecutive_fn(start));
/// assert(p == rgb8_pixel_t(0,1,2));
/// \endcode
///
/// \{

template <typename P1,typename Op>
BOOST_FORCEINLINE
void static_generate(P1& dst,Op op)                      { detail::element_recursion<size<P1>::value>::static_generate(dst,op); }
/// \}

/// \defgroup ColorBaseAlgorithmTransform static_transform
/// \ingroup ColorBaseAlgorithm
/// \brief Equivalent to std::transform. Pairs the elements semantically
///
/// Example: Write a generic function that adds two pixels into a homogeneous result pixel.
/// \code
/// template <typename Result>
/// struct my_plus {
///     template <typename T1, typename T2>
///     Result operator()(T1 f1, T2 f2) const { return f1+f2; }
/// };
///
/// template <typename Pixel1, typename Pixel2, typename Pixel3>
/// void sum_channels(const Pixel1& p1, const Pixel2& p2, Pixel3& result) {
///     using result_channel_t = typename channel_type<Pixel3>::type;
///     static_transform(p1,p2,result,my_plus<result_channel_t>());
/// }
///
/// rgb8_pixel_t p1(1,2,3);
/// bgr8_pixel_t p2(3,2,1);
/// rgb8_pixel_t result;
/// sum_channels(p1,p2,result);
/// assert(result == rgb8_pixel_t(2,4,6));
/// \endcode
/// \{

//static_transform with one source
template <typename Src,typename Dst,typename Op>
BOOST_FORCEINLINE
Op static_transform(Src& src,Dst& dst,Op op)              { return detail::element_recursion<size<Dst>::value>::static_transform(src,dst,op); }
template <typename Src,typename Dst,typename Op>
BOOST_FORCEINLINE
Op static_transform(const Src& src,Dst& dst,Op op)              { return detail::element_recursion<size<Dst>::value>::static_transform(src,dst,op); }
//static_transform with two sources
template <typename P2,typename P3,typename Dst,typename Op>
BOOST_FORCEINLINE
Op static_transform(P2& p2,P3& p3,Dst& dst,Op op) { return detail::element_recursion<size<Dst>::value>::static_transform(p2,p3,dst,op); }
template <typename P2,typename P3,typename Dst,typename Op>
BOOST_FORCEINLINE
Op static_transform(P2& p2,const P3& p3,Dst& dst,Op op) { return detail::element_recursion<size<Dst>::value>::static_transform(p2,p3,dst,op); }
template <typename P2,typename P3,typename Dst,typename Op>
BOOST_FORCEINLINE
Op static_transform(const P2& p2,P3& p3,Dst& dst,Op op) { return detail::element_recursion<size<Dst>::value>::static_transform(p2,p3,dst,op); }
template <typename P2,typename P3,typename Dst,typename Op>
BOOST_FORCEINLINE
Op static_transform(const P2& p2,const P3& p3,Dst& dst,Op op) { return detail::element_recursion<size<Dst>::value>::static_transform(p2,p3,dst,op); }
/// \}

/// \defgroup ColorBaseAlgorithmForEach static_for_each
/// \ingroup ColorBaseAlgorithm
/// \brief Equivalent to std::for_each. Pairs the elements semantically
///
/// Example: Use static_for_each to increment a planar pixel iterator
/// \code
/// struct increment {
///     template <typename Incrementable>
///     void operator()(Incrementable& x) const { ++x; }
/// };
///
/// template <typename ColorBase>
/// void increment_elements(ColorBase& cb) {
///     static_for_each(cb, increment());
/// }
///
/// uint8_t red[2], green[2], blue[2];
/// rgb8c_planar_ptr_t p1(red,green,blue);
/// rgb8c_planar_ptr_t p2=p1;
/// increment_elements(p1);
/// ++p2;
/// assert(p1 == p2);
/// \endcode
/// \{

//static_for_each with one source
template <typename P1,typename Op>
BOOST_FORCEINLINE
Op static_for_each(      P1& p1, Op op)                          { return detail::element_recursion<size<P1>::value>::static_for_each(p1,op); }
template <typename P1,typename Op>
BOOST_FORCEINLINE
Op static_for_each(const P1& p1, Op op)                          { return detail::element_recursion<size<P1>::value>::static_for_each(p1,op); }
//static_for_each with two sources
template <typename P1,typename P2,typename Op>
BOOST_FORCEINLINE
Op static_for_each(P1& p1,      P2& p2, Op op)             { return detail::element_recursion<size<P1>::value>::static_for_each(p1,p2,op); }
template <typename P1,typename P2,typename Op>
BOOST_FORCEINLINE
Op static_for_each(P1& p1,const P2& p2, Op op)             { return detail::element_recursion<size<P1>::value>::static_for_each(p1,p2,op); }
template <typename P1,typename P2,typename Op>
BOOST_FORCEINLINE
Op static_for_each(const P1& p1,      P2& p2, Op op)             { return detail::element_recursion<size<P1>::value>::static_for_each(p1,p2,op); }
template <typename P1,typename P2,typename Op>
BOOST_FORCEINLINE
Op static_for_each(const P1& p1,const P2& p2, Op op)             { return detail::element_recursion<size<P1>::value>::static_for_each(p1,p2,op); }
//static_for_each with three sources
template <typename P1,typename P2,typename P3,typename Op>
BOOST_FORCEINLINE
Op static_for_each(P1& p1,P2& p2,P3& p3,Op op) { return detail::element_recursion<size<P1>::value>::static_for_each(p1,p2,p3,op); }
template <typename P1,typename P2,typename P3,typename Op>
BOOST_FORCEINLINE
Op static_for_each(P1& p1,P2& p2,const P3& p3,Op op) { return detail::element_recursion<size<P1>::value>::static_for_each(p1,p2,p3,op); }
template <typename P1,typename P2,typename P3,typename Op>
BOOST_FORCEINLINE
Op static_for_each(P1& p1,const P2& p2,P3& p3,Op op) { return detail::element_recursion<size<P1>::value>::static_for_each(p1,p2,p3,op); }
template <typename P1,typename P2,typename P3,typename Op>
BOOST_FORCEINLINE
Op static_for_each(P1& p1,const P2& p2,const P3& p3,Op op) { return detail::element_recursion<size<P1>::value>::static_for_each(p1,p2,p3,op); }
template <typename P1,typename P2,typename P3,typename Op>
BOOST_FORCEINLINE
Op static_for_each(const P1& p1,P2& p2,P3& p3,Op op) { return detail::element_recursion<size<P1>::value>::static_for_each(p1,p2,p3,op); }
template <typename P1,typename P2,typename P3,typename Op>
BOOST_FORCEINLINE
Op static_for_each(const P1& p1,P2& p2,const P3& p3,Op op) { return detail::element_recursion<size<P1>::value>::static_for_each(p1,p2,p3,op); }
template <typename P1,typename P2,typename P3,typename Op>
BOOST_FORCEINLINE
Op static_for_each(const P1& p1,const P2& p2,P3& p3,Op op) { return detail::element_recursion<size<P1>::value>::static_for_each(p1,p2,p3,op); }
template <typename P1,typename P2,typename P3,typename Op>
BOOST_FORCEINLINE
Op static_for_each(const P1& p1,const P2& p2,const P3& p3,Op op) { return detail::element_recursion<size<P1>::value>::static_for_each(p1,p2,p3,op); }
///\}

} }  // namespace boost::gil

#endif

/* color_base_algorithm.hpp
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
*/