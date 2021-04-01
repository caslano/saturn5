// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file detail/manage_bimap_key.hpp
/// \brief Utility class to manage the set types of a bimap.

#ifndef BOOST_BIMAP_DETAIL_MANAGE_BIMAP_KEY_HPP
#define BOOST_BIMAP_DETAIL_MANAGE_BIMAP_KEY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

#include <boost/bimap/detail/is_set_type_of.hpp>

#include <boost/bimap/set_of.hpp>

namespace boost {
namespace bimaps {
namespace detail {

/** \struct boost::bimaps::detail::manage_bimap_key
\brief Metafunction to manage the set types of a bimap.

\code
template< class Type >
struct manage_bimap_key
{
    typedef -SetType- type;
}
\endcode

See also bimap, bimap_core.
                                                                                **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class Type >
struct manage_bimap_key
{

typedef BOOST_DEDUCED_TYPENAME

    mpl::eval_if< BOOST_DEDUCED_TYPENAME is_set_type_of< Type >::type,
    // {
            mpl::identity< Type >,
    // }
    // else
    // {
            // Default it to a set
            mpl::identity< set_of< Type > >
    // }

    >::type set_type;

    // Returns set_type and evaluate the concept_checked_type

    typedef BOOST_DEDUCED_TYPENAME mpl::if_c< true, set_type, 
        BOOST_DEDUCED_TYPENAME set_type::lazy_concept_checked::type
    >::type type;
};



#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

} // namespace detail
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_DETAIL_MANAGE_BIMAP_KEY_HPP



/* manage_bimap_key.hpp
/HiowrRrictFdpwFcY1JMiE5GYpmA4xhijoYUh7yHRKh38hoC9+ruCllLVlRdP64wXgesGISN5jwcHmBwTW+AEdyq3/QUoHgrCMAlaQC2wjiNVBaVnll0WUp8jT2w4hBR4y8/XK0Kv6TxP7e+z1q4IjbY4g+JAIjoKog7NSyDCTmZr2BM5HEZ2pHMHfPdDAjbLiaFOY3fH6I+FlJiosaX3toK7g3S3WusQazBzYwinpR0TmIesG0C7+BvhLMAmII+5kQMyNxTxunlVcgOzYvu2oSkOmfK3d1snf1BBp18kMJ+TA6k8adIoGVYq/fiMiBW/Rsufun0hnSlMTQExu5qxGP2EqrTqjAaRzvafk7jiIVdmXS607QZLG4rBBVk+I17zC2AkaftfwrXDIlKV0EDqygyOWaRO2pfH9WjwSly8xy9pBfVrLtVSH71FDNJaF8KngxNSTsS39R1Tz4Re/T5lbvFOlHezYh2GOj6XDgwH+qHR/oFPeNlwloap5Vm5NNSr1tpnDwEFHzUFDJ4uSNTLx4qxVeEXNK+XRGkQ4/0D/Q/w3dYS0cEEnMow==
*/