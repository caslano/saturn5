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
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
*/