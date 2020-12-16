/*!
@file
Defines `boost::hana::Searchable`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_SEARCHABLE_HPP
#define BOOST_HANA_CONCEPT_SEARCHABLE_HPP

#include <boost/hana/fwd/concept/searchable.hpp>

#include <boost/hana/any_of.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/find_if.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename S>
    struct Searchable
        : hana::integral_constant<bool,
            !is_default<any_of_impl<typename tag_of<S>::type>>::value &&
            !is_default<find_if_impl<typename tag_of<S>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_SEARCHABLE_HPP

/* searchable.hpp
swvj3t5pUF3O3XgYz6dD8wXyLk6BOZC1/2H1TOYTxvVceqyi9M9yj3Fdwqamhsl8wmqQdXe3OqwsFMa5V2o5TfYoEuZC5pTw0UxZHIzrUrFDzDbpEcyJrJ3JdXnOFBj3fVXLilLPTJgDz9LWmQuVGfYaf1+nDW8s73c/GMdV3JGaqSwQxrO7v3XHmTKDMM69h4u3v8wgjN/hMwu3GyNnD4zPgocvr12Q3LXn9HZ9/Gc+YR5kPufa3FFmss/4e9C1UGtHyV2ziaVGBcvswvgdHj9jho3UBcbzcmDiGWepC4zfHY3H95WZCIFRXbDwhXvJXMMK8Hwuu7NCWQyMZ3BjgxLfpWYwrlnMbN8EqZkWN/Lx/eFSM5gVWXTxtJuyDzBvPq+7R55Q5pRgvO+rpry/KjudoH1HNthvqawjjN8rr0+t/fPuh/HeeoSHtpZ5gXEODT4OnST7DmuebUHZNnTymyTZ2/3GezTlw91I6S2MZ6lys7rlJAcYz3yRsmeqKQuG8bO82PrznbJwLa5aOa8jkgPMluy4WynZo1jtmlds3gyR/sF4Xlxu+JhK/2C874fLfe8sM3/gzzd7Vg3e/zKXd4DNAXn/Zdvm4rMHyD5oFp64bZ/0XbvmQ797bZR5w8wp7sKwDbdkV2CWFOdYONNVmb92v4OvHGXmq8Fykm0ve8FEeqRdc/CI1jdk/2AWFLc1Lk8JZUHac9pXs/kovdXiHM/WlHM3RLvf0N8NF8jsanFtjjWRsydMu1+NQEsLmRfNvKbGF1UWodnsAiPlnRqp3e9ygwIJMmeazfi85IGyGFgusiY9H1nLDGo2ceRo+daI055lfweHdbJ/2kwYSk+uIbOr1ay5Z6NmypK0+/19bGm0smQthw0np8i3TYo2L/2K2e5XlqpZ5uPeL2VXtGs6t6ot/UuHWdFzfr4cYacsU7PhDsdlx8wOGl9zUoNVcoYYYJz7/ub9CypzguXiHu06Kvl5aPa1pl1lZb6wnNyHFy/aKvPT7lf96Ic9yvxh3L995xP+/KwVxjW7cTRBvgfrarZg9hqJC9Su+bHILjmvgzRr8yjusrJgrWZdXs7roCxEs+CVL/srC9XsldX+N8rCNKtyrt08ZeHas8R+sJCzNUKLc6/m5KAsEpab6jkh2WmkshjNrlYt/q/sCsyGLHhf/RHKEjT7sCujoeyDZicT71yXmdds4Mk+z2V2Nfvrbc9cMruavX15S37ObHkIP48jq5ScKf3z0GzZ9YahMkuabdrQ47P0XTOTNTfPS/80KxH5r8xShGYTZobKt9QCGM/gpjoNf0kfYNzbKT2jjyuL1azRR9cr0iPN/iqyLJ+yeM3q/cfip/RPe5bFb2b5KTt0SJvPbQ3zKjupxRVqcKuX9B3GOz3o2qdwZRe0ZzH58ipAZgLG+77bq6+vsjTNPq/u0U3mBWZFdrDNrViZFy3OvUiKfCebHDaepeRvyy8pM8DykN35vWW7zBKMrznp6Lncyny1azbpPidZ5ky7Zr1eR3YoC9SuWdXErZbMoHbNjNR2S5SFaNf8dTtUvqHDYFyXwTtzbZb51OzO3t3yrorS7FUJBzl3YzVrteD4b5kzzXa9nGOrLFEz57fVyytL1qz0kOUG6btm0RcbtVf2TqtZrQ8pltJ3zV5+7ltR+n7E2FL7ncsvZ4hmPa67dZSZgPEZWX56+aMyE5rZ3K6+S1lJGO/RV59T8h1ZQbOWniNeKKumWY9Dt87Ke0yz1Jw5Jsm8wKy5Dw1PW8u8aObcdJi8i8M0K33tuoPMi2bR/U07y7zAuEdtbe56yrxodm1jg1wyLzAXPucrJR+TmYAZyN7MrPjn5zIwD7JiB0KdpLfoSD4=
*/