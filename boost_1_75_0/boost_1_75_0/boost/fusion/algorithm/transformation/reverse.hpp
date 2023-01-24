/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REVERSE_07212005_1230)
#define FUSION_REVERSE_07212005_1230

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/reverse_view/reverse_view.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct reverse
        {
            typedef reverse_view<Sequence> type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        enable_if<
            traits::is_sequence<Sequence>
          , reverse_view<Sequence const>
        >::type
    reverse(Sequence const& view)
    {
        return reverse_view<Sequence const>(view);
    }
}}

#endif


/* reverse.hpp
NbsV1IR2G8Z8bwN1LG5BYMs5XmHzPdL15ZZ92PjxpT8K92xcO54rPtGhXK4DysOZXJDvVg8QEPH8RjWOKZEtyFM7xVucqdfSnPcaLSlVz/TUvNyVk5dgLRtJmfOb8f0U5twvB2fccu7+zd8gL5mNZXq5il6BAXwlTFAVfiBNXUKGe+f8ZbgpOQxcPEA6JN95+Br7IpWUmL4ylw75dKBs15VYIaSSEv9UYuUNScrmgTuK8xCOkOeozKH23AbtcAWDm4rrjRTcVBwK4bJNi2NRS1sMilhHJTSyawZqiqEmyq6zJbWskjrJBMsxBCwB+1QmscP2YkjMHRaAkKTynXAClVrUxCoVbaph3eT740B8kOBRGBIUTiFBNku0oXj5AjLb7MLYoNqkcWDUYHi0OiZoHNviMMWljOa/wyCUhGElwW/Q46i/tlqg1dk/1uqYwla87+V5T0BZ6P5xINgUw2+sZVTqgrsV9yzJqsegaQ0GIU2AeWQDdQ5+iTxHMSFcfU1Ptsqwr3z7jd3URzsJd+EkBICawxzaLT93PxS+sAU7+xrr7sJkodXy4HyXC82QfZWZddTij4fYqCYNDY6gqxnnbf1b79MPYqLFG5+DF7Ca1sw+w0QJJgFD52SLP2yuMsQDW8aZfnqkzm6u48crKrX8uAGc21K9wZnn2AAgQqfXU/2Br3VIQzbseW1rWukTd91S3WVvwNk4jAa9jbVh
*/