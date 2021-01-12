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
L/WFYvjrIfzrWA6YZGYa+8nLIewOWf5xm4cro2auqA9kmb3i0DPMlWd2ZWAjnqf2ChgfI9enDvxMw4jXSCGdMvZ5M/Af6vzrgTY+UEX2uUuFJ3VLoj7w524fiGX1Fgj7tS9PR6GROty3cF2EdFGvX0OZwpA6xk7Lfhvcf4/QRw6QqftnzP3FIf0hgr7MoDrbBm3xdrj/Pv9+MYim4+Az50GqE9hl7vf7zEcO6DPN/NY7Ieyx
*/