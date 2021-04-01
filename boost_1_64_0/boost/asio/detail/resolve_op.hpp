//
// detail/resolve_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_RESOLVE_OP_HPP
#define BOOST_ASIO_DETAIL_RESOLVE_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/detail/operation.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class resolve_op : public operation
{
public:
  // The error code to be passed to the completion handler.
  boost::system::error_code ec_;

protected:
  resolve_op(func_type complete_func)
    : operation(complete_func)
  {
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_RESOLVE_OP_HPP

/* resolve_op.hpp
z2oLmbMZ5Jf46zdzdr+92+yEhq2HcCmeTVteYJCSuxmGTYfM5POVlrfa8dHW9hQs9+mon/LImcVaKk2H2CgmEM8W63RE17z0aA0eNCQYaZdN7EnUZCZDG6n9DlBwKw6/dvcsaTyAUTrLEOCLoXcaUFe60rnZrgBCl0pRd3Hdvm1nDsToDW5U5S27kdBnfH/Man2dmdmi5sTlVOvp95TxZdznGFtrpXnq814uoSI0QX9vEORKIBRVDeJI3kfzYmfPXpi6KUf5KlLlVwZ8AV0CY/YOcw6qEvvHHRPO7UJH6Jz2+A+rhK4No/HZRcGOmag4sbjoHtiG/e07kNGsf6OGNSgEjAtnDzI02yhhW78q5qWjqL7oWis4fkLza0Ml3t6XN30+gwgbYMsdpbQ4dpZOx7vh75x/7CIDq28pG7Tp1Zq61SYx2KKZ/BJLklZFq+uecpU/KntOAQTEl5T5mYB6SWGwP8FjBwZskC1gX48pbLcXNH2W4iT/ai4+WY2OdlGs1BlirnFFprQP0cQAMNN9F6XCYcAEnMfETROeEzFndK/oAv/pi8mzfEK5kQ==
*/