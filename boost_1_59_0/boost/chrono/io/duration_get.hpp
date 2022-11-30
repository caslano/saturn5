//  (C) Copyright Howard Hinnant
//  (C) Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//

#ifndef BOOST_CHRONO_IO_DURATION_GET_HPP
#define BOOST_CHRONO_IO_DURATION_GET_HPP

#include <boost/chrono/config.hpp>
#include <string>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/mpl/if.hpp>
#include <boost/integer/common_factor_rt.hpp>
#include <boost/chrono/detail/scan_keyword.hpp>
#include <boost/chrono/detail/no_warning/signed_unsigned_cmp.hpp>
#include <boost/chrono/process_cpu_clocks.hpp>

#include <boost/assert.hpp>
#include <locale>

/**
 * Duration formatting facet for input.
 */
namespace boost
{
  namespace chrono
  {

    namespace detail
    {
      template <class Rep, bool = is_scalar<Rep>::value>
      struct duration_io_intermediate
      {
        typedef Rep type;
      };

      template <class Rep>
      struct duration_io_intermediate<Rep, true>
      {
        typedef typename mpl::if_c<is_floating_point<Rep>::value, long double, typename mpl::if_c<
            is_signed<Rep>::value, long long, unsigned long long>::type>::type type;
      };

      template <class Rep>
      struct duration_io_intermediate<process_times<Rep>, false>
      {
        typedef process_times<typename duration_io_intermediate<Rep>::type> type;
      };

      template <typename intermediate_type>
      typename enable_if<is_integral<intermediate_type> , bool>::type reduce(intermediate_type& r,
          unsigned long long& den, std::ios_base::iostate& err)
      {
        typedef typename common_type<intermediate_type, unsigned long long>::type common_type_t;

        // Reduce r * num / den
        common_type_t t = integer::gcd<common_type_t>(common_type_t(r), common_type_t(den));
        r /= t;
        den /= t;
        if (den != 1)
        {
          // Conversion to Period is integral and not exact
          err |= std::ios_base::failbit;
          return false;
        }
        return true;
      }
      template <typename intermediate_type>
      typename disable_if<is_integral<intermediate_type> , bool>::type reduce(intermediate_type&, unsigned long long&,
          std::ios_base::iostate&)
      {
        return true;
      }

    }

    /**
     * @c duration_get is used to parse a character sequence, extracting
     * components of a duration into a class duration.
     * Each get member parses a format as produced by a corresponding format specifier to time_put<>::put.
     * If the sequence being parsed matches the correct format, the
     * corresponding member of the class duration argument are set to the
     * value used to produce the sequence;
     * otherwise either an error is reported or unspecified values are assigned.
     * In other words, user confirmation is required for reliable parsing of
     * user-entered durations, but machine-generated formats can be parsed
     * reliably. This allows parsers to be aggressive about interpreting user
     * variations on standard formats.
     *
     * If the end iterator is reached during parsing of the get() member
     * function, the member sets std::ios_base::eofbit in err.
     */
    template <class CharT, class InputIterator = std::istreambuf_iterator<CharT> >
    class duration_get: public std::locale::facet
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
       * Type of iterator used to scan the character buffer.
       */
      typedef InputIterator iter_type;

      /**
       * Construct a @c duration_get facet.
       * @param refs
       * @Effects Construct a @c duration_get facet.
       * If the @c refs argument is @c 0 then destruction of the object is
       * delegated to the @c locale, or locales, containing it. This allows
       * the user to ignore lifetime management issues. On the other had,
       * if @c refs is @c 1 then the object must be explicitly deleted;
       * the @c locale will not do so. In this case, the object can be
       * maintained across the lifetime of multiple locales.
       */

      explicit duration_get(size_t refs = 0) :
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
       * specifier character, format.
       * If the number of elements in the range [pattern,pat_end) is not
       * sufficient to unambiguously determine whether the conversion
       * specification is complete and valid, the function evaluates
       * err = std::ios_base::failbit. Otherwise, the function evaluates
       * s = get_value(s, end, ios, err, r) when the conversion specification is 'v' and
       * s = get_value(s, end, ios, err, rt) when the conversion specification is 'u'.
       * If err == std::ios_base::goodbit holds after
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
       * Once r and rt are retrieved,
       * Returns: s
       */
      template <typename Rep, typename Period>
      iter_type get(iter_type s, iter_type end, std::ios_base& ios, std::ios_base::iostate& err,
          duration<Rep, Period> &d, const char_type *pattern, const char_type *pat_end) const
      {
        if (std::has_facet<duration_units<CharT> >(ios.getloc()))
        {
          duration_units<CharT> const&facet = std::use_facet<duration_units<CharT> >(ios.getloc());
          return get(facet, s, end, ios, err, d, pattern, pat_end);
        }
        else
        {
          duration_units_default<CharT> facet;
          return get(facet, s, end, ios, err, d, pattern, pat_end);
        }
      }

      template <typename Rep, typename Period>
      iter_type get(duration_units<CharT> const&facet, iter_type s, iter_type end, std::ios_base& ios,
          std::ios_base::iostate& err, duration<Rep, Period> &d, const char_type *pattern, const char_type *pat_end) const
      {

        typedef typename detail::duration_io_intermediate<Rep>::type intermediate_type;
        intermediate_type r;
        rt_ratio rt;
        bool value_found = false, unit_found = false;

        const std::ctype<char_type>& ct = std::use_facet<std::ctype<char_type> >(ios.getloc());
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
            case 'v':
            {
              if (value_found)
              {
                err |= std::ios_base::failbit;
                return s;
              }
              value_found = true;
              s = get_value(s, end, ios, err, r);
              if (err & (std::ios_base::badbit | std::ios_base::failbit))
              {
                return s;
              }
              break;
            }
            case 'u':
            {
              if (unit_found)
              {
                err |= std::ios_base::failbit;
                return s;
              }
              unit_found = true;
              s = get_unit(facet, s, end, ios, err, rt);
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
            return s;
          }

        }

        unsigned long long num = rt.num;
        unsigned long long den = rt.den;

        // r should be multiplied by (num/den) / Period
        // Reduce (num/den) / Period to lowest terms
        unsigned long long gcd_n1_n2 = integer::gcd<unsigned long long>(num, Period::num);
        unsigned long long gcd_d1_d2 = integer::gcd<unsigned long long>(den, Period::den);
        num /= gcd_n1_n2;
        den /= gcd_d1_d2;
        unsigned long long n2 = Period::num / gcd_n1_n2;
        unsigned long long d2 = Period::den / gcd_d1_d2;
        if (num > (std::numeric_limits<unsigned long long>::max)() / d2 || den
            > (std::numeric_limits<unsigned long long>::max)() / n2)
        {
          // (num/den) / Period overflows
          err |= std::ios_base::failbit;
          return s;
        }
        num *= d2;
        den *= n2;

        typedef typename common_type<intermediate_type, unsigned long long>::type common_type_t;

        // num / den is now factor to multiply by r
        if (!detail::reduce(r, den, err)) return s;

        if (chrono::detail::gt(r, ( (duration_values<common_type_t>::max)() / num)))
        {
          // Conversion to Period overflowed
          err |= std::ios_base::failbit;
          return s;
        }
        common_type_t t = r * num;
        t /= den;
        if (t > duration_values<common_type_t>::zero())
        {
          if ( (duration_values<Rep>::max)() < Rep(t))
          {
            // Conversion to Period overflowed
            err |= std::ios_base::failbit;
            return s;
          }
        }
        // Success!  Store it.
        d = duration<Rep, Period> (Rep(t));

        return s;
      }

      /**
       *
       * @param s start input stream iterator
       * @param end end input stream iterator
       * @param ios a reference to a ios_base
       * @param err the ios_base state
       * @param d the duration
       * Stores the duration pattern from the @c duration_unit facet in let say @c str. Last as if
       * @code
       *   return get(s, end, ios, err, ios, d, str.data(), str.data() + str.size());
       * @codeend
       * @Returns An iterator pointing just beyond the last character that can be determined to be part of a valid name
       */
      template <typename Rep, typename Period>
      iter_type get(iter_type s, iter_type end, std::ios_base& ios, std::ios_base::iostate& err,
          duration<Rep, Period> & d) const
      {
        if (std::has_facet<duration_units<CharT> >(ios.getloc()))
        {
          duration_units<CharT> const&facet = std::use_facet<duration_units<CharT> >(ios.getloc());
          std::basic_string<CharT> str = facet.get_pattern();
          return get(facet, s, end, ios, err, d, str.data(), str.data() + str.size());
        }
        else
        {
          duration_units_default<CharT> facet;
          std::basic_string<CharT> str = facet.get_pattern();
          return get(facet, s, end, ios, err, d, str.data(), str.data() + str.size());
        }
      }

      /**
       *
       * @param s start input stream iterator
       * @param end end input stream iterator
       * @param ios a reference to a ios_base
       * @param err the ios_base state
       * @param r a reference to the duration representation.
       * @Effects As if
       * @code
       * return std::use_facet<std::num_get<cahr_type, iter_type> >(ios.getloc()).get(s, end, ios, err, r);
       * @endcode
       *
       * @Returns An iterator pointing just beyond the last character that can be determined to be part of a valid name
       */
      template <typename Rep>
      iter_type get_value(iter_type s, iter_type end, std::ios_base& ios, std::ios_base::iostate& err, Rep& r) const
      {
        return std::use_facet<std::num_get<CharT, iter_type> >(ios.getloc()).get(s, end, ios, err, r);
      }
      template <typename Rep>
      iter_type get_value(iter_type s, iter_type end, std::ios_base& ios, std::ios_base::iostate& err, process_times<Rep>& r) const
      {
        if (s == end) {
            err |= std::ios_base::eofbit;
            return s;
        } else if (*s != '{') { // mandatory '{'
            err |= std::ios_base::failbit;
            return s;
        }
        ++s;
        s = std::use_facet<std::num_get<CharT, iter_type> >(ios.getloc()).get(s, end, ios, err, r.real);
        if (s == end) {
            err |= std::ios_base::eofbit;
            return s;
        } else if (*s != ';') { // mandatory ';'
            err |= std::ios_base::failbit;
            return s;
        }
        ++s;
        s = std::use_facet<std::num_get<CharT, iter_type> >(ios.getloc()).get(s, end, ios, err, r.user);
        if (s == end) {
            err |= std::ios_base::eofbit;
            return s;
        } else if (*s != ';') { // mandatory ';'
            err |= std::ios_base::failbit;
            return s;
        }
        ++s;
        s = std::use_facet<std::num_get<CharT, iter_type> >(ios.getloc()).get(s, end, ios, err, r.system);
        if (s == end) {
            err |= std::ios_base::eofbit;
            return s;
        } else if (*s != '}') { // mandatory '}'
            err |= std::ios_base::failbit;
            return s;
        }
        return s;
      }

      /**
       *
       * @param s start input stream iterator
       * @param e end input stream iterator
       * @param ios a reference to a ios_base
       * @param err the ios_base state
       * @param rt a reference to the duration run-time ratio.
       * @Returns An iterator pointing just beyond the last character that can be determined to be part of a valid name
       */
      iter_type get_unit(iter_type i, iter_type e, std::ios_base& is, std::ios_base::iostate& err, rt_ratio &rt) const
      {
        if (std::has_facet<duration_units<CharT> >(is.getloc()))
        {
          return get_unit(std::use_facet<duration_units<CharT> >(is.getloc()), i, e, is, err, rt);
        }
        else
        {
          duration_units_default<CharT> facet;
          return get_unit(facet, i, e, is, err, rt);
        }
      }


      iter_type get_unit(duration_units<CharT> const &facet, iter_type i, iter_type e, std::ios_base& is,
          std::ios_base::iostate& err, rt_ratio &rt) const
      {

        if (*i == '[')
        {
          // parse [N/D]s or [N/D]second or [N/D]seconds format
          ++i;
          i = std::use_facet<std::num_get<CharT, iter_type> >(is.getloc()).get(i, e, is, err, rt.num);
          if ( (err & std::ios_base::failbit) != 0)
          {
            return i;
          }

          if (i == e)
          {
            err |= std::ios_base::failbit;
            return i;
          }
          CharT x = *i++;
          if (x != '/')
          {
            err |= std::ios_base::failbit;
            return i;
          }
          i = std::use_facet<std::num_get<CharT, iter_type> >(is.getloc()).get(i, e, is, err, rt.den);
          if ( (err & std::ios_base::failbit) != 0)
          {
            return i;
          }
          if (i == e)
          {
            err |= std::ios_base::failbit;
            return i;
          }
          if (*i != ']')
          {
            err |= std::ios_base::failbit;
            return i;
          }
          ++i;
          if (i == e)
          {
            err |= std::ios_base::failbit;
            return i;
          }
          // parse s or second or seconds
          return do_get_n_d_valid_unit(facet, i, e, is, err);
        }
        else
        {
          return do_get_valid_unit(facet, i, e, is, err, rt);
        }
      }

      /**
       * Unique identifier for this type of facet.
       */
      static std::locale::id id;

      /**
       * @Effects Destroy the facet
       */
      ~duration_get()
      {
      }

    protected:

      /**
       * Extracts the run-time ratio associated to the duration when it is given in prefix form.
       *
       * This is an extension point of this facet so that we can take in account other periods that can have a useful
       * translation in other contexts, as e.g. days and weeks.
       *
       * @param facet the duration_units facet
       * @param i start input stream iterator.
       * @param e end input stream iterator.
       * @param ios a reference to a ios_base.
       * @param err the ios_base state.
       * @return @c s
       */
      iter_type do_get_n_d_valid_unit(duration_units<CharT> const &facet, iter_type i, iter_type e,
          std::ios_base&, std::ios_base::iostate& err) const
      {
        // parse SI name, short or long

        const string_type* units = facet.get_n_d_valid_units_start();
        const string_type* units_end = facet.get_n_d_valid_units_end();

        const string_type* k = chrono_detail::scan_keyword(i, e, units, units_end,
        //~ std::use_facet<std::ctype<CharT> >(loc),
            err);
        if (err & (std::ios_base::badbit | std::ios_base::failbit))
        {
          return i;
        }
        if (!facet.match_n_d_valid_unit(k))
        {
          err |= std::ios_base::failbit;
        }
        return i;
      }

      /**
       * Extracts the run-time ratio associated to the duration when it is given in prefix form.
       *
       * This is an extension point of this facet so that we can take in account other periods that can have a useful
       * translation in other contexts, as e.g. days and weeks.
       *
       * @param facet the duration_units facet
       * @param i start input stream iterator.
       * @param e end input stream iterator.
       * @param ios a reference to a ios_base.
       * @param err the ios_base state.
       * @param rt a reference to the duration run-time ratio.
       * @Effects
       * @Returns An iterator pointing just beyond the last character that can be determined to be part of a valid name.
       */
      iter_type do_get_valid_unit(duration_units<CharT> const &facet, iter_type i, iter_type e,
          std::ios_base&, std::ios_base::iostate& err, rt_ratio &rt) const
      {
        // parse SI name, short or long

        const string_type* units = facet.get_valid_units_start();
        const string_type* units_end = facet.get_valid_units_end();

        err = std::ios_base::goodbit;
        const string_type* k = chrono_detail::scan_keyword(i, e, units, units_end,
        //~ std::use_facet<std::ctype<CharT> >(loc),
            err);
        if (err & (std::ios_base::badbit | std::ios_base::failbit))
        {
          return i;
        }
        if (!facet.match_valid_unit(k, rt))
        {
          err |= std::ios_base::failbit;
        }
        return i;
      }
    };

    /**
     * Unique identifier for this type of facet.
     */
    template <class CharT, class InputIterator>
    std::locale::id duration_get<CharT, InputIterator>::id;

  } // chrono
}
// boost

#endif  // header

/* duration_get.hpp
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
*/