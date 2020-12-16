/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BACK_EXTENDED_DEQUE_26112006_2209)
#define BOOST_FUSION_BACK_EXTENDED_DEQUE_26112006_2209

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>

#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/container/deque/detail/keyed_element.hpp>

namespace boost { namespace fusion
{
    template <typename Deque, typename T>
    struct back_extended_deque
      : detail::keyed_element<typename Deque::next_up, T, Deque>
      , sequence_base<back_extended_deque<Deque, T> >
    {
        typedef detail::keyed_element<typename Deque::next_up, T, Deque> base;
        typedef typename Deque::next_down next_down;
        typedef mpl::int_<(Deque::next_up::value + 1)> next_up;
        typedef mpl::int_<(result_of::size<Deque>::value + 1)> size;

        template <typename Arg>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        back_extended_deque(Deque const& deque, Arg const& val)
          : base(val, deque)
        {}

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename Arg>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        back_extended_deque(Deque const& deque, Arg& val)
          : base(val, deque)
        {}
#else
        template <typename Arg>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        back_extended_deque(Deque const& deque, Arg&& val)
          : base(BOOST_FUSION_FWD_ELEM(Arg, val), deque)
        {}
#endif
    };
}}

#endif

/* back_extended_deque.hpp
/QjBmO5kPHCBun0Z0j9SX/4gyxYQVq819KX1XV4P3K9RxOp+v+Pv/m6M2rcjYtlzyaVJP8bssU9bVv3t+r3afZC9kZQtKXMJuIWQJfe5X8h90Jc4GL/GBGT8l5KxeCFuxItQ7T+PSp+FTrgOL8YfsTMq9w9d8AG8BL/DbtiqIW2A2BctOAHTcS5m4AM4FfdgJn6OWaj0GcrGXpiDUzAXb0Ur7sLp+CXOwHZskw1H4kycjXn4EObjmzgL/4UF2IvrZgdORicux0J8BmfjX7AI2zbhehFH4Fx04Dxch/PxDbwBlRvMBdgbF2IaluCtuAh34RL8ApdiG/rY3IjDcRk68SZ8EEuxEm9W0ou3YK+zuM/C63EF3oK34U5ciZ9jGZ53NmMWYTzejg68A9fhanwd78J/4u+xRzP6QOAkvAdvxntxB96HX+AabNOce2kchn9AO67FP+CD+Bquw59xPUa24P4Or8eHlPTiJlyDm/ExfBj34CP4Nm7BY7gV/4HbsMU53N9hJyzHJHwcF+Ef8Ql8Aj/D7di2Jdf0OAqfwnn4NG7DnfgB7kKlR+AzOBR3owOfxYfwT/guPoe/a819Hl6Oe9CKL+B9+CK+invxX/gS9jmXczpm4n68Aw/gXnwFf8CD2DWc+zyciK/hrfg6PouV+DW+gRedR18MHIOHcBG+jU/gO/gZvott6dB4GEfiezgHj+AWfB8/wA+weVvu+3AIfoSzsAofxD/jW/gxNmrH/R8OwE/Rip/jPfgFvoLH8B/4JfY8n/tAtOBXuAqP4wv4Nf6Af8VL2nO/hePxW7wJv8Od+Df8Cr/Hjpw/f8Ak/BEX4Um8C3/Crfh33IP/wMN4Cr/BnzGsA30+sD3+C6MwtCH3cXg2DsFmuByb43vYAi/tSN0uOrAlVmArbM75szVOwnNxE7bBJ7EtvovtUPk9S+V+y0bYH6nd1xXz/+/7aPdnS4P3YsEpOAWn4BScglON9/9Tz9T9f6E163Q896/c359neK7fda/eULahAUG5rkvW7sGSkoePHjcu0WJ1OLKdhdOstLXW/my1656xIuS305a3LE6Z/3z2tnHDzpqfdCikdOWWTtWZrucEJD8knzYT9H7a8m4pxfbYAC/AdFed+RmqL98fvCYLTsEpOAWn4BScglNwCk7BKTgFp//YdEbf/19o5Z+l0Gk9Pe//b2Vo418jdQCnCJ0IJwjPKeO5LVbvecePsoxPGZVoKcjm1Wv2osD7Z2tjfU0tzJF5ucZ5Od7vWHNY52bTPuExTp69gDTzZ+Z7jJU3O7vAmjMnRB/zyPzdYxu6K/MKrSFe7xsskz4N2wh9CasJP7QhbUvMtlcZepDsC5HtrmWcrzh9nC/yoIFhe2UbcpnndI21N82Z69o2ewPzbS5uYL7N/f2Muba+u56/ej1MRKi/tvv/vnqYjZ2V+esev/f5N1+edXJe6x3hPZqeuNZfPVLd+x6Ux6njU7x0X5cF41ssat9l89pTj1xOe7U8Vy9lnmNB6sb05+rlneCdsBN2xy4YhZfgIOyK8dgNk7G79E29DG/DHrgXI/Eg9sQj2As/xSj8Cvvg37AvnsB++ngGUkal7JI+j/EMzpXn39viYmyPq/AC6RPbAUtxg7y/Zbfdt09n/yGB1VOFX6XVVR0bFmZaXxWx2bfO6hTLNuWB7Q6E2Phg/VVwCk7BKTgFp+AUnIJTcPptT2d0/H/t/l8Wrn/f/zb0/d+sjP//kdKW7ciY7bBOI9nq/IsxrkqZ73TOseQX8Bd9frw+n7FQZfn5bHGCPp/3ohvmJ7vXU+iU+Yqp6nyrw5Jh4Y/cqzA/jfS0W6XMd28pi6p/s3FTlKZ9h3HlLaSWR8U=
*/