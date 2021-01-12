// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_INITIALIZERS_THROW_ON_ERROR_HPP
#define BOOST_PROCESS_DETAIL_INITIALIZERS_THROW_ON_ERROR_HPP

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/handler_base.hpp>

namespace boost { namespace process { namespace detail {

struct throw_on_error_ : ::boost::process::detail::handler
{
    template <class Executor>
    void on_error(Executor& exec, const std::error_code & ec) const
    {
        throw process_error(ec, "process creation failed");
    }

    const throw_on_error_ &operator()() const {return *this;}
};

}

constexpr boost::process::detail::throw_on_error_ throw_on_error;

}}

#endif

/* throw_on_error.hpp
9lW7wUqCmNUOCDeP3P4JXEByDxgo2IpWMCZtNs+kTRBGUIIEGVJSMrxSnYkH4TV6TbUaGBNaOvcLzFHwuIBJa7pPp8gQvxIQAWQliU5OhCdxjnhKa6m9gFEJ1i4q6KBARrpRWDtyNTVarWZij3xKy+eWj92J7ijWNe/bhHNVJhnaQKbJrpsYHFo9fYmSQDVoNLx+Zh4s/Yq0M8uBAYGeP6XE6OkJLWlZB8bIp/MLSlzMM7TQ
*/