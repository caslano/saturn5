/*!
@file
Defines `boost::hana::Struct`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_STRUCT_HPP
#define BOOST_HANA_CONCEPT_STRUCT_HPP

#include <boost/hana/fwd/concept/struct.hpp>

#include <boost/hana/accessors.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename S>
    struct Struct
        : hana::integral_constant<bool,
            !is_default<accessors_impl<typename tag_of<S>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_STRUCT_HPP

/* struct.hpp
MCuyGoWmHpc5O4+ZJ2uQ2n6xMj9YQTLLXieGyizBnMgmzpxaRvYPxjnE78y5UuYFxjUr4bLFTc4zGM/L1HwlZ0rNYM4UF5DL8l9lu7X7ZeQaJd/Qidr97lWKz6UsTbMGuxJjZDcvIF+ez3/cOkjNYB5ktj7vZY98tbiBz87/R+oJc+P+bXIwl3rCCpP1ffFF3n/DYOaU3+fWjx8oi9DilmyZ3VP2D8b1jOmd6CT7B8tPcacLjZC+J2k53AhYkqwsWbtfz7Hz5sicwXjOFn8NGyE1u4j9IFu/rJR8Q3vA+H42CTcuST1hxclKHpst3z3BWtxb290y8yGwEmRBZxp/ljmD8bwkvGyaIHMG4908uPeGneymFjf+QK0cspuwQhQX9e2gzGCK9pxTj/qclxmE5SM7s3HcNKknzJqs7KkrU6WeqJATn1n2xWXOPGAOZKcu9YxU5g9z5HmJXFFcZhBmYJtbsajUE2ZDtm5VATmvw2DeZG08lqdKPWGuZL2+juknNYPxTj+zct4jNYMVINvsuUG+J95pNmTTsXCpy2XjXQloeuS6MgOM87v65I3snweM57pCQstJygJhPmRbz+84LbnDPMlO7h19QnKH+ZLFNVkyUlkijOu5wvbsnx2DcX6fng3rpSwdxju23WvOAJkXGL8D2sWU/7N/ycZWf5PNnz/nD+MZtN99paMyPxjv7Zx/V/tIXWD2vO/rbb7IvMB4Hy5duOinLALGfa/yKYfsdCyM84vfX8BeWTzMiWyRfzHZ2yQY97Z/xKgjMkswnnn//APlXfxOu2bb9FxRUrMr8uvbbHtcN/yQzBKMz8+f7oV6KPOF5SEbvLZFDdk/GJ/Jk+o3kPdKAIzfR1Ujeq6UepK5ZF3z2IC1Uk9YYbKJXZrJs8TBSpI5tPst76oUmA2Zs/sROcvTYWXJHg93yiG7chXfBWQZq4fslRxg6jmz9v7tmCn1JQeYK9ntKWUbKRtzVeqSba8XfZSfO0XC8lFci6D/9JV5gTmTNV1ouVx2DGZJ1nf0n/4lwYqQPRrb54rMBCwnPcv8AJvDsmNaDk+8vOU70uGacVyQvWe07BiM4+Z8/1v2rwKMc99/Y4SV1BNWmuL69L/7XFkYzJziAv36FlYWDnOjuKGe+64qi4HZkA13yZ9L5gVWmGze5lvyXrkAs6D7tavZ+7bMEsyR4nIUv5hX6gmzIqvlbC5nsgn+XQEy93b7rKVmMI47EvJ5g+yYFrfUa4Gr1EyLq2aauFBZkBZndmi7nFmhMHeyFz1Nt8sMatYzcOlcqRksP1l68BDJPRFWkOzXX6Ey82kwngm7Pb9mSV1uGF9z4XOfE1IXmD3ZJNueZ5T5wQxkSZ8u/5K6aNf8dm+/7FgwzIus8LOe8q6KgFX4v7ll9aHMRpnPBJgV2ZS9P7fJjsG8yBrv2FJGZgLmRvbPV8vpygw3MUtko3ofHSF9h/mylW8hOQTBPMnWNe6ZLPsAU+dEVj8uvVku780YmAdZ20HRcyQ/mAtZxTZtXsnMw1Q9s2YjNuxWC8nvpuxKtg39FlRFWSbMi+IOH558SpnHLdyPrHe1/cnSP5glWb0v87opC4QZyEat6bFIegvzJCs6Ole69BZWgOx+huVWqQvMluz56pS7MvOw0mR3iuU5LnWBmVHuW442+ywzDytCcQ2rDJD8LFMwd2THol/tkLmGeZMF3qr4r7JWMK51lb+tNykLgTlSXMzaDuNkJmD8nPfvd46SusDyUdyKhe/ku2eBdr9nyRWSlMXC3Ciu9v3pfZQlwrh/PSu7esiuwIry/Ww3RskswbhHvTo6rZea3cY/yR72KP9B9gjmQ5ZepE8lZf4wK7I3A++ayyw=
*/