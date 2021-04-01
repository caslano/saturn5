//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_DURATION_HPP
#define BOOST_COMPUTE_DETAIL_DURATION_HPP

#include <boost/config.hpp>

#ifndef BOOST_COMPUTE_NO_HDR_CHRONO
#include <chrono>
#endif

#ifndef BOOST_COMPUTE_NO_BOOST_CHRONO
#include <boost/chrono/duration.hpp>
#endif

namespace boost {
namespace compute {
namespace detail {

#ifndef BOOST_COMPUTE_NO_HDR_CHRONO
template<class Rep, class Period>
inline std::chrono::duration<Rep, Period>
make_duration_from_nanoseconds(std::chrono::duration<Rep, Period>, size_t nanoseconds)
{
    return std::chrono::duration_cast<std::chrono::duration<Rep, Period> >(
        std::chrono::nanoseconds(nanoseconds)
    );
}
#endif // BOOST_COMPUTE_NO_HDR_CHRONO

#ifndef BOOST_COMPUTE_NO_BOOST_CHRONO
template<class Rep, class Period>
inline boost::chrono::duration<Rep, Period>
make_duration_from_nanoseconds(boost::chrono::duration<Rep, Period>, size_t nanoseconds)
{
    return boost::chrono::duration_cast<boost::chrono::duration<Rep, Period> >(
        boost::chrono::nanoseconds(nanoseconds)
    );
}
#endif // BOOST_COMPUTE_NO_BOOST_CHRONO

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_DURATION_HPP

/* duration.hpp
r8fI0d82CnH0SDWAiTstFrD6utVszNMTOzJdctGbrAWsoSmqLcSN8twwCvV4P++n66jaUDrnf3oEMgwpHqJK8HDZc8Wt+CtfC1WSXlppqqRIN3idY4Q2/L+8P71xf1NzJame2LYlAQ/2lFKyqFqcdJDoHG2c2eYVvm+062v7iMBW2zQiyCymp1U9iXh/5a2x4fDyxMuxArR0ZnKsnuAw11LVjD5q8k/5UMEod2LlO0SuQ3mlHlDzY6vopTADP3R6g4mZgedKVvAml2FQxhY8K+CdrLbn5ZEjqd0Qg9/Te+IcpEbvV6eBykRsbUjvR5xdtBIPcYwOJZBHu2t2IJX6ldQ/rLecfbWn4VW78ndPgCx0NuM4Dds/cfR43bRRyf7wl5iFviN+Wc8qqAGcmyViK519EGv31AsXZ0mY5QPICGw0MsML53It4mDXybXIyG7GTscef7NQR2DEK7gRyiVKpyzETuNAmhuQOJdHl/JSGyUd4OdyD5O7XSVbY6nqIITXz3Rq00lKNSrIbbitpMVsvdROq1cqF9gtkYVv+XPEQpPgPVETWgHEsx3SKQ==
*/