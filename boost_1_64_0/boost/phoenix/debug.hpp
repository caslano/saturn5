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
MXQQBLYFDk7H0AOG/BB630wqYEEVw5LLCTrsi+Z+4E6D/urF6OHphQuDyd87tGtSelxAio4nQVeRZhhc+ZZ38L8NRnf/pHxqMVQ3fZAQp5RpAVRrYT+iy8bGxdVpQyC365+IXgDcq2ClbSFcMHOLF0yJHl9rf5FG844W4rN7HoZyGGKafS+xhMf8MDBOMTiKKh5oa+I6zHX/SNW9EgTbjHsTsY83K7+Cr9MRRDfL6peA/AnhNxR3WQfdSmQ3wTL5fUTOqPcvaJ8gN+rfZ4TLxmkoHAcdNaQshj8YqxSsriVoUqP9IokN2T+FKl5Hz3eCjFpDldKsoFMckVYTDHyRB1V3KtrjyT/NXUZp+oaFKxRD24gjDuwezhd3UMkhtEiy/JAlAk5jvVi8nONGGXsK7/8qD1ujK1HSivCN2IDyMs5o7CHecXJBurZ7xiuZ1H7pH/YhpCA7jIMtBbcwe/elzJaJh/avR04yxSUdix+ol360CCDwhxiMTREDyS1pvQxuBeehtcT6qlwazCVabur90e1F89BN6gPqqsvXnBI+fmDp4PEC2x/fe/g8vg==
*/