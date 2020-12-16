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
vJ4NvJ6beR238jruAA+Cd4EfgveCH4F/Aj8GXwY/AXeC7RDfEbA9eAz8HO5mog+BoeAXYH3wMNdrPgJ2Ab8Eu4NHwV7gMbAf+A04BDwBjge/Bc8HT4JZ4HdgHvgjuBBUOO8y0AVeC9YDK8D64FawAfg4GAY+C0aAL4GR4H6wIXgUjDLTD8aAP4JNQSfyPQ5sBTYH24DxYGewA8vJrfhdAmazvMPBLBjFNVzkW4r1JRVsTr1OK+p7kqnvmUJdD4w6j7qYGeb1U+eTxnCsZ/huCF7PBrCeDWQ9S2Y9G8x6NojpX6b4/g5uYDyRbOu5lg/CIxx1ZUPA3uAw8Gzqo1Kpj8oEU8Bs6rrc1IeVUx+2mPqvS6n/upr+zHQgD/g+jTBMRwjYnekYxusZDg4CR4DDaNdr8TD8DIa36tQuYDlcxHJIYznksBzSeR/NpU4pk/q0LOqUsnmdOUzvJ/rdCefg/TnY0seYx/gv5ho8BdSVFYEpoJtr7pQwn8rBa6mDWsM1n9ZTD3Uz9VAbqYe6m2sivUy906vUO+2nzukEdU4/UefkQpquBcPA68AocBUYDa4G48HrwZbgGrA1uBZsB64Du4E3gsPBDeAo8GZwCrgRnAHeBs4B7+C663eCZeBdYDl4N7gc/B14F/h78FFwC/g4+AfwWfB+cDu4FXwR/BO4A3wIfA18mOuxbwPfA58FPwBvBQ2Uw3NgJPgAGAc+CbYEnwJ7gZVgX/BpcABohh8CLjCvi+GngIVgKu3rHDXrwiq/9ujCNg3F/zD7YYJpxCYN8+jE1oFbYHbARPVA/KBXNzZneGDt2FVwvxtGa8iGB9aRbRlRs5ZsTArCgFngdHATGHgtJZgUn66sfGRwbVkcMnE3mAIeArPAu0edWa3ZodHIrzHIC9MNLIXZCPMEjFWDth/2qLEeLVoq+AHKyK5Jw7GxgXVpMeM82rTu4HiYQBq1Q+MC69RanIU8OctxSnq1OeMdWrOmvsG6TDDJMOkwy2AqYCphDsCo4zh+vE63Vver+9X96n7/T7+fZ/wfXZZnYPw/keP/Ubbxf/vYfxPuAVDdGgApRZax/39h3H93kHH/1KLaj/vDb7Xj/tOKTm/cf7A3rUHG/aM8aa31mD/8VzPmz+PBx/xx/Ocd89drFXDs8BsnvrHJjTiSlCvXX+N4v8ffEJXIfvD5Yo92rlat0CeC9z6YLsa37Cc31HdyvJszAj0GQ4yJwcb9GW+y7v/OFXtT51rEO9D4B9198SWg54Lx2TUA7NudK/4SnH/0zv/Uae+jx++XzTft9wbTANB/fz1ukC32OOcNSFMn2XvxG6QLxyzpaqZ+0OlaEqC/frb4a+/crOKoCdDpCKoJmCNh2jjX4Gt9nWOa7iv/hyfPnN3UHqOFo6Oa7hhu1wQwfJjE35HxMRx8Mxz8aQ1AH8W0noe03p7nNH0rt+pEN14nrhD5bw3X2zpWsln8RIl9EuxDJZ4uEsd02G8R+1HU204M4423ldYb/CD2Qdgd0mlIOMu5W6rjCKfHI+aWmHlFvchKidtA6bjUcqa7yBIW5WMJWyRh47kH6DUS1mU4EDZMOdUKho9VvvBmPZ6Cezbaon/I8JD/Uw9RS03Eqegitkg5ajvqjU8XMWq+V6PQT+8f+czFXre+WgNxrc9N70d5SZ7WT+iwrXxuvbVWIq+qpuLt3Kp7WVbkVtVZ3OJz6+N1W+Vzk8uPh1ujiwNpK4KMowRo+9yqqraiXAVf/2MLH4ZXwzSCWeZd/6OQ7WEQHQXbQ/izj8kWi71ExmTDdBuA9pP3/yo5nqLHUzOiTk9n4b2OT/i5au7d1xY8wvHlnTlyHTVqLDz+oHdhW9dgnmnfFUw=
*/