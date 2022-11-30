//  (C) Copyright Howard Hinnant
//  (C) Copyright 2011 Vicente J. Botet Escriba
//  Copyright (c) Microsoft Corporation 2014
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//

#ifndef BOOST_CHRONO_IO_TIME_POINT_UNITS_HPP
#define BOOST_CHRONO_IO_TIME_POINT_UNITS_HPP

#include <boost/chrono/config.hpp>
#include <boost/chrono/process_cpu_clocks.hpp>
#include <boost/chrono/system_clocks.hpp>
#include <boost/chrono/thread_clock.hpp>
#include <boost/chrono/io/ios_base_state.hpp>
#include <string>
#include <iosfwd>
#include <ios>
#include <locale>
#include <algorithm>

namespace boost
{
  namespace chrono
  {
    /**
     * customization point to the epoch associated to the clock @c Clock
     * The default calls @c f.do_get_epoch(Clock()). The user can overload this function.
     * @return the string epoch associated to the @c Clock
     */
    template <typename CharT, typename Clock, typename TPUFacet>
    std::basic_string<CharT> get_epoch_custom(Clock, TPUFacet& f)
    {
      return f.do_get_epoch(Clock());
    }

    /**
     * @c time_point_units facet gives useful information about the time_point pattern,
     * the text associated to a time_point's epoch,
     */
    template <typename CharT=char>
    class time_point_units: public std::locale::facet
    {
    public:
      /**
       * Type of character the facet is instantiated on.
       */
      typedef CharT char_type;
      /**
       * Type of character string used by member functions.
       */
      typedef std::basic_string<char_type> string_type;

      /**
       * Unique identifier for this type of facet.
       */
      static std::locale::id id;

      /**
       * Construct a @c time_point_units facet.
       * @param refs
       * @Effects Construct a @c time_point_units facet.
       * If the @c refs argument is @c 0 then destruction of the object is
       * delegated to the @c locale, or locales, containing it. This allows
       * the user to ignore lifetime management issues. On the other had,
       * if @c refs is @c 1 then the object must be explicitly deleted;
       * the @c locale will not do so. In this case, the object can be
       * maintained across the lifetime of multiple locales.
       */
      explicit time_point_units(size_t refs = 0) :
        std::locale::facet(refs)
      {
      }

      /**
       * @return the pattern to be used by default.
       */
      virtual string_type get_pattern() const =0;

      /**
       * @return the epoch associated to the clock @c Clock calling @c do_get_epoch(Clock())
       */
      template <typename Clock>
      string_type get_epoch() const
      {
        return get_epoch_custom<CharT>(Clock(), *this);
      }

    protected:
      /**
       * Destroy the facet.
       */
      virtual ~time_point_units() {}

    public:

      /**
       *
       * @param c a dummy instance of @c system_clock.
       * @return The epoch string associated to the @c system_clock.
       */
      virtual string_type do_get_epoch(system_clock) const=0;

      /**
       *
       * @param c a dummy instance of @c steady_clock.
       * @return The epoch string associated to the @c steady_clock.
       */
      virtual string_type do_get_epoch(steady_clock) const=0;

#if defined(BOOST_CHRONO_HAS_PROCESS_CLOCKS)
      /**
       *
       * @param c a dummy instance of @c process_real_cpu_clock.
       * @return The epoch string associated to the @c process_real_cpu_clock.
       */
      virtual string_type do_get_epoch(process_real_cpu_clock) const=0;
#if ! BOOST_OS_WINDOWS || BOOST_PLAT_WINDOWS_DESKTOP
      /**
       *
       * @param c a dummy instance of @c process_user_cpu_clock.
       * @return The epoch string associated to the @c process_user_cpu_clock.
       */
      virtual string_type do_get_epoch(process_user_cpu_clock) const=0;
      /**
       *
       * @param c a dummy instance of @c process_system_cpu_clock.
       * @return The epoch string associated to the @c process_system_cpu_clock.
       */
      virtual string_type do_get_epoch(process_system_cpu_clock) const=0;
      /**
       *
       * @param c a dummy instance of @c process_cpu_clock.
       * @return The epoch string associated to the @c process_cpu_clock.
       */
      virtual string_type do_get_epoch(process_cpu_clock) const=0;
#endif
#endif
#if defined(BOOST_CHRONO_HAS_THREAD_CLOCK)
      /**
       *
       * @param c a dummy instance of @c thread_clock.
       * @return The epoch string associated to the @c thread_clock.
       */
      virtual string_type do_get_epoch(thread_clock) const=0;
#endif

    };

    template <typename CharT>
    std::locale::id time_point_units<CharT>::id;


    // This class is used to define the strings for the default English
    template <typename CharT=char>
    class time_point_units_default: public time_point_units<CharT>
    {
    public:
      /**
       * Type of character the facet is instantiated on.
       */
      typedef CharT char_type;
      /**
       * Type of character string returned by member functions.
       */
      typedef std::basic_string<char_type> string_type;

      explicit time_point_units_default(size_t refs = 0) :
        time_point_units<CharT> (refs)
      {
      }
      ~time_point_units_default() {}

      /**
       * @return the default pattern "%d%e".
       */
      string_type get_pattern() const
      {
        static const CharT t[] =
        { '%', 'd', '%', 'e' };
        static const string_type pattern(t, t + sizeof (t) / sizeof (t[0]));

        return pattern;
      }

    //protected:
      /**
       * @param c a dummy instance of @c system_clock.
       * @return The epoch string returned by @c clock_string<system_clock,CharT>::since().
       */
      string_type do_get_epoch(system_clock ) const
      {
        return clock_string<system_clock,CharT>::since();
      }
      /**
       * @param c a dummy instance of @c steady_clock.
       * @return The epoch string returned by @c clock_string<steady_clock,CharT>::since().
       */
      string_type do_get_epoch(steady_clock ) const
      {
        return clock_string<steady_clock,CharT>::since();
      }

#if defined(BOOST_CHRONO_HAS_PROCESS_CLOCKS)
      /**
       * @param c a dummy instance of @c process_real_cpu_clock.
       * @return The epoch string returned by @c clock_string<process_real_cpu_clock,CharT>::since().
       */
      string_type do_get_epoch(process_real_cpu_clock ) const
      {
        return clock_string<process_real_cpu_clock,CharT>::since();
      }
#if ! BOOST_OS_WINDOWS || BOOST_PLAT_WINDOWS_DESKTOP
      /**
       * @param c a dummy instance of @c process_user_cpu_clock.
       * @return The epoch string returned by @c clock_string<process_user_cpu_clock,CharT>::since().
       */
      string_type do_get_epoch(process_user_cpu_clock ) const
      {
        return clock_string<process_user_cpu_clock,CharT>::since();
      }
      /**
       * @param c a dummy instance of @c process_system_cpu_clock.
       * @return The epoch string returned by @c clock_string<process_system_cpu_clock,CharT>::since().
       */
      string_type do_get_epoch(process_system_cpu_clock ) const
      {
        return clock_string<process_system_cpu_clock,CharT>::since();
      }
      /**
       * @param c a dummy instance of @c process_cpu_clock.
       * @return The epoch string returned by @c clock_string<process_cpu_clock,CharT>::since().
       */
      string_type do_get_epoch(process_cpu_clock ) const
      {
        return clock_string<process_cpu_clock,CharT>::since();
      }

#endif
#endif
#if defined(BOOST_CHRONO_HAS_THREAD_CLOCK)
      /**
       * @param c a dummy instance of @c thread_clock.
       * @return The epoch string returned by @c clock_string<thread_clock,CharT>::since().
       */
      string_type do_get_epoch(thread_clock ) const
      {
        return clock_string<thread_clock,CharT>::since();
      }
#endif

    };


  } // chrono

} // boost

#endif  // header

/* time_point_units.hpp
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
*/