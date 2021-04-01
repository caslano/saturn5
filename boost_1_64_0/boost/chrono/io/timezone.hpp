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
9kFz5IdlWlRUFk6zGlYoJUu3h7IHAzYBUPKcFAAmCkQl5nCKQefW1r0aWKAtVnX+cxX49jFD470CmMSR8L4HnyR/NxChKzKSsyouD2Mi9Fjhuq2uC4xFBMYqRZveDQ0O5+/YiMfHxduTk3TzYQeQLa2h7kSlIrJkHO/4A2DkdKdGpk7vVzUSqCZXu/XXXcNu45N4Z1Catx6OkMAZmS7zwdtHAJ3McfuErXTc3f18LJ+ZwaGSqTUEDPC02avuECkFqnmLco70vnGXgOCO2exHhWbgjjAgtb9QMqjEZqty3xFpJMGf929J5bBT5hsnl+WZVQxFzZjL8Aw2NXVjmeaM1hfQOE9ifw9UtlrWQ0/T4LM+yeYVic7aKgw651jX94vMi1fbeLTU8ONpwVrc539Vn7Y2HV1B6cjGymvjdgxMSxu6yLOOM3LIhWKK22nSgJ6Q/Jjq30TWQu2kNLoJ48yFPHkls5yCMM7H1As35lKJ53h2cu3dL3XJ4CAdKDBtl5qYkoL2VMm/9F1A+okSzhdJBk+i8+fA1wHfLGKGop2JDoOGk86ldi25vFSeAg==
*/