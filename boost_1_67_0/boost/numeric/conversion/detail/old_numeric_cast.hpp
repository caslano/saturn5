//  boost cast.hpp header file  ----------------------------------------------//

//  (C) Copyright Kevlin Henney and Dave Abrahams 1999.
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/conversion for Documentation.

//  Revision History
//  02 Jun 14  Remove VC6 workarounds.
//  16 Jul 11  Bugfixes for VC6.
//  23 JUN 05  Code extracted from /boost/cast.hpp into this new header.
//             Keeps this legacy version of numeric_cast<> for old compilers
//             wich can't compile the new version in /boost/numeric/conversion/cast.hpp
//             (Fernando Cacciola)
//  02 Apr 01  Removed BOOST_NO_LIMITS workarounds and included
//             <boost/limits.hpp> instead (the workaround did not
//             actually compile when BOOST_NO_LIMITS was defined in
//             any case, so we loose nothing). (John Maddock)
//  21 Jan 01  Undid a bug I introduced yesterday. numeric_cast<> never
//             worked with stock GCC; trying to get it to do that broke
//             vc-stlport.
//  20 Jan 01  Moved BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS to config.hpp.
//             Removed unused BOOST_EXPLICIT_TARGET macro. Moved
//             boost::detail::type to boost/type.hpp. Made it compile with
//             stock gcc again (Dave Abrahams)
//  29 Nov 00  Remove nested namespace cast, cleanup spacing before Formal
//             Review (Beman Dawes)
//  19 Oct 00  Fix numeric_cast for floating-point types (Dave Abrahams)
//  15 Jul 00  Suppress numeric_cast warnings for GCC, Borland and MSVC
//             (Dave Abrahams)
//  30 Jun 00  More MSVC6 wordarounds.  See comments below.  (Dave Abrahams)
//  28 Jun 00  Removed implicit_cast<>.  See comment below. (Beman Dawes)
//  27 Jun 00  More MSVC6 workarounds
//  15 Jun 00  Add workarounds for MSVC6
//   2 Feb 00  Remove bad_numeric_cast ";" syntax error (Doncho Angelov)
//  26 Jan 00  Add missing throw() to bad_numeric_cast::what(0 (Adam Levar)
//  29 Dec 99  Change using declarations so usages in other namespaces work
//             correctly (Dave Abrahams)
//  23 Sep 99  Change polymorphic_downcast assert to also detect M.I. errors
//             as suggested Darin Adler and improved by Valentin Bonnard.
//   2 Sep 99  Remove controversial asserts, simplify, rename.
//  30 Aug 99  Move to cast.hpp, replace value_cast with numeric_cast,
//             place in nested namespace.
//   3 Aug 99  Initial version

#ifndef BOOST_OLD_NUMERIC_CAST_HPP
#define BOOST_OLD_NUMERIC_CAST_HPP

# include <boost/config.hpp>
# include <cassert>
# include <typeinfo>
# include <boost/type.hpp>
# include <boost/limits.hpp>
# include <boost/numeric/conversion/converter_policies.hpp>

namespace boost
{
  using numeric::bad_numeric_cast;

//  LEGACY numeric_cast [only for some old broken compilers] --------------------------------------//

//  Contributed by Kevlin Henney

//  numeric_cast  ------------------------------------------------------------//

#if !defined(BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS) || defined(BOOST_SGI_CPP_LIMITS)

    namespace detail
    {
      template <class T>
      struct signed_numeric_limits : std::numeric_limits<T>
      {
             static inline T min BOOST_PREVENT_MACRO_SUBSTITUTION ()
         {
             return (std::numeric_limits<T>::min)() >= 0
                     // unary minus causes integral promotion, thus the static_cast<>
                     ? static_cast<T>(-(std::numeric_limits<T>::max)())
                     : (std::numeric_limits<T>::min)();
         };
      };

      // Move to namespace boost in utility.hpp?
      template <class T, bool specialized>
      struct fixed_numeric_limits_base
          : public if_true< std::numeric_limits<T>::is_signed >
           ::BOOST_NESTED_TEMPLATE then< signed_numeric_limits<T>,
                            std::numeric_limits<T>
                   >::type
      {};

      template <class T>
      struct fixed_numeric_limits
          : fixed_numeric_limits_base<T,(std::numeric_limits<T>::is_specialized)>
      {};

# ifdef BOOST_HAS_LONG_LONG
      // cover implementations which supply no specialization for long
      // long / unsigned long long. Not intended to be full
      // numeric_limits replacements, but good enough for numeric_cast<>
      template <>
      struct fixed_numeric_limits_base< ::boost::long_long_type, false>
      {
          BOOST_STATIC_CONSTANT(bool, is_specialized = true);
          BOOST_STATIC_CONSTANT(bool, is_signed = true);
          static  ::boost::long_long_type max BOOST_PREVENT_MACRO_SUBSTITUTION ()
          {
#  ifdef LONGLONG_MAX
              return LONGLONG_MAX;
#  else
              return 9223372036854775807LL; // hope this is portable
#  endif
          }

          static  ::boost::long_long_type min BOOST_PREVENT_MACRO_SUBSTITUTION ()
          {
#  ifdef LONGLONG_MIN
              return LONGLONG_MIN;
#  else
               return -( 9223372036854775807LL )-1; // hope this is portable
#  endif
          }
      };

      template <>
      struct fixed_numeric_limits_base< ::boost::ulong_long_type, false>
      {
          BOOST_STATIC_CONSTANT(bool, is_specialized = true);
          BOOST_STATIC_CONSTANT(bool, is_signed = false);
          static  ::boost::ulong_long_type max BOOST_PREVENT_MACRO_SUBSTITUTION ()
          {
#  ifdef ULONGLONG_MAX
              return ULONGLONG_MAX;
#  else
              return 0xffffffffffffffffULL; // hope this is portable
#  endif
          }

          static  ::boost::ulong_long_type min BOOST_PREVENT_MACRO_SUBSTITUTION () { return 0; }
      };
# endif
    } // namespace detail

// less_than_type_min -
  //    x_is_signed should be numeric_limits<X>::is_signed
  //    y_is_signed should be numeric_limits<Y>::is_signed
  //    y_min should be numeric_limits<Y>::min()
  //
  //    check(x, y_min) returns true iff x < y_min without invoking comparisons
  //    between signed and unsigned values.
  //
  //    "poor man's partial specialization" is in use here.
    template <bool x_is_signed, bool y_is_signed>
    struct less_than_type_min
    {
        template <class X, class Y>
        static bool check(X x, Y y_min)
            { return x < y_min; }
    };

    template <>
    struct less_than_type_min<false, true>
    {
        template <class X, class Y>
        static bool check(X, Y)
            { return false; }
    };

    template <>
    struct less_than_type_min<true, false>
    {
        template <class X, class Y>
        static bool check(X x, Y)
            { return x < 0; }
    };

  // greater_than_type_max -
  //    same_sign should be:
  //            numeric_limits<X>::is_signed == numeric_limits<Y>::is_signed
  //    y_max should be numeric_limits<Y>::max()
  //
  //    check(x, y_max) returns true iff x > y_max without invoking comparisons
  //    between signed and unsigned values.
  //
  //    "poor man's partial specialization" is in use here.
    template <bool same_sign, bool x_is_signed>
    struct greater_than_type_max;

    template<>
    struct greater_than_type_max<true, true>
    {
        template <class X, class Y>
        static inline bool check(X x, Y y_max)
            { return x > y_max; }
    };

    template <>
    struct greater_than_type_max<false, true>
    {
        // What does the standard say about this? I think it's right, and it
        // will work with every compiler I know of.
        template <class X, class Y>
        static inline bool check(X x, Y)
            { return x >= 0 && static_cast<X>(static_cast<Y>(x)) != x; }
    };

    template<>
    struct greater_than_type_max<true, false>
    {
        template <class X, class Y>
        static inline bool check(X x, Y y_max)
            { return x > y_max; }
    };

    template <>
    struct greater_than_type_max<false, false>
    {
        // What does the standard say about this? I think it's right, and it
        // will work with every compiler I know of.
        template <class X, class Y>
        static inline bool check(X x, Y)
            { return static_cast<X>(static_cast<Y>(x)) != x; }
    };

#else // use #pragma hacks if available

  namespace detail
  {
# if BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4018)
#  pragma warning(disable : 4146)
#elif defined(__BORLANDC__)
#  pragma option push -w-8041
# endif

       // Move to namespace boost in utility.hpp?
       template <class T>
       struct fixed_numeric_limits : public std::numeric_limits<T>
       {
           static inline T min BOOST_PREVENT_MACRO_SUBSTITUTION ()
           {
               return std::numeric_limits<T>::is_signed && (std::numeric_limits<T>::min)() >= 0
                   ? T(-(std::numeric_limits<T>::max)()) : (std::numeric_limits<T>::min)();
           }
       };

# if BOOST_MSVC
#  pragma warning(pop)
#elif defined(__BORLANDC__)
#  pragma option pop
# endif
  } // namespace detail

#endif

    template<typename Target, typename Source>
    inline Target numeric_cast(Source arg)
    {
        // typedefs abbreviating respective trait classes
        typedef detail::fixed_numeric_limits<Source> arg_traits;
        typedef detail::fixed_numeric_limits<Target> result_traits;

#if defined(BOOST_STRICT_CONFIG) \
    || (!defined(__HP_aCC) || __HP_aCC > 33900) \
         && (!defined(BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS) \
             || defined(BOOST_SGI_CPP_LIMITS))
        // typedefs that act as compile time assertions
        // (to be replaced by boost compile time assertions
        // as and when they become available and are stable)
        typedef bool argument_must_be_numeric[arg_traits::is_specialized];
        typedef bool result_must_be_numeric[result_traits::is_specialized];

        const bool arg_is_signed = arg_traits::is_signed;
        const bool result_is_signed = result_traits::is_signed;
        const bool same_sign = arg_is_signed == result_is_signed;

        if (less_than_type_min<arg_is_signed, result_is_signed>::check(arg, (result_traits::min)())
            || greater_than_type_max<same_sign, arg_is_signed>::check(arg, (result_traits::max)())
            )

#else // We need to use #pragma hacks if available

# if BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4018)
#elif defined(__BORLANDC__)
#pragma option push -w-8012
# endif
        if ((arg < 0 && !result_traits::is_signed)  // loss of negative range
             || (arg_traits::is_signed && arg < (result_traits::min)())  // underflow
             || arg > (result_traits::max)())            // overflow
# if BOOST_MSVC
#  pragma warning(pop)
#elif defined(__BORLANDC__)
#pragma option pop
# endif
#endif
        {
            throw bad_numeric_cast();
        }
        return static_cast<Target>(arg);
    } // numeric_cast

} // namespace boost

#endif  // BOOST_OLD_NUMERIC_CAST_HPP

/* old_numeric_cast.hpp
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
*/