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
af94m61jtdXkQEr4els6ZBkN4BhPVu8dVwK0nbBAzZpmoglGhaM/W7lLlWlp86fNUmznK4greg7hfR1D9R4QkMOMBkCeS/UUpxAEHwtuN0la/Buy0mhano6wP4hSFosithYesCUJdgu4aM0RpiRYHr2ltK7BVVr8l1laFZruTWjcthJFPe422w9GGGmOjKPPVojASjd6z+tkHs9E12sfUrZ8+w25l0F68XouW3/LEo5EiREYtv/7ETEeYcMMjKwuz6JmX/jLCucASQveBKIsyX/LBPgR7lYVHUCGKP9eUkW7j9zpYnzopWdAe069XsScXIHhVVLsjkAxK+Hq7Tt66ror4XantcF3ZxaQiT/+UfnDR92Uo3Qd3B0uh8c3cIh+7LZk7AlZNWpIlZYi8c/WgLW+C7NLMp55BpBA1EE06op4uOyac6+dLfIaLoWAXJz5XjXLgOFQ9VzldZmtFhuVEeUtWk7nSL7WNDbOKbPCbEXUgtRFB+1PK4PhcmgvSLJ3GzV0KGoVeGJOkbk27lZ8Oo1VIqORAKiCF4pxW3QOzIz+jPHQqQ2o1WPRrA==
*/