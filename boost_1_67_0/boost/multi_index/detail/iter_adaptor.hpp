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