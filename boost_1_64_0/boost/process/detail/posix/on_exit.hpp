// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_POSIX_ON_EXIT_HPP_
#define BOOST_PROCESS_POSIX_ON_EXIT_HPP_

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/handler_base.hpp>
#include <boost/process/detail/posix/async_handler.hpp>
#include <system_error>
#include <functional>

namespace boost { namespace process { namespace detail { namespace posix {

struct on_exit_ : boost::process::detail::posix::async_handler
{
    std::function<void(int, const std::error_code&)> handler;
    on_exit_(const std::function<void(int, const std::error_code&)> & handler) : handler(handler)
    {

    }

    template<typename Executor>
    std::function<void(int, const std::error_code&)> on_exit_handler(Executor&) 
    {
        return handler;

    }
};


}}}}
#endif /* BOOST_PROCESS_POSIX_ON_EXIT_HPP_ */

/* on_exit.hpp
6Na+heFRH/IBf6N4ShViONDa71xGzjPgt0pXEcbijUjE+x/ZfclpeSIQbYCYwOezdJB6jyaCeX+uGtfheRUFdMb0f5bJUS9LAx59KlUP+UaY2bmxjyexOxy5UN2kl8i1gWqKJs9nmK3m0LnULqFTlUdtEAcWPI5o1z8BOLxrQRHfB3CG111sXjqEfmff2O2GvE2F8DpLrXsH9u3cxJDmYvAC8mF5THzedDLKYKQ+eW+NqJhqdLUuYBOLQgSR4O/GEHJ3XcO4u+lKVdfDkH3c7UyVdz9ZBMx/cyMwhMFTJWMpjQ1iMrbXPnTtB3P7KDBXVDLqj8uZKwoheF21FnMaoZiOn529w6nm0WCFE4xfDsG9sjvV05MDxx4nr8MMRqTs/duzlNFp9oSA66nrRcJQopU2wXX7rquV/GPApwcvh+v4Uro+MDPuMaxEe68PnEsHPFdpqyXnBHHRGivHT7XolgSxNpD+A4Rdluo08+5+ctgZRQ8McKExpaWXe+CB7FBEtCwCuI8RB+nGPQpzQnO9HnRZmIBySG2H2sf8UZdXig9wS/vHdtOshqkagw==
*/