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
pB+McHudcX2RomizQqmKNjssipb7k2cmFa28r6PFZ4lK+2cUbZ1KKtqESlG05Bi/ol2tvIp2KChjXBiminmpm+/tN1NTrUaOqRSNzDa2Gtlq6GYZ1Khhymuo0Te5MfLkgJiTNPvHeqBSZo3/x9AuGCRKuXaQKOULzYRxlpkwzgaezTwB5wLnABcC5wJZa42DZJtSE/B24EXAZ4HzgL8Gzgf+HrgA+GfgQuDfgYuAtN40A9lmFwM5sW0F7g+MA48=
*/