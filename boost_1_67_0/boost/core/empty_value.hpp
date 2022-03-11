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
    template<class... Args>
    explicit empty_value(boost::empty_init_t, Args&&... args)
        : value_(std::forward<Args>(args)...) { }
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
    template<class... Args>
    explicit empty_value(boost::empty_init_t, Args&&... args)
        : T(std::forward<Args>(args)...) { }
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

#endif

/* empty_value.hpp
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
*/