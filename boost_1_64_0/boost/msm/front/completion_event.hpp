// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_FRONT_COMMON_COMPLETION_EVENT_H
#define BOOST_MSM_FRONT_COMMON_COMPLETION_EVENT_H

namespace boost { namespace msm { namespace front
{

    struct none
    {
        // make every event convertible to none.
        // to support standard-conform implementation of pseudo exits.
        none(){}
        template <class Event>
        none(Event const&){}

        typedef int completion_event;
    };

}}}

#endif //BOOST_MSM_FRONT_COMMON_COMPLETION_EVENT_H


/* completion_event.hpp
lJqWkfzJKsPYzzTZs7WadH2j1GWZwRpTDZSqbQfZI3ovZCvgCB1drmcLZpqOZJrtCVsvU9xXFcLJvtPtm179fhy2h2PTPsMo+Vl/SfJuDykL73tzCUeSDQKevkNSr2Kj5ngU5stOLZu1nOTKPN0Yq4YWQYfr0FTAlCdyaJTglqdN3aSMT6v9OlQDWcH84mHE/RF7M2bV2XzuzKtF9K7EppXcnDTx+lhZ93wDzD31IYyu8sxW3XYl6HQ6gtVaRyCoB7adaqvAE2J5RvGlYTBu6kMQzFkXprlS0M9sDaQVgtf7LpJZ4YZVxyB48cp/byqjgWfc8b/jYGYp1v8KdAaTiLwEtPwsl4d3Bx+kbRrnyYiEvQpWHCuSnCIFPYRg/W9og/c5rpVkDjDs4PGjqhx/+lt3SVbxUhT1pj/z4FKJBFsqB/8pjq+BsIFULpXPEhnKurJ9DQoWYb9Jd/cv39CP+j+QomkWQzNsPwr+F6mcPDoiWyvlXgyA+1m77cLVmTYkuT5J109vNb5j7P7Ylo6Ykn1VhvffmNrS7Im6e6QO4Jr3enEjrYmmyqh91w==
*/