// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_HANDLER_HPP_
#define BOOST_PROCESS_DETAIL_POSIX_HANDLER_HPP_

#include <boost/process/detail/handler_base.hpp>

namespace boost { namespace process { namespace detail { namespace posix {

//does not extend anything.
struct handler_base_ext : handler_base 
{
    template<typename Executor>
    void on_fork_error  (Executor &, const std::error_code&) const {}

    template<typename Executor>
    void on_exec_setup  (Executor &) const {}

    template<typename Executor>
    void on_exec_error  (Executor &, const std::error_code&) const {}
};


template <class Handler>
struct on_fork_error_ : handler_base_ext
{
    explicit on_fork_error_(Handler handler) : handler_(handler) {}

    template <class Executor>
    void on_fork_error(Executor &e, const std::error_code &ec) const
    {
        handler_(e, ec);
    }
private:
    Handler handler_;
};


template <class Handler>
struct on_exec_setup_ : handler_base_ext
{
    explicit on_exec_setup_(Handler handler) : handler_(handler) {}

    template <class Executor>
    void on_exec_setup(Executor &e) const
    {
        handler_(e);
    }
private:
    Handler handler_;
};

template <class Handler>
struct on_exec_error_ : handler_base_ext
{
    explicit on_exec_error_(Handler handler) : handler_(handler) {}

    template <class Executor>
    void on_exec_error(Executor &e, const std::error_code &ec) const
    {
        handler_(e, ec);
    }
private:
    Handler handler_;
};

}}}}



#endif /* BOOST_PROCESS_DETAIL_POSIX_HANDLER_HPP_ */

/* handler.hpp
gumZ3hweB3GPAFLPFunSEfsuZL6eTtOaIiZCyBDyaUbuLzO1kjWofeSER2sMHGsw3w/0fd+NdR8CpZivVk3PGTxrFAP8rpXvi3tKplG8zS8kBiLuMvZ3M3goYYoyBfD1MKLT2mAMqZ4RW2D5/iTAPZOOshtaIvd8dnqMB6G64844KK2YLburc1ywtxYbUrflCJiAOl0PcDDgmLoD3+hOHpujpTa+3QEpGbZaVwxaLtjR8J96vNhtx7t3EpZVd0PG/jvqCJe2LfSs4SST6M+GbH6/3OnvbCyaiqhPPOXJsf2gc/OpbeqvU8/2rTESm4wI2S25HfG9clIr10OPS99efEtW52S5LeVXIMtomzHQP1oDTIStS0hkuesnEsoMA00+8Hg6CajGVhV72eyBsQ4BBmBP2bPeeQF0K2GpOP2bxrn6CHy9fgyqt82xJC1V/huIJHn2mbm1jZTLDS+hQYgMp4NXYvuWjKt+IcXwSJMV+Uz/9H+dThPOOkM0cPB4AL2epa7tpwXr8Kib/y/zUhIQmhPZkus19cu6a5RMVZBImo/wkgCfMKHAdnUefg==
*/