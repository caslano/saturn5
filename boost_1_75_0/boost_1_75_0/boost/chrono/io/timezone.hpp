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
iWi9T09l5WrpyKNaJ4u0aKmR9TQl8FlI4KkQeytb8eLv9LXFd+q8VK2fP+fjzrBG50c/D1PHHCFnoLeTYbJedasuEIV8yVO+CnnSz7lbVDYZshwqb0hOXrMhcSCAobEkHGEQ0poJHeB0dD/MVBT0mRKflcI6zoKaML1ILloBHKQsoWmnngYYSxCeK9ar1PMG2J5ce8UUfgeG4OvHQvBVIQ1/mfFxJUL0UlRp91Z00KL1fdGgY5poVeQB0bqUfI8trDwFRlCJREgmQs6EGHq5Oexh5i0IiAaegQKdhgOZJH4H8HBxkm3C9HjCiTs5hdSgiKAiJVIvOtbSi2DyHeXgyslBNOhGgp1sOxY2Ult8vwTnhaog4L+BLQWBjfxFo1+lRL6Ybgr6q3h8uWg0qWIwmEhZlqcGKTMO8iPTrg7FzxMiqRj4xEPoR8kRlS59Sxfuop6SUI6ZCltFOsgxbPeZes0g7T6PKYJCiMTbQ5zsL4ySLCPHTGGyKMRMkYrgToQxU3KYil4WPHz3o0T+Au5HS5hxRUc4VYaZUi09015nsl0/jbEpc2FgYlo0pN2rSiOLasvvSZhyMjdz2XrewdJx0ek6JzA5pBcmMSC/919D/TpYxTGtQ7O11A0ll676gZIQ0VpBvudW3cpyHfCXi8BSwVWA6KoIOFeZi2jofa6i7F+7nvRrpyCpbmZuosTrIfIU7tiqZ1YFe/NRo3PX
*/