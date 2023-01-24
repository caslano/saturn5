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
ZH0WPC7Ttu1xTtts7jVfnnv90uAS515hgwPQPtMxCvHPmloH8ff4wj/x/3KTiviB9idoTR60/78h/dGGOkk/WiF9wfX01SB8tTB/YjYT5uGyME8Tz1LK9rpo3xReQ7TfBGl/8+dA+xO0abBfUaZ9RvpjvUi/vOlVJP0DjPLnhL7wZ6J0XRLp5/wUEukXjZRJ/5mRftYAuV3XaZCPXZd5KXYdkf0AybCDsXVMiEK7buYksussHWrqsOvuWuLfrvvhhrrsujNpqdUGxy2KXddGseu2eqjg4wE55Ycrseu6N6zTrut9mXZdpoddV9XsSq26zP9/WnUecmD48x5GHcmBAXVbdWnhNWjVbeFWHRl13/yHiQMmCgaAHpSsupqpY7ysuhUG/1bdC4GsukkhWXVg1B2Y/JI/o+4aLgjUcuAolwOSUZe1N4hRN/MRmfsnP+Knno2PXrulfyh6bemEOvTaE5/412sN4v3rtXsD6LXmAbnVrb0CvTY36lL0WrLLerX12kszVYvul6TVvlG0Ws1HIWq1Ew3/tVrt+V0habXPsmW6XpQtr6Uvke25pmGh2nOHiO479ZPpfpsH3ctzmSXu2G+sCtkvJHrn1I/7kx0drR+ST6uEk30JJ/vNrZDsF+Hj8lzmL4PjGa+5zEIJFY8EJHwhJIOu2IvwiRFj92lUhF/sQfhSPuBrFcLPYlMLRohVEJYic0CpmgPKOAeU
*/