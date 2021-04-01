// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_MAKE_DEDUCED_ITEMS_HPP
#define BOOST_PARAMETER_AUX_PACK_MAKE_DEDUCED_ITEMS_HPP

#include <boost/parameter/aux_/void.hpp>
#include <boost/parameter/aux_/pack/deduced_item.hpp>
#include <boost/parameter/deduced.hpp>
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

    template <typename Spec, typename Tail>
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    using make_deduced_items = ::boost::mp11::mp_if<
        ::std::is_same<Spec,::boost::parameter::void_>
      , ::boost::mp11::mp_identity< ::boost::parameter::void_>
      , ::boost::mp11::mp_if<
            ::boost::parameter::aux::is_deduced<Spec>
          , ::boost::parameter::aux::make_deduced_item<Spec,Tail>
          , Tail
        >
    >;
#else
    struct make_deduced_items
      : ::boost::mpl::eval_if<
            ::boost::is_same<Spec,::boost::parameter::void_>
          , ::boost::mpl::identity< ::boost::parameter::void_>
          , ::boost::mpl::eval_if<
                ::boost::parameter::aux::is_deduced<Spec>
              , ::boost::parameter::aux::make_deduced_item<Spec,Tail>
              , Tail
            >
        >
    {
    };
#endif  // BOOST_PARAMETER_CAN_USE_MP11
}}} // namespace boost::parameter::aux

#endif  // include guard


/* make_deduced_items.hpp
MPPy9NhfIGDLANS1ohzWn1ZqF/x9Ytk5gM8s+DiiZTfTVnpmqqkNp2zGqzHbxK3xGi+fChvr83FHl+D5aFg643OJtO02Q6f5WBhdjmtAQ/gllFtSL7U8A043a9pTIW6fB1QzGthQaCkVjC5ufkNKKc4bZETr/DV7EY/pwJSL2Ontg8tyfiTQX57zaqlTxKZH2U9siuAY6DADiFiP7nPUFe/htLrqanEJqXVRpFUkRNHplDSaFUYFceQoom0j+HWqrlTOeql+PAP3TXk4JR8VnrhLgItAk4Adv7cxg5gElh/jANlaLk4XmKDqqBhaGtbg3lz/5ZFI46XHBQMBLH1+6YP1i5F6kQmokKO0HuhcsOFr5flm55pC5+vc18nPZtvJ26fyhOK+G5Xont49xfomOq5xHAaSo6j93BmUyAmRbeEd7sgoDH3EFCXe+Al6eTUDtbDAQ99myy63WK1MgnAegBOqfRrsb3JmwK7vRzZo6oQ7EoDBzXNhDi31Ng2GRHUF1N/f8UZYuyWyqXXPuMpLeSmPDwuGp4lGIaXvZg90eY1A/N1oMJDuSpD2XQ==
*/