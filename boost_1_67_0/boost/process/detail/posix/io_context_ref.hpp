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