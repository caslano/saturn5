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
BaW8kfQtQrxmNu91JG/ZVMnHRtc1DlsKAIl5YeB9vTPpzO3osJNk9nXzOGyVxa2q1zkEnR/JWlxMc0EW6jktT+SX4+eMVOyNA9vyeYFsdGxKGKbwCONXAjavWhlbKZsXGwvThheFFPABq42RHl5iYk/nLmuDbYzHazh3ehFmpJp1L0soUv7OrB7blytMNSu2+XA6+ARBe89dQ1LdXSLK+mAZczst2dZ3b1kZMdM8ut+KBRsK6dta+JmYgKplqtSDQVkocrPiR709z60tp2u2f0Yx7WrddzXj0SOgiurKj+oqx4VPRDl08qK+2DWBTzCtyw66sXNeTcA7F1zsasBqU61vd85R52rS0FDI/YtaNZupRIo1SXJuzsLJkR0T0yk+/ufOzigHsjqLfoPbbxi/j0gnPDtSW2s8s7a3/KDU5vNqcbe+eO9EXQNCZbIsB/c7kghH3JqHRZvdOy+zxYKJhu7s7PfCCSGV1qVF1Hs9iFaGrl6Ckl6yprJyYpZuZqb1zMkVEPn3aLR3H59FVad2rYAqaMyyHcfij+2kkarziWmsFn9gS4H45fYvy9vB4p2ZSzLv7tTHN4QIHeoyd4FMKMCKCt2oKJv6eqbPn1H6+6NMTbPk5VNCfpyuKf6OBiA0o81nsuV8Vij5j9W3WMm3IhHv2K1d3PkinuGkQP+iM936jDavmBeGp5WhQ/nkoajk0LtkjpnSoCDEepka
*/