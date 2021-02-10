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
Qxk4G3mjPJpKTlOuWsCsiiwr7lLo4PNC5fWGbmWGS1yD0qlv6vhqNWzkXa2mKLrreqNy49E8zzj5eWGhxIC4S1E7Ii42G/imrRUpUGfhjaMIOQ0HbNQSUMxTk8os/acFzXBq42CDgBgsJtbNUMy1g3+lAFp162Rty32jzLpIujLQqrpVlSMKWQKQseQ8c0kBpyUynvKtFfAKmtHsPldlsVT3/J1FNOeUE6K3VqfWU8qVSlQiWIRlKGfBEQ9ctl4FnQvXIFTWgLhTBleyhjEtFNkDSahMJTdf2t9wJUda2GRD/UYaTeASywja2IBvE/bAj2NVmhcPOGVrJRMOS5MwoFAgQbXMMnBbB6IUiJK1KSAYevGO2SRjmTvyds3q66Rk+Z6I0o06j4s8Sa25Tp92IpFqmSQuBIOmRbT4hMU2cQIa2jKIhu+Di8l4MGQAnD49YwdcuXIKZGzQKDyY9Or0aIKESxAdJIjFfJkjfzyezMcXgfi4VogyUE3Le+QhBpXlprcrgGLU6zXKgwN8kDizNcSj10Ul1CcJOkRtp6tOGttX6xZmDqkO2XFRofNBjzJ43bPvmzuxzAX6Efl5XtR5rPhCmnP2d6UwdhBpfgJj5bk74aAjl0VtcSc6C6l1m6PJPfyG2xi9jaIpTUH8
*/