
#ifndef DATE_TIME_DATE_GENERATOR_PARSER_HPP__
#define DATE_TIME_DATE_GENERATOR_PARSER_HPP__

/* Copyright (c) 2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <string>
#include <vector>
#include <iterator> // istreambuf_iterator
#include <boost/throw_exception.hpp>
#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/string_parse_tree.hpp>
#include <boost/date_time/date_generators.hpp>
#include <boost/date_time/format_date_parser.hpp>

namespace boost { namespace date_time {

  //! Class for date_generator parsing 
  /*! The elements of a date_generator "phrase" are parsed from the input stream in a 
   *  particular order. All elements are required and the order in which they appear 
   *  cannot change, however, the elements themselves can be changed. The default 
   *  elements and their order are as follows:
   *
   * - partial_date                     => "dd Month"
   * - nth_day_of_the_week_in_month     => "nth weekday of month"
   * - first_day_of_the_week_in_month   => "first weekday of month"
   * - last_day_of_the_week_in_month    => "last weekday of month"
   * - first_day_of_the_week_after      => "weekday after"
   * - first_day_of_the_week_before     => "weekday before"
   *
   * Weekday and Month names and formats are handled via the date_input_facet. 
   *
   */
  template<class date_type, typename charT>
  class date_generator_parser
  {
   public:
    typedef std::basic_string<charT>        string_type;
    typedef std::istreambuf_iterator<charT> stream_itr_type;

    typedef typename date_type::month_type       month_type;
    typedef typename date_type::day_of_week_type day_of_week_type;
    typedef typename date_type::day_type         day_type;

    typedef string_parse_tree<charT>                          parse_tree_type;
    typedef typename parse_tree_type::parse_match_result_type match_results;
    typedef std::vector<std::basic_string<charT> >            collection_type;

    typedef partial_date<date_type>          partial_date_type;
    typedef nth_kday_of_month<date_type>     nth_kday_type;
    typedef first_kday_of_month<date_type>   first_kday_type;
    typedef last_kday_of_month<date_type>    last_kday_type;
    typedef first_kday_after<date_type>      kday_after_type;
    typedef first_kday_before<date_type>     kday_before_type;

    typedef charT char_type;
    static const char_type first_string[6];
    static const char_type second_string[7];
    static const char_type third_string[6];
    static const char_type fourth_string[7];
    static const char_type fifth_string[6];
    static const char_type last_string[5];
    static const char_type before_string[8];
    static const char_type after_string[6];
    static const char_type of_string[3];

    enum phrase_elements {first=0, second, third, fourth, fifth, last,
                          before, after, of, number_of_phrase_elements};

    //! Creates a date_generator_parser with the default set of "element_strings"
    date_generator_parser()
    {
      element_strings(string_type(first_string),
                      string_type(second_string),
                      string_type(third_string),
                      string_type(fourth_string),
                      string_type(fifth_string),
                      string_type(last_string),
                      string_type(before_string),
                      string_type(after_string),
                      string_type(of_string));
    }

    //! Creates a date_generator_parser using a user defined set of element strings
    date_generator_parser(const string_type& first_str,
                          const string_type& second_str,
                          const string_type& third_str,
                          const string_type& fourth_str,
                          const string_type& fifth_str,
                          const string_type& last_str,
                          const string_type& before_str,
                          const string_type& after_str,
                          const string_type& of_str)
    {
      element_strings(first_str, second_str, third_str, fourth_str, fifth_str,
                      last_str, before_str, after_str, of_str);
    }

    //! Replace strings that determine nth week for generator
    void element_strings(const string_type& first_str,
                         const string_type& second_str,
                         const string_type& third_str,
                         const string_type& fourth_str,
                         const string_type& fifth_str,
                         const string_type& last_str,
                         const string_type& before_str,
                         const string_type& after_str,
                         const string_type& of_str)
    {
      collection_type phrases;
      phrases.push_back(first_str);
      phrases.push_back(second_str);
      phrases.push_back(third_str);
      phrases.push_back(fourth_str);
      phrases.push_back(fifth_str);
      phrases.push_back(last_str);
      phrases.push_back(before_str);
      phrases.push_back(after_str);
      phrases.push_back(of_str);
      m_element_strings = parse_tree_type(phrases, this->first); // enum first
    }

    void element_strings(const collection_type& col)
    {
      m_element_strings = parse_tree_type(col, this->first); // enum first
    }

    //! returns partial_date parsed from stream
    template<class facet_type>
    partial_date_type
    get_partial_date_type(stream_itr_type& sitr,
                          stream_itr_type& stream_end,
                          std::ios_base& a_ios,
                          const facet_type& facet) const
    {
      // skip leading whitespace
      while(std::isspace(*sitr) && sitr != stream_end) { ++sitr; }

      day_type d(1);
      month_type m(1);
      facet.get(sitr, stream_end, a_ios, d);
      facet.get(sitr, stream_end, a_ios, m);

      return partial_date_type(d,m);
    }

    //! returns nth_kday_of_week parsed from stream
    template<class facet_type>
    nth_kday_type
    get_nth_kday_type(stream_itr_type& sitr,
                      stream_itr_type& stream_end,
                      std::ios_base& a_ios,
                      const facet_type& facet) const
    {
      // skip leading whitespace
      while(std::isspace(*sitr) && sitr != stream_end) { ++sitr; }
 
      typename nth_kday_type::week_num wn;
      day_of_week_type wd(0); // no default constructor
      month_type m(1);        // no default constructor

      match_results mr = m_element_strings.match(sitr, stream_end);
      switch(mr.current_match) {
        case first  : { wn = nth_kday_type::first; break; }
        case second : { wn = nth_kday_type::second; break; }
        case third  : { wn = nth_kday_type::third; break; }
        case fourth : { wn = nth_kday_type::fourth; break; }
        case fifth  : { wn = nth_kday_type::fifth; break; }
        default:
        {
          boost::throw_exception(std::ios_base::failure("Parse failed. No match found for '" + mr.cache + "'"));
          BOOST_DATE_TIME_UNREACHABLE_EXPRESSION(wn = nth_kday_type::first);
        }
      }                                         // week num
      facet.get(sitr, stream_end, a_ios, wd);   // day_of_week
      extract_element(sitr, stream_end, of);    // "of" element
      facet.get(sitr, stream_end, a_ios, m);    // month

      return nth_kday_type(wn, wd, m);
    }

    //! returns first_kday_of_week parsed from stream
    template<class facet_type>
    first_kday_type
    get_first_kday_type(stream_itr_type& sitr,
                        stream_itr_type& stream_end,
                        std::ios_base& a_ios,
                        const facet_type& facet) const
    {
      // skip leading whitespace
      while(std::isspace(*sitr) && sitr != stream_end) { ++sitr; }

      day_of_week_type wd(0); // no default constructor
      month_type m(1);        // no default constructor

      extract_element(sitr, stream_end, first); // "first" element
      facet.get(sitr, stream_end, a_ios, wd);   // day_of_week
      extract_element(sitr, stream_end, of);    // "of" element
      facet.get(sitr, stream_end, a_ios, m);    // month


      return first_kday_type(wd, m);
    }

    //! returns last_kday_of_week parsed from stream
    template<class facet_type>
    last_kday_type
    get_last_kday_type(stream_itr_type& sitr,
                       stream_itr_type& stream_end,
                       std::ios_base& a_ios,
                       const facet_type& facet) const
    {
      // skip leading whitespace
      while(std::isspace(*sitr) && sitr != stream_end) { ++sitr; }

      day_of_week_type wd(0); // no default constructor
      month_type m(1);        // no default constructor
 
      extract_element(sitr, stream_end, last); // "last" element
      facet.get(sitr, stream_end, a_ios, wd);  // day_of_week
      extract_element(sitr, stream_end, of);   // "of" element
      facet.get(sitr, stream_end, a_ios, m);   // month


      return last_kday_type(wd, m);
    }

    //! returns first_kday_of_week parsed from stream
    template<class facet_type>
    kday_before_type
    get_kday_before_type(stream_itr_type& sitr,
                         stream_itr_type& stream_end,
                         std::ios_base& a_ios,
                         const facet_type& facet) const
    {
      // skip leading whitespace
      while(std::isspace(*sitr) && sitr != stream_end) { ++sitr; }

      day_of_week_type wd(0); // no default constructor

      facet.get(sitr, stream_end, a_ios, wd);   // day_of_week
      extract_element(sitr, stream_end, before);// "before" element

      return kday_before_type(wd);
    }

    //! returns first_kday_of_week parsed from stream
    template<class facet_type>
    kday_after_type
    get_kday_after_type(stream_itr_type& sitr,
                        stream_itr_type& stream_end,
                        std::ios_base& a_ios,
                        const facet_type& facet) const
    {
      // skip leading whitespace
      while(std::isspace(*sitr) && sitr != stream_end) { ++sitr; }

      day_of_week_type wd(0); // no default constructor

      facet.get(sitr, stream_end, a_ios, wd);   // day_of_week
      extract_element(sitr, stream_end, after); // "after" element

      return kday_after_type(wd);
    }

   private:
    parse_tree_type m_element_strings;

    //! Extracts phrase element from input. Throws ios_base::failure on error.
    void extract_element(stream_itr_type& sitr,
                         stream_itr_type& stream_end,
                         typename date_generator_parser::phrase_elements ele) const
    {
      // skip leading whitespace
      while(std::isspace(*sitr) && sitr != stream_end) { ++sitr; }
      match_results mr = m_element_strings.match(sitr, stream_end);
      if(mr.current_match != ele) {
        boost::throw_exception(std::ios_base::failure("Parse failed. No match found for '" + mr.cache + "'"));
      }
    }

  };

  template<class date_type, class CharT>
  const typename date_generator_parser<date_type, CharT>::char_type
  date_generator_parser<date_type, CharT>::first_string[6] =
    {'f','i','r','s','t'};
  template<class date_type, class CharT>
  const typename date_generator_parser<date_type, CharT>::char_type
  date_generator_parser<date_type, CharT>::second_string[7] =
    {'s','e','c','o','n','d'};
  template<class date_type, class CharT>
  const typename date_generator_parser<date_type, CharT>::char_type
  date_generator_parser<date_type, CharT>::third_string[6] =
    {'t','h','i','r','d'};
  template<class date_type, class CharT>
  const typename date_generator_parser<date_type, CharT>::char_type
  date_generator_parser<date_type, CharT>::fourth_string[7] =
    {'f','o','u','r','t','h'};
  template<class date_type, class CharT>
  const typename date_generator_parser<date_type, CharT>::char_type
  date_generator_parser<date_type, CharT>::fifth_string[6] =
    {'f','i','f','t','h'};
  template<class date_type, class CharT>
  const typename date_generator_parser<date_type, CharT>::char_type
  date_generator_parser<date_type, CharT>::last_string[5] =
    {'l','a','s','t'};
  template<class date_type, class CharT>
  const typename date_generator_parser<date_type, CharT>::char_type
  date_generator_parser<date_type, CharT>::before_string[8] =
    {'b','e','f','o','r','e'};
  template<class date_type, class CharT>
  const typename date_generator_parser<date_type, CharT>::char_type
  date_generator_parser<date_type, CharT>::after_string[6] =
    {'a','f','t','e','r'};
  template<class date_type, class CharT>
  const typename date_generator_parser<date_type, CharT>::char_type
  date_generator_parser<date_type, CharT>::of_string[3] =
    {'o','f'};

} } //namespace

#endif // DATE_TIME_DATE_GENERATOR_PARSER_HPP__


/* date_generator_parser.hpp
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
*/