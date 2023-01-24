/* Copyright 2006-2011 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_INTERMODULE_HOLDER_HPP
#define BOOST_FLYWEIGHT_INTERMODULE_HOLDER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/flyweight/holder_tag.hpp>
#include <boost/flyweight/intermodule_holder_fwd.hpp>
#include <boost/interprocess/detail/intermodule_singleton.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

/* intermodule_holder_class guarantees a unique instance across all dynamic
 * modules of a program.
 */

namespace boost{

namespace flyweights{

template<typename C>
struct intermodule_holder_class:
  interprocess::ipcdetail::intermodule_singleton<C,true>,
  holder_marker
{
  typedef intermodule_holder_class type;
  BOOST_MPL_AUX_LAMBDA_SUPPORT(1,intermodule_holder_class,(C))
};

/* intermodule_holder_class specifier */

struct intermodule_holder:holder_marker
{
  template<typename C>
  struct apply
  {
    typedef intermodule_holder_class<C> type;
  };
};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* intermodule_holder.hpp
E1NU85W7uYj19zb8I1tqyzmNrEnMyLAmSTbhLuKHuLXY1Sk7suHscI8my/LUfqGONc0sl+pvoP/ipYJ+Sa47MegDbdivgL0Ef3Mshi92yNtxk+HcczNMnttyWNe6XPLeyWpwZ2q557YsE0aG+ctyL660GlEiwP7E+I5sacMI89lzdKdDJmEMQpB8/jmdzyjBsfduJJeAAgzDPSOppUex3C8VT5xt9tdTFLRi+T9s8ZTtv72Dbtcj8/uTin3uHNYEm7nHzb2MxOvZJVWCSPCIMybhgXvGMftoHY+4/MnGAc7WSVOTIB93TyeWvAMUqOsQA2aPxEv+41xdyU9+d1LBgrdIsoU/Rf8fKBBiqTdXsRSqrEvVymoPY0iCAqXee2A3JvSOOe5RMDV4hD5YdlfI03MRG023Qaj121JNPPY7ePtgBPeAuPN3TYC489RfeNz5nAn6uPNrblXjzvenn/DZQvR7tTOFJ34s/cw9pKQ83yfb5L92j6JQCPokjhAUeyZDkMFD0H8BMeh7hYhBH843QBeC/gtDzPnd4yLGnM8JF3N+0ruG0yUBCpLvqpAx598NjDk/6qpoVJa9pzJMRqCjz0oD5heoEToCYEuAYcJ9hZOpxZK8Dbr4NoQx3yvJ12NHuz9L19Gu+JZ1tHupo1EZ2SBDg9czTtqqBH0Q1ng9ChyrFUMo+5VaKPs1lmqA13D6JDNEqreBy4HDGMp+
*/