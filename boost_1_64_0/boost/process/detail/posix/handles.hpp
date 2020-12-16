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
diB7kYQu1KlIJpKDLEBWIuuQzchHXSrnaFT+Kn9/1u/P3f8vu6QoMPj/3xz7Hxi7/7HLGH/RmTH+qosY45+iOl9AJxuEDTp9mMM2OmjL1na2LkZ0gwcNGWb7jxXdwEHBvcRsfTXV839grz62Pln0J/XsrXutadi4Szz6jHSEfZToMBzYh5TZ+vqi79Wz78mZfZz6Bqof3HNYf6e+ocZFfRh9I9WrD6M/2pz31D4kyeiPDeh15z1n3I8LnrePM1+aB8MgV3pmOm1bahxN/Fz3OkTvvtcheve9DtG773WobhXvdYi7616H6H9jr0PcK97rUN3d9zrE7Vf3OsT9N/Y6xN19r0N1c9/rUN1/Y69D3Cve61Dd3fc6xM19r0Pj5r7XIW6/sdch7u57Haqb+16H6v4bex3i7r7XoXH/9b0OcXff61Dd3Pc6xO039jrE3X2vQ+P+a3sd4n4Yex1+fBh7HWITudehuZ/3in5Ab0tsY0WHhnHVxGfQyb366L6INZIt009+l3aqLtOxURciX+BvVVpwPlFOzvjAE2J8dm6x6T/+rF5wnfAZlr0u/tNin0s7ZhXXMVKEZ8YAvSzjiSREt7GKxjZFxkiGbBnWxehJ93X7bT+JJvy8kpKZPJgcfdy3iU0PyoLHdeyiM47/rCdh5JTo+ZIctkkRtqtqocDWOX7/Y3FvZcYGJdULjvEJzBUaFhMoK9gSWFyNTNPvfVNC+Fyh2Ry/mEhfEbI98XD3eYv2B89lsY66PSYkcM2S5ZrZY0LIJ3TB65CKLs6MuwzP7xTcEoy9I1/RJ0HyCj15FTFee7uO135Py9a7yNfYtqkXXrZKWGw8Kz+ybNljm0eI/YPWEErSFVZVt/KlYXrMuvMeS0N1XP/5YnOS1dp93h5hHHm5a1Pvt8tdB7HpTx5jx2VKMP7eo61/hgkvqD/8Mui0fThByqCMZQmtm18q7nO5Hj5s0HH0rZbDisrt4+LeQY/VXvcPuUnOUcLi/PZeHReKezbvO15s0Bk/dRx+8mRkbbymfbG4Xyj3wjoy/kC10L2w4NrIe6EVxzibe2EurIntehjQJfD3VVDvj9/c5yFwf3z76/eH2SNA9gIw5eiPvUfahe4RHTN+v5frCVfA77BNSA/Ns2SPgqLCghyCs++PIiIazM8DXx061Fds53lD45Zay/FMb0NriDc0xvDWBgFdnOu9w7lMOdpVR8LPnphXaMpRJ3FfYvVyG1se4f/M4FhR8R+6f08U92hvVzQ3sjqc233kDGNAPcKlLDPqjDzvJeVB5rPVD1jcSdnPoV+lRnAs4ffOsYszTDmOEdtCPdb0cxQ2bkvj9266hGvGL34jfsusxpwlEJ+EVIwinndnSHj9CC9ZwwmdoyY2gTSon0AiQuMeuVaaR/wki8zYsZUSh7reROPO9ppiYY+TPUlsJno7cv9udkmbHfbEjhmOfUPPl/SkW6kaz9VyHOcp5Pn0MCl4zWqm44TNmDWzt8Kdcs7+nmR6tB7hqmwlzQ09R1mR5WqSNZq42OMhL0AurYUC4ViEiy1MhD1J9OJEnPn7B4gdYvwKi9FzEqh6vb9jEw53HKXz3pZ7xjz7KOfotJzrfU3eocsK6aRsDRC/UhblHucaqk6vrY5D25pu5mDKceP64ceNGrjO0SSBZk1d9PTXID8R/naxXxAYtmdqgPB9pIuY6u42r0j98s8uS0SURDmfSe+Lza3cBVGOcqNp13LzqtjcL4t6huYH7UsMXrek5CDrRIheJ7luzx/m+0pJw/L1sY7/J40R7xQ6lv8VpDGyCTlIfi2XMBbkFxZOm2neKDS/upMY5mROdI7nv0/sV7vln4bl0eeXvks4x5mLe1M=
*/