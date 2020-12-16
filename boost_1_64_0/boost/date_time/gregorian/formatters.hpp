#ifndef GREGORIAN_FORMATTERS_HPP___
#define GREGORIAN_FORMATTERS_HPP___

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/date_time/compiler_config.hpp"
#include "boost/date_time/gregorian/gregorian_types.hpp"
#if defined(BOOST_DATE_TIME_INCLUDE_LIMITED_HEADERS)
#include "boost/date_time/date_formatting_limited.hpp"
#else
#include "boost/date_time/date_formatting.hpp"
#endif
#include "boost/date_time/iso_format.hpp"
#include "boost/date_time/date_format_simple.hpp"

/* NOTE: "to_*_string" code for older compilers, ones that define 
 * BOOST_DATE_TIME_INCLUDE_LIMITED_HEADERS, is located in 
 * formatters_limited.hpp
 */

namespace boost {
namespace gregorian {

  // wrapper function for to_simple_(w)string(date)
  template<class charT>
  inline 
  std::basic_string<charT> to_simple_string_type(const date& d) {
    return date_time::date_formatter<date,date_time::simple_format<charT>,charT>::date_to_string(d);
  }
  //! To YYYY-mmm-DD string where mmm 3 char month name. Example:  2002-Jan-01
  /*!\ingroup date_format
   */
  inline std::string to_simple_string(const date& d) {
    return to_simple_string_type<char>(d);
  }


  // wrapper function for to_simple_(w)string(date_period)
  template<class charT>
  inline std::basic_string<charT> to_simple_string_type(const date_period& d) {
    typedef std::basic_string<charT> string_type;
    charT b = '[', m = '/', e=']';

    string_type d1(date_time::date_formatter<date,date_time::simple_format<charT>,charT>::date_to_string(d.begin()));
    string_type d2(date_time::date_formatter<date,date_time::simple_format<charT>,charT>::date_to_string(d.last()));
    return string_type(b + d1 + m + d2 + e);
  }
  //! Convert date period to simple string. Example: [2002-Jan-01/2002-Jan-02]
  /*!\ingroup date_format
   */
  inline std::string to_simple_string(const date_period& d) {
    return to_simple_string_type<char>(d);
  }

  // wrapper function for to_iso_(w)string(date_period)
  template<class charT>
  inline std::basic_string<charT> to_iso_string_type(const date_period& d) {
    charT sep = '/';
    std::basic_string<charT> s(date_time::date_formatter<date,date_time::iso_format<charT>,charT>::date_to_string(d.begin()));
    return s + sep + date_time::date_formatter<date,date_time::iso_format<charT>,charT>::date_to_string(d.last());
  }
  //! Date period to iso standard format CCYYMMDD/CCYYMMDD. Example: 20021225/20021231
  /*!\ingroup date_format
   */
  inline std::string to_iso_string(const date_period& d) {
    return to_iso_string_type<char>(d);
  }


  // wrapper function for to_iso_extended_(w)string(date)
  template<class charT>
  inline std::basic_string<charT> to_iso_extended_string_type(const date& d) {
    return date_time::date_formatter<date,date_time::iso_extended_format<charT>,charT>::date_to_string(d);
  }
  //! Convert to iso extended format string CCYY-MM-DD. Example 2002-12-31
  /*!\ingroup date_format
   */
  inline std::string to_iso_extended_string(const date& d) {
    return to_iso_extended_string_type<char>(d);
  }

  // wrapper function for to_iso_(w)string(date)
  template<class charT>
  inline std::basic_string<charT> to_iso_string_type(const date& d) {
    return date_time::date_formatter<date,date_time::iso_format<charT>,charT>::date_to_string(d);
  }
  //! Convert to iso standard string YYYYMMDD. Example: 20021231
  /*!\ingroup date_format
   */
  inline std::string to_iso_string(const date& d) {
    return to_iso_string_type<char>(d);
  }

  
  

  // wrapper function for to_sql_(w)string(date)
  template<class charT>
  inline std::basic_string<charT> to_sql_string_type(const date& d) 
  {
    date::ymd_type ymd = d.year_month_day();
    std::basic_ostringstream<charT> ss;
    ss << ymd.year << "-"
       << std::setw(2) << std::setfill(ss.widen('0')) 
       << ymd.month.as_number() //solves problem with gcc 3.1 hanging
       << "-"
       << std::setw(2) << std::setfill(ss.widen('0')) 
       << ymd.day;
    return ss.str();
  }
  inline std::string to_sql_string(const date& d) {
    return to_sql_string_type<char>(d);
  }


#if !defined(BOOST_NO_STD_WSTRING)
  //! Convert date period to simple string. Example: [2002-Jan-01/2002-Jan-02]
  /*!\ingroup date_format
   */
  inline std::wstring to_simple_wstring(const date_period& d) {
    return to_simple_string_type<wchar_t>(d);
  }
  //! To YYYY-mmm-DD string where mmm 3 char month name. Example:  2002-Jan-01
  /*!\ingroup date_format
   */
  inline std::wstring to_simple_wstring(const date& d) {
    return to_simple_string_type<wchar_t>(d);
  }
  //! Date period to iso standard format CCYYMMDD/CCYYMMDD. Example: 20021225/20021231
  /*!\ingroup date_format
   */
  inline std::wstring to_iso_wstring(const date_period& d) {
    return to_iso_string_type<wchar_t>(d);
  }
  //! Convert to iso extended format string CCYY-MM-DD. Example 2002-12-31
  /*!\ingroup date_format
   */
  inline std::wstring to_iso_extended_wstring(const date& d) {
    return to_iso_extended_string_type<wchar_t>(d);
  }
  //! Convert to iso standard string YYYYMMDD. Example: 20021231
  /*!\ingroup date_format
   */
  inline std::wstring to_iso_wstring(const date& d) {
    return to_iso_string_type<wchar_t>(d);
  }
  inline std::wstring to_sql_wstring(const date& d) {
    return to_sql_string_type<wchar_t>(d);
  }
#endif // BOOST_NO_STD_WSTRING

} } //namespace gregorian


#endif


/* formatters.hpp
ZkwckActQzDxxHw8ZJa3P49fz+2c4pa2FMHEH8vD01KWd2WuGRMH5OwlCCbeJRcPmeX9dw6/njs4cpK3GMHEX8jB01KW97lsMyYOyJMWIZh4v2w8ZJa3K1uUicPfRCtaiGDivbLwtJQlb8syY+KAXLYAwcQHj8ZDZsk3GV0/Ewf4GfMRTDx9FJ6WsrwvGGXGxAF50TwEE8/JxENmebsz+TO3ai3Vhl86F8HE80fiaSnL+6qRZkwckNfPQTDxkhF4yCzvW0fwZ27VWqoNv3E2golPGY6npSzv24ebMXFA3v06gonPHYaHzPK+bxh/5iZxitt7sxBMfMFQPC1leccPNWPigPzFawgmvnoIHjLL+9Eh/Hpu4xS3r15FMPG3MvC0lOX9eIYZEwfkX2YimPj2dDxklne3dH49t3OK29EZCCb+ThqelrK8u6eZMXFAPj0dwcT3peIhs7wHpPLruYMjJ2enIZj454PxtJTlPWiwGRMH5NBpCCb+4yA8ZJb3qEGiTNxFboNUhmDiX6fgaSlLfkiKGRMH5MZTEUzcPxAPmSWfN7B+Jg7wkVMQTLxyAJ6WsrzHDDBj4oDcfDKCif/dHw+Z5T25P3/mVq2l2vBRpQgmfq4fnpayvMv6mTFxQL6lBMHEXYjILO/5r/BnbtVaqg0fMwnBxBu9gqelLO9Ffc2YOCC3nYhg4s364iGzvNf24c/cJE5xi5uAYOJX9MHTUpb3+t5mTByQO45HMPHo3njILO+dL/PruY1T3JKKEUz8ppfxtJTlvfslMyYOyF3HIZh4q5fwkFnen/Xi13M7p7gl+xBM/J5eeFrK8v7iRTMmDsj9ixBM3PsiHjLL+1BPfj13cOQkpRDBxB/piaelLO9fepgxcUDOHItg4p174CGzvE92F2XiDcltyBiDYOKPd8fTUpb8b8lmTByQcwsQTLxbMh4yS/7sC/UzcYAvyEcw8e4v4Gkpy/ufbmZMHJBL8xBMfEA3PGSWd1g3/sytWku14afmIpj4oK54WsrybtzVjIkD8rwcBBMf1QUPmeV9eRf+zK1aS7XhF2YjmHj283hayvJu/rwZEwfkNVkIJj7+OTxklveNz/FnbhKnuK0bjWDik57F01KW9y3PmjFxQN4xCsHEZ3XGQ2Z5t+nMr+c2TnHblYlg4nOewdNSlnfbZ8yYOCB/OhLBxN94Gg+Z5d3haX49t3OK2/4RCCa+6ik8LWV5d3zKjIkD8k/DEUx8Syc8ZJb3c5349dzBkZPDwxBMfNuTeFrK8u76pBkTB+QTQxFM/KMn8JBZ3n2fEGXiYeQ2/DoEwcR3P46npSz5no+bMXFAPpOBYOKfJeEhs+RTkupn4gB/Ph3BxL94DE9LWd6pj5kxcUBumI5g4ocexUNmeWc9yp+5VWupNnx4GoKJ/9IRT0tZ3rkdzZg4IF+WimDiJxPxkFneExP5M7dqLdWGv3IwgomffgRPS1nepY+YMXFAvmEQgok7EZFZ3rM78GduEqe43ZyCYOKhHfC0lOU9r70ZEwfk1gMRTLxpezxklvdKL7+e2zjF7d4BCCZ+qRdPS1neax42Y+KA3L4/gol7HsZDZnlXPMSv53ZOcUvsh2Di1z+Ep6Us7x0PmjFxQH72FQQTv/NBPGSW994Efj13cOSkS18EE787AU9LWd6fPmDGxAG5Tx8EE094AA+Z5X2wnSgTb0RuQ4/eCCbeth2elrLkD8SbMXFAHvgygol3iMdDZskfjqufiQP84JcQTLxjHJ6WsryP3G/GxAF5dC8EE3/ufjxklvep+/gzt2ot1YbPeRHBxLveh6elLO8zbc2YOCBP6Ilg4n3b4iGzvBu05c/cqrVUG76kB4KJ978=
*/