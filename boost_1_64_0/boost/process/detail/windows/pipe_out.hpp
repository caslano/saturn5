// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_PIPE_OUT_HPP
#define BOOST_PROCESS_WINDOWS_PIPE_OUT_HPP

#include <boost/winapi/process.hpp>
#include <boost/winapi/handles.hpp>
#include <boost/process/detail/used_handles.hpp>
#include <boost/process/detail/handler_base.hpp>

namespace boost { namespace process { namespace detail { namespace windows {



template<int p1, int p2>
struct pipe_out : public ::boost::process::detail::handler_base, ::boost::process::detail::uses_handles
{
    ::boost::winapi::HANDLE_ handle;

    ::boost::winapi::HANDLE_ get_used_handles() const { return handle; }

    pipe_out(::boost::winapi::HANDLE_ handle) : handle(handle) {}
    template<typename T>
    pipe_out(T & p) : handle(p.native_sink())
    {
        p.assign_sink(::boost::winapi::INVALID_HANDLE_VALUE_);
    }

    template<typename WindowsExecutor>
    void on_setup(WindowsExecutor &e) const;

    template<typename WindowsExecutor>
    void on_error(WindowsExecutor &, const std::error_code &) const
    {
        ::boost::winapi::CloseHandle(handle);
    }

    template<typename WindowsExecutor>
    void on_success(WindowsExecutor &) const
    {
        ::boost::winapi::CloseHandle(handle);
    }
};

template<>
template<typename WindowsExecutor>
void pipe_out<1,-1>::on_setup(WindowsExecutor &e) const
{
    boost::winapi::SetHandleInformation(handle,
            boost::winapi::HANDLE_FLAG_INHERIT_,
            boost::winapi::HANDLE_FLAG_INHERIT_);

    e.startup_info.hStdOutput = handle;
    e.startup_info.dwFlags   |= ::boost::winapi::STARTF_USESTDHANDLES_;
    e.inherit_handles = true;
}

template<>
template<typename WindowsExecutor>
void pipe_out<2,-1>::on_setup(WindowsExecutor &e) const
{
    boost::winapi::SetHandleInformation(handle,
            boost::winapi::HANDLE_FLAG_INHERIT_,
            boost::winapi::HANDLE_FLAG_INHERIT_);


    e.startup_info.hStdError = handle;
    e.startup_info.dwFlags  |= ::boost::winapi::STARTF_USESTDHANDLES_;
    e.inherit_handles = true;
}

template<>
template<typename WindowsExecutor>
void pipe_out<1,2>::on_setup(WindowsExecutor &e) const
{
    boost::winapi::SetHandleInformation(handle,
            boost::winapi::HANDLE_FLAG_INHERIT_,
            boost::winapi::HANDLE_FLAG_INHERIT_);

    e.startup_info.hStdOutput = handle;
    e.startup_info.hStdError  = handle;
    e.startup_info.dwFlags   |= ::boost::winapi::STARTF_USESTDHANDLES_;
    e.inherit_handles = true;
}

template<int p1, int p2>
struct async_pipe_out : public pipe_out<p1, p2>
{
    async_pipe &pipe;
    template<typename AsyncPipe>
    async_pipe_out(AsyncPipe & p) : pipe_out<p1, p2>(p.native_sink()), pipe(p)
    {
    }

    template<typename Pipe, typename Executor>
    static void close(Pipe & pipe, Executor &)
    {
        boost::system::error_code ec;
        std::move(pipe).sink().close(ec);
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

/* pipe_out.hpp
KTmNm9jM74nqZ35MdOP13jOn2ww916bMrPoQuo/6q9jXsJexh4o/ARb+KDNdHw6Teoav3PKCiPG91W9Fp429lr2snq8y+xVs8svXj9/6OakzVnj38gfRaWp3re9+KteVxT7Ewt8QU1yPyNyuPGf93u9vYh+r/bxQwz0nFm7hpzYzrtOo9U2ZR8NPv5qy1qL9tMl1kNhHW/ipzMxz5URdvaOGn6HiR4D2M8jgZ4yFn9rMuD4uZcc9Tjhc03Wmmb/Xc0xN78zpPYenxO9W9pr2MuK2VyXxn6zprg+jxX+7/bwtxPyusF7PeUB01pMG/ux0G6fPJ31L1U17IcJvN69FOvc+v6v6HuHFfgfYP7R8Ldf7mY2bYm02ay5pjtklCZctNSPN6iw93Sc2z89I/qYsYKbLgn43wNfv1vonHJIvdf0jczl6LUjylZjFuNcScGp9fqrUPc5wEwbTO/IpzkRZ6kN44GLVL4qtZahbpowiDNZ7DRxumonuFKu+Ef789bxMOEwUnbvoG8Wwv7IxXxevY33OcK077x/F1ip+/whdc/9Il4k1YteIch5g2UfCrfc+kqF8fCR639ob2x62WkfAH+/9pGjYSuxftIfQT0q1d9DrBqdry7ukd9RPcpW1i+J2GTHL4TtYQfpssg5yr7E+O+wBtgY+/rZ2iMOPRRFS7nOSDe2LXx11RruKZym5rqPHESXl2kef6T5brv28+tdd7P0Jo9H9XEJXkVPGe0m/KYB2sSDZ3Zc7ofpyB0YyRkt29eVO/M/6ctEwobbuy5nTXsJUyL1zk3VfLt2yL6f0VifrvlywqS8ncTue7OrLtfPalxtWy92XU2vX3Nsdl98MZyn+zu8/kOvlmKND+oXxO5LfyA3kI8NZ5AG36c/Nq/P/059z1H8Dann2vUZwbey79avt2RcbyrWx77aEa6P750z6W2pbn0HC93Dkry6W9RRvEqHtdXT9qrbA2Qx1h9PEOAceDr9wliF7AXe0qmvx0/wOfXYax7hYr8dqfclbf8p7MuT15AzdBzop9n/oOvBTuc6nnsrU5XpoXZkfsKp78d9yHkT3AQvF/jfbSnXuw7XwW8dOp0Xnqo1v1RveYSCQhjJ5TnQuccpeqOqvmOY6iEsLykawfP9An+kq7yYeNsxNr0KWqnrg2xB4h2eJOMoF6aHnMCoYy4V6ptZz1/o56TUfngfm8jxMbbr7XIiyci/W+WPUXIcaL5xAwfH3EGJHHnSQfF4o+rnjJ8qbgzbTWWrSHkt4vxe96cxFc1IHkmy9fx7/7mz9X+nr+vDQX5/rep+ed7Q4HyzA6xl16mw/ySH0RxFfxXWsOY2sJ2kwgbcTkzjRcPLEHM4ozc7R7+JP8VPvKmameTs7Gj/MfQp3vo6GY8R+Di2Vv0U6aPfGM911Gfun2PWkFxRsOBdeTlnU9UCG6My2VeJ/MYNnxWyQrYP5PHnDOv040QmQ81MKySMb0tX5KYFtgkoHdZfzU2KKcX6K+1xcdx9ws/jd0Vm2dXjut7XkflZnrpSD20QnzHmt3fT2mPN/uhhnXzn66h3rq7664bvm+Ocya4GRnlN0POMI/YxNfXZ5luqbLPVM596q8sU3w+RvpipfDyCDKV+J9Z15y1G+yFycPlq8b23gTuengTIHKl7o/JQh9sm2HpbnGmr3lt+ImC92ceL3nhAMxG/Deo/Yl5H1nnaUmc7E7aa8s9VY3tmq6n29R/TT0bdFoV8y3uJcD8lDkndOIfYoeAfv11p9J4T0wUzSx/P7J+OdHmyzkz/gFtg2hjrG+UykjCeJV8ZnkpJlXNf9VnTX2cvwVJ5F1FyJ8qOeTnO3mV2f845f6bxM5rWtRd/cNic=
*/