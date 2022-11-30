// Copyright 2015-2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_FWD_HPP
#define BOOST_HISTOGRAM_FWD_HPP

/**
  \file boost/histogram/fwd.hpp
  Forward declarations, tag types and type aliases.
*/

#include <boost/config.hpp> // BOOST_ATTRIBUTE_NODISCARD
#include <boost/core/use_default.hpp>
#include <tuple>
#include <type_traits>
#include <vector>

namespace boost {
namespace histogram {

/// Tag type to indicate use of a default type
using boost::use_default;

namespace axis {

/// Integral type for axis indices
using index_type = int;

/// Real type for axis indices
using real_index_type = double;

/// Empty metadata type
struct null_type {
  template <class Archive>
  void serialize(Archive&, unsigned /* version */) {}
};

/// Another alias for an empty metadata type
using empty_type = null_type;

// some forward declarations must be hidden from doxygen to fix the reference docu :(
#ifndef BOOST_HISTOGRAM_DOXYGEN_INVOKED

namespace transform {

struct id;

struct log;

struct sqrt;

struct pow;

} // namespace transform

template <class Value = double, class Transform = use_default,
          class MetaData = use_default, class Options = use_default>
class regular;

template <class Value = int, class MetaData = use_default, class Options = use_default>
class integer;

template <class Value = double, class MetaData = use_default, class Options = use_default,
          class Allocator = std::allocator<Value>>
class variable;

template <class Value = int, class MetaData = use_default, class Options = use_default,
          class Allocator = std::allocator<Value>>
class category;

template <class MetaData = use_default>
class boolean;

template <class... Ts>
class variant;

#endif // BOOST_HISTOGRAM_DOXYGEN_INVOKED

} // namespace axis

#ifndef BOOST_HISTOGRAM_DOXYGEN_INVOKED

template <class T>
struct weight_type;

template <class T>
struct sample_type;

namespace accumulators {

template <class ValueType = double, bool ThreadSafe = false>
class count;

template <class ValueType = double>
class sum;

template <class ValueType = double>
class weighted_sum;

template <class ValueType = double>
class mean;

template <class ValueType = double>
class weighted_mean;

template <class T>
class thread_safe;

template <class T>
struct is_thread_safe;

} // namespace accumulators

struct unsafe_access;

template <class Allocator = std::allocator<char>>
class unlimited_storage;

template <class T>
class storage_adaptor;

#endif // BOOST_HISTOGRAM_DOXYGEN_INVOKED

/// Vector-like storage for fast zero-overhead access to cells.
template <class T, class A = std::allocator<T>>
using dense_storage = storage_adaptor<std::vector<T, A>>;

/// Default storage, optimized for unweighted histograms
using default_storage = unlimited_storage<>;

/// Dense storage which tracks sums of weights and a variance estimate.
using weight_storage = dense_storage<accumulators::weighted_sum<>>;

/// Dense storage which tracks means of samples in each cell.
using profile_storage = dense_storage<accumulators::mean<>>;

/// Dense storage which tracks means of weighted samples in each cell.
using weighted_profile_storage = dense_storage<accumulators::weighted_mean<>>;

// some forward declarations must be hidden from doxygen to fix the reference docu :(
#ifndef BOOST_HISTOGRAM_DOXYGEN_INVOKED

template <class Axes, class Storage = default_storage>
class BOOST_ATTRIBUTE_NODISCARD histogram;

#endif // BOOST_HISTOGRAM_DOXYGEN_INVOKED

namespace detail {

/*
 Most of the histogram code is generic and works for any number of axes. Buffers with a
 fixed maximum capacity are used in some places, which have a size equal to the rank of
 a histogram. The buffers are allocated from the stack to improve performance, which
 means in C++ that they need a preset maximum capacity. 32 seems like a safe upper limit
 for the rank. You can nevertheless increase it with the compile-time flag
 BOOST_HISTOGRAM_DETAIL_AXES_LIMIT, if necessary.
*/
#ifndef BOOST_HISTOGRAM_DETAIL_AXES_LIMIT
#define BOOST_HISTOGRAM_DETAIL_AXES_LIMIT 32
#endif

template <class T>
struct buffer_size_impl
    : std::integral_constant<std::size_t, BOOST_HISTOGRAM_DETAIL_AXES_LIMIT> {};

template <class... Ts>
struct buffer_size_impl<std::tuple<Ts...>>
    : std::integral_constant<std::size_t, sizeof...(Ts)> {};

template <class T>
using buffer_size = typename buffer_size_impl<T>::type;

} // namespace detail

} // namespace histogram
} // namespace boost

#endif

/* fwd.hpp
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
*/