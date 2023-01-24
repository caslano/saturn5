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
x44z8FULYCzHX46s+020JmWd/Qev9S7lsumNhC0OErZcwMKWuxIx+9RG5Zs/uLlJoeZm6s2l/2FqOi/fMYBytk6wLjuoQbmaI59iWkKSd3vk8VNVxx+RmtYQT4bSqwlBLCU1A58MK9bSyTD4SzoZFr1A+GKpkkLeqJhA9v1I3r9LlSrAF+SF/bPmyfU9XfxkL9lh1mJ7yEcZtWM2XQkz6ZIVzioCsX0AHu+JhbCXTON3DCD28TsRxmDmGohNbAhi72EZS2VdZj0eiN5wGjds2FAfvRMGu9qGmthwQ32CZQy7Z2hy9c3EwkyV4fjIcXt89i7VMTCKztxYoMou98bDv1d4Y/DUUR2LInAeR+znuxOWCAZ/QBqqo9aCeLyKAniju38ePqUvbaUvFZeWF+fZl2ZvneDyRyYZAJ1RqmGjaAA9UQfoSihVKf/jBKJD55saJjqqVn46amLdQBerBmbbtKJIvWgVFrEazHeEIfTDo/z71lGTZj9g0+gTSo2ENgSX7teg8Wg2QSMmo5W9uUTVUlIa3/gDMF4LZh1yy9UampoW44/ybVXrULCBGp3RNTCUA7Sei/mtWgFWtbCgr1bqkALMTE4tTsQFoo6eR6CWWsFChJXiaZzTVsnmuRcy7mnR9N1ghDxDCZvcAxy1lHurxXXKOYqTe8n4BhF7tCgLNF3DfxeTuTRCm8xJR0xNxMleQz721TCcfRV4LJxy
*/