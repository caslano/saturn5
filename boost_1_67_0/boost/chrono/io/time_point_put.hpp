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