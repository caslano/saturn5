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
ZsF2n9+bT8T2VsJK5IkJ3/yS/GHfbYP1R+/CzzyiLQD+yEsAEJCPb331OgffR/NHTHjabozTCaTLjpZNjtzRPt1S7sXsg3GCEph/kPUzIuFJMWVeZP2TlphpiJla+ue72AR/2IbQH6sVUW29WSTul1Hc0XGD0vtXruequSU6Rq3RRlKV/GegWgbZZXO7Jo/VV3s8E+pgJEH3c3z33wVqZER637/NNH0MCJvnGeXhC+gNDcwtgtIXKpEw9HJhrC7yQS7Gfc/cvu5/xUufdou+OrClEKF5Goh+M+n+xBd9j4Q9JMsbDlmTu6SqKY7b3pYKH/3LM+1sNrH3+4cTCVue6kc6n0l6r3BBwHSyG4GBkHcpeculeLfRV45jC8/uY+fNLK+CaaOU7UQgFRQQGIP1F8wKNHMsLjCB2bTM4V8MH1OO7e99tt0ICrWKmmqWi7QCQMyGCYYJ057T3FTM5a9h02f70kcP08Sx23ydvGfDMdsP3SS5UxkTW8dd0a7LX1NhoItUWgkbn+hd0mpRa98Gk4irAScMfpoLuGHUrkWvYXS1szrfy0bjpI/XEar3Hm3CEZGwYpqfOgipAtDaO43duWcWm5NqC+xODDti9ivyOhYAbXfC/DDQ82Dymi+LzamPacpKKKSudNIyJx/KP1JhOtIFqbjgPjR5gej4us1BebT5Q++NuUxMyTmsfvDZXNsBl8My0ADXypOWz7Zj
*/