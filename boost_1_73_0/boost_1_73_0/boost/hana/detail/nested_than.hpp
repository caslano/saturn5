/*!
@file
Defines `boost::hana::detail::nested_than`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_NESTED_THAN_HPP
#define BOOST_HANA_DETAIL_NESTED_THAN_HPP

#include <boost/hana/detail/nested_than_fwd.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/functional/flip.hpp>
#include <boost/hana/functional/partial.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @cond
    template <typename Algorithm>
    template <typename X>
    constexpr decltype(auto) nested_than_t<Algorithm>::operator()(X&& x) const
    { return hana::partial(hana::flip(Algorithm{}), static_cast<X&&>(x)); }
    //! @endcond
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_NESTED_THAN_HPP

/* nested_than.hpp
jwc+D5wNRFsl5gE38zvgFiD7nBezZJmCPC7LFHTJZRC/CtvLIH6laYmQDdcRsuEecrT1jvaho33iaPuGLe2AsKWd4WhnO9r9jvago/3B0d52tB2O9h9H6+cV9uS1kaX2TRZ95qBYnzkoZpAKHQSDzuIrSjG68dD0ky9VJaVuCqRHlr2R3h/pe7u9r7p8Ba6DtasCrmLtmqnkGpGIvrFuTNg7JLhLpV63dKmS63So0s/0DwnMoyP1tQvrFzTs4pY=
*/