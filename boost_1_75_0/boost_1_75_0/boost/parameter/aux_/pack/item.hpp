// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_ITEM_HPP
#define BOOST_PARAMETER_AUX_PACK_ITEM_HPP

#include <boost/parameter/aux_/void.hpp>
#include <boost/config.hpp>
#include <boost/config/workaround.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    // A parameter spec item typelist.
    template <
        typename Spec
      , typename Arg
      , typename Tail = ::boost::parameter::void_
    >
    struct item
    {
        typedef Spec spec;
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
        typedef ::boost::is_const<
            typename ::boost::remove_reference<Arg>::type
        > is_arg_const;
#endif
        typedef Arg arg;
        typedef Tail tail;
    };

    template <typename Spec, typename Arg, typename Tail>
    struct make_item
    {
        typedef boost::parameter::aux
        ::item<Spec,Arg,typename Tail::type> type;
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* item.hpp
f6eIbfkFpjciQLyQk/cIoBFS8defB4cuVTzJBw8HQvUvZpB1kY9QjpCPUEmRSIVbCCe5Wzj7ZYGcP9XshKTcQz8Ko72PAr5IVN7ErGBnrdwMPiTdgYedQpuehZapWSou1j4d/VQq9NPw6wB0OrJ+41CcfzPwpeleMj5t7t1bI7a4IppcWTjTgszH+T4ewnw87sLDY6KQwECzI37gzHWCCo3eobS4BKFOEi7PjhBSTXH4E2SlGp4xcLBdc5C84Wk3uPgqaLC1vzdYkAxns/toYqDN4KEogORWD/nuFuPWqP6FW3Z+UJi6TE+FLUuhUl/JG0RwWGKxS190cCaqSFC1SP8FUDuVhNVc4io9XukLUGF/dDn8SQceiKoXbhdersBsiP6odAeQSwlKAvYQCWY049l1IUDNMyF23Zlf4mgjnwFo1+jbituJA7mhAmlxWNU33egdJJWoqykBJCuobsiuSCsoAgQSGzK5Ye0o7UjtKGehdwMuA+h2ypwh7ai5oSKhImHTAyTbHNsuA7rRPhUdpGBR4sfQdrUfga9cosPcUGiQfZC7w9zQacoL88n85sh4uxMJNUB/9HAS86Hi01NcXdGQcz/f2Dt+IPmQ1hs7/oU4dkw4EHqaPAajMxbKi8HLxnDaZ/fdIj9pRh+0LQMMnLbUyOzL/ORO2zokZ7Wm0GWxgFApgrNj5WuApLHksSmlsryR8y+jd7l4bO+8
*/