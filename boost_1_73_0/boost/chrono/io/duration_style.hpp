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
/wafgIvgIrgKLoYb4RK4Hb4B98I18FP4vJ0PuBb6g4wXYDm4DmbAF2EWfBVWh6/Z5QQ3wU5wBOwG8+FgOBIOhQ/BEXAmHAmfhGPhU7AAzoYT4Bw7//BReD18xi5nuBzeDVfAv8Jn4XT4MdwEP4G74CG4D34Gv4ZH7PyHuF7g6fAbWAces+s5/M4uT/g9vBD+APPhcVgI/fFclzAE74JxcAYsD2fCZPgITIHzYKquZ661wvtU
*/