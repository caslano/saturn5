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