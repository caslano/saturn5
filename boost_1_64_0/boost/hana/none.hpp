/*!
@file
Defines `boost::hana::none`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_NONE_HPP
#define BOOST_HANA_NONE_HPP

#include <boost/hana/fwd/none.hpp>

#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/id.hpp>
#include <boost/hana/none_of.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto none_t::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using None = BOOST_HANA_DISPATCH_IF(none_impl<S>,
            hana::Searchable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S>::value,
        "hana::none(xs) requires 'xs' to be a Searchable");
    #endif

        return None::apply(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename S, bool condition>
    struct none_impl<S, when<condition>> : default_ {
        template <typename Xs>
        static constexpr auto apply(Xs&& xs)
        { return hana::none_of(static_cast<Xs&&>(xs), hana::id); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_NONE_HPP

/* none.hpp
uqa1n8DgyapYGBPsuWyegSf7Mh+JguM3n9mtDAJEkXff9zozWqARc1/U93fbWnrYFyENJlkYmuW7qXd1ytNpMNp/kbwnzWlK5lCkc84MjI1/1tlDa3vs3fOpLy3935HGCZ9IGp7ZyFvymrLrwZOVAOd1dmoJIKi5LlrYEWHBngiiAzB6Bv7tfyx5q4X0Ih+q1I4tsGX2y1g8rsX5hZ+Gt3p2jYZYEDg3GLOpg9ZeFKPUHdXHgZNWLeeZcbp56/lPGqAck7qkJyRVQH9uTTUh5/R81nWTPi7/YOoOVkWjw+y3nikcpODgeYJc2rhaF9cflVjy8BfyTF6Bt3Wt48x/n1h/0NF+1lj8obo9Pcd/KdWJm02BYz+XnB66noPmz/t0iQTRwB7wTzLoFg1GO3cbOMIRi8Ab3QqBcs45IxcWyrcepqQhP38KQ2lXTkEF0OKvGXTesaaGWqygLMKcwqjF9gZjlNpcO3xVBT6ag6ZgsIolT3o+q8xLPwUeR4Hn5v2HsUVibrSlgSx4dXQXlDP59W0rXFpKEsVhW9hZ0MOeimfPMmZxZqIZT8SlPg==
*/