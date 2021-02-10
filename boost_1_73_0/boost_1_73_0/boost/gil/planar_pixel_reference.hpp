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
oRkgDJZclR/R7ntSK30GgftvrfRI4jzpi6OfHOW+IuvlaYt8xJw9ZgwRjYB+9n2KgGNGUPyFQvyDdQWSjjEVuE01nJaKZXRisMNZQbTAjp3MCfo2JRdwFl9LLXw1saA7IDUCpW/xSIbNnQ2I0GwMqb6l2XW3c5JP61+4MtZuiIxUpbRcJ3K3372X99hDCWP4yDFf2ihFrlwXwqC0U4FnrTuhuqCEDTW9CH5uLXoFvd3Tt76O/T8WpQnLkvVVfaEekppVOZEK67Es8IQu4PN1qFM4BjPyEjj6VjHemHoLKzEyw02pBMqsHV1quVhwxXZgbdiKMQfcsee+0VYwDli1FTIZbysCJlA2INg8H4YRcQvSq42j0zkdDn4+3nIsJuIi9a7UjnuntKlERX1kdFI2ZurwTAet/u03N17BSfend6+dp56Ed+PkcnnFSX0oC8soXYyWM0puiGiSnTgXlCHec9hUSiIpbdOyeDk07nbLC0Lw1PVkhx835UpmnhzYOJ0vD9OsxNNyr7gZmXjnCTD78HGeAfNfLEb8m2PecZ3q1LCMEKE9NFe7cWFMdzAEUVbyqpNxZHIyAdeuOqfn/ej6mRsUqP8a1/JcZv2bVHmuF+PLmP/yrncc1PzOXzacoDLHLEo/h7izjt8uvjls
*/