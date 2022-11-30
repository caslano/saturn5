/////////////////////////////////////////////////////////////////////
//  Copyright 2018 Glen Joseph Fernandes. 
//  Copyright 2021 Matt Borland. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_DETAIL_EMPTY_VALUE_HPP
#define BOOST_MP_DETAIL_EMPTY_VALUE_HPP

#include <utility>
#include <boost/multiprecision/detail/standalone_config.hpp>

#if defined(BOOST_GCC_VERSION) && (BOOST_GCC_VERSION >= 40700)
#define BOOST_DETAIL_EMPTY_VALUE_BASE
#elif defined(BOOST_INTEL) && defined(_MSC_VER) && (_MSC_VER >= 1800)
#define BOOST_DETAIL_EMPTY_VALUE_BASE
#elif defined(BOOST_MSVC) && (BOOST_MSVC >= 1800)
#define BOOST_DETAIL_EMPTY_VALUE_BASE
#elif defined(BOOST_CLANG) && !defined(__CUDACC__)
#if __has_feature(is_empty) && __has_feature(is_final)
#define BOOST_DETAIL_EMPTY_VALUE_BASE
#endif
#endif

namespace boost { namespace multiprecision { namespace detail {

template <typename T>
struct use_empty_value_base 
{
#if defined(BOOST_DETAIL_EMPTY_VALUE_BASE)
        static constexpr bool value = __is_empty(T) && !__is_final(T);
#else
        static constexpr bool value = false;
#endif
};

struct empty_init_t {};

namespace empty_impl {

template <typename T, unsigned N = 0, 
          bool E = boost::multiprecision::detail::use_empty_value_base<T>::value>
class empty_value
{
private:
    T value_;

public:
    using type = T;

    empty_value() = default;
    explicit empty_value(boost::multiprecision::detail::empty_init_t) : value_ {} {}

    template <typename U, typename... Args>
    empty_value(boost::multiprecision::detail::empty_init_t, U&& value, Args&&... args) :
        value_ {std::forward<U>(value), std::forward<Args>(args)...} {}

    const T& get() const noexcept { return value_; }
    T& get() noexcept { return value_; }
};

template <typename T, unsigned N>
class empty_value<T, N, true> : T
{
public:
    using type = T;

    empty_value() = default;
    explicit empty_value(boost::multiprecision::detail::empty_init_t) : T{} {}

    template <typename U, typename... Args>
    empty_value(boost::multiprecision::detail::empty_init_t, U&& value, Args&&... args) :
        T{std::forward<U>(value), std::forward<Args>(args)...} {}

    const T& get() const noexcept { return *this; }
    T& get() noexcept { return *this; }
};

} // Namespace empty impl

using empty_impl::empty_value;

BOOST_INLINE_CONSTEXPR empty_init_t empty_init = empty_init_t();

}}} // Namespaces

#endif // BOOST_MP_DETAIL_EMPTY_VALUE_HPP

/* empty_value.hpp
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
*/