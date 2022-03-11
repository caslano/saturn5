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
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
*/