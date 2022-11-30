//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_DETAIL_VALUE_HPP
#define BOOST_JSON_DETAIL_VALUE_HPP

#include <boost/json/kind.hpp>
#include <boost/json/storage_ptr.hpp>
#include <cstdint>
#include <limits>
#include <new>
#include <utility>

BOOST_JSON_NS_BEGIN
namespace detail {

struct key_t
{
};

#if 0
template<class T>
struct to_number_limit
    : std::numeric_limits<T>
{
};

template<class T>
struct to_number_limit<T const>
    : to_number_limit<T>
{
};

template<>
struct to_number_limit<long long>
{
    static constexpr long long (min)() noexcept
    {
        return -9223372036854774784;
    }

    static constexpr long long (max)() noexcept
    {
        return 9223372036854774784;
    }
};

template<>
struct to_number_limit<unsigned long long>
{
    static constexpr
    unsigned long long (min)() noexcept
    {
        return 0;
    }

    static constexpr
    unsigned long long (max)() noexcept
    {
        return 18446744073709549568ULL;
    }
};
#else

template<class T>
class to_number_limit
{
    // unsigned

    static constexpr
    double min1(std::false_type)
    {
        return 0.0;
    }

    static constexpr
    double max1(std::false_type)
    {
        return max2u(std::integral_constant<
            bool, (std::numeric_limits<T>::max)() ==
            UINT64_MAX>{});
    }

    static constexpr
    double max2u(std::false_type)
    {
        return static_cast<double>(
            (std::numeric_limits<T>::max)());
    }

    static constexpr
    double max2u(std::true_type)
    {
        return 18446744073709549568.0;
    }

    // signed

    static constexpr
    double min1(std::true_type)
    {
        return min2s(std::integral_constant<
            bool, (std::numeric_limits<T>::max)() ==
            INT64_MAX>{});
    }

    static constexpr
    double min2s(std::false_type)
    {
        return static_cast<double>(
            (std::numeric_limits<T>::min)());
    }

    static constexpr
    double min2s(std::true_type)
    {
        return -9223372036854774784.0;
    }

    static constexpr
    double max1(std::true_type)
    {
        return max2s(std::integral_constant<
            bool, (std::numeric_limits<T>::max)() ==
            INT64_MAX>{});
    }

    static constexpr
    double max2s(std::false_type)
    {
        return static_cast<double>(
            (std::numeric_limits<T>::max)());
    }

    static constexpr
    double max2s(std::true_type)
    {
        return 9223372036854774784.0;
    }

public:
    static constexpr
    double (min)() noexcept
    {
        return min1(std::is_signed<T>{});
    }

    static constexpr
    double (max)() noexcept
    {
        return max1(std::is_signed<T>{});
    }
};

#endif

struct scalar
{
    storage_ptr sp; // must come first
    kind k;         // must come second
    union
    {
        bool b;
        std::int64_t i;
        std::uint64_t u;
        double d;
    };

    explicit
    scalar(storage_ptr sp_ = {}) noexcept
        : sp(std::move(sp_))
        , k(json::kind::null)
    {
    }

    explicit
    scalar(bool b_,
        storage_ptr sp_ = {}) noexcept
        : sp(std::move(sp_))
        , k(json::kind::bool_)
        , b(b_)
    {
    }

    explicit
    scalar(std::int64_t i_,
        storage_ptr sp_ = {}) noexcept
        : sp(std::move(sp_))
        , k(json::kind::int64)
        , i(i_)
    {
    }

    explicit
    scalar(std::uint64_t u_,
        storage_ptr sp_ = {}) noexcept
        : sp(std::move(sp_))
        , k(json::kind::uint64)
        , u(u_)
    {
    }

    explicit
    scalar(double d_,
        storage_ptr sp_ = {}) noexcept
        : sp(std::move(sp_))
        , k(json::kind::double_)
        , d(d_)
    {
    }
};

struct access
{
    template<class Value, class... Args>
    static
    Value&
    construct_value(Value* p, Args&&... args)
    {
        return *reinterpret_cast<
            Value*>(::new(p) Value(
            std::forward<Args>(args)...));
    }

    template<class KeyValuePair, class... Args>
    static
    KeyValuePair&
    construct_key_value_pair(
        KeyValuePair* p, Args&&... args)
    {
        return *reinterpret_cast<
            KeyValuePair*>(::new(p)
                KeyValuePair(
                    std::forward<Args>(args)...));
    }

    template<class Value>
    static
    char const*
    release_key(
        Value& jv,
        std::size_t& len) noexcept
    {
        BOOST_ASSERT(jv.is_string());
        jv.str_.sp_.~storage_ptr();
        return jv.str_.impl_.release_key(len);
    }

    using index_t = std::uint32_t;

    template<class KeyValuePair>
    static
    index_t&
    next(KeyValuePair& e) noexcept
    {
        return e.next_;
    }

    template<class KeyValuePair>
    static
    index_t const&
    next(KeyValuePair const& e) noexcept
    {
        return e.next_;
    }
};

} // detail
BOOST_JSON_NS_END

#endif

/* value.hpp
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
*/