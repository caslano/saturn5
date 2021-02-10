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
Y3VybC1tYXN0ZXIvbGliL3Z0bHMvbnNzLmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSKyl04Y4CAACGBQAAGwAJAAAAAAABAAAAAABFaCYAY3VybC1tYXN0ZXIvbGliL3Z0bHMvbnNzZy5oVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUmNun+yzjAAAbBYCAB4ACQAAAAAAAQAAAAAAFWsmAGN1cmwtbWFzdGVyL2xpYi92dGxzL29wZW5zc2wuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJVs+uyYQIAADoFAAAeAAkAAAAAAAEAAAAAAA34JgBjdXJsLW1hc3Rlci9saWIvdnRscy9vcGVuc3NsLmhVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSYPLGCvcQAAA9PwAAHQAJAAAAAAABAAAAAACz+iYAY3VybC1tYXN0ZXIvbGliL3Z0bHMvcnVzdGxzLmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSBevK1CoCAADQBAAAHQAJAAAAAAABAAAAAADuCycAY3VybC1tYXN0ZXIvbGliL3Z0bHMvcnVzdGxzLmhVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSaM9PSqJKAAApRAEAHwAJAAAAAAAB
*/