// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_UNMATCHED_ARGUMENT_HPP
#define BOOST_PARAMETER_AUX_PACK_UNMATCHED_ARGUMENT_HPP

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <type_traits>
#else
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct unmatched_argument
    {
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        static_assert(::std::is_same<T,void>::value, "T == void");
#else
        BOOST_MPL_ASSERT((
            typename ::boost::mpl::if_<
                ::boost::is_same<T,void>
              , ::boost::mpl::true_
              , ::boost::mpl::false_
            >::type
        ));
#endif
        typedef int type;
    }; 
}}} // namespace boost::parameter::aux

#endif  // include guard


/* unmatched_argument.hpp
D/J6aqO4QQ+m8RxEVUMtoFHMB5LzYSpSntEVqcDNqpkUXOX+yhU0VKahkKBYgYVKapwp4zKDK8uMT1JUy1Ne00WJUpGlu1xMO4JIIYJkjSzRDFKAMqlAgn1oypRJLauDbi1YNjW1L6Rk5WsKokRPoH94BWdXfZjEiisfvpxdf7r48xq+HF5eHp5f38DFCRye3yDW72fnx5hvjpYksPtKMoWWJfBpVXCWaoM/b/X0H1biqa6wgvLBiakpK+lmVUhOMk1TLgMt/Uf8g4FqMFg8mr/VpVBs0EE0JEMkDR2tNHHakCbWC0nNMDmoRkpGYRrXSY4ZfXK4LGde6j60HmEAvencqu6Dc3h5+tfXnW8jvWlEltu7uN1TzQRwn6AUPPSocVHUdVDQ2z+IUIK2RMVK3HEJJcXy08fw+Ii5ZdA/isu3dSujzz6As9UftWgH1ptbySp4gHAcpE4Ib97AMIM+iYdO1IcFNl5MDqLx3DPKSSGwlzVobl3JhHQ1oGfdpeVEsP8PKIMcjlb7FNeDEy32d83mQv9KVmOFG79GvYVhwSasw0LmodvEwlokJDNasuKe+NDfc7K+9RiHSsHcvZOP6+4l2GbVyiueuaEbvPNg2/26M/wl+LbtheviK/NFjAPQsWn39l1nFx/fe5aK
*/