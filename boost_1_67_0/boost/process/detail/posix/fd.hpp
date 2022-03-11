// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_FD_HPP
#define BOOST_PROCESS_DETAIL_POSIX_FD_HPP

#include <boost/process/detail/posix/handler.hpp>
#include <unistd.h>
#include <boost/process/detail/used_handles.hpp>
#include <array>

namespace boost { namespace process { namespace detail { namespace posix {


struct close_fd_ : handler_base_ext, ::boost::process::detail::uses_handles
{
    close_fd_(int fd) : fd_(fd) {}

    template <class PosixExecutor>
    void on_exec_setup(PosixExecutor& e) const
    {
        if (::close(fd_) == -1)
            e.set_error(::boost::process::detail::get_last_error(), "close() failed");
    }

    int get_used_handles() {return fd_;}


private:
    int fd_;
};

template <class Range>
struct close_fds_ : handler_base_ext, ::boost::process::detail::uses_handles
{
public:
    close_fds_(const Range &fds) : fds_(fds) {}

    template <class PosixExecutor>
    void on_exec_setup(PosixExecutor& e) const
    {
        for (auto & fd_ : fds_)
            if (::close(fd_) == -1)
            {
                 e.set_error(::boost::process::detail::get_last_error(), "close() failed");
                 break;
            }
    }

    Range& get_used_handles() {return fds_;}

private:
    Range fds_;
};



template <class FileDescriptor>
struct bind_fd_ : handler_base_ext, ::boost::process::detail::uses_handles
{
public:
    bind_fd_(int id, const FileDescriptor &fd) : id_(id), fd_(fd) {}

    template <class PosixExecutor>
    void on_exec_setup(PosixExecutor& e) const
    {
        if (::dup2(fd_, id_) == -1)
             e.set_error(::boost::process::detail::get_last_error(), "dup2() failed");
    }

    std::array<int, 2> get_used_handles() {return {id_, fd_};}


private:
    int id_;
    FileDescriptor fd_;
};


struct fd_
{
    constexpr fd_() {};
    close_fd_ close(int _fd) const {return close_fd_(_fd);}
    close_fds_<std::vector<int>> close(const std::initializer_list<int> & vec) const {return std::vector<int>(vec);}
    template<typename Range>
    close_fds_<Range> close(const Range & r) const {return r;}

    template <class FileDescriptor>
    bind_fd_<FileDescriptor> bind(int id, const FileDescriptor & fd) const {return {id, fd};}

};


}}}}

#endif

/* fd.hpp
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
*/