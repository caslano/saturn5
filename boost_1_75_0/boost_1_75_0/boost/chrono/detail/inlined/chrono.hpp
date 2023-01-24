//  chrono.cpp  --------------------------------------------------------------//

//  Copyright Beman Dawes 2008
//  Copyright Vicente J. Botet Escriba 2009

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_CHRONO_DETAIL_INLINED_CHRONO_HPP
#define BOOST_CHRONO_DETAIL_INLINED_CHRONO_HPP

#include <boost/version.hpp>
#include <boost/chrono/chrono.hpp>
#if defined BOOST_CHRONO_PROVIDE_HYBRID_ERROR_HANDLING
#include <boost/system/system_error.hpp>
#endif
#include <boost/throw_exception.hpp>
#include <boost/chrono/detail/system.hpp>

//----------------------------------------------------------------------------//
//                                                                            //
//                     Platform-specific Implementations                      //
//                                                                            //
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
//                                Windows                                     //
//----------------------------------------------------------------------------//
#if defined(BOOST_CHRONO_WINDOWS_API)
#include <boost/chrono/detail/inlined/win/chrono.hpp>

//----------------------------------------------------------------------------//
//                                 Mac                                        //
//----------------------------------------------------------------------------//
#elif defined(BOOST_CHRONO_MAC_API)
#include <boost/chrono/detail/inlined/mac/chrono.hpp>

//----------------------------------------------------------------------------//
//                                POSIX                                     //
//----------------------------------------------------------------------------//
#elif defined(BOOST_CHRONO_POSIX_API)
#include <boost/chrono/detail/inlined/posix/chrono.hpp>

#endif  // POSIX

#endif

/* chrono.hpp
0WMUjrKEfgO8o0Uvvj3QaNEVs2oBpUsKKA3UU1ASnmCg1Id8qHziP4NS5hP+QSn9CU3A6H8eDTRg9K2itT0pWxUl3DUBA0a7rkxwto69MD1+gCNcghhgecnelFtrMOlmpwy1BJPe0puS43t7AdUd14vdfyJfhferazCY9FssSxxm6cuyLIYsC0kWlJkr24XqlHsmNP4YUkJDKKzsyCzR+lgmhhfLZDOSnIkWS5k6yXUw+daXfkvXSa6GybeOmZJlk2QFQ/hf+o3TyVYwzNrp4RmytRPzjaxQ/lxKDX+/bJYo/wK8d1ppBzgbG5XBjO2mxoqgiM5CD1aAY5/MZAyFw4wJifwpVOANl7yAchiK6qn0FP4H8IuZ2B9woynyp+imwNshKCh/N90Ouo2DovXxJ6merPP0+Ahn+0TPsN0EEY7mAOIWi9Y0B3CN1KdCKn8b5x5CUntkQmqpcIxszVz8EGcYhIAkv0vI76pZIEM/TtoXrcMeBe0E2OxY4x5FC4I0T8sIGFL8TFiLYmpdAfUvRzOCY6nAG7cSVp8zoA1BGrUhoKbABsJuHhayUZgjlS9+HKqA8m40C7I6HwdujIitKZ7JacD34d5VIvTvR0kFWDUI5fDDYw3NpGm7+0Hcqh/g9TuaYmEp68nPjej7AE8bAOeDdMx8kYp+arcycHBAXezHHoAr1NZiwDfJ8xuYba2PDaIfgtiHUditVpa8
*/