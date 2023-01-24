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
eV6bsuzM7LTsB4gweCSONPapqQH2hG48/bXLavY80C+1NtxQz2ZtZYSk3cCswDqc4B6TWhkG5R+W7AzxbURx0SW/t7lGBNwuYnS6fr5wWuCLho3gQAVP+aIeV5h3x3ldlKZsGQxyLXFEVyL3KkbyoFnPMcsOrct5CX/WYltZuZSh7l00c+so2E/rfibkQtK6KW3z/C3ZTtNmNzh6J1Wubh30+tk18svlf9Fnvu3yMpPCUx0Vj1gqMBanwYp+T6of5lrCFNxjMtd5XqYIZj8B2MK6FRG6EgE46uTQ8VUCi7VEewW+0mwIbNFT82wv1cbq642A7eEXNhBLK3ddfhFAdjKG6L6xnB0YFrZq3GTKUwMubrPvnHzYPH8vFH0/MsPUmgkt1wYc5rF7jKK747F4Rcehw+fPSdzDc80SGg3OhSLnPIpfgD9dzJvA41vGhsM96j2RvK+Ez8oPhufL8URGAVKV+XVvx2GMFxjEz5+6Jyb6n654ln+kW8Ts+Pqwdh136IyGuex05YCjvZQWlw/IdZNdbvAWJ54ktjqI/fc7cKc7a7D26zR7RvMNkomTAAx/YVgCk2uRa+22O/p/vuzgSHTZZPfZSFWpbfqrX93SqjNPrOCq6v09u8GAV3j36pzAA3NMQ8TynbpSEp73u0j37CZQCWuKuiela4V0lWSVjLVY8oxE5+o4E4MOMcOaEQ6sAFmpf76OGGtAbTvs
*/