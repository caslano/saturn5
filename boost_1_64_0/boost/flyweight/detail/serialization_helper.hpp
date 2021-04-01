/* Copyright 2006-2014 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_DETAIL_SERIALIZATION_HELPER_HPP
#define BOOST_FLYWEIGHT_DETAIL_SERIALIZATION_HELPER_HPP

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/noncopyable.hpp>
#include <boost/serialization/extended_type_info.hpp>
#include <vector>

namespace boost{

namespace flyweights{

namespace detail{

/* The serialization helpers for flyweight<T> map numerical IDs to
 * flyweight exemplars --an exemplar is the flyweight object
 * associated to a given value that appears first on the serialization
 * stream, so that subsequent equivalent flyweight objects will be made
 * to refer to it during the serialization process.
 */

template<typename Flyweight>
struct flyweight_value_address
{
  typedef const typename Flyweight::value_type* result_type;

  result_type operator()(const Flyweight& x)const{return &x.get();}
};

template<typename Flyweight>
class save_helper:private noncopyable
{
  typedef multi_index::multi_index_container<
    Flyweight,
    multi_index::indexed_by<
      multi_index::random_access<>,
      multi_index::hashed_unique<flyweight_value_address<Flyweight> >
    >
  > table;

public:

  typedef typename table::size_type size_type;

  size_type size()const{return t.size();}

  size_type find(const Flyweight& x)const
  {
    return multi_index::project<0>(t,multi_index::get<1>(t).find(&x.get()))
             -t.begin();
  }

  void push_back(const Flyweight& x){t.push_back(x);}
  
private:
  table t;
};

template<typename Flyweight>
class load_helper:private noncopyable
{
  typedef std::vector<Flyweight> table;

public:

  typedef typename table::size_type size_type;

  size_type size()const{return t.size();}

  Flyweight operator[](size_type n)const{return t[n];}

  void push_back(const Flyweight& x){t.push_back(x);}
  
private:
  table t;
};

} /* namespace flyweights::detail */

} /* namespace flyweights */

} /* namespace boost */

#endif

/* serialization_helper.hpp
CFQ1Ru3M5Qd2StoUVZ8v+Guzue0rtwZjp01U4pZuxtytn0iAxMhXvz3EsNi5dWqZAi/IvUh7YMuZ0JE/o8ZFCmfrAb4qvZY4HboZWZwsQ0+IRbQYk8AFkovb8YzzGPZ4Z7W4qjAY+gGZ/XtPlHinH7fjEv0ojaERdKsLikUYGxWQ6HHQr0nDaNZ40ky1SvEO0DWbboV2/NXk6RvFUC30+ZbR1L+b7eHjmv3+/vSTsk2uuQtBb/k03Qfb/IUc5CG9wcTl2HtbyCFuvM1uCkgaxKGDB+HCScUtlMdW/vwc3tNB43LDpLEHDiX/p3B4grnI22GNYEVgSD3xvB9I+62utM3i/OZeIgzdKHb+MVmX14MMZlwHh6/z5OQQTfGzkSflo/Ft57YLI0d2HmhROuth2voYCnwmAXolRtivLNNyrv7p9Vkn6Q/5D670L8s0FiJP0ELyRjfdWC5o0vSIT66I/4OFWrhPcHBag6D8BOwvOF6+ZdOOXZw3/atjIg0nRhCSikVIHG1nYs4xnaGTRFI1sHmRh+kr4zVtsc2Biu9eZrX/FIr1KJ+Du3qm1Q==
*/