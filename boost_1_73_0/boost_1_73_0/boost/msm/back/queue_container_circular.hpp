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
Wx+jvN0eJ9HP6BcqsT1AxQ0HvrWpwQYG90BgxzW8ILZwpXfSXBH22mMtRaekkaWsQ7JcxQlYo97lH/XI3CObaB3DU5ZsZuyzr9Aj2SItoEhm7MtcFvA9KiKP/HxeF26SZ1G272rJq4tJ3znIqc7oaJWe3/oHUEsDBAoAAAAIAC1nSlLrY0HnswEAAPYCAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0OTQ0VVQFAAG2SCRgbVJNb6MwFLxb4j88tap6okhZemjWQUXZVImUFBbcVffo4peNtWAj22mbf18D+dhse8H287yZeYOpQ+sqbjEhVKq19stf3L1pI2xCyhXLSZmWy/4D6RObw+yZzYrHdCiFi4IUD9M4Ho369e42JjQ6EdBo4CSX5BJKNK9oQisFEmqwrXceYPti1YiEnNMXs3z5e5AcfbuFdOs2qJysuEPhef/po9GerFeZ1tLj9ipVfzjKJMQ2rj12JwSo4g0OgwK+OzSK18BPWlIreJNuA1JJJ/2dQdtqZdG3RkMvtU5IlZCGyxpetNgFncBQA1rppuHKu7zupMdRtPXa37uxJodR76/mWckW+fiqs5FnBYvu4vgawrCjDE3VOi9bybab5R7fedPWeOOJD4i18XuLSqD579py
*/