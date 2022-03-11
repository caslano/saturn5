/* boost integer_traits.hpp header file
 *
 * Copyright Jens Maurer 2000
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * $Id$
 *
 * Idea by Beman Dawes, Ed Brey, Steve Cleary, and Nathan Myers
 */

//  See http://www.boost.org/libs/integer for documentation.


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
#elif defined(__BORLANDC__) || defined(__CYGWIN__) || defined(__MINGW32__) || (defined(__BEOS__) && defined(__GNUC__))
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