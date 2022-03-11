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