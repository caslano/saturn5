// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_BACK_QUEUE_CONTAINER_CIRCULAR_H
#define BOOST_MSM_BACK_QUEUE_CONTAINER_CIRCULAR_H

#include <boost/circular_buffer.hpp>

namespace boost { namespace msm { namespace back
{
    struct queue_container_circular
    {
        typedef int queue_container_policy;

        template <class Element>
        struct In 
        {
            typedef typename boost::circular_buffer<Element> type;
        };
    };

} } }//boost::msm::back


#endif //BOOST_MSM_BACK_QUEUE_CONTAINER_CIRCULAR_H

/* queue_container_circular.hpp
RsGaj9+btonCBZSwmbstV8bRSDA1zANh4ECF99X0dn4zJpGmDZ+n/KtU4VZSK0Mc4r1GQ/vJmSMVzF02mxNTEb0BvqWUshU2/2yFINAYzG8J2Yae2MAbMK+U8Y73hKS+yX7150LqF7zpCcRH15QfefCJjAur98AdrVKYe0K09BnVLadn6HhnvMlUnnNcuJZM8tA19p9iu4qARzHoZ58s2YX5ZwPtNsVmmqLy2gI6jS5plUCVJ5prbV03bETR69QBz0cF9Ea8KIWhSPVIv59ntgzzVibscc/+zORAzex9xP8kZM19iYCyNUQMjcSbAC10Ob1+o2PsQTQsY+Nazc8A6gZh8ougzLgh7kYoIYKTQcON8NL1aYgd4/adkbnb7vFZIZiAZniEP02IlW0lqlkVRNoNzrZih/S6Lv5TcmPO1AbOSwtxYZhoinMyINfVqnHgM03gjuJt7mOPcXC+BJ0bMsWWpuuxH5hWKJV6j//BAsXz3mcRyoWsJV/cGgjB1k+Rhcb9qBHz68dZwWY+hDgTaU6YhOQA5nKKcbMz5om3XguVvGKg/otm6sWOsA==
*/