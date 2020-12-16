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
/WNdwdvBXmAFOJn9ZOeA73Mu6j3gGvaLbeZa+/dz7f032N91AvwL5xw+CYaDz4BRnKvXF3yO/U1/BXPA58H54MvgpeAO9jO9wjmBr4K7wNfAt9gP9h37wVo72A8G7uHcvrfN9IPvgMXgfnAZ+C54JXgAXAm+z7l994KPgfeB74CbwIPmcebnLP38wbOP9a0+OIn1pgvnkHZnvenFftsk7iHQm3Oy+7A/sS/X3h8IHjGU9IEd+RbrkZ8Mq7HPzOy7ObI97N/WZ9bvhbD/2X6z0+kzq66/LB15FqzPrDXKdCjMHJhymHUn6/rH6n51v7pf3a/uV/er+9X96n51v7pf3a/uV/PvZxv/l+H/0xv/xxre0s+eBOGUUy0qyUjLK8wrTcsqKswWbcAPMb65/1dxjLiHwzM+3Bw8K8HscPPTBgQfU6PfXtK/vyVG5lK409xFxbb1ZqdwbIvjtHeKvYEj0PqyzcAH5fh3RkOO95vHS3xj+pY5xrlFJaW+vXrHnmOGm2j4jktCtFZhMo8nYh7WTiXrxoou3OVwXuHABKywCPwJaRh0Dtb1Er4j7didWezhVedkMW/WyvFI2uGfdnOOVkemoZJpiHAsey881JwF5ggPA8Lqm2lpXTUtXCsgS+IaW+Xc0Ry7yZHjk9QAVU/O5x1T/slv3PhV2N+COUy70dQ+ry5XVa+PSKU+wlwT/aZUzxyQ7MIsGctb5jcWGAu3FbCjnsCN9cSnHaAmwixrjtlNsY+vDGe9Tad2oCcOmg4dwbNRb1Om6nqLSa2su77hMd/cMtYbzi9iuMGWMaq5eYVZaQVFWdkcC/P6aa7nh80WexOjJ/dnZn3U47AXyfEoyxq5JXpMuEyOnVBN8Defe0+/4qvnEofbtIm/761zR/U9MBjlGQm+iwjfgXkbZjvMSzDPwThRjs+CIaAB89cYlmstxnHNsuw+jWVZXMxxWe+cL0/exdrmWlvyi+O19KvnX79iK1uUt/bjtulWYrgWhanXjQMngFNRtpXTbGVrJiItzx107RD676D3kf9Q7D2NBHMncZj61IW0lvqAmHztFcO21PvIvyv2rkYi0nkDTLjhCro29p5zTb8RAcs0FTwocfWRetHOc9/KMbO/O1nCPsLxeZYryxP3ppThszBvwIyK0v/DHX5rMUZKDYd1bqfWgCAf5J5UdEutWmaSRqQZbvm2MepN1GaMZJkNAM9NQPlOt5aZ3O3Bygt+7eW1XuwJRj/OFf4aJhph20h5ISrEhwhYZgxvKbNrxd7MGIh0PgZzQgUvswXnmX4bBSyzFHCNxNXK6IlyCaNuIljZvHma5RHL8sB1wk1fp/b7il8bmSFpx/MjgWvasEwmcZ+BOJhImhnwEzXDWibmbTT3ksKMgmwctpSNx4VlwzBxtdaAea6HcSCNbSQ85qb4pbEFu+VdjCQUpgPaqiRfGktQb0oz3WmFWdn5GZfIM0e/h/C56vXvWa+9vvVdhRoatuE2f0hijesZNeS6QXyGyfVF2fUptrZrEufMz2J+n0vNXcoMm1aDC1gEfaei/6b6uNLrJoySurFYjida5o5erOtqvhzrrgKtzb5MjjXBsdAa1yivRi9GN6bJ5u9iKW+kz6a9uYr24nh7foVE+rSpjWA+hrkIYbba8wtvsDlFKnh+0b+5Xjv3MRH726oL/m6EeY1rDQxPMMN69B98T2LYSaqzihE/c8SP54zRfNeiH7zlRvq3ITpvI2eafmaaCkC40Y/oyKjPYtkdl7ju1brUOVGiTQVrr3WprmxwjXDjNbIdnyNuck1+ehidPimnenINSDXLLXpm4HJ7geV2D+t5Bcxg3LcHZvqXW16ppdzwQ8037cyzfrM=
*/