// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_BACK_QUEUE_CONTAINER_DEQUE_H
#define BOOST_MSM_BACK_QUEUE_CONTAINER_DEQUE_H

#include <deque>

namespace boost { namespace msm { namespace back
{
    struct queue_container_deque
    {
        typedef int queue_container_policy;

        template <class Element>
        struct In 
        {
            typedef typename std::deque<Element> type;
        };
    };

} } }//boost::msm::back


#endif //BOOST_MSM_BACK_QUEUE_CONTAINER_DEQUE_H

/* queue_container_deque.hpp
W4fSQMgg9K6OZvx2n0yf2S80cr0DwR0HvvYpgA8AupcBG27hBVHBhd1od0Hoa4/1FK3RTle6TshsvszAWw7OfyGI58e6+jOZBGSVLpbwUGSrMf3sMwlIMc0ZsGxMv5zTA36kLA3Iz6cF69I9SdNtW2suztK/6SCHOo2OhqPTU/8AUEsDBAoAAAAIAC1nSlLrdEXmtAEAAP8CAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0OTQ1VVQFAAG2SCRgbVLLbtswELwT0D8sEgQ5KQJc+xCXESK4DmzArlSJKdojI65hohIpkHQS/31JyY866YWP5XBmdkjq0LqaW0wJlWqj/fQH92/aCJuSas0KUmXVqh8ge2YLmP9i8/J7NpTiZUnKp9l4PBr18/1kTGhyJqDJwEmuyTVUaF7RxFYKJNRg1+w9wPbFuhUpuaQv58Xq9yA5+jKBbOe2qJysuUPhef+5R5MDWa8ya6THHVTqfnOSSYltXXe6nRKgirc4NAr47tAo3gA/a0mt4E26LUglnfRnBm2nlcW+qncOaoMigHljPV0y8FHrhFQpabls4EWLfRREhxrQWrctV975bbAzTZKvoc2HY+uPN4u8YstiehNsFXnJkvvx5BbiONDFpu6ct1HLLvT2
*/