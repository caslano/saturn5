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
s26l6F0CkGYBjV/+J9buFTmlhR9u8qfL0+nW6cR7RTV3I6XAkCLGSLzhz0RX8xbvCZ8aGianJYkJqVDJ+MM3e2Y+vtl6x5vtp/Ia/bEL1IiZUPbTPtJNIv7H30fPoZMDIZ/uUK85rP6+g5d2e285PEpFysMmH7A7VVo9yJPcXHyreEn0rOyu5hZbVbxPHDF5QB9SmBtGQg7QHkDBTBUeoMVAB+hSVGQAnQa0t05/rpFwVHw5QOeoPCrLbKALVf4=
*/