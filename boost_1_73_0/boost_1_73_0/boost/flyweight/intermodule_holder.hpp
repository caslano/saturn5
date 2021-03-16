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
qHY8VdEIII7x7z1R9EyXeTXjDze/9PqZiDaxAAWMb+afPfCL4SfyO4U/VzWjbM0ZgPcYPy3ouU8+KWpx7+4VD60/1HFsN4AGCvFr+yWfvnhXt73P/nJ4S5aStQu7HsYXte5oXdd8wdsXyt577IuqUyMAXmV8ynurh/5Q98bA/65ZuMj0WvhSgAuMP3vWtHj1nfNn9d5e7mwW92NbgI4G4l8bPS31hM/8VY+sbnxo58tPbQZ4gPEnE1JCJkfMn/c=
*/