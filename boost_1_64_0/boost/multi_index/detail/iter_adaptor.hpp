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
DA6Wd/Yds66iHsexuUYOVn2h5CAfMJjpKlyhxcC2q50QYH+UQyx/lOOhzuPn/JVLWzNV0Z1HisXAjqNwfAC+IQzm4o5jcPAdinoCLMww9GXM64cchCNxxyAwB9YPjgpAgDA4VHye09K0QLXyRFiWQ+MB9YWlfmDQlIg72ncxOdjnpA8JQCFhcBj66e146lmqlSfBiEy+V0f2hRKXvklcwxZH+/AWA3s8ODAA0wkDDFw65POyUxW1B+cDvgsA54V4zAc5cOehZHKwbQj1AfZRwsvXvk+kDpJEoTXMLSE0hLV5TZSZn/3AwL2CwCzMNfReAd6HPNLahzwFWjz7kPmfuuwP0XikPVyfaA+724m0edjrhuEB3pM+Ck+GlgOdhTmV75jCvpGHsuPUlsB1dHhE1MPE679ZHOC490dju1dMUmy202Cp9l/NApmn9mCXWDRV4v+GpLNw3yYHew21UgAqcxUG83AMKO4h+9rpcK2OMUMY3O4HBpEORztwFgPbrpQTgFa6a+wY8felu4wma9IZUElzZXWGyttS6HJsaKrA/2LnfGKlKxBsDsaeQwCyKP7WseLvM6866EGkiW8wmjBYQBjk+oBBk3MMJAd7bPyjkM/HHSf+/vDRd0aQRQ2eor5QRhhU3ey0L8gaOh0PPBx4TFxWCEUUSwP99x7YZvDrqpVn8578Aso72g8MnHloWAzsmHxLCzFmjMTgBLQvHL3tV4p6Du+7xLNV3m4/MHDmlWAxsM/5LCmEzUkO8PL/0u3GbaCo58JP2ezbLtdQIw9xiUGoIyx/uQsqYrHw6ghvFqLtTOJwEq6nP1g8UVHPwxjfKq4Irafn+YKDOy9/ZvGP/PzPZ9/2JRjmGjE7zqGvTrqSXe2udiNNFsuNwwWMQ1mm0pe+8kceOjuijk5Q98ODfdwXF7Lv1ini8+pHWsjmeiGkckgeaG291OnaWtfRodXVZmHrjq8Uss3xVMvmOJ9jNO6r/Vs/cak36Uo6tDqaLJa7X1wEj0GfH19wmOnIj81i4fVpfLQQekgeTsdofKETKc7OxXA82ZzmrajGhxlzXfcLse4Vny5hMDmw/nRHIZxLGGDjN5x9wceqlZdAXQ5hMFj1idEu7+AU967PKZ9QthF/cQNEHzZeHeL29BhxpjVGXMpjRI/4xO37YIVLPFqbkhur384GCZuHbZe/qJDj9J2FI+SEw69QLb0Mxg4leyzdZT1josPz0rqOGzck26OubgzxMPGuMeYXwmiSibPxVrFdHgwp6uUwIyt9jn5VxC3ucJxIV9MPKJgH2+iPLeS9WwzYt/3nZWSfvgJKCmmttQrF7fNHJpzpERYL717FnoUwhvoGjp0rHbZkPYp0DbmrkzysRn1jY19wCMeijsyyNg/bn2G3QqglecALAVrOe+5l1dKrMJYC+0DnYx/q8aVfhFIpx2Ml8zBjmhby2frzrbP1V0PZSJKHPKVfL/ZnfHC3e2XzsO/kFDisSjhcgL3hlKfpDr5roMzQr/Pw06kuIevYGI01iHq6hIFZ2PPFtLQOcaGlQ1zLcVcWZ6h+sch1vyivEB/lFU51CIOHFXNiitAhCIf56OXU1HWoaul16AutdCmKdVs7ywccyitEnBxHnm82D/tsabAQdiMcLsKIE0NmPSKJIkJ8NZ0ujBMOj/mEQ7Ix5OjUjIeJ1/dpy0L4mLC4WHw+13sFxbm8Ac7L5PsBJBbBhD9YxKsc6lLMw6NLbVHIsfEvwTP3O/6yvbbYxzMoHlGmwuF233BwtPq0edh9Y2IhnEI4oCA0p1prVEtvhBnUNx4brOLS5C6qdKtLUR074iFH1koPE689Ymwh+wlfhnrEbR83KepNUJdLegQ=
*/