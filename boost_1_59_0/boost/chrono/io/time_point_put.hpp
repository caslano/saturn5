//  (C) Copyright Howard Hinnant
//  (C) Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//

/**
 * Duration formatting facet for output.
 */
#ifndef BOOST_CHRONO_IO_TIME_POINT_PUT_HPP
#define BOOST_CHRONO_IO_TIME_POINT_PUT_HPP

#include <boost/chrono/config.hpp>
#include <boost/chrono/io/time_point_units.hpp>
#include <boost/chrono/io/duration_put.hpp>
#include <boost/assert.hpp>
#include <locale>

namespace boost
{
  namespace chrono
  {

    /**
     * @tparam ChatT a character type
     * @tparam OutputIterator a model of @c OutputIterator
     *
     * The @c time_point_put facet provides facilities for formatted output of @c time_point values.
     * The member function of @c time_point_put take a @c time_point and format it into character string representation.
     *
     */
    template <class CharT, class OutputIterator = std::ostreambuf_iterator<CharT> >
    class time_point_put: public std::locale::facet
    {
    public:
      /**
       * Type of character the facet is instantiated on.
       */
      typedef CharT char_type;
      /**
       * Type of character string passed to member functions.
       */
      typedef std::basic_string<CharT> string_type;
      /**
       * Type of iterator used to write in the character buffer.
       */
      typedef OutputIterator iter_type;

      /**
       * Construct a time_point_put facet.
       * @param refs
       * @Effects Construct a time_point_put facet.
       * If the @c refs argument is @c 0 then destruction of the object is
       * delegated to the @c locale, or locales, containing it. This allows
       * the user to ignore lifetime management issues. On the other had,
       * if @c refs is @c 1 then the object must be explicitly deleted;
       * the @c locale will not do so. In this case, the object can be
       * maintained across the lifetime of multiple locales.
       */
      explicit time_point_put(size_t refs = 0) :
        std::locale::facet(refs)
      {
      }

      /**
       * @param i an output stream iterator
       * @param ios a reference to a ios_base
       * @param fill the character used as filler
       * @param tp the @c time_point
       * @param pattern begin of the formatting pattern
       * @param pat_end end of the formatting pattern
       *
       * @Effects Steps through the sequence from @c pattern to @c pat_end,
       * identifying characters that are part of a pattern sequence. Each character
       * that is not part of a pattern sequence is written to @c s immediately, and
       * each pattern sequence, as it is identified, results in a call to
       * @c put_duration or @c put_epoch;
       * thus, pattern elements and other characters are interleaved in the output
       * in the order in which they appear in the pattern. Pattern sequences are
       * identified by converting each character @c c to a @c char value as if by
       * @c ct.narrow(c,0), where @c ct is a reference to @c ctype<charT> obtained from
       * @c ios.getloc(). The first character of each sequence is equal to @c '%',
       * followed by a pattern specifier character @c spec, which can be @c 'd' for
       * the duration value or @c 'e' for the epoch.
       * For each valid pattern sequence identified, calls
       * <c>put_duration(s, ios, fill, tp.time_since_epoch())</c> or <c>put_epoch(s, ios)</c>.
       *
       * @Returns An iterator pointing immediately after the last character produced.
       */

      template <class Clock, class Duration>
      iter_type put(iter_type i, std::ios_base& ios, char_type fill, time_point<Clock, Duration> const& tp, const CharT* pattern,
          const CharT* pat_end) const
      {
        if (std::has_facet<time_point_units<CharT> >(ios.getloc()))
        {
          time_point_units<CharT> const &facet =
              std::use_facet<time_point_units<CharT> >(ios.getloc());
          return put(facet, i, ios, fill, tp, pattern, pat_end);
        }
        else
        {
          time_point_units_default<CharT> facet;
          return put(facet, i, ios, fill, tp, pattern, pat_end);
        }
      }

      template <class Clock, class Duration>
      iter_type put(time_point_units<CharT> const& units_facet, iter_type s, std::ios_base& ios, char_type fill,
          time_point<Clock, Duration> const& tp, const CharT* pattern, const CharT* pat_end) const
      {

        const std::ctype<char_type>& ct = std::use_facet<std::ctype<char_type> >(ios.getloc());
        for (; pattern != pat_end; ++pattern)
        {
          if (ct.narrow(*pattern, 0) == '%')
          {
            if (++pattern == pat_end)
            {
              *s++ = pattern[-1];
              break;
            }
            char fmt = ct.narrow(*pattern, 0);
            switch (fmt)
            {
            case 'd':
            {
              s = put_duration(s, ios, fill, tp.time_since_epoch());
              break;
            }
            case 'e':
            {
              s = put_epoch<Clock> (units_facet, s, ios);
              break;
            }
            default:
              BOOST_ASSERT(false && "Boost::Chrono internal error.");
              break;
            }
          }
          else
            *s++ = *pattern;
        }
        return s;
      }

      /**
       * @param i an output stream iterator
       * @param ios a reference to a ios_base
       * @param fill the character used as filler
       * @param tp the @c time_point
       * @param pattern begin of the formatting pattern
       * @param pat_end end of the formatting pattern
       *
       * @Effects Stores the time_point pattern from the @c time_point_unit facet in let say @c str. Last as if
       * @code
       *   return put(s, ios, dill, tp, str.data(), str.data() + str.size());
       * @endcode
       * @Returns An iterator pointing immediately after the last character produced.
       */
      template <class Clock, class Duration>
      iter_type put(iter_type i, std::ios_base& ios, char_type fill, time_point<Clock, Duration> const& tp) const
      {
        if (std::has_facet<time_point_units<CharT> >(ios.getloc()))
        {
          time_point_units<CharT> const &facet =
              std::use_facet<time_point_units<CharT> >(ios.getloc());
          std::basic_string<CharT> str = facet.get_pattern();
          return put(facet, i, ios, fill, tp, str.data(), str.data() + str.size());
        }
        else
        {
          time_point_units_default<CharT> facet;
          std::basic_string<CharT> str = facet.get_pattern();
          return put(facet, i, ios, fill, tp, str.data(), str.data() + str.size());
        }
      }

      /**
       * @param i an output stream iterator
       * @param ios a reference to a ios_base
       * @param fill the character used as filler
       * @param d the @c duration
       * @Effects As if <c>facet.put(s, ios, fill, d)</c> where facet is the @c duration_put<CharT> facet associated
       * to the @c ios or a new instance of @c duration_put<CharT>.
       * @Returns An iterator pointing immediately after the last character produced.
       */
      template <typename Rep, typename Period>
      iter_type put_duration(iter_type i, std::ios_base& ios, char_type fill, duration<Rep, Period> const& d) const
      {
        if (std::has_facet<duration_put<CharT> >(ios.getloc()))
        {
          duration_put<CharT> const &facet = std::use_facet<duration_put<CharT> >(ios.getloc());
          return facet.put(i, ios, fill, d);
        }
        else
        {
          duration_put<CharT> facet;
          return facet.put(i, ios, fill, d);
        }
      }

      /**
       *
       * @param i an output stream iterator
       * @param ios a reference to a ios_base
       * @Effects As if
       * @code
       * string_type str = facet.template get_epoch<Clock>();
       * s=std::copy(str.begin(), str.end(), s);
       * @endcode
       * where facet is the @c time_point_units<CharT> facet associated
       * to the @c ios or a new instance of @c time_point_units_default<CharT>.
       * @Returns s, iterator pointing immediately after the last character produced.
       */

      template <typename Clock>
      iter_type put_epoch(iter_type i, std::ios_base& os) const
      {
        if (std::has_facet<time_point_units<CharT> >(os.getloc()))
        {
          time_point_units<CharT> const &facet = std::use_facet<time_point_units<CharT> >(os.getloc());
          return put_epoch<Clock> (facet, i, os);
        }
        else
        {
          time_point_units_default<CharT> facet;
          return put_epoch<Clock> (facet, i, os);
        }
      }

      template <typename Clock>
      iter_type put_epoch(time_point_units<CharT> const& facet, iter_type s, std::ios_base&) const
      {
        string_type str = facet.template get_epoch<Clock>();
        s= std::copy(str.begin(), str.end(), s);
        return s;
      }

      /**
       * Unique identifier for this type of facet.
       */
      static std::locale::id id;

      /**
       * @Effects Destroy the facet
       */
      ~time_point_put()
      {
      }

    };

    template <class CharT, class OutputIterator>
    std::locale::id time_point_put<CharT, OutputIterator>::id;

  } // chrono
} // boost

#endif  // header

/* time_point_put.hpp
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
*/