// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_EXCEPTION_HPP_
#define BOOST_PROCESS_EXCEPTION_HPP_

#include <system_error>

namespace boost
{
namespace process
{
///The exception usually thrown by boost.process.
/** It merely inherits [std::system_error](http://en.cppreference.com/w/cpp/error/system_error)
 * but can then be distinguished in the catch-block from other system errors.
 *
 */
struct process_error : std::system_error
{
    using std::system_error::system_error;
};

}
}



#endif /* BOOST_PROCESS_EXCEPTION_HPP_ */

/* exception.hpp
BB+C5BUGsITCk2Vg3PStoqHz7Qv6Pn88L4WWYUOe0iK0RtLtJQLzwOBHUQFKXJ+ogCywIgWC4l2x7LGIG1w/h2Rjri4JjJXY9fnRDFpuWhKbWmqa3Dl2gg6bhLHMy94dpyaOGgT8YfAiBHvC80HLciiFSOtT+//MKym3rIsXkwRNZEHY/doL8xM/t0MGfsGoRFWBshwFEbJsEoEoVeKscTn8fGecHwOlA3Ed0niz3cBMlmbdT8zPa8SPfgoLbvOmKMhkMWWOkBvTBUjB+TSsHUaoIC51vhCQIKYaKGtawDEPWRAvKEt5eVs8wAYJqRfy0Z/wCO+TNsVMrP77bNwaQYbQRbTTi9+SrJYQ6VRKbeBt37wvCYjrQzUGRgvymHfPC7puUt1b+h35H93o74VkTqMP7m118ogo66MFpioKmD7ZU4CsScjJOuKeNSYagBvq52+PhLZ/eYzrwP5o/zbx235S4LHPJhdgHpDF/dibx7+ZnNQHbXa9by/l8K8zPL2RgVC2rj2R54FsT5UEUkCZNSd6YlgJGTddkAQlk4l1PLhZrb0ne37ozOVEvOtEqOwkJ8RGYONn2sHeSc2yB2uOKF86zaTrJsrWdaZFppvMGmAw+Qc/f2F7QDEWkc/+2Ft0owhSQT2s2Xgxg0sedjfXyRoy3j9/O+mlOoo90dIaEDrsvMed7FRxsTopDePCEiSBGl21O6/x2+UURxqY
*/