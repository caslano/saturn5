// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_COMPARE_HANDLES_HPP_
#define BOOST_PROCESS_DETAIL_POSIX_COMPARE_HANDLES_HPP_


#include <boost/process/detail/config.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

namespace boost { namespace process { namespace detail { namespace posix {


inline bool compare_handles(int lhs, int rhs)
{

    if ((lhs == -1) || (rhs == -1))
        return false;

    if (lhs == rhs)
        return true;

    struct stat stat1, stat2;
    if(fstat(lhs, &stat1) < 0) ::boost::process::detail::throw_last_error("fstat() failed");
    if(fstat(rhs, &stat2) < 0) ::boost::process::detail::throw_last_error("fstat() failed");
    
    return (stat1.st_dev == stat2.st_dev) && (stat1.st_ino == stat2.st_ino);   
}





}}}}



#endif /* BOOST_PROCESS_DETAIL_POSIX_COMPARE_HANDLES_HPP_ */

/* compare_handles.hpp
cy9XaW5kb3dzL1ZDNi9zcmMvLmdpdGlnbm9yZVVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlI8C5LPzgAAABUCAAAtAAkAAAAAAAEAAAAAANUgLQBjdXJsLW1hc3Rlci9wcm9qZWN0cy9XaW5kb3dzL1ZDNi9zcmMvY3VybC5kc3dVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSuL6dBucJAAARwgAALgAJAAAAAAABAAAAAAD3IS0AY3VybC1tYXN0ZXIvcHJvamVjdHMvV2luZG93cy9WQzYvc3JjL2N1cmwudG1wbFVUBQABtkgkYFBLAQIAAAoAAAAAAC1nSlIAAAAAAAAAAAAAAAAjAAkAAAAAAAAAEAAAADMsLQBjdXJsLW1hc3Rlci9wcm9qZWN0cy9XaW5kb3dzL1ZDNy4xL1VUBQABtkgkYFBLAQIAAAoAAAAAAC1nSlKE4n4hDgAAAA4AAAAtAAkAAAAAAAEAAAAAAH0sLQBjdXJsLW1hc3Rlci9wcm9qZWN0cy9XaW5kb3dzL1ZDNy4xLy5naXRpZ25vcmVVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSj0X2iVUEAAAZNgAALwAJAAAAAAABAAAAAADfLC0AY3VybC1tYXN0ZXIvcHJvamVj
*/