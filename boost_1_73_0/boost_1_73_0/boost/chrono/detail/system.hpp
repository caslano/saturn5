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
w+kOhmUhEIx+cailRhzMlE+3+0xybWbw8Uo+zLUNfuzDiGO+Ls5+bCDEhCgz8UejC6IdtFgaNt9EcyEzjuMVlqZiRpf2qlChftJHst3C72KjMk4RDvh+kwxgM2GnDF+hux25zJVxix1Led1YSiZeZS582KeYKoMFzXAQYhGjOEbIgN5brHVsk7mGNCBGVdWo98zk1yjIBQpEOhlD3q2SLy7KIUo4eQieQJB5wW9MRFf3jC11DHi8SLyTYgaeFiU=
*/