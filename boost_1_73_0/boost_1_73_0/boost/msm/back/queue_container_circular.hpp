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
/X9gt9Sg205WY7TaJ5vDFUGRHm+A5j+JT5dA9sHaa4ZBQbMibZ8eONIOxlhGpQbYZDTnQaNsVLuY315ozInzQvX546FqRNjV38S+xFNLMDJAM+VCjLOgz5ZYSkFmEGTmUKNchHUG1peVmUr59DQWCbB8MTVl6HMFOldgvhUfVQETjPm9WjGzcYm9YrBGxxES0HlQL3y5YlQMOiO8F7bWE0ez5dlUwZpfd4CSLEMaWM3DisSc1D/itnzAI1xNor4=
*/