/*
Copyright 2018 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_CORE_EMPTY_VALUE_HPP
#define BOOST_CORE_EMPTY_VALUE_HPP

#include <boost/config.hpp>
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#include <utility>
#endif

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

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4510)
#endif

namespace boost {

template<class T>
struct use_empty_value_base {
    enum {
#if defined(BOOST_DETAIL_EMPTY_VALUE_BASE)
        value = __is_empty(T) && !__is_final(T)
#else
        value = false
#endif
    };
};

struct empty_init_t { };

namespace empty_ {

template<class T, unsigned N = 0,
    bool E = boost::use_empty_value_base<T>::value>
class empty_value {
public:
    typedef T type;

#if !defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS)
    empty_value() = default;
#else
    empty_value() { }
#endif

    empty_value(boost::empty_init_t)
        : value_() { }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template<class U, class... Args>
    empty_value(boost::empty_init_t, U&& value, Args&&... args)
        : value_(std::forward<U>(value), std::forward<Args>(args)...) { }
#else
    template<class U>
    empty_value(boost::empty_init_t, U&& value)
        : value_(std::forward<U>(value)) { }
#endif
#else
    template<class U>
    empty_value(boost::empty_init_t, const U& value)
        : value_(value) { }

    template<class U>
    empty_value(boost::empty_init_t, U& value)
        : value_(value) { }
#endif

    const T& get() const BOOST_NOEXCEPT {
        return value_;
    }

    T& get() BOOST_NOEXCEPT {
        return value_;
    }

private:
    T value_;
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
template<class T, unsigned N>
class empty_value<T, N, true>
    : T {
public:
    typedef T type;

#if !defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS)
    empty_value() = default;
#else
    empty_value() { }
#endif

    empty_value(boost::empty_init_t)
        : T() { }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template<class U, class... Args>
    empty_value(boost::empty_init_t, U&& value, Args&&... args)
        : T(std::forward<U>(value), std::forward<Args>(args)...) { }
#else
    template<class U>
    empty_value(boost::empty_init_t, U&& value)
        : T(std::forward<U>(value)) { }
#endif
#else
    template<class U>
    empty_value(boost::empty_init_t, const U& value)
        : T(value) { }

    template<class U>
    empty_value(boost::empty_init_t, U& value)
        : T(value) { }
#endif

    const T& get() const BOOST_NOEXCEPT {
        return *this;
    }

    T& get() BOOST_NOEXCEPT {
        return *this;
    }
};
#endif

} /* empty_ */

using empty_::empty_value;

BOOST_INLINE_CONSTEXPR empty_init_t empty_init = empty_init_t();

} /* boost */

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#endif

/* empty_value.hpp
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
*/