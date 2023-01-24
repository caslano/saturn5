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
IE8ktkHsbCbYqIR1LsP5/E3hL+LgzK+VRw4bI3IRTL+0HulASaMyx9md+Z1Cc1aKKX+Xw1AvPanaeXGBv3ZKHMm329x+9SiBZcF/gRXBEmBdrBMjyc2d2NFeJNPW0OmU1YftSEAzztcyZLzNGf4b6qvCWbJItQo8DXQGVIYL/lVD3hhk0QJAB12wu0pcaJeABVf0oswVH3bdvOagTSyF6GY9htKkBTWpRCm+6OVW9notqzz/eDVybs0HeKJ+3JaSIP2UwvHs53Ltbb53pzncEAtQyyM0ZdXlbKcXEj16yYtTPm4QUBBImwjZT8sVddwwU75fR/wqqFa05MkIn4yKWZcyUPszWt73F5d6TtLTguFwhgdDtrfZeM74XTtywxENadYjTVqPBRdiQCOnyzu/xSy5jAMB+ytSyaiEYJDy5I+EMo/2FBmL+x965K75rM7tbfkx50ym8Zb5ZiKt8uOT3Yeq6X1lRQDmgJUaGJqm2Mc8H6vvHxY/m+00vCEvaHJa9Q1nADotSG8SGXyciuP3JclZ3qqPyG9jDJ+/v36MWXJhZgYpl5Wm9xFf6J+xZRyl9/21DSYDEO0pyRFamKkcpdlNjemuhn/qgV4nx4CGZ+ccQsTpQ2dwLodk/I+wxFOnNW7lKIIPBFXFevUPW/GsVVN8+Stz3a/btkCedbnOukYYev0oNVr6CFn3CJJCSIIiY5/U7/c7UPQCKgkL
*/