// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_POSIX_FILE_OUT_HPP
#define BOOST_PROCESS_POSIX_FILE_OUT_HPP

#include <boost/process/detail/posix/handler.hpp>
#include <boost/process/detail/posix/file_descriptor.hpp>
#include <boost/process/detail/used_handles.hpp>
#include <unistd.h>

namespace boost { namespace process { namespace detail { namespace posix {

template<int p1, int p2>
struct file_out : handler_base_ext, ::boost::process::detail::uses_handles
{
    file_descriptor file;
    int handle = file.handle();

    template<typename T>
    file_out(T&& t) : file(std::forward<T>(t), file_descriptor::write), handle(file.handle()) {}
    file_out(FILE * f) : handle(fileno(f)) {}

    std::array<int, 3> get_used_handles()
    {
        const auto pp1 = p1 != -1 ? p1 : p2;
        const auto pp2 = p2 != -1 ? p2 : p1;

        return {handle, pp1, pp2};
    }

    template <typename Executor>
    void on_exec_setup(Executor &e) const;
};

template<>
template<typename Executor>
void file_out<1,-1>::on_exec_setup(Executor &e) const
{
    if (::dup2(handle, STDOUT_FILENO) == -1)
         e.set_error(::boost::process::detail::get_last_error(), "dup2() failed");
}

template<>
template<typename Executor>
void file_out<2,-1>::on_exec_setup(Executor &e) const
{
    if (::dup2(handle, STDERR_FILENO) == -1)
         e.set_error(::boost::process::detail::get_last_error(), "dup2() failed");
}

template<>
template<typename Executor>
void file_out<1,2>::on_exec_setup(Executor &e) const
{
    if (::dup2(handle, STDOUT_FILENO) == -1)
         e.set_error(::boost::process::detail::get_last_error(), "dup2() failed");

    if (::dup2(handle, STDERR_FILENO) == -1)
         e.set_error(::boost::process::detail::get_last_error(), "dup2() failed");

}

}}}}

#endif

/* file_out.hpp
TvQZjvdOKUnIpG+IfNdSJf1g/WB6rMcbaz9r7PreXvfQ2tbWkl8Hj81l9L2Dz5f+i46+an55YY/y/Ir8QFTOd3Nu/Zf68/xoHxq6bg6eH/EcJHZdp36+yxnRyCLrY60ts88PRxZZRyttmWkHlyGLrLeltsy0jZ8ii6zLGmTO7ywVxt5P7MXnh9f1DGPvI/ap54fX/WRj76XfGMy7xONb9/4fWseeUxyQb+35XHnr+dMn1TR+vmWrBa2/P9Y6/H/e+va6dez/nnXsJ3pu74mue3ffl+HY696/tMen8ny9EnrJ02GYYek8BEiyxc2Haaf6n3K8ToAHYTQ8BA/DiaE5AHCA+ovDZKu/VE/QXxOYDJvCVNgMNoctYAuYBvvB5vA0lYfSdfAH0vWFputLGA2/0nRt8+g3av2evxL2wtyNgJ+c9+eFv4cnwT/CU+FzcABMIv7BMBkOgS8iHwtfhlPUPV/dp8FXkc+Gr8G5Kp8H92F/Bb4B31V/H6n7x3A/8q/gu9DnCbrHwWQYDz9E3hh+DNuoewd17wg/Rd4THoKD1H24umfCL5Dnwq/gVHUvVPcZ0IL7YBTM1PXC9fUcv8YwAbaBybAt9MNuMAn2VHkvGA0HwVh4lrqPVfefQA+cBH2wUN1nq3sx3EP6ymCy1ntN6Fs0XKT17scUY/jJeZAe+BCsBx+GHeAueDJ8AnaBj8KRcCccDx+Hk+FvYJnKa9TfQvWn7Y7vzMdud2XoBVgOo+EFMHQOr3wL1u/KK8PP4ZXzalvCwbAdHAYz4HDYD46AWXAkHAdHwWKYBeeq/nI4Bl4Kz4Y3wxy4BebCbXA8fApOgK/Cc+Cb8Fx4CE6BX8Lz9XzemTAeFsEGcDbsD4vhUFgCR8FSmA3L4IWwAl4Bq+AtsBpuhfPgdlgDX4Y5cD9cAL+EU825YvodEs7BrIw4V6xay3kejIc1sAFcAJvAhbAb/CkcDJfCMfBGOFnlBXAjnA1vhYfhqND3PZih8cZgTpdYoYd2BQfBVnAUTIdD4MlwJOym8sNwceh7GLxJw6uPqdLwstGrD0fDpvAnMA2Og33hBFgIp8A58Dx4ATwf1sA8uACeA6+Gk+D1cDJcp+7aH/P95tj9cVv0AjwJJsN2MBW2h81hJ9gCdoD9YEd4msoPw70e/Taj32pWwn6YPdq+c72UG8yDHeBU2AXmw27wY5gBC2BvOAv2gUWwGJbAUlgBr4OV8GZYBbfAufBVtb8L34WH4fvwew3fCrQzmAKXwqbwEtgZLoN94Ao4AF4GR8Er4TR4DayE18Il8Dq4At4An4Vr4XfwI+jzEh+MhhtgPtwIL4MfwZXqvgreBbfDu+Er6v6Gur8F74Nfwa2wiQ932BJ+DFvDh2Fn+BjsCl+C0+FrsBq+AefBhXAhXASXwZ/CFXAxvFLDWwk/hHdoPPdA5Hpd6Ht92Mbluojlug0wAcbAOBin9lawPkyHDWCoHx+r4d3m0o931X12ToWNYAYcqPZRsBc8D/aG5bAPXAn7wqthP3gN7A5vgj3grSo/DFeG3gXru+aVsCFmaSh+7V96wLawJ8xQe2+194W9YD/YH2bB0+B2eDrcAQfBx+EQuBcOhUfhMN3PZDiMg5nm/qLvZWFDl/uLR8vZCxtAHzwMV4Tef8Jr1F8DzCL1d532M6thU7gWpsF1sC+8GY6FG2AR3AjL4K2wEt4Jq1XvIng7vARugj+Hd8BVomfng3eB7vdJPT87wG9hNPwOir8ofQ+n7/5WwiWYdvrSaKv2v4/BzvA3sCscrf3ILm0nT8Ch8Ek4FT4Fp6leAfwd9lI4CvsF8Cw4V91r4NO4L4PPwMvgH+Gd6n43fAH7r+HLcBt8BT4=
*/