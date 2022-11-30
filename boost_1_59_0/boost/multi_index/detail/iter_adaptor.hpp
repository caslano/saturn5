/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_ITER_ADAPTOR_HPP
#define BOOST_MULTI_INDEX_DETAIL_ITER_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/mpl/apply.hpp>
#include <boost/operators.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* Poor man's version of boost::iterator_adaptor. Used instead of the
 * original as compile times for the latter are significantly higher.
 * The interface is not replicated exactly, only to the extent necessary
 * for internal consumption.
 */

/* NB. The purpose of the (non-inclass) global operators ==, < and - defined
 * above is to partially alleviate a problem of MSVC++ 6.0 by * which
 * friend-injected operators on T are not visible if T is instantiated only
 * in template code where T is a dependent type.
 */

class iter_adaptor_access
{
public:
  template<class Class>
    static typename Class::reference dereference(const Class& x)
  {
    return x.dereference();
  }

  template<class Class>
  static bool equal(const Class& x,const Class& y)
  {
    return x.equal(y);
  }

  template<class Class>
  static void increment(Class& x)
  {
    x.increment();
  }

  template<class Class>
  static void decrement(Class& x)
  {
    x.decrement();
  }

  template<class Class>
  static void advance(Class& x,typename Class::difference_type n)
  {
    x.advance(n);
  }

  template<class Class>
  static typename Class::difference_type distance_to(
    const Class& x,const Class& y)
  {
    return x.distance_to(y);
  }
};

template<typename Category>
struct iter_adaptor_selector;

template<class Derived,class Base>
class forward_iter_adaptor_base:
  public forward_iterator_helper<
    Derived,
    typename Base::value_type,
    typename Base::difference_type,
    typename Base::pointer,
    typename Base::reference>
{
public:
  typedef typename Base::reference reference;

  reference operator*()const
  {
    return iter_adaptor_access::dereference(final());
  }

  friend bool operator==(const Derived& x,const Derived& y)
  {
    return iter_adaptor_access::equal(x,y);
  }

  Derived& operator++()
  {
    iter_adaptor_access::increment(final());
    return final();
  }

private:
  Derived& final(){return *static_cast<Derived*>(this);}
  const Derived& final()const{return *static_cast<const Derived*>(this);}
};

template<class Derived,class Base>
bool operator==(
  const forward_iter_adaptor_base<Derived,Base>& x,
  const forward_iter_adaptor_base<Derived,Base>& y)
{
  return iter_adaptor_access::equal(
    static_cast<const Derived&>(x),static_cast<const Derived&>(y));
}

template<>
struct iter_adaptor_selector<std::forward_iterator_tag>
{
  template<class Derived,class Base>
  struct apply
  {
    typedef forward_iter_adaptor_base<Derived,Base> type;
  };
};

template<class Derived,class Base>
class bidirectional_iter_adaptor_base:
  public bidirectional_iterator_helper<
    Derived,
    typename Base::value_type,
    typename Base::difference_type,
    typename Base::pointer,
    typename Base::reference>
{
public:
  typedef typename Base::reference reference;

  reference operator*()const
  {
    return iter_adaptor_access::dereference(final());
  }

  friend bool operator==(const Derived& x,const Derived& y)
  {
    return iter_adaptor_access::equal(x,y);
  }

  Derived& operator++()
  {
    iter_adaptor_access::increment(final());
    return final();
  }

  Derived& operator--()
  {
    iter_adaptor_access::decrement(final());
    return final();
  }

private:
  Derived& final(){return *static_cast<Derived*>(this);}
  const Derived& final()const{return *static_cast<const Derived*>(this);}
};

template<class Derived,class Base>
bool operator==(
  const bidirectional_iter_adaptor_base<Derived,Base>& x,
  const bidirectional_iter_adaptor_base<Derived,Base>& y)
{
  return iter_adaptor_access::equal(
    static_cast<const Derived&>(x),static_cast<const Derived&>(y));
}

template<>
struct iter_adaptor_selector<std::bidirectional_iterator_tag>
{
  template<class Derived,class Base>
  struct apply
  {
    typedef bidirectional_iter_adaptor_base<Derived,Base> type;
  };
};

template<class Derived,class Base>
class random_access_iter_adaptor_base:
  public random_access_iterator_helper<
    Derived,
    typename Base::value_type,
    typename Base::difference_type,
    typename Base::pointer,
    typename Base::reference>
{
public:
  typedef typename Base::reference       reference;
  typedef typename Base::difference_type difference_type;

  reference operator*()const
  {
    return iter_adaptor_access::dereference(final());
  }

  friend bool operator==(const Derived& x,const Derived& y)
  {
    return iter_adaptor_access::equal(x,y);
  }

  friend bool operator<(const Derived& x,const Derived& y)
  {
    return iter_adaptor_access::distance_to(x,y)>0;
  }

  Derived& operator++()
  {
    iter_adaptor_access::increment(final());
    return final();
  }

  Derived& operator--()
  {
    iter_adaptor_access::decrement(final());
    return final();
  }

  Derived& operator+=(difference_type n)
  {
    iter_adaptor_access::advance(final(),n);
    return final();
  }

  Derived& operator-=(difference_type n)
  {
    iter_adaptor_access::advance(final(),-n);
    return final();
  }

  friend difference_type operator-(const Derived& x,const Derived& y)
  {
    return iter_adaptor_access::distance_to(y,x);
  }

private:
  Derived& final(){return *static_cast<Derived*>(this);}
  const Derived& final()const{return *static_cast<const Derived*>(this);}
};

template<class Derived,class Base>
bool operator==(
  const random_access_iter_adaptor_base<Derived,Base>& x,
  const random_access_iter_adaptor_base<Derived,Base>& y)
{
  return iter_adaptor_access::equal(
    static_cast<const Derived&>(x),static_cast<const Derived&>(y));
}

template<class Derived,class Base>
bool operator<(
  const random_access_iter_adaptor_base<Derived,Base>& x,
  const random_access_iter_adaptor_base<Derived,Base>& y)
{
  return iter_adaptor_access::distance_to(
    static_cast<const Derived&>(x),static_cast<const Derived&>(y))>0;
}

template<class Derived,class Base>
typename random_access_iter_adaptor_base<Derived,Base>::difference_type
operator-(
  const random_access_iter_adaptor_base<Derived,Base>& x,
  const random_access_iter_adaptor_base<Derived,Base>& y)
{
  return iter_adaptor_access::distance_to(
    static_cast<const Derived&>(y),static_cast<const Derived&>(x));
}

template<>
struct iter_adaptor_selector<std::random_access_iterator_tag>
{
  template<class Derived,class Base>
  struct apply
  {
    typedef random_access_iter_adaptor_base<Derived,Base> type;
  };
};

template<class Derived,class Base>
struct iter_adaptor_base
{
  typedef iter_adaptor_selector<
    typename Base::iterator_category> selector;
  typedef typename mpl::apply2<
    selector,Derived,Base>::type      type;
};

template<class Derived,class Base>
class iter_adaptor:public iter_adaptor_base<Derived,Base>::type
{
protected:
  iter_adaptor(){}
  explicit iter_adaptor(const Base& b_):b(b_){}

  const Base& base_reference()const{return b;}
  Base&       base_reference(){return b;}

private:
  Base b;
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* iter_adaptor.hpp
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
*/