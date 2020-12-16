// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_NULL_IN_HPP
#define BOOST_PROCESS_DETAIL_POSIX_NULL_IN_HPP

#include <boost/process/pipe.hpp>
#include <boost/process/detail/posix/handler.hpp>
#include <boost/process/detail/posix/file_descriptor.hpp>
#include <unistd.h>
#include <boost/process/detail/used_handles.hpp>
#include <array>

namespace boost { namespace process { namespace detail { namespace posix {

struct null_in : handler_base_ext, ::boost::process::detail::uses_handles
{
    file_descriptor source{"/dev/null", file_descriptor::read};

    std::array<int, 2> get_used_handles()
    {
        return {STDIN_FILENO, source.handle()};
    }


public:
    template <class Executor>
    void on_exec_setup(Executor &e) const
    {
        if (::dup2(source.handle(), STDIN_FILENO) == -1)
             e.set_error(::boost::process::detail::get_last_error(), "dup2() failed");
    }
};

}}}}

#endif

/* null_in.hpp
i520aRwvdmP9Z0XYBXMWO22rHS52fJ+FlXdpgxGbNtgsEZta/g4S1gD/POrEZc353kwmv6IX7gyNSbhFxySEbNZhczM6bJ6vyGY/NqsCNjXOHeMY22Dyg/e8sDXCxjSX6xgWRucWJgzv4YThdYSRomFMaEHYiYRRZcn8OF8Ny4QTEd/F2I0O2EUvya8oTWuwaR7IG//5e0I290TYvIBNO7/YvF2RzV7b5rmKbJKY/NYicK6q5z8RslkXYdMZm3vRYbOhIpuxLfVc8ecPjTzXKd7R/ks57ua31z98SOUGW+T46cQAD182OekiryBJfvvvn5CWyRzL30G20mOnNEt0srw8pmyN3+6E/6jqHtT1X59UKcb/8y7rwF6g8UpE+iE+FXRGnkH8IsEwthDWVm3vdebb4xpmG/SvyN9BHo+/Q3rcFrdmSDsdI9AeOm0yOO6ABOI8V+O8FbeO6DqJP+wTnWkKt+2MexcN+zUdV6DxDUt3L/S9kcB5u6p9NyE6GJBnTR5BlROS7fFHcZ5fa+eOA5SHjvZ6mJ+3tPf6z1Bd3xZmLcrOluoa2zqzJlSirTP7yHtsnVlLc29zozNrae60dWYtzSdsXVuzL73RdewS0i2xdSZ+s22d2fs+3daZ8152nNlD3vjtZutMnFvaOuM3zdaZOMfbOhPng8caXZuQ7gOjyzDp2GLrTFzW2zoTl9W2rr3JF1vXzuSLrTNxKbV1Ji7ZRtfexOUUW2fi0sXWmTxtZutMOaht60w5qGLrTDq+b2Z0Jh17bJ1Jx05bZ9Lxsq0z6RhuztHOpGNrM6Mz6dho60w67rN1HU0+2zqTjuttnUnHcltn0rHI1pl0zLV1Jh1Fts6+HkbX1qRjqK0z6ehl60w6Otg6k46mts6k45Km5deznWPrTJwn2zoT52Gtw9ezTUF3UXvR5dD7KcMjQvqFbURfnMvowWCrQjCM4HudVVjEa2c+1vHo5Dv4CNePow9J+hrOSkRn+iC0Pwx9cNykvBqKLsPogu9wqejS0LmNo8RN2hulry28LVLO+4LxZ9rexM9i06cV3o7C+aXNIbLPcD86Ge8lbQfBsLea8xaHnfNVE7b9DS15hd6fGt4/eUC+7dHptyE6+aay+wN17VNjp98UmvZVJg7ObwTt07TzUd/9u/jPCpYV64nk4PEHzcOPB7cIHi9KCx9306Sb2evVqgbXwa7pvGeyIaqsGZdXUKqjs2dOn55VzCu1Y3yn3QdRG/o644cN/13G4Wh4HjO2wSPtKa7jcNQ2csyO+zgcp+0uGQMjja2u43DUNnJMtWljeFPcZ3vcxuU4/SZy7JHr6j4uR23Rqa25tu5jc9Q+fLyAZZl1fyPWk5W4fSl+sjwuY0/MmsAu403M+sQVjftOlGvYzSPH/BUVOMbVZcyC+c44KDbVTfuHWb9YroVtV1vs4hxhlZRmlc405WC/7rOS2ZEyQ+3bXcaCdzDfKKvtd3mxaYbNneji4hqUs0lXm7GhcDynxsX64jwLM+NivdjpOqDY235S1M9i/KyV77lpcdFVLBP2HRHnX4PdibJuYU45myEc19Lx6j2weR/2VF6AnJQsbnLcS/XOv3u7uEeus4zKdZ1gqc/k3rTrbe45dNxzqotzGT+RALmH0Mk95DZm3YyVcNZtKTpWIrwe0zrXOe5A69G9RqdlVvV7jF7Lq+oPlB+noHWn6k050rpNxyp07m7J7xnEhzyNtCXNE7po3VaYnVtSEjas1q3OiazL1L9jDXV5xrnUZW628uxzqcvcbCPads4T95qudZv6tcfGOZ5RbvWZ2psxBB7z/Hat04x9ignf2e/gXq8501NQV9rnS+c46po8cf+7a/t9bY4=
*/