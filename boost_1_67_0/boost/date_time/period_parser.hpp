
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
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
*/