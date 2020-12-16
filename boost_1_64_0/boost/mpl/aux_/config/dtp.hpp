
#ifndef BOOST_MPL_AUX_CONFIG_DTP_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_DTP_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/workaround.hpp>

// MWCW 7.x-8.0 "losts" default template parameters of nested class 
// templates when their owner classes are passed as arguments to other 
// templates; Borland 5.5.1 "forgets" them from the very beginning (if 
// the owner class is a class template), and Borland 5.6 isn't even
// able to compile a definition of nested class template with DTP

#if    !defined(BOOST_MPL_CFG_NO_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && BOOST_WORKAROUND(__BORLANDC__, >= 0x560) \
    && BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610))

#   define BOOST_MPL_CFG_NO_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES

#endif


#if    !defined(BOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && (   BOOST_WORKAROUND(__MWERKS__, <= 0x3001) \
        || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610)) \
        || defined(BOOST_MPL_CFG_NO_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES) \
        )
        
#   define BOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES

#endif

#endif // BOOST_MPL_AUX_CONFIG_DTP_HPP_INCLUDED

/* dtp.hpp
v4T6byEuQf1V7aVBfgex21PUX4izpaEeivV6w/4FMfdZB94A8VcUT4M4B+J1zzvwRoitXohwFsSbIH6Pw5shzq0X4fMQb4E44WUH3gqxWwMab4i3IfhVB96O4NciPKqPBnkHYv+mA+9E0n8rwjMh3oX409iO/+9/b+Vv+pv+pr/pb/qb/qa/6W/6m/6mv+k/Rf7Ojq5GkwI8/SnCXzikcOIYPAqNYmJiSglhCijCH2KkCH9IkWgjgXpX+qZWkulbGovrd6MMlsYSlcFasjKYmpr/Rt8b/qqlkYRGXahbWEqeh5lVpzz+aGNhavIHm2BrQ0tTI0nDBoRmElh0oW9qZv0HfSPJItdV+zVDtOHFpvESRep/bl9mJjijP+chrt45xr9syL/2DstLEgthXhIadVXx3cqji/KYmklaHtgEupOXmJFV52z+ZGNubC2xjcXozhVLbJ8SxLkr/dGWkulbS+aPqbGVZPpm1pLpjzaVSN/M2FwyfQvJ/DGzlKy85r/ruEjrlmQskXCqBRJOa0J9CaYcoNDT3defEWrk7uFs5EOLYjESUWsts/YMLSw6FchQoac3R0DhxzIFtBAWTJbDowh/OhoKJsYy+AImhy0UMBIEDDYfIpGdJsBTt/wwb/fD6j/gh5+LI8XC0sxakphjNhJMc+02ktQVZtP9me5XNmamkpfHzEpy3yw6t23JfqMaSYzwG9XxPA47HM2E+LvZmAz7ZW8AHLypAg41jMFiRAOE6KZMqrOjL94K43nguTg+4Ze66RzIono4T6bC8rAFACFGKD2CGhrNp9IZQs8JPD5DQOVH0HgMOpXJDuPgfmPdjRrKiebGChjUKJg2ZsNHfj+cISbCfpOdzoHycDaVkUDgwUAzw3B6mBIRQ09iuYTfd6eyGfEYxiXCCIW5UoWRNRUkchliPKSYHDrk4vgwRjg2kc9gd+bHhqDqBB5UJfKQ3E2FmQJI+HrDwt81nxrGBe0yj66sxGXiloxQLpXN5AuSYNeihsM6pIWFMdmMTjLh22GgKQOtMABAZx0uB6bMR1S7kPFElY3WRSd5PJNN58Qz6EJrTJ5ARaLD4XZg8UhDnlhEAUB/JJ4azuPEck2F/acLvrCHMumg3cbVxTSaGs1hC8I50Qxeoqg0wnIzuaxEoh7afEVJiX5enkpn8kNh34cjNhr6X+kL+wrq1i/0OKECU2H+v5ALZaZQ63dyXH3C0MOxAromYPDBb234EtlAbWGt8hh8PoNOtCDacIWhpQqjjvaJX8sZ7N/LYaX8UgZdQoZCDvs39vwYXmeZeOUQ/Rc1VS6ctbqtJ9YdxOXdqyRxOwvL7uUv3h07y/+p/OHmuVv5Qz3x/MXl/0z+YvUvLsPqVlz2x7rtbncm6oun2qVONC2KgRaQKBfv6jiZeDf/pYwvljxOT6KhALWRaChAbSQaCgBcVLj6+QT6ioJM5HUdeHEdDjcRj8Ox4AvHJQB+JeOCzjI6I5zHYHTmM0LFllud5VHiGuI6cKUnoLE50UwaixqCvhCmKz0Bj0nQEteB06U4poYkosViQxewukAbIyIP43Hg6oUmoImnhcnEC/gLPfGCiuvxCbH/tYzb2Q6Wnc3g0dC30QAgWmyiLQBO+ngerHGcDmbJgGp4PhopAqZCxyM4dIDnizocXEagPOIiF8PYGonIi8P6IsaDJUGWHyxmKOLNn8cxqIT2F3xRxWV4F8VlODdQP3x93L0DiAMBUUal0ekEHBrNJWIYYTymh7Dw8l8MHu2V3j1dLuhSdwKXx4lkhAqYcV0biNsw2XABLxDj8ak0AZTAXJmCxE4yDps46GMyQsjEZbD14DF+mCbwsSFanM+XIGZ8CWImPsw=
*/