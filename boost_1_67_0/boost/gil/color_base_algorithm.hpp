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