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
Oe45fJAcHGXvZnTfWXLnIDtd2T6tkKbMBMSezqP3/fMxjRHPOv8sOuwiU9zaE+KnRKpio8pZI0zhgTJ5txQiwwuSwuHG8LKB+gN0oZ3nw+AlR95cbpDAa8UwasPMVehokN/cIOB3g47yXMxQ29dzZ3wvgPI1VCx1zfXKVbGYi20TX06mDysKXWcNI0Saih09L76J65ncaNG55oN5K9kuCNamMXFUPe/A8q7E6M7IdxgrvAtz
*/