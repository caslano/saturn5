
#ifndef DATETIME_PERIOD_PARSER_HPP___
#define DATETIME_PERIOD_PARSER_HPP___

/* Copyright (c) 2002-2004 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <ios>
#include <string>
#include <vector>
#include <iterator>
#include <boost/throw_exception.hpp>
#include <boost/date_time/special_defs.hpp>
#include <boost/date_time/string_parse_tree.hpp>
#include <boost/date_time/string_convert.hpp>


namespace boost { namespace date_time {


  //! Not a facet, but a class used to specify and control period parsing
  /*! Provides settings for the following:
   *   - period_separator -- default '/'
   *   - period_open_start_delimeter -- default '['
   *   - period_open_range_end_delimeter -- default ')'
   *   - period_closed_range_end_delimeter -- default ']'
   *   - display_as_open_range, display_as_closed_range -- default closed_range
   *
   *  For a typical date_period, the contents of the input stream would be
   *@code
   *  [2004-Jan-04/2004-Feb-01]
   *@endcode
   * where the date format is controlled by the date facet
   */
  template<class date_type, typename CharT>
  class period_parser {
  public:
    typedef std::basic_string<CharT> string_type;
    typedef CharT                    char_type;
    //typedef typename std::basic_string<char_type>::const_iterator const_itr_type;
    typedef std::istreambuf_iterator<CharT> stream_itr_type;
    typedef string_parse_tree<CharT> parse_tree_type;
    typedef typename parse_tree_type::parse_match_result_type match_results;
    typedef std::vector<std::basic_string<CharT> > collection_type;

    static const char_type default_period_separator[2];
    static const char_type default_period_start_delimeter[2];
    static const char_type default_period_open_range_end_delimeter[2];
    static const char_type default_period_closed_range_end_delimeter[2];

    enum period_range_option { AS_OPEN_RANGE, AS_CLOSED_RANGE };

    //! Constructor that sets up period parser options
    period_parser(period_range_option range_opt = AS_CLOSED_RANGE,
                  const char_type* const period_separator = default_period_separator,
                  const char_type* const period_start_delimeter = default_period_start_delimeter,
                  const char_type* const period_open_range_end_delimeter = default_period_open_range_end_delimeter,
                  const char_type* const period_closed_range_end_delimeter = default_period_closed_range_end_delimeter)
      : m_range_option(range_opt)
    {
      delimiters.push_back(string_type(period_separator));
      delimiters.push_back(string_type(period_start_delimeter));
      delimiters.push_back(string_type(period_open_range_end_delimeter));
      delimiters.push_back(string_type(period_closed_range_end_delimeter));
    }

    period_parser(const period_parser<date_type,CharT>& p_parser)
    {
      this->delimiters = p_parser.delimiters;
      this->m_range_option = p_parser.m_range_option;
    }

    period_range_option range_option() const
    {
      return m_range_option;
    }
    void range_option(period_range_option option)
    {
      m_range_option = option;
    }
    collection_type delimiter_strings() const
    {
      return delimiters;
    }
    void delimiter_strings(const string_type& separator,
                           const string_type& start_delim,
                           const string_type& open_end_delim,
                           const string_type& closed_end_delim)
    {
      delimiters.clear();
      delimiters.push_back(separator);
      delimiters.push_back(start_delim);
      delimiters.push_back(open_end_delim);
      delimiters.push_back(closed_end_delim);
    }

    //! Generic code to parse a period -- no matter the period type.
    /*! This generic code will parse any period using a facet to
     *  to get the 'elements'.  For example, in the case of a date_period
     *  the elements will be instances of a date which will be parsed
     *  according the to setup in the passed facet parameter.
     *
     *  The steps for parsing a period are always the same:
     *  - consume the start delimiter
     *  - get start element
     *  - consume the separator
     *  - get either last or end element depending on range settings
     *  - consume the end delimeter depending on range settings
     *
     *  Thus for a typical date period the contents of the input stream
     *  might look like this:
     *@code
     *
     *    [March 01, 2004/June 07, 2004]   <-- closed range
     *    [March 01, 2004/June 08, 2004)   <-- open range
     *
     *@endcode
     */
    template<class period_type, class duration_type, class facet_type>
    period_type get_period(stream_itr_type& sitr,
                           stream_itr_type& stream_end,
                           std::ios_base& a_ios,
                           const period_type& /* p */,
                           const duration_type& dur_unit,
                           const facet_type& facet) const
    {
      // skip leading whitespace
      while(std::isspace(*sitr) && sitr != stream_end) { ++sitr; }

      typedef typename period_type::point_type point_type;
      point_type p1(not_a_date_time), p2(not_a_date_time);


      consume_delim(sitr, stream_end, delimiters[START]);       // start delim
      facet.get(sitr, stream_end, a_ios, p1);                   // first point
      consume_delim(sitr, stream_end, delimiters[SEPARATOR]);   // separator
      facet.get(sitr, stream_end, a_ios, p2);                   // second point

      // period construction parameters are always open range [begin, end)
      if (m_range_option == AS_CLOSED_RANGE) {
        consume_delim(sitr, stream_end, delimiters[CLOSED_END]);// end delim
        // add 1 duration unit to p2 to make range open
        p2 += dur_unit;
      }
      else {
        consume_delim(sitr, stream_end, delimiters[OPEN_END]);  // end delim
      }

      return period_type(p1, p2);
    }

  private:
    collection_type delimiters;
    period_range_option m_range_option;

    enum delim_ids { SEPARATOR, START, OPEN_END, CLOSED_END };

    //! throws ios_base::failure if delimiter and parsed data do not match
    void consume_delim(stream_itr_type& sitr,
                       stream_itr_type& stream_end,
                       const string_type& delim) const
    {
      /* string_parse_tree will not parse a string of punctuation characters
       * without knowing exactly how many characters to process
       * Ex [2000. Will not parse out the '[' string without knowing
       * to process only one character. By using length of the delimiter
       * string we can safely iterate past it. */
      string_type s;
      for(unsigned int i = 0; i < delim.length() && sitr != stream_end; ++i) {
        s += *sitr;
        ++sitr;
      }
      if(s != delim) {
        boost::throw_exception(std::ios_base::failure("Parse failed. Expected '"
          + convert_string_type<char_type,char>(delim) + "' but found '" + convert_string_type<char_type,char>(s) + "'"));
      }
    }
  };

  template <class date_type, class char_type>
  const typename period_parser<date_type, char_type>::char_type
  period_parser<date_type, char_type>::default_period_separator[2] = {'/'};

  template <class date_type, class char_type>
  const typename period_parser<date_type, char_type>::char_type
  period_parser<date_type, char_type>::default_period_start_delimeter[2] = {'['};

  template <class date_type, class char_type>
  const typename period_parser<date_type, char_type>::char_type
  period_parser<date_type, char_type>::default_period_open_range_end_delimeter[2] = {')'};

  template <class date_type, class char_type>
  const typename period_parser<date_type, char_type>::char_type
  period_parser<date_type, char_type>::default_period_closed_range_end_delimeter[2] = {']'};

 } } //namespace boost::date_time

#endif // DATETIME_PERIOD_PARSER_HPP___

/* period_parser.hpp
09jScyctErevw0UCF5mnV8tF4pkJbOmZAnWaMYUqXNmXDjW7GSsq7kQ2l9VwyTPWM43ZkVlirxEYP8l9kGqTyWrzgb42Pak2e+RuwTykFbaWBbPKw17ftNvFjpDHwBtZdG8aNIUZPHJ4ZBNmFcFEbFPZ6vk4VWXGWhPC3DOerZ7j+eqJy8wP7zAS+5Q1Gldi2lLVEa4+ZriGE672mnTuI05X+ch/atk9bJ/46/foa7T9OonnIx8Ry/G+YU3cL7jm4Rh+qj5rpxJ2wv9ySq64qunCH6SwctFM4Lpwz5W9STOEAzVFcqgUzqFSajIZn4AzDOQhO0KMhdRaOsRQ9f9Ven3ABE0FcMFwVQXwz1naU3bIey5/Yu7IOhTV9qSV/yRotsjlDbW6CXUDx1NS54cFIX9aYFGu0esHXrpaH9BHKgpeekjc4fvpFFVRgO05OdSiTFGsh3LO057cUs0Ok0P8diNUGnuKFHAjm3Jy5Oyh6TH8IalxWKv5fx7TGD1of6zq/Z+rSHX6xz8p5yk/9m+aYCZHKW5+lAL/8I08SsnmYSyy+fvTXZCwOaE+9N+LH+fPg0b7/0oixSlDuf1/TXL2/xzcOdTc/nW2df38EI6qttRg/2SKBeUrtT0KKhtH1b1Evf/ks3Kf56UggUaGED2uuNHCfYyFHGjUcKW8B/slvI/RztgfgzmqNsOp/K/nJdUfzTh4/hBz+/9ZSZ6/bLyS8M05x9z+f6b1/p3IUS06I7Z/5860cn6Sx+F/HhYLf5oCb37/6QoCPXm+0j/pfRP2z7w1xvt/HNXXNdQ/f6pOqn/Gc/DHa8zvP9xgnZ4dOKrymlh69DPFErutGAen/t08+M54/3cyQw3hDdoM/CHfZtzL0qkqnnKy/UVhvP3uUZFMkRNLT2L3C/X1sfuPVJXQ8gGqmxduWuNVbXC80sIieCz7yZac1tE2V34PTcAXybmIV+9/V1AlrlY727y+s3nW8O9VJyh86fOIpY9O08H6I1rPTuHnFWUnrBW//0f4wf4s/6o8kCz4sflHzSVh9fX57nJ+QUZXH+qddHFy76bCm7jvb9Lk2FApNZcbQ6VUoAaqijTip9jZwr72flzYJ+DCPg4X9t4Ie8EIJs6/a0dX73W4twi1/rNUmb0Iz3V2zOcaLV+utaNw8kfy5VMGSOnK959P0gsnrOizqOgTWdFF+qI/PZ8VfQGWubylzWSwn4IoziEU/7zPBMWq81ECG05VefU+IYFVkbUpSpWEjCJ4BNz4VIWVLKVf0QZ8qOKO7K4LOTJ17ssxqB06CbkhAPhgSm7+Jt8mbSZpf8DlggA622Gh+AdlgCTbS7jeR8rQdl8qjH5pIRQ3JA77w+Nhwy/r6Yd6urhWt8WLV8JIm3cpI313JMZlRIxP7kVijNMT4xaQ/SLcRCKTCHGKC9UGv/Z42Fz+nUTz5TifbhwF2yqBGjK4UJ4towRcQqk4k6Rd9Mv+XEwTFI+2+XlfPpABFGC0DzyKiLjyHiTieCTiBEnEM8s0rxc+JuV/eApajRxK2LL4+qEdE/mlt376udM89A5shNQ3OPHQJlwLk9BKccyB8mnArREqa9ZYOfbRA1ZVrrPyHPFIhr7oHdEuX8FQJe86ckO0NJ0/QZLbFhN7rNaJRokVDn0ZdhkBrwTfnQ4tdcl06BTIrkdZ60A0x8WgcVSWmTcN01l/5u0V/Xkc9ufrtHF5dZXsz4tlf04DaS58J8YS+hBOvDH3Tsp9F8tdrM9dqtsT3upqggTQHxXIue5CB+D60LtYYWIg3HyTzkhRZQM9s4zt7T6lvV27VcSzqkIZJ2DRknBF2VqTcbxXnop1/4zbr99FvFBX91vPUev+Tpo=
*/