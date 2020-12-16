// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_SET_060912_HPP
#define BOOST_PARAMETER_SET_060912_HPP

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/list.hpp>

namespace boost { namespace parameter { namespace aux {

    typedef ::boost::mp11::mp_list<> set0;
}}} // namespace boost::parameter::aux

#include <boost/mp11/algorithm.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename S, typename K>
    struct insert_
    {
        using type = ::boost::mp11::mp_insert_c<S,0,K>;
    };
}}} // namespace boost::parameter::aux

#include <boost/mp11/integral.hpp>
#include <boost/mp11/utility.hpp>
#include <type_traits>

namespace boost { namespace parameter { namespace aux {

    template <typename Set, typename K>
    struct has_key_
    {
        using type = ::boost::mp11::mp_if<
            ::boost::mp11::mp_empty<Set>
          , ::boost::mp11::mp_false
          , ::std::is_same<
                ::boost::mp11::mp_find<Set,K>
              , ::boost::mp11::mp_size<Set>
            >
        >;
    };
}}} // namespace boost::parameter::aux

#elif BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#include <boost/mpl/list.hpp>

namespace boost { namespace parameter { namespace aux {

    typedef ::boost::mpl::list0<> set0;
}}} // namespace boost::parameter::aux

#include <boost/mpl/push_front.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename Set, typename K>
    struct insert_ : ::boost::mpl::push_front<Set,K>
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/find.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename Set, typename K>
    struct has_key_
    {
        typedef typename ::boost::mpl::find<Set,K>::type iter;
        typedef typename ::boost::mpl::if_<
            ::boost::is_same<iter,typename ::boost::mpl::end<Set>::type>
          , ::boost::mpl::false_
          , ::boost::mpl::true_
        >::type type;
    };
}}} // namespace boost::parameter::aux

#else   // !BOOST_PARAMETER_CAN_USE_MP11 && Borland workarounds not needed
#include <boost/mpl/set/set0.hpp>

namespace boost { namespace parameter { namespace aux {

    typedef ::boost::mpl::set0<> set0;
}}} // namespace boost::parameter::aux

#include <boost/mpl/insert.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename Set, typename K>
    struct insert_ : ::boost::mpl::insert<Set,K>
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/mpl/has_key.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename Set, typename K>
    struct has_key_ : ::boost::mpl::has_key<Set,K>
    {
    };
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_CAN_USE_MP11 || Borland workarounds needed
#endif  // include guard


/* set.hpp
ZejqLfQUjn6uRFYhh5D+3M/koqvN6OkrJI37mbnV6OptFcdAv7raK9f91atP8j26wqzTfKnWlefeZMt4t65cARUnwzqHpWpl1UJZic7AsP5BbZ1BJpXVYN0Na9tNKr7ePveBzX7F+0AfvYle5uf7aY+i10Xq+uV+9Xabup4mevOk+3foLc33PQd9H3yrctOA3GDWfvKcIew0GUE7vg/5Bv+97Wm2lcgJewzjd4otH3kIOY60c6aocukp5XI8T9fhG7abx4yZlIvLGept6+q2Mc64bQyz1azdDytWcw79PCJTmUcTfxW96vu/5CL1PMPexN5D6zJD+Rvnt44OUNeHVtF1oui6hQrzgN1FvRzB7HgdcpC+7zmeI7UU/XdUbsLYZZaCqyjqUzNWwV22tXAHPMC+F3M/GV3g1dtM9OZTnVU3maUqdMU6Jq010leQykdXvYYdoMwPEW9X+k7/bfi8SvsAv/qxFct1P3UxXF1voesi8crY0MJvXXQpNw08+73Ezw2sMaaqJxLmeWxAoVdXnXz6yRxn2EXpaGeRe14fJzp6VZmP29S8Hj2tqEZPzxdVP29/qaj6eftbRaZ5u467U5V5+zlvfhd/5WlTE+VGJsub4Zrkd6Hkt7Hkt0KZW9r1fQx53ltNnqdfoG5cW1R93bjZJ88VfvJ8coI3z/epMnapMu5OljOddS6qjDurODrL+pq0TWZQDuyuIM+3Iu+S70Z2//1zG+VnoN/+uZ263ttvvnup6yk636RBxrUUeW4i/UAR+yuMPXmBS1qYz3sxu+mCm4cNN2FLrvM92yxG3OTg5qR6j3fJel7kNZ21Uzmsxbh7xHAXuuQd8xk3ZjebcJOqzmVbGmV+f94c3x7ctFDPRJYGugJDTOedVA7rtDe+8+b4zGHFF+PGnb8jLmdtm7909SrWYW32dTMEcxTmlnK2WynSit/JCM+ksINi3xq7NiLYaWkRCU3PsOKreYYVZz5v0PxMxrTnPSKWa+bnI3rPu1yzeHainlFbPOv2fUYdhfmYxTt0xyu/Q6eeVbufS7DPIt5tjpjo8+xank3dPcmdwSZukFbCIZ3bJ+tnU6YD30lvHp+dstXsWwfbJ9f8Wwe49X0PQY8be7hGKHpP0MeTa3ZmwMV8F+HtyabvIpjOEphbUlU/j9an3Xn1U5Q7JZ+PcU3iq1P5pF/rxfrcAEm70Q42oPvuhN+ImJg2qd20PudB6P1S30+W5xlybr2nLbStwXmCdSrroVL+sqYpd+z2IA0wBxrPVhOmSP7kI1zyJELlr6G7b9T3PsuU20LSJnutpY6bx/4xyk2E3iPSR5mHk5a27nMQVGpQoCnP9yg3jdTptC3RVwW6OsfG10tUH7TA5QqKCAp0RoSlqn8ZQUGu0CT6EqtzBq3OONTP8LKmEg+73KzOOtTvbCk3yfoZzxhlnmnzdwZi7tTKZyAuU+ZQ955qycu2Ke68OBesZcqcZMqB7aLz8JoKf061eYgslW8LSR72iR9/efjQJw8BpVXzUDpV8rDwaKU81PkFeYicpvawWudB0txEuSnwm+YkrpvTPBSzJ82NJc0JpZ40z9FpdiVdfHofVvooqja9z4gbf+ndVlo5vZ+VVk3vHp3euv9WenvXIL1DL5DeLJ/0zjeltyXpCcVNGmmJxXGSsAEShyyP0MI87SqeD3v26lt+Z07HOVaVYV05K7T6M1vbSr92Xvq1euIgGrmEfjtnuu7XVGfjr78tUO44SNz6OwKEc8ExyLR33OLMHUnnoelux4niqamMLxU6nWwEL1RpveDYgh/9XRUb4d6NyNjCraUxvAT5ze9tnvz+SuPLaeMqlbM5gUTYn333qQ9+bHjZnD8=
*/