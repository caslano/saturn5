/*!
@file
Defines `boost::hana::Orderable`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_ORDERABLE_HPP
#define BOOST_HANA_CONCEPT_ORDERABLE_HPP

#include <boost/hana/fwd/concept/orderable.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/less.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename Ord>
    struct Orderable
        : hana::integral_constant<bool,
            !is_default<less_impl<typename tag_of<Ord>::type,
                                  typename tag_of<Ord>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_ORDERABLE_HPP

/* orderable.hpp
YmV+0LS1IKyekc8MSq01rb7Lg6lQI5LtxiGoizxUj9dpReEdljKGAkuE2ClaLMaN+tzs2gi10owH8+QFTy0y2Ay+Kzz4S7uSQVMFaWiCOhffqAfQBzWyKK1KPQQJBXW1jf2CmmjN3Gz1jeGFAy23sN/y11i4stLKNtDerW7M+AGo4WzRaNSUHx8dXfkda9RWft8Yra/83k3esWgO9BoYusqW8CVgWkEczsahA4N/NC4Mo0hn1FeIedVAnTajJUBuiJMDcVtt80dLyTXv+bq3OoX5hYIEIq9RbjDWvCd1BtvJ9VhfMwwnbeYWtNFuNcPJCnegowNurTnBBUs0Z1RVmg2+fFWEPloYDRs4/W2X218iuNgN/0AvAQwAGizl0zI+PnwVRmP/Bw+Wc4AivimWphyz4Gb9r0GLylYFRyAiExShKddsWB2xStAZQ5bwlawNk8mXGJryzIYyPfIZmj4W5Cw02zCg38uvkV8MGZq2ZaCZNhT2TePLz9IoJzuBfdFDX0pwdSKFTFtuhqfykDRs4GvhL3+EB5AvwHRhyWQPNLqKuatPeC6+U0Psf0ZTxG/5TNg3rvaoVOIN80+sdbTmKmO2Hw0udHvTvQKzvkZYQDSMcWvptunpxuDOa/7OT++CZvUf9j43++RVxAoUfD8UvFptXNXo+elbgo3tAFb7LDUBI7siyXiw/U62TAeZwND8HPwXUEEEC9D6erTC
*/