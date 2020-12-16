/* Copyright 2006-2014 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_HASHED_FACTORY_HPP
#define BOOST_FLYWEIGHT_HASHED_FACTORY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/flyweight/factory_tag.hpp>
#include <boost/flyweight/hashed_factory_fwd.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/if.hpp>

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#include <utility>
#endif

/* Flyweight factory based on a hashed container implemented
 * with Boost.MultiIndex.
 */

namespace boost{

namespace flyweights{

template<
  typename Entry,typename Key,
  typename Hash,typename Pred,typename Allocator
>
class hashed_factory_class:public factory_marker
{
  struct index_list:
    boost::mpl::vector1<
      multi_index::hashed_unique<
        multi_index::identity<Entry>,
        typename boost::mpl::if_<
          mpl::is_na<Hash>,
          hash<Key>,
          Hash
        >::type,
        typename boost::mpl::if_<
          mpl::is_na<Pred>,
          std::equal_to<Key>,
          Pred
        >::type
      >
    >
  {};

  typedef multi_index::multi_index_container<
    Entry,
    index_list,
    typename boost::mpl::if_<
      mpl::is_na<Allocator>,
      std::allocator<Entry>,
      Allocator
    >::type
  > container_type;

public:
  typedef const Entry* handle_type;
  
  handle_type insert(const Entry& x)
  {
    return &*cont.insert(x).first;
  }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
  handle_type insert(Entry&& x)
  {
    return &*cont.insert(std::move(x)).first;
  }
#endif

  void erase(handle_type h)
  {
    cont.erase(cont.iterator_to(*h));
  }

  static const Entry& entry(handle_type h){return *h;}

private:  
  container_type cont;

public:
  typedef hashed_factory_class type;
  BOOST_MPL_AUX_LAMBDA_SUPPORT(
    5,hashed_factory_class,(Entry,Key,Hash,Pred,Allocator))
};

/* hashed_factory_class specifier */

template<
  typename Hash,typename Pred,typename Allocator
  BOOST_FLYWEIGHT_NOT_A_PLACEHOLDER_EXPRESSION_DEF
>
struct hashed_factory:factory_marker
{
  template<typename Entry,typename Key>
  struct apply:
    mpl::apply2<
      hashed_factory_class<
        boost::mpl::_1,boost::mpl::_2,Hash,Pred,Allocator
      >,
      Entry,Key
    >
  {};
};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* hashed_factory.hpp
hZjNt4Ea2PIRch8Lf1NrP3GwwSvHwOC8Xylq8hLDZDLW4MKW5pMBudv78YEoR7a+Eu0boMI3emvYbjwUy4TvFPhZFviP6fjTHGJLbPLcYFioU3CxhWutsD+BNlxODS01cuwG6oPoOhk3v1xGNlkEpNVRuqjHbFajZZEhBxghzyDIgVSx46FSyzu3YIBytseQM20h9yM7JkNVbJ4mq+IUOxfjK4fxOnDnoZ0yovgUlNU9JEoSoeTYKxcotc+YK82nBQRTrof9p/B0MiVFSwCXHdpJfiV8ogyLT9RZ5+teSG5BnRn/sCaXb/HdF/G8n2B5T+YQ+AZ5eithfhtokeedPjm/jZYo+qKN5eaVelkXhtg0cOQwnwp/3rvB/hd+5lM8oWXWkzYZxcvJmgz+xaAwaCpX4GRSdHU9m5j9/NwAfVq6fuVKIRxVuElgCuw1kDo8VUDOQHnAkNYk0vJR4NM9NjGgcAGajvTY0Ve/XOo02QLfovUzFEns3T9n57o6cYY/ddUHiKmLkuS2cBiPeZZiWBb9ZRafnyqz8NtlHe3FhowaMQY9TEI36NCnGqHJyXQOL21dg0SpYMPo8h47xsioq3QqNlGIQFWd5LjHjsES9gwdFuZdY45eSHDnstpQNKDz4iTGJnmf3qzVRnOF7jvaySxCU2Wf83Nx5EJpM50HI53sn4XaA4vIDTe5SOqGgikRuVcnMkKB/zCHHbHvvsMlsyvXIeN/ZlPsn+RnuV77dYliJPxiLmnR6O29ydQHeMVt4Yn09jRPdMt9/SztlSnMUOQorrJrYb9sR3XUpXKT1QvvUjTBBrMHAiIhHzaz0L7Lh0ACOADOA7E9rZ2APAnPLjcpaHhpEF10IyMK3BxpNuTMYknV6rIb0DyIVkygt1UpPq+WO0JZZGkm4BXXEWvYq3bFkTBDIPRnwDoXByfQLHmO97W0lv57rljKKpW8qHWU1yv4+DpAXbdTH+8io8Q9H1mhISoYSCNunEeTabQ7Ef4PJcibsqgpPXsJ5Ep9sFEbXqq6CctCVsjs8itUJKfKNf3hXDk+oFdLWsIq4M8ieJIEf1kHf0BmvLearldcTq87qxU+7vGrfPQjwtjbl+5Ik1R/S1QxejYDrMjha7y9YhhUUU/akSxRJ+iovai+yQ20srI4/oviNvxM0/G8i6VOokAxaMiSS2g+lCJAFlP9xuOBMibziksLLsbR3TCR/uEUww0Q/oF5OIkoLhBv7qOsWCu4aieTPnY6woYbGSDo/0WF4SUVx2E4VvQHRUss7YeyWQRp6bm2xY1DoEF18JeJBOzV76f4O0TxqsuUi55MJhNmYu3hJRWptd+SxiZTx3uHk/LwK7ZBHe4oHcVfvHZUjmeKN2x43dkLHmekFuddxiYxR6hOPzvw9NUW/iKK6EQwViaVyce2FXOHGY7jpBvKuWW8dHklDbGV+mE27z0NGJvH05byBGAh9CJ9usTmL2AArI/7+cz2Ip6PWXKRooQj0YwGltd4LfnQ4EvGPik79h0jSEbhCsrr8RW9oHPfR5czJzN+tuK0Sb9GupM5Z4YcFy5GV0WGxAPpMnEG8UDzB3HJvXw4ipmjIAQaYgVE6/sLGdDRzsbRf2Z71p7F6t0vvmxtKCmjclgMHaHOyq1/2MG2SXt3SLQJUK/2Pihc6W23l6kqIlydn8PMXE+n4UPk89UYpQcWs+u8eONEj6s+PA0jPe0UaX9crNZLn9CduCgFYR1XH1KX4eG6DM9xbKSq/vfXRi255NerHGyBKDofP1yRsa6F3sOk9FNkc/zYJie+teJ2czp4Pg4W8ew1HxxkUHygwEeEDhZxgXeSJHSrTVf6CiqFRipFgkohUdn0K04=
*/