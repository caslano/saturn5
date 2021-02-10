/* Copyright 2006-2015 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_ASSOC_CONTAINER_FACTORY_HPP
#define BOOST_FLYWEIGHT_ASSOC_CONTAINER_FACTORY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/flyweight/assoc_container_factory_fwd.hpp>
#include <boost/flyweight/detail/is_placeholder_expr.hpp>
#include <boost/flyweight/detail/nested_xxx_if_not_ph.hpp>
#include <boost/flyweight/factory_tag.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/if.hpp>

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#include <utility>
#endif

namespace boost{namespace flyweights{namespace detail{
BOOST_FLYWEIGHT_NESTED_XXX_IF_NOT_PLACEHOLDER_EXPRESSION_DEF(iterator)
BOOST_FLYWEIGHT_NESTED_XXX_IF_NOT_PLACEHOLDER_EXPRESSION_DEF(value_type)
}}} /* namespace boost::flyweights::detail */

/* Factory class using a given associative container.
 */

namespace boost{

namespace flyweights{

template<typename Container>
class assoc_container_factory_class:public factory_marker
{
public:
  /* When assoc_container_factory_class<Container> is an MPL placeholder
   * expression, referring to Container::iterator and Container::value_type
   * force the MPL placeholder expression Container to be instantiated, which
   * is wasteful and can fail in concept-checked STL implementations.
   * We protect ourselves against this circumstance.
   */

  typedef typename detail::nested_iterator_if_not_placeholder_expression<
    Container
  >::type                                handle_type;
  typedef typename detail::nested_value_type_if_not_placeholder_expression<
    Container
  >::type                                entry_type;
  
  handle_type insert(const entry_type& x)
  {
    return cont.insert(x).first;
  }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
  handle_type insert(entry_type&& x)
  {
    return cont.insert(std::move(x)).first;
  }
#endif

  void erase(handle_type h)
  {
    cont.erase(h);
  }

  static const entry_type& entry(handle_type h){return *h;}

private:
  /* As above, avoid instantiating Container if it is an
   * MPL placeholder expression.
   */

  typedef typename mpl::if_<
    detail::is_placeholder_expression<Container>,
    int,
    Container
  >::type container_type;
  container_type cont;

public:
  typedef assoc_container_factory_class type;
  BOOST_MPL_AUX_LAMBDA_SUPPORT(1,assoc_container_factory_class,(Container))
};

/* assoc_container_factory_class specifier */

template<
  typename ContainerSpecifier
  BOOST_FLYWEIGHT_NOT_A_PLACEHOLDER_EXPRESSION_DEF
>
struct assoc_container_factory:factory_marker
{
  template<typename Entry,typename Key>
  struct apply
  {
    typedef assoc_container_factory_class<
      typename mpl::apply2<ContainerSpecifier,Entry,Key>::type
    > type;
  };
};

}  /* namespace flyweights */

} /* namespace boost */

#endif

/* assoc_container_factory.hpp
AwAA9QcAADMACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1JBTkRPTV9GSUxFLjNVVAUAAbZIJGCtVFFvo0YQfudXjOiLHRF8aU5Kr01P5RxyoSHGMviuliKhNSxh72AX7S5xoqb/vbMLbi7XSMnDYeGFYeebmW++Wf/ahYMfdjm+gYMXr9zeOV647p2WUnyhhX7eIc8fYPih4zWurwg1g0evh3wKr/J6gIn1ysdYp+Y5z18R7tokaf5mxvk6N49oGTxH/7no7iW7qTVM5lM4evfuFziEn98cnXhwRjijDaSa8i2VNx6cltbyR03u7nxF33tANZDGfwKY1UyBEpXeEUkBnxtWUK5oCURBSVUh2RZfGAddU6hYQ2GeLDfR4qMHu5oV9YhzL3pQteibEmpyS0HSgrLbAaYjUoOoEAHxS6Y0YvaaCe5jeAqaylaNMCYJ0igB5JawhmwxHNFQa92pX2ezopcNVjIrRaFmxZ4Kv9btd1VtMJuW3IPoNGgBvaIemP0etKJklVmRIjR2/bZhqvYe08KAvJwJCYo2zQiHroyqoQQK6ciWZ3ZCh9kzbRYluDLRdrVon2xEWkegqpccwyEtuK8USLwHPS+ptPstEfsoI8uW8hda9ph7CYJj
*/