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
TYcUA4vhC3+TJaxLwmabYLNx8cGOLGFDJewQE+yQYvii60GviCtD0x2yCW2TXTgwv4ItBuYg9818YO6S+9jCNByLsl4TT9FwLMCo8RU8pEqBln7jYf7rrZvgF19XHgDUgbVVII+e8waRk+yYFA3v6EwrejruZw3FhrNipyVMJh6zv9o/OzOToxwcUYkON7GBPCDEhihw6TfxXkclOGn3LQ202FUfl6BjYhdEN/UIejRAcpMZuWSEM7WgvqOQjj+grsmdvfWLougprT4C+ZtC2QxLfk1W1q5QHAyy2PwI/Om/m5m1LScd4YgaoBRPQTLPa2A0tEIOZgEoNSdN3Okl6yhbuxp0uezzmMOMMbP0uHxz6AHvemxmPx35zSDmN+U7GYb50OygH6h4oYSvnbIETCaNuLzgnbYRp3WtHhhVQYPDnR+Y/E7HEJ25SGcuruuPOWmi9AKM1BukabUSqCtE00z+fVPwKDEeQKvsEF2dpqaP+p56XB7N/S9dwho9i55GDuNNS4+f9+P7YpqIVAkhDxkiDfTq8014rIhLmgbGEty3CE45rP194Ywma+BAF4KjfiLP4Hk/8ch+Qk5NZT/xIBDzBJrfQEEbGQxtV4a2K0cbq6Dt2tkbK9HGIpB/LSwiYqiLUxSmWI+iJnd5eIShRXad0f31OaP8xVbKGr3UeNCaHeG2/rdcrupiFG5XQzrr0nKvkaLcQbzSJRfALoEVipR/AdhbssdM6GR85+OhPNPjgDieKeysF8RK/o96WladTuKrZkGdY5wF1xtZ8Ayky61HNgleUgSIYmcPPgyhbGbOI831ivaUO5XptNylKMxKUJmlIBjc/Fxyynq/fSijyqM1Otu88yvOmRQgTknf95VZGk7Tbjkt5cjwwD+rveuk/bXVpqJ9hr7TFC3rZbTop1C07c5jEjetcT1ZArBZmnGj5YBQ70NROBmrC0WO1uiY3IqWYAY0ORdosSxFh/x1gESOvM7pHnG7aloQZ/qUYzPkEM70Rdp7Ab6BzBQXXfKIkrtSWAcAk+QSE8UEqdM84huF68W/o+huHn/F3ZSjQjWWSLbeStHTUA7gesyjFRXBZL0R2NsILFH0NHFoyw8afZdTAnmJrNjFBiV3EpleMo/uXM37xc1PKgKgQtWRZgHfA/cSqbxDZRsJJ7jyQHAah+rophxVaWTn7lVS9yhR993Pgrq+Bur++SVQN0/xfDpKejpluK+Tj2TyFi+f1fIwpbdHlvkklTkRy5S2AG+johSfxB1RucXqDIn5MToNQgMRFQjzbz99LvYz5/oD97s7Q3Nvs44HqJ70fXy58aQvK9igzdKuAdew5KR7ogvlQZH++JU8CgYJNJ+GkmdslL+Ei3WnLwL/uHwXBK4AD2M1LwiBgzoSkPH6UIVb3xj8fB6cp2QB0BctDUB3qUDvIlAbXkIcAG80Ag9RgVcCsJCfp6a6ou/7G7SXSBABsl0iQDb6BS9GV+a7RLyOSdEzP0Sg4fAMtgfrvi2riF4/zenwxDuKp035MDre4Q0prTiCcetOK8XWhP7kf5PoOaG++G4QvNhELwLqi/fxxRP04jv1xVZ8wavmV188DS8Ct0Pqp2rqfEwdAqllaurdmNoTUt9VU0dgakpQboC2BnK8pOYY3EiwEweYA2dsMgOKwD9OX2zgesiyVM3iwEJ6YdxFNfXLgSoi2iFNLXVl4GqQiUkHJGjUxQ6HVMvc9Is+5HK3zbupdryjCL4PwnctfHfB9zB8T8A3EhonDr4OpyvE/es/oWE13GfzCd/7P/6B+eb9H2i+kfF+Txmf/abn3uX0bCm/l7P7r5fyqSms0+W1HN4O23FPfYTbABQYgv/CsHymFmQ=
*/