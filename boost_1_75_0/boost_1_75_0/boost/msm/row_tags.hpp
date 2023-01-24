// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_ROW_TAGS_H
#define BOOST_MSM_ROW_TAGS_H



namespace boost { namespace msm
{
//tags
struct a_row_tag {};
struct g_row_tag {};
struct _row_tag {};
struct row_tag {};
// tags for internal transitions
struct a_irow_tag {};
struct g_irow_tag {};
struct _irow_tag {};
struct irow_tag {};
// tags for transitions internal to state machines (not using any substate)
struct sm_a_i_row_tag {};
struct sm_g_i_row_tag {};
struct sm__i_row_tag {};
struct sm_i_row_tag {};

// flags used internally to handle terminate / interrupt states
struct TerminateFlag 
{
    typedef int non_forwarding_flag;
    typedef int event_blocking_flag;
};
struct InterruptedFlag
{
    typedef int non_forwarding_flag;
    typedef int event_blocking_flag;
};
template <class EndEvent>
struct EndInterruptFlag
{
    typedef int non_forwarding_flag;
};

} } // boost::msm
#endif //BOOST_MSM_ROW_TAGS_H


/* row_tags.hpp
ftclEvbvXEL4G/o5HQfwY95SOuYuJbx67SuCufOWBcq+L5N4DmoXJWKOLNhSJIhLsT6Ot+ROWE9Dp05jJJvxkyVHyhQJ7VPRMp1XzaWu0ekcyW0J8HFgpqs0cREVQ7I/CvuZKjOg6toP7swEnOroCvWdXANYExR1zMba+Z7URLLcBL2K/Ve/3L1Q/6i8eNFAlVdb8ssjSMPW6aUuSUgySkiaCsnln4NVrgzxLYgzdXUQxKgMSF63kScIu6YeT163Rk5eZ70TcoK4vzWnrrVt8+0hm85oGU85I0r5lp+RVYPcbrfj2XlsGOx68UJVL9hdwCcqmT4TFdyIdryd3iPtM1bLQeJo+6lEHM3ks+hPiRzu+oyvp3jVs+L+lRVvevhX0sXDFlxFG/6jBXLkfYLVlSxMflE0/VIqyWTH+idUkgnrKCW5aYESqnTCCJ/6logmF4mmEogmV/a+/cGU1QqAPPVHw6z+7FIN1XMKM8zYi+Ens6Fdc4fZ+K0158KhemWHb4XUNYY534ZxgluLT1a6Yxd/C3OUebQuOffHzAsQjg8l5Q2wVs4ao3D/g8SgRRttTWAJ9kH2FmbaryoKk9cYZS/skcHk05PWYPPlNdh84lpag82nNuGyuBXWW1OUtVRcZs1TPHbtwqS6ViYIJyXHbYajVxQvd59MbrqIMGl51XcxVXLMKTTijn1tDYliHPUi9qOkahAbicILj04d
*/