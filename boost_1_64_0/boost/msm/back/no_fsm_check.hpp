// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_BACK_NO_FSM_CHECK_H
#define BOOST_MSM_BACK_NO_FSM_CHECK_H

#include <boost/mpl/assert.hpp>

#include <boost/msm/back/metafunctions.hpp>

namespace boost { namespace msm { namespace back
{
    struct no_fsm_check
    {
        typedef int fsm_check;
        // no fsm structure checking
        template <class Fsm>
        static void check_orthogonality()
        {
        }
        template <class Fsm>
        static void check_unreachable_states()
        {
        }
    };

} } }//boost::msm::back


#endif //BOOST_MSM_BACK_NO_FSM_CHECK_H

/* no_fsm_check.hpp
dOHM88rWHAPj/BhcoQtjM/Kf6cJke/qRf3V2/zj5cUqT5VtHurEZl52Y72oRR/ePc6pDLZd5Hqybz5Tmc35/ONOnziMzAxaWZ6L1q5vm+ezSWLs/KWHrGeU5AQ/N6cDoIHJEHUztazBMjllij9Fp+56Jf8f7McjKN/9wrD+cX0+BDj8WWfn0FE72hzN9ar/K+rFOYaLtcrUfg0jc3xt8ah0Mod4lk9P8GAwcO8/gB9Y7G16c8fW45vsHbozxdYMJNhtdur4uxa5t62HMN5/0aN7Hj/DgeNu57zGz2tNfen3nsr/umvNaz4qmJ7jo9IFCugw9XxzqpnOy4rr/Oc/9uIGAruvMo+z5MBEz54T+PoyI3Qeqzvp83rz7eIwf6/d79lB0HeHF+31/ks7pW8KavrUdXmbh+XL0VuN3bVpPV/sxTr1l54FYXRwPhqCP1Xa+uMaHM3KycTf4cfb5tbbJW7w4v7/FbvVi/P4WuL0OBnUL2yfrYfAj17uD6+pg8CPbb4t3uDAd3rnp9YSd45zMhW70vp1t++qZQL4bIdvb0lX7glth1h75uljZIZvx1vewFurhZNi2ZF6qg3FcU+/99Y+JtvMwmytnbQGLmlw2LrbfMjZR+/sLRq918KwmQZj1VLAe5tTafHQemxewMXbsM3ZGTHNjiCe1r2ozNbAb02/cE8/bOHY5iEt23Mp56UkA9t+LKdn01d6YYdaaNj/OpLExTb+/Fj8XH71gLn+4ZMFC9bX+ei/6AR+dYB6ioO9kW5CVE3FSn/P6sXIBrdfBcsntym+l+niJs/ct0g/6cHiu2bcIPGToypaT/6fsPIDbaKo4foRePlBC76J3UBw+CN1O7IAh2MJ2AqHJsiU7IrZ06OQUqukdTO+D6B1EL0MRvYPoHUSdoYvey1vd3v+93bdngGHmy/j/09a3u2/rYd4iNKTc7k9jDFGMWf0R+xtKj7dWNhqr6dYrp6MnOZNCUV+997haerXMPlAXifWob1muMj67d6Iyc3zqaOCt5G4uRwm0W8sYN3ZnG0myVW+L80v93XkqQDLIVrsu31Uc7PYb8zUJ+Z2DXJYKRoy7O9/O48w2k5vH/q4s8li/bZaG3fhKMj76IS1Ozv8K38n/rc1rDf3KLdO1cjKoDXrEzznfivvZPuOOGA20+fM1x22euUnNHQxx2y7nz44aGKdu5XAYzjFeeOHIM7bY33fDUGUw9HQaNYNpiT3OnrfleKJLGH2azryaol49Rcc8ZX84vLDUET779zeB7h01js4hDfslAwLj5/DvmW4/XkEJpFUuc2Cfz6m+FwzCz7TyHaDZoj7A6X87NCrmA6qcd94ldZ2/0iTrtfqBsD3ucxi/IBqYd1xZcSqs+Nsu0/LCQnnMg7Pifr7X8CBfm4A2fJmvHYA24DJes/GhnMr/gGYu6NWr41oSb52ybmovoYqkMUPor4TeDJ1Zj34A3csyv2PR+ykz0o6Qb06/vTTDNlj4NbRYxM/zqr9AN683oCHATv4G3VxyaW3awQzlivyjifH5rH/6WmrnVEIx/CDNbDUzStjQ9p5LSo5uetqWIs+YgLHbQeZuxgQFmQjmIpqxWaqh3V4czFkqM30PYDbV71K52/QRetugckthZ4uZNh/Xm4uLR8WbatExq6XXcRazv/fuYP+eFg/vpUw5f89u1EBfPuzq5G04fVwR8YlnmKXPh7SaxfCtTt0WBOZeSwGdUlGrpXWDuyuIx/ge4p1A/B730k0EVYQ/4+tpFmnju52I8b18ZBeO/G9Zd6PjzHZKVHXrjWZdvB8Y3VPqaVvOtJKrxQ9c53a8EwttfFu8sv9WpWgT48kDpW5uc5u7eqyPAjrd1ds=
*/