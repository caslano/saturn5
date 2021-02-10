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
qwK7JIuz0Lo4A/k2aLlE7110lTMF/Hp8WiM3ErBaLJ/wYbte5fIarBCwvd+UWK5z+akxFvxclAsBv5+XpWDIcws5urlKUHyMUIAYQxRXKYpPYhQfcxTnIEetSFGKyywF3CWsI4vMTsPIzv/Jf1BLAwQKAAAACAAtZ0pSeXNKIKoBAAD1AgAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDk0MlVUBQABtkgkYG1SW2+bMBR+t8R/OGpV9YkiJfShmYOKslSJRAoDd+oeXXyyoAFGttM1/742JGTZ9uLL8efvcmxqUJuSa4wIrdqttNMvPPyWSuiIFBuWkSIukn6A+IWtYPnKlvlznJD8aRGGk0k/P9yHhAbnizQYuMg1uYYC1TsqX1cCCVXY1QcL0H2xbERE/qJdZsmPQWo6Dcc66H3XSWVQHBHi9bkuf87nMJneQ7w3O2xNVXIHoMEf7DQ4SvZeFnVlcUcvZb8ZzUREN6Ybb0cEaMsbHNoA+GFQtbwGftaqZGtBwYCi2oiqjUjDqxrepDh4jmqoAS1l0/DW+rl1IrMg2FuVLy7m/BTx8WaVFmydzW6cYJbmLHgIJ7fg+47SV2VnQGFZdc71I37wpqvxzhKfEFtl1xpbgerymIFvvYwW7PKY
*/