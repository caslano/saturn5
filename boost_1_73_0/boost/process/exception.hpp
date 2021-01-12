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
NbW1875kcn4NBt7uXvXKJ4fHncZyFUzXE495s1Dz0WH1AFyTBpIB07qnRfcAOUB0JvzAwV4ZjnDeERHgr5hc0X0IknIx8gIheeiyV7poGr9ByFG5f3oaLUt581Taqm+cTlvxzVNqq8anNR4TMrqt/5qVntGg/ZsW4Gp5M3e/+fP1XIcDKE2BJSAttQf/cb1iP/9X3zWUIcKdIFUT7CDbknNyeHx4fp5jrLKFP8FX0Erg5YG5
*/