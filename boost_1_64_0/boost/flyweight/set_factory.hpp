/* Copyright 2006-2009 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_SET_FACTORY_HPP
#define BOOST_FLYWEIGHT_SET_FACTORY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/detail/allocator_utilities.hpp>
#include <boost/flyweight/assoc_container_factory.hpp>
#include <boost/flyweight/factory_tag.hpp>
#include <boost/flyweight/set_factory_fwd.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/if.hpp>
#include <set>

/* Particularization of assoc_container_factory_class using a set.
 */

namespace boost{

namespace flyweights{

template<
  typename Entry,typename Key,
  typename Compare,typename Allocator
>
class set_factory_class:
  public assoc_container_factory_class<
    std::set<
      Entry,
      typename boost::mpl::if_<
        mpl::is_na<Compare>,
        std::less<Key>,
        Compare
      >::type,
      typename boost::mpl::if_<
        mpl::is_na<Allocator>,
        std::allocator<Entry>,
        Allocator
      >::type
    >
  >
{
public:
  typedef set_factory_class type;
  BOOST_MPL_AUX_LAMBDA_SUPPORT(
    4,set_factory_class,(Entry,Key,Compare,Allocator))
};

/* set_factory_class specifier */

template<
  typename Compare,typename Allocator
  BOOST_FLYWEIGHT_NOT_A_PLACEHOLDER_EXPRESSION_DEF
>
struct set_factory:factory_marker
{
  template<typename Entry,typename Key>
  struct apply:
    mpl::apply2<
      set_factory_class<
        boost::mpl::_1,boost::mpl::_2,Compare,Allocator
      >,
      Entry,Key
    >
  {};
};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* set_factory.hpp
dOzIeCXppcDQSeJX452JVyP/OCqyIZmK5jsyyGWOoPuTvMnlgWSJ58yY1BmlpoWpMv1ck68ZA7zi77GNyMAftZe8VAA3UHyK4IRIUmUqr+VMOZcc489/wwZ8CI+UwGIXp3LPbdTRHiRBlYDbOUDhx+z0ebjwWkGbGV74Pr7/dp+r7NpX3pvgBr3CGLJxlBAK0ToaxAe7Wu8WvRdapcviGcbMqz3oTcLihoO37nMHz9jwh15CGdhMuJXpqNl/EZtTQfhLpkFBfbwPCXz3AN9U71vK2KZ+tdiZfHggKJ8YwOjjkw/NPGH3xR1tO2iZv/GRbTWalHHE/hGsHheAlK/kEnWTG4kc8Xw1k0Tvjf28Lkj2izfXA0zIzxp9AyXvpg8J+UtK0OTZE7TweNfjtjywO9YaBNRfBhUfSb6+87Z7hT2+xwZZEs5xAu81zOiX0vdLFijPbb0U5W2KirCc3TzdUu84w+BF28x4Z0JJD3/dkST05SQh0Q66ASkHy0V+q3QrIJrhXncdadeI3rj2XShSwkw1mXl2GiOOSnVNRfpwWNpabck8J4KH41VtNg==
*/