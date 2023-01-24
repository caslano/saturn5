
#ifndef BOOST_MPL_BACK_INSERTER_HPP_INCLUDED
#define BOOST_MPL_BACK_INSERTER_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/push_back.hpp>
#include <boost/mpl/inserter.hpp>

namespace boost {
namespace mpl {

template<
      typename Sequence
    >
struct back_inserter
    : inserter< Sequence,push_back<> >
{
};

}}

#endif // BOOST_MPL_BACK_INSERTER_HPP_INCLUDED

/* back_inserter.hpp
yBmO0g+pwfszI0hpv7fC6burjC1A4UjrZAVCGSKA4tKve/Ay+4KgjxiY33wBPYiHkGJSpn2J/kZgaWQ6gAxiCoaDRiKG1YbFvGgKH7OCPhQFMQTpH1BMtgyaQJmgumE+ua3MLmnZO3xVF86D6EtvJ7wjn0umk+hOuiPalE0GvT9jNEfUhzv+aGpLl1W7woPlQxLZAEQBPbIzTZmi+4PfTWKXAHQiIYS6Kewxctf6fJQXuvtFtsvEZ+ca9OQFqhqJfgEtEuG80n1XDDIDGxgKbVJqMzoAgfiZgANQjBUYwjnjdYWxJi394O18ZZpvFOOUU8Rp+QyBD5LtUjHLq36XgaTdHj+boZtuPkg8SDxUOwAfch5wHrod0v2Fjko5ne6aCoGETCceDL3f/5gYUsW9vdG8KEyKYtF5LNe8SBzqIWBZX2KZBBVub6dqGz9++xbXvIRKvBPY0E+L81dh4fvdIniY0RAbfPNuwxSBXFhS9miQNSp3gfA7HDewLxO58LTLGi1ZVoCwkXwzNaNnkkv0TrNEU2Iu30VgYslphql7C6YQoQbKCqBeo9JyOG829PpsTmo57r2T0m7V1AMfDc8k35v9Yh+t1Ev/P1Yv6jWl5caHjDqshUxHWd8m5no/iesfdUFRdWe0AkAe9h1U4kwyCtWXvrnW7V5znQe3uexHdW1Be/cHAndvSXY7J70jcggeP94ZESBuZUY421El
*/