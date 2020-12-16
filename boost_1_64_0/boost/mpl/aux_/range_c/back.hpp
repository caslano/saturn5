
#ifndef BOOST_MPL_AUX_RANGE_C_BACK_HPP_INCLUDED
#define BOOST_MPL_AUX_RANGE_C_BACK_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/back_fwd.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/mpl/aux_/range_c/tag.hpp>

namespace boost { namespace mpl {

template<>
struct back_impl< aux::half_open_range_tag >
{
    template< typename Range > struct apply
    {
        typedef typename prior< typename Range::finish >::type type;
    };
};

}}

#endif // BOOST_MPL_AUX_RANGE_C_BACK_HPP_INCLUDED

/* back.hpp
VfAnrIp3sBr+htWxGNtdDayANbES1sImWBs7Yh3sjHVxCLpjInrgaKyHE9ELZ2F9nIfeuBB9kDKkvazce5F7Men8px//vyH3EpdIn2Gr0BXX4Ku4FtvjOozB9fg2voeHcAOm4UZ8gO/jE9yMuZR2mVgXt2Ff3I7BuAMH44cYjbsxHpPxHfwIT+BePIMf4ze4Hy/i3/ASHsRC0j7bBw9jU/wCW+ExjMEvcTYex7n4NZ7Ak/gHfo95qK/n0RkvYGO8iK/jD9gRf8Ru+BOOxVRci5dxE17F7XgNL+KveAmv4y28gY/xJjrbs91hbcylHJ8wNzZFOxyK9hiFeXAM5sUJ6IDbMD9+iAXwOjpi2TzUe+yKRXASOuEMLIqf4Sv4EItjLupJCXRAFyyMruiMpbASlkZvLIM9sSz2w3I4AMvjIKyAcVgRp2Ml3ICVcStWxWSshn/D6ngIa+AxrIXfYW28hXXQMR/1H4uhOzqjB5bBelgNvdAX6+MAbICh6IN3jccnud9kvA+VTlCuC0zvdueW9nN2WAXzYn3Mh43QAcMwP+qxACZiQVyDjrgDC+FOLIw/YBG8iU54G4tiKSVurISvYC10Rg8sjsY+HuX+k9yXStf08Zgk2+ubqvc0fHEitsdJOB4n41acgldwKhZTzl/QBadjK5yBw3AmrsBZeARnI+lhv2m6n0RdlvSU5//2qAzn5PzxPBbHS1gaU7AC/ohV8SesjT9jPUxFH/wFW+FV7IDXMAh/xUF4HcPxBi7B27gB03AL3sEreBcf4D18jPel3fkDbIq/YUt8iGMxHWfiI3wLH+MR/B1P4hP8Dp/iT/gP/AX/kHoVkNt0n4n7TnIe1Zb/d5T9KvOQL6wvFsdfsDRexSZ4DZvjTRyEt3A63sa5mIbJeBcv4j10kPe0CmE6euIj7I+PMRR/xwjMlZv1wtz4EdrhQbTHT9EBf8H8WEzeuyqDJbExlkI/LI1vYBlcj2VxE5bDZCyPqeiG9vL+VRF8FV2wClbEalgTq6MH1sAorIVLsTauxjp4Ad3RTt6vckAvrIQNsC42xP7ojcHYCKOwKY5FX/wIW+B+bIknsJW8h9UWC2J7dMIe6IG9sCEGYAj2xjDsi7MxFA9gGH6Cg/AkDsZzGI4/YgRewxi8g8PwMcZhbupLPBZEPb6CCVgSR8p2R97LPTDObeU90zZKXZP61UXqlx+6YlesgQOxMQahHwZjDxyEfXEwjsVwnIQRuBWH4k6Mxm8xBn/HWKl3w7AuxqM/6nEcJuBEHIEzcCTOwVH4IY7GFByDv+BYvIFv4j0cj+k4EcuybpOwLU7GLjgFu+I0DMDp2Adn4jichZtwHh7CBXgMF+INXIRKX9NLsAQuxWa4DPviSgzCVTgB38EluBa34Do8jevxHG7AK7gRb+AmLEW92oz1cQv2wK04A/fgZvwIP8C9+AN+jCm4H5X3tD7HRngEG+NR7IBfYHc8hv3wSwzFv2MknsYEPINj8SxOxm/wLfwWF+D3cj5YzU7up8l9NvLecN+rjFz/lZPrvwpYHStiS6yM7fFV7IZVcQBWwyFYHYdjTUzC2jgX6+B7WBe3oDvuQg88gJ54CL3wLNbH69gA72BDTEdvtCOtPuiAr6ErNsba2ATr4evYCJtiK/TFNtgcA7AFRmNL1GMrHI2tcTK2wanYDudie1yKHXAVdsR12Ak3YWfchV3wMPrhd9gVL2E3vILd8QH642PsiQWpn72wPAbgq9gba2EffA37oi/2Rz8cgCEYiBE4EGMxCMdhML6JoTgPw/BdHISbcTDuxHD8FCPwEA7FYxiJpzEKL2A0/ogxeB1j8SEOQ+V8OR7dUY9NMQGb4QjsiyM=
*/