/* boost integer_traits.hpp header file
 *
 * Copyright Jens Maurer 2000
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 *
 * $Id$
 *
 * Idea by Beman Dawes, Ed Brey, Steve Cleary, and Nathan Myers
 */

//  See https://www.boost.org/libs/integer for documentation.


#ifndef BOOST_INTEGER_TRAITS_HPP
#define BOOST_INTEGER_TRAITS_HPP

#include <boost/config.hpp>
#include <boost/limits.hpp>

// These are an implementation detail and not part of the interface
#include <limits.h>
// we need wchar.h for WCHAR_MAX/MIN but not all platforms provide it,
// and some may have <wchar.h> but not <cwchar> ...
#if !defined(BOOST_NO_INTRINSIC_WCHAR_T) && (!defined(BOOST_NO_CWCHAR) || defined(sun) || defined(__sun) || defined(__QNX__))
#include <wchar.h>
#endif

//
// We simply cannot include this header on gcc without getting copious warnings of the kind:
//
// ../../../boost/integer_traits.hpp:164:66: warning: use of C99 long long integer constant
//
// And yet there is no other reasonable implementation, so we declare this a system header
// to suppress these warnings.
//
#if defined(__GNUC__) && (__GNUC__ >= 4)
#pragma GCC system_header
#endif

namespace boost {
template<class T>
class integer_traits : public std::numeric_limits<T>
{
public:
  BOOST_STATIC_CONSTANT(bool, is_integral = false);
};

namespace detail {
template<class T, T min_val, T max_val>
class integer_traits_base
{
public:
  BOOST_STATIC_CONSTANT(bool, is_integral = true);
  BOOST_STATIC_CONSTANT(T, const_min = min_val);
  BOOST_STATIC_CONSTANT(T, const_max = max_val);
};

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
//  A definition is required even for integral static constants
template<class T, T min_val, T max_val>
const bool integer_traits_base<T, min_val, max_val>::is_integral;

template<class T, T min_val, T max_val>
const T integer_traits_base<T, min_val, max_val>::const_min;

template<class T, T min_val, T max_val>
const T integer_traits_base<T, min_val, max_val>::const_max;
#endif

} // namespace detail

template<>
class integer_traits<bool>
  : public std::numeric_limits<bool>,
    public detail::integer_traits_base<bool, false, true>
{ };

template<>
class integer_traits<char>
  : public std::numeric_limits<char>,
    public detail::integer_traits_base<char, CHAR_MIN, CHAR_MAX>
{ };

template<>
class integer_traits<signed char>
  : public std::numeric_limits<signed char>,
    public detail::integer_traits_base<signed char, SCHAR_MIN, SCHAR_MAX>
{ };

template<>
class integer_traits<unsigned char>
  : public std::numeric_limits<unsigned char>,
    public detail::integer_traits_base<unsigned char, 0, UCHAR_MAX>
{ };

#ifndef BOOST_NO_INTRINSIC_WCHAR_T
template<>
class integer_traits<wchar_t>
  : public std::numeric_limits<wchar_t>,
    // Don't trust WCHAR_MIN and WCHAR_MAX with Mac OS X's native
    // library: they are wrong!
#if defined(WCHAR_MIN) && defined(WCHAR_MAX) && !defined(__APPLE__)
    public detail::integer_traits_base<wchar_t, WCHAR_MIN, WCHAR_MAX>
#elif defined(BOOST_BORLANDC) || defined(__CYGWIN__) || defined(__MINGW32__) || (defined(__BEOS__) && defined(__GNUC__))
    // No WCHAR_MIN and WCHAR_MAX, whar_t is short and unsigned:
    public detail::integer_traits_base<wchar_t, 0, 0xffff>
#elif (defined(__sgi) && (!defined(__SGI_STL_PORT) || __SGI_STL_PORT < 0x400))\
    || (defined __APPLE__)\
    || (defined(__OpenBSD__) && defined(__GNUC__))\
    || (defined(__NetBSD__) && defined(__GNUC__))\
    || (defined(__FreeBSD__) && defined(__GNUC__))\
    || (defined(__DragonFly__) && defined(__GNUC__))\
    || (defined(__hpux) && defined(__GNUC__) && (__GNUC__ == 3) && !defined(__SGI_STL_PORT))
    // No WCHAR_MIN and WCHAR_MAX, wchar_t has the same range as int.
    //  - SGI MIPSpro with native library
    //  - gcc 3.x on HP-UX
    //  - Mac OS X with native library
    //  - gcc on FreeBSD, OpenBSD and NetBSD
    public detail::integer_traits_base<wchar_t, INT_MIN, INT_MAX>
#else
#error No WCHAR_MIN and WCHAR_MAX present, please adjust integer_traits<> for your compiler.
#endif
{ };
#endif // BOOST_NO_INTRINSIC_WCHAR_T

template<>
class integer_traits<short>
  : public std::numeric_limits<short>,
    public detail::integer_traits_base<short, SHRT_MIN, SHRT_MAX>
{ };

template<>
class integer_traits<unsigned short>
  : public std::numeric_limits<unsigned short>,
    public detail::integer_traits_base<unsigned short, 0, USHRT_MAX>
{ };

template<>
class integer_traits<int>
  : public std::numeric_limits<int>,
    public detail::integer_traits_base<int, INT_MIN, INT_MAX>
{ };

template<>
class integer_traits<unsigned int>
  : public std::numeric_limits<unsigned int>,
    public detail::integer_traits_base<unsigned int, 0, UINT_MAX>
{ };

template<>
class integer_traits<long>
  : public std::numeric_limits<long>,
    public detail::integer_traits_base<long, LONG_MIN, LONG_MAX>
{ };

template<>
class integer_traits<unsigned long>
  : public std::numeric_limits<unsigned long>,
    public detail::integer_traits_base<unsigned long, 0, ULONG_MAX>
{ };

#if !defined(BOOST_NO_INTEGRAL_INT64_T) && !defined(BOOST_NO_INT64_T)
#if defined(ULLONG_MAX) && defined(BOOST_HAS_LONG_LONG)

template<>
class integer_traits< ::boost::long_long_type>
  : public std::numeric_limits< ::boost::long_long_type>,
    public detail::integer_traits_base< ::boost::long_long_type, LLONG_MIN, LLONG_MAX>
{ };

template<>
class integer_traits< ::boost::ulong_long_type>
  : public std::numeric_limits< ::boost::ulong_long_type>,
    public detail::integer_traits_base< ::boost::ulong_long_type, 0, ULLONG_MAX>
{ };

#elif defined(ULONG_LONG_MAX) && defined(BOOST_HAS_LONG_LONG)

template<>
class integer_traits< ::boost::long_long_type>  : public std::numeric_limits< ::boost::long_long_type>,    public detail::integer_traits_base< ::boost::long_long_type, LONG_LONG_MIN, LONG_LONG_MAX>{ };
template<>
class integer_traits< ::boost::ulong_long_type>
  : public std::numeric_limits< ::boost::ulong_long_type>,
    public detail::integer_traits_base< ::boost::ulong_long_type, 0, ULONG_LONG_MAX>
{ };

#elif defined(ULONGLONG_MAX) && defined(BOOST_HAS_LONG_LONG)

template<>
class integer_traits< ::boost::long_long_type>
  : public std::numeric_limits< ::boost::long_long_type>,
    public detail::integer_traits_base< ::boost::long_long_type, LONGLONG_MIN, LONGLONG_MAX>
{ };

template<>
class integer_traits< ::boost::ulong_long_type>
  : public std::numeric_limits< ::boost::ulong_long_type>,
    public detail::integer_traits_base< ::boost::ulong_long_type, 0, ULONGLONG_MAX>
{ };

#elif defined(_LLONG_MAX) && defined(_C2) && defined(BOOST_HAS_LONG_LONG)

template<>
class integer_traits< ::boost::long_long_type>
  : public std::numeric_limits< ::boost::long_long_type>,
    public detail::integer_traits_base< ::boost::long_long_type, -_LLONG_MAX - _C2, _LLONG_MAX>
{ };

template<>
class integer_traits< ::boost::ulong_long_type>
  : public std::numeric_limits< ::boost::ulong_long_type>,
    public detail::integer_traits_base< ::boost::ulong_long_type, 0, _ULLONG_MAX>
{ };

#elif defined(BOOST_HAS_LONG_LONG)
//
// we have long long but no constants, this happens for example with gcc in -ansi mode,
// we'll just have to work out the values for ourselves (assumes 2's compliment representation):
//
template<>
class integer_traits< ::boost::long_long_type>
  : public std::numeric_limits< ::boost::long_long_type>,
    public detail::integer_traits_base< ::boost::long_long_type, (1LL << (sizeof(::boost::long_long_type) * CHAR_BIT - 1)), ~(1LL << (sizeof(::boost::long_long_type) * CHAR_BIT - 1))>
{ };

template<>
class integer_traits< ::boost::ulong_long_type>
  : public std::numeric_limits< ::boost::ulong_long_type>,
    public detail::integer_traits_base< ::boost::ulong_long_type, 0, ~0uLL>
{ };

#elif defined(BOOST_HAS_MS_INT64)

template<>
class integer_traits< __int64>
  : public std::numeric_limits< __int64>,
    public detail::integer_traits_base< __int64, _I64_MIN, _I64_MAX>
{ };

template<>
class integer_traits< unsigned __int64>
  : public std::numeric_limits< unsigned __int64>,
    public detail::integer_traits_base< unsigned __int64, 0, _UI64_MAX>
{ };

#endif
#endif

} // namespace boost

#endif /* BOOST_INTEGER_TRAITS_HPP */




/* integer_traits.hpp
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
*/