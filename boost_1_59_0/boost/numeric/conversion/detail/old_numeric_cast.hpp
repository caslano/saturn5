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
#elif defined(BOOST_BORLANDC)
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
#elif defined(BOOST_BORLANDC)
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
#elif defined(BOOST_BORLANDC)
#pragma option push -w-8012
# endif
        if ((arg < 0 && !result_traits::is_signed)  // loss of negative range
             || (arg_traits::is_signed && arg < (result_traits::min)())  // underflow
             || arg > (result_traits::max)())            // overflow
# if BOOST_MSVC
#  pragma warning(pop)
#elif defined(BOOST_BORLANDC)
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