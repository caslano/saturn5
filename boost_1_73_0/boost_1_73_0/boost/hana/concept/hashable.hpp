/*!
@file
Defines `boost::hana::Hashable`.

@copyright Louis Dionne 2016
@copyright Jason Rice 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_HASHABLE_HPP
#define BOOST_HANA_CONCEPT_HASHABLE_HPP

#include <boost/hana/fwd/concept/hashable.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/hash.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename T>
    struct Hashable
        : hana::integral_constant<bool,
            !is_default<hash_impl<typename tag_of<T>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_HASHABLE_HPP

/* hashable.hpp
0gxxXqdhlvFqE7AWNb2s9AY/9gvklpRQJgE4IfQ/K+DUo9MQTDEFumoBwImzADYJdghSb4VW+rBMszHxo/ROOyrk+KD0TneBDFwLr6IMxkqrK83tqSmqR0QMxFILZHgzHZ+PHoAZbO1a8KEpb30shgxo2DKFF2fCVkbvQSqk5KlQn9ZnS1YPupS2/dhavCUFeqgm9Wb8Eh1+ITs6R7D2P70sEmPdtKecR8kqdhdKwVbJRWa0itDRTmfLeFlwTCB4zxTAl1VD8A+81yyMfTpUvkKwiaEZIA4hxnUSRQ4GOgCy6gB6Dj0TLCokVsiileGJcgQxLpMOT+KUOQ8QB6uatOKvX2JVWoRVlqGxirqMFwC4ZU9wahyPTjwaZIN/lRKGVoYuX+g/A7yWdtZu36Ky/++2nJrtlJM05DEtJbSvOashDBOId24R2t4+M3xEDb+qbnccIrlxEs8jisOXrUCo9czOMrCmPxtCybPcTUimuAWGvgDjPBhkPB4muh0N3XIs7s7zMMJLEZuVZ4mwyxNOeTChsBfKzKPrKPtMH5vhP8fjV93DITaQXRQQNFutTfOUJ8aoHw1R5NM1oHb8TqqSQQ9Be+UVmX5d/vQ6WNQbcAj1vlL7/tGsz9P7CI1W4iXDMDBEgK1y3JqFbtCu
*/