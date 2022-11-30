
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
#include <climits>

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

        template<std::size_t Bits> struct hash_combine_impl
        {
            template <typename SizeT>
            inline static SizeT fn(SizeT seed, SizeT value)
            {
                seed ^= value + 0x9e3779b9 + (seed<<6) + (seed>>2);
                return seed;
            }
        };

        template<> struct hash_combine_impl<32>
        {
            inline static boost::uint32_t fn(boost::uint32_t h1, boost::uint32_t k1)
            {
                const boost::uint32_t c1 = 0xcc9e2d51;
                const boost::uint32_t c2 = 0x1b873593;

                k1 *= c1;
                k1 = BOOST_FUNCTIONAL_HASH_ROTL32(k1,15);
                k1 *= c2;

                h1 ^= k1;
                h1 = BOOST_FUNCTIONAL_HASH_ROTL32(h1,13);
                h1 = h1*5+0xe6546b64;

                return h1;
            }
        };

        template<> struct hash_combine_impl<64>
        {
            inline static boost::uint64_t fn(boost::uint64_t h, boost::uint64_t k)
            {
                const boost::uint64_t m = (boost::uint64_t(0xc6a4a793) << 32) + 0x5bd1e995;
                const int r = 47;

                k *= m;
                k ^= k >> r;
                k *= m;

                h ^= k;
                h *= m;

                // Completely arbitrary number, to prevent 0's
                // from hashing to 0.
                h += 0xe6546b64;

                return h;
            }
        };
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
        seed = boost::hash_detail::hash_combine_impl<sizeof(std::size_t) * CHAR_BIT>::fn(seed, hasher(v));
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

#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x551))
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