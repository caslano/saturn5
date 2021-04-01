// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_INITIALIZERS_CLOSE_IN_HPP
#define BOOST_PROCESS_WINDOWS_INITIALIZERS_CLOSE_IN_HPP


#include <boost/process/detail/posix/handler.hpp>
#include <boost/process/detail/used_handles.hpp>

namespace boost { namespace process { namespace detail { namespace posix {

struct close_in : handler_base_ext, ::boost::process::detail::uses_handles
{
    template <class Executor>
    void on_exec_setup(Executor &e) const
    {
        if (::close(STDIN_FILENO) == -1)
            e.set_error(::boost::process::detail::get_last_error(), "close() failed");
    }

    int get_used_handles() {return STDIN_FILENO;}

};

}}}}

#endif

/* close_in.hpp
G10R6SmkirfsZ397JpSHdM1quvdxpaWpMy5ko7hd2dQu7rOb/fCDZQm9I0ekEjg14Nmfu3RbU9okwyCjU49VTL0HlsLXHGpzP8/gh5EFY1jEfpquH3VYKdMsHgm0dNcyAwfNvKSIi3aUh9r1+xCqp0l8hKRXfl9NozGK2n9xx6J1czYxDuhIwLN4E3rm8djW/UCUh6EswQgkZcXmfOT6dijQUl4ExKipWJF/pCH/tdNvqd/0MP900Hx7SUtOITRbt4czO8hgzj1tBJ7bjBZX2A6CN2A7ycq3iZSDWbBkY5QCuHF3SQRkAHz1JzB0OLlM6RGu4oW/z+hyzQLPyZV8/h1CSwuuTwQyuqqbIoWH2oLb55JC+7oSre2SS8C2vlmGR5LKeTl/ThdcFP3dgMb4pJBFTFod+HWyz0/DmEJSnI/L+9vUzDzqgepjfa4tgPghffsQWLprZzNlzexqHhIRUo/hnzHZ+/JNeZtRUdkztUEKJvL0MJFLOqWYud6va16rrHAuDDfrjFxuzG9a2Fcp6xKsUzPoZw4pzQtapMX8ba8LJz6sdCptC3BAZg==
*/