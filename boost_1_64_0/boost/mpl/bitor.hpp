
#ifndef BOOST_MPL_BITOR_HPP_INCLUDED
#define BOOST_MPL_BITOR_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2009
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

// agurt, 23/jan/10: workaround a conflict with <iso646.h> header's 
// macros, see http://tinyurl.com/ycwdxco; 'defined(bitor)'
// has to be checked in a separate condition, otherwise GCC complains 
// about 'bitor' being an alternative token
#if defined(_MSC_VER) && !defined(__clang__)
#ifndef __GCCXML__
#if defined(bitor)
#   pragma push_macro("bitor")
#   undef bitor
#   define bitor(x)
#endif
#endif
#endif

#define AUX778076_OP_NAME   bitor_
#define AUX778076_OP_PREFIX bitor
#define AUX778076_OP_TOKEN  |
#include <boost/mpl/aux_/arithmetic_op.hpp>

#if defined(_MSC_VER) && !defined(__clang__)
#ifndef __GCCXML__
#if defined(bitor)
#   pragma pop_macro("bitor")
#endif
#endif
#endif

#endif // BOOST_MPL_BITOR_HPP_INCLUDED

/* bitor.hpp
p+l6D/3dQH9TAqmpAfrD/wbp+/XXZoY30990yjeG/p5Bfy36W0l/V9Lf9+jvtv//9vtz17/f7Gm2rqFuxNGXFy42N0hmLVqqMVaOetl3HCYLnHTrbf5E7HaPu92XeKQ1I+Bjry/KGDlus3LESwJ6sbAVCNNjO2tFwNjsetwK2bFufICZC8NZpkjmKpJlV1grKRFYHuQkdjCreLyftYq+At0PZnq/YtiZSfxnepYwvVbQRQGSyA+XCwrP8+xbzw3YQPCwiN7lwJuGli/8qS9eUC+r1Gn57Z6Wn/i8zo6rJEqqlR6mrylkrnJb3luqjZ8en2Bt0zYPcCocws1t7rLz3d5hWcqiiOJqpfogQT54/QeAxDPs323TwvFnLKeFxHFSM0uP6UBegUYwMW8O+BbWPxr71yYl5hn2cU85EXD1qqUGvWU57xeeE1u497CpCDSCFeVDcYOMh5D3r7u+nLunq3+u3pbYHpiDcAb+GwRXbt3+ob9FW4z/g9OiOfa31vtbNINnCdDGADxR0DY+tqU9vFEQBkLi0BO//ePd2O7UScKRHPOk91sWkQBXGvSn3fA2nEJvgz/ianKYjQ6ktsH3cup2oOltCHtMvjgmxP5FL+ZnBvSIbcQXLq51+hYSfAzuJc3NnovTPqBv0hgSID3yZCP7q/bi/qQJ/ehalUigjlNXoOxjXBaZeXHK50Dz5HRHxZBCVX2yCeV8AQ3QluvEi2RJcebiokx5Zs+YorA+59CtMtzp19DaPjg6GWTBh2w2KUAOWPAbEbRLmAhUjvMCeI94Rwg5EaOLoEB2bGL2AQXWa+PP9f9+yZXHJRrgeK6bPOoy5JCjimsvizwcne6Tat59XMLCnIdUzKnqx9vg6+vEw77cU3+jRx5tklvHAfHcZQYTRzRbxhz9WHwc5XwcHpidE71ChuIM6w8yx9Y+o3PsW9S9CCXF9hnEwXlqq3JxuEOPMU7gVQW7ob6qQgrp9thbwFuNKjE/nZSCeCbOSO+OBb96Dznr8/Stnv7wy+dNin0TsG/aAuz1gmbBvgHKtxd7aHdLnlHs26jgOfd7vEK1qH6saIG/eS9zOhKmNWFwS/npdbP+bdCVf43MOcyzg0S0Z8TFZ5waGaE3uV4a/T4EN6Gfqj47NvY6jv7JnsRw1O6QiOuNLzwqe29QvY97KEh7LVHExterh7ESvI+JGDG7RXwLw9fZoa2ufyQwG59ZMO9O65MaJVKF8KrdTMhvWLuIshiGN73kZbDI8pIZtgC3CrKW3DZ/LIrBEX3koyhGubmj4Ed9DISPopW+yO6HRU9AIYkRr4Xil8TbEaUxQSPmvoMm1yyxYZtu5PSnLswrDJdKMPfZdwjHGO2CXPuIgjw0OtZF7y5JPvBluM0/9/w3Ecgx+zRpN1QxFtOe966V31BLlnO//9PfA+cmWskRwFcOQHZw6i/n+rXibKq40W8OO2U5iOldQQcCE42/Pex5MwIi0RxQELT+5mpDwUgbkPHO7w+ed+mhwzJCaDX40VrzA6Dl3W6HEHOWolA17hBaM96j0e1eUU5jcKo7dNet0jFYhRFrwz2/geYfJn49b1rVV7xPnrFgsXMm00zMepJc1XeR8xw8ZnfT3N3UiBWpy06Kc7skLbg44HFA3FXxThZzx0x8jHRaHHacxuL3sPwRSInOAEJgL0cJQv+Qu2WYvlNx/wt5Y92ddkfv8JAXsMu/To9YYJefu2DM1YdQ5Hc8dFhQHuGHOUzf7weo+HlkNxYXNiF6OSWyl5Z97kYzcVfB2062fNeCEmujKeJWt46uD/+t65o2mLJRngVvN1N2cyde6uJJ6WsocVNdhid9+zuLJ3VZU1mwdpMdPpJT13M=
*/