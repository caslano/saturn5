//  Copyright 2009-2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_CHRONO_DETAIL_SYSTEM_HPP
#define BOOST_CHRONO_DETAIL_SYSTEM_HPP

#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING

#include <boost/system/error_code.hpp>

namespace boost {
namespace chrono {
    inline bool is_throws(system::error_code  & ec) { return (&ec==&boost::throws()); }
}
}

#endif
#endif

/* system.hpp
LAHsEATqMhv1xoGX1WnPCGD3IT3FOxrn9fIpgBq4+uBIPGH/6wHMbo8sI4YUBUAr0UvLZcpCFhg9bpCPNACoO4kMa16IJTxJtHRPyiO7nt1CpC17EV6TGpeHHS9GpcRJ9NtCJ4VMlP0iha0jGDgiQ9VfNpMAVdjnDIT1ELiX5bGWTcNlpxY67+qkzmU8TQaQGj/thKMxAKdoHfo0rk2tCiHSPFvTi7KEphjwI85jams51d5J6lwnGTB6A3Vr8qcBdewbfHTsoGHH8Nqf92fRtDc8xVRpwh39KPP9KiRRblbsy+zf+1PD+zn96e9Z7HmCpT9AawP6O1Wu71wsTfwjlkbFHtKfPm+DJ1jX94RSQrcLNeJevAHV4SkI7L1XcPelGcOkjMb+lGFzbfvCdbnJ0+H5+rYEaN7bPytYc/brNz50hU4THzqFr5FCRINDuErX5bst2QP8BonOrWDgvaWOONFfPyjH+l1dd5zo4U5JZznfT5zoh2cyKGpQnOieNE706RF+4kQXLdTEid4Rf71xorNUcaJHz6SyaZowN947TnTpoIDiRPd4CkP8TvMO8YuXqdhUPsBCRcc6WJTfuyFU9NP/Ocrvpln+o/y+N0sTKjrh8YBCRSdDqOgr91jgrKqOUNHyhcw3/EaLnnW/DEEL64gWbZ4lgc8DfqJF3/LY9YGPNlp0M2zX9CnnJ1p0znxNtGjAlYZEi35WGy26
*/