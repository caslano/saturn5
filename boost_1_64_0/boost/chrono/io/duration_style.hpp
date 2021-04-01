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
CNYXztXZ1RZnqPJYDKTf02ctRJG/OubidTm3EqwullvJubGug2JPxvxdcZciV318mySOImJ2vKczHqw3Q5lZZbW+eUbIYXpj4EMdyT/lKZ74VI4WShPW+SYq7ZXQgYpCg5CsvkwW9uDdfHB5vPV8DcIqPPOziQQX3XncLyKrNcc3sryuzO9ul25BZQEabgjYqm916AZpGdcMAAhK9tIrQQBSvDbyXrAMvoIEPWM+tUvqeEu9BgQLDC3Vy0UuPEi/KyMhyKqDw0z9XQNu3+oQhQ1mkvIOWnTjuIIGwiG/0CaUAq6BmvqA4KK7+NlPnhx0Ven1bSDzzOVg80R2fUKLTo++nOkS7ydoTNua30MCbP+qNXyWB18yOv62NAnpck7V2DigwfrPqyeSMt7eAoVD9EgIYO86YpkDVZMbmh3u9B/7jtptXlECvv8Z93/7Ll1AGKODpo/UmsF2i8gSyXZSFcObER89+cjnmSYBuGUHNbC8AmQW97DsSRBRnslWqTgeLAny3y4IqzEM8HpLglInV6LisGhnkyIDApNsDP788KlVrSUplC8/XPdEDQ==
*/