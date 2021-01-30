// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_POSIX_EXE_HPP_
#define BOOST_PROCESS_DETAIL_POSIX_EXE_HPP_


namespace boost
{
namespace process
{
namespace detail
{
namespace posix
{

template<class StringType, class Executor>
inline void apply_exe(const StringType & exe, Executor & e)
{
    e.exe = exe.c_str();
}

}



}
}
}



#endif /* INCLUDE_BOOST_PROCESS_WINDOWS_ARGS_HPP_ */

/* exe.hpp
9s+vQ8WVXvpXucrMfUXjost6lGrsRUq/TKX7dN760pN13zeTf8B4YmTPi+tDKjOXbrXXRL2S5X4eEh91
*/