#ifndef DATE_TIME_SIMPLE_FORMAT_HPP___
#define DATE_TIME_SIMPLE_FORMAT_HPP___

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/date_time/parse_format_base.hpp"

namespace boost {
namespace date_time {

//! Class to provide simple basic formatting rules
template<class charT>
class simple_format {
public:

  //! String used printed is date is invalid
  static const charT* not_a_date()
  {
    return "not-a-date-time";
  }
  //! String used to for positive infinity value
  static const charT* pos_infinity()
  {  
    return "+infinity";
  }
  //! String used to for positive infinity value
  static const charT* neg_infinity()
  {
    return "-infinity";
  }
  //! Describe month format
  static month_format_spec month_format()
  {
    return month_as_short_string;
  }
  static ymd_order_spec date_order()
  {
    return ymd_order_iso; //YYYY-MM-DD
  }
  //! This format uses '-' to separate date elements
  static bool has_date_sep_chars()
  {
    return true;
  }
  //! Char to sep?
  static charT year_sep_char()
  {
    return '-';
  }
  //! char between year-month
  static charT month_sep_char()
  {
    return '-';
  }
  //! Char to separate month-day
  static charT day_sep_char()
  {
    return '-';
  }
  //! char between date-hours
  static charT hour_sep_char()
  {
    return ' ';
  }
  //! char between hour and minute
  static charT minute_sep_char()
  {
    return ':';
  }
  //! char for second
  static charT second_sep_char()
  {
    return ':';
  }

};

#ifndef BOOST_NO_STD_WSTRING

//! Specialization of formmating rules for wchar_t
template<>
class simple_format<wchar_t> {
public:

  //! String used printed is date is invalid
  static const wchar_t* not_a_date()
  {
    return L"not-a-date-time";
  }
  //! String used to for positive infinity value
  static const wchar_t* pos_infinity()
  {   
    return L"+infinity";
  }
  //! String used to for positive infinity value
  static const wchar_t* neg_infinity()
  {
    return L"-infinity";
  }
  //! Describe month format
  static month_format_spec month_format()
  {
    return month_as_short_string;
  }
  static ymd_order_spec date_order()
  {
    return ymd_order_iso; //YYYY-MM-DD
  }
  //! This format uses '-' to separate date elements
  static bool has_date_sep_chars()
  {
    return true;
  }
  //! Char to sep?
  static wchar_t year_sep_char()
  {
    return '-';
  }
  //! char between year-month
  static wchar_t month_sep_char()
  {
    return '-';
  }
  //! Char to separate month-day
  static wchar_t day_sep_char()
  {
    return '-';
  }
  //! char between date-hours
  static wchar_t hour_sep_char()
  {
    return ' ';
  }
  //! char between hour and minute
  static wchar_t minute_sep_char()
  {
    return ':';
  }
  //! char for second
  static wchar_t second_sep_char()
  {
    return ':';
  }

};

#endif // BOOST_NO_STD_WSTRING
} } //namespace date_time




#endif

/* date_format_simple.hpp
94P95nrz5nrz5s2b9/ZlwruCiJFv6+UjnbxwnfJO2c27+K1EqSZCHMblmxvC3nULnMF8F5WZV5cvOQ0NGXcSDJIYOnUvP5bRGyPQW2dHbwChV/8SVVF/O/0n3ZY7udzZXK6rKPeMvdzXP1C5FYmmY3v1oFthwK4jLHbG44fTday7y7pZqlCTuJInOqOSh+2VLEclaUBuvzsSualcbq4oV2MvV4xy+9zaET3OwNubKR0LoKPd4poKFpczyP4C5GN2kIkAucxNqMyIQqWcy33VCeWetZfb/j2Vu9St9B5WI66VvM4psk4tQMXUyZjNINcIkE/YQV4JkC6gEkyIRGUBl5ssym2wlzsW5d5PgLDunwbdy7HTPYlAJQNK7xRjSu/7jgDNI0D5vORkJ0tgsIFO8NX4LmVAr6XFAPQwAOUl6KI+j7I+4Xdb0D7uas2WGxjaEgGt2g7tfED7GPzwTpfVL2Utty7gr1QYmpLRLh3tQLSAfR/DHiBgP2KHnQTYv6MMyujFfJewmoGJvcGj7AsDnr1PgvO+FjpVooIHuYJtHWN0xX37qIIBQL6ti4K5X/IIlegRKlEjVCJH6DGGVhEL2pmAttepeyHBu3CetLri09Owe2/lURzmtyXU9Qw1W0B91A7VCahLnMZwaTfkOoZvW2KMJ8ygWIOScaCp0/YfVMcaK6u77FJpQiahbJIGq2QvgxK07AVaTLpp+z+xJuAWbtHYDmjRU/YWHb6XantC0neHQ82EbVykpyjyJ3uRH76lInfQl0ZrhPCWEhissWNf2upyzYNLIDOpzmMmhYSe0F+5xkfao8bN9hqvpRpD7QUI1Z3cwaFe7BmRzxLt1ZH5Hz3l1Ax2CjawXQFxBRIa5nJUDnc5Zox0Oe6h77YjiI8nj3J30m9JPhV1ulwJ7uTkZGdyYjL+EhMTkxOTkvh3269//yN/sexpdWymZbxFfH8KwYj2IihNC4Xbr75RmA7Pkcao+gixKrMaXSwLKtLB2hBKE94IAoJXmiOcBvyTZ/rWNpjpT2KmP6Zn+uqvMF9Dx/OSJq5P2uqqekUsZ1H+Wy6/WJTPt5cvofL/nu3MuP25FINKv5usLP/sTNH2sXwukxdSVm2Up1Wt8c6aySCC9Hmz9YlHJ07OkEeQ7M6ZmOq9GAqHI6heCdDxBNFNgfZgwMoh7HHg3EdjuYX5BFCB1EBz+dW6bBbYxlJUUmaUqeUyN3KZaRR3xGwj+XFOnkHJKtKv9j9kBkkCTEXaq6SRow7ksoUlkqbJ4lUm1Z7xlcxiTMMUgQb3VVk7+kKnSBt/RfWfupQpMb54T2CPWBzq8n5DWLsq0BLRcgXNuwBUHLI97lY+hxVSXy/gSQ+ZHvxsvfyXBkAthpBM+cNJrB/pUkChJ88yUDzt9/En0EAB1tRpg2F3GdMglMKJ6eBIlWXlKqqSOFVXC1YAD3mAnJT85opGTMSkYIE5TQr3zYjjN/9QSBUnrFx50xFsJ1KquIRwoTVEJNFpCZtDgunHGBGQm+KbFE+l+asrUiQid2Np5+RXb+KtJsXLvln7vNBgYyAS6/tK5qBU8C5AW83ftQdBtTYa1dMkqm6MjUTLI399jKf05l8SvLjt/rA0KNzCQbOffYM6xK+UZJeErlXDHiikL3Sco6wr4vSawFdr9kGUzkcy5FJTG6lCAIybbK73S5wR2SFLrRSmILrt4EzVBywZYY9yy9hqNnUrsTg8zfOr67lD17eUfj2DyzpBweljqYcio0uDMztpXbKlRGDYytqA1sJ+V7Gr6Ve0/9d/Me1fuqyrMC0p8jEJWik9UiWUDdby2EAL7YjjjiohjOjMsiJHy6TDWMKcvcTJRoPGW8oPj8A=
*/