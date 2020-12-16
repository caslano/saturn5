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
2UTHZUDHdjXj9xo6jkfn2gZtEeys98R+kM1Kt3A/cHE/WGlUWKrvCZGlRl1psq4hRl0d1ed+12w/ZTUnYlM9Fr7OFfP/khhkWtOFfpjync271+nY7QQPjy6DKDCs8/ej68UN6nLRH+mr4xU+D5yUSXE+hpaIoe/VtK54xJoJK05NaysxukWpxfAXDpyc4b8WBWGtXIIUYhAhksm4RI95+DhJr/jESeRsmYCloOxytofF0HvfGDSz9GoMmXE7X8DBi9Uu0LXYncIoSqSDVKzh+yxO0I1SfPe13pyMV9Sejwis/9raE/2R6+01yKlp9tk9wray+jiO/UeiHgHlPK5Vxbwrpqq49aLN4vgXYvjzn4Q9NDD9WS/wpP4wS99wAzmUX0YYu58upOin6NdNZz6s8eIN7ddwwQRCSQG30FC+QHQ1BV3N4s/DP9X+itxu1ZsXC+mKSazjEtQxRavjtOZ1rIFwUTO8ef3DRJc/l+jyF70kury/SuN9NmsOCIN8ouFCQslG1DMI9SRq9WTH1nOBWhxfj/lhDT9nL8QJLyw3+3+BoqiwOIidHHg3vyrGf2QR2F6x7+P4Hsv/e+6I/D9BJs0mxTKLzBxQR23U695k10aLnYkCdHBgNywfAfl6QAECCgR9lY8vui2kIHN/8O4ilh9pQXsM/38esf2qu95gxXilB8ALQbhV/nCRenl/fTa2fyB9Vsi85LsDFJzsnd8+cZFPsXoZ5EVQYK83NEr0KtGHHmEs0P9k9To0o1W+B431om0tZ+pt2KvvK7Ux+8qbcl/JxL7ycvy+QgR0hH2FmC1mWzmbWCXWfMbY0wR2EZqdlb9tsa0YO4pHO15k8poG2FDHhO9yZ0HVOGkYO8uCo53bjMobJGr7oIdeeTvV9dsTfW476v69+ukj7N9VMeO8RI5zhglbeWv374T4/fsmra+Vsq+7MtnXl9HXtuq4B1q/f2c0DXgR6197hK38dmMrf8GodomsdoZWLed3x/0/9Vaujfcoa1Xzd3vc+xHovbOfak7vOe/Q6b22PH3HfEKjMqri6gMei43PikvfNY6+y+y5oqrF/vekqN+neHlaISqCHcaireqVL4mbNY3fC5Qo7ew9Kl6Pwa+5VpYn+mLB0f8Y8DjoyRbwSN56S7gwN0EiwXSeBFO7yT9LQKYOlnHQYdEh81YBmXZGfGIyyI7hzeHNHrfA3UeAt6ABb6czbGsTzXKzhDpzN0Ldi+pN97UA9BMPdnK8v/uzGER1x60E8vYvDoYW/IZ54rnd4W4w0Ju0GEH8qGUIxvvuQ91MplZwyDT+vyzfF3ZiB98EX8FiZs9FB1ukzxfzL9Pz3JkgGO9hVKeeigsooWnsbj8f75jo3uFREzmIUMrGkJVTVxoD2NgVNNLP723StPcp7V3IIE6Q2r1v+7lXo8RluOumZQocKVGsa7VSebz6+Br8QwxO+kOmi6mZqF908HfwTdHyPOeJO7/lH+M8x/eCuPfsuPfMuPeMY54XY+U/ntD2yw/Q8GRlP5q+7Gd05ZyrDsZFB2mz5BBIjHHW1l8ZAZ94NBsZBn6Je8+Ney+Ie8+Oe8+Me8+Ie7dr77HnX9kz9dmw5vbO/X23OLd5x5zPzx+X+Sfr+ZOM/KH2fBZltOo8lingX5YHDAU8BZUb2uQJX88TwlxQR8r43MCpxvn7HV7wrYRTA+CS00QC/1eGlMV76jX36dd8PUpirvmm/Ejf7kdu7+d/bNneDycdo73pR23vvJf19t586wlor8b//OOPk1+86nC0FfpTuG/U7a7/7bEmIcSpO6KrIYAITZ75B4LiVnARrZvDqDLOmaMPRnkt2PUli0m5f/5nL1rgh29T9BNwKms=
*/