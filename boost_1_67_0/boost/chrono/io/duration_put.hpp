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