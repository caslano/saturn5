// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Borrowed from <boost/archive/add_facet.hpp>

#ifndef BOOST_IOSTREAMS_DETAIL_ADD_FACET_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_ADD_FACET_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp>  // BOOST_DINKUMWARE_STDLIB.
#include <boost/detail/workaround.hpp>

//------------------Definition of add_facet-----------------------------------//

// Does STLport uses old Dinkumware locale?
#if (defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)) && \
    defined(_STLP_NO_OWN_IOSTREAMS) \
    /**/
#  if (defined(_YVALS) && !defined(__IBMCPP__)) || defined(_CPPLIB_VER)
#    define BOOST_IOSTREMS_STLPORT_WITH_OLD_DINKUMWARE
#  endif
#endif

namespace boost { namespace iostreams { namespace detail {

template<class Facet>
inline std::locale add_facet(const std::locale &l, Facet * f)
{
    return
        #if BOOST_WORKAROUND(BOOST_DINKUMWARE_STDLIB, == 1) || \
            defined(BOOST_IOSTREMS_STLPORT_WITH_OLD_DINKUMWARE) \
            /**/
            std::locale(std::_Addfac(l, f));
        #else
            // standard compatible
            std::locale(l, f);
        #endif
}

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_ADD_FACET_HPP_INCLUDED

/* add_facet.hpp
7wnOM9zOT6Lk56e8K6xLtdQxQ8p7GtKR8i5+KKC8M7O18pYynBmin0vYyvdz8Rv0rpDLtSy3vKXNEndSr413/V2FrSu/We2j6sDrvjv8Td7jP4Pr4iv/7iBlOrNy7w4qvYHvDh0sddwo66tvkHeHPg/oZer0msz9pmSYhX/cTGVMXMYyVm1rpHu+lhtG3Mrt5yTB6crPNFM/ifCVf8dw/DajL7weHUvrUPKeEeOtEe2L7h/dPHpYeG1f/fAaviR6xQ2TZU2DrKsPWFOv72Vw+2PnqvgLAvcGaH3Ooer8EtO+ALeMRio/i1W/ukx/6Vd6/3H62ws7mte8p5eujZ2bOXnenOl5l5YskrUqt945PWid7OEqvOuFWieb0oV/RK89yPXI6GTcS9+NefCJflfy3Ziwrm52rG3um52u/CyzOtE7S1J1KOFISWM6l6OsSF3fOafNkTr9Pa3NXqDOn8HvKKO+E958v5h1Hv/B90cuFW2e98Sv+Z1B8nqhOt+YfPoR3PiVo9zOtnyktyH/Gfpo7veNz1Z+c7G7cGrge6vWvgxSfppYjdGNCOlj2f2rz7V+0wXq3aLiZ7zh/nCfUdSn1hfSbK4EzaPHh7hvEpz7RpVn+XMOx3BP9v1yNlqqaovFbKsjtK2X77bZ7oP7PzJgQtd/FCTe3eY3H+f1mMf3OmNt92dfS/vs/ln1D/14w/r+7zXZfJR3pjjbvejAhY1uSf9DjaXRL3uSjt/7aNVtwFymbMDMa5H4/dBx3T+47sEbXu1we/eY0DZgbplqu++7KuPa39f9auuhxEkf7lryVKuq24b5V9uAMdueCW2L5YZu6rojbh9w6A+zOhW2Kd7zxQ/XNP/PsyVTVZsxoWzDHNfWHhyoq76pot4hPpG/r+bvffI3KmK9KH9nI0f5Xezu3VNr/tQ5tS9R4lwm27dWwlpwFWwAr4U94PVwELwBToCrYQZcA6fDm+BMeDNcDG+By+GtcBVcBzfAO+B2uB7uhHfBA/Ae+D38HaxD2u6FreH9sB98AF4CH4QZ8GHdno3ki1uPfAXas/ktp20uhjXhVVq4FAkXbwg3R8LNhXEwT8KlOfux4DkSLhIOlXD9JdxAmAQHwbZwMEyFw2B7OAT2scPBAeLupGuHxJ9gSNcIiX8krAPPl3C4y14h4pZwESo90qf1lIRbA2vCm+HpcC1sCW+BA+Gt8FyIHrrp6SPlVMeQngWSnnxYG17qpMfj7JNR+3JUuOZ2eqBaW+UlHfAZaLs/C9vCH2AH+DwcBHfCMXAXvAjuhpPF31T4IsyGL8FV8GV4g5y/Ce6F98NX4R/ha/Al+Doshm/BA/Bt+Bl8F34L34Me0voXGAU/gPXhftgdfgh7wQPwHHgQZsCP4XR4CObAv8H58DO4DH4B18Mj8Cl4FL4Pj0Ef5fQdjILfw0R4EtaD5EeV6yCP7LuQPR4pSDO7DwDV4aNcQRhMgeGwBYyEZ8Io2AvWgBfDaJgOe8AMWBNmwVhYAOPg9XJ+DawNb4UJ8EmYBD+CydBO1CkwEtaHcbABrAsbwjYwBfaHjeEg2BSOgKfDNNgcToAt4GTYCs6GreEVsA1cBNvC22AHuBl2gsWwM3wbdoH7YDf4EewOv4BnwmOQ/KjyXOus0Qf3in7HQ3RJHTMp92iYDRvCXNgZzobd4RzRz7nwQvhbeDGcB6fA+XAWXCB6+hs4Fy6EC+HlcBG8Et4OF8F7JJ6jsMBZvw6XSfpiIWHV0VfS1x8mwQGwFTwHdoMD4VlwEOwHR8KBcDA8D54L08U9Aw6F+XAYvBKOgIvl/FF4wlnfDXNF/+znxGFJz2O0G7HwSZgCn4KN4Q54NnwGZsLn4FL4Arw=
*/