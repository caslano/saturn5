// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_INITIALIZERS_ASYNC_OUT_HPP
#define BOOST_PROCESS_WINDOWS_INITIALIZERS_ASYNC_OUT_HPP

#include <boost/winapi/process.hpp>
#include <boost/winapi/handles.hpp>
#include <boost/winapi/handle_info.hpp>
#include <boost/winapi/error_codes.hpp>
#include <boost/asio/read.hpp>
#include <boost/process/detail/handler_base.hpp>
#include <boost/process/detail/used_handles.hpp>
#include <boost/process/detail/windows/asio_fwd.hpp>

#include <istream>
#include <memory>
#include <exception>
#include <future>


namespace boost { namespace process { namespace detail { namespace windows {


template <typename Executor>
inline void apply_out_handles(Executor &e, void* handle, std::integral_constant<int, 1>, std::integral_constant<int, -1>)
{
    boost::winapi::SetHandleInformation(handle,
            boost::winapi::HANDLE_FLAG_INHERIT_,
            boost::winapi::HANDLE_FLAG_INHERIT_);

    e.startup_info.hStdOutput = handle;
    e.startup_info.dwFlags   |= ::boost::winapi::STARTF_USESTDHANDLES_;
    e.inherit_handles = true;
}

template <typename Executor>
inline void apply_out_handles(Executor &e, void* handle, std::integral_constant<int, 2>, std::integral_constant<int, -1>)
{
    boost::winapi::SetHandleInformation(handle,
            boost::winapi::HANDLE_FLAG_INHERIT_,
            boost::winapi::HANDLE_FLAG_INHERIT_);


    e.startup_info.hStdError = handle;
    e.startup_info.dwFlags  |= ::boost::winapi::STARTF_USESTDHANDLES_;
    e.inherit_handles = true;
}

template <typename Executor>
inline void apply_out_handles(Executor &e, void* handle, std::integral_constant<int, 1>, std::integral_constant<int, 2>)
{
    boost::winapi::SetHandleInformation(handle,
            boost::winapi::HANDLE_FLAG_INHERIT_,
            boost::winapi::HANDLE_FLAG_INHERIT_);

    e.startup_info.hStdOutput = handle;
    e.startup_info.hStdError  = handle;
    e.startup_info.dwFlags   |= ::boost::winapi::STARTF_USESTDHANDLES_;
    e.inherit_handles = true;
}

template<int p1, int p2, typename Buffer>
struct async_out_buffer : ::boost::process::detail::windows::handler_base_ext,
                          ::boost::process::detail::windows::require_io_context
{
    Buffer & buf;

    std::shared_ptr<boost::process::async_pipe> pipe;


    async_out_buffer(Buffer & buf) : buf(buf)
    {
    }
    template <typename Executor>
    inline void on_success(Executor&)
    {
        auto pipe_ = this->pipe;
        boost::asio::async_read(*pipe_, buf,
                [pipe_](const boost::system::error_code&, std::size_t){});
        std::move(*pipe_).sink().close();
        this->pipe       = nullptr;

    }

    template<typename Executor>
    void on_error(Executor &, const std::error_code &) const
    {
        std::move(*pipe).sink().close();
    }

    template <typename WindowsExecutor>
    void on_setup(WindowsExecutor &exec)
    {
        if (!pipe)
            pipe = std::make_shared<boost::process::async_pipe>(get_io_context(exec.seq));
        apply_out_handles(exec, std::move(*pipe).sink().native_handle(),
                std::integral_constant<int, p1>(), std::integral_constant<int, p2>());
    }
};



template<int p1, int p2, typename Type>
struct async_out_future : ::boost::process::detail::windows::handler_base_ext,
                          ::boost::process::detail::windows::require_io_context,
                          ::boost::process::detail::uses_handles
{
    std::shared_ptr<boost::process::async_pipe> pipe;
    std::shared_ptr<std::promise<Type>> promise = std::make_shared<std::promise<Type>>();
    std::shared_ptr<boost::asio::streambuf> buffer = std::make_shared<boost::asio::streambuf>();

    ::boost::winapi::HANDLE_ get_used_handles() const
    {
        return std::move(*pipe).sink().native_handle();
    }


    async_out_future(std::future<Type> & fut)
    {
        fut = promise->get_future();
    }
    template <typename Executor>
    inline void on_success(Executor&)
    {
        auto pipe_    = this->pipe;
        auto buffer_  = this->buffer;
        auto promise_ = this->promise;
        std::move(*pipe_).sink().close();
        boost::asio::async_read(*pipe_, *buffer_,
                [pipe_, buffer_, promise_](const boost::system::error_code& ec, std::size_t)
                {
                    if (ec && (ec.value() != ::boost::winapi::ERROR_BROKEN_PIPE_))
                    {
                        std::error_code e(ec.value(), std::system_category());
                        promise_->set_exception(std::make_exception_ptr(process_error(e)));
                    }
                    else
                    {
                        std::istream is (buffer_.get());
                        Type arg;
                        if (buffer_->size() > 0)
                        {
                          arg.resize(buffer_->size());
                          is.read(&*arg.begin(), buffer_->size());
                        }

                        promise_->set_value(std::move(arg));


                    }
                });
        this->pipe    = nullptr;
        this->buffer  = nullptr;
        this->promise = nullptr;


    }

    template<typename Executor>
    void on_error(Executor &, const std::error_code &) const
    {
        std::move(*pipe).sink().close();
    }

    template <typename WindowsExecutor>
    void on_setup(WindowsExecutor &exec)
    {
        if (!pipe)
            pipe = std::make_shared<boost::process::async_pipe>(get_io_context(exec.seq));

        apply_out_handles(exec, std::move(*pipe).sink().native_handle(),
                std::integral_constant<int, p1>(), std::integral_constant<int, p2>());
    }
};


}}}}

#endif

/* async_out.hpp
MPgEHAUHwhvgIDgb5sA/wGvgIpgLl8Kn4Bq4He6GO+ALcBc8BHfD7+FeGKH84sTDfbASfB62gS/D7vAVmA1fhf3gQTgQHobD4WtwAnwdToZvwOvhETgTHoXz4FtwMXwbroTH4d3wHXgPfA9uge/D7fAD+Cz8EL4OT8G3lN4JuB9+CF+An8KP4Tn4CXQovzoV4Z9hZfgXWAeehhfBM/AS+AXMgF/CLPgV7A3Pwqvg1zAPnocj4c9wsvK3Mwu64ELohmugB66HYfB5GAEPwCj4FoyGp2EM/BLGwp9gGeiVeYT9Ar81ON7gdzANxiv/PAmwI0yCXWEyHAnLw0JYAd4G0+CdsDJcD6vArbAqfAlWh4dgDXgS1oSnYS3oCeN+EZaDdWF9WB82h41gP9gMToYt4BrYEh6Dbvg5bAzPwibwG3gZ9HiZj2ASTIcV1XZd2BE2gpmwFewE28AusB3sCrvCLJgNu8G+sDu8GvrG3Qjlh2cy7AtnwH5wDuwPF8EBcBW8Gp5VfkZue40v2sCzH/+yr5GeOKTaBeM+cRkNCJ0J1xCmfFJqG/f/aBtXaWCpfVypfdx/h31cwDbutk9K7eL+G37/3PX/MRN+j/X/Cka0PF98nWfLLsP/MZqcgqKiwLr0zTa2AciCbQOQBdsGILOxDRC5rW8A5Da+AZAF2waILEx9xy8je0BPq9yrvsun5DqPcOu3BpUsUmTZmX6pKY8KXp9X8nJ6fd7UraDW4rEsyMy25F1RyVUuWl5JyX1eDXpZykxV8vTevellU56m5B0ze6dndKY8Ja+s5L26demWieGBNU0VyzcLrfJqKg3t7WVtV03V5x0zO2ndWkpXpJY8aos8IzurU2aPLEsedaw2CUp2UbD/BiW/ONiOQskbBttdKHmjYPsKJW+s5SXzb+LPpwe7pLt1DDQVuViBaFkr/a1KM31r6zcoLenb+Pd/D6vsEpF1yu7RzUx/qX+s9enQNTPDOjYv02MQGxVLHm3VOMzo0lPL2pt2G1qWrvYTli86zw4lbWS0vKv1+5cW+UGvjO0cTGKye1nG8SEl79kjq0uGZbweDsj7ZPfs0StTj7/XlNw/vsXwxEhTca+XiONg7Flyf76h4hnrXUim0x0pma5zj169S+T7Zsn4zG7pXRiC5jFxtGQ8vWnm/ZaKo/N7ZGcygLv07pKRnqXj3w7EiwURtjGZGVf0suR9TMUz8v2RlryPB8flpGdlWeLfKdG3OrmOf1fFZ/bviUKX3kpRl/1eoG7dO3fpQHR6dzPuRFBct/SeOu6kiuvfvFHrnF69s7swGgNlvq/L7J3JId6Rypfoyz+p+D69MtmBWb3Te5n1/aBke5RZlRn/oT9e9UWvXr4hb40/peJ7Z/fp1Zui1VDU8R/54zmCuvTO7JDTuEmrnB7ds8w2f3xBvFnvT4LiWjcx8/00UO/07N5d0n37Kp0D3Iz/zB/PjMIO7O2P7mWJ/7OOV02T4cu8quL/UnL8pffp3TknK7NvZpZF57TSYYT06EfX9ejPgAg6F3weOEaz0ukXU35G5MwSnZk/RB6O3N6eK1Hsufz+cNZEGPJrRnAQmhIeTGIuuE0egXAlkZM3pISvkXGjrD5f3hW9mrb2XJIH/wK2Vg5la2Vnv6V19ZomFxrjzG9vvS3x1dW2PPjj/079vv+kOM4Fas0t+DrLfC8+eD1F2qLXU6ij1c+/tnnbIqs4zCFpnOcVvyUm7nbdR3Y2b9rXiuiR6r5Ul7V/kNvauym7M/b1Clm/D8vCa/B5VyWjvbu2ERV2sVFBrVl/tkps2Yipw+2ly9nItUj5abEvU8nt/LRo+7xVa33xpxwJyjah4Wrx6RNb21gc7cs=
*/