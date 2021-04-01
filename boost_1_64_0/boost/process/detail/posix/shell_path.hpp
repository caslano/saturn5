// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_POSIX_SHELL_PATH_HPP
#define BOOST_PROCESS_POSIX_SHELL_PATH_HPP

#include <boost/process/detail/config.hpp>
#include <boost/system/error_code.hpp>
#include <boost/filesystem/path.hpp>

namespace boost { namespace process { namespace detail { namespace posix {

inline boost::filesystem::path shell_path()
{
    return "/bin/sh";
}

inline boost::filesystem::path shell_path(std::error_code &ec)
{
    ec.clear();
    return "/bin/sh";
}

}}}}

#endif

/* shell_path.hpp
8+/60KacJRNtWw2NQjKKEonYcwmWsela3FZ6b6/KLA3TjiW9IpJr3tp2m05zdihtJRMTKTgkXmfipNqMJVzFKftWN4Bc16No5iThAK6nIt2lX8paYNdMC7QS5sP6UXkH0IBe/qbc7GN5tr5Y+DrOQ8soFhRx2SFOOvRPMEtxUcubhEI15awX+SymmXqhFGRuTxvTCcVMfK5GleZsgHvVHuNWK83BGayoBG6X40q182F332P5QWBK+kmnGEIG2DWM5/WsS7vtIrWuHsEMU/R6B2c2z4bCNgVMFn7LXvszFVvlQKw5CwV0MUa1YWsRpzDw1SP55ZmFkdt/hXpx/9wdpgzoS5JPw5YeH7i9X1XYsB5CwbUQqplXSJoVgbbsZgZF7NXE7UWssc4Q3bKn9T5N+kJdlfV0wRFi1LU4cLTjNCQCB/Fov1ekRqmMIUc0CC04TlzSqrV+y4vKGF/Tiu54WR9pXZQYH0q2f04D7Vafc0nbNSg8cu0FRTVmNkFb3nyE8H3j+CFgpLYmQVZGQhPkwHui12P6hcx4aKo/9gYgBJPmM9frRX3d2GkEjQ==
*/