// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_BACK_DEFAULT_COMPILE_POLICY_HPP
#define BOOST_MSM_BACK_DEFAULT_COMPILE_POLICY_HPP

#include <boost/mpl/bool.hpp>

namespace boost { namespace msm { namespace back
{
struct favor_runtime_speed 
{
    typedef int compile_policy;
    typedef ::boost::mpl::true_ add_forwarding_rows;
};

}}}// boost::msm::back
#endif // BOOST_MSM_BACK_DEFAULT_COMPILE_POLICY_HPP

/* default_compile_policy.hpp
1CqT3+92L3v/ad/3sXZaE0Sb9D6msVeaUNVLgzY6BeiDVxtLArRxD8BxrGdIcOR51lzzrDtRO10hcBMU7vWmceLLpz7g9OXq4UPuHyeryR39UgmuBkjNuHk60of2C2u1NokBGhIDWCOK9uXHq6k8Lcp3/sGw++GLkDsNqkIwa94dv1k5z4lRnUdJ+dNGqwCORwN7L0BVH6uWVW1G/r1esxwUuPNzZCwqm1OYEwUx3Vt/ASMxUiqig4Ug2V+mYO+Voy4SWdwLYhTynLXLQaPppv2sl+pCptEpVKlqTqdsTLLZ7CL6md/q04BElUiFcZLdsYve1fOKkJ0W6TWGZXumb5IK4+wp2udZETIzLsnt0m/olaOFSUNXEHq4XD0afNFWqiQG9E80krQvgzXM67X1MNvjUq6zXZ/yYISt1fRnokDZ2K6Z/kxDduxpa2C281ScrjgqDhlHhNeoc6TGaUtzu8U9Krr0KNmhZonbGJgv/SqBCXuBGlnESEaXWFsiM47JtejxeB+lnASAnANQNMeo8ByjwnPMJeF5u4RntNA31vPB84bDHngOXAC0F0wocm7AkkdMAD+Wq9nQK4+1/Vg+NHPwoIz3pQc53u3ZTAVEO474IDvRHbvsbQnZ6e+Eiuys4Mj+53D9LRNUTnt3P7imUngDqUAKiJFlU5S8avYMp8DeB/EBJVIKRzg1mGitwvlrTQR5ZbIFkT1UtJEJ
*/