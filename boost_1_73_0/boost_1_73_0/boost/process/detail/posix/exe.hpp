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
Y3VybC1tYXN0ZXIvcHJvamVjdHMvV2luZG93cy9WQzcvLmdpdGlnbm9yZVVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJakr1jLQQAAEg0AAAtAAkAAAAAAAEAAAAAAHBJLQBjdXJsLW1hc3Rlci9wcm9qZWN0cy9XaW5kb3dzL1ZDNy9jdXJsLWFsbC5zbG5VVAUAAbZIJGBQSwECAAAKAAAAAAAtZ0pSAAAAAAAAAAAAAAAAJQAJAAAAAAAAABAAAADxTS0AY3VybC1tYXN0ZXIvcHJvamVjdHMvV2luZG93cy9WQzcvbGliL1VUBQABtkgkYFBLAQIAAAoAAAAAAC1nSlIVB0g1EQAAABEAAAAvAAkAAAAAAAEAAAAAAD1OLQBjdXJsLW1hc3Rlci9wcm9qZWN0cy9XaW5kb3dzL1ZDNy9saWIvLmdpdGlnbm9yZVVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKZF/HkCAMAABodAAAwAAkAAAAAAAEAAAAAAKROLQBjdXJsLW1hc3Rlci9wcm9qZWN0cy9XaW5kb3dzL1ZDNy9saWIvbGliY3VybC5zbG5VVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSwbhVe34HAABIjwAAMQAJAAAAAAABAAAAAAAD
*/