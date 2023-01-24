
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
frZJcYIxaz+/Vb+D/klIsnrMHicCo/bdBxpY9YvHwGnnh6r8A3+ONLn+uWyB1O1sJfIjLf61SxWnoHiS0np2bPXH7/MGX+Y/2uSmGp2RrFfLnZGVlNPInQ1UZzzkvN+f3jAVePRQukzzIXeGOntUB2UeMZ5h2frdb9WYvnIvGPfPT7dp/Zrc/B0AZyyY0zCWJsM7InGgKkkJyHyRHZHNQDWSMFD/SCi1Eag3A7UxQpEXkgG0mYnuVSj1JRIF6jtgejOsEr9MLjmRlm8LquQL4duDHeQm+VTQR5aRN8NoOorln7BcLdHyQ1j+K5avYBmRaVmKZTWWMuLXYvk+LKsRuQPLL2K5lHwUvBzB8hUsV0m0/CCW38Lyj1iGZVqqWFZhKSF+DZa3YVmFyO1Y3o9lLbkLyhyWP8eyVaLlLVg+jOWvsSQyLevIJ6Hsw/IXWC6QaHkrll/D8mUsJZmWEfJpKM/H8nksZ0u0jJKDcHabsfwxlo0SLRPkHpDuwLKM3AvlTizbyG1QDmP5MpaLJFo2kX+BcgBKicQi18Asvyt+EMqu8AiUR3y0LImOkCXkQpna/wfg+0iN8mayPUWH2K1kayQIPZVhVG80CNdlL6O2AQVeGXVL+ItBPznGqOviX4Rxez2jbgwGSYi8k1Fj8SCMyPcyKgOyCPkIpchNoTvCXw1GyZeBCpGbyFeijwD1EMpuJlcpS+k81qBRP44u
*/