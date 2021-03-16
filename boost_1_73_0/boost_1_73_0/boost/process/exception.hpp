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
9eDhlAcV17qQ+zn670eMp6QDz/Tx4AwPc8CJLtxzmQfrvnKhfwW2m0L0Y6kHy35DXQ/3IG+AA02beHCcC5CPOWVJcw/mooztN7tw10EeTML89tYNAHc1wVzS1oHD7vdgOtrYra0LD2I9f/+4B+t7Y59aBXDLYLR1EcbC3Q6c1wz96GBMPoBj9vYO3IFtbnaNC4dj7jsb28dxWNa6ywBqMB5GYDP7AOvi+ebYTjGuFtzrQMazar6rA3Xo86df8+A=
*/