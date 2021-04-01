//  boost/chrono/round.hpp  ------------------------------------------------------------//

//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/chrono for documentation.

#ifndef BOOST_CHRONO_CEIL_HPP
#define BOOST_CHRONO_CEIL_HPP

#include <boost/chrono/duration.hpp>

namespace boost
{
  namespace chrono
  {

    /**
     * rounds up
     */
    template <class To, class Rep, class Period>
    To ceil(const duration<Rep, Period>& d)
    {
        To t = duration_cast<To>(d);
        if (t < d)
            ++t;
        return t;
    }

  } // namespace chrono
} // namespace boost

#endif

/* ceil.hpp
c/uk0ppl3SIaYs59e2NSrl1iydJz6x7VR0GE5R07vGsLrr/i2Zz17Cdle7reXfNl0wJ7IDzlRwmXtTRJuuUOsZbSHRH89UMf8l+3xOZ146qIb84kyS9KwRmPVuHACR9qoC/xTh0nSJ9srYRWjUFOZ3OWb4LB/NqDO7gwY4vTzFlXovT2TnhEBPl3uW8XvRWpPtkGh0UuE0xqkalj6YdeLXAmYQriB7/hWC/2WQCkqNCECFkAHMWjC34N5L6MmJ9EIpwfC2fJueJ6k3oI9DDd4kQHJyWCfoZUPvi3qKkk2iNBtFQhAJgxVqGx5nZFD7wFC3gTY4Wx/SXtLFQIpLkrJdnmOLGcJmQD2wguhKRm9gI5NO/q2mekzeGORNzahAk1dCJnY1U2JDo+LB+VPaXnEf8y/JOuWW2Uw4no3rNPCNTmNu67hfEGW169nqbsFzBm4GfdcVsWmKk4TrG/bMcF9+1tHx0xAI1/V00TJlIL/wotOLULefQ4XIhDodoHnraWwABI8OIKVkKfPAwVmMvNQOm3xyG8OUSYiDdKlXnI4RZghhOIqKUPbPXd1Q==
*/