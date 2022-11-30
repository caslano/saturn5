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
          { { "jan", static_cast<unsigned short>(1) },  { "january",   static_cast<unsigned short>(1) },
            { "feb", static_cast<unsigned short>(2) },  { "february",  static_cast<unsigned short>(2) },
            { "mar", static_cast<unsigned short>(3) },  { "march",     static_cast<unsigned short>(3) },
            { "apr", static_cast<unsigned short>(4) },  { "april",     static_cast<unsigned short>(4) },
            { "may", static_cast<unsigned short>(5) },
            { "jun", static_cast<unsigned short>(6) },  { "june",      static_cast<unsigned short>(6) },
            { "jul", static_cast<unsigned short>(7) },  { "july",      static_cast<unsigned short>(7) },
            { "aug", static_cast<unsigned short>(8) },  { "august",    static_cast<unsigned short>(8) },
            { "sep", static_cast<unsigned short>(9) },  { "september", static_cast<unsigned short>(9) },
            { "oct", static_cast<unsigned short>(10) }, { "october",   static_cast<unsigned short>(10)},
            { "nov", static_cast<unsigned short>(11) }, { "november",  static_cast<unsigned short>(11)},
            { "dec", static_cast<unsigned short>(12) }, { "december",  static_cast<unsigned short>(12)}
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
W+1+f8Qyw0phvyhCBOPtMwCZSeNqz7xQ1pUbrbiCRjGzNrIVoniuNr/X2pq6559d3Hp0iRY4kS4W4EA6z1eF4IbAYT4/mStpnsqgUdtOybaHCc02vM24J3nafElla+hg1ZK3vlyebiE+076ujWM7PVH5VzwdLOeZ5HWdiiVJD/MrCxT2GC29kMgth7928XlR9y645IBngbuBoGhL5iFMe7HQBV4ygQfgIddyhqnW3J08OTQzZx/hzerncfpYN/9AuUu22VyHNfrA/eIFFZResfWtCJ3FaIk+EYfdpfurFDa74xBcINRvTgVyxlkvf9s5Rengu9vldHSFAqSjxG3n4pHA3X4mZWB9yj00TWFBD6dymnjGbLZayp5DO27KczhtwEPSOyWpkLjLxZT9BLCgbuqb7b526tzl25o7JP7EDS4AChzjWGHOLvXwoZD9fPbADGfkytBSmEOLOXpXUzl5VqyqW7s+qqQra/kw+WuBR1vWm/ehTWOIzf9PaWciRVG6h7dWPJ2ihdo4EiASLeN6+oap7PsQVk1eiS+ERHWUCAQUvk0YRBZE9aqmkWM/mUTUkeAATuZtYFmv8xiv2D0pf3l9Y5I+Qb0Pa/IeYCGKcV8VQbsGCAyLx7Bsw/A/cMegbdoa3LMB/1Izqr3qGBtbc8XONA4R+4bRO222nMSRUO4guZfNMaDY4oBKCAV4Khkt7qWC/MTJIyluN31WODKjbNaInLkYF9ig1STtlYCk+s/zcY6bwA2T5Pxjd9tEJLOafn/Th1zjvuZ1sey2PIvROmWPivAMz9CmmfZT2QnX9UyWZD2s8fP6ximiTFPyX/lQjAYt3chskBnDAgyWdFszS/s7s8hl0Srs7aTNOVntQjepx9nRC4Y5FzoEwZ/jQoYAuC3/U5nv4YI5DhqhObIOCzTSNppkBjcPy0VXLyKwotf5p1xWU/NH0Yvy6VyqdeDvbr713vTBq1NjvWxInthVZFz4hpOAg9U9GnG8NVhgx8eN+qDOkVbaELKgUsWfwcVoSyXGJORuGFk0JrCgFgI6QJbAoafjFUnlxt+Vvc1nvWWhsrs9J+Cy4VzWVMUGpJj23EYwObFcvfcZ8h4rC4Y51GbqaYJbQVtMdmUOoctnK41IfKKaUIzVXIq36esmD87L0AxEu8z6HliyO6EGHrNtaNUu6Bk2HG0EGXVGEV6hSaSVtCDa+vD7DM2FWG5LitJWdpc9iywmB5wYTyIns4NoSrkzS2M2WE1a2SGKBngpKEfiEsWld6Cs9hY7Zxf1+MDCxWmLm4okj77U5o14pMk705YZCRkanGgof5DF/lKT26fjapOT1V9KCqjn+CRWEoVEboDHw3T/dwuVszZxCxXgJOGO0HIkLro3IPSESRmVPILIVnNk9VvHQCynvmmf2oAP0keO4CaLU+tqFfqq0o60LyWdaXeqyeMW4ViC4soCps8Hx5PKivPh4+Xakp2UGBXh57mSbo0+Mj0SiZMCzOyXHJJaL6dyqfM5nE8QbCBvKHgrsQr0aiT39XS0xl0fJ9AKZbQeCSNVrUuzwO6G/lpK+kJzA28U+8zyAopCHiEmuhTJeMZTKSLoh4owmJQzW2wSQ9zLjm8VaasJfA0wX5cSfRrUdh2pWeioZ/wzHQ7nOugAHzhGB5FqKAAaZrpcfZihdmtJwiO4xje9TNqL810r9cRsdE0oqX+62neXMVUfu3MVC8CTCNRtSSlXCc+o0+h65d0zTizwBaFewGYggzLXZI7NQ6EVv8kUfpgcsYxlj+6zbI2gMbNjS815pB+/hX4nmkjGMsiczcRKdAmyQJjw78JiCKjiKexwM6xwaLAsE8ndB61BHU4P4qPx0CnekmyQR0IQYZYHg+3EWQwX28Fj9XkNgeX49/46Uq2yJTLovkLCH51X2qdFw4Qi3OE561a/rOEA95gEAhoqPK+4Yr3HYRrereYSvXmvSpzy4ZNA+a8X3QTrVlPWlicEZXhNNokYgV0Oo2nLyBwjw7kNNuCy5Y6D4CPd4uilXlcO5kJQV5WgSGASumHd3JqSAhNjJh4QqrPSdGPhKhiEmm4y11OJs2PfSqinM/S+DKLHGRXGTY9kLRxN5eHZo7CMiqFFejGHrhVFS6CJGw/UhyRdR8QDEtDx+xM8TrLHaTZbCcMaWLiemGdxKONlXgabDdnTbFZfuZlM0l6KXC61PB0hQiP7NSHCeUKpKFJxkRZIHRFWXJ/31CVPdULx2GKzJpVIa9orH8s6+irfsqUinySrVo8hwoZcMnlR0FvCdIQ4dNJzs+PNvl9tIbuV+Rqxo5FQ2cJVVbgHP4UxD/u1kiGwYqgR3udrQ5RA6noS9BCqRrK6AqYn0YQKoA4tZW3jcn65ZSYbpscts5KrNGl1j50gRdReoO+O/zjBtu+QYWdpIMcsB8/UX+fK7fE1LMkJzdvJtHLjx5K0/9Nx7AbCEDsWGFTrBoz2mcZYrLswVDp5z+IR2OI/nFaOFDF0Q6clW4TnTAkVqX8EHDFm3kG4zEAl5xozweTqFlwz7vfOnOIyGD9zwaZElBofElTrKO9lqsBwvVDgTOkD8p+QlrY02z7CALNSLWIGetEiyHu61mRAVNlGY3GAPxwRPJeeth6NGwxliJFzbs/0AwbSSxr1/bXgBaBicRzAEAIOTJrbcRj21MJ3XyQmhbDIy7UnUyKzjToh1Qg58ImgzqLIpM3eTOQSaQ9HKXizbGRjT4Ei2cXX84deQWLbE/h2h4QcU1IeyyHnZftQz1b8qcCNqQyfsEFi+UkB0oIx0rYsk0YIpgR7hFBULB5x1a1s+3c+Dumh9IIOqFN7P1TAc0S1lys2f58lLxZGyPvgt0P2D4dJfZfJ6I2c731Wwxqc+NusK9Fv2Y4P7ThABPqSoUV0ZaqihW9XScjys+SXiMSNiSn+Rj8MoY9xp37Y6WZOJsEMUp4AIug1DgqDyafRPk00l8+Y+kQaaXiyvCAZZUv/fQBawtkOzDCkvsHyRgwSwDwQ1ZQXq+ddKc/ze4vv/I7rl+PrRu/35IjvHG9lbMzvJ/X363vvUfP6yO+xb39ZWMFe694BLnebyfqTsRd+8eCvpNRWj0YQFnmF22yIotZLYj30Mb9LLCuaohZC7onN0cIjxYT51+kLF0J+Q042RcBUMlA3O+aTPqXCyuF9XGfbJ2JWlXtss9n5z6QGMzF5jKSaDcjZESaEsfKLHMk5dkZn/4g3Kl3J1xFUC0OkU/NDH8TJnf48y495xnfhVxvbItjZTZRTWV7ySwv9+uJudj928GzWqQkMCGU3Hd2iPcmN3vxOHCxaMQzmnUpvvGecmAEk3GJKpfhNdbY2gp7vMGhnZnj7ZOLlpEytR1xQLaFZMSwXzmXchm1mRh4T//zAibMOU80RLokLDmfb0u6HsYo7k/hdzY4mgZG0b0LWlQ3a5pqR3ivGHA3xJP1xPBtWITfGK7fgn/EyXwz2Bm6+3530BqgAFoICmkO2llGAGeJ41EM4k0f7htun6BxnCtFCfNybYOMR4wuhqXGmR9IPpsF0CGGejNbAYjZ1Sk8benf2tBM7RvBF24ab59GBfhoebImsBoOYXUnzsG3QSsW8psHqXLrUFQSueOy5SuwbiFbpUmZOFo51xw/n29Q0N6Mgca/MTy3JhTAG/ZW1xqpvytNF78bLardL31tTz3pCMVfTqp2uYF1Uqu7iaFZ63NJMrE5ed+r0MiwOt4NxGKHNIuLJDhr7nUN1Gx5ZFb0kqhgvkJyMnijNoDXkz40fiNKEgc2PAC3D0lQdyYtlxYViaCUQVObdEcJHnJdQ/DMGJ5wBZKzPLnxST2AfNM6PVKLOl9RNjudDMPFRaGHywdWc5Lyj7W+lv+yQ3isxAGqg9wEb53zO+ZcTnRlTMKri4w5Vo2L2+vDvCVvN4pL46zcdYAKgB8MaweMS2pJmXdnDZgX+JzB1Fu98dQTAC/OeOv0Rnhg/BppEMp3eOfI2ImYoCOCEQKbRP5JRR8GJ+BS/IJHYhV84GO9Gyi7S/3uWyWcqsXg09YZshS3bSo3RaidVejVjtcJQlBgeX9cBu1x+ZG6VuJdAjKG993WLqMorHsOLBgwMeyzv88B5+vbwFT9wArE4+KN74XC/Ble2tyJTgSigAUOa13PcHNWELYQZJdK/Ln5sY5ngk00YoebYlmBoWHjvxrjOMnFavEZs0lDx5oV6lH03yn4Zoo1m70sYGLanLIJUyXuhQqBqZ49tBdezsJsnz11BRXhjisiDA8eXtuiw2YRqPxXLALUrVXuuWzjYxyK/pFaOEKb7vM5x2lpEmaQy2xqCePtk9/jucRqKZDABGIfmrULiwGNpKYj0mue+0PgcE5LXGRYpVaA0Do/8ASm7r8VzpYbvlXzMqh6ly+Rmb/+Ydhm5mIy4bsGnisL+oXlUNrScO2YiJyruK8NEzEAuTDRvI7/cAzKMHnV5TUhcSMhW8CYx+QX+arB+w1NQlKhbo/zf+bdOzBQm7xS3oyQN2w81Y1bVuAhJR4q2nxbSM2h5rhXcyLmKsJsk7LhRDoBg1/EpNfWbucQLENDQXzYsdFV/DqfNDKE00GMqssFObNOWHIzr3fnMoEERl24dhl3f0kSbr7+w6yZrXPxQORmYfFDUA72LKqM4SQjVBaWi4bsWr65o4boZAMZ1XUcIDViK3m/e1DET3sNBew8c2Zq6awrI50FMX3LeAAQs+9PzgUU892zLgGw43yX8AmNgqa/Uv8N6fs+tLjIL/L4fFtq8wlGCs/IXUKz2qjsXzjiNhB+5jkJvpIYs85H2ZcNTVaEDKxSjYRZIS0SEvPlgSoUqjbN5MjQoZgtqzz+UIiN6/cwQyxXC0gqRGZNN0iBlmETyd6WLlbYq8oEAAq1oPMO6m4ta7moPPcHUZ5T2hNhfOS5aSHr0pwkvgN1pjsu2VW1nu+Mow7oabmx6QpMik+rJKAQKblqnGqFzTZfxJXhSlsH7DDWMUCrSoFK3/ZFogU5kptFIz/9+qAKi9ReJ0xTtW17MVrzR4bmzmqMcDUEldL+5M2SPTQ0CZA9iidOabfgGnSiAaDkVIXIQbXPvKQaBeudpE3KH/kbtDxmFgv+kgKiCTvXCBcJtRjHqMah/NN5PVQo8io8MN1Qekb4J0iSDfhSdbeFBmyu1neAznevJgs2rE+vBF/SApkY8M8+Cd8rnuS9XChFpWGiwniqc8ojT9BhHKppJ9QbfF5oPKTUuebMx/VYCDJzEYVV/SxfZiEA0wrIMdKGKIUhd6oE8MRiLdJlKA/owcYpiqDNlIR0m8CkEmvBuqKL9gaFDr8nEPxNwFnPzni3NfKWWyl2l1X4ED/Ole62Hl2vJKgIXeiIJg2uCQhqUHsVwc2kMYR5UV0k8BMRd6hx+fqhXIeaPbiod1dPa19X9ZnUeRITIa/BfD3JlZtpjfw1R8yRg8/OTaA4R58WRMDUm/tCS9vyd2JMirMnRMcWBeDnk0aZ8qYKetalokfV9JLQx0pTFVDakbeAP7rateT2LOJDuVPVshmtbbNRlkdskFlEXk5WobCV35NiTsd5810PobseWJIheWdZLKbmpNBZpPO5Gg3EN7VDWuRwMpHQea7F+XN56BdizfAsB6LB7Z5ONTVpxEL7mINjOUTmfUTO1cHLrgDGoBqI8gf1WDpuwr78no18Z4ygeyJSHdAoSfLKFwoXsUd7Pyl+FOBj1xTD2hSCuDOF0J60sd9PHZDtFNNwRHIMiXfv+yR20ZBE3HLSgr6F8lDCujgL5JZBtIo9YFpe7Zu9X32iA0dBna+qupD1d2N2QU/T+5GgkX83kBkNeCzr08OWbMswDM3fP3PidvSOGQ/qh3mDY6TosiNgxDFflMkkH9aXjKpy8rQmw0BHZ7Va8/gA8mVT8lw9qtIURL9esR6gHEF1GrhjZQ2ekC/mv2dGyecY32QO3ilJvVtrttY+i6wbB62Ryu2RqaGKW096M2Q5C3Fru4/3SdhYkGF+5a63E52xXVQC3Zzavqf1jvkLfkFdtHYDUC2OtPqLR75N9C/Hfj0zyHU4wY/cEO8R+3qs37lZqqf+v9kgwfZBqM2ijveSVi9JYIkZfVMYeFghm6hwq42vjUGS4Qi86EKXsoWabOGmGEFDYEwlASI51an7wKMn6pdhorD+kWztrnek//rB22r2S3cHmXBaToDAKP0vG54ViHKsObnYzPcHVQobqMS2vBDsRbfgdMhveFbIF559DDGfgMJtX4O1KLfImcB8rD9zxw/JV1rpINGdPRdI7I3YozUQWjggk0jkZ1B+eYzI+TSZzrV1W7nveCfikh13WrsHt5Sx49s/uzVKcBlOKRj32uFc1DQOrrCcXnayqGLpNVbUbrXLqyv2MVjbbss3anOfV2XqK+JOXV22oicsK3nJS0u3djpcYUEDK1nmX+jg6pqFEK0jWwlEdMddw2Qywk7AsrMBCHzM6V4L9bqGGNHJME7hupAb+h1+zjLLCSarWZXokhX+VjXdyxu0l9xqm6uyA/xn9FDPuE8TvMlZ4hRKGiJWhT39GLY2gV/HsbdZv7b1657/S2tR9eDgmxb47txemKVUHlivgzbUyGddRLgO17SL7HCYZI79SosdRILE9dNzMYHGYQnlh2v8YWdFAmn/W/ooDj+XBchfOjNUgS3GkdDrkzvez0jmb5gJwtc451+b2Thha43LK62/PvQ+NYi7A3e3u8pItVFp4pHJw0GkwNvt2PsPOsKPTIFM3R9899LDjXBrFzauZ6/sZCAuYFU+dR/1r71+Lq0iqYc53uWy2mTVa1vM9ow5DsvFId9nIajdMRgXu4qgNhu1+h56P397VH7LYRZB0Ifo4CYgfoSFdvypFyXbSJZKcpVgHXKfpe+vZI+TvHMmZI5OlWJtFbM+uSZD/otQvnYkVDHlAqttWnXzf6hyZMrXEXkSVzGZ3/CI9wpvps/iW+Tfrp2Vd3HIimikk0vuxNCrDCmj8WDI2SL2qWIdJc1dDkodU8SPQ2NXhKUQu2UPml93rUiUYaKosDp4j/q8xosBiRT3eIZqQ/hRDZFMCEjN3traTfWjaxN5Gp/AxLBbho9CDpja+0PyJTLrlxutUMOndMtWaQ+tLqf3fICJradE1zw29TGK+VxD1DGWIEIYEJHVTw1rBGTnsGB02g8Stb4K8NgyRY7JLZuw3a3SprqF3pdCLtixej7WIgSacHe5PDjX9wjxvfDZTmFofvnv59oNjRZpgCJTohXL+JiVN1iYqRrgc8FOeSfN1+yT6tpJ8h2Axlo8Vn6zY+RfCzY+yVgMEZBqg07oOOOXSkc3P/beh8EyFU1inBsiHwyhQ3VvqEFywPC2rafSTToa0wSwrL+vvsB//iuzbOaN0xxmxCuuQF23MwNUvnCVD0gBVaAYPC9cB1acA6z3QtUyGGlcqQoC03PpxxD+PtvkWxvVcwnMMuc+ZD2bpndvvR+kMS1FT08fzA0d3iK3TOvutSbT2EH09yCEq8AKsgMNt2/WFLQ1gcnHcoT2QbWrcLIrT1GjECdqGtFEM/UCKMn72Ay9O030aapQ8Rbpamg9pDt9gWkczF0evpEiQCD2XqZgHzw+sWsDekLX3OIumlqEZlDzw6ZobPrPunT0xmk3u138gvdT4A+tR
*/