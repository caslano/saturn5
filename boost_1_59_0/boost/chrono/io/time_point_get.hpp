//  (C) Copyright Howard Hinnant
//  (C) Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//

#ifndef BOOST_CHRONO_IO_TIME_POINT_GET_HPP
#define BOOST_CHRONO_IO_TIME_POINT_GET_HPP

#include <boost/chrono/config.hpp>
#include <boost/chrono/detail/scan_keyword.hpp>
#include <boost/chrono/io/time_point_units.hpp>
#include <boost/chrono/io/duration_get.hpp>
#include <boost/assert.hpp>
#include <locale>
#include <string>

/**
 * Duration formatting facet for input.
 */
namespace boost
{
  namespace chrono
  {

    template <class CharT, class InputIterator = std::istreambuf_iterator<CharT> >
    class time_point_get: public std::locale::facet
    {
    public:
      /**
       * Type of character the facet is instantiated on.
       */
      typedef CharT char_type;
      /**
       * Type of iterator used to scan the character buffer.
       */
      typedef InputIterator iter_type;

      /**
       * Construct a @c time_point_get facet.
       * @param refs
       * @Effects Construct a @c time_point_get facet.
       * If the @c refs argument is @c 0 then destruction of the object is
       * delegated to the @c locale, or locales, containing it. This allows
       * the user to ignore lifetime management issues. On the other had,
       * if @c refs is @c 1 then the object must be explicitly deleted;
       * the @c locale will not do so. In this case, the object can be
       * maintained across the lifetime of multiple locales.
       */

      explicit time_point_get(size_t refs = 0) :
        std::locale::facet(refs)
      {
      }

      /**
       * @param s start input stream iterator
       * @param end end input stream iterator
       * @param ios a reference to a ios_base
       * @param err the ios_base state
       * @param d the duration
       * @param pattern begin of the formatting pattern
       * @param pat_end end of the formatting pattern
       *
       * Requires: [pattern,pat_end) shall be a valid range.
       *
       * Effects: The function starts by evaluating err = std::ios_base::goodbit.
       * It then enters a loop, reading zero or more characters from s at
       * each iteration. Unless otherwise specified below, the loop
       * terminates when the first of the following conditions holds:
       * - The expression pattern == pat_end evaluates to true.
       * - The expression err == std::ios_base::goodbit evaluates to false.
       * - The expression s == end evaluates to true, in which case the
       * function evaluates err = std::ios_base::eofbit | std::ios_base::failbit.
       * - The next element of pattern is equal to '%', followed by a conversion
       * specifier character, the functions @c get_duration or @c get_epoch are called depending on
       * whether the format is @c 'd' or @c 'e'.
       * If the number of elements in the range [pattern,pat_end) is not
       * sufficient to unambiguously determine whether the conversion
       * specification is complete and valid, the function evaluates
       * err = std::ios_base::failbit. Otherwise, the function evaluates
       * s = do_get(s, end, ios, err, d). If err == std::ios_base::goodbit holds after
       * the evaluation of the expression, the function increments pattern to
       * point just past the end of the conversion specification and continues
       * looping.
       * - The expression isspace(*pattern, ios.getloc()) evaluates to true, in
       * which case the function first increments pattern until
       * pattern == pat_end || !isspace(*pattern, ios.getloc()) evaluates to true,
       * then advances s until s == end || !isspace(*s, ios.getloc()) is true,
       * and finally resumes looping.
       * - The next character read from s matches the element pointed to by
       * pattern in a case-insensitive comparison, in which case the function
       * evaluates ++pattern, ++s and continues looping. Otherwise, the function
       * evaluates err = std::ios_base::failbit.
       *
       * Returns: s
       */

      template <class Clock, class Duration>
      iter_type get(iter_type i, iter_type e, std::ios_base& is, std::ios_base::iostate& err,
          time_point<Clock, Duration> &tp, const char_type *pattern, const char_type *pat_end) const
      {
        if (std::has_facet<time_point_units<CharT> >(is.getloc()))
        {
          time_point_units<CharT> const &facet = std::use_facet<time_point_units<CharT> >(is.getloc());
          return get(facet, i, e, is, err, tp, pattern, pat_end);
        }
        else
        {
          time_point_units_default<CharT> facet;
          return get(facet, i, e, is, err, tp, pattern, pat_end);
        }
      }

      template <class Clock, class Duration>
      iter_type get(time_point_units<CharT> const &facet, iter_type s, iter_type end, std::ios_base& ios,
          std::ios_base::iostate& err, time_point<Clock, Duration> &tp, const char_type *pattern,
          const char_type *pat_end) const
      {

        Duration d;
        bool duration_found = false, epoch_found = false;

        const std::ctype<char_type>& ct = std::use_facet<std::ctype<char_type> >(ios.getloc());
        err = std::ios_base::goodbit;
        while (pattern != pat_end && err == std::ios_base::goodbit)
        {
          if (s == end)
          {
            err |= std::ios_base::eofbit;
            break;
          }
          if (ct.narrow(*pattern, 0) == '%')
          {
            if (++pattern == pat_end)
            {
              err |= std::ios_base::failbit;
              return s;
            }
            char cmd = ct.narrow(*pattern, 0);
            switch (cmd)
            {
            case 'd':
            {
              if (duration_found)
              {
                err |= std::ios_base::failbit;
                return s;
              }
              duration_found = true;
              s = get_duration(s, end, ios, err, d);
              if (err & (std::ios_base::badbit | std::ios_base::failbit))
              {
                return s;
              }
              break;
            }
            case 'e':
            {
              if (epoch_found)
              {
                err |= std::ios_base::failbit;
                return s;
              }
              epoch_found = true;
              s = get_epoch<Clock> (facet, s, end, ios, err);
              if (err & (std::ios_base::badbit | std::ios_base::failbit))
              {
                return s;
              }
              break;
            }
            default:
              BOOST_ASSERT(false && "Boost::Chrono internal error.");
              break;
            }

            ++pattern;
          }
          else if (ct.is(std::ctype_base::space, *pattern))
          {
            for (++pattern; pattern != pat_end && ct.is(std::ctype_base::space, *pattern); ++pattern)
              ;
            for (; s != end && ct.is(std::ctype_base::space, *s); ++s)
              ;
          }
          else if (ct.toupper(*s) == ct.toupper(*pattern))
          {
            ++s;
            ++pattern;
          }
          else
          {
            err |= std::ios_base::failbit;
          }
        }

        // Success!  Store it.
        tp = time_point<Clock, Duration> (d);
        return s;
      }

      /**
       *
       * @param s an input stream iterator
       * @param ios a reference to a ios_base
       * @param d the duration
       * Stores the duration pattern from the @c duration_unit facet in let say @c str. Last as if
       * @code
       *   return get(s, end, ios, err, ios, d, str.data(), str.data() + str.size());
       * @codeend
       * @Returns An iterator pointing just beyond the last character that can be determined to be part of a valid name
       */
      template <class Clock, class Duration>
      iter_type get(iter_type i, iter_type e, std::ios_base& is, std::ios_base::iostate& err,
          time_point<Clock, Duration> &tp) const
      {
        if (std::has_facet<time_point_units<CharT> >(is.getloc()))
        {
          time_point_units<CharT> const &facet = std::use_facet<time_point_units<CharT> >(is.getloc());
          std::basic_string<CharT> str = facet.get_pattern();
          return get(facet, i, e, is, err, tp, str.data(), str.data() + str.size());
        }
        else
        {
          time_point_units_default<CharT> facet;
          std::basic_string<CharT> str = facet.get_pattern();
          return get(facet, i, e, is, err, tp, str.data(), str.data() + str.size());
        }
      }

      /**
       * As if
       * @code
       * return facet.get(s, end, ios, err, d);
       * @endcode
       * where @c facet is either the @c duration_get facet associated to the @c ios or an instance of the default @c duration_get facet.
       *
       * @Returns An iterator pointing just beyond the last character that can be determined to be part of a valid duration.
       */
      template <typename Rep, typename Period>
      iter_type get_duration(iter_type i, iter_type e, std::ios_base& is, std::ios_base::iostate& err,
          duration<Rep, Period>& d) const
      {
        if (std::has_facet<duration_get<CharT> >(is.getloc()))
        {
          duration_get<CharT> const &facet = std::use_facet<duration_get<CharT> >(is.getloc());
          return get_duration(facet, i, e, is, err, d);
        }
        else
        {
          duration_get<CharT> facet;
          return get_duration(facet, i, e, is, err, d);
        }
      }

      template <typename Rep, typename Period>
      iter_type get_duration(duration_get<CharT> const& facet, iter_type s, iter_type end, std::ios_base& ios,
          std::ios_base::iostate& err, duration<Rep, Period>& d) const
      {
        return facet.get(s, end, ios, err, d);
      }

      /**
       *
       * @Effects Let @c facet be the @c time_point_units facet associated to @c is or a new instance of the default @c time_point_units_default facet.
       * Let @c epoch be the epoch string associated to the Clock using this facet.
       * Scans @c i to match @c epoch or @c e is reached.
       *
       * If not match before the @c e is reached @c std::ios_base::failbit is set in @c err.
       * If @c e is reached @c std::ios_base::failbit is set in @c err.
       *
       * @Returns An iterator pointing just beyond the last character that can be determined to be part of a valid epoch.
       */
      template <class Clock>
      iter_type get_epoch(iter_type i, iter_type e, std::ios_base& is, std::ios_base::iostate& err) const
      {
        if (std::has_facet<time_point_units<CharT> >(is.getloc()))
        {
          time_point_units<CharT> const &facet = std::use_facet<time_point_units<CharT> >(is.getloc());
          return get_epoch<Clock>(facet, i, e, is, err);
        }
        else
        {
          time_point_units_default<CharT> facet;
          return get_epoch<Clock>(facet, i, e, is, err);
        }
      }

      template <class Clock>
      iter_type get_epoch(time_point_units<CharT> const &facet, iter_type i, iter_type e, std::ios_base&,
          std::ios_base::iostate& err) const
      {
        const std::basic_string<CharT> epoch = facet.template get_epoch<Clock> ();
        std::ptrdiff_t k = chrono_detail::scan_keyword(i, e, &epoch, &epoch + 1,
        //~ std::use_facet<std::ctype<CharT> >(ios.getloc()),
            err) - &epoch;
        if (k == 1)
        {
          err |= std::ios_base::failbit;
          return i;
        }
        return i;
      }

      /**
       * Unique identifier for this type of facet.
       */
      static std::locale::id id;

      /**
       * @Effects Destroy the facet
       */
      ~time_point_get()
      {
      }
    };

    /**
     * Unique identifier for this type of facet.
     */
    template <class CharT, class InputIterator>
    std::locale::id time_point_get<CharT, InputIterator>::id;

  } // chrono
}
// boost

#endif  // header

/* time_point_get.hpp
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
*/