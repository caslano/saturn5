
// Copyright 2005-2009 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  Based on Peter Dimov's proposal
//  http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2005/n1756.pdf
//  issue 6.18.

// This implements the extensions to the standard.
// It's undocumented, so you shouldn't use it....

#if !defined(BOOST_FUNCTIONAL_HASH_EXTENSIONS_HPP)
#define BOOST_FUNCTIONAL_HASH_EXTENSIONS_HPP

#include <boost/config.hpp>
#if defined(BOOST_HAS_PRAGMA_ONCE)
#pragma once
#endif

#include <boost/container_hash/hash.hpp>
#include <boost/detail/container_fwd.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/static_assert.hpp>

#if !defined(BOOST_NO_CXX11_HDR_ARRAY)
#   include <array>
#endif

#if !defined(BOOST_NO_CXX11_HDR_TUPLE)
#   include <tuple>
#endif

#include <memory>

#if defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
#include <boost/type_traits/is_array.hpp>
#endif

namespace boost
{
    template <class A, class B>
    std::size_t hash_value(std::pair<A, B> const&);
    template <class T, class A>
    std::size_t hash_value(std::vector<T, A> const&);
    template <class T, class A>
    std::size_t hash_value(std::list<T, A> const& v);
    template <class T, class A>
    std::size_t hash_value(std::deque<T, A> const& v);
    template <class K, class C, class A>
    std::size_t hash_value(std::set<K, C, A> const& v);
    template <class K, class C, class A>
    std::size_t hash_value(std::multiset<K, C, A> const& v);
    template <class K, class T, class C, class A>
    std::size_t hash_value(std::map<K, T, C, A> const& v);
    template <class K, class T, class C, class A>
    std::size_t hash_value(std::multimap<K, T, C, A> const& v);

    template <class T>
    std::size_t hash_value(std::complex<T> const&);

    template <class A, class B>
    std::size_t hash_value(std::pair<A, B> const& v)
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, v.first);
        boost::hash_combine(seed, v.second);
        return seed;
    }

    template <class T, class A>
    std::size_t hash_value(std::vector<T, A> const& v)
    {
        return boost::hash_range(v.begin(), v.end());
    }

    template <class T, class A>
    std::size_t hash_value(std::list<T, A> const& v)
    {
        return boost::hash_range(v.begin(), v.end());
    }

    template <class T, class A>
    std::size_t hash_value(std::deque<T, A> const& v)
    {
        return boost::hash_range(v.begin(), v.end());
    }

    template <class K, class C, class A>
    std::size_t hash_value(std::set<K, C, A> const& v)
    {
        return boost::hash_range(v.begin(), v.end());
    }

    template <class K, class C, class A>
    std::size_t hash_value(std::multiset<K, C, A> const& v)
    {
        return boost::hash_range(v.begin(), v.end());
    }

    template <class K, class T, class C, class A>
    std::size_t hash_value(std::map<K, T, C, A> const& v)
    {
        return boost::hash_range(v.begin(), v.end());
    }

    template <class K, class T, class C, class A>
    std::size_t hash_value(std::multimap<K, T, C, A> const& v)
    {
        return boost::hash_range(v.begin(), v.end());
    }

    template <class T>
    std::size_t hash_value(std::complex<T> const& v)
    {
        boost::hash<T> hasher;
        std::size_t seed = hasher(v.imag());
        seed ^= hasher(v.real()) + (seed<<6) + (seed>>2);
        return seed;
    }

#if !defined(BOOST_NO_CXX11_HDR_ARRAY)
    template <class T, std::size_t N>
    std::size_t hash_value(std::array<T, N> const& v)
    {
        return boost::hash_range(v.begin(), v.end());
    }
#endif

#if !defined(BOOST_NO_CXX11_HDR_TUPLE)
    namespace hash_detail {
        template <std::size_t I, typename T>
        inline typename boost::enable_if_c<(I == std::tuple_size<T>::value),
                void>::type
            hash_combine_tuple(std::size_t&, T const&)
        {
        }

        template <std::size_t I, typename T>
        inline typename boost::enable_if_c<(I < std::tuple_size<T>::value),
                void>::type
            hash_combine_tuple(std::size_t& seed, T const& v)
        {
            boost::hash_combine(seed, std::get<I>(v));
            boost::hash_detail::hash_combine_tuple<I + 1>(seed, v);
        }

        template <typename T>
        inline std::size_t hash_tuple(T const& v)
        {
            std::size_t seed = 0;
            boost::hash_detail::hash_combine_tuple<0>(seed, v);
            return seed;
        }
    }

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template <typename... T>
    inline std::size_t hash_value(std::tuple<T...> const& v)
    {
        return boost::hash_detail::hash_tuple(v);
    }
#else

    inline std::size_t hash_value(std::tuple<> const& v)
    {
        return boost::hash_detail::hash_tuple(v);
    }

    template<typename A0>
    inline std::size_t hash_value(std::tuple<A0> const& v)
    {
        return boost::hash_detail::hash_tuple(v);
    }

    template<typename A0, typename A1>
    inline std::size_t hash_value(std::tuple<A0, A1> const& v)
    {
        return boost::hash_detail::hash_tuple(v);
    }

    template<typename A0, typename A1, typename A2>
    inline std::size_t hash_value(std::tuple<A0, A1, A2> const& v)
    {
        return boost::hash_detail::hash_tuple(v);
    }

    template<typename A0, typename A1, typename A2, typename A3>
    inline std::size_t hash_value(std::tuple<A0, A1, A2, A3> const& v)
    {
        return boost::hash_detail::hash_tuple(v);
    }

    template<typename A0, typename A1, typename A2, typename A3, typename A4>
    inline std::size_t hash_value(std::tuple<A0, A1, A2, A3, A4> const& v)
    {
        return boost::hash_detail::hash_tuple(v);
    }

    template<typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
    inline std::size_t hash_value(std::tuple<A0, A1, A2, A3, A4, A5> const& v)
    {
        return boost::hash_detail::hash_tuple(v);
    }

    template<typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
    inline std::size_t hash_value(std::tuple<A0, A1, A2, A3, A4, A5, A6> const& v)
    {
        return boost::hash_detail::hash_tuple(v);
    }

    template<typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
    inline std::size_t hash_value(std::tuple<A0, A1, A2, A3, A4, A5, A6, A7> const& v)
    {
        return boost::hash_detail::hash_tuple(v);
    }

    template<typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
    inline std::size_t hash_value(std::tuple<A0, A1, A2, A3, A4, A5, A6, A7, A8> const& v)
    {
        return boost::hash_detail::hash_tuple(v);
    }

    template<typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
    inline std::size_t hash_value(std::tuple<A0, A1, A2, A3, A4, A5, A6, A7, A8, A9> const& v)
    {
        return boost::hash_detail::hash_tuple(v);
    }

#endif

#endif

#if !defined(BOOST_NO_CXX11_SMART_PTR)
    template <typename T>
    inline std::size_t hash_value(std::shared_ptr<T> const& x) {
        return boost::hash_value(x.get());
    }

    template <typename T, typename Deleter>
    inline std::size_t hash_value(std::unique_ptr<T, Deleter> const& x) {
        return boost::hash_value(x.get());
    }
#endif

    //
    // call_hash_impl
    //

    // On compilers without function template ordering, this deals with arrays.

#if defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
    namespace hash_detail
    {
        template <bool IsArray>
        struct call_hash_impl
        {
            template <class T>
            struct inner
            {
                static std::size_t call(T const& v)
                {
                    using namespace boost;
                    return hash_value(v);
                }
            };
        };

        template <>
        struct call_hash_impl<true>
        {
            template <class Array>
            struct inner
            {
                static std::size_t call(Array const& v)
                {
                    const int size = sizeof(v) / sizeof(*v);
                    return boost::hash_range(v, v + size);
                }
            };
        };

        template <class T>
        struct call_hash
            : public call_hash_impl<boost::is_array<T>::value>
                ::BOOST_NESTED_TEMPLATE inner<T>
        {
        };
    }
#endif // BOOST_NO_FUNCTION_TEMPLATE_ORDERING

    //
    // boost::hash
    //


#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

    template <class T> struct hash
        : boost::hash_detail::hash_base<T>
    {
#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
        std::size_t operator()(T const& val) const
        {
            return hash_value(val);
        }
#else
        std::size_t operator()(T const& val) const
        {
            return hash_detail::call_hash<T>::call(val);
        }
#endif
    };

#if BOOST_WORKAROUND(__DMC__, <= 0x848)
    template <class T, unsigned int n> struct hash<T[n]>
        : boost::hash_detail::hash_base<T[n]>
    {
        std::size_t operator()(const T* val) const
        {
            return boost::hash_range(val, val+n);
        }
    };
#endif

#else // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

    // On compilers without partial specialization, boost::hash<T>
    // has already been declared to deal with pointers, so just
    // need to supply the non-pointer version of hash_impl.

    namespace hash_detail
    {
        template <bool IsPointer>
        struct hash_impl;

        template <>
        struct hash_impl<false>
        {
            template <class T>
            struct inner
                : boost::hash_detail::hash_base<T>
            {
#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
                std::size_t operator()(T const& val) const
                {
                    return hash_value(val);
                }
#else
                std::size_t operator()(T const& val) const
                {
                    return hash_detail::call_hash<T>::call(val);
                }
#endif
            };
        };
    }
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
}

#endif

/* extensions.hpp
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
*/