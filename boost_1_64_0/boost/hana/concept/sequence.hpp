/*!
@file
Defines `boost::hana::Sequence`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_SEQUENCE_HPP
#define BOOST_HANA_CONCEPT_SEQUENCE_HPP

#include <boost/hana/fwd/concept/sequence.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/integral_constant.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    namespace detail {
        template <typename S, typename Tag = typename hana::tag_of<S>::type>
        struct sequence_dispatch
            : hana::integral_constant<bool,
                hana::Sequence<Tag>::value
            >
        { };

        template <typename S>
        struct sequence_dispatch<S, S>
            : hana::integral_constant<bool, false>
        { };
    }

    //! @cond
    template <typename S, bool condition>
    struct Sequence<S, when<condition>>
        : detail::sequence_dispatch<S>
    { };
    //! @endcond
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_SEQUENCE_HPP

/* sequence.hpp
/+B3a6VVb5PuCWckh3yIHCbf7Di6d82J41X8leZ/37uU81nNlOLTDjDD1OergBC8cpZRBMRCejGPE4KXyrRTxSUX9McVn37q6V1wY1gOePLWNZbWS5EXX/Yy2KWarxR80lw2yr96ScPoo6Pswoc26pNscgMil4dg/EoiAn2VdmsFbB3xDvWT0+Yiw3S5j/ot7PC6J2392VGLGX5Y80aQqmp97u/DNgPrYWEXZC2rjBgAdo4q97hb8yBKjgilc7xQehc4W7jKZEnrvM4r7TQn/SuD6zcGjuN0HlkauVMMM12wpVfgHb+UV1JBPu0qvq7BqiUNiGGNrUqRTA7PLebPfKZjbcCktbJGXMiBKl1xHtLq5PTiq5rlXymH1hRDkXHJT2ZXdR2mj0z7KLsFi5F7oxIQY61M9/RslW2HYMjdPcid8mWFH7gZt80z/DxIwsh9b8l0esE8tLLzUPCId0xlrOvsYaTHqty5DqOt4QjRdo/cOTIBRww0y2KtmqwwayCKIsFoLDhg1W+1B9c35gad6wg5iuq0YLQwf18h10nosiviewo3Jg+0MeQNpQ==
*/