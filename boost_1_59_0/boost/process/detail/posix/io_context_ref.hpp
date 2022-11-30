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
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
*/