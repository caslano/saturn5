//
// Copyright 2005-2007 Adobe Systems Incorporated
// Copyright 2019 Mateusz Loskot <mateusz at loskot dot net>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_COLOR_BASE_HPP
#define BOOST_GIL_COLOR_BASE_HPP

#include <boost/gil/utilities.hpp>
#include <boost/gil/concepts.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <type_traits>

namespace boost { namespace gil {

// Forward-declare
template <typename P> P* memunit_advanced(const P* p, std::ptrdiff_t diff);

// Forward-declare semantic_at_c
template <int K, typename ColorBase>
auto semantic_at_c(ColorBase& p)
    -> typename std::enable_if
    <
        !std::is_const<ColorBase>::value,
        typename kth_semantic_element_reference_type<ColorBase, K>::type
    >::type;


template <int K, typename ColorBase>
typename kth_semantic_element_const_reference_type<ColorBase,K>::type semantic_at_c(const ColorBase& p);

// Forward declare element_reference_type
template <typename ColorBase> struct element_reference_type;
template <typename ColorBase> struct element_const_reference_type;
template <typename ColorBase, int K> struct kth_element_type;
template <typename ColorBase, int K> struct kth_element_type<const ColorBase,K> : public kth_element_type<ColorBase,K> {};
template <typename ColorBase, int K> struct kth_element_reference_type;
template <typename ColorBase, int K> struct kth_element_reference_type<const ColorBase,K> : public kth_element_reference_type<ColorBase,K> {};
template <typename ColorBase, int K> struct kth_element_const_reference_type;
template <typename ColorBase, int K> struct kth_element_const_reference_type<const ColorBase,K> : public kth_element_const_reference_type<ColorBase,K> {};

namespace detail {

template <typename DstLayout, typename SrcLayout, int K>
struct mapping_transform : mp11::mp_at
    <
        typename SrcLayout::channel_mapping_t,
        typename detail::type_to_index
        <
            typename DstLayout::channel_mapping_t,
            std::integral_constant<int, K>
        >
    >::type
{};

/// \defgroup ColorBaseModelHomogeneous detail::homogeneous_color_base
/// \ingroup ColorBaseModel
/// \brief A homogeneous color base holding one color element.
/// Models HomogeneousColorBaseConcept or HomogeneousColorBaseValueConcept
/// If the element type models Regular, this class models HomogeneousColorBaseValueConcept.

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

/// \brief A homogeneous color base holding one color element.
/// Models HomogeneousColorBaseConcept or HomogeneousColorBaseValueConcept
/// \ingroup ColorBaseModelHomogeneous
template <typename Element, typename Layout>
struct homogeneous_color_base<Element, Layout, 1>
{
    using layout_t = Layout;

    homogeneous_color_base() = default;
    homogeneous_color_base(Element v) : v0_(v) {}

    template <typename E2, typename L2>
    homogeneous_color_base(homogeneous_color_base<E2, L2, 1> const& c)
        : v0_(gil::at_c<0>(c))
    {}

    auto at(std::integral_constant<int, 0>)
        -> typename element_reference_type<homogeneous_color_base>::type
    { return v0_; }

    auto at(std::integral_constant<int, 0>) const
        -> typename element_const_reference_type<homogeneous_color_base>::type
    { return v0_; }

    // grayscale pixel values are convertible to channel type
    // FIXME: explicit?
    operator Element() const { return v0_; }

private:
    Element v0_{};
};

/// \brief A homogeneous color base holding two color elements
/// Models HomogeneousColorBaseConcept or HomogeneousColorBaseValueConcept
/// \ingroup ColorBaseModelHomogeneous
template <typename Element, typename Layout>
struct homogeneous_color_base<Element, Layout, 2>
{
    using layout_t = Layout;

    homogeneous_color_base() = default;
    explicit homogeneous_color_base(Element v) : v0_(v), v1_(v) {}
    homogeneous_color_base(Element v0, Element v1) : v0_(v0), v1_(v1) {}

    template <typename E2, typename L2>
    homogeneous_color_base(homogeneous_color_base<E2, L2, 2> const& c)
        : v0_(gil::at_c<mapping_transform<Layout, L2, 0>::value>(c))
        , v1_(gil::at_c<mapping_transform<Layout, L2, 1>::value>(c))
    {}

    // Support for l-value reference proxy copy construction
    template <typename E2, typename L2>
    homogeneous_color_base(homogeneous_color_base<E2, L2, 2>& c)
        : v0_(gil::at_c<mapping_transform<Layout, L2, 0>::value>(c))
        , v1_(gil::at_c<mapping_transform<Layout, L2, 1>::value>(c))
    {}

    // Support for planar_pixel_iterator construction and dereferencing
    template <typename P>
    homogeneous_color_base(P* p, bool)
        : v0_(&semantic_at_c<0>(*p))
        , v1_(&semantic_at_c<1>(*p))
    {}

    // Support for planar_pixel_reference offset constructor
    template <typename Ptr>
    homogeneous_color_base(Ptr const& ptr, std::ptrdiff_t diff)
        : v0_(*memunit_advanced(semantic_at_c<0>(ptr), diff))
        , v1_(*memunit_advanced(semantic_at_c<1>(ptr), diff))
    {}

    template <typename Ref>
    Ref deref() const
    {
        return Ref(*semantic_at_c<0>(*this), *semantic_at_c<1>(*this));
    }

    auto at(std::integral_constant<int, 0>)
        -> typename element_reference_type<homogeneous_color_base>::type
    { return v0_; }

    auto at(std::integral_constant<int, 0>) const
        -> typename element_const_reference_type<homogeneous_color_base>::type
    { return v0_; }

    auto at(std::integral_constant<int, 1>)
        -> typename element_reference_type<homogeneous_color_base>::type
    { return v1_; }

    auto at(std::integral_constant<int, 1>) const
        -> typename element_const_reference_type<homogeneous_color_base>::type
    { return v1_; }

    // Support for planar_pixel_reference operator[]
    Element at_c_dynamic(std::size_t i) const
    {
        if (i == 0)
            return v0_;
        else
            return v1_;
    }

private:
    Element v0_{};
    Element v1_{};
};

/// \brief A homogeneous color base holding three color elements.
/// Models HomogeneousColorBaseConcept or HomogeneousColorBaseValueConcept
/// \ingroup ColorBaseModelHomogeneous
template <typename Element, typename Layout>
struct homogeneous_color_base<Element, Layout, 3>
{
    using layout_t = Layout;

    homogeneous_color_base() = default;
    explicit homogeneous_color_base(Element v) : v0_(v), v1_(v), v2_(v) {}
    homogeneous_color_base(Element v0, Element v1, Element v2)
        : v0_(v0), v1_(v1), v2_(v2)
    {}

    template <typename E2, typename L2>
    homogeneous_color_base(homogeneous_color_base<E2, L2, 3> const& c)
        : v0_(gil::at_c<mapping_transform<Layout, L2, 0>::value>(c))
        , v1_(gil::at_c<mapping_transform<Layout, L2, 1>::value>(c))
        , v2_(gil::at_c<mapping_transform<Layout, L2, 2>::value>(c))
    {}

    // Support for l-value reference proxy copy construction
    template <typename E2, typename L2>
    homogeneous_color_base(homogeneous_color_base<E2, L2, 3>& c)
        : v0_(gil::at_c<mapping_transform<Layout, L2, 0>::value>(c))
        , v1_(gil::at_c<mapping_transform<Layout, L2, 1>::value>(c))
        , v2_(gil::at_c<mapping_transform<Layout, L2, 2>::value>(c))
    {}

    // Support for planar_pixel_iterator construction and dereferencing
    template <typename P>
    homogeneous_color_base(P* p, bool)
        : v0_(&semantic_at_c<0>(*p))
        , v1_(&semantic_at_c<1>(*p))
        , v2_(&semantic_at_c<2>(*p))
    {}

    // Support for planar_pixel_reference offset constructor
    template <typename Ptr>
    homogeneous_color_base(Ptr const& ptr, std::ptrdiff_t diff)
        : v0_(*memunit_advanced(semantic_at_c<0>(ptr), diff))
        , v1_(*memunit_advanced(semantic_at_c<1>(ptr), diff))
        , v2_(*memunit_advanced(semantic_at_c<2>(ptr), diff))
    {}

    template <typename Ref>
    Ref deref() const
    {
        return Ref(
            *semantic_at_c<0>(*this),
            *semantic_at_c<1>(*this),
            *semantic_at_c<2>(*this));
    }

    auto at(std::integral_constant<int, 0>)
        -> typename element_reference_type<homogeneous_color_base>::type
    { return v0_; }

    auto at(std::integral_constant<int, 0>) const
        -> typename element_const_reference_type<homogeneous_color_base>::type
    { return v0_; }

    auto at(std::integral_constant<int, 1>)
        -> typename element_reference_type<homogeneous_color_base>::type
    { return v1_; }

    auto at(std::integral_constant<int, 1>) const
        -> typename element_const_reference_type<homogeneous_color_base>::type
    { return v1_; }

    auto at(std::integral_constant<int, 2>)
        -> typename element_reference_type<homogeneous_color_base>::type
    { return v2_; }

    auto at(std::integral_constant<int, 2>) const
        -> typename element_const_reference_type<homogeneous_color_base>::type
    { return v2_; }

    // Support for planar_pixel_reference operator[]
    Element at_c_dynamic(std::size_t i) const
    {
        switch (i)
        {
        case 0: return v0_;
        case 1: return v1_;
        }
        return v2_;
    }

private:
    Element v0_{};
    Element v1_{};
    Element v2_{};
};

/// \brief A homogeneous color base holding four color elements.
/// Models HomogeneousColorBaseConcept or HomogeneousColorBaseValueConcept
/// \ingroup ColorBaseModelHomogeneous
template <typename Element, typename Layout>
struct homogeneous_color_base<Element, Layout, 4>
{
    using layout_t = Layout;

    homogeneous_color_base() = default;
    explicit homogeneous_color_base(Element v) : v0_(v), v1_(v), v2_(v), v3_(v) {}
    homogeneous_color_base(Element v0, Element v1, Element v2, Element v3)
        : v0_(v0), v1_(v1), v2_(v2), v3_(v3)
    {}

    template <typename E2, typename L2>
    homogeneous_color_base(homogeneous_color_base<E2, L2, 4> const& c)
        : v0_(gil::at_c<mapping_transform<Layout, L2, 0>::value>(c))
        , v1_(gil::at_c<mapping_transform<Layout, L2, 1>::value>(c))
        , v2_(gil::at_c<mapping_transform<Layout, L2, 2>::value>(c))
        , v3_(gil::at_c<mapping_transform<Layout, L2, 3>::value>(c))
    {}

    // Support for l-value reference proxy copy construction
    template <typename E2, typename L2>
    homogeneous_color_base(homogeneous_color_base<E2, L2, 4>& c)
        : v0_(gil::at_c<mapping_transform<Layout, L2, 0>::value>(c))
        , v1_(gil::at_c<mapping_transform<Layout, L2, 1>::value>(c))
        , v2_(gil::at_c<mapping_transform<Layout, L2, 2>::value>(c))
        , v3_(gil::at_c<mapping_transform<Layout, L2, 3>::value>(c))
    {}

    // Support for planar_pixel_iterator construction and dereferencing
    template <typename P>
    homogeneous_color_base(P * p, bool)
        : v0_(&semantic_at_c<0>(*p))
        , v1_(&semantic_at_c<1>(*p))
        , v2_(&semantic_at_c<2>(*p))
        , v3_(&semantic_at_c<3>(*p))
    {}

    // Support for planar_pixel_reference offset constructor
    template <typename Ptr>
    homogeneous_color_base(Ptr const& ptr, std::ptrdiff_t diff)
        : v0_(*memunit_advanced(semantic_at_c<0>(ptr), diff))
        , v1_(*memunit_advanced(semantic_at_c<1>(ptr), diff))
        , v2_(*memunit_advanced(semantic_at_c<2>(ptr), diff))
        , v3_(*memunit_advanced(semantic_at_c<3>(ptr), diff))
    {}

    template <typename Ref>
    Ref deref() const
    {
        return Ref(
            *semantic_at_c<0>(*this),
            *semantic_at_c<1>(*this),
            *semantic_at_c<2>(*this),
            *semantic_at_c<3>(*this));
    }

    auto at(std::integral_constant<int, 0>)
        -> typename element_reference_type<homogeneous_color_base>::type
    { return v0_; }

    auto at(std::integral_constant<int, 0>) const
        -> typename element_const_reference_type<homogeneous_color_base>::type
    { return v0_; }

    auto at(std::integral_constant<int, 1>)
        -> typename element_reference_type<homogeneous_color_base>::type
    { return v1_; }

    auto at(std::integral_constant<int, 1>) const
        -> typename element_const_reference_type<homogeneous_color_base>::type
    { return v1_; }

    auto at(std::integral_constant<int, 2>)
        -> typename element_reference_type<homogeneous_color_base>::type
    { return v2_; }

    auto at(std::integral_constant<int, 2>) const
        -> typename element_const_reference_type<homogeneous_color_base>::type
    { return v2_; }

    auto at(std::integral_constant<int, 3>)
        -> typename element_reference_type<homogeneous_color_base>::type
    { return v3_; }

    auto at(std::integral_constant<int, 3>) const
        -> typename element_const_reference_type<homogeneous_color_base>::type
    { return v3_; }

    // Support for planar_pixel_reference operator[]
    Element at_c_dynamic(std::size_t i) const
    {
        switch (i)
        {
        case 0: return v0_;
        case 1: return v1_;
        case 2: return v2_;
        }
        return v3_;
    }

private:
    Element v0_{};
    Element v1_{};
    Element v2_{};
    Element v3_{};
};

/// \brief A homogeneous color base holding five color elements.
/// Models HomogeneousColorBaseConcept or HomogeneousColorBaseValueConcept
/// \ingroup ColorBaseModelHomogeneous
template <typename Element, typename Layout>
struct homogeneous_color_base<Element, Layout, 5>
{
    using layout_t = Layout;

    homogeneous_color_base() = default;
    explicit homogeneous_color_base(Element v)
        : v0_(v), v1_(v), v2_(v), v3_(v), v4_(v)
    {}

    homogeneous_color_base(Element v0, Element v1, Element v2, Element v3, Element v4)
        : v0_(v0), v1_(v1), v2_(v2), v3_(v3), v4_(v4)
    {}

    template <typename E2, typename L2>
    homogeneous_color_base(homogeneous_color_base<E2, L2, 5> const& c)
        : v0_(gil::at_c<mapping_transform<Layout, L2, 0>::value>(c))
        , v1_(gil::at_c<mapping_transform<Layout, L2, 1>::value>(c))
        , v2_(gil::at_c<mapping_transform<Layout, L2, 2>::value>(c))
        , v3_(gil::at_c<mapping_transform<Layout, L2, 3>::value>(c))
        , v4_(gil::at_c<mapping_transform<Layout, L2, 4>::value>(c))
    {}

    // Support for l-value reference proxy copy construction
    template <typename E2, typename L2>
    homogeneous_color_base(homogeneous_color_base<E2, L2, 5>& c)
        : v0_(gil::at_c<mapping_transform<Layout, L2, 0>::value>(c))
        , v1_(gil::at_c<mapping_transform<Layout, L2, 1>::value>(c))
        , v2_(gil::at_c<mapping_transform<Layout, L2, 2>::value>(c))
        , v3_(gil::at_c<mapping_transform<Layout, L2, 3>::value>(c))
        , v4_(gil::at_c<mapping_transform<Layout, L2, 4>::value>(c))
    {}

    // Support for planar_pixel_iterator construction and dereferencing
    template <typename P>
    homogeneous_color_base(P* p, bool)
        : v0_(&semantic_at_c<0>(*p))
        , v1_(&semantic_at_c<1>(*p))
        , v2_(&semantic_at_c<2>(*p))
        , v3_(&semantic_at_c<3>(*p))
        , v4_(&semantic_at_c<4>(*p))
    {}

    // Support for planar_pixel_reference offset constructor
    template <typename Ptr>
    homogeneous_color_base(Ptr const& ptr, std::ptrdiff_t diff)
        : v0_(*memunit_advanced(semantic_at_c<0>(ptr), diff))
        , v1_(*memunit_advanced(semantic_at_c<1>(ptr), diff))
        , v2_(*memunit_advanced(semantic_at_c<2>(ptr), diff))
        , v3_(*memunit_advanced(semantic_at_c<3>(ptr), diff))
        , v4_(*memunit_advanced(semantic_at_c<4>(ptr), diff))
    {}


    auto at(std::integral_constant<int, 0>)
        -> typename element_reference_type<homogeneous_color_base>::type
    { return v0_; }

    auto at(std::integral_constant<int, 0>) const
        -> typename element_const_reference_type<homogeneous_color_base>::type
    { return v0_; }

    auto at(std::integral_constant<int, 1>)
        -> typename element_reference_type<homogeneous_color_base>::type
    { return v1_; }

    auto at(std::integral_constant<int, 1>) const
        -> typename element_const_reference_type<homogeneous_color_base>::type
    { return v1_; }

    auto at(std::integral_constant<int, 2>)
        -> typename element_reference_type<homogeneous_color_base>::type
    { return v2_; }

    auto at(std::integral_constant<int, 2>) const
        -> typename element_const_reference_type<homogeneous_color_base>::type
    { return v2_; }

    auto at(std::integral_constant<int, 3>)
        -> typename element_reference_type<homogeneous_color_base>::type
    { return v3_; }

    auto at(std::integral_constant<int, 3>) const
        -> typename element_const_reference_type<homogeneous_color_base>::type
    { return v3_; }

    auto at(std::integral_constant<int, 4>)
        -> typename element_reference_type<homogeneous_color_base>::type
    { return v4_; }

    auto at(std::integral_constant<int, 4>) const
        -> typename element_const_reference_type<homogeneous_color_base>::type
    { return v4_; }

    template <typename Ref>
    Ref deref() const
    {
        return Ref(
            *semantic_at_c<0>(*this),
            *semantic_at_c<1>(*this),
            *semantic_at_c<2>(*this),
            *semantic_at_c<3>(*this),
            *semantic_at_c<4>(*this));
    }

    // Support for planar_pixel_reference operator[]
    Element at_c_dynamic(std::size_t i) const
    {
        switch (i)
        {
        case 0: return v0_;
        case 1: return v1_;
        case 2: return v2_;
        case 3: return v3_;
        }
        return v4_;
    }

private:
    Element v0_{};
    Element v1_{};
    Element v2_{};
    Element v3_{};
    Element v4_{};
};

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

// The following way of casting adjacent channels (the contents of color_base) into an array appears to be unsafe
// -- there is no guarantee that the compiler won't add any padding between adjacent channels.
// Note, however, that GIL _must_ be compiled with compiler settings ensuring there is no padding in the color base structs.
// This is because the color base structs must model the interleaved organization in memory. In other words, the client may
// have existing RGB image in the form "RGBRGBRGB..." and we must be able to represent it with an array of RGB color bases (i.e. RGB pixels)
// with no padding. We have tested with char/int/float/double channels on gcc and VC and have so far discovered no problem.
// We have even tried using strange channels consisting of short + char (3 bytes). With the default 4-byte alignment on VC, the size
// of this channel is padded to 4 bytes, so an RGB pixel of it will be 4x3=12 bytes. The code below will still work properly.
// However, the client must nevertheless ensure that proper compiler settings are used for their compiler and their channel types.

template <typename Element, typename Layout, int K>
auto dynamic_at_c(homogeneous_color_base<Element,Layout,K>& cb, std::size_t i)
    -> typename element_reference_type<homogeneous_color_base<Element, Layout, K>>::type
{
    BOOST_ASSERT(i < K);
    return (gil_reinterpret_cast<Element*>(&cb))[i];
}

template <typename Element, typename Layout, int K>
auto dynamic_at_c(homogeneous_color_base<Element, Layout, K> const& cb, std::size_t i)
    -> typename element_const_reference_type
        <
            homogeneous_color_base<Element, Layout, K>
        >::type
{
    BOOST_ASSERT(i < K);
    return (gil_reinterpret_cast_c<const Element*>(&cb))[i];
}

template <typename Element, typename Layout, int K>
auto dynamic_at_c(homogeneous_color_base<Element&, Layout, K> const& cb, std::size_t i)
    -> typename element_reference_type
        <
            homogeneous_color_base<Element&, Layout, K>
        >::type
{
    BOOST_ASSERT(i < K);
    return cb.at_c_dynamic(i);
}

template <typename Element, typename Layout, int K>
auto dynamic_at_c(
    homogeneous_color_base<Element const&, Layout, K>const& cb, std::size_t i)
    -> typename element_const_reference_type
        <
            homogeneous_color_base<Element const&, Layout, K>
        >::type
{
    BOOST_ASSERT(i < K);
    return cb.at_c_dynamic(i);
}

} // namespace detail

template <typename Element, typename Layout, int K1, int K>
struct kth_element_type<detail::homogeneous_color_base<Element, Layout, K1>, K>
{
    using type = Element;
};

template <typename Element, typename Layout, int K1, int K>
struct kth_element_reference_type<detail::homogeneous_color_base<Element, Layout, K1>, K>
    : std::add_lvalue_reference<Element>
{};

template <typename Element, typename Layout, int K1, int K>
struct kth_element_const_reference_type
    <
        detail::homogeneous_color_base<Element, Layout, K1>,
        K
    >
    : std::add_lvalue_reference<typename std::add_const<Element>::type>
{};

/// \brief Provides mutable access to the K-th element, in physical order
/// \ingroup ColorBaseModelHomogeneous
template <int K, typename E, typename L, int N>
inline
auto at_c(detail::homogeneous_color_base<E, L, N>& p)
    -> typename std::add_lvalue_reference<E>::type
{
    return p.at(std::integral_constant<int, K>());
}

/// \brief Provides constant access to the K-th element, in physical order
/// \ingroup ColorBaseModelHomogeneous
template <int K, typename E, typename L, int N>
inline
auto at_c(const detail::homogeneous_color_base<E, L, N>& p)
    -> typename std::add_lvalue_reference<typename std::add_const<E>::type>::type
{
    return p.at(std::integral_constant<int, K>());
}

namespace detail
{

struct swap_fn
{
    template <typename T>
    void operator()(T& x, T& y) const
    {
        using std::swap;
        swap(x, y);
    }
};

} // namespace detail

template <typename E, typename L, int N>
inline
void swap(
    detail::homogeneous_color_base<E, L, N>& x,
    detail::homogeneous_color_base<E, L, N>& y)
{
    static_for_each(x, y, detail::swap_fn());
}

}}  // namespace boost::gil

#endif

/* color_base.hpp
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
*/