//  (C) Copyright Howard Hinnant
//  (C) Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//

/**
 * Duration formatting facet for output.
 */
#ifndef BOOST_CHRONO_IO_DURATION_PUT_HPP
#define BOOST_CHRONO_IO_DURATION_PUT_HPP

#include <boost/chrono/config.hpp>
#include <boost/chrono/io/duration_units.hpp>
#include <boost/chrono/process_cpu_clocks.hpp>
#include <boost/assert.hpp>
#include <locale>

namespace boost
{
  namespace chrono
  {

    namespace detail
    {
      template <class T>
      struct propagate {
        typedef T type;
      };
      template <>
      struct propagate<boost::int_least32_t> {
        typedef boost::int_least64_t type;
      };
    }
    /**
     * @tparam ChatT a character type
     * @tparam OutputIterator a model of @c OutputIterator
     *
     * The @c duration_put facet provides facilities for formatted output of duration values.
     * The member function of @c duration_put take a duration and format it into character string representation.
     *
     */
    template <class CharT, class OutputIterator = std::ostreambuf_iterator<CharT> >
    class duration_put: public std::locale::facet
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
       * Construct a duration_put facet.
       * @param refs
       * @Effects Construct a duration_put facet.
       * If the @c refs argument is @c 0 then destruction of the object is
       * delegated to the @c locale, or locales, containing it. This allows
       * the user to ignore lifetime management issues. On the other had,
       * if @c refs is @c 1 then the object must be explicitly deleted;
       * the @c locale will not do so. In this case, the object can be
       * maintained across the lifetime of multiple locales.
       */
      explicit duration_put(size_t refs = 0) :
        std::locale::facet(refs)
      {
      }

      /**
       *
       * @param s an output stream iterator
       * @param ios a reference to a ios_base
       * @param fill the character used as filler
       * @param d the duration
       * @param pattern begin of the formatting pattern
       * @param pat_end end of the formatting pattern
       *
       * @Effects Steps through the sequence from @c pattern to @c pat_end,
       * identifying characters that are part of a pattern sequence. Each character
       * that is not part of a pattern sequence is written to @c s immediately, and
       * each pattern sequence, as it is identified, results in a call to
       * @c put_value or @c put_unit;
       * thus, pattern elements and other characters are interleaved in the output
       * in the order in which they appear in the pattern. Pattern sequences are
       * identified by converting each character @c c to a @c char value as if by
       * @c ct.narrow(c,0), where @c ct is a reference to @c ctype<charT> obtained from
       * @c ios.getloc(). The first character of each sequence is equal to @c '%',
       * followed by a pattern specifier character @c spec, which can be @c 'v' for
       * the duration value or @c 'u' for the duration unit. .
       * For each valid pattern sequence identified, calls
       * <c>put_value(s, ios, fill, d)</c> or <c>put_unit(s, ios, fill, d)</c>.
       *
       * @Returns An iterator pointing immediately after the last character produced.
       */
      template <typename Rep, typename Period>
      iter_type put(iter_type s, std::ios_base& ios, char_type fill, duration<Rep, Period> const& d, const CharT* pattern,
          const CharT* pat_end, const char_type* val = 0) const
      {
        if (std::has_facet<duration_units<CharT> >(ios.getloc()))
        {
          duration_units<CharT> const&facet = std::use_facet<duration_units<CharT> >(
              ios.getloc());
          return put(facet, s, ios, fill, d, pattern, pat_end, val);
        }
        else
        {
          duration_units_default<CharT> facet;
          return put(facet, s, ios, fill, d, pattern, pat_end, val);
        }
      }

      template <typename Rep, typename Period>
      iter_type put(duration_units<CharT> const& units_facet, iter_type s, std::ios_base& ios, char_type fill,
          duration<Rep, Period> const& d, const CharT* pattern, const CharT* pat_end, const char_type* val = 0) const
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
            case 'v':
            {
              s = put_value(s, ios, fill, d, val);
              break;
            }
            case 'u':
            {
              s = put_unit(units_facet, s, ios, fill, d);
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
       *
       * @param s an output stream iterator
       * @param ios a reference to a ios_base
       * @param fill the character used as filler
       * @param d the duration
       * @Effects imbue in @c ios the @c duration_units_default facet if not already present.
       * Retrieves Stores the duration pattern from the @c duration_unit facet in let say @c str. Last as if
       * @code
       *   return put(s, ios, d, str.data(), str.data() + str.size());
       * @endcode
       * @Returns An iterator pointing immediately after the last character produced.
       */
      template <typename Rep, typename Period>
      iter_type put(iter_type s, std::ios_base& ios, char_type fill, duration<Rep, Period> const& d, const char_type* val = 0) const
      {
        if (std::has_facet<duration_units<CharT> >(ios.getloc()))
        {
          duration_units<CharT> const&facet = std::use_facet<duration_units<CharT> >(
              ios.getloc());
          std::basic_string<CharT> str = facet.get_pattern();
          return put(facet, s, ios, fill, d, str.data(), str.data() + str.size(), val);
        }
        else
        {
          duration_units_default<CharT> facet;
          std::basic_string<CharT> str = facet.get_pattern();

          return put(facet, s, ios, fill, d, str.data(), str.data() + str.size(), val);
        }
      }

      /**
       *
       * @param s an output stream iterator
       * @param ios a reference to a ios_base
       * @param fill the character used as filler
       * @param d the duration
       * @Effects As if s=std::use_facet<std::num_put<CharT, iter_type> >(ios.getloc()).put(s, ios, fill, static_cast<long int> (d.count())).
       * @Returns s, iterator pointing immediately after the last character produced.
       */
      template <typename Rep, typename Period>
      iter_type put_value(iter_type s, std::ios_base& ios, char_type fill, duration<Rep, Period> const& d, const char_type* val = 0) const
      {
        if (val)
        {
          while (*val) {
            *s = *val;
            s++; val++;
          }
          return s;
        }
        return std::use_facet<std::num_put<CharT, iter_type> >(ios.getloc()).put(s, ios, fill,
            static_cast<typename detail::propagate<Rep>::type> (d.count()));
      }

      template <typename Rep, typename Period>
      iter_type put_value(iter_type s, std::ios_base& ios, char_type fill, duration<process_times<Rep>, Period> const& d, const char_type* = 0) const
      {
        *s++ = CharT('{');
        s = put_value(s, ios, fill, process_real_cpu_clock::duration(d.count().real));
        *s++ = CharT(';');
        s = put_value(s, ios, fill, process_user_cpu_clock::duration(d.count().user));
        *s++ = CharT(';');
        s = put_value(s, ios, fill, process_system_cpu_clock::duration(d.count().system));
        *s++ = CharT('}');
        return s;
      }

      /**
       *
       * @param s an output stream iterator
       * @param ios a reference to a ios_base
       * @param fill the character used as filler
       * @param d the duration
       * @Effects Let facet be the duration_units<CharT> facet associated to ios. If the associated unit is named,
       * as if
       * @code
          string_type str = facet.get_unit(get_duration_style(ios), d);
          s=std::copy(str.begin(), str.end(), s);
       * @endcode
       * Otherwise, format the unit as "[Period::num/Period::den]" followed by the unit associated to [N/D] obtained using facet.get_n_d_unit(get_duration_style(ios), d)
       * @Returns s, iterator pointing immediately after the last character produced.
       */
      template <typename Rep, typename Period>
      iter_type put_unit(iter_type s, std::ios_base& ios, char_type fill, duration<Rep, Period> const& d) const
      {
        if (std::has_facet<duration_units<CharT> >(ios.getloc()))
        {
          duration_units<CharT> const&facet = std::use_facet<duration_units<CharT> >(
              ios.getloc());
          return put_unit(facet, s, ios, fill, d);
        }
        else
        {
          duration_units_default<CharT> facet;
          return put_unit(facet, s, ios, fill, d);
        }
      }

      template <typename Rep, typename Period>
      iter_type put_unit(duration_units<CharT> const& facet, iter_type s, std::ios_base& ios, char_type fill,
          duration<Rep, Period> const& d) const
      {
        if (facet.template is_named_unit<Period>()) {
          string_type str = facet.get_unit(get_duration_style(ios), d);
          s=std::copy(str.begin(), str.end(), s);
        } else {
          *s++ = CharT('[');
          std::use_facet<std::num_put<CharT, iter_type> >(ios.getloc()).put(s, ios, fill, Period::num);
          *s++ = CharT('/');
          std::use_facet<std::num_put<CharT, iter_type> >(ios.getloc()).put(s, ios, fill, Period::den);
          *s++ = CharT(']');
          string_type str = facet.get_n_d_unit(get_duration_style(ios), d);
          s=std::copy(str.begin(), str.end(), s);
        }
        return s;
      }
      template <typename Rep, typename Period>
      iter_type put_unit(duration_units<CharT> const& facet, iter_type s, std::ios_base& ios, char_type fill,
          duration<process_times<Rep>, Period> const& d) const
      {
        duration<Rep,Period> real(d.count().real);
        if (facet.template is_named_unit<Period>()) {
          string_type str = facet.get_unit(get_duration_style(ios), real);
          s=std::copy(str.begin(), str.end(), s);
        } else {
          *s++ = CharT('[');
          std::use_facet<std::num_put<CharT, iter_type> >(ios.getloc()).put(s, ios, fill, Period::num);
          *s++ = CharT('/');
          std::use_facet<std::num_put<CharT, iter_type> >(ios.getloc()).put(s, ios, fill, Period::den);
          *s++ = CharT(']');
          string_type str = facet.get_n_d_unit(get_duration_style(ios), real);
          s=std::copy(str.begin(), str.end(), s);
        }
        return s;
      }

      /**
       * Unique identifier for this type of facet.
       */
      static std::locale::id id;

      /**
       * @Effects Destroy the facet
       */
      ~duration_put()
      {
      }

    };

    template <class CharT, class OutputIterator>
    std::locale::id duration_put<CharT, OutputIterator>::id;

  } // chrono
} // boost

#endif  // header

/* duration_put.hpp
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
*/