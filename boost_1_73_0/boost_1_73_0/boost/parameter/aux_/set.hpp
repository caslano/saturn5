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
W8wqSvTggNaA8hAtUA1ev4VrgJRuEf0arLh6qzV9b83Prf8BUEsDBAoAAAAIAC1nSlK9sNVZ5QIAAJMGAAAkAAkAY3VybC1tYXN0ZXIvdGVzdHMvbGlidGVzdC90ZXN0dXRpbC5oVVQFAAG2SCRgrVVRT9swEH7PrzjRlxaFBvo0GJrWFTaqsYLaIlQJKXLja+Ph2JHttCDx43eXFDrQpvKAq8apc3ff3XffpS21MBIXcHHePzsfp4Ob8WV6Ofw2PZ9MU77cTIeX6UXUIhtlcJdZsv9xK4J92LnS+pvSor32uHb2N2bh39Zp+gTNh7zuaN8FksDW5SntwG6XJ2jXLukG5ZTv03QX0B3nxpeEPe9SvqUTcmPPgS0fnVrmAdqDDhwdH3+CA+gd9g5jOBNGoYZJQDNHt4zhVNYnX3Px8ND1+CUGDCB0dxNqmisP3i7CWjgEutcqQ+NRgvAg0WdOzemHMhByhIXSCIOr69lw9COGda6ynIM82gp8bistIRcrBIcZqlUToxQugF2QOwWXygcKWAVlTZewEQK6wnMMhhfaWxArobSYE5AIkIdQ+pMkySqnKftE2swn2XP53TwUL5XMKIlCPIItAwQLlccY2DKGwkq14J0IocOymmvl83ibDUEZmVgHHrXmWOSn
*/