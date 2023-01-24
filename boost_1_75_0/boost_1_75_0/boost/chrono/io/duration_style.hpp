//  (C) Copyright Howard Hinnant
//  (C) Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
// This code was adapted by Vicente from Howard Hinnant's experimental work
// on chrono i/o to Boost

#ifndef BOOST_CHRONO_IO_DURATION_STYLE_HPP
#define BOOST_CHRONO_IO_DURATION_STYLE_HPP

#include <boost/detail/scoped_enum_emulation.hpp>

namespace boost
{
  namespace chrono
  {
    /**
     * Scoped enumeration emulation stating whether the duration I/O style is long or short.
     * prefix means duration::rep with whatever stream/locale settings are set for it followed by a long name representing the unit
     * symbol means duration::rep with whatever stream/locale settings are set for it followed by a SI unit abbreviation
     */
    BOOST_SCOPED_ENUM_DECLARE_BEGIN(duration_style)
          {
            prefix, symbol
          }
    BOOST_SCOPED_ENUM_DECLARE_END(duration_style)


  } // chrono

}

#endif  // header

/* duration_style.hpp
6KEdyQsHnewzzZWo3grLqg1GS4eA7GmRzBb7Wx0QdzIIf5WwZN7z0Mxv4Koufp7Okg0e7BIWEcoDStSk+M1RxcHg2e+fIFy5Uyng6E3GhFMME5oZpHWdBALD2BLEBMJfHJExocgLE7YwTNA1p5hwOEha/OVsGJZFjYOY6C0vwHNlGkzYIq35FpUkQqZ/3nL4xjCBiXXeM0MhJYQKeWUM0NODVML+C6HI5G6hyr0ypInpTM+DIXPck1ZJa2HOZWB7QpLuIIwwnha0pDo4urKzRRrFHRe3Ce2ZFPRHkuly1SEFVIFkypgGaV84ynhlvgvfWBleriSoNWbCHBOICCR9EC6hbS3iTWNKH6RvJ6RvJ+RvKiEpREoNUUpYpLm2yFDYCaj6yMVURApHbmxHoU5tTYvc39lSdgxWbSFIjzQERJhn97HPR+Ez+fDYPlkT1ncv3Q2+KaUnP5+V0t9r2PNt9nyVPZex5+JSlI/KhM77aME2+2jCYyzD0RKQl4CiW0aAEARvXwcjPi4XrqaQT4lkulN4YxQBIvLcSzZzYCaKhVUlTLfOutSO1diCPRuzp6FU1l2bVXFJgSHSvaEwRHa+xsZXQ1wbdCULkiUNcZAgR/jd3VRtaVCGh6Gp7gfhrLMskd+Vwpe6rtzhDPdMGCocXstOwCdUhfEHhSLp553y0b2jqWSY5WvRuF3eop9dpIn5mSbH/AT/fyW4JReV
*/