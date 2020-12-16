// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_ASYNC_IN_HPP
#define BOOST_PROCESS_DETAIL_POSIX_ASYNC_IN_HPP

#include <boost/process/detail/handler_base.hpp>
#include <boost/process/detail/posix/async_handler.hpp>
#include <boost/asio/write.hpp>
#include <boost/process/async_pipe.hpp>
#include <memory>
#include <future>
#include <boost/process/detail/used_handles.hpp>
#include <array>

namespace boost { namespace process { namespace detail { namespace posix {


template<typename Buffer>
struct async_in_buffer : ::boost::process::detail::posix::handler_base_ext,
                         ::boost::process::detail::posix::require_io_context,
                         ::boost::process::detail::uses_handles
{
    Buffer & buf;

    std::shared_ptr<std::promise<void>> promise;
    async_in_buffer operator>(std::future<void> & fut)
    {
        promise = std::make_shared<std::promise<void>>();
        fut = promise->get_future(); return std::move(*this);
    }


    std::shared_ptr<boost::process::async_pipe> pipe;

    async_in_buffer(Buffer & buf) : buf(buf)
    {
    }
    template <typename Executor>
    inline void on_success(Executor)
    {
        auto  pipe_              = this->pipe;
        if (this->promise)
        {
            auto promise_ = this->promise;

            boost::asio::async_write(*pipe_, buf,
                [pipe_, promise_](const boost::system::error_code & ec, std::size_t)
                {
                    if (ec && (ec.value() != EBADF) && (ec.value() != EPERM) && (ec.value() != ENOENT))
                    {
                        std::error_code e(ec.value(), std::system_category());
                        promise_->set_exception(std::make_exception_ptr(process_error(e)));
                    }
                    else
                        promise_->set_value();
                });
        }
        else
            boost::asio::async_write(*pipe_, buf,
                [pipe_](const boost::system::error_code&, std::size_t){});

        std::move(*pipe_).source().close();

        this->pipe = nullptr;
    }

    template<typename Executor>
    void on_error(Executor &, const std::error_code &) const
    {
        std::move(*pipe).source().close();
    }

    template<typename Executor>
    void on_setup(Executor & exec)
    {
        if (!pipe)
            pipe = std::make_shared<boost::process::async_pipe>(get_io_context(exec.seq));
    }

    std::array<int, 3> get_used_handles()
    {
        if (pipe)
            return {STDIN_FILENO, pipe->native_source(), pipe->native_sink()};
        else  //if pipe is not constructed, limit_ds is invoked before -> this also means on_exec_setup gets invoked before.
            return {STDIN_FILENO, STDIN_FILENO, STDIN_FILENO};
    }


    template <typename Executor>
    void on_exec_setup(Executor &exec)
    {
        if (::dup2(pipe->native_source(), STDIN_FILENO) == -1)
            exec.set_error(::boost::process::detail::get_last_error(), "dup2() failed");

        if (pipe->native_source() != STDIN_FILENO)
            ::close(pipe->native_source());
        ::close(pipe->native_sink());
    }
};


}}}}

#endif

/* async_in.hpp
9wN2RJOJ7wd0xk6YGTujB/bCV7APlsa+WAu7YiiGYzvshu2xO3bHaByNMTgbY3EuDsJNOAy343D5fh0xy/uy5D2AydiGlCSnH3ibfHVxKXbCd7AHLsfBuBLH4yqcg+/ialyLH+B6/Bg34jncjDdxC6bgNryD2/GufP6rfO7CRu1AX9yFuXA3NjVznmJr3I/h8nkUluD7rQ8e4HlfPIixeATfwKM4DD/B4fgpjsRjOAo/w1l4ErfiGfwcv8LTeBbP4dd4Gy9gZus8QZgNL+OreAXr41VsgtcwFH/Avngdp+INnIk3cQnexkOYgqfwFH6JX+B5vIM/4l38A++jkxPXkk4cH3xgXT8+wmD8DVvjY+yFCvli0IwD0IKT0QXnoisuQDdcj+54FL3xB8yOt9AH72BOtDhz3xPmw9xYCPNjABbAUPTH9lgQw7EIDsRXcDYWxXn4Kq7CEngKy+DXmBXvoAf+ihVR4Xwth54YKP+uxWSx3U/AMZa/QfvwJII4D+p6eL9wDhbG1XLer7XYEDfgQNyIo3ETzsRduAm34hEsbmG7sCR+j6XwLpbGh1gGTZwfr6ErlkVPLIe5sAIWwooYhJWwFgbK8zsI22NljMTXcQhWwSlYFedhNVyP1XEL1sCd+BHbmYR7cR/uw7O4H7/BQ/gzfowP8DC6y3m1vPA45sbPsACewBJ4El/DM1gFv8KaeA6b4tfYEr/BzngRu+Ml7IuXcQBexWF4DUfh9zgFf8AEvIGL8Ca+g7dwI97Grfgz7sEU/Bjv4Kd4D0/ifTyPv+B9fICP8BE+xd+Qc1z5HQvhE3wVn2I5Oe9WJTRjLbRgPXTGFuiCbdANO2Mm7I5ZMBrdcSB64JuYDcehF05Bb0xAH5yHOXAx5sSl6IdbMTfuwLx4HPPjKfTHb7AgXsHCeBOL4M9YFJ2tnyd0xeLohaXxFSyLJbA8VsQKGIgVsSZWwtoYhI2wMjbBKtgaq2JbrI5dsQZ2w1o4EuvgW2j9HM3C+jyfiw1wKTbGJGyG+7ElXsdQdHfh7ygWwDZYBEtgIJbEqvi+9fOKH2Bj3IEh2IHXB2BHHIVhuBi74DvYFbdgOL6P3fBD7I5J2AOPYU88gf3wDEbjNYzFX3AQ/o6DMTs//N7AnDgE8+MwDMARWBVHYwMcgz1wLEbjOByIM3EozsJFmIjL8G1chfNwPc7Hz3AhnsJF+BUuxTu4DB/hO/gHrkEPN77fsCiuwxK4HgNwIjbGSdgZJ+MonIJv4TScjCtwIa7Ed3AVrsYNeBU348+4BbNm4nsSc+A2zI37sRAewAZ4EEPwCPbGoxiNn+BA/BTfxM8xAU/gJjyJW/EU7sAvcC+exuP4JZ7Br/ABXsDXMvM9hIF4FdviNeyJ3+E4/AEn4k5cirtwK36IX+BuPId78CLexCv4Iz7B2+iche8hzIr30B/vYyn8BV+X8cbyeXN8gu3xD+yLTzEaf8VR+ACn4UOchYqZ70F0wp3ojAfRFc+gG97ATPgTuuN9zIaP0Qtd3fn+wVcwOxZHHyyDflgHc2NbzIO9MS/GYgGcjP44HQvibCyE67EwvodFcDsWxV+wDPpn5e8fVsXyGIwVsDMGYQS+jnFYDcdidVyONXAd1sb3sA4ewGA8g/XwPNbHO9gAf8UmaPbg+hwzYTP0wOboiS3RB1thYQzFktgOQ7E9hmEH7IodMRLDsDd2wVjshlOxB76LvXA9RuFH2Af3Yl88izF4H2PRgwu+OCyKb+BrOAQb4kjsiG9iNI7BtzEeN+MkPIST8ThOwWs4G3/DRMzqSX0WBuACbIFLsAcuxd64DKfgalyI7+IyXIOrcANuwI24FzfhJdyKv+I2/B3fR8U=
*/