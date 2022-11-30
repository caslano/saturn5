// Copyright (c) 2019 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_HANDLES_HPP_
#define BOOST_PROCESS_DETAIL_POSIX_HANDLES_HPP_

#include <vector>
#include <system_error>
#include <dirent.h>
#include <sys/stat.h>
#include <algorithm>
#include <boost/process/detail/posix/handler.hpp>

namespace boost { namespace process { namespace detail { namespace posix {


using native_handle_type = int;

inline std::vector<native_handle_type> get_handles(std::error_code & ec)
{
    std::vector<native_handle_type> res;

    std::unique_ptr<DIR, void(*)(DIR*)> dir{::opendir("/dev/fd"), +[](DIR* p){::closedir(p);}};
    if (!dir)
    {
        ec = ::boost::process::detail::get_last_error();
        return {};
    }
    else
        ec.clear();

    auto my_fd = ::dirfd(dir.get());

    struct ::dirent * ent_p;

    while ((ent_p = readdir(dir.get())) != nullptr)
    {
        if (ent_p->d_name[0] == '.')
            continue;

        const auto conv = std::atoi(ent_p->d_name);
        if (conv == 0 && (ent_p->d_name[0] != '0' && ent_p->d_name[1] != '\0'))
            continue;

        if (conv == my_fd)
            continue;

        res.push_back(conv);
    }
    return res;
}

inline std::vector<native_handle_type> get_handles()
{
    std::error_code ec;

    auto res = get_handles(ec);
    if (ec)
        boost::process::detail::throw_error(ec, "open_dir(\"/dev/fd\") failed");

    return res;
}


inline bool is_stream_handle(native_handle_type handle, std::error_code & ec)
{
    struct ::stat stat_;

    if (::fstat(handle, &stat_) != 0)
    {
        ec = ::boost::process::detail::get_last_error();
    }
    else
        ec.clear();

    return S_ISCHR  (stat_.st_mode)  //This macro returns non-zero if the file is a character special file (a device like a terminal).
        || S_ISBLK  (stat_.st_mode) // This macro returns non-zero if the file is a block special file (a device like a disk).
        || S_ISREG  (stat_.st_mode) // This macro returns non-zero if the file is a regular file.
        || S_ISFIFO (stat_.st_mode) // This macro returns non-zero if the file is a FIFO special file, or a pipe. See section 15. Pipes and FIFOs.
        || S_ISSOCK (stat_.st_mode) ;// This macro returns non-zero if the file is a socket. See section 16. Sockets.;
}


inline bool is_stream_handle(native_handle_type handle)
{
    std::error_code ec;
    auto res = is_stream_handle(handle, ec);
    if (ec)
        boost::process::detail::throw_error(ec, "fstat() failed");

    return res;
}

struct limit_handles_ : handler_base_ext
{
    limit_handles_() {}
    ~limit_handles_() {}
    mutable std::vector<int> used_handles;

    template<typename Executor>
    void on_setup(Executor & exec) const
    {
        used_handles = get_used_handles(exec);
    }

    template<typename Executor>
    void on_exec_setup(Executor & exec) const
    {
        auto dir = ::opendir("/dev/fd");
        if (!dir)
        {
            exec.set_error(::boost::process::detail::get_last_error(), "opendir(\"/dev/fd\")");
            return;
        }

        auto my_fd = ::dirfd(dir);
        struct ::dirent * ent_p;

        while ((ent_p = readdir(dir)) != nullptr)
        {
            if (ent_p->d_name[0] == '.')
                continue;

            const auto conv = std::atoi(ent_p->d_name);

            if ((conv == my_fd) || (conv == -1))
                continue;

            if (std::find(used_handles.begin(), used_handles.end(), conv) != used_handles.end())
                continue;

            if (::close(conv) != 0)
            {
                exec.set_error(::boost::process::detail::get_last_error(), "close() failed");
                return;
            }
        }
        ::closedir(dir);
    }
};

}}}}

#endif //PROCESS_HANDLES_HPP

/* handles.hpp
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
*/