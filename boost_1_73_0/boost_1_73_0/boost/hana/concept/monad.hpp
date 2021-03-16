/*!
@file
Defines `boost::hana::Monad`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_MONAD_HPP
#define BOOST_HANA_CONCEPT_MONAD_HPP

#include <boost/hana/fwd/concept/monad.hpp>

#include <boost/hana/chain.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/flatten.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename M>
    struct Monad
        : hana::integral_constant<bool,
            !is_default<flatten_impl<typename tag_of<M>::type>>::value ||
            !is_default<chain_impl<typename tag_of<M>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_MONAD_HPP

/* monad.hpp
VswbWeOanb8D1whNe1JZZn9FWWY/B/8/59OdUPBqTIDtZyEUzedfA05Msr28GqH5vVGl/TtuMJjhaD0AOQ0zg8FmNCFM3TC/YYHmc3K0jGLYRZGSwK8MLQ31LXP1ZxWgNIzUn3ERe5CRIrEDNbm+T6JBxtxa+OszNIXxuM7vFU8WWTaKEHXt84Z2b0iWC7gTjMVdF5L91w8Y+zV3gLHT5A4wlu0hYC3wYeAc4PeAtDd8PyQb4teHRIQeCckA/Qc=
*/