/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/overflow_policy.hpp
 * \author Andrey Semashev
 * \date   23.02.2016
 *
 * The header contains the \c overflow_policy keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_OVERFLOW_POLICY_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_OVERFLOW_POLICY_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass interprocess queue overflow policy to the queue constructor
BOOST_PARAMETER_KEYWORD(tag, overflow_policy)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_OVERFLOW_POLICY_HPP_INCLUDED_

/* overflow_policy.hpp
babuH8R1hjxf8XSm4nqqNGs7x4+XVPpMweHq/hB1/yt133Osui9zRKW6n9I5rkS/j6R0jqv3Uv/+cbVSFsrkdgJzgPwmlmldN0Wr67ayyHXdVha5rtvKIte1nfdYpWu1jlTr7QV1P1N+47r0kjPg79PJOuKW/wPXt/6m1rcm3de7YPCBc+Y+tG72Xj3ePuTF6Ne3/h/XsWZZYpsGe0KtkMu2r8HuDDI/X2EYvkldfNh8nfniNJ/YZ818zFiaDzuqM1+iPb8w5aba+IrDtGMHG19bmPp1WLZyw9RvpOaDwpRbbuNbGabcb2187WH4PrbLLwwfqPk6Sp35ltj5wuR3v40vN0x+x2o+Qhj53WLjSwnDN83G5wlT7vn2/MLo4zC73sKUe7bm414YvoF2uYThq7XLJUx/fsLOF6Yde9r4FoXR2yM2vvIw+ZW6bHIOw+d22fILU+7B9vkljFxOt8s5TH7v2/iKw+TXaG+vM59eDz/d/50KPEn4kqBS4ZtJO5LAOWAf8DSwHzgXzAXPAgvAc8BdwHPBPcHzwH3A88HjwAtA3e8qnOvlteshTP0Psus/DN8w+/gJI9/dhG+u/30dPEH4NrF9uxhE/Xw4GEwENweTwWxwC3BLMA8cAe4GbiXy2BqcCG4vctkWPBLMA6skvhocAh4l13KOqrxL0qfkWp+jKuvHfXgxuBF4CZgCLgDTwUvBzcBrwMHg5eAw8CowF7waHCv388ErwPHglWCR8E0SvoOE7yuw0EdSr8FSrx4QbVfheKnXiVKvk6Q+LVKfUySfm/zvB+AMyacvtFDyWS75PCP5PAtuDD4H9gNXgGng8+Dm4AvgcPBFcAy4CiwA3wTHgSvBncGXwd3BV8CJ4GvSzlfByXJdLemPkvRfgVP0M67sXQElqvEkz/NS39FS3zHgJuB2YCqYJ3rYHtwazAe3BQvAhT3I56gkayZ0E7QaSpzB+lhoOrQQWg59D2XVJln7QidAN0EroHVQZl2SVQTVQgugNqgdSqxPsnKgEqgFWgy9Cv0MZTWQBvJC10EroZ+hXA/80ExoMbQaso5OskZAUyDW8uv1+6zd/0+u24/2vFf/2v2SkfH/+PX7nN8a0Rp+03mt4zPj9Vp+9nNg/TX3G3qYzm0Nu66ffSD02v5i8lzL3+wLEbjG/09e379sZPyfusaf81f/lHX+QeerGs9WZV+NDV7zv76zVdvB4LX/nKMa8fr/Qmgu88gSaBVkNTK3QPtCHmg+tBRaA/VvYh6ESqG50GLoVSjRy34AUDnUCt0DtUPJzcRDpdA8aCm0GvoZyjqGMiAPtBBaDq2Fko9ljoRKIC80D7oJehJafWxsf4FYiIVYiIVYiIVYiIVY+P+FP339f4Vb/aMW/3fD+f+zsi3tdzvTJd+OIRe0B3R9ATaAg8T/adcJZRNKppS5qVl9s0fZMK8t8PG6vTNtNsx7Ff+uBhus5MV/Gdg3e3B9F3awO1PsFNbOOdHus+cre4CUbfcfXhLXyTxH2jEbuhnelIOD2tHgmcUtWzsamr1id+8PDlf8M6w+5G5qC/lpW+6NKn1NvWXzWxqg7p9kJfPvUMhkZ7bnQdkE1nfbZFmk7u/H9WF9fM2q2gx/AIPfS7LZr1FkJO0SO/CNKo66BstNzkQsE7kdKfpvC5LbVBa+cMtR/08p/kPNNnhpb7a1X597aNB0yjyOPti7V+/hvUf2HtkzLrl3b/5J2tgK10eo9/59RCbKD2hhyvrt4079Rp8lIAk2kkQ9oVvgLTwksP1qX318k1kCUEYuwXIwtVvycK3Xh8apjmP8a32ljntBLhmrt8JbHFTH+upjdb0syaev6KdK8W7Hnrou7WdwGbU=
*/