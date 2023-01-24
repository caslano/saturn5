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
x37W8DVOBxR0ZAfdJmJshRfhVtlsY8/iqwIbDFE6TCEAHH83+iJpzUNCdLFLGAX7xWAt5KvcRdKP1M3uEsiJGCb4VQBHvinVAFKXusQCTBt6Phkq5mK9CdzjB7husQ2Z8uHM5daN89d+mKiUHstafIEZUm2ZrFbA/TgLZK8cu7YhUV1sM+dgloJ21dwAN8FhuZAza7l1fZOz2GtwMTe58drwPKfOSSjtWTQRpNmBx8IYyDkdYzOd7f1sUUtBu2sjm/cA7qfb0AWoYr/spcgVSr6NPUK3+wAnfI1Ruk6uhHnYUV2pz8OV+jxcyefhy+SKgEFKqz3qS4UOYAP/pMD7vgvkit26Z3wx6/gEuwTPEU/71mRjTUfwrNRejb1OJK/uF0FwYTYq3oI2ZiU/hb0LYhzbeYg775G6i8qTQdMMr6Rl5YzzLysnEXiRvX4Kj43IVfJT1YbI+iuGfdYN0XHE8W2lKH3nIJE9ezQc83lmPD+gFH2t2R0ALJyTjHXOkhJ9HnkwLD6MR92rFbasTSA0/RLvl1hUa49SgMIr6uPy/T2gLmUUkoh2Jo7AeUwkAFggbdjXY2bXwCN6GXUzE+IQSYtLqx1QbPCnum/gNJzopUTpSre2E+ElDu6c3oa6NpxEFNPi8A64DecnNzJPW2StyqWdLyTWIDdXr7YfrQ1vuRtR/D4qETkkNuCIpOme4ZIUtKlXcYRqA1uyQBo1
*/