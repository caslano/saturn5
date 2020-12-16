#ifndef _GREGORIAN__CONVERSION_HPP___
#define _GREGORIAN__CONVERSION_HPP___

/* Copyright (c) 2004-2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <cstring>
#include <string>
#include <stdexcept>
#include <boost/throw_exception.hpp>
#include <boost/date_time/c_time.hpp>
#include <boost/date_time/special_defs.hpp>
#include <boost/date_time/gregorian/gregorian_types.hpp>

namespace boost {

namespace gregorian {

  //! Converts a date to a tm struct. Throws out_of_range exception if date is a special value
  inline
  std::tm to_tm(const date& d)
  {
    if (d.is_special())
    {
        std::string s = "tm unable to handle ";
        switch (d.as_special())
        {
        case date_time::not_a_date_time:
            s += "not-a-date-time value"; break;
        case date_time::neg_infin:
            s += "-infinity date value"; break;
        case date_time::pos_infin:
            s += "+infinity date value"; break;
        default:
            s += "a special date value"; break;
        }
        boost::throw_exception(std::out_of_range(s));
    }

    std::tm datetm;
    std::memset(&datetm, 0, sizeof(datetm));
    boost::gregorian::date::ymd_type ymd = d.year_month_day();
    datetm.tm_year = ymd.year - 1900;
    datetm.tm_mon = ymd.month - 1;
    datetm.tm_mday = ymd.day;
    datetm.tm_wday = d.day_of_week();
    datetm.tm_yday = d.day_of_year() - 1;
    datetm.tm_isdst = -1; // negative because not enough info to set tm_isdst
    return datetm;
  }

  //! Converts a tm structure into a date dropping the any time values.
  inline
  date date_from_tm(const std::tm& datetm)
  {
    return date(static_cast<unsigned short>(datetm.tm_year+1900),
                static_cast<unsigned short>(datetm.tm_mon+1),
                static_cast<unsigned short>(datetm.tm_mday));
  }

} } //namespace boost::gregorian

#endif

/* conversion.hpp
SOJDX3EOZcFv7ZXo47kryuA24wsHJPErX3ZOLBX8jns5FkkcUZ5T74AkXr7WOZQFv9PWRh/P3VEGt3lBByTx0WucE0sFv9usiUUSR5QXf+6AJD55tXMoC35nr44+nsdFEU6e+MwBSfyWWufEUsHvw2tjkcQR5eWfOiCJ3/2ScygLfue91FySeByQ4dlPHJDEZ65yTiwVnD9qVSySOKL80scOSOL3rXQOZcH5k1YemCSOyK/Z7YAkPn+Fc2Kp4HfPFbFI4ojy5l0OSOKPvegcyoLfZ74YfeXWuFjKyG/Z6YAk/mSNc2Kp4He/mlgkcUT5o48ckMRrljuHsuD3wOXRV26Ni6WM/O4PHZDEV1Y7J5YKfl9cHYskjih/84EDkvhry5xDWfB72LLoKzctyuD23Q4HJPHXX3BOLBX8Hv5CLJI4ohze7oAk/v7zzqEs+D3q+ejjuSvK4Obe7oAk/sFS58RSwe+xS2ORxBHl1PcdkMS/eM45lAW/pz4XfTx3RxncWr/ngCT+1bPOiaWC39OfjUUSR5Sz3nVAEm94xjmUBb/vfSb6eB4XRTjp/I4DkvhvS5wTSwW/5yyJRRJHlI9/2wFJPNFBlAW/H326uSRxNJP3b3NAEo972jmxVHD+gadikcQR5RPfckAST3vKOZQF55948sAkcUQ+f6sDknibJ50TSwW/n34iFkkcUT5jiwOSePYTzqEs+L3i8egrt8bFUka+8E0HJPHDH3dOLBX8fumxWCRxRHlAnQOSeN5jzqEs+L1pcfSVW+NiKSNfstkBSbzbYufEUsHvzYtikcQR5SvecEASDyxyDmXB7x3/iL5y06IMbmWvOyCJn/4P58RSwe+PHo1FEkeUKzY5IIkXP+ocyoLfXy6MPp67ogxuYzY6IIlfuNA5sVTw+5tHYpHEEeUprzkgiZc+4hzKgt+/Phx9PHdHGdymveqAJD7kYefEUsHv8EOxSOKI8j0bHJDERzzkHMqC38kPRR/P46IIJ7PXOyCJj3zQObFU8Dv1wVgkcUR54ToHJPGJC5xDWfA7c0FzSeLode7+VxyQxMc+4JxYKjif/kAskjii/PjLDkjiU+93DmXB+c73H5gkjsg/tdYBSXz6fOfEUsHvI+bHIokjyi+ucUASv3eecygLfnedF33l1rhYysivWu2AJD5nrnNiqeD3iXNjkcT/xd55xkdRhHF4r4QcIZCoqFg4op4aezSKgKIJRj0waFRUVMAAooCUQAo1kA7JEUoChKJI7yhNCEUIRcCOqChWVMSDKIogSNE4797MZr1sdrKbeb/tfAiX2TbP/vfem+f3Yy6A/H4FgokvnIGHzPJuN4M/c6vWUm34j7YimPiS6XhayvJ+cLoZEwfkr7cgmPi6aXjILO8npvFnbhKnuH33NoKJbyjD01KW91NlZkwckCs3I5j4rql4yCzvHlP59dzGKW7HNiGY+LtT8LSU5d1rihkTB+RzGxFMfP9kPGSW9+DJ/Hpu5xS3fzcgmPiBUjwtZXmnl5oxcUButAHBxA+X4CGzvHNK+PXcwZGTJuUIJn5kEp6WsrzzJ5kxcUC+Yj2CiZ+aiIfM8i6ZKMrE4Uvcm65DMPHfJ+BpKUveN8GMiQPyVW8hmPj58XjILPlp4+tn4gDvWYtg4lXFeFrK8p5ZbMbEAfn2NQgmHo6IzPJePI4/c6vWUm34O1cjmHjEODwtZXkv85kxcUCOX4Vg4lf68JBZ3uVF/JlbtZZqwyesRDDxFkV4Wsry3lRoxsQB+fE3EUz85kI8ZJb3nrH8mZvEKW6d3kAw8dvG4mkpy/v9MWZMHJC7r0Aw8XvH4CGzvL8s4NdzG6e4vbgcwcTvL8DTUpb31/k=
*/