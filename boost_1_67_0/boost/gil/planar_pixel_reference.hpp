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