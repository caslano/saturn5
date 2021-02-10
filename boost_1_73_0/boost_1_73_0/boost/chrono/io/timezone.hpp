//  (C) Copyright Howard Hinnant
//  (C) Copyright 2010-2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
// This code was adapted by Vicente from Howard Hinnant's experimental work
// on chrono i/o to Boost

#ifndef BOOST_CHRONO_IO_TIMEZONE_HPP
#define BOOST_CHRONO_IO_TIMEZONE_HPP
#include <boost/detail/scoped_enum_emulation.hpp>

namespace boost
{
  namespace chrono
  {
    /**
     * Scoped enumeration emulation stating whether the time_point for system_clock I/O is UTC or local.
     */
    BOOST_SCOPED_ENUM_DECLARE_BEGIN(timezone)
          {
            utc, local
          }
    BOOST_SCOPED_ENUM_DECLARE_END(timezone)

  } // chrono
} // boost

#endif  // header

/* timezone.hpp
UHeQcMMPzII6jUYKrtUM+1htthhYyxcsG7GnFEx7lrL+Bz+Y+MNgEkTLC87ek3CWNd+azneXVV2Mo7vFFOwCcPxLYl/2SttC+SnV2ys8oqqAyC/K28bYC8dj8CfhDDfkcPHttk32sQWhh6V2e4/e47xpbi8stOuzvfsXUEsDBAoAAAAIAC1nSlIIP7iNuAgAAL4UAAAqAAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL2N1cmxfZWFzeV9wYXVzZS4zVVQFAAG2SCRgrVhrbxq5Gv7uX2FxPjRZEdLLh+6lWh2a0O1oCSAgzUaKhMyMB3wy2OzYE8KqP/48r+0ZBrZVu9JSlcvYfu/P875O76HDf/jXXqxH4vg3Xwv/f4EXPutDk9L8T6buywcWi888/MPBB3x+h6pLfjj1eXHOv+vUZ37mTy2irnf0fbH4DnUPZCS9XdLhhwV9xZNwMp6/Mtt9qVZrx8+uzvmrn376kV/w1y9fv+zya6GVLPjMSb2U5arL32X+yX/X4vm5Z+WvXS4dF0XvSOB8rSy3Jnc7UUqO74VKpbYy48LyTNq0VEv8UJq7teS5KiS/Gk/uk9FvXb5bq3Qd5exNxe3aVEXG1+JJ8lKmUj0FMVtROm5ySID8TFkHmZVTRvegXnIn
*/