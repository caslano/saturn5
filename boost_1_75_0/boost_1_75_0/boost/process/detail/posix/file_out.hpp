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
a7NkUx7ni+AYyQEDcrD8CTKxHoR/tNvL3b1iPokMZd2fBuRdfxq9B1I+2l2hkcEepI9rPeHfpdhSjy/nkTtfRPxFVLL8fQ1Ro9sJNJerDc2YjhCQntcesP02GS0MHm6ia4cCY7xwW4NlSwIxxoPYsDREPeQDRJj8PTryRPHfjy0Bv4OO0MGNQXca9feggJzrI5RlEBR83XsZ3PoKvgBvgHHP7zdJ9S49xIRUAEOrSx/u8i1esklqEEhgqmAAtr/ejoeyRocPMhzB7OKPaLGF+/n1PKgkOESAyH5hNdWa/qA1DlhTOlsMiBc4Av39H559UBZw6TZku/XtxQfmeop7B+O0JzDjYEU3YghqWJjdRxmgXDGnX2eH/AAI8jTcR2D/w9mcdzHbOP/zfth/6dX6r84+cyFbdgOi0X4R/RzjrZVOvmowz0m3mi7F3BshIUt7XSB+Jo2BR6edXEnXRr2MiuRdnyjFVCMuE72n/puZwXlNiV/BomhfMlg2tYwCtADxLAsQey5NOVEA0FLcq82b7yrNy+59et3s9iCWTwxFV4L1cbVb+HdCnS4EoHk+F9rMF/A9gO3LquFGwN3Rb2oKc7fzeVV8m6uFpNBcHRJ+qad51cp99Qx4oqjmiUcg9lmLdk0xlUfP4VngtwJ0S1SdwDd1lJ7vVz7rBdq94x3r0XUM0DpEJIpSndBOBDOX1fFPbNs3ZI2rqPDYmfl7
*/