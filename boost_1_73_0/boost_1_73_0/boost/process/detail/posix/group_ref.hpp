// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_GROUP_REF_HPP_
#define BOOST_PROCESS_DETAIL_POSIX_GROUP_REF_HPP_

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/posix/group_handle.hpp>
#include <boost/process/detail/posix/handler.hpp>
#include <unistd.h>


namespace boost { namespace process {

namespace detail { namespace posix {



struct group_ref : handler_base_ext
{
    group_handle & grp;


    explicit group_ref(group_handle & g) :
                grp(g)
    {}

    template <class Executor>
    void on_exec_setup(Executor&) const
    {
        if (grp.grp == -1)
            ::setpgid(0, 0);
        else
            ::setpgid(0, grp.grp);
    }

    template <class Executor>
    void on_success(Executor& exec) const
    {
        if (grp.grp == -1)
            grp.grp = exec.pid;

    }

};

}}}}


#endif /* BOOST_PROCESS_DETAIL_POSIX_GROUP_REF_HPP_ */

/* group_ref.hpp
c1Z62rRT4W+bpz7J34dKfSt86tstaD6UotZnxu0V7fG/R7o/GyoPyEpMScrpn5QZyOjrdLgPwNG5j50+MuP2KfSZLh1s5FKP+x/oSzns98hhn5DDp4oc9vnI4fM0FV+X+z6P3L9M0/du7qtAf74S5cZ5YsbhNFePizywrx0Y55WVLfLEk2+Fzn0ncDGusPcBMB7YPjmGl0Du/ie3bBX6QZQ9qvTFa0pc/lF5/pby/JjyfL3y/Oc03Z7S4ngMj60=
*/