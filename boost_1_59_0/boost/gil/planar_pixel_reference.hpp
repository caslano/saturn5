//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_PLANAR_PIXEL_REFERENCE_HPP
#define BOOST_GIL_PLANAR_PIXEL_REFERENCE_HPP

#include <boost/gil/channel.hpp>
#include <boost/gil/color_base.hpp>
#include <boost/gil/concepts.hpp>
#include <boost/gil/pixel.hpp>
#include <boost/gil/planar_pixel_iterator.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <type_traits>

namespace boost { namespace gil {

/// \defgroup ColorBaseModelPlanarRef planar_pixel_reference
/// \ingroup ColorBaseModel
/// \brief A homogeneous color base whose element is a channel reference. Models HomogeneousColorBaseConcept, HomogeneousPixelConcept.
/// This class is used as a reference proxy to a planar pixel.

/// \defgroup PixelModelPlanarRef planar_pixel_reference
/// \ingroup PixelModel
/// \brief A reference proxy to a planar pixel. Models HomogeneousColorBaseConcept, HomogeneousPixelConcept.

/// \ingroup PixelModelPlanarRef ColorBaseModelPlanarRef PixelBasedModel
/// \brief A reference proxy to a planar pixel.
///
/// A reference to a planar pixel is a proxy class containing references to each of the corresponding channels.
/// Models: HomogeneousColorBaseConcept, HomogeneousPixelConcept
///
/// \tparam ChannelReference A channel reference, either const or mutable
/// \tparam ColorSpace
template <typename ChannelReference, typename ColorSpace>
struct planar_pixel_reference : detail::homogeneous_color_base
    <
        ChannelReference,
        layout<ColorSpace>,
        mp11::mp_size<ColorSpace>::value
    >
{
    using parent_t =detail::homogeneous_color_base
        <
            ChannelReference,
            layout<ColorSpace>,
            mp11::mp_size<ColorSpace>::value
        >;

private:
    // These three are only defined for homogeneous pixels
    using channel_t = typename channel_traits<ChannelReference>::value_type;
    using channel_const_reference = typename channel_traits<ChannelReference>::const_reference;

public:
    static constexpr bool is_mutable = channel_traits<ChannelReference>::is_mutable;
    using value_type = pixel<channel_t,layout<ColorSpace>>;
    using reference = planar_pixel_reference<ChannelReference, ColorSpace>;
    using const_reference = planar_pixel_reference<channel_const_reference,ColorSpace>;

    planar_pixel_reference(ChannelReference v0, ChannelReference v1)
        : parent_t(v0, v1)
    {}

    planar_pixel_reference(ChannelReference v0, ChannelReference v1, ChannelReference v2)
        : parent_t(v0, v1, v2)
    {}

    planar_pixel_reference(ChannelReference v0, ChannelReference v1, ChannelReference v2, ChannelReference v3)
        : parent_t(v0, v1, v2, v3)
    {}

    planar_pixel_reference(ChannelReference v0, ChannelReference v1, ChannelReference v2, ChannelReference v3, ChannelReference v4)
        : parent_t(v0, v1, v2, v3, v4)
    {}

    planar_pixel_reference(ChannelReference v0, ChannelReference v1, ChannelReference v2, ChannelReference v3, ChannelReference v4, ChannelReference v5)
        : parent_t(v0, v1, v2, v3, v4, v5)
    {}

    planar_pixel_reference(planar_pixel_reference const& p) : parent_t(p) {}

    // TODO: What is the purpose of returning via const reference?
    auto operator=(planar_pixel_reference const& p) const -> planar_pixel_reference const&
    {
        static_copy(p, *this);
        return *this;
    }

    template <typename Pixel>
    planar_pixel_reference(Pixel const& p) : parent_t(p)
    {
         check_compatible<Pixel>();
    }

    // TODO: What is the purpose of returning via const reference?
    template <typename Pixel>
    auto operator=(Pixel const& p) const -> planar_pixel_reference const&
    {
        check_compatible<Pixel>();
        static_copy(p, *this);
        return *this;
    }

    // PERFORMANCE_CHECK: Is this constructor necessary?
    template <typename ChannelV, typename Mapping>
    planar_pixel_reference(pixel<ChannelV, layout<ColorSpace, Mapping>>& p)
       : parent_t(p)
    {
        check_compatible<pixel<ChannelV, layout<ColorSpace, Mapping>>>();
    }

    // Construct at offset from a given location
    template <typename ChannelPtr>
    planar_pixel_reference(planar_pixel_iterator<ChannelPtr, ColorSpace> const& p, std::ptrdiff_t diff)
        : parent_t(p, diff)
    {}

// This overload is necessary for a compiler implementing Core Issue 574
// to prevent generation of an implicit copy assignment operator (the reason
// for generating implicit copy assignment operator is that according to
// Core Issue 574, a cv-qualified assignment operator is not considered
// "copy assignment operator").
// EDG implemented Core Issue 574 starting with EDG Version 3.8. I'm not
// sure why they did it for a template member function as well.
#if BOOST_WORKAROUND(__HP_aCC, >= 61700) || BOOST_WORKAROUND(__INTEL_COMPILER, >= 1000)
    const planar_pixel_reference& operator=(const planar_pixel_reference& p) { static_copy(p,*this); return *this; }
    template <typename P> const planar_pixel_reference& operator=(const P& p) { check_compatible<P>(); static_copy(p,*this); return *this; }
#endif

    template <typename Pixel>
    bool operator==(Pixel const& p) const
    {
        check_compatible<Pixel>();
        return static_equal(*this, p);
    }

    template <typename Pixel>
    bool operator!=(Pixel const &p) const { return !(*this == p); }

    auto operator[](std::size_t i) const -> ChannelReference { return this->at_c_dynamic(i); }
    auto operator->() const -> planar_pixel_reference const* { return this; }

private:
    template <typename Pixel>
    static void check_compatible()
    {
        gil_function_requires<PixelsCompatibleConcept<Pixel, planar_pixel_reference>>();
    }
};

/////////////////////////////
//  ColorBasedConcept
/////////////////////////////

template <typename ChannelReference, typename ColorSpace, int K>
struct kth_element_type<planar_pixel_reference<ChannelReference, ColorSpace>, K>
{
    using type = ChannelReference;
};

template <typename ChannelReference, typename ColorSpace, int K>
struct kth_element_reference_type
    <
        planar_pixel_reference<ChannelReference, ColorSpace>,
        K
    >
{
    using type = ChannelReference;
};

template <typename ChannelReference, typename ColorSpace, int K>
struct kth_element_const_reference_type
    <
        planar_pixel_reference<ChannelReference, ColorSpace>,
        K
    >
    : std::add_lvalue_reference<typename std::add_const<ChannelReference>::type>
{
    //    using type = typename channel_traits<ChannelReference>::const_reference;
};

/////////////////////////////
//  PixelConcept
/////////////////////////////

/// \brief Metafunction predicate that flags planar_pixel_reference as a model of PixelConcept. Required by PixelConcept
/// \ingroup PixelModelPlanarRef
template <typename ChannelReference, typename ColorSpace>
struct is_pixel< planar_pixel_reference<ChannelReference, ColorSpace>>
    : std::true_type
{};

/////////////////////////////
//  HomogeneousPixelBasedConcept
/////////////////////////////

/// \brief Specifies the color space type of a planar pixel reference. Required by PixelBasedConcept
/// \ingroup PixelModelPlanarRef
template <typename ChannelReference, typename ColorSpace>
struct color_space_type<planar_pixel_reference<ChannelReference,ColorSpace> > {
    using type = ColorSpace;
};

/// \brief Specifies the color space type of a planar pixel reference. Required by PixelBasedConcept
/// \ingroup PixelModelPlanarRef
template <typename ChannelReference, typename ColorSpace>
struct channel_mapping_type<planar_pixel_reference<ChannelReference,ColorSpace> > {
    using type = typename layout<ColorSpace>::channel_mapping_t;
};

/// \brief Specifies that planar_pixel_reference represents a planar construct. Required by PixelBasedConcept
/// \ingroup PixelModelPlanarRef
template <typename ChannelReference, typename ColorSpace>
struct is_planar<planar_pixel_reference<ChannelReference, ColorSpace>>
    : std::true_type
{};

/// \brief Specifies the color space type of a planar pixel reference. Required by HomogeneousPixelBasedConcept
/// \ingroup PixelModelPlanarRef
template <typename ChannelReference, typename ColorSpace>
struct channel_type<planar_pixel_reference<ChannelReference,ColorSpace> > {
    using type = typename channel_traits<ChannelReference>::value_type;
};

}}  // namespace boost::gil

namespace std {
// We are forced to define swap inside std namespace because on some platforms (Visual Studio 8) STL calls swap qualified.
// swap with 'left bias':
// - swap between proxy and anything
// - swap between value type and proxy
// - swap between proxy and proxy
// Having three overloads allows us to swap between different (but compatible) models of PixelConcept

/// \brief  swap for planar_pixel_reference
/// \ingroup PixelModelPlanarRef
template <typename CR, typename CS, typename R> inline
void swap(const boost::gil::planar_pixel_reference<CR,CS> x, R& y) {
    boost::gil::swap_proxy<typename boost::gil::planar_pixel_reference<CR,CS>::value_type>(x,y);
}

/// \brief  swap for planar_pixel_reference
/// \ingroup PixelModelPlanarRef
template <typename CR, typename CS> inline
void swap(typename boost::gil::planar_pixel_reference<CR,CS>::value_type& x, const boost::gil::planar_pixel_reference<CR,CS> y) {
    boost::gil::swap_proxy<typename boost::gil::planar_pixel_reference<CR,CS>::value_type>(x,y);
}

/// \brief  swap for planar_pixel_reference
/// \ingroup PixelModelPlanarRef
template <typename CR, typename CS> inline
void swap(const boost::gil::planar_pixel_reference<CR,CS> x, const boost::gil::planar_pixel_reference<CR,CS> y) {
    boost::gil::swap_proxy<typename boost::gil::planar_pixel_reference<CR,CS>::value_type>(x,y);
}

}   // namespace std

#endif

/* planar_pixel_reference.hpp
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
*/