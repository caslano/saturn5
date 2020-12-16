// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_POSIX_CHILD_HPP
#define BOOST_PROCESS_POSIX_CHILD_HPP

#include <utility>
#include <system_error>

namespace boost { namespace process { namespace detail { namespace posix {

typedef ::pid_t pid_t;

struct child_handle
{
    int pid {-1};
    explicit child_handle(int pid) : pid(pid)
    {}

    child_handle()  = default;
    ~child_handle() = default;

    child_handle(const child_handle & c) = delete;
    child_handle(child_handle && c) : pid(c.pid)
    {
        c.pid = -1;
    }
    child_handle &operator=(const child_handle & c) = delete;
    child_handle &operator=(child_handle && c)
    {
        pid = c.pid;
        c.pid = -1;
        return *this;
    }

    int id() const
    {
        return pid;
    }
    bool in_group() const {return true;}
    bool in_group(std::error_code&) const noexcept {return true;}

    typedef int process_handle_t;
    process_handle_t process_handle() const { return pid; }

    bool valid() const
    {
        return pid != -1;
    }
};

}}}}

#endif

/* child_handle.hpp
EEuiIufyyIQlMQuWwoL4GpbDslgdy2EXrIjdsSr2wmo4E6vjUqyBa7Em7sbaeAQr4VkMxKsYhPexGYoxy22/n/FN+XcwKyn1NzLnM/my4R4sgXuxDCZjDdyHTXE/tsBPsSUewjA8jD3xCPbBozgUP8GRMr/i/M/7a47+yNY3k+f8P4l0lpRCcmNgfX9SEKnJHrOj36aj36aj36aj3+bfut9mBN9TI0iJpM17/jN9OB0Px8PxcDwcD8cjo4+X3v+fLjXh/V7MGACrDfr/E7Pv/09M3/9fi5nVfv5azKL289diTiIWGtwuVIs5i1iz5tacvjLmkvZ+AuJuxI37v3fz4RpO9vk7Yj3ocqwhD+kDXuk6Q7TvqEdNG1vAuN+fOUH0FaD3QG6jdh/Ke/55Dcibbn8+XxwqXp9hijK56Npe4iKH8B8P2f9nmsgz3KRvm9GPdZcoXo8zNTc5i7ag1XZ93TaK11tzrOsbjUEo2uLWiDxdTemM+Sfa5RaJPH1NRn2VPGT/qXkiT4zJaFw+P5wkXh9lakufBqO+vTl5NkHkGWPqYHK1H7tP9OUaI16foDse0f1Zi3g9hddnitffMMl+uIZ9BHbLWLLuPvr9MlXUtfN35/8Ron1LG/Pu0wzcM389QWufT5nx7H3vN4nZ3/d+mpj9fe9HRUy7732P+jxIPC+UYHseKJ7v5bm+vdcl4a+192rtaxlvN3lR7W7G7Szptcel3/5yqqs1nufqRqeyfhP2zxu77+ulKVWmZLzdLaP3/xu3W6XXvvPf305n3B6aXjtaxtsxM9qOltH2wT+7772dSX6ny78vyViM1MTuvveS2ABLYQssjZ0xCHtiZYzCKhiLVTFON65dDZyMtXA61sYErIuJstzF2ACXY0NcjeXwIyyP+zEAP8dKeBqb4A1sirexOZrZ9hB0wZaYHVthTgzFV7E1VsQ2GIjtsTp2wAYYhs2xE3bCLtgFu+nGwYvGCIzDSByJPXEc9lKeb26RgGTH3CKOekxHPaajHvO/ox4zNNlRd/n/+Hi54/9xufSCxv/fYHDtv8Hg2p+Y/b3/xLRrf3kLu4zrrv/FC1rcyf5eeBl3VuMso8bt6wK0bXGV69XH3Gzr1MUy6ccWkLHMthhZ9cu7q/UTWiyrVj+hxjxErGldWTdBzLhuoqduzMOa8j7qI9bvTOkDXkmYotZNyGqJ9Oslck6z5l3MtVkv9f6LHSLmJO9HlOVR+hiLRV9nQfzP7kc0Xk7GjeYukPcV8T5M5VV6FRUztaQvkplliRN5TWxXce7TuCzuBd5gVyfhLpbLYsqk/GJf76HeS3JbrLuPpQjbZHCPnqhveCTydLH4ie225YmKlqP5izqZ0/J+rbviIr17VEwv0cVXvHaN1wzvG5N1L0dF+TMsDSjf8L4xWefwpcg3zlKVfOndy3WWfIdEvtmWJgbl2bbpGPm0/Y0Z1I2XbPexfSeWH2gpxfLp1bFsE3k6Ww6bXNWxK33ENUtdJb37qUtOF/17+TznUu8nXCrKibVcoG5qqpm7GEke4jWtvDT3PslzooJ47y+aGikz1Hsp94qy5ltaPrPf2hgQJ8jna/+a9SDrxsE8J8oZZQkS5eiOEVn19Wr7RL4Qy26Ts7xvS9tmbTkWkieK7d7wzuI4zCFPWX4iOiu9SCM5KvEktlHcj5VmvamnrGK77/SGWG9/SzG2z75+ijyij/wdkaenxT/tPsRGDRZDYqrH8R1xHPuwZo57ms8V9/Vpn5nY8IiouKj+0eHifjZZn/dErKOjxYd1LKAe7BW7erAP0kgyuAfmI1Inb3092bP1YEtk2qu71z0lu3aPewqpFzsTRSpO6k3qI+vX+sqxMGo=
*/