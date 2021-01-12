/*!
@file
Defines `boost::hana::Monoid`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_MONOID_HPP
#define BOOST_HANA_CONCEPT_MONOID_HPP

#include <boost/hana/fwd/concept/monoid.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/plus.hpp>
#include <boost/hana/zero.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename M>
    struct Monoid
        : hana::integral_constant<bool,
            !is_default<zero_impl<typename tag_of<M>::type>>::value &&
            !is_default<plus_impl<typename tag_of<M>::type,
                                  typename tag_of<M>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_MONOID_HPP

/* monoid.hpp
Ie0+d5cZGl0/Uq+81Y9uC0iuE1BCvE7CSsB3OYbCiN1diVh+pJMTu+zwi8xP/OUbDAMIhdeHqTmx5mNquTW0qyDqR474emEGVN84XerohTmaaLGU42ETTBcD8mE0ZADIsdyJGOhabnFie5jhGXR0+wIgOJC9542F0O/fsv3I97UvUxaUuSKmSBPf3mCNPCla8TmF1Z1RsTIb2eX3y7X3Fb91iExWRa6Q1JhOOEmsvu6IqpGF
*/