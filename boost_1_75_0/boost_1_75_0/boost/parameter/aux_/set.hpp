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
JrLo3wcT6dfyhmCn3sT8g5O7CIqDSQMwjAQSPLhDgiZocIcfCe7u7hrcGSS4BQjuGgjuLsEJ7gTJ4O4zDMwAM/uv1e5ht7ZqT33o6kvf3nq6PxIrERdu2SoVNqlYh3O+p1HUqNXKQVzvTPfNjhQmD2OEbOmYoIDNhXanFphpD9CN8JMGPZE+J0M5PLcNKhy5XyCSpnx27p3XvY7dD60RiJ2+AadgvEdVdE50WtyW9GvamPLt2T52xe1Z0PW6wtORY2RAbX++7eKhrAccsdc3APoxdgQGUqp6QhFqItc4aVBfgzA+eG0IqzoFQvbPCMI54zGCC3wxRM1/klhqnb5/ooKjjkCO+Oq6XsCN5KGhu/2b96Dt1QjOjId+WpHlMIl6rDqCB9CznEtKPxyhNhu5rYtYKdCUM7+hGgUQqqwhMv+azNNx33d2/ieU/0eh5v3wX4Ua4fkPoe4f4Gecbzofh2S3vZ9oY9hFitV+F8vQR97SNx8uo5Bhffwqb7xZkipYMKaEaLWIfsTdUjeDUkiBmayCRwMmHa6QXkE9u3RhXQH441GJeTEb/sVnqTCHPxEgz5z4V6AW236V+npAAfBXoD669Lm/CHT7u1DTIiz2ZhHnl1aIn44Lb1cGxVl9G/j1yOWvl6a/SO9LsGZOqrpD8U4800Oir7c7XDL2jkdEEqHoMiIlqPOxx1IPr/He0MiIMkiFusg4p7oEXsMb
*/