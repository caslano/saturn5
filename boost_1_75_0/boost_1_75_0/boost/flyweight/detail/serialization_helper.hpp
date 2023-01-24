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
ZhODw5fcycEmhsZxGaKcy+BjL/q37OU7uao0Ints5mJhj+0ZRyyba1L15LmkTs3NVNHwKdizEE3dtPQiVjU3kWJZ/KVd3owQ8V/jsInlaPjiiMha8VQ7F6LO9W/FEkn1GrvqBbvIf4cnqBXak08YVcWqhs19GEbgLq0Y1ZcGO+LYWFo+7TNpGq1i/aAVhSZzdUCFZI+ciZKMjsnRXNZyDmiRDZh8Drzn06n2tIw/beJPt+LTlYvwIAzaOpsEKTgSv49RuzzqnnVbeTtsjIGRfbQewjnAsC4ptBQdMqRs4ClfieEpXHF2z+YYQxoReFc2pDFD5FiynaOOBykqkZBYGYeeCCA8LobamtZztC8i1nc8hkH/GBqCleqESEGfKrHHcs8rHEtcunTkoRUqVYt8pW7aVKdUUWyog1aK1bEwU+0E+imVvbqMv6Jeo+0BGHyLWvFE+nEMasKfwD4aPLpw4Ip1l5ypk23a7G5RJWNg1AHFuoznVaaKFjrIow9ADgMDRf5cWTUnTVb3kPTmpIU0BTE94HQJGWdtsREdmy54GSe6xjdo3st4ma5t+DWWX0++hMmW0Fz6G90t4lPqnpfoOgfu/aa8k4r/5JVsXvVP5bkGzNNv8fRD3wgxTz9AeS+gi4cuXend+TyDO3gGE17S22UMeykd4w1xnIrl43jm47DqRVKGMxruAy2gebRMM3aVhT5z13kBqnSI4V+B
*/