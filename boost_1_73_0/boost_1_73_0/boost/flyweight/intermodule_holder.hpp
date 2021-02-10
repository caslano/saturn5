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
4vlsDF/80TyokViBlVTjy8VGC5LJ5/psJwoC8EfRBEfjxex1+joYFIv0tHkzC+PAzsxmx/kfUEsDBAoAAAAIAC1nSlJFD0Cm2wcAADgSAAA0AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9SRUFERlVOQ1RJT04uM1VUBQABtkgkYK1Xe4/iyBH/35+iQhQNjDzM7p6ivcfeKR4GbsmygMDcZiIkq7HbQ2dst9PdHpa7zXdPVXcbmMfmJtIxD6C73vWrh/vrDpz/Ya+gT+Lgd1+J/Uvwhe8t01zJf/HUPM+QJF/A/SDjGt9foOoSjlxfkh68iOsLdC1X4nW9o89J8gJ1azKS/l0S8zqhj3jiOD3/QNZ7JW63BrqDHrz+7rtv4QLevHrzKoRrVglewNLwasPVbQjvMnvyty37/Lmv+U8hcAOs6D8QGG+FBi1zs2OKA34uRMorzTNgGjKuUyU2+EVUYLYcclFwGMzmN+PpzyHstiLdejl72YDeyqbIYMvuOSiecnHvxNRMGZA5SkD5mdAGZTZGyKqP6jkYrkrtxZARrNAS2D0TBdugOmZga0ytv7+8TBtVoCeXmUz1ZdqGor815SOvbtCaku1B1gaMhEbzEIg+hFJmIqd3DBEe
*/