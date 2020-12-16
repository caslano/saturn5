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
tOJV9ERP1qMPhqMvVkR/rIUl0VEecfpdTPX9F8KH6KPqdzTHaYe9UL6ThCEYg2XwcZR2CLES9sMHVP+Wqv9ST6bBDeyNxD7iLGHvZbdEEA2JbkQCMZ6YR6wldhEFxHUigJveNYlWRAyRQUwmFhIbiH3EWcK7D/mIkA6cZ2AUXvyEZeBhc35H5onuacRm4jwRSVo3Io/Y1Z11Rdh7cO5EtCDiiPFELrGROEHcIiJ7chwiMoiZxFJiM1FAXCT8o9lPEpFHKUfMJuYRG4kC4hYR8ij7TGIAkUPkEWuJM8Q+4joR3os8xABiGpFNLCU2ELuIi0RIb87FiAFEBjGTWEhsJk4Q9j7kIZoQA4jJxAoinygg7H1ZXqIdEUfkEHkObZyr4EHiFhH5GOVHtCLGE7nEWuIgcYa4RUT0YzxEAjGNyCPyiX3EdSIkhmMA0YSIJpKIHCKP2EycIC4SuUw7gJ1nHaIPkUJMI+YRa4l84gRhf4JpEq2IGCKJyCHyiB3ECeIyEdKfciQyiFwij8gnjhK3iIgBrC8ihkgixhNziKXEDuIgcZnwHsg8EZ2IFCKXyCM2O7RRnmgZRFkRnYg4osUpyhwXEg2Pse5wB3GCuEVExDL/RAIxjVhBbCQOEhcJ7zjKjOhGxBEziR3EBuIEcZ7wj2cdEk2ITsQAYjwxk1hL7CKOEmcJy2DqFdGEiCEyiHnEBmIXcZYIGMJyEq2IaCKbmEmsJfYRl4mABJaHiCZGE/OIjcQu4ihxkfBPZL6ITkQMkUPkERuIo8R1wn8o0yKiiSRiJrGU2EucJW4RG2zM8zDWEdGJSCJmEkuJfOIM4Z1EHqIO0YqIJkYT84jNxFHiOhGRzDohook4IofIJZYSO4gCwvInxkO0IgYQOcRSYi9xhvAezjohOhEpRJ9T5MGlxA4b84T7iOuEfwplQLQg4ojxRB6RT5wgLhP2VOooUZXoRmQQ84jNRM4xposXiYA0pku0IuKIDGIysYMoIK4T3un0Y983msglVhO7iALiOhHS125pQcQQ44l5xEbiKHHv797fvb97f/f+7v3d+7v3d+/v3t+9v3t/9/7++T87MdRidbZ91mxAekZiWlb6iMwhic5/ZqXUHTwiOSWhbv169etFDa07MqtBVP2HdL/RTRrXzUqKz0xMqJuZmMLv0hMLc8RnZGQNiM9Kq8/n7LLqOdulaGZpEWiJdDwaDuY24EfxFm335CGZ6VnpQ7Mja/aqFdkzg2YPkscmpw2LbEsjCHxxLJPfUpcInMuwvCXVM7pPbPtevSxGmkWSenawGGlWSevUvhv3sMJUmoekde7RoWev7hZTXptKN6fZJa1n3z6mNC9J69GTVMbpLWmkdO7ZI7Ztp56d27a3OPJ0C3wzzKLb1Thb0sKfvB9gCVdeo09GG/mdfGEJJcbS8mwa/Y22QWmfYIjRJsPJdqQx1tJMWdLoCm8rbfPzfYFAj8K2mGS8TCXRy6Z/x67TdVtxavwjGT/DeRcznLfLcOOcbWemmdsKD2sv3yKgPa1AlUaLFDJflXlE5C3zlU/7CwtkPBO9mjnGz7jqBTvb0k51NqNSpA2eSPvft301vpPR5tyGou2wZKYPM+bHKtMO9ahsWUJJmefnhqdjfip7zLYV145RV8k3UsrkKNP4Tea5ltd3njb9jSCezIxIVcMEYk4HaTPCaN/fNJ+rne0aqTqartflHplOCI/Sbut2CGR5k4dkZySmkuZsl/Zbmf7DXleZvpHP0QBLZmq8+g7qZlUWb8q6IZW/ympeasp01ni+YnnJFm9/2HLd3tsS7dnWMs/TW6axkWGnyjRe9uoh66WwTIexeVP8pnann5Z8NewTLBc9cm0=
*/