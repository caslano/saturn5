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
GmdNVi2dDaiXLomWPSKMlJlCVmKLuXRsZmTI6TRCJSPNcVoKoIIR1ED0Ge4Zls9Ri+WVbxkdOKvMO2HA2AgI1WDgL5SOEj60Xgehk+4P8uJZpLhgUsiVf+YoT4gGnQ61dVFqnQLiRok4aIvDdZQLs4eB1VMmSIyO4CopLKW14aS1ptVElBxHLlvPuKTYcjxa9FfJ5INXE5fA8u7MFemRZt42kqEJmY7CBfC9lsihRQdhHQ45vC075yJN9kFZKi8r69XDittkKqkErTcAFxj9y+UU12m5phJqvPJ5Pa7f+wDNi8rC6X1d98qAwWrwmQrFBLX6ZOlTFsx26ZfGlCG2kpilVV/mSKVKoE51XOqrrakiTUyAv4dqCsJrIPsFAwSkhTCWwQhfYXP7z9PdH3NH9BzR32UfUbIWLCBhZMHWckeJToLRHTd6xT1SYZC571yo1Z9eMDWn5uKA4++c1h2YETWPdbGGCJdp10leba8l9Jjh4ydwGa1aZBVBuKmnbDiPmcD6B74KfaUU1YXQOXhKa1nj5k3W2Y09htrAhvOSOijHXG6AxF22OfdUSQ==
*/