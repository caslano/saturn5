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
1DTgItclUejUZHzzTQAmI4WHNRu2AlStUoN6+GPpwcejnfwqF2AX8FMhnxpUypAwlQkrBN1upz5jYtpgst709zBeeeYBV0GqXOwJJVP0QweCP9tdLi3u/3tDbwS7vcl2cbxQyrmdxSH8GMbT4mO03/K0lo6OSyD9KOaLQtN8kS4SiiChLfNFQav9Kft1g30B03HnwAY6VOIbDxgr0dr/wWsqvksb9BpHOr71afr+r5kHpW5igPbKNvD5Pzgn0dvT0Mj0PJLeHbHTe/fViPT0Nrr405jpBSLTK5D0rtwaCz3yf6rT8xK9bLHCcclLUHw+lKD8HeWY4dY+uT+2A5ct9n/3ReTfJ/k/J8T5j3q/S/k+M/u/phHOLW9rem0TgOALPxRFYuAkeV1TaX/t4b00PBISt6tzKaceOmLBJcWUvbFfp6Lwunevan9zn2J/k203298s2m9hf3MhzRwdL2L2N5OPOG1a/P6f3P7GWOFJSiHEsRzZRLL8I0lN+/SfuTDDBZkesu6WPiy+BplSkiXlsd2ZFVXenPU3xjTThjem46xsEj3Risthj3o4PhL9b17R6TcdiEB/U0weDSzp34z0jU6uPdoToI6kHJ0wJ59Ad85VNbAbp91kRU9NHd0pxMWUuSF/XRzqTtnzrZAqbGyKrpF2/xXfG2WW9uzyxr/vhWNoUBCp8Z1cRNZDxdsBqgl+VrQIwDP9XWEPKvM6KEhpVxRL2L3+/sR6B67gH8Pc1gl+Vkl+UDC/qhV2XNrFgpt85EZGr4Jo5bjpcGImizOTxZjJYsx0EsxIdc+w0B8YV6H+lORiTj7jMKZjnpSoQEJPOxI+DhJ62366vYnxG5+0RzTh4uqmI7iLzoKNDgwyGXL93bqUGC6dn1tfQ8PR5MUgyLJmmrM22PLKxN+TuNxrsRSXV0lx+eW/MiX02+LKxN1eJ6vBDuSx83VOTlynWN3kgFoGbyU3UM6NixIJj0n/l36IJxRuoqQtkESH6D6+meuBpQLbKwyyvVyiv5nrfRZZsDgEWGw+jEQlE3bWQGtynRQFB5YgOmmnObaoxiWzLIEs6Y0bD6DBNyWuIYMBMAllFZu6Cl9hCbruCC5Bp8BAf0s7vNE2HoHiKyAWEksxkZRDfyLmn1howfwlsCgLTebDUEouIGl74nFoINTNhLrCCnUUovIGPZ4++ajc+kepdmcsVCv+myBW/DZKylko1H/B4M+3Kjh+PxpwB4C2jy6kzme2GCnxP0LdFThRdxr/9WGo/EjjqT5of9jIaGDd0RVzYzDoqkinneAlDVnwbSv+0oHvYoe6U3y15sJVXMoNkIu2AHKMwf+YkJfTWsLpPfxMyU+RvTwV/7iWu3BACzeGpuJfmq8nZkDG0rnTMNQmZAE7TmTnYYd+/j8sQBLoGnKQF2P51lQ3z+3mYtvEzT9Qbi5saJ0go1shQnsMDQPWM5qx+GNi5YdOKAAj+8sxy48TiBEmtPz1TtS5hsmlzTLqG4uLsG9cjX2jVvaNbtt0lzZeRK1xRReEW+5fNjwvrMIu3IbaJVRjQs7Qy2fjO+g3maIy+v14vyVCJPj2xJ2I6kYXdxvv3Y6zlDbgEHypGayYe+9QlVLdxM4FlSTc9d1HO9hCA5iMf+MrXIrTYbiuCeLAdVQs5W3N/vk5ZT9r2A0x7aeuec60n/qbN4NtsjeeLjKVFHI3xGhvnKby+9TaqPqupmcV+Px1se3XbX7WzN/OHTHaxzL8JS3wf3N3G+yHhxG6jp34Rqz1K5zqIF6aNMltpX4adulLQemvK5umWJjnc+lVmfafoilm37xEm670K9uPs8/TlPQYJtEt7vuDUX25GfcXRhI72AWhK1ZPyPQ=
*/