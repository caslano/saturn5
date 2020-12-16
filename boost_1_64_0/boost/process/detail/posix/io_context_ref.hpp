// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_POSIX_IO_CONTEXT_REF_HPP_
#define BOOST_PROCESS_POSIX_IO_CONTEXT_REF_HPP_

#include <boost/process/detail/posix/handler.hpp>
#include <boost/process/detail/posix/async_handler.hpp>
#include <boost/asio/io_context.hpp>

#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/algorithm/transformation/filter_if.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/view/transform_view.hpp>
#include <boost/fusion/container/vector/convert.hpp>


#include <boost/process/detail/posix/sigchld_service.hpp>
#include <boost/process/detail/posix/is_running.hpp>

#include <functional>
#include <type_traits>
#include <memory>
#include <vector>
#include <sys/wait.h>

namespace boost { namespace process { namespace detail { namespace posix {

template<typename Executor>
struct on_exit_handler_transformer
{
    Executor & exec;
    on_exit_handler_transformer(Executor & exec) : exec(exec) {}
    template<typename Sig>
    struct result;

    template<typename T>
    struct result<on_exit_handler_transformer<Executor>(T&)>
    {
        typedef typename T::on_exit_handler_t type;
    };

    template<typename T>
    auto operator()(T& t) const -> typename T::on_exit_handler_t
    {
        return t.on_exit_handler(exec);
    }
};

template<typename Executor>
struct async_handler_collector
{
    Executor & exec;
    std::vector<std::function<void(int, const std::error_code & ec)>> &handlers;


    async_handler_collector(Executor & exec,
            std::vector<std::function<void(int, const std::error_code & ec)>> &handlers)
                : exec(exec), handlers(handlers) {}

    template<typename T>
    void operator()(T & t) const
    {
        handlers.push_back(t.on_exit_handler(exec));
    }
};

//Also set's up waiting for the exit, so it can close async stuff.
struct io_context_ref : handler_base_ext
{
    io_context_ref(boost::asio::io_context & ios) : ios(ios)
    {

    }
    boost::asio::io_context &get() {return ios;};
    
    template <class Executor>
    void on_success(Executor& exec)
    {
        ios.notify_fork(boost::asio::io_context::fork_parent);
        //must be on the heap so I can move it into the lambda.
        auto asyncs = boost::fusion::filter_if<
                        is_async_handler<
                        typename std::remove_reference< boost::mpl::_ > ::type
                        >>(exec.seq);

        //ok, check if there are actually any.
        if (boost::fusion::empty(asyncs))
            return;

        std::vector<std::function<void(int, const std::error_code & ec)>> funcs;
        funcs.reserve(boost::fusion::size(asyncs));
        boost::fusion::for_each(asyncs, async_handler_collector<Executor>(exec, funcs));

        auto & es = exec.exit_status;

        auto wh = [funcs, es](int val, const std::error_code & ec)
                {
                    es->store(val);
                    for (auto & func : funcs)
                        func(::boost::process::detail::posix::eval_exit_status(val), ec);
                };

        sigchld_service.async_wait(exec.pid, std::move(wh));
    }

    template<typename Executor>
    void on_setup (Executor &) const {/*ios.notify_fork(boost::asio::io_context::fork_prepare);*/}

    template<typename Executor>
    void on_exec_setup  (Executor &) const {/*ios.notify_fork(boost::asio::io_context::fork_child);*/}

    template <class Executor>
    void on_error(Executor&, const std::error_code &) const {/*ios.notify_fork(boost::asio::io_context::fork_parent);*/}

private:
    boost::asio::io_context &ios;
    boost::process::detail::posix::sigchld_service &sigchld_service = boost::asio::use_service<boost::process::detail::posix::sigchld_service>(ios);
};

}}}}

#endif /* BOOST_PROCESS_WINDOWS_IO_CONTEXT_REF_HPP_ */

/* io_context_ref.hpp
17rQ+DX7bbF18Gz7XuzXSMbwivvpAYUlzhLWRzpf40CSXDNuQ9vfyxLuTMcY8bywPUz8Gm60FWPqwIai68BI8NESz/cCz0mMk4nsNtiX89yILoXjG/RapTnHoB7GvRXI22TNW723eHbrczOok3SdLnaSVrmeXfV6ztFJ10u8pFXpSad2bmTG6cpLot4EJbl6TVseJe+JKF3vAfXv0frbvFO6XjO1jSgr7u972EZ+x2RZbnOhXG2L5WXb7V3OadvLL7byzoQt19K2reO0Ne+pxdNzNA5pDts0sbXrgomJYltYOoVLo/YNHPYNxN51D2uxbeKwbRJhWyq2BdOZciK2zRy2zdxtc7Lmlph76vFG9pocLRx+WzjTYPxOzMopyZscSkMbh30b295+x+Ua8aZmzjWosYzDlven3ZTNC8R+mtdtLsVH4nYTcx6KPdjLPKTdoqvhTTTvt6VT8kpmFuU43osXi80M72RvlGXbBbbTtO1S4LliV+jN8UZLfL3pcu+XOOvqZWKT5x3rreJMEymy30e8kqZvPHM9peY9Zq/4+4G9suciJm05DHyfKfv2qt/Lxe4MV3+h/TWvEd0Yr12vMTXLMV9+pZx/KlcwluckOhPOFcxRmcwz5ICVavZfst+dxxdKMswcOP32CrPhQL6b9uBOmPIuGefJl7zwBfclLch11M8/ik2Mne/mHd45Lw43TQe7TRm/6U0CfpNMfRwIY45fwqC9Oz/XuXdibbFtrccea0DgGJ8mbOocwg7OI3LO40OfVVJYUD5dhzwnWtvsfaqIW0mpXce3k/Ab4l5Nwtyp6Wgo5UFuCJOOezUu51L3NwjENZm6A6mLpCJHIWlIPWRpkszRlLVJntH2hnT09dW9gf7dUNkISca2MWyCHI0cgzRF3iacZhA3JBjesTDwbGnyG99lW5qUn8sSqOeTpZ63ny8JqeFtGXEuzyH7W4z6WXVJRif1sOjq6MMNHfVt0C7NfONRr+q3XQNI/YnO1J9i2yR8D33RNTNzcKQ+FF0Lo5N6T8JsY3R2fZau8yK5/ujL3yf4k/Krz1gt1/qcNXop06LbFdJpWUxxzsl0lkP0O815pdyFzX3v39GS38pE0qtkriEXX57T8oh2n/tul8mvW8g3k/l2+LIlxzJv7CSutYZFyH/3e019rnq3efLiL7YCf6oPe6Zaco3terVHO4m7N9kzlFcOdBx5WwV03ir9PSdG3RzdwDoYHW1NiRku5zqe/BksYfZPnMq5Usy7WDEPmEn0g+m+nNg+iO2rYrvZ/wmDmZ33PllVyoNA7BZgd/kx2FH+m2Jnx1WiavYvzpSwMhML/MGwzpL34Cm5WXwWhNqHbg2bf9yrZ1FW6RS5tvqce1jC+MAfRRj2e+SUQmcd85PkSV+e2bWDz3z8pRrb4LaA0hhMcp11bkYHeX6ba3uGHMfIuZcRRg1J44X+u0ljxPxNsbGwuVZsDibUx4ZnMe3XUrebb9HjmgbcT49tabWOnhSdZF0U3dDaEj3ftHG80kLy0XWNBNlnQfxPjE2OWWS9EzPEI89gc82vrBplPRyr7Xj8TBuOeU4OOS5g19l8778k5TdK4p9D/M+T/PUntid/7XCKubMLAgGJXW/srhe7n/z19DokyfVmXzS16YzNGrHZ60+UsELpkZfgmc45ryvaSwnXY0pbezvfdxDOFxLOnf5tCWHlNS9njl1g0zV/vmwTsH0hOpZRll28tawbvUd5XvZ94EkJy6cdMVHsRBTne9wXOEcS5/hazrHa/yznCL1Dcw4qY3vu66R28i7AW1cTxkgeK/HLxG8f8Ts0caamkzrW5H2JZZfLKZL3t1SvynDgFE3rfNEdqF7FuqI=
*/