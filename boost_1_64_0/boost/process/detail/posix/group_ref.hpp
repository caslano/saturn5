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
UDg6OyM2a8CxXOzhi6ha2xGUdx57fcotOf8ufZlQpdbDZ7BDTmw0jDfYosEY8GZKp8iWcyNMtBuEZ/sM5CwYMSSjSx6Kc4nP5SbxTGD81qx5lMW8PcsiG/MNr1x86vuFR8ZOb7En/XpobdyKWgyggTM3pJtH2J7WwG6ukULHdT75SbOj5F7dxZrgbJJE8f74Muo1ciRHkO0IdyA+/qRu/FnkhiY8uyLYRWAGeFfb3GMyRZTBhfwy9PSkT1YbSniG2U/TwpZ7uZGGQtWHDfG1Z82ra4qKkknWmZKGoZFTAxTcd30AoaBE4rF86biSmDeYQhLIkKjK8KjV2I1UP37wzI7Wh0lF5cVtYZctlURUnQD2sUOUnbUsCFuEAl4O0jsw0VacypEgceNP0UuK3sV7ZDDkJpnzjs1OtFzyZnbX2SwwznTc+poN/IwI5/y12tyceFQ0tmBtEmdWKnkRxs9RCvmCjSmfcRMfU2spGIgc8i+eTIjGNd6pqX1LYcxbWkVsi+gbsWxqXNNnMuT2IVo2/mkgehYuLtoHH2uubPXD5N2u7ZHNYm6iuHp3gw==
*/