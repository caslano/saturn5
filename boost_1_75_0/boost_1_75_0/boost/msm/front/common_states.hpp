// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_FRONT_COMMON_STATES_H
#define BOOST_MSM_FRONT_COMMON_STATES_H

#include <boost/mpl/int.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/fusion/container/map.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/msm/front/detail/common_states.hpp>

namespace boost { namespace msm { namespace front
{
// default base: non-polymorphic, not visitable
struct default_base_state 
{
    ~default_base_state(){}
};
// default polymorphic base state. Derive all states from it to get polymorphic behavior
struct polymorphic_state
{
    virtual ~polymorphic_state() {}
};

}}}

#endif //BOOST_MSM_FRONT_COMMON_STATES_H


/* common_states.hpp
Q433KRq1VmaKOYtpipbF8/VXOM91kvbqyfM7Dk/hszI8qYI4EbPDd4K6TAzO8l58DS6STfyq3dFJTNA6j90oV3modNrgSwixaibqAfcNbYPB/XJPv3Af84bb1jMUuF/5wBtubSc5xkgF88zpQXGYFwiHD8QHg2Vjul9YfmvpBcuH6aHAsul9b1juusMfLF8UyLC0lGBpKsOCpStU4HjiZmabYPCcS/MLz4brvODZmxYKPBfe84ZnRKI/ePZNCwrP/GDwLGsdDJ6b/cPzaZwXPPVCgqeDDzwv3+4PnvBpQWktMxCtuVoFg2VYD7+wjLvWC5YuPUKBJXuRNywbbwskLzpM9S8vPp7mKy/Ci5m82LCi1i3Li/RFdcmLUy2DwT2iu1+4/4jxgju9eyhwP/auN9zbO/rD4e1TguIwJxAO2weF5VWTX1gebOQFy0RTKLC8/o43LDq/sAyZfHn6a0iLYLBsMfqF5bsGXrD8xxgKLJVve8OScqtfOT4pKCxZgWCZc10wWLT+Ybm3nhcsh7uFAku4DyxjOviV489cnpxY2zwYLHd18wvLa3ovWGJDguWehd6wvH2LDMtAvoofbxb34DJ9lakgv7nGNtgi9ogxw468Lc5dYD+KpwSxhSD2xY+0EQpHJsrL5HStgfqao2+884E0ZnLQqvlW55OLa90Fk5prrB/AaGCS4yEevjnxXI0pIcx6myAOjhFSB8dZ
*/