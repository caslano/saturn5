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

#elif BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
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
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
*/