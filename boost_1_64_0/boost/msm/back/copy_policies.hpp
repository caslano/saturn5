// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_BACK_COPY_POLICIES_H
#define BOOST_MSM_BACK_COPY_POLICIES_H

#include <boost/noncopyable.hpp>

namespace boost { namespace msm { namespace back
{
    // deactivates copy
    struct NoCopy : ::boost::noncopyable
    {
    };
    
    // allows deep copy
    struct DeepCopy
    {
    };
} } }//boost::msm::back


#endif //BOOST_MSM_BACK_COPY_POLICIES_H

/* copy_policies.hpp
/AndDpD3jNTI6mAwchcIUYER1rGnMhqZZLJI3LsABrCfVSnXdLxEjmmD0r3n1Mwda0IlraCFZ0UoZIpTckxmlDMijUAuHeQnM6AvkADXg9OVZORiR5eGe7hxqWtEgyXGiscjZF2vBYJqlnGT32n0tMD5kodgVgNkoN6QtcbmY82kpm8oo3vgr7Mmvv0hX+ZAyQBAc/zVwW234Qy5CL+Wr0ZTFntX6Y5DdmS6k8BbV+Zde4bUzrjOAj8mK+29AzSRSjOrUFzI087PMMQC2/UygeslMNGob4Me0quB1O4G6xnXkxztWo44/UUgF08jrOaSpeWTPCj6l2QEzmZUQCBSHrDyLjy5qzg5wvR7Yao4Ekv1454fPibhj10z15LImae+kDPkjvKLPXPMYVvrcGLDK/BHdoC+Z2uQQmQfxn07iuEY0GtVRnAXJaafliWts2FWEMLIy2MM053tReh+FfcwtbhnoBD2t0K6OGcSxQAunhnSQk8D1HFA5OCmwBX7shOTRsKwV3fLERA/IkkeeFH0DH7puO3FuFRdh1o9LPwv6FiFvcm7kek3r30ORw==
*/