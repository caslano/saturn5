
#ifndef DATE_TIME_SPECIAL_VALUES_PARSER_HPP__
#define DATE_TIME_SPECIAL_VALUES_PARSER_HPP__

/* Copyright (c) 2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date: 
 */


#include "boost/date_time/string_parse_tree.hpp"
#include "boost/date_time/special_defs.hpp"
#include <string>
#include <vector>

namespace boost { namespace date_time {

  //! Class for special_value parsing 
  /*! 
   * TODO: add doc-comments for which elements can be changed
   * Parses input stream for strings representing special_values. 
   * Special values parsed are:
   *  - not_a_date_time
   *  - neg_infin
   *  - pod_infin
   *  - min_date_time
   *  - max_date_time
   */
  template<class date_type, typename charT>
  class special_values_parser
  {
   public:
    typedef std::basic_string<charT>        string_type;
    typedef std::basic_stringstream<charT>  stringstream_type;
    typedef std::istreambuf_iterator<charT> stream_itr_type;
    typedef typename date_type::duration_type duration_type;
    typedef string_parse_tree<charT> parse_tree_type;
    typedef typename parse_tree_type::parse_match_result_type match_results;
    typedef std::vector<std::basic_string<charT> > collection_type;

    typedef charT char_type;
    static const char_type nadt_string[16];
    static const char_type neg_inf_string[10];
    static const char_type pos_inf_string[10];
    static const char_type min_date_time_string[18];
    static const char_type max_date_time_string[18];
   
    //! Creates a special_values_parser with the default set of "sv_strings"
    special_values_parser()
    {
      sv_strings(string_type(nadt_string),
                 string_type(neg_inf_string),
                 string_type(pos_inf_string),
                 string_type(min_date_time_string),
                 string_type(max_date_time_string));
    }

    //! Creates a special_values_parser using a user defined set of element strings
    special_values_parser(const string_type& nadt_str,
                          const string_type& neg_inf_str,
                          const string_type& pos_inf_str,
                          const string_type& min_dt_str,
                          const string_type& max_dt_str)
    {
      sv_strings(nadt_str, neg_inf_str, pos_inf_str, min_dt_str, max_dt_str);
    }

    special_values_parser(typename collection_type::iterator beg, typename collection_type::iterator end)
    {
      collection_type phrases;
      std::copy(beg, end, std::back_inserter(phrases));
      m_sv_strings = parse_tree_type(phrases, static_cast<int>(not_a_date_time));
    }

    special_values_parser(const special_values_parser<date_type,charT>& svp)
    {
      this->m_sv_strings = svp.m_sv_strings;
    }

    //! Replace special value strings
    void sv_strings(const string_type& nadt_str,
                    const string_type& neg_inf_str,
                    const string_type& pos_inf_str,
                    const string_type& min_dt_str,
                    const string_type& max_dt_str)
    {
      collection_type phrases;
      phrases.push_back(nadt_str);
      phrases.push_back(neg_inf_str);
      phrases.push_back(pos_inf_str);
      phrases.push_back(min_dt_str);
      phrases.push_back(max_dt_str);
      m_sv_strings = parse_tree_type(phrases, static_cast<int>(not_a_date_time));
    }

    //! The parser is expensive to create, and not thread-safe so it cannot be static
    //! therefore given a string, determine if it is likely to be a special value.
    //! A negative response is a definite no, whereas a positive is only likely and
    //! match() should be called and return value checked.
    //! \param[in]  str  the string to check
    //! \returns  false if it is definitely not a special value
    static bool likely(const string_type& str)
    {
        if (!str.empty()) {
            switch (str[0]) {
                // See string definitions at the end of this class..
                case '+':
                case '-':
                case 'n':
                case 'm':
                    return true;

                default:
                    break;
            }
        }

        return false;
    }

    //! Given an input iterator, attempt to match it to a known special value
    //! \param[in]  sitr  the start iterator
    //! \param[in]  str_end  the end iterator
    //! \param[out]  mr  the match result:
    //!                  mr.current_match is set to the corresponding special_value or -1
    //! \returns  whether something matched
    bool match(stream_itr_type& sitr, 
                        stream_itr_type& str_end,
                        match_results& mr) const
    {
      unsigned int level = 0;
      m_sv_strings.match(sitr, str_end, mr, level);
      return (mr.current_match != match_results::PARSE_ERROR);
    }

   private:
    parse_tree_type m_sv_strings;
    
  };

  template<class date_type, class CharT>
  const typename special_values_parser<date_type, CharT>::char_type
  special_values_parser<date_type, CharT>::nadt_string[16] =
  {'n','o','t','-','a','-','d','a','t','e','-','t','i','m','e'};
  template<class date_type, class CharT>
  const typename special_values_parser<date_type, CharT>::char_type
  special_values_parser<date_type, CharT>::neg_inf_string[10] =
  {'-','i','n','f','i','n','i','t','y'};
  template<class date_type, class CharT>
  const typename special_values_parser<date_type, CharT>::char_type
  special_values_parser<date_type, CharT>::pos_inf_string[10] =
  {'+','i','n','f','i','n','i','t','y'};
  template<class date_type, class CharT>
  const typename special_values_parser<date_type, CharT>::char_type
  special_values_parser<date_type, CharT>::min_date_time_string[18] =
  {'m','i','n','i','m','u','m','-','d','a','t','e','-','t','i','m','e'};
  template<class date_type, class CharT>
  const typename special_values_parser<date_type, CharT>::char_type
  special_values_parser<date_type, CharT>::max_date_time_string[18] =
  {'m','a','x','i','m','u','m','-','d','a','t','e','-','t','i','m','e'};

} } //namespace

#endif // DATE_TIME_SPECIAL_VALUES_PARSER_HPP__


/* special_values_parser.hpp
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
*/