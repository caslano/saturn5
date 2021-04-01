/*!
@file
Defines `boost::hana::Metafunction`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_METAFUNCTION_HPP
#define BOOST_HANA_CONCEPT_METAFUNCTION_HPP

#include <boost/hana/fwd/concept/metafunction.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    namespace detail {
        template <typename F, typename Tag = typename tag_of<F>::type>
        struct metafunction_dispatch
            : hana::integral_constant<bool,
                Metafunction<Tag>::value
            >
        { };

        template <typename F>
        struct metafunction_dispatch<F, F>
            : hana::integral_constant<bool, false>
        { };
    }

    template <typename F>
    struct Metafunction
        : detail::metafunction_dispatch<F>
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_METAFUNCTION_HPP

/* metafunction.hpp
eFrFLPgSXz42oucmBklUiiOaL2+nwRQmPCjYS3V0rBBjb1KLHu8hMNkNHKORCesjj29GvKw7Epvg5kt5lUGWWf5BIYgnU8+qU5evM4w6DHGHo10fKaJijX0KeW1DI3Al0O9JIHE8F59VOrchdNoF0cWcJkaqj7h77ENlqfDXEo2YvTjrd5s3RhNnwBIvXs9f7RhR2BCqednk0/H3iVZNsCvPuvqln4rzf6bn4C9D+giDLr+f4A3uMr2yfxNK0pWS1YVOp5MgtneYxoO48GgVB2qRH/66fr8u5IqvmZz9JiNyT2MbiNj1ZeyvpyuaPIeEdpMsYoQDpwDenBI/rbhX+F/AqV5ZcuHtlaFEurm49h4mHl7CuZZ6DlAxavnpzvY4frsguwed+VHhxwhPM27UqHnKwr3AeHWKdjcTzrFSe0wrQw93ti40gS7pWwhsaMrPqmJI9FGvAzqeteRo8NbLPsLKnaIFxvQ6+NO2ZdUcx+bXI5eRRCQb28PP7w920UKKdUbgebcGfYrB0BWUUjpp+gV0u23p6JcaHubEGyYvgkPRZITmrM1ewXmHXw==
*/