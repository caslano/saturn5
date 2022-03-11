// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_IO_CONTEXT_REF_HPP_
#define BOOST_PROCESS_WINDOWS_IO_CONTEXT_REF_HPP_

#include <boost/process/detail/handler_base.hpp>
#include <boost/process/detail/windows/async_handler.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/windows/object_handle.hpp>
#include <boost/winapi/process.hpp>
#include <boost/winapi/handles.hpp>

#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/algorithm/transformation/filter_if.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/view/transform_view.hpp>
#include <boost/fusion/container/vector/convert.hpp>


#include <functional>
#include <type_traits>
#include <memory>
#include <atomic>
#include <vector>

#include <boost/type_index.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

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
struct io_context_ref : boost::process::detail::handler_base
{

    io_context_ref(boost::asio::io_context & ios)
            : ios(ios)
    {
    }
    boost::asio::io_context &get() {return ios;};

    template <class Executor>
    void on_success(Executor& exec) const
    {
        auto asyncs = boost::fusion::filter_if<
                      is_async_handler<
                      typename std::remove_reference< boost::mpl::_ > ::type
                      >>(exec.seq);

        //ok, check if there are actually any.
        if (boost::fusion::empty(asyncs))
        {
            return;
        }

        ::boost::winapi::PROCESS_INFORMATION_ & proc = exec.proc_info;
        auto this_proc = ::boost::winapi::GetCurrentProcess();

        auto proc_in = proc.hProcess;;
        ::boost::winapi::HANDLE_ process_handle;

        if (!::boost::winapi::DuplicateHandle(
              this_proc, proc_in, this_proc, &process_handle, 0,
              static_cast<::boost::winapi::BOOL_>(true),
               ::boost::winapi::DUPLICATE_SAME_ACCESS_))

        exec.set_error(::boost::process::detail::get_last_error(),
                                 "Duplicate Pipe Failed");


        std::vector<std::function<void(int, const std::error_code & ec)>> funcs;
        funcs.reserve(boost::fusion::size(asyncs));
        boost::fusion::for_each(asyncs, async_handler_collector<Executor>(exec, funcs));

        wait_handler wh(std::move(funcs), ios, process_handle, exec.exit_status);

        auto handle_p = wh.handle.get();
        handle_p->async_wait(std::move(wh));
    }


    struct wait_handler
    {
        std::vector<std::function<void(int, const std::error_code & ec)>> funcs;
        std::unique_ptr<boost::asio::windows::object_handle> handle;
        std::shared_ptr<std::atomic<int>> exit_status;
        wait_handler(const wait_handler & ) = delete;
        wait_handler(wait_handler && ) = default;
        wait_handler(std::vector<std::function<void(int, const std::error_code & ec)>> && funcs,
                     boost::asio::io_context & ios, void * handle,
                     const std::shared_ptr<std::atomic<int>> &exit_status)
                : funcs(std::move(funcs)),
                  handle(new boost::asio::windows::object_handle(ios.get_executor(), handle)),
                  exit_status(exit_status)
        {

        }
        void operator()(const boost::system::error_code & ec_in)
        {
            std::error_code ec;
            if (ec_in)
                ec = std::error_code(ec_in.value(), std::system_category());

            ::boost::winapi::DWORD_ code;
            ::boost::winapi::GetExitCodeProcess(handle->native_handle(), &code);
            exit_status->store(code);

            for (auto & func : funcs)
                func(code, ec);
        }

    };

private:
    boost::asio::io_context &ios;
};

}}}}

#endif /* BOOST_PROCESS_WINDOWS_IO_CONTEXT_REF_HPP_ */

/* io_context_ref.hpp
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
*/