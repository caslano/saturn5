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
kVQv32nybud/fv0Yefxk/pvn82M46Z2BV+nEMKWcWSB1XrVPnY0ntVlXdcWNWU35nVsuUbkud9kmvkSmK4nG8WZSZnifZrNgZDD7T0ALlmMz4MZGtleTigKeU51APdVYPBePkpnaQJ0miyodp4VLcpZmsBDxumUFNDEwwjQWT64R/oywFJIjiEqCoYFEKA2W4zOkBZhzgRK0gJytEEx5sGfR7HiSFmgQMZZoXsbtq7vQf7gZRrfTWTTxxsMLXsnMsjVVtFxbnko1NP7gIQiH/tQbQML4yhRbQiE0MIhxUT3CokqzmOxRF4fB/cDJ0oWt73TNQtmd5bdiu0rY3rd9AeUiz1kRN973HefQyhoF/UNrZzANI+e89xU6HetPR/JSg0SelnZw3/CF5WWGXcOxRSylWSvbqXz7ubIdyb5CLlFDJ4KO8XlXnJaGNUG+cglPVluxsHOGOnuASducm/pEzVGmyzXETDNgS22nsHU/YQoWiAW0VSJ0m9CnGluXE1pwkblkeOtPwbTY2t/TFvmfe9ciR5vc+r6Y9T8XpEXG3siH63A67tP31rgtEl4FEUTTPv3QWgMYeJHXIt/vRlGrtmIrnlZlJlj85vR2LWQbp86uZWf/5/gXUEsDBAoAAAAIAC1nSlKV2yerGQIA
*/