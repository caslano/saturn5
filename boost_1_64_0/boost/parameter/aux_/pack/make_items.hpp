// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_MAKE_ITEMS_HPP
#define BOOST_PARAMETER_AUX_PACK_MAKE_ITEMS_HPP

#include <boost/parameter/aux_/void.hpp>
#include <boost/parameter/aux_/pack/item.hpp>
#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/utility.hpp>
#include <type_traits>
#else
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    // Creates a item typelist.
    template <typename Spec, typename Arg, typename Tail>
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    using make_items = ::boost::mp11::mp_if<
        ::std::is_same<Arg,::boost::parameter::void_>
      , ::boost::mp11::mp_identity< ::boost::parameter::void_>
      , ::boost::parameter::aux::make_item<Spec,Arg,Tail>
    >;
#else
    struct make_items
      : ::boost::mpl::eval_if<
            ::boost::is_same<Arg,::boost::parameter::void_>
          , ::boost::mpl::identity< ::boost::parameter::void_>
          , ::boost::parameter::aux::make_item<Spec,Arg,Tail>
        >
    {
    };
#endif
}}} // namespace boost::parameter::aux

#endif  // include guard


/* make_items.hpp
GGlIWVEbX01v3o6XuMwkhzsJxVnfG41zEDJCfwA970pmljR3lFg6QO4IlXPQspIpqc2ThbJECjd2YX4buZIElnuAvMhzR8AWazP+uIN2B1zVYY4nU0CI7svr72Kr/Ar0z/9Au9nVJaWMWhZ/v3nyT8ix1E7Av6GJZWLbWLM6YSYrlm2T88xDEEoZhCIv0NQFyUaZJB/m244VTHCsarTEIdPmwE+TWsUrol9ud5zK+Pfl5t72a2697Q0vt9kqWKlnuE7D7W2toLEwB+JIU8pr09m8v/S95nz9T8/SgK3Y/MyCQU4052OwTAzjm52h/sFivRA7CsxcVMQKae3uJJyE/x8LWO5MAkPqps9ECQWqje9lMSOfoiJ8obfytiTm8pev62vp4bUlMGwthr57+PZGpqP/h95IfpE9h3SZzklCWUQaC3Av3DfEaOHOTW5lR9hhZsbJOsnaqMo6bqm0ivFGjSclwDGfQWJLjVEOTozQCRc3Q/ZPtGooq0YUvMgHuhRf98wZSgaYhxzbNYWktEFiof5nlL2sdXoXGuWtrmWenfG+TVi3NQJmRrpYSQ==
*/