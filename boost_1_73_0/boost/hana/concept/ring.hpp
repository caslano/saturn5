/*!
@file
Defines `boost::hana::Ring`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_RING_HPP
#define BOOST_HANA_CONCEPT_RING_HPP

#include <boost/hana/fwd/concept/ring.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/mult.hpp>
#include <boost/hana/one.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename R>
    struct Ring
        : hana::integral_constant<bool,
            !is_default<one_impl<typename tag_of<R>::type>>::value &&
            !is_default<mult_impl<typename tag_of<R>::type,
                                  typename tag_of<R>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_RING_HPP

/* ring.hpp
ACYUsBuLEj3BTBBbRaWJ66Gbnpgq9429ci3rnlqEaboXVtqhIp/8ECFdiD1iQS4Chw+wPYpkaJLDMAeLnK5Firmjom4UKU5mumHYh1aigwWRqcLdbIN+Na1r7EwCn516795ZX9rJzNNZ0AToC+YVACuikoBGPIpge6eWJqi93kpzUDukiB1SBJ1GwHxx1Bc7o3r1AV/sFKfyHLkLjKYuJNWk7/9GmokyZO2X+cwd8dOkcgGt
*/