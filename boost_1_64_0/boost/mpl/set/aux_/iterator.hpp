
#ifndef BOOST_MPL_SET_AUX_ITERATOR_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_ITERATOR_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2007
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/set/aux_/set0.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

// used by 's_iter_get'
template< typename Set, typename Tail > struct s_iter;

template< typename Set, typename Tail > struct s_iter_get
    : eval_if< 
          has_key< Set,typename Tail::item_type_ >
        , identity< s_iter<Set,Tail> >
        , next< s_iter<Set,Tail> >
        >
{
};

template< typename Set, typename Tail > struct s_iter_impl
{
    typedef Tail                        tail_;
    typedef forward_iterator_tag        category;
    typedef typename Tail::item_type_   type;

#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    typedef typename s_iter_get< Set,typename Tail::base >::type next;
#endif
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< typename Set, typename Tail > 
struct next< s_iter<Set,Tail> >
    : s_iter_get< Set,typename Tail::base >
{
};

template< typename Set > 
struct next< s_iter<Set,set0<> > >
{
    typedef s_iter<Set,set0<> > type;
};

template< typename Set, typename Tail > struct s_iter
    : s_iter_impl<Set,Tail>
{
};

template< typename Set > struct s_iter<Set, set0<> >
{
    typedef forward_iterator_tag category;
};

#else

template< typename Set >
struct s_end_iter
{
    typedef forward_iterator_tag    category;
    typedef s_iter<Set,set0<> >     next;
};

template< typename Set, typename Tail > struct s_iter
    : if_< 
          is_same< Tail,set0<> >
        , s_end_iter<Set>
        , s_iter_impl<Set,Tail>
        >::type
{
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

}}

#endif // BOOST_MPL_SET_AUX_ITERATOR_HPP_INCLUDED

/* iterator.hpp
3SGs80loWpyPrW+NZYZZ5x/gi3wX+QL0W8395Rdj3hbs3x/QQPZOzecyn//G7d1gzL+L4y1qzFeAdSnuMrtyri1tLCjX9xWMheQaroqxqBwfNWDjRj6O7jDm6S3f/0W5/vL+rzHvVpn/Qzl5vvAAyn0r3/9AHLKf22OIoyxr39qYQ9Y9PG0s8gP73B7l5Fl0J/gic5tdYbcga9UDWsmz92RjgUtso4+xOPn2Yz+0J8/jB4PJ/LMf/sk6rVGwO1u+/+vCOgrO0UTo14+Po8nGnBNY56nI2488HryNunIt+i7syrPjudBexrBFYLLnxTJjDllbsQq+yP3ReuQo6CC2EfrJfOwn0Er2dt1mLPo8lwujnNyX7YNWh9nnw8Zc3eX9X2M+WWN4Aho04ZyfNuaOci7PGnOUkPk/6FyZtb9kzL9a1v+hD8m5LG8VqyvrGQoZC8mzoiLGwnIfdYsxp3zTu5SxTCePG+WNRV5jXVwol87+VTcWkH1raxvzlZH1f6hbhOfwGhtzp3F7TdHeLK57P9h+jvchxDaY+3NLY1G5/3gCuhxiG23Q3gXZ/w8++9huR9g4yHbjjXnLc867o+5GWf+H2MRnnzF/Eda5L3yWsW4Q/DvE17HDYaMBn2deBBvFmo4xFqxv5Nr5P9hoyzmfhPzKtcAb0Oo7Wf8HX3x8DzET7cn7oXOMOeUbPAuh1U6ObakxRwbHthI+y3dG16GusBDsyrvXH0ODEbL+z1hcHe4HO+HfRL7P2wtf9sj8H/ppa9bqc2P2UiKxr9Cen/vVKfhcWOb/kPOirMF5+Cd7qP2MvlaUbVxGjmStbp6qVlfuhQpWNRszOd7CYKVk/s9YSNbh3WrMW4H7QTljmXJ/VNlYVPZErYb25JsHt4PJvGM9+CLrMhrB7t1s425jbvmO+33GwrvZ5wdR7jP25dGq//q9xVaoK+v5nzIWeEe+/2EsOFy+/2ssInO0cbAh8z6JiFfWb7wAu7KvWqox11i2kWHMI/d0A8G+4b4xDHYbyPo/lIvK+j9jvl3y/i/i+I7Zq1Vxr8F1X0d7y9num6j7i4PYDJSL4+N3NvzT9X9gN7GNINqTZ5orUE7WjayFps9xex8ib2ky/weWIuv/UFf2nvg7dJH9Vfagj5/ia72D6AeS82PG/I04518iv/J+zzeIoxDn/AxsNONy56CffGv/J7AE+f6HMae80+W4zdgNnMsCxrxLOUc3GQvJnMLNxtx1uL2SxsLyPl1ZYw5ZC1HJWDBT1v8Zy5T5klpg8qytrjHPVrbb0FhE3se5C3GIps1QLpl9aW7MVZ7z+4gxf28u9xdjDvkeqddY3Db5/gdsZBQh1gF1xb8uKDeBY0uAXdn3Iwl15Tu3KcibnC/ToZW88zgA7d3Odocai8pal5HIb1MuNxr+fcDjyzhjvt2swSuoW4njmAK7LXmcnA67/WX+D6wk150FG924H8w35u7LuVyCcud4fFluzCF7iq1BXdk/dgNiW87lPoJ+t8r3f5FfeYdth7HAMPn+hzGvvMd3AL5s49iOgs3gul9Aq7/L/B9i2yTzf9BZnqlH4V8zvl67iHL5ZP0fYnta1v+hnMzL569mrBX3gxuNueVdj2LG/PIN6RLGgrI3ZBljEXn/oyLKPcJaVTUWle+Q1zTmke/y1IFd2a+5AdqTfQiaGHOsl/3/0J68v+CB3Yny/V9oUJLbexzlasj6P5ST78i2NeaTZ/nPGcuUfQI7o5ywbtBK3oHpacwh7/T3Rj5knXkamMwj9TcWJ/syDYHd43yOGmHMKRr8Dew9zvnLxsJVZP0f7J6R+T/UPSbv/8JuZ9b0HcQ7S9b/GQt8z77Mg/ZN2MZitJc=
*/