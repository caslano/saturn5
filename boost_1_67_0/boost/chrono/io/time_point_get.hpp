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