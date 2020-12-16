#ifndef DATE_TIME_TIME_CLOCK_HPP___
#define DATE_TIME_TIME_CLOCK_HPP___

/* Copyright (c) 2002,2003,2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

/*! @file time_clock.hpp
  This file contains the interface for clock devices.
*/

#include "boost/date_time/c_time.hpp"
#include "boost/shared_ptr.hpp"

namespace boost {
namespace date_time {


  //! A clock providing time level services based on C time_t capabilities
  /*! This clock provides resolution to the 1 second level
   */
  template<class time_type>
  class second_clock
  {
  public:
    typedef typename time_type::date_type date_type;
    typedef typename time_type::time_duration_type time_duration_type;

    static time_type local_time()
    {
      ::std::time_t t;
      ::std::time(&t);
      ::std::tm curr, *curr_ptr;
      //curr_ptr = ::std::localtime(&t);
      curr_ptr = c_time::localtime(&t, &curr);
      return create_time(curr_ptr);
    }


    //! Get the current day in universal date as a ymd_type
    static time_type universal_time()
    {

      ::std::time_t t;
      ::std::time(&t);
      ::std::tm curr, *curr_ptr;
      //curr_ptr = ::std::gmtime(&t);
      curr_ptr = c_time::gmtime(&t, &curr);
      return create_time(curr_ptr);
    }

    template<class time_zone_type>
    static time_type local_time(boost::shared_ptr<time_zone_type> tz_ptr)
    {
      typedef typename time_type::utc_time_type utc_time_type;
      utc_time_type utc_time = second_clock<utc_time_type>::universal_time();
      return time_type(utc_time, tz_ptr);
    }


  private:
    static time_type create_time(::std::tm* current)
    {
      date_type d(static_cast<unsigned short>(current->tm_year + 1900),
                  static_cast<unsigned short>(current->tm_mon + 1),
                  static_cast<unsigned short>(current->tm_mday));
      time_duration_type td(current->tm_hour,
                            current->tm_min,
                            current->tm_sec);
      return time_type(d,td);
    }

  };


} } //namespace date_time


#endif

/* time_clock.hpp
5yd0Z1XelGUuj8TjKAEn+3FmKZnGTpPgFG1EYhMbOnnAZJ2UGpfDO61wn4gannuoeUyv7R00ULtoHrzLH3P7ZeYTcjfEeXC+2PLgkxl70c4HKgx/IiNwH4ba1xt7u9N9EX2/xS1LKEU/aghxGP7zwIgDjVqb27eRDVZ46wW1eLfmDTEudMmNnnD67Rc+b8CW+FjkzY9LoS68UQh10Iw4jHBYguM6NGavQVt2cjKwrD0ux0G88RzyDPLe6nb0S1aAeb6DPNFbyL/U5iPZmVScPSeMz2NnUi7lTGrE3bx/Y/Ch+dI8PDQ/FQ/NT1OH5gsgTXQ8zoqyB7oXHWaDJDZxCq0mctGr4gS2Frbkj5Jh8KnsY4RJ/1g+e/11Lt9gwKJHDL7gBS9Gs4dbK1tcfGbt5twhBjg6eHUxgBLcArcm3HTewPSYoj5x3+ZgrE8B12dyLjsBsNRnDOjaiGjvw76PJHKsEkdNOUNi/wJffjIYcRh0l9fQg9+AYEwb0AM3QWBlSyFj/UGPIQZXcuPLeDqvHwe/BMFc23sgGEcjfjXg5DjtOT6G0F0nxwQnSR9toP4qaWd6RGIxUzslAu49qOuJAxlBqnHk6WuxtzbmtmDu6N6ov753BXsvEWE9iWQAhE5G0A4j+2k1z/jUsPvOc26mnu+MogcmJu9762mAlPPXGh4uFfy14c72OIDB1qkKb0QH7uGXoYctXM1jSgrq8cZc1TPGmd4QypQ0XWao4h64pj1ehSwV3I5Qv+q3karXiz7m3Gh2Mk5fNg87xSfs1GJDzhCDK3LdSxAsXXzcIYJrIk0vcV/Zpf51EqWK9hZ1qr9c3/yK/Osa0+kMe/eAFJY2qyRGAzxs5Cs8Ja3/JVKHTz3wKNn3DgRiD+1LeipmVbdn48idgSP3HDVyF0LjxRo40yFXt8exXwXYn2ne7wFDZDCORmoouTd7INPz+Gzam10EP5F1rXy416YQ+GS5gMUzJ4B77GluNTNN01woux+5kgB4pwAg5qBXbOH22alTaOIu/Yx1qdsjyD4oyQXokUzIk5xIyJlIyBmKkIcAxVGbSVPA1WYTPth5E9KwA2cTX62kMXcuU+asX2nNdyyX+lcHlrrMWurTtwMJSzjTpb+AGgChlwMrJN87ow8v5Z1m8DVspbxjjqR8DVD+fYekfD6MjK44Je7Co51iNB5lUrOvsfBhpewEI5k/mjLKC49I9ujgdTP8NvYAixHiHjnCdKQzOcFs6QUMS9fkIFDkUzU4z5bx8Ud481e25HiA3vE4Eg4oetsYdqXKy/jceOETEBDLjjnSEy2Fa5jtv1UHgxVQ4LpPQpyO3CDT/MMVeWQ9HsOlM4DMHuOFDyFSSng5Nl64/xgWUc7mGfseO4soHiWiXLWKRZRzOEGzHXvWIuxZy1TPOmcV+fU5Q267DZpFnfd8zjKJslxuzXIwZxkeo5QhIf9QyqXWlAWQcid7eGESX/cwkXjhmMfWDzPAYiWMNHXeBx/sYWeljf3wFvwGgiK//TuJJ7+C9+nr7eDm6a5D6bRQbbzwT/AmrzNYzgNygg3pCmEbeijKlt3GlL2akwy3YeUvwco3qMp7IA1Nyd+r/in605qHqLLUkaWDnlrqt9sOYex52bNfvDD7UO4imxnPxQZ3EaeqyIxbu8gJFCrlmH3Ph9ShdKyp3BGTv+QafkPTdMd8mr6z5rfHzcPiZAjEUoF2FteX5gCwZk+26sFdYE/GrOygB0X/mrwO+lfI86yzBl8MXCmcMTqZsfGj+6/RFy3/eEAuWl77rbloUWuExnx1ZjoQK5CysuZUVlxfVo4cgyWgK5DXncmrHCR6OXGMlnKdY5xGQtVnN5KEdUy88MM=
*/