
// Copyright 2005-2014 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  Based on Peter Dimov's proposal
//  http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2005/n1756.pdf
//  issue 6.18.
//
//  This also contains public domain code from MurmurHash. From the
//  MurmurHash header:

// MurmurHash3 was written by Austin Appleby, and is placed in the public
// domain. The author hereby disclaims copyright to this source code.

#if !defined(BOOST_FUNCTIONAL_HASH_HASH_HPP)
#define BOOST_FUNCTIONAL_HASH_HASH_HPP

#include <boost/container_hash/hash_fwd.hpp>
#include <functional>
#include <iterator>
#include <boost/container_hash/detail/hash_float.hpp>
#include <string>
#include <boost/limits.hpp>
#include <boost/type_traits/is_enum.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/cstdint.hpp>

#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#include <boost/type_traits/is_pointer.hpp>
#endif

#if !defined(BOOST_NO_CXX11_HDR_TYPEINDEX)
#include <typeindex>
#endif

#if !defined(BOOST_NO_CXX11_HDR_SYSTEM_ERROR)
#include <system_error>
#endif

#if defined(BOOST_MSVC)
#pragma warning(push)

#if BOOST_MSVC >= 1400
#pragma warning(disable:6295) // Ill-defined for-loop : 'unsigned int' values
                              // are always of range '0' to '4294967295'.
                              // Loop executes infinitely.
#endif

#endif

#if BOOST_WORKAROUND(__GNUC__, < 3) \
    && !defined(__SGI_STL_PORT) && !defined(_STLPORT_VERSION)
#define BOOST_HASH_CHAR_TRAITS string_char_traits
#else
#define BOOST_HASH_CHAR_TRAITS char_traits
#endif

#if defined(_MSC_VER)
#   define BOOST_FUNCTIONAL_HASH_ROTL32(x, r) _rotl(x,r)
#else
#   define BOOST_FUNCTIONAL_HASH_ROTL32(x, r) (x << r) | (x >> (32 - r))
#endif

// Detect whether standard library has C++17 headers

#if !defined(BOOST_HASH_CXX17)
#   if defined(BOOST_MSVC)
#       if defined(_HAS_CXX17) && _HAS_CXX17
#           define BOOST_HASH_CXX17 1
#       endif
#   elif defined(__cplusplus) && __cplusplus >= 201703
#       define BOOST_HASH_CXX17 1
#   endif
#endif

#if !defined(BOOST_HASH_CXX17)
#   define BOOST_HASH_CXX17 0
#endif

#if BOOST_HASH_CXX17 && defined(__has_include)
#   if !defined(BOOST_HASH_HAS_STRING_VIEW) && __has_include(<string_view>)
#       define BOOST_HASH_HAS_STRING_VIEW 1
#   endif
#   if !defined(BOOST_HASH_HAS_OPTIONAL) && __has_include(<optional>)
#       define BOOST_HASH_HAS_OPTIONAL 1
#   endif
#   if !defined(BOOST_HASH_HAS_VARIANT) && __has_include(<variant>)
#       define BOOST_HASH_HAS_VARIANT 1
#   endif
#endif

#if !defined(BOOST_HASH_HAS_STRING_VIEW)
#   define BOOST_HASH_HAS_STRING_VIEW 0
#endif

#if !defined(BOOST_HASH_HAS_OPTIONAL)
#   define BOOST_HASH_HAS_OPTIONAL 0
#endif

#if !defined(BOOST_HASH_HAS_VARIANT)
#   define BOOST_HASH_HAS_VARIANT 0
#endif

#if BOOST_HASH_HAS_STRING_VIEW
#   include <string_view>
#endif

#if BOOST_HASH_HAS_OPTIONAL
#   include <optional>
#endif

#if BOOST_HASH_HAS_VARIANT
#   include <variant>
#endif

namespace boost
{
    namespace hash_detail
    {
#if defined(BOOST_NO_CXX98_FUNCTION_BASE)
        template <typename T>
        struct hash_base
        {
            typedef T argument_type;
            typedef std::size_t result_type;
        };
#else
        template <typename T>
        struct hash_base : std::unary_function<T, std::size_t> {};
#endif

        struct enable_hash_value { typedef std::size_t type; };

        template <typename T> struct basic_numbers {};
        template <typename T> struct long_numbers;
        template <typename T> struct ulong_numbers;
        template <typename T> struct float_numbers {};

        template <> struct basic_numbers<bool> :
            boost::hash_detail::enable_hash_value {};
        template <> struct basic_numbers<char> :
            boost::hash_detail::enable_hash_value {};
        template <> struct basic_numbers<unsigned char> :
            boost::hash_detail::enable_hash_value {};
        template <> struct basic_numbers<signed char> :
            boost::hash_detail::enable_hash_value {};
        template <> struct basic_numbers<short> :
            boost::hash_detail::enable_hash_value {};
        template <> struct basic_numbers<unsigned short> :
            boost::hash_detail::enable_hash_value {};
        template <> struct basic_numbers<int> :
            boost::hash_detail::enable_hash_value {};
        template <> struct basic_numbers<unsigned int> :
            boost::hash_detail::enable_hash_value {};
        template <> struct basic_numbers<long> :
            boost::hash_detail::enable_hash_value {};
        template <> struct basic_numbers<unsigned long> :
            boost::hash_detail::enable_hash_value {};

#if !defined(BOOST_NO_INTRINSIC_WCHAR_T)
        template <> struct basic_numbers<wchar_t> :
            boost::hash_detail::enable_hash_value {};
#endif

#if !defined(BOOST_NO_CXX11_CHAR16_T)
        template <> struct basic_numbers<char16_t> :
            boost::hash_detail::enable_hash_value {};
#endif

#if !defined(BOOST_NO_CXX11_CHAR32_T)
        template <> struct basic_numbers<char32_t> :
            boost::hash_detail::enable_hash_value {};
#endif

        // long_numbers is defined like this to allow for separate
        // specialization for long_long and int128_type, in case
        // they conflict.
        template <typename T> struct long_numbers2 {};
        template <typename T> struct ulong_numbers2 {};
        template <typename T> struct long_numbers : long_numbers2<T> {};
        template <typename T> struct ulong_numbers : ulong_numbers2<T> {};

#if !defined(BOOST_NO_LONG_LONG)
        template <> struct long_numbers<boost::long_long_type> :
            boost::hash_detail::enable_hash_value {};
        template <> struct ulong_numbers<boost::ulong_long_type> :
            boost::hash_detail::enable_hash_value {};
#endif

#if defined(BOOST_HAS_INT128)
        template <> struct long_numbers2<boost::int128_type> :
            boost::hash_detail::enable_hash_value {};
        template <> struct ulong_numbers2<boost::uint128_type> :
            boost::hash_detail::enable_hash_value {};
#endif

        template <> struct float_numbers<float> :
            boost::hash_detail::enable_hash_value {};
        template <> struct float_numbers<double> :
            boost::hash_detail::enable_hash_value {};
        template <> struct float_numbers<long double> :
            boost::hash_detail::enable_hash_value {};
    }

    template <typename T>
    typename boost::hash_detail::basic_numbers<T>::type hash_value(T);
    template <typename T>
    typename boost::hash_detail::long_numbers<T>::type hash_value(T);
    template <typename T>
    typename boost::hash_detail::ulong_numbers<T>::type hash_value(T);

    template <typename T>
    typename boost::enable_if<boost::is_enum<T>, std::size_t>::type
        hash_value(T);

#if !BOOST_WORKAROUND(__DMC__, <= 0x848)
    template <class T> std::size_t hash_value(T* const&);
#else
    template <class T> std::size_t hash_value(T*);
#endif

#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
    template< class T, unsigned N >
    std::size_t hash_value(const T (&x)[N]);

    template< class T, unsigned N >
    std::size_t hash_value(T (&x)[N]);
#endif

    template <class Ch, class A>
    std::size_t hash_value(
        std::basic_string<Ch, std::BOOST_HASH_CHAR_TRAITS<Ch>, A> const&);

#if BOOST_HASH_HAS_STRING_VIEW
    template <class Ch>
    std::size_t hash_value(
        std::basic_string_view<Ch, std::BOOST_HASH_CHAR_TRAITS<Ch> > const&);
#endif

    template <typename T>
    typename boost::hash_detail::float_numbers<T>::type hash_value(T);

#if BOOST_HASH_HAS_OPTIONAL
    template <typename T>
    std::size_t hash_value(std::optional<T> const&);
#endif

#if BOOST_HASH_HAS_VARIANT
    std::size_t hash_value(std::monostate);
    template <typename... Types>
    std::size_t hash_value(std::variant<Types...> const&);
#endif

#if !defined(BOOST_NO_CXX11_HDR_TYPEINDEX)
    std::size_t hash_value(std::type_index);
#endif

#if !defined(BOOST_NO_CXX11_HDR_SYSTEM_ERROR)
    std::size_t hash_value(std::error_code const&);
    std::size_t hash_value(std::error_condition const&);
#endif

    // Implementation

    namespace hash_detail
    {
        template <class T>
        inline std::size_t hash_value_signed(T val)
        {
             const unsigned int size_t_bits = std::numeric_limits<std::size_t>::digits;
             // ceiling(std::numeric_limits<T>::digits / size_t_bits) - 1
             const int length = (std::numeric_limits<T>::digits - 1)
                 / static_cast<int>(size_t_bits);

             std::size_t seed = 0;
             T positive = val < 0 ? -1 - val : val;

             // Hopefully, this loop can be unrolled.
             for(unsigned int i = length * size_t_bits; i > 0; i -= size_t_bits)
             {
                 seed ^= (std::size_t) (positive >> i) + (seed<<6) + (seed>>2);
             }
             seed ^= (std::size_t) val + (seed<<6) + (seed>>2);

             return seed;
        }

        template <class T>
        inline std::size_t hash_value_unsigned(T val)
        {
             const unsigned int size_t_bits = std::numeric_limits<std::size_t>::digits;
             // ceiling(std::numeric_limits<T>::digits / size_t_bits) - 1
             const int length = (std::numeric_limits<T>::digits - 1)
                 / static_cast<int>(size_t_bits);

             std::size_t seed = 0;

             // Hopefully, this loop can be unrolled.
             for(unsigned int i = length * size_t_bits; i > 0; i -= size_t_bits)
             {
                 seed ^= (std::size_t) (val >> i) + (seed<<6) + (seed>>2);
             }
             seed ^= (std::size_t) val + (seed<<6) + (seed>>2);

             return seed;
        }

        template <typename SizeT>
        inline void hash_combine_impl(SizeT& seed, SizeT value)
        {
            seed ^= value + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }

        inline void hash_combine_impl(boost::uint32_t& h1,
                boost::uint32_t k1)
        {
            const uint32_t c1 = 0xcc9e2d51;
            const uint32_t c2 = 0x1b873593;

            k1 *= c1;
            k1 = BOOST_FUNCTIONAL_HASH_ROTL32(k1,15);
            k1 *= c2;

            h1 ^= k1;
            h1 = BOOST_FUNCTIONAL_HASH_ROTL32(h1,13);
            h1 = h1*5+0xe6546b64;
        }


// Don't define 64-bit hash combine on platforms without 64 bit integers,
// and also not for 32-bit gcc as it warns about the 64-bit constant.
#if !defined(BOOST_NO_INT64_T) && \
        !(defined(__GNUC__) && ULONG_MAX == 0xffffffff)

        inline void hash_combine_impl(boost::uint64_t& h,
                boost::uint64_t k)
        {
            const boost::uint64_t m = UINT64_C(0xc6a4a7935bd1e995);
            const int r = 47;

            k *= m;
            k ^= k >> r;
            k *= m;

            h ^= k;
            h *= m;

            // Completely arbitrary number, to prevent 0's
            // from hashing to 0.
            h += 0xe6546b64;
        }

#endif // BOOST_NO_INT64_T
    }

    template <typename T>
    typename boost::hash_detail::basic_numbers<T>::type hash_value(T v)
    {
        return static_cast<std::size_t>(v);
    }

    template <typename T>
    typename boost::hash_detail::long_numbers<T>::type hash_value(T v)
    {
        return hash_detail::hash_value_signed(v);
    }

    template <typename T>
    typename boost::hash_detail::ulong_numbers<T>::type hash_value(T v)
    {
        return hash_detail::hash_value_unsigned(v);
    }

    template <typename T>
    typename boost::enable_if<boost::is_enum<T>, std::size_t>::type
        hash_value(T v)
    {
        return static_cast<std::size_t>(v);
    }

    // Implementation by Alberto Barbati and Dave Harris.
#if !BOOST_WORKAROUND(__DMC__, <= 0x848)
    template <class T> std::size_t hash_value(T* const& v)
#else
    template <class T> std::size_t hash_value(T* v)
#endif
    {
#if defined(__VMS) && __INITIAL_POINTER_SIZE == 64
    // for some reason ptrdiff_t on OpenVMS compiler with
    // 64 bit is not 64 bit !!!
        std::size_t x = static_cast<std::size_t>(
           reinterpret_cast<long long int>(v));
#else
        std::size_t x = static_cast<std::size_t>(
           reinterpret_cast<std::ptrdiff_t>(v));
#endif
        return x + (x >> 3);
    }

#if defined(BOOST_MSVC)
#pragma warning(push)
#if BOOST_MSVC <= 1400
#pragma warning(disable:4267) // 'argument' : conversion from 'size_t' to
                              // 'unsigned int', possible loss of data
                              // A misguided attempt to detect 64-bit
                              // incompatability.
#endif
#endif

    template <class T>
    inline void hash_combine(std::size_t& seed, T const& v)
    {
        boost::hash<T> hasher;
        return boost::hash_detail::hash_combine_impl(seed, hasher(v));
    }

#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif

    template <class It>
    inline std::size_t hash_range(It first, It last)
    {
        std::size_t seed = 0;

        for(; first != last; ++first)
        {
            hash_combine<typename std::iterator_traits<It>::value_type>(seed, *first);
        }

        return seed;
    }

    template <class It>
    inline void hash_range(std::size_t& seed, It first, It last)
    {
        for(; first != last; ++first)
        {
            hash_combine<typename std::iterator_traits<It>::value_type>(seed, *first);
        }
    }

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x551))
    template <class T>
    inline std::size_t hash_range(T* first, T* last)
    {
        std::size_t seed = 0;

        for(; first != last; ++first)
        {
            boost::hash<T> hasher;
            seed ^= hasher(*first) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }

        return seed;
    }

    template <class T>
    inline void hash_range(std::size_t& seed, T* first, T* last)
    {
        for(; first != last; ++first)
        {
            boost::hash<T> hasher;
            seed ^= hasher(*first) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }
    }
#endif

#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
    template< class T, unsigned N >
    inline std::size_t hash_value(const T (&x)[N])
    {
        return hash_range(x, x + N);
    }

    template< class T, unsigned N >
    inline std::size_t hash_value(T (&x)[N])
    {
        return hash_range(x, x + N);
    }
#endif

    template <class Ch, class A>
    inline std::size_t hash_value(
        std::basic_string<Ch, std::BOOST_HASH_CHAR_TRAITS<Ch>, A> const& v)
    {
        return hash_range(v.begin(), v.end());
    }

#if BOOST_HASH_HAS_STRING_VIEW
    template <class Ch>
    inline std::size_t hash_value(
        std::basic_string_view<Ch, std::BOOST_HASH_CHAR_TRAITS<Ch> > const& v)
    {
        return hash_range(v.begin(), v.end());
    }
#endif

    template <typename T>
    typename boost::hash_detail::float_numbers<T>::type hash_value(T v)
    {
        return boost::hash_detail::float_hash_value(v);
    }

#if BOOST_HASH_HAS_OPTIONAL
    template <typename T>
    inline std::size_t hash_value(std::optional<T> const& v) {
        if (!v) {
            // Arbitray value for empty optional.
            return 0x12345678;
        } else {
            boost::hash<T> hf;
            return hf(*v);
        }
    }
#endif

#if BOOST_HASH_HAS_VARIANT
    inline std::size_t hash_value(std::monostate) {
        return 0x87654321;
    }

    template <typename... Types>
    inline std::size_t hash_value(std::variant<Types...> const& v) {
        std::size_t seed = 0;
        hash_combine(seed, v.index());
        std::visit([&seed](auto&& x) { hash_combine(seed, x); }, v);
        return seed;
    }
#endif


#if !defined(BOOST_NO_CXX11_HDR_TYPEINDEX)
    inline std::size_t hash_value(std::type_index v)
    {
        return v.hash_code();
    }
#endif

#if !defined(BOOST_NO_CXX11_HDR_SYSTEM_ERROR)
    inline std::size_t hash_value(std::error_code const& v) {
        std::size_t seed = 0;
        hash_combine(seed, v.value());
        hash_combine(seed, &v.category());
        return seed;
    }

    inline std::size_t hash_value(std::error_condition const& v) {
        std::size_t seed = 0;
        hash_combine(seed, v.value());
        hash_combine(seed, &v.category());
        return seed;
    }
#endif

    //
    // boost::hash
    //

    // Define the specializations required by the standard. The general purpose
    // boost::hash is defined later in extensions.hpp if
    // BOOST_HASH_NO_EXTENSIONS is not defined.

    // BOOST_HASH_SPECIALIZE - define a specialization for a type which is
    // passed by copy.
    //
    // BOOST_HASH_SPECIALIZE_REF - define a specialization for a type which is
    // passed by const reference.
    //
    // These are undefined later.

#define BOOST_HASH_SPECIALIZE(type) \
    template <> struct hash<type> \
         : public boost::hash_detail::hash_base<type> \
    { \
        std::size_t operator()(type v) const \
        { \
            return boost::hash_value(v); \
        } \
    };

#define BOOST_HASH_SPECIALIZE_REF(type) \
    template <> struct hash<type> \
         : public boost::hash_detail::hash_base<type> \
    { \
        std::size_t operator()(type const& v) const \
        { \
            return boost::hash_value(v); \
        } \
    };

#define BOOST_HASH_SPECIALIZE_TEMPLATE_REF(type) \
    struct hash<type> \
         : public boost::hash_detail::hash_base<type> \
    { \
        std::size_t operator()(type const& v) const \
        { \
            return boost::hash_value(v); \
        } \
    };

    BOOST_HASH_SPECIALIZE(bool)
    BOOST_HASH_SPECIALIZE(char)
    BOOST_HASH_SPECIALIZE(signed char)
    BOOST_HASH_SPECIALIZE(unsigned char)
#if !defined(BOOST_NO_INTRINSIC_WCHAR_T)
    BOOST_HASH_SPECIALIZE(wchar_t)
#endif
#if !defined(BOOST_NO_CXX11_CHAR16_T)
    BOOST_HASH_SPECIALIZE(char16_t)
#endif
#if !defined(BOOST_NO_CXX11_CHAR32_T)
    BOOST_HASH_SPECIALIZE(char32_t)
#endif
    BOOST_HASH_SPECIALIZE(short)
    BOOST_HASH_SPECIALIZE(unsigned short)
    BOOST_HASH_SPECIALIZE(int)
    BOOST_HASH_SPECIALIZE(unsigned int)
    BOOST_HASH_SPECIALIZE(long)
    BOOST_HASH_SPECIALIZE(unsigned long)

    BOOST_HASH_SPECIALIZE(float)
    BOOST_HASH_SPECIALIZE(double)
    BOOST_HASH_SPECIALIZE(long double)

    BOOST_HASH_SPECIALIZE_REF(std::string)
#if !defined(BOOST_NO_STD_WSTRING) && !defined(BOOST_NO_INTRINSIC_WCHAR_T)
    BOOST_HASH_SPECIALIZE_REF(std::wstring)
#endif
#if !defined(BOOST_NO_CXX11_CHAR16_T)
    BOOST_HASH_SPECIALIZE_REF(std::basic_string<char16_t>)
#endif
#if !defined(BOOST_NO_CXX11_CHAR32_T)
    BOOST_HASH_SPECIALIZE_REF(std::basic_string<char32_t>)
#endif

#if BOOST_HASH_HAS_STRING_VIEW
    BOOST_HASH_SPECIALIZE_REF(std::string_view)
#   if !defined(BOOST_NO_STD_WSTRING) && !defined(BOOST_NO_INTRINSIC_WCHAR_T)
    BOOST_HASH_SPECIALIZE_REF(std::wstring_view)
#   endif
#   if !defined(BOOST_NO_CXX11_CHAR16_T)
    BOOST_HASH_SPECIALIZE_REF(std::basic_string_view<char16_t>)
#   endif
#   if !defined(BOOST_NO_CXX11_CHAR32_T)
    BOOST_HASH_SPECIALIZE_REF(std::basic_string_view<char32_t>)
#   endif
#endif

#if !defined(BOOST_NO_LONG_LONG)
    BOOST_HASH_SPECIALIZE(boost::long_long_type)
    BOOST_HASH_SPECIALIZE(boost::ulong_long_type)
#endif

#if defined(BOOST_HAS_INT128)
    BOOST_HASH_SPECIALIZE(boost::int128_type)
    BOOST_HASH_SPECIALIZE(boost::uint128_type)
#endif

#if BOOST_HASH_HAS_OPTIONAL
    template <typename T>
    BOOST_HASH_SPECIALIZE_TEMPLATE_REF(std::optional<T>)
#endif

#if !defined(BOOST_HASH_HAS_VARIANT)
    template <typename... T>
    BOOST_HASH_SPECIALIZE_TEMPLATE_REF(std::variant<T...>)
    BOOST_HASH_SPECIALIZE(std::monostate)
#endif

#if !defined(BOOST_NO_CXX11_HDR_TYPEINDEX)
    BOOST_HASH_SPECIALIZE(std::type_index)
#endif

#undef BOOST_HASH_SPECIALIZE
#undef BOOST_HASH_SPECIALIZE_REF
#undef BOOST_HASH_SPECIALIZE_TEMPLATE_REF

// Specializing boost::hash for pointers.

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

    template <class T>
    struct hash<T*>
        : public boost::hash_detail::hash_base<T*>
    {
        std::size_t operator()(T* v) const
        {
#if !BOOST_WORKAROUND(__SUNPRO_CC, <= 0x590)
            return boost::hash_value(v);
#else
            std::size_t x = static_cast<std::size_t>(
                reinterpret_cast<std::ptrdiff_t>(v));

            return x + (x >> 3);
#endif
        }
    };

#else

    // For compilers without partial specialization, we define a
    // boost::hash for all remaining types. But hash_impl is only defined
    // for pointers in 'extensions.hpp' - so when BOOST_HASH_NO_EXTENSIONS
    // is defined there will still be a compile error for types not supported
    // in the standard.

    namespace hash_detail
    {
        template <bool IsPointer>
        struct hash_impl;

        template <>
        struct hash_impl<true>
        {
            template <class T>
            struct inner
                : public boost::hash_detail::hash_base<T>
            {
                std::size_t operator()(T val) const
                {
#if !BOOST_WORKAROUND(__SUNPRO_CC, <= 590)
                    return boost::hash_value(val);
#else
                    std::size_t x = static_cast<std::size_t>(
                        reinterpret_cast<std::ptrdiff_t>(val));

                    return x + (x >> 3);
#endif
                }
            };
        };
    }

    template <class T> struct hash
        : public boost::hash_detail::hash_impl<boost::is_pointer<T>::value>
            ::BOOST_NESTED_TEMPLATE inner<T>
    {
    };

#endif
}

#undef BOOST_HASH_CHAR_TRAITS
#undef BOOST_FUNCTIONAL_HASH_ROTL32

#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif

#endif // BOOST_FUNCTIONAL_HASH_HASH_HPP

// Include this outside of the include guards in case the file is included
// twice - once with BOOST_HASH_NO_EXTENSIONS defined, and then with it
// undefined.

#if !defined(BOOST_HASH_NO_EXTENSIONS) \
    && !defined(BOOST_FUNCTIONAL_HASH_EXTENSIONS_HPP)
#include <boost/container_hash/extensions.hpp>
#endif

/* hash.hpp
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
*/