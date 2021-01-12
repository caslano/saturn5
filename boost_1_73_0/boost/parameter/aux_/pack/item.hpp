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
ZGaSjCSZYWbSFkRClmk7kI3MpLSIioqKigoIiIqKioqKiuKCiIqKijuKu4i7IoIsRUTF5dx7zz3vnNv3oC4frD/MvP+979xzz13eeXd7ffw7e5zzb+1xzr+3xzn/5h7n/Lt7nPNv73HOv7/HOf8GH+f8O3yc82/xcc6/x8c5/yYf5/y7fJzzb/Nxzr/Pxzn/Rp/kPcgvdfgm5Jc5fDPy1zt8C/LLJad9LVc43Ob3Sofb/L7B
*/