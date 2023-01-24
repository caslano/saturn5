/*!
@file
Defines `boost::hana::MonadPlus`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_MONAD_PLUS_HPP
#define BOOST_HANA_CONCEPT_MONAD_PLUS_HPP

#include <boost/hana/fwd/concept/monad_plus.hpp>

#include <boost/hana/concat.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/empty.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename M>
    struct MonadPlus
        : hana::integral_constant<bool,
            !is_default<concat_impl<typename tag_of<M>::type>>::value &&
            !is_default<empty_impl<typename tag_of<M>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_MONAD_PLUS_HPP

/* monad_plus.hpp
TJG0BlFGDa2/GdUIsfZpvG/i9y8RxM+MG0aq8cCr/BvNSoK/0gyvTBtGnxK3jJK7LP6NMPd9IPorLf3ouGjw3Sa+/qlJlHHTV7l417Je/8ZeNQx3ZTa5KwN+81LhcmeGf2OGfBqf34epS/zQWi5WXgxPHfi0F5+W2ODxXXzsxse7Uv2VGRt2+jdau/6kgQ75N4b8Sw3/EbZlCGzLUNiWWNiWoBsBD/g3DnyPOpuHwDUPhWuOhWuWT9vWX3BKvAswZvNvhFSVgDFbkImvf3Iudj/5LuyqZv/iPYIt3ME7ynfB1vi6hKVykyA3C/yV9IV6iGjkZSCWhi7jqeflf5rCaU9QtjT/D+DnUbzcCH8e+Lsf/jQaeRSBxd5vzRPqlgjaG8Bx9N3WPGPdEqOe1j9nlD9bpFILOflpBPa4QScpX6J6BCoy/e2teeG6JeFly1ESOkVZLsL190NQVfguf2mWvzJ/e+r5AahyD9bV8KZgs8BfMvzNeDOmrnmmuiWmmLrR89B6xb4b0pb+ZhwKPnHpsuXYJv4oneBDar2n+kv8rf4Kr9Bd8fC3zAYXdypcyjLgUp4DlzudcNl4E1y2rDslVibA33JIVlkMySpXQ7LKH0KyyrsgWeUmSFZZua66C2H2N1Shd8+j0Pz1U+QvU+WvUmOK0QDJXan9DR2Y7qP+BjQJ+5IANYAgNV5JAErhL6UgqAGi/JUgfylgU+Qu
*/