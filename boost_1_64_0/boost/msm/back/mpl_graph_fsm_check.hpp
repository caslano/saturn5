// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_BACK_MPL_GRAPH_FSM_CHECK_H
#define BOOST_MSM_BACK_MPL_GRAPH_FSM_CHECK_H

#include <boost/mpl/assert.hpp>

#include <boost/msm/back/metafunctions.hpp>

namespace boost { namespace msm { namespace back
{
    struct mpl_graph_fsm_check
    {
        typedef int fsm_check;
        // checks that regions are truly orthogonal (one state belongs to 1 region)
        // using the mpl_graph library (part of metagraph)
        template <class Fsm>
        static void check_orthogonality()
        {
            BOOST_MPL_ASSERT_RELATION( ::boost::msm::back::check_regions_orthogonality<Fsm>::states_in_regions_raw,
                                       ==, 
                                       ::boost::msm::back::check_regions_orthogonality<Fsm>::cumulated_states_in_regions_raw );

        }
        // checks that all states are reachable or created using the explicit_creation typedef
        // using the mpl_graph library (part of metagraph)
        template <class Fsm>
        static void check_unreachable_states()
        {
            BOOST_MPL_ASSERT_RELATION( ::boost::msm::back::check_no_unreachable_state<Fsm>::states_in_fsm,
                                       ==, 
                                       ::boost::msm::back::check_no_unreachable_state<Fsm>::cumulated_states_in_regions );

        }
    };

} } }//boost::msm::back


#endif //BOOST_MSM_BACK_MPL_GRAPH_FSM_CHECK_H

/* mpl_graph_fsm_check.hpp
GcUEHvzFs726VCr0EpTZFrjRzIg5Vzs2y3APdEs/bn44l1iphwq2llvWFhvNtD02wY52Jvkt02oWePcWOlxWJeyvjwf3+zxGxDjnMU7gYA3AR16EB1BXQNGKm1gDqjpA93hnyp0cP2mis4EQDFFBJLhVQgX359JY6BJS9W6W+/f8NI6V+qYjbo5an8QCSQa50T1SxzbD0hp/lKfWc7XerlKTU0QiSSXaPjvfVIeHXYMDMxiNhDRi5eye715BBe5j2+0f7ll52MhQUJ5zWKkpBdl1r95amSG9h6I2JFpEb4nbuXojxZqNxj3ptyj6M76fWlZjdKJ7w+akGg6Fve/cL7vU0tD/tht84iiEz9y/VDmdgFYGmN/OOYcXOoNcHeurXNsJi6u/i95j6OJvLbnjaAWdCpdDrvS/DPK7Z/hMj1JCvPFZNnfHaoqYOrHTLsfgP1+TQN1LQjo2P3UVQsd44+omLqJ2WWbe6FjwRpVp0UcC6CuPvCJ4FtcZ/TwmT3785ZDKIy3apkXSUPDINA44ivtfdgIxHLwpItZcKthproFNeo4dmNICmn0mSA==
*/