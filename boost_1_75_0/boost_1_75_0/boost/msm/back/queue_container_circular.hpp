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
XBrHLw5ZbS7mHC8lRA+mNiX/WOPNQfxjxoEyx981MKh/7I+04P6xwwHXUfzzvMo/1m2UH/+YX57/8y3/PJ/etC6eJ/9YnsLzI7z8YzLueoQHwt3N4VfA8/fW1MnzmZznr9Q/hkLhgUtfTZG1uo+XbJbf9ZRZ/tZT7tNJjnKv9ZRZda+n1CFYeA4k/0Kl/sQrESpq++FQPl+CuRKhQj62mR4+to63vaGYEZJQcfsIlVtra6+eUPExI4IJlcAOt6/Lg6zNuDJloXIoM+jazCH8tG62MYQ5avORdcxRt73mf46aYPCYoyIy0lMvGhz5gWzunIBqv+eV2Nz3nKzT5lbNUZM5IwN6/qk56q82/+Z1r0swr9fYcEXnCozracoMteWrtLJTt3F97YXaqzdD9cMVl2JcSzPU99eFNEPdlCHzR1mGvMZTIa/x3F6t917j8d1Dcb1JvYeinUnZQ1HNuMl5YQjuT7hovGp7KOys6apZg0LaQ2Ezeu2hsEAfH6A+ZhmlPRR9jaHvIfm5mxr+I90U+Jd0A/gfxLa/7nbV4Dd3A/gHhgT/Xd284G8IfXyA+hjXTYK/UbfQ4X+nqxr+RV0V+PO6AvyDse3JXa8a/PW6AvwDQoL/dBcv+Dd3Afipj3u6SPBv7RI6/I90UcP/aBcF/kRo+0IWtt25y1WDf2NngP/+kOD/srMX/LM6A/zUx/mdJfhnd74E+k/1oP9U
*/