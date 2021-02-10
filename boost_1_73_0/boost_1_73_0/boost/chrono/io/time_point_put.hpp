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
bQKWm6HFxCprlWGFZBbsa7UX4L5DDzWVC2dhHXlFuiob6vCEodoIajitBR++M8RGSxm19E78mw1G19E/K3X2Le8sRf9rnp2Qxj/1zDP/Fx2rqfwf+NUfDtmV0aADJQm3mcyVjlznwQETQGeYe8rggj2VcDUezb8qImLtS0LQoqeD+e10xD/1h7cDRhIHi/Hv/OwvWZpzFLfQsWDJ64gmaqlU0KGvFfvQIgQCry/oXKQL5qeHIMIa4GRNGduVBu8mxVTh+0bu4jR4AEKU3+N8JmWN8zgJXciyNKWN8N4ADFuxkg1G8wo1gAnX+QzGgX7bcteTQ5+SM/OgrTmBwBdJAQOmQbSovewMZhEvCb46k5oiRqNZQJEwLZ3/XdfYk3KISaHQvz4kwwEGeZROufdTQ82BtkKfOBARDVGh89bp6YZ6Tv1uaMfVAMNyvJdAnaXm58mUBmAflXp1KeNicPnmdjhPJsPBH4Pr0FDESbvx9LupCqfQCp9ptPK2U0w/zueTy9chwUY3HHUIlXmK6ftSB4ujA45RM/YgRG+vIDowWpfV8+3G3/Ek0fSWL6scsuPwh+sdWK/O70mv6PEEtyVhw/UisNVShpgBtBpkHdZKEWNjTfqI0q3lxSmhcScazERBCN9zmjLAEVAJezNq
*/