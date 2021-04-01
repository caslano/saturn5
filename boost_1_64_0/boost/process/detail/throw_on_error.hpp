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
8JR0hzL/0G5aGejINrEjq/FzpA3mm4CHvjIq8p5T700nKbseq5dR1s2KatTmccP4+z7/WCtowZM2Yjt6otfWVXsb9IWMz9dQL33AszN5hRC9ojHPnJGXVjCogFydZp0e+0e1+SAK8YKRG3AJvfYpXAUWHmnDw9oTL/TEurMoqEJFdt+Z3TM8kkBkm+7137mwWTX5vQx13CcQREk4DDmWBz8G1nwe6lUNO7A1n+OXj2Mih8sAQDpRfr2QVcyQmC00PTEKXzOgd7mmzE5iQL6pYmRumy+S5NNhSl5ELbAD4kkYqmIU1h/vIuv2RcqP7IUaEETFxLD4ddVN04Eq5iXMALR3olBwf6nOHFMM99sDHQ+T3Qe9gIc9CRiY7ICEHpaN++xkh2z0cx/tjmw7HSvJZxXgQ+H+d0H4uAemrvrKVtXX/NBi/fEk5pja9aDNolWlRGKWEfTZLkrcU8zcIMa4QAvhOyNrxFrHBgRAO+1l6tIJJa0zFSFhhnZsDaxIMJMX15ICvkzKIQr3CJoLloHuMa3l6ciZNpnxZ7gYozVB5Rs2hxNNR6XGjNnlqQ==
*/