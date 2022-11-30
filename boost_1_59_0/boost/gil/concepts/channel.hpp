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
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
*/