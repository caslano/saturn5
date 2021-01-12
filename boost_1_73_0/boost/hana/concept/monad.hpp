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
f27R6CEaSzxo9HjRmB4B8A6LRi/RmOlBo9eLRqUAP2bR6CMaYzxo9HnQ2J4TsC4aG9ZFLwwK7KU6Sh5FEhQE05JmaxKxmOUXLE7UGB70szkOz9XVh+Nkm4addkGpTVGCcvJ3Dnr9w265W9f9D7K3F4EAvao0bjbTJUPWUGreU6cisWF+2Gd3tUafPbRvMCGx8tlgPYqffZnP51HV+QgVTjvkDHK92HUQB8MfQpWUpa+YgBi1
*/