//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_CONCEPTS_CHANNEL_HPP
#define BOOST_GIL_CONCEPTS_CHANNEL_HPP

#include <boost/gil/concepts/basic.hpp>
#include <boost/gil/concepts/concept_check.hpp>
#include <boost/gil/concepts/fwd.hpp>

#include <boost/concept_check.hpp>

#include <utility> // std::swap
#include <type_traits>

#if defined(BOOST_CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic ignored "-Wunused-local-typedefs"
#endif

#if defined(BOOST_GCC) && (BOOST_GCC >= 40900)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#endif

namespace boost { namespace gil {

// Forward declarations
template <typename T>
struct channel_traits;

template <typename DstT, typename SrcT>
auto channel_convert(SrcT const& val)
    -> typename channel_traits<DstT>::value_type;

/// \ingroup ChannelConcept
/// \brief A channel is the building block of a color.
/// Color is defined as a mixture of primary colors and a channel defines
/// the degree to which each primary color is used in the mixture.
///
/// For example, in the RGB color space, using 8-bit unsigned channels,
/// the color red is defined as [255 0 0], which means maximum of Red,
/// and no Green and Blue.
///
/// Built-in scalar types, such as \p int and \p float, are valid GIL channels.
/// In more complex scenarios, channels may be represented as bit ranges or
/// even individual bits.
/// In such cases special classes are needed to represent the value and
/// reference to a channel.
///
/// Channels have a traits class, \p channel_traits, which defines their
/// associated types as well as their operating ranges.
///
/// \code
/// concept ChannelConcept<typename T> : EqualityComparable<T>
/// {
///     typename value_type      = T;        // use channel_traits<T>::value_type to access it
///     typename reference       = T&;       // use channel_traits<T>::reference to access it
///     typename pointer         = T*;       // use channel_traits<T>::pointer to access it
///     typename const_reference = const T&; // use channel_traits<T>::const_reference to access it
///     typename const_pointer   = const T*; // use channel_traits<T>::const_pointer to access it
///     static const bool is_mutable;        // use channel_traits<T>::is_mutable to access it
///
///     static T min_value();                // use channel_traits<T>::min_value to access it
///     static T max_value();                // use channel_traits<T>::max_value to access it
/// };
/// \endcode
template <typename T>
struct ChannelConcept
{
    void constraints()
    {
        gil_function_requires<boost::EqualityComparableConcept<T>>();

        using v = typename channel_traits<T>::value_type;
        using r = typename channel_traits<T>::reference;
        using p = typename channel_traits<T>::pointer;
        using cr = typename channel_traits<T>::const_reference;
        using cp = typename channel_traits<T>::const_pointer;

        channel_traits<T>::min_value();
        channel_traits<T>::max_value();
    }

     T c;
};

namespace detail
{

/// \tparam T models ChannelConcept
template <typename T>
struct ChannelIsMutableConcept
{
    void constraints()
    {
        c1 = c2;
        using std::swap;
        swap(c1, c2);
    }
    T c1;
    T c2;
};

} // namespace detail

/// \brief A channel that allows for modifying its value
/// \code
/// concept MutableChannelConcept<ChannelConcept T> : Assignable<T>, Swappable<T> {};
/// \endcode
/// \ingroup ChannelConcept
template <typename T>
struct MutableChannelConcept
{
    void constraints()
    {
        gil_function_requires<ChannelConcept<T>>();
        gil_function_requires<detail::ChannelIsMutableConcept<T>>();
    }
};

/// \brief A channel that supports default construction.
/// \code
/// concept ChannelValueConcept<ChannelConcept T> : Regular<T> {};
/// \endcode
/// \ingroup ChannelConcept
template <typename T>
struct ChannelValueConcept
{
    void constraints()
    {
        gil_function_requires<ChannelConcept<T>>();
        gil_function_requires<Regular<T>>();
    }
};

/// \brief Predicate metafunction returning whether two channels are compatible
///
/// Channels are considered compatible if their value types
/// (ignoring constness and references) are the same.
///
/// Example:
///
/// \code
/// static_assert(channels_are_compatible<uint8_t, const uint8_t&>::value, "");
/// \endcode
/// \ingroup ChannelAlgorithm
template <typename T1, typename T2>  // Models GIL Pixel
struct channels_are_compatible
    : std::is_same
        <
            typename channel_traits<T1>::value_type,
            typename channel_traits<T2>::value_type
        >
{
};

/// \brief Channels are compatible if their associated value types (ignoring constness and references) are the same
///
/// \code
/// concept ChannelsCompatibleConcept<ChannelConcept T1, ChannelConcept T2>
/// {
///     where SameType<T1::value_type, T2::value_type>;
/// };
/// \endcode
/// \ingroup ChannelConcept
template <typename Channel1, typename Channel2>
struct ChannelsCompatibleConcept
{
    void constraints()
    {
        static_assert(channels_are_compatible<Channel1, Channel2>::value, "");
    }
};

/// \brief A channel is convertible to another one if the \p channel_convert algorithm is defined for the two channels.
///
/// Convertibility is non-symmetric and implies that one channel can be
/// converted to another. Conversion is explicit and often lossy operation.
///
/// concept ChannelConvertibleConcept<ChannelConcept SrcChannel, ChannelValueConcept DstChannel>
/// {
///     DstChannel channel_convert(const SrcChannel&);
/// };
/// \endcode
/// \ingroup ChannelConcept
template <typename SrcChannel, typename DstChannel>
struct ChannelConvertibleConcept
{
    void constraints()
    {
        gil_function_requires<ChannelConcept<SrcChannel>>();
        gil_function_requires<MutableChannelConcept<DstChannel>>();
        dst = channel_convert<DstChannel, SrcChannel>(src);
        ignore_unused_variable_warning(dst);
    }
    SrcChannel src;
    DstChannel dst;
};

}} // namespace boost::gil

#if defined(BOOST_CLANG)
#pragma clang diagnostic pop
#endif

#if defined(BOOST_GCC) && (BOOST_GCC >= 40900)
#pragma GCC diagnostic pop
#endif

#endif

/* channel.hpp
QtH+ls1tb2ZerorZXNeGTb/yLYpXL0/Dwf7WzcO+DO79XeCcv8DCpNCfKyyorwbDhNpf9ffoXoW+FXxCXxN+Dpd6NfoalevaNTFiqj8wzDH1XUsyhwk5H7VIDAIFdoPAtPd71s8bF0lsWh1MmJwSYc9bLHCVGIHN2tiBaYF5SwSmTooJbNzCJmtS5q3EOM5yz6G4F+OsbEtct3OKDdfPO8l1D+xxfdPxaHJ0Oet1tQjr+oHtGCRmxj5iJ3YQ02cLxby0mxgPicn3lYqjIe46vlxr9O1z0Cb9sWr/RnG4tWLwIxLvDBmc356k4kAUgPWDiKNM3xNDjKgn5l0RtjPEKfuYH35UCmfYWWIyMM/sRueLeNN8WT5Dl/i4fnzBSp+2O8bIIcjwxPSTMaRIuyU4TIMdjzXOWjwSKOf3Fm7HZ53tWSR4dmzM03HB0SDCs98Ss2Ox5jFwGoqN8v9mcIYUYZdojMJl/AhrcETvZoBnDpcKTkQZXGfh0fG0Lws5nU3iuUpyIuI5beHR8aRaybFjEW3sjSGHIMtDYFYMYo571DngqH6CqRwzNDhOVLIdkRvdHpn35eRFtsfFKyTevD2+hLzm7fH8lYLjlN81AnNiIWfdKsVRlOZt5lrJiUjn5tUSj67LT5LTvM0M3U5wIuL5qoVHxzPaRo4di5zvQg5Bhj+XmB2DuFN1y3L7TlUxn+np7U1ncL99qFgKHC6Ukv0l/6Teto6GO1mtK+zw/amu7q50Mh0ZflMnw9OuY4Xviff2dxVgYcua8ImUElJSUnpcv38ZJ2whn+pP9nZ3O2FxgIVhqZ+NybDJFMIWk/liZmHvjo2iPKema3H9JvQV0M/wg3sh+IpTlBOYm5VSrZ4xqgud/aR/laKYSPalh5TO61uNBD4WEzhO611RntJzEO+EEPeV+o0MCz/VDjaBP53iTI+LQ2ct1XCLoYJ3LXgGSnCUzoUIeH5qsYMFEVAPP+LiMgKRx9QSwcNuCN4W8S0KfG9L4ZZ9R786gIcB/EIX411mqeEiQ3o3qzLqs0zxh31Wci1KnWPZtmWaEx0vzzN/0ufxPDPLGGM8vivF2siGXqlfheZ7RucoTlAuso4vMu/c+jjuyvhtuDhQGEonh7KFvPpndzYXvPgk+O3L5+FrBbTT1NM8fF7vEXG0rZgvDMwUgn94Hr6+AkT+upVz8/WlJa4hjwf8+rh4O82/wMDKUofMQv51qwRfj4QRfNbj9Grw+d7OPqwo2Va47n/C7QwHN7cgpXkqPIa5sc0K0zQl1jpyub2OLOYSyUI6tzCb++jGSP/4i5qsEy7k/hU5keskqbfv5x5PIpUKzC/EnmBh+k6Txp5qY7THX2DmFfv928GDdaxmh7AAE/702wQnJAxNdqOmAqrYL91lnbPjWo53JuV6b3IGD/uTUuFbHE5dJPP5RDqbWNiaHnXBu4aYM+6HOaPdl7dXNa7hsopx3/QMovHP3D4A+OCuQbx+MZTtTwfftuBbrqh6hPoWvJNxsf9NMHX4TfgeMvU53ttrG52+pHhX0y49ro9UIlGQExyv4osV1nzOOiVxZYjSTQRzCvV84lyX6Ts6xKLnu9GlAnfmux85mI6We/RPWObg+qx3DQ8XVw9gltgYcout83A7xZvy/lrSnWfFWY0ofFM4ttxf1fk88/BJwXHn4aEVDubYw864uKwU+Sb7SoenM8L5flUUvimc7xW+kPl+NXlyvuece63Cm9u+2UYffDvwbLsJy3Rlm4OVfPNPXe7vPcHlKMtepQqjrjyjoNch57rcOsZ28sL1s+C5d1Frtyfm2o/CNYDgOGMO40jdARzblsQ1xtuJOWOaxnPnEfeNo0I+y+46wXE=
*/