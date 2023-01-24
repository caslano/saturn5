//  boost thread_clock.cpp  -----------------------------------------------------------//

//  Copyright 2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  See http://www.boost.org/libs/chrono for documentation.

//--------------------------------------------------------------------------------------//
#ifndef BOOST_CHRONO_DETAIL_INLINED_THREAD_CLOCK_HPP
#define BOOST_CHRONO_DETAIL_INLINED_THREAD_CLOCK_HPP

#include <boost/chrono/config.hpp>
#include <boost/version.hpp>
#if defined(BOOST_CHRONO_HAS_THREAD_CLOCK)
#include <boost/chrono/thread_clock.hpp>
#include <boost/throw_exception.hpp>
#if defined BOOST_CHRONO_PROVIDE_HYBRID_ERROR_HANDLING
#include <boost/system/system_error.hpp>
#endif
#include <boost/throw_exception.hpp>
#include <boost/chrono/detail/system.hpp>

//----------------------------------------------------------------------------//
//                                Windows                                     //
//----------------------------------------------------------------------------//
#if defined(BOOST_CHRONO_WINDOWS_API)
#include <boost/chrono/detail/inlined/win/thread_clock.hpp>

//----------------------------------------------------------------------------//
//                                 Mac                                        //
//----------------------------------------------------------------------------//
#elif defined(BOOST_CHRONO_MAC_API)
#include <boost/chrono/detail/inlined/mac/thread_clock.hpp>

//----------------------------------------------------------------------------//
//                                POSIX                                     //
//----------------------------------------------------------------------------//
#elif defined(BOOST_CHRONO_POSIX_API)
#include <boost/chrono/detail/inlined/posix/thread_clock.hpp>

#endif  // POSIX

#endif
#endif

/* thread_clock.hpp
w0blKDz4Yb+aLS+r6vATBo2poLeBwK1dCemh6ANBwgmbRTDofBVlAIberMS55twz5MB5acyUlO/O8Ulm5BEJOMWRhdhZdQdz/sWR+W+a2mO3Ja8Zmf+WobYeB2D+t5L5P4Dz3xiLcHxCeFVTcEKgx52O7Dm6BVltdI58GzycN9lJTSl8MK4krodZux6z53L5Iv3PwMUnm6m3QdTa0duyGxOAHYk7AXB6CQkdFyl4psKucGc0o4l6uOAgWkseAmatN+eeSQY1M3y666EIXJYYgrSJ1MqDIHskbLnlHUWR9DbFkxCtuuT2KBqtA5USGveV7xyFQ28icK/C6YukMJfKP2G2LXiWDHKonU8O5+he/ijCxjU72fNJ/0Rrb+iT585IoeC+IF1Bgo7es7i77KqIZR1kl2nKPuNhLhqMzEWj8Ujb5MoYkpE0GS1dk2iEeYU2+HlH9PaEMePYokbihKdg/GmOr3QOJJgQjgzGPuEwnsxc46ROvTGddaqrulM7Sq+K2KedtPEpkyfdq8R/imCR0o9yno1wpTHFMyw8xT1MsHtGmumNA1LF4ErYXpdHMEdIYcLq42TdXGsj2PVQoVgIQjGVY+b4hEdg1xVGZggiJPL8Arn0/Vj6vQVYGnK4McfIqZJV9VRZXS/zomum+fKiL07z5UWfnebNizKL7J/uY5Ft01iwdi9+lDp2Mo2vlvlRkE/soInAO2GSR82z
*/