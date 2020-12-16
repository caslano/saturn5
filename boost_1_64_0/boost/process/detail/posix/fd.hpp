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
Bm+CZ6I133O7NY6V12ZvD9EdjnY7RoXoG9lubzapjvf0YE7TAE7pTWQ+8lpH/iLHWIwPSOs8iet3viTSeY2zTpzjHXT3ortEdB/xRaO7Al1T7zqmSdN+fLGk52OrE3W3iLq7zmqsbrXraqRntoS/k/CvlvA3+76gbmoIv1XkfUdHe5VFCwqd+2FPkTpuKOOUZwlnjYRzq+8P3tvsNJoxHfuYoHOR6DzuiycvlxOXy947pq2/LmnuT3q4z2oeh4j/mciC9dJV0pDBdZnCXAvmOVitmau5VuI7SHyTRP9936nE92sTn503Z34ekbBOMuOkPPGb5G0V1gc86xltDTR9wBqPoz50TCvnXBP3QvH/hK8+ca/0oefsF/S55B30zP3bHtOaPqm3xHmKJ4b4mnN/nMMMzwbOfkf3NtlNOLdIfOt871KPs5xtyoxz7bwulbJtKX634fc68XuH7xB+q9SvuT4rqwrocUX3BXTniO6LnF0fxzd851ixwqwPKi8KjvOakhN5jjZ9wu3WGOKtttLxZ/ZQMelaJP785rpbKfbujJLSpfxGpkmbquABKrhHFOmZzJihccQ50Rizvvxx+2xo4W8wq3Xt9guYyxzruf+AoYvH4Kb7E4/yHu8YILgO2z/bXoc9aGbtdbVdbVmfkKytLesdkjW1Zb1Csga2rGdIFmXLepj1wTNqr6s9aMsyQrL3ZtReV/ucLTNp3jUzfA1tA2TRReFrZTfN/PvWyqYh++A7Xbcafs8U/XfC3KgTynlRS+pWxkbar9NI86uK8CJ+pF3QVvAjbYX09k9aEEyvtaSFJfYttt1x1vSJnznsvn7rWOvJ/nnrxo61TmvY7ID8UJ+C8deu7P+ndt8/OG3YgZnpJ74OzH0d1bHX27mvo/rPrQ9zX+914uvn3Ne9nfh6rBNdH+a+zuzE1425r4M89vo2is5K9+h7K33nuhO2waToPNA7A/OH4b2wEbwPtoRbYRt4P+wFH4TD4XY4Hj4EZ8GHYQncBS+ET8GL4W54Dfw9vA1+Be+AR+Cd8Bk4mDT8EWbCl+E0uBfOgq/BRfANuBi+C5fB9+DV8EN4M/wIPgo/gXvgp/BZeAjuh5/Dj+EReAB+Br9XeYwXOaScmI+t70z0fdFO2BOzUcupOXrtYHs4AHaCk2BnOA2eAstgN7gYngqvgN01v73gFtgbPg37wpfgaXAfHAKriWu45vtM+BUcDS3SOQY2haNhOvwJ7AtzYX84Hg6GE2A+nAinq7wQToYXwvPgYng+vB5OhbthAfwzLISfwVkwhfZcBDvDYjgBlsNSeB5cCCvhxbAKLocXwavgxfBWeCl8GF4OfwuvhM/CX8AX4TWwF+V9HRwIV8PxcB3Mh7fAcrgezoU3w4vgLVpvK7yh50qo9TZG1w5aeo55azgGdoWT4C/gZLgengvvhTPgw3AW3AVnwydhCXwGlsFn4QVwL6yAf4ZV8G1YDd+B8+ABWAM/gQvgl3AhPAIvhIHE/hR6oZwPDi+GfrgEpsClsCW8BLaGy2F76Fzv1BtOhkPhlXAk/IVjndNYuApOgL+EE+FqeBFcC1fAPHgTnAo3wmnwXjgd3g8L4EPwTrgb3gXfgHfDd+A98CO4FX4L74d+yn47TIQPwebwYdge7oC94WOwP/wNPB3ugmPhbjgFPgPz4fPwCvgCvA7uhy/BD+CrMCawDgHGw4OwHvTpupxG0A+bwQbwdPge/kbAgzAHHoLnwMMwD34Gp8PPYTn8Gl4Cv4HXw+/gn3Wd0GswCh7Q8K3o4BzuOBbVpWN6YbIxUzHlmKWY1Zgfmo99N+5j7w2ejZ5Sdyb6v2Re9n9iTvZ/83zs/8a52HXzsP8187A=
*/