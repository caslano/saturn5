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
8Uu3VBwrCCHcKfT725Rb9FXeIzKucF9w/TvpPU2jujBZmx3Cw95oj3XPJM4GcfYx4HE2kA+emZWI3zAbqFuMdX/YHvIh2RC9/8To/VN9XrBC9CbgkMFKEXZ3g5UVM/7MuO/cEdW9uvaVb/Tarqj+LSnR9//7bv4/2kGDqN4Kfu6RtExaOP8skNMi6buSM1dynP+brLyfSOT9hKthlRdF7h4Hqbwk8qEMv6x8HJEYuwJb4jqF
*/