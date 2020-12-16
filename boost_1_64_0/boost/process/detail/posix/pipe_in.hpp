// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_POSIX_PIPE_IN_HPP
#define BOOST_PROCESS_POSIX_PIPE_IN_HPP

#include <boost/process/pipe.hpp>
#include <boost/process/detail/posix/handler.hpp>
#include <unistd.h>
#include <boost/process/detail/used_handles.hpp>
#include <array>

namespace boost { namespace process { namespace detail { namespace posix {

struct pipe_in : handler_base_ext, ::boost::process::detail::uses_handles
{
    int source;
    int sink; //opposite end

    pipe_in(int sink, int source) : source(source), sink(sink) {}

    std::array<int, 3> get_used_handles()
    {
        return {STDIN_FILENO, source, sink};
    }


    template<typename T>
    pipe_in(T & p) : source(p.native_source()), sink(p.native_sink())
    {
        p.assign_source(-1);
    }

    template<typename Executor>
    void on_error(Executor &, const std::error_code &) const
    {
        ::close(source);
    }

    template<typename Executor>
    void on_success(Executor &) const
    {
        ::close(source);
    }

    template <class Executor>
    void on_exec_setup(Executor &e) const
    {
        if (::dup2(source, STDIN_FILENO) == -1)
             e.set_error(::boost::process::detail::get_last_error(), "dup2() failed");
        if (source != STDIN_FILENO)
            ::close(source);

        ::close(sink);
    }

};

class async_pipe;

struct async_pipe_in : public pipe_in
{
    async_pipe &pipe;

    template<typename AsyncPipe>
    async_pipe_in(AsyncPipe & p) : pipe_in(p.native_sink(), p.native_source()), pipe(p)
    {
    }

    template<typename Pipe, typename Executor>
    static void close(Pipe & pipe, Executor &)
    {
        boost::system::error_code ec;
        std::move(pipe).source().close(ec);
    }

    template<typename Executor>
    void on_error(Executor & exec, const std::error_code &)
    {
        close(pipe, exec);
    }

    template<typename Executor>
    void on_success(Executor &exec)
    {
        close(pipe, exec);
    }
};

}}}}

#endif

/* pipe_in.hpp
GTwHboWL4DZ4EXwNXgzfgivh+/AGGJ9AfQpT4M2wAbwFtoS3ws7wNngGXAunwjthAbwLLoR3w3Ph/fA6+AC8Bz4I18OH4D/go/Bj+Bj8Fj4OE/zUnzAJPgHrwqdgPbgZtoRPw27wGdgLboF9oOwlAjfACfARmAu3wnnwBXgznAofgtPgJvi57gEU69GxLzr+qAymI7yXya+lL/g+mqHfA51gDuwMp8EusEiPi/V4NuwKF8Hj4d2wu36fnwjLYF+4E/aDn8L+cC88BUYTj0yYAAfAVDgQNoOD9bvgNNgVDoG94VA4BA6Ho+AoOBGOhrPhWHgOPAMug+PgNbATXAcn6Pv5VtNnTl7rd1sKsknzYzffdz74BUyGX8K68CuYDvfCxnAfbA6/gV3gftgDfgcHw+/hMHgAjoI/wDHwJzgZ/gwL4UF4JrSiiS/wwBugF94Ho+B6GA1lnyr4NKwC5XvDE+qPlDIl6WmF8B4kvwsIvwm8BAb0K2AevALOhlfBpfBquApeAx+A18K/wxvgdngjfA2ugm/BW+CH8Db4KVwD/ZzzDpgM18JUeCdMg/fC1nAdbA8fgH3gg3A4fAj+Da6Hl6r7zXAjfAo+BnfAJ+En8Cn4LXwa/gi3wl/g85A63XoBdoDbYG/4DzgavgLHwTcgdaeENwM+BefBHXAhfBMugq/CpfA1eAHcDq+H78Jb4C64Fr4PdY82Hgp6PVz2aJur5epvMAfOh1PgWTAfLtLycDa8BC6A18KFcLW6695G2l9CXeiyt1F1LcdxsBqsAeNhTdgAJmi5SIR9YZKe/ygtl2lwLqwH58O6cKEe7462fnWfn/457DOElCLLkVuRMmQnsh+pk8ueR8hgpAhZhqxBypAdyF4kapLPSkMykMFIPrIMWYOUITuQPUig4SMJaYH0QEYi+chiZGXAjbitg7J30Z+831CDHUe+59B25COXPYdKkaX/4T2HMsZ4jnjfobQRsveQ275D/7U9h3pnen7XvkNpY/8zew9lvPnH7D/0ILL5T9p/6NVMz39sD6K/6v5Df+W9hxa8+fv2H3qBunA3EjvFZzVBeiMTkMXIdUgZsgux8nBHKn+Vv8pf5a/yV/mr/FX+Kn+Vv//nX9Sfuf8fw5Fn/EH7/52eXn7/P3SR+/+hc+7/Z+t8opMtt4wuSnTsB6h7WqFz3dNqcLJl1qpdEG3Jr4WuKQ9lrdqiVBkvHEhxRWvVmjV3Phfb3ow/S3NfX17cI9ekdZ8LZmzNfKXguVN0/sUCcU/zrvF0oW8qxgqtud3pKPT0jttzFEoLibu4H8D9UvFXPTBvQ/O50MT/PnHrQhNu88j1Vs2+LCvFJsp7nac1fZexZmx0howRbM3Ml/Rya6mG1kC/S/zu9djra85hFzk7/y6VuLcn/+LMXJITJdz0Cs8zStJACh1rQ10k56np/dJT1XKbD9tMwujiup4kcZW5gqskjJ89xob8FxO12YPNdWJjeSPWKTRrMp4j7qnenzxVZI2gZhiv8zHeicTGVV+Y6TZXFRvGVOm6O1UXtnFZc0dsDvhCa+4sjI5ccyddbVpE6bl8Cx9gBkmc7+i4WFTu80jUz2AM2vvl3Jsj55GM45h0Ra53Y9aHmY087lgn5jQKc8ckEbP2yRB0Q5Hz0cXrGjB+OCz5t+eshtZBWZxmr4PySmr5NRO22jqz9sOTqeXXUah2VPg6CvHostMc8/Q4/jLVuf7B4a93oGPoqaCOfEz5kY6hdx8rX/HYffcx9BWP6c+eG9BX+fmG7Jtn1Vt9+bvPxizbmJhT8Rhu97HaFY8ddx8jXvEYevex/n+9sfVHOgbdfUx5xWPx3cfcVzwnwX1sfUVj6I98TLw=
*/