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

template <class ValueType = double>
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
struct is_thread_safe : std::false_type {};
template <class T>
struct is_thread_safe<thread_safe<T>> : std::true_type {};

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

} // namespace histogram
} // namespace boost

#endif

/* fwd.hpp
IOUuSnl1dMq9CKlhe8HGnl5d+V/5Ea2s6rdGt60LrB3a1kl99bb1nomxbeuG0xg2XjejnoBmLcpoUU2kZo5rowjsCH/EGAv/kZHgV8WF34dGlS8AbU5cpwHJ5Bz/exGfdB9pexRQM6t/R5zS/yk14HOgGYI7rlPwevcZBrtqt3Np1Wcx0bmPqiBQJ5zfpF4PG5yg2cHtNyN1euiJO1JrpCMtJeUq6KpXVK/ECOM+al0FUPjsA0RBv0LtfMPa2DJ2/Ej4twokvF7cmztloTqoOJbfJ+C9GRUnHr/z+8bCD+lL8E/HhQ8MiIVfNoDgH44Lvz78WQz8zXhvRpWPB3+aIRZ/XwPhfyIOvNT3m3rpBuE1jjGYweIC/qFyYPOTXIrUIOf24j6R7a5qbFodUadxqKX7O4bVvw8leubH19+Y+Puo+4sG6ijnZu6cosr7e4wnulAL9eeIj1aD22XyePgXSIBofv3YEuHXDyKcyhsdxamxFuaUHLyKKb42NEhqTiKc/rcS/DsMvmRc9Gzsof0+j4f1huipXnpDdOKE2IboB6fIhqiL9FdG0r82Pjb9eyfHppf8+GNH1saJb+Y+owMQ++vd/CEyULZWYPxO9tYnR+ytz4/4A98fay/9AzaWftfE97V5THaQSb0ou0vOUBsPf0bOlWc1bU5b2x+oe4q17yy629UMbAd/OOhweHPbqBOPL/UJU5AaluTHnDqRUv/GgdRzjjf1HaVI/TVTPm/tsaVPovRDkXujefSJwj9777EWpN+B9FONY0sp/Va2X98RN/3JyJ+N17+7WWDPP8Kfbqp/jME3SimHObrvLARZw9nBwlS2nXssFWrjDC+0Tw8vxOkDHEVQPbwU4dBs5THa7wK/d4TnabDakwYsallOR/+xmEj34LyHdzwjwYkPzShx24kYbkzgQNwMTGZ5jyMkvJFoJSNO1WYEQCEA+PzPiVQzR6JmxsHvBmY82BO/+RjnXdpNtmupHsKGzHdGil2cAMCRZWqUAknyxi6ljve42tCw4wqHg/XhpX9R2AC6v3emRpjFqaZz1nbvBRzk5ivNbxzOYQGGfjCw3CJGiBLl0ltxNofxzJMFdKp/PEHg8UThmSrxsEUnOeoILLfH4rKtwoIDr2DTxQyFeEZYwwgKu5V41UhtQtbWvHbb9eTr0Q3elZu2OtUPl7GJKiMzPgNIQlmtnbhY+6Pvp9iX4fsCvmlnpHyndj/ifs3qrI73a85hh5hwH4QFtSrhlJCa6jl82ybtfgbBADcdOqaQNGf5dJdb/exs7bbKmv5YhJE3ZhYME9dQhtm9HF95W6k9VxCj4TmmWCyY+pBYW0VMGXZ8d1c2VrH955nR5ZlJnrvIxnxupfAJhrLgIQNXwK4SZOAtnTZV1SszyY9Dzh7NsRg61C8O1+8Jlhptk1po2Xjll2EEL0mVN4LOBKlz2Ky+Cse5JpiQup3UYgAk60XxuJh8UM2t/mGMduhEbDPxSb0xVeQEZjuetPVhLOP2939lXJItLyx2q/UynbDHrAQDhzhho93+mbQ2pmvbZFZ8N/NNkTi+E9KINCchzZUy3LfEa9DwzB0obbR/pKzhUsOzV9ZLeZqd+WGAZdpKPnE52e0W3RyrDq1NNhjRz01UfMIInEpxDak/SjlI2obTtqvkUf4QyaO7EY84hHuELxPEniZij1nY38JHzCeqM3l64KTOu7OvekqO1GzMJtiA0urg7bHeXS+hYby/diDNpr/8TDtZcoqHApzqEprCPIBHr0E7d2LvrKWG3f1n6Ao9dmrf5w89zvY9B0ii2/d37dSaW7k1tzrVf7B3JeBRVVc4kzcmQ2bIGyRApCnEJq2RSXXCS2swUSc=
*/