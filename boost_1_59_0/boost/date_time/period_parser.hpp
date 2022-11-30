
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
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
*/