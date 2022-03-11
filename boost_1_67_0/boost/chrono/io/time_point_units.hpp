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