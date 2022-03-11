
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