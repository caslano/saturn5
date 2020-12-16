#ifndef _DATE_TIME_DATE_PARSING_HPP___
#define _DATE_TIME_DATE_PARSING_HPP___

/* Copyright (c) 2002,2003,2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <map>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/parse_format_base.hpp>
#include <boost/date_time/period.hpp>

#if defined(BOOST_DATE_TIME_NO_LOCALE)
#include <cctype> // ::tolower(int)
#else
#include <locale> // std::tolower(char, locale)
#endif

namespace boost {
namespace date_time {

  //! A function to replace the std::transform( , , ,tolower) construct
  /*! This function simply takes a string, and changes all the characters
   * in that string to lowercase (according to the default system locale).
   * In the event that a compiler does not support locales, the old
   * C style tolower() is used.
   */
  inline
  std::string
  convert_to_lower(std::string inp)
  {
#if !defined(BOOST_DATE_TIME_NO_LOCALE)
    const std::locale loc(std::locale::classic());
#endif
    std::string::size_type i = 0, n = inp.length();
    for (; i < n; ++i) {
      inp[i] =
#if defined(BOOST_DATE_TIME_NO_LOCALE)
        static_cast<char>(std::tolower(inp[i]));
#else
        // tolower and others were brought in to std for borland >= v564
        // in compiler_config.hpp
        std::tolower(inp[i], loc);
#endif
    }
    return inp;
  }

    //! Helper function for parse_date.
    template<class month_type>
    inline unsigned short
    month_str_to_ushort(std::string const& s) {
      if((s.at(0) >= '0') && (s.at(0) <= '9')) {
        return boost::lexical_cast<unsigned short>(s);
      }
      else {
        std::string str = convert_to_lower(s);
        //c++98 support
#if defined(BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX)
        static std::map<std::string, unsigned short> month_map;
        typedef std::map<std::string, unsigned short>::value_type vtype;
        if( month_map.empty() ) {
          month_map.insert( vtype("jan", static_cast<unsigned short>(1)) );
          month_map.insert( vtype("january", static_cast<unsigned short>(1)) );
          month_map.insert( vtype("feb", static_cast<unsigned short>(2)) );
          month_map.insert( vtype("february", static_cast<unsigned short>(2)) );
          month_map.insert( vtype("mar", static_cast<unsigned short>(3)) );
          month_map.insert( vtype("march", static_cast<unsigned short>(3)) );
          month_map.insert( vtype("apr", static_cast<unsigned short>(4)) );
          month_map.insert( vtype("april", static_cast<unsigned short>(4)) );
          month_map.insert( vtype("may", static_cast<unsigned short>(5)) );
          month_map.insert( vtype("jun", static_cast<unsigned short>(6)) );
          month_map.insert( vtype("june", static_cast<unsigned short>(6)) );
          month_map.insert( vtype("jul", static_cast<unsigned short>(7)) );
          month_map.insert( vtype("july", static_cast<unsigned short>(7)) );
          month_map.insert( vtype("aug", static_cast<unsigned short>(8)) );
          month_map.insert( vtype("august", static_cast<unsigned short>(8)) );
          month_map.insert( vtype("sep", static_cast<unsigned short>(9)) );
          month_map.insert( vtype("september", static_cast<unsigned short>(9)) );
          month_map.insert( vtype("oct", static_cast<unsigned short>(10)) );
          month_map.insert( vtype("october", static_cast<unsigned short>(10)) );
          month_map.insert( vtype("nov", static_cast<unsigned short>(11)) );
          month_map.insert( vtype("november", static_cast<unsigned short>(11)) );
          month_map.insert( vtype("dec", static_cast<unsigned short>(12)) );
          month_map.insert( vtype("december", static_cast<unsigned short>(12)) );
        }
#else  //c+11 and beyond
        static std::map<std::string, unsigned short> month_map =
          { { "jan", 1 },  { "january", 1 },
            { "feb", 2 },  { "february", 2 },
            { "mar", 3 },  { "march", 3 },
            { "apr", 4 },  { "april", 4 },
            { "may", 5 },
            { "jun", 6 },  { "june", 6 },
            { "jul", 7 },  { "july", 7 },
            { "aug", 8 },  { "august", 8 },
            { "sep", 9 },  { "september", 9 },
            { "oct", 10 }, { "october", 10 },
            { "nov", 11 }, { "november", 11 },
            { "dec", 12 }, { "december", 12 }
          };
#endif
        std::map<std::string, unsigned short>::const_iterator mitr = month_map.find( str );
        if ( mitr !=  month_map.end() ) {
          return mitr->second;
        }
      }
      return 13; // intentionally out of range - name not found
    }
 

    //! Generic function to parse a delimited date (eg: 2002-02-10)
    /*! Accepted formats are: "2003-02-10" or " 2003-Feb-10" or
     * "2003-Feburary-10"
     * The order in which the Month, Day, & Year appear in the argument
     * string can be accomodated by passing in the appropriate ymd_order_spec
     */
    template<class date_type>
    date_type
    parse_date(const std::string& s, int order_spec = ymd_order_iso) {
      std::string spec_str;
      if(order_spec == ymd_order_iso) {
        spec_str = "ymd";
      }
      else if(order_spec == ymd_order_dmy) {
        spec_str = "dmy";
      }
      else { // (order_spec == ymd_order_us)
        spec_str = "mdy";
      }

      typedef typename date_type::month_type month_type;
      unsigned pos = 0;
      unsigned short year(0), month(0), day(0);
      typedef typename std::basic_string<char>::traits_type traits_type;
      typedef boost::char_separator<char, traits_type> char_separator_type;
      typedef boost::tokenizer<char_separator_type,
                               std::basic_string<char>::const_iterator,
                               std::basic_string<char> > tokenizer;
      typedef boost::tokenizer<char_separator_type,
                               std::basic_string<char>::const_iterator,
                               std::basic_string<char> >::iterator tokenizer_iterator;
      // may need more delimiters, these work for the regression tests
      const char sep_char[] = {',','-','.',' ','/','\0'};
      char_separator_type sep(sep_char);
      tokenizer tok(s,sep);
      for(tokenizer_iterator beg=tok.begin();
          beg!=tok.end() && pos < spec_str.size();
          ++beg, ++pos) {
        switch(spec_str.at(pos)) {
          case 'y':
          {
            year = boost::lexical_cast<unsigned short>(*beg);
            break;
          }
          case 'm':
          {
            month = month_str_to_ushort<month_type>(*beg);
            break;
          }
          case 'd':
          {
            day = boost::lexical_cast<unsigned short>(*beg);
            break;
          }
          default: break;
        } //switch
      }
      return date_type(year, month, day);
    }

    //! Generic function to parse undelimited date (eg: 20020201)
    template<class date_type>
    date_type
    parse_undelimited_date(const std::string& s) {
      int offsets[] = {4,2,2};
      int pos = 0;
      //typename date_type::ymd_type ymd((year_type::min)(),1,1);
      unsigned short y = 0, m = 0, d = 0;

      /* The two bool arguments state that parsing will not wrap
       * (only the first 8 characters will be parsed) and partial
       * strings will not be parsed.
       * Ex:
       * "2005121" will parse 2005 & 12, but not the "1" */
      boost::offset_separator osf(offsets, offsets+3, false, false);

      typedef typename boost::tokenizer<boost::offset_separator,
                                        std::basic_string<char>::const_iterator,
                                        std::basic_string<char> > tokenizer_type;
      tokenizer_type tok(s, osf);
      for(typename tokenizer_type::iterator ti=tok.begin(); ti!=tok.end();++ti) {
        unsigned short i = boost::lexical_cast<unsigned short>(*ti);
        switch(pos) {
        case 0: y = i; break;
        case 1: m = i; break;
        case 2: d = i; break;
        default:       break;
        }
        pos++;
      }
      return date_type(y,m,d);
    }

    //! Helper function for 'date gregorian::from_stream()'
    /*! Creates a string from the iterators that reference the
     * begining & end of a char[] or string. All elements are
     * used in output string */
    template<class date_type, class iterator_type>
    inline
    date_type
    from_stream_type(iterator_type& beg,
                     iterator_type const& end,
                     char)
    {
      std::ostringstream ss;
      while(beg != end) {
        ss << *beg++;
      }
      return parse_date<date_type>(ss.str());
    }

    //! Helper function for 'date gregorian::from_stream()'
    /*! Returns the first string found in the stream referenced by the
     * begining & end iterators */
    template<class date_type, class iterator_type>
    inline
    date_type
    from_stream_type(iterator_type& beg,
                     iterator_type const& /* end */,
                     std::string const&)
    {
      return parse_date<date_type>(*beg);
    }

    /* I believe the wchar stuff would be best elsewhere, perhaps in
     * parse_date<>()? In the mean time this gets us started... */
    //! Helper function for 'date gregorian::from_stream()'
    /*! Creates a string from the iterators that reference the
     * begining & end of a wstring. All elements are
     * used in output string */
    template<class date_type, class iterator_type>
    inline
    date_type from_stream_type(iterator_type& beg,
                               iterator_type const& end,
                               wchar_t)
    {
      std::ostringstream ss;
#if !defined(BOOST_DATE_TIME_NO_LOCALE)
      std::locale loc;
      std::ctype<wchar_t> const& fac = std::use_facet<std::ctype<wchar_t> >(loc);
      while(beg != end) {
        ss << fac.narrow(*beg++, 'X'); // 'X' will cause exception to be thrown
      }
#else
      while(beg != end) {
        char c = 'X'; // 'X' will cause exception to be thrown
        const wchar_t wc = *beg++;
        if (wc >= 0 && wc <= 127)
          c = static_cast< char >(wc);
        ss << c;
      }
#endif
      return parse_date<date_type>(ss.str());
    }
#ifndef BOOST_NO_STD_WSTRING
    //! Helper function for 'date gregorian::from_stream()'
    /*! Creates a string from the first wstring found in the stream
     * referenced by the begining & end iterators */
    template<class date_type, class iterator_type>
    inline
    date_type
    from_stream_type(iterator_type& beg,
                     iterator_type const& /* end */,
                     std::wstring const&) {
      std::wstring ws = *beg;
      std::ostringstream ss;
      std::wstring::iterator wsb = ws.begin(), wse = ws.end();
#if !defined(BOOST_DATE_TIME_NO_LOCALE)
      std::locale loc;
      std::ctype<wchar_t> const& fac = std::use_facet<std::ctype<wchar_t> >(loc);
      while(wsb != wse) {
        ss << fac.narrow(*wsb++, 'X'); // 'X' will cause exception to be thrown
      }
#else
      while(wsb != wse) {
        char c = 'X'; // 'X' will cause exception to be thrown
        const wchar_t wc = *wsb++;
        if (wc >= 0 && wc <= 127)
          c = static_cast< char >(wc);
        ss << c;
      }
#endif
      return parse_date<date_type>(ss.str());
    }
#endif // BOOST_NO_STD_WSTRING
#if (defined(BOOST_MSVC) && (_MSC_VER < 1300))
    // This function cannot be compiled with MSVC 6.0 due to internal compiler shorcomings
#else
    //! function called by wrapper functions: date_period_from_(w)string()
    template<class date_type, class charT>
    period<date_type, typename date_type::duration_type>
    from_simple_string_type(const std::basic_string<charT>& s){
      typedef typename std::basic_string<charT>::traits_type traits_type;
      typedef typename boost::char_separator<charT, traits_type> char_separator;
      typedef typename boost::tokenizer<char_separator,
                                        typename std::basic_string<charT>::const_iterator,
                                        std::basic_string<charT> > tokenizer;
      const charT sep_list[4] = {'[','/',']','\0'};
      char_separator sep(sep_list);
      tokenizer tokens(s, sep);
      typename tokenizer::iterator tok_it = tokens.begin();
      std::basic_string<charT> date_string = *tok_it;
      // get 2 string iterators and generate a date from them
      typename std::basic_string<charT>::iterator date_string_start = date_string.begin(),
                                                  date_string_end = date_string.end();
      typedef typename std::iterator_traits<typename std::basic_string<charT>::iterator>::value_type value_type;
      date_type d1 = from_stream_type<date_type>(date_string_start, date_string_end, value_type());
      date_string = *(++tok_it); // next token
      date_string_start = date_string.begin(), date_string_end = date_string.end();
      date_type d2 = from_stream_type<date_type>(date_string_start, date_string_end, value_type());
      return period<date_type, typename date_type::duration_type>(d1, d2);
    }
#endif

} } //namespace date_time




#endif


/* date_parsing.hpp
RGyzk6XMA+bJuOQJVDLUnXLkQhSqjvLr16vDXf7trAMKgafovUA7rWNYxFm6U5b6RSSa4+Bd64GLuC6Xi+qhar4u/6Ur9ZnnnwcM+545c2NzA5w1kbMGt8zTuaLh7fm9Aa9wVnz+Zh/8faR90g13NcW+6ZSo8hcvkeXjsYfRn4tbpZuvl6Ub5wcFgNDayPrfnROnfdWHuSiXOqcsvv66Kqq+G+5sSn8Niyo/tLIJ/fXD7yL6643qpvXXkwBg9388O87+uhpFtf/jQHz9dVJUfefd0ZT+Sokq33xxE/pr2/0R/fXAEw3x2sNdzmWlHcQZcdnfnRBZ39C46hNHtXQuaxj7vlm78E18PxyuqhXfEIiG7QfxOs1F+wRrMn1CFEcNHipTZ8fTekGsj9LMHAqHemMPSgdjHzicGXuVHkrmHO5Q1ZG1h3KQi0H/7jP6N9fpEGb8P9kf5v6KU/9fQPrwXgkJSkEOYWaITLk46E/b+8nR3ZYaKy7UsYoicYxAEjJxp6ayeaJCEYf+dGeR99YsOoQIDtYjTsL9hUGZQGd0kNJsb8nZMua4Q/eFUjjQkkx4u0IrBJps1om+/k2DQ8b82XNPg931e+OnrIBfT44sm8GybOmjtrmCEEqn2dJVT48zBgjxe7JIpkmx4lAnBQ9gL0adnhgtZXXhW8RPyzvXZTqCS/4ol1A88ri/3S0gsS8Stgg/ue9Ah8WkSKPQpVrQXsJHk0I+B0QeWSyfMmXKTjxHrXOI829/sUy8Ik4fc94qBDsDmlXKZ4kVdNmrhREAJAwNMD7eBS0l0BJL+C/Bf9aPwdvt5L0VteyzZf5nOH8m5wcpYNUqtMosE3ohambkiGFnqyIUn199roP9RpK2HRbm1gvtUkFQjwmRBZXVXyZaK17JcESBRgoM/woD0Z3oIkufO/1anvcLsBNvW1+bDiL/Xa2JWEnw8xrZHH1oLA2+uhRxEeqz6Q72G/RnXCf+AdeJf9TXidlLBZ89Tx5jtJZBjtAyyOEJdR/F4nZwDjwly7gNDn2EwX+GWfTU4O4fwtppUW+uvLmo/EF75Q9WoXJyYHndjzQGBpX23WXQ+z9MjWs/bXFXxH768Z8Ovp9ysd13KnqyjR+UfC1+Wq54lOjJkAfioyflgFTFkAw9kKIw/dFvofz1Wx6VokVxSrcfklja7jA6vHxa6/gv/2DGJ9bf7jTU5nNWUvX6hQuSpRvq4XpeDBfzYjiLKAYkiHkx3Lus0Ikjp4xne5ry6cqaR0zp5Jk7M0DcBskzYom+PAm39/UZ6FCPFUtYwp9Y/wNOmNInzHgbpJYHhvRNbwGp0AbpUUBazZDa2yBt2iEgZQKMX4MJ5tHYU8lkJc4PhC6AHsfDZtFKLnoiJexCgi58GSc0x0i5HNIAxDpblkIjC98mh1rTv5b1KwydELGKvQuXSm/ek3gxJT6MxfQGFtPbejGdA86enwYNkrX4UpXfrONU1VL3fCSF2Z78M4/RcXmAssas8rel9EKpjgUdGp39emQ/BSaQ1fNLP07PhVAXEGT40sliguUZKhuXMtan/onVGWxYr10s1DofJoaX504zJ2vC/E8+wjD9X/zWoE8tSuM730z5beT5ZN7yJpxP+v828vz7YDznBVH2i9tYKPDhivjoWbE4/6GQ2q9G/jl6v+q9KMZ+1Z3nS4+H9H71juX/ZWEc+9UttIIi96t/UNyB9quy76z9Kosrv/sPqPxv9sq/X/Aj71cxVYcWgQor30OBFObVIA8cGUybE6O7OjDGV/9BL68tGuNRAuP6JBh7b8mQqhwCAl0O89r2UzlmKEHRkon95dBWH59ppKMyj1QL2snX7x1JsmD3oeZhEXhvoJQ=
*/