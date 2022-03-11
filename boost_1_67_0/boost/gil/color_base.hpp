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