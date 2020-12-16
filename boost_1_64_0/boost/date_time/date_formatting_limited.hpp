#ifndef DATE_TIME_DATE_FORMATTING_LIMITED_HPP___
#define DATE_TIME_DATE_FORMATTING_LIMITED_HPP___

/* Copyright (c) 2002-2004 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/date_time/iso_format.hpp"
#include "boost/date_time/compiler_config.hpp"
#include <string>
#include <sstream>
#include <iomanip>


namespace boost {
namespace date_time {

  //! Formats a month as as string into an ostream
  template<class month_type, class format_type>
  class month_formatter
  {
  public:
    //! Formats a month as as string into an ostream
    /*! This function demands that month_type provide
     *  functions for converting to short and long strings
     *  if that capability is used.
     */
    static std::ostream& format_month(const month_type& month,
                                      std::ostream& os)
    {
      switch (format_type::month_format()) 
      {
        case month_as_short_string: 
        { 
          os << month.as_short_string(); 
          break;
        }
        case month_as_long_string: 
        { 
          os << month.as_long_string(); 
          break;
        }
        case month_as_integer: 
        { 
          os << std::setw(2) << std::setfill('0') << month.as_number();
          break;
        }
     
      }
      return os;
    } // format_month
  };


  //! Convert ymd to a standard string formatting policies
  template<class ymd_type, class format_type>
  class ymd_formatter
  {
  public:
    //! Convert ymd to a standard string formatting policies
    /*! This is standard code for handling date formatting with
     *  year-month-day based date information.  This function 
     *  uses the format_type to control whether the string will
     *  contain separator characters, and if so what the character
     *  will be.  In addtion, it can format the month as either
     *  an integer or a string as controled by the formatting 
     *  policy
     */ 
    static std::string ymd_to_string(ymd_type ymd)
    {
      typedef typename ymd_type::month_type month_type;
      std::ostringstream ss;
      ss << ymd.year;
      if (format_type::has_date_sep_chars()) {
        ss << format_type::month_sep_char();
      }
      //this name is a bit ugly, oh well....
      month_formatter<month_type,format_type>::format_month(ymd.month, ss);
      if (format_type::has_date_sep_chars()) {
        ss << format_type::day_sep_char();
      }
      ss  << std::setw(2) << std::setfill('0') 
          << ymd.day;
      return ss.str();
    }
  };


  //! Convert a date to string using format policies
  template<class date_type, class format_type>
  class date_formatter
  {
  public:
    //! Convert to a date to standard string using format policies
    static std::string date_to_string(date_type d)
    {
      typedef typename date_type::ymd_type ymd_type;
      if (d.is_not_a_date()) {
        return format_type::not_a_date();
      }
      if (d.is_neg_infinity()) {
        return format_type::neg_infinity();
      }
      if (d.is_pos_infinity()) {
        return format_type::pos_infinity();
      }
      ymd_type ymd = d.year_month_day();
      return ymd_formatter<ymd_type, format_type>::ymd_to_string(ymd);
    }    
  };


} } //namespace date_time


#endif


/* date_formatting_limited.hpp
q7ZZfDk76bB8mtNsQNGPKVlRZF4Z2w0W9rLt7TKaK2T9BZq3xtU/D/V3CDClkSO7UnaFY/jY7HGOoIBwDUNoygeEbXYIpwLC+Q6zoqbHccKDdRz+SOWxoj0Os9xrN09AS7dD60rQlI1fC8yYAKVW3pYjjXq7l7NDQauj7lsY5oD8JOzy2EDC8DmpziuGkZBp0vR+pvZyWly2/nYBxf3G4HxDuc/8+JDWGNsOD0U5v+Vy1g1OgvskKid6jmoc7hYo1KAi1Rfsc7jkH329FzsWorPcz1Crk0H91wCTIlGPcnfAMHKz2A3gf+LgzP/o0/Z4eOthbCl21RB1Wgojo31ANBlqKDfJH/M0Q63QTXLOQcRQ/a3jzxmFgo1KRS/6YDx3xpt7JOmMIxhuSMC91Q63O+BudsQNsOMSBlgB6DAGNEIAescO6On+BOgSAoTux70GB0nVLVVljYfzvtjfBwo3vtu/3Js4ABcz/O0DkxBgJuD3I/jarL8KXbTKWpjcXqrkbvTzHLETNCTJvWpnZYgoyMzFSuGpNc7F6JwC5/Vl3DnHAecdzP+TDrZ1znJGua9AOd2O8sP9qHPOVi1dIQY5k9BkR2vvoUDs0LxW3UMnMugnByQBPaVf8h4KGAs8/+M91Hr+Z5Q6sPPjIpzJGUTK8pFZFNHYDaO++zAKpchhiBTa7EOkjVS3PhQU+bybttDvQWFpCBtAavROHJ6lx349+x9HWnYzNwCQoPpbxySam40UClywDW2vsJVfWX91Bwa+3qLhm9K5O3cOLtn5GJo6SVMcyLOFFFJIoS3ERyE+W0gxhRTbQvwU4reFBCgkYAuppJBKa8gKvkd6OX5s4Y0cjh8bhCqCUGULqaaQaltILYXU2kLqKKTOBn8Jw18SX+5yDl8eH76Kw1fFh6/h8DXx4Xdx+F3x4Q9y+IPx4Ts4fEd8+DYO3/Y9WCfEmYbuOUQwtODin3YhLE0uDnqZg/0evnnTCeURAtiFRfQ5aYs8QWQutB8nCB4khmplS68EoMLI7V/sjaE/IpJE2O98rCyp6+OhXCuY18S4u1VFGjKEYFstbQNmmg6P+SbA7S57BaSdwvRi0We7WA5YILjLcHVVHD7VaYEWDNIczHVL5pEr8s0ne2PCJddUMQ48daAqGCAUuclAezsFIDSQHdlCU8A4wpec8U6nHzmhVekEsV6uR8SJ4QwRRKYM13TelCGlx3r/W6HFi0FwKmsWgb6T0D++rPEQPqc5OjffEHFAVBgkljUO56g+lqjcyAUiagRH7emjjnFMOTI1S9f4856DGD00AaZNwaz1GJlL0RbUAP76nmrDfcElI6g0V3M0Tw3aw+VpdZYbuj09kmaPbE/HA3UyeVBQiGeFS/CuroPwiAriDCdCs2WPy+bQY10cnCuDc2Wwh4K5f/bgnoNgGh2pPBFRKCMKVQThQGq+bzv0MC1fHWqlJWbdR0bAuQEh1e139BY5Od3u8yqhTyfSxz6zzucSyhojBrd/LzpA+wZiHvpsb8IB2jsowpxfPdaplp29OOXRVo80AR5V1vg5A76NAPOIcCUAs0F+Wa4AwRdNOqPjeZBArt2c63yZqzIy2ZIrW+XKRq4M8RXNolj0cjIn7tzRlZSepPM/T0WbOpH+LqRP4byEzpSbMK+pCS0F/td5bHN6rm0+z4ufyAvjZ3Bf/NRdTAGdvXynQ/z8NvwCVvwClZs6Dy/PBq/QBs9nVtYmifls8lExZKNU69gGFnoxYI3yZ2/qcD4VnfO1wcp/wruG9p/gSeI/4f6/7+3Qf4I2e1gyeL/ay6Xqf8Be9bcHfbfz5DxdOgjStQxJn7zxhZeJlRsvhMeffbD2FoMJZzJ9Rq4=
*/