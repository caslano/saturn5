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
SJ71Hkvgtxq3aHlLT7zdcaxUOzDzvGJx4lCNY961gMi63/7eh4oH0yP70rowY4q96uGMDrTf94/rxh5wG5HS8d2L9Tu9sbX+sVKnLVnWIq7vI9kC3tiAwZfq4mWicfBSJqZOD+1dF8+v1rMP+9XB6DdezdiB/fvFIYRa9rWfH66a3Ex9H4rOhLNER6KN9DVzeYq3gDImthYbXFgM65QUQFa3cpAa3N7jSQ9y45k1Y4uErs+39tB7usw7SdivTetxjLjmQ8t1HsGH6uOM/+h10zt2n5M9idCshyvwZeEcvhfqemywi+7iO1R2j2H4oRdrjHCT3YdjGCKp/Xe6Ta9twHEK1c12H6+mmn7SB9k4A9Ax41tuepYVfkuPBURf5v0uB4uldKcpGc1zjDlNcz8rlxvsuq5KV3N+lR7qolO+Ws9TLDQ0U16Zewua7iRis88ZWOylmUpOx4QldTHGMoSxjdyx/WDp0H5Htnq8xvFtEKbWg7RG18RLPRjHT8HouX3HwThVjNFD9QRN65DytPksP6ftSwYgd3DPGD5zBw914UwwMPsg1W1cGB0enLHCjW56XFXvi0khApno/SP3WMqWzTg5Tz+kIPf66R17Tl6/NOPkXf3U/DKDX+p12jA3Hb+EbOjF4Q6dgwjUnG3hu1baxUIdY7fVdKl733z1uvMQF86Zr8OP4dfVnx5Q+1RlmaHThVlvnuS6TgxBHvb+wD1DLDq5uBZCWrLZHvOOYP8Y9WVzJgfkt4xdcPiRBlveMja72v4eqN95sIigK86prkRb9X3IizNfQeiMb96nq4etdWi+V6EfjJm6mU9xi1iGtrCVfrG4Ti+OY58F/Mtgs0SIbvs7nWJav2xDO5HWnEuIDUMM3Stle62zBZyZqrW2/Co807Xxxa/Co207NlVtvF/jpna/14vza9zuN+zHG60TU3W92C/OiEPb/FdgYcHsX/iwfs3rfTmtWyfom+dKwp0emvZsc04cStUwC+ZZD0WhOh3XPXT4UC/bmHPdvB/jxFxz3uzGuN9LTxuaY5617/IwY4iVBsMJIVVFDeE687Yw8FB7W8h6B79g6IZH6HpPLGnop3YlWu3aMnCpos2fU3uxlie37XsjXjqHKXruhubI19jmdYYmk4j+Fk35tVcsjOWrES4+LnPh1UsuIqvn6KFzkiELZpODbbr53jZTT15v6Inat5TZD1BHtY/0g6v9anARP87SjYmhsfo4dvV7+tzU9s90fWxts8p+9t+PM6cz9vMa9XCesc07lwbbleJxM+agZeuhSRuxa9PIFW66/d1fJYsHxQKhT8sRJg29nnh0DnTh/FPRa0AfLoOtcV653Pp+Fj/GmXO7Hu+G+hhluKaGuNGHI7j19dalbfsmjVEvWMlXV80eQ9nIz/rCWR2PjI27ceor5ExcjN1W28dfeHR0VjNnCpEF5ptgHEzp1noY9150rn4/hDaDKd81ooZZGlm8IDq5aTqzXtXDOsg+p/hNfQxCcL03IO7x4iTKitUb6tFlL+b7GcSisRZm8RELZ8+Y5RxQoDhOWq31a10sAZp9G7YgzLqnDs7+DiWwZq79YGtjm5qkUA+HfTpAbRP1cEBW1NRp/GJxfzjUZb+HUgdH2sSgJdjginVxvUkOGtmUMLjwkjq4jJ6vyYH1cDgIgxre6mDUl2v04bTf2jiqhlR3ok09XtSl9bC9bSucCmIuetVrn3nt5MeZfXDDf2VnF66tW+JasDz7+Zc9PBj3mNqewvv0j5Mfp021+Jvkwbr569b115R+cKZP49cH1sFK27PelRHT/Rj0ysG+weQPqoPhDUlbJsGDbQynrxIzWc+gW+9PHVIHN92PK3txHnmY7wY=
*/