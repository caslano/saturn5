// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_WINDOWS_GROUP_REF_HPP_
#define BOOST_PROCESS_DETAIL_WINDOWS_GROUP_REF_HPP_

#include <boost/winapi/process.hpp>
#include <boost/process/detail/config.hpp>
#include <boost/process/detail/windows/group_handle.hpp>
#include <boost/process/detail/used_handles.hpp>
#include <boost/process/detail/windows/handler.hpp>

namespace boost { namespace process {

namespace detail { namespace windows {



struct group_ref : handler_base_ext, ::boost::process::detail::uses_handles
{
    ::boost::winapi::HANDLE_ handle;

    ::boost::winapi::HANDLE_ get_used_handles() const { return handle; }

    explicit group_ref(group_handle &g) :
                handle(g.handle())
    {}

    template <class Executor>
    void on_setup(Executor& exec) const
    {
        //I can only enable this if the current process supports breakaways.
        if (in_group() && break_away_enabled(nullptr))
            exec.creation_flags  |= boost::winapi::CREATE_BREAKAWAY_FROM_JOB_;
    }


    template <class Executor>
    void on_success(Executor& exec) const
    {
        if (!::boost::winapi::AssignProcessToJobObject(handle, exec.proc_info.hProcess))
            exec.set_error(::boost::process::detail::get_last_error(),
                           "AssignProcessToJobObject() failed.");

    }

};

}}}}


#endif /* BOOST_PROCESS_DETAIL_WINDOWS_GROUP_HPP_ */

/* group_ref.hpp
X9j6guk+JVwzBz70oqRKSAH1Pmh089wxDUUHWW0ERnc6ebSPmbg7jN+ORp3zPlua9bvxE/QyhEKlHoY9/+vuxUHZIUsbVGrlQZGTh2pRyLDZL2VVg5UpiKJUHlOf09l9pp9MTkIEYCaxcdmEg/g33s32bElUNrm45SkiMcAWRm3CdvcG152szs+8VDvL8hFB2AyRcGT46OZMC21Ak0bRP3/N7edPa3OmmZ1GG3FgodnchMM/
*/