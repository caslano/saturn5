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
cOYinP8JU8F5oYcKhjfDEIY8LzibqeEskJ9xxA7qKcFp/ezS4Fz6H4IT1xcvF86F/uFcSqsGAOphrQrUeDWo29mdDbTpxQvam7uqHvtc/Zgj1pYuAVz46aUBvPYTAvgxLfJdjn++A05L2oGrojm0ethVq7gvcf/jJ9xvp3Idfu3hOlQNmcFzyNRbISLZMNEdxbvosQi4hK+89I4mJx6IUJ+EcSSEx8+j9bzXX0EpPJcODjo894ocT9dnHs3/6MYYOGx1Pv+apKNupdsD6XZfuv2EfDuabt9Nt2+n2xb59rGX8Xozuh1Dtzu+RjEyr8nxTZKF81KRkuLeAtna9lIBecjDXrTDZoCxjvxYr8F60K4npVqbYVI6+3Aj7KHcyJOzJmOSf4g2sTeliFf+PCytlwi0RIPZ6C80kAwZqmkkhXE1lN5ADFQ6+81T9hBLfT44w6vP59R9NsxAsvfu6L1yR/cUlU1M8P/B6RfCIN66/fQLGG7dy9VKEA0coGb+ACqXAbrFEyAYt8oP9ZqVMG7iJufMlxEOuT7XPsZdVd8KkFTKI/dkYSUkZ54YVXhca7sdvngL7D/+Ta8qylPtjl5+rL7GObmt272CQjU2OS/Up88nKnV95G/1Y3KrapCgqgX2eJxWHBxna4wDYOG5l0xgaPNKYKIpzl1mN8XJOdSC9u+tX7361xz69/3MCI3cvyHB+sd0YtVXvUKqVZap
*/