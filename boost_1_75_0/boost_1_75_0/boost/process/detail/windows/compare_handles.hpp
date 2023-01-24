// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_WINDOWS_COMPARE_HANDLES_HPP_
#define BOOST_PROCESS_DETAIL_WINDOWS_COMPARE_HANDLES_HPP_

#include <boost/winapi/handles.hpp>
#include <boost/winapi/file_management.hpp>
#include <boost/process/detail/config.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

inline bool compare_handles(boost::winapi::HANDLE_ lhs, boost::winapi::HANDLE_ rhs)
{
    if ( (lhs == ::boost::winapi::INVALID_HANDLE_VALUE_)
      || (rhs == ::boost::winapi::INVALID_HANDLE_VALUE_))
        return false;

    if (lhs == rhs)
        return true;

    ::boost::winapi::BY_HANDLE_FILE_INFORMATION_ lhs_info{0,{0,0},{0,0},{0,0},0,0,0,0,0,0};
    ::boost::winapi::BY_HANDLE_FILE_INFORMATION_ rhs_info{0,{0,0},{0,0},{0,0},0,0,0,0,0,0};

    if (!::boost::winapi::GetFileInformationByHandle(lhs, &lhs_info))
        ::boost::process::detail::throw_last_error("GetFileInformationByHandle");

    if (!::boost::winapi::GetFileInformationByHandle(rhs, &rhs_info))
        ::boost::process::detail::throw_last_error("GetFileInformationByHandle");

    return     (lhs_info.nFileIndexHigh == rhs_info.nFileIndexHigh)
            && (lhs_info.nFileIndexLow  == rhs_info.nFileIndexLow);
}

}}}}



#endif /* BOOST_PROCESS_DETAIL_WINDOWS_COMPARE_HANDLES_HPP_ */

/* compare_handles.hpp
u6zgx7VIbcH4W42biVncqnfbNRU2AOnW6zOsC1OanZ6DQVvMGHnDz/XGmLspqXnJjIr34y532gX/q4Nm1LHXp0nUyBDExbZ81Eiw71ZXYmuv/9WWD2ok7igxnvC5o8F+OSuSNzsX1doWX8NrzONXtGk4BLcSxS97CDDYaWjxPibRbeEscVcwOjwlY4Es2y3K65/iYnBvUR/EEKh+cOQnLiYcKDikhAmafArni3l8oGyVfGDZaY0Qx4wrSjz5gukV0edc9PNFWrf98ZMMrUFHQvMrddFTdATxgQD/uGv6xS7vynf/nbalaOZdBms+JvezO9hopwNbs2Vz3pdkbT9Zf+gjWbQGUMUkLWqrvPcJ3z0fx/J5Skozk89SEs1exZb0YkPsogEsVXJo0NfwlTGXEIdepxA12PZuXZb4nsN9D/erYO8wbC2R4T4dKPx3awGpjU4+u/NPmKCpBzh8Q5ITuppEltzFlb0Qe3FIUOutpGICRNT5RjbURC+oeI8qVEPPH96U5BuVAnpUG2rckB3ZszuSVhP6F1T1VIJOgFLfBbnRI0xegLAY9iYUx0Y968kH9n7Hl9QlWQOzNqj9voycfmE/2k2EpkCIv8ArDbqSg6HJGw3vEH1ojln3miBAq+UPmVcOob5DRB/yqXudKLWvFZtEsuSWmlDTw6RkmFtiu1uoGPCwtVZQvCgcL4/X4y4TMUyvYy5reYM6ek42
*/