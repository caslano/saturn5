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
jGGyjmpnw5dCUXybEzMUvALl/I74FEWXXRxHly9MUXRZgSdUSD+QlJWjn4mr48DMkzJDiHH2WQjSPzby8qHAGqeo5XW/37Kx2GvNNJsdo+eJKxd64WKvuNQJpqeFxblhdgu9v7a6/XVGXGUfuqy7vrduNFDlrY0XLs5ykfDKKRrcubdTwtt7y4vzfi/0LZ8bLioucvp1KvokXFbUMacMiVhRvoC6Mq8v+l0p6tR7idYf9h7bPHaGyzn4N8cP6f4=
*/