/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller
    Copyright (c) 2014 John Fletcher
 
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_DEBUG_HPP
#define BOOST_PHOENIX_DEBUG_HPP

#include <iostream>
#include <boost/phoenix/version.hpp>
// Some other things may be needed here...

// Include all proto for the time being...
#include <boost/proto/proto.hpp>

namespace boost { namespace phoenix
  {

    // For now just drop through to the Proto versions.

    /// \brief Pretty-print a Phoenix expression tree using the Proto code.
    ///
    /// \note Equivalent to <tt>functional::display_expr(0, sout)(expr)</tt>
    /// \param expr The Phoenix expression tree to pretty-print
    /// \param sout The \c ostream to which the output should be
    ///             written. If not specified, defaults to
    ///             <tt>std::cout</tt>.
    template<typename Expr>
    void display_expr(Expr const &expr, std::ostream &sout)
    {
      boost::proto::display_expr(expr,sout);
    }

    /// \overload
    ///
    template<typename Expr>
    void display_expr(Expr const &expr)
    {
      boost::proto::display_expr(expr);
    }

  } // namespace phoenix
} // namespace boost



#endif

/* debug.hpp
wS3rJXEUVImt7upeUc1ihywD1q06UrbTUQLokbI+uRHg2IZmtKSswmXNkY0YM8tiuzIxC4jtl7C4sA8OOdu2LN+iIwfKGl/WEzLXkxdcUUWJBqMA3aLx/d3Dsmbh0+z2gn54m5aAtbqb0l6OW1EKstU2s9MZYJGp3QosOi1mwMPPt4LHrrEZELnArWCimXYGRPx8K3jotCijAvw2e9mhh2N7Pce3ufKbRFrWPFR4icGTqdgLrwV7A89jbwIbZybpcxS6G+IatyA56YyZObS+P/LP2cwImwkolV1Qy0XfA2YK2wo6b7BrAjVnP56PiM5V9xYdRIdGWe/w2zx+Nwlu0Zh0eJa1Jz/PbpJ9pLdoVDkqy1pV32c3q5ybXyaZsSusdB7p65yZJOfZlzm6naEX70ThZdn41PfZI+xBqR6UukXD0itX1q78PLtZ6ci7jVggHc1lzarvs9tV7upbNHxcLorAp9nNTW4lcMgwkLLW5OfZLXLkyC0axaCSGXsWRpncAtqz5DrsDXcPS0BSiJDW110leKi0rFCBQCciu4eF0uSdVfKeZIcpgMsZe4AqXSmWvFkYeaenxxslBmUKSJk9WVTEyV3cqlhrY3XxeYWutVl3K7etm1CYEh63akXQGF0PGJ70u1RAc6bLOoI+
*/