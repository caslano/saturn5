/*
 boost/numeric/odeint/stepper/detail/pid_step_adjuster_coefficients.hpp

 [begin_description]
 Coefficients for the PID stepsize controller.
 [end_description]

 Copyright 2017 Valentin Noah Hartmann

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_PID_STEP_ADJUSTER_COEFFICIENTS_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_PID_STEP_ADJUSTER_COEFFICIENTS_HPP_INCLUDED

#include <boost/array.hpp>

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

enum adjuster_type{
    BASIC,
    H0211,
    H211b,
    H211PI,
    H0312,
    H312b,
    H312PID,
    H0321,
    H321
};

template<int Type>
class pid_step_adjuster_coefficients;

template<>
class pid_step_adjuster_coefficients<BASIC> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] = 1.0;
        (*this)[1] = 0.0;
        (*this)[2] = 0.0;
        (*this)[3] = 0.0;
        (*this)[4] = 0.0;
    }
};

template<>
class pid_step_adjuster_coefficients<H0211> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] = 1.0 / 2.0;
        (*this)[1] = 1.0 / 2.0;
        (*this)[2] = 0.0;
        (*this)[3] = 1.0 / 2.0;
        (*this)[4] = 0.0;
    }
};

template<>
class pid_step_adjuster_coefficients<H211b> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] = 1.0 / 5.0;
        (*this)[1] = 2.0 / 5.0;
        (*this)[2] = 0.0;
        (*this)[3] = 1.0 / 5.0;
        (*this)[4] = 0.0;
    }
};

template<>
class pid_step_adjuster_coefficients<H211PI> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] = 1.0 / 6.0;
        (*this)[1] = 2.0 / 6.0;
        (*this)[2] = 0.0;
        (*this)[3] = 0.0;
        (*this)[4] = 0.0;
    }
};

template<>
class pid_step_adjuster_coefficients<H0312> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] = 1.0 / 4.0;
        (*this)[1] = 2.0 / 2.0;
        (*this)[2] = 1.0 / 4.0;
        (*this)[3] = 3.0 / 4.0;
        (*this)[4] = 1.0 / 4.0;
    }
};

template<>
class pid_step_adjuster_coefficients<H312b> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] = 1.0 / 6.0;
        (*this)[1] = 2.0 / 6.0;
        (*this)[2] = 1.0 / 6.0;
        (*this)[3] = 3.0 / 6.0;
        (*this)[4] = 1.0 / 6.0;
    }
};

template<>
class pid_step_adjuster_coefficients<H312PID> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] = 1.0 / 18.0;
        (*this)[1] = 2.0 / 9.0;
        (*this)[2] = 1.0 / 18.0;
        (*this)[3] = 0.0;
        (*this)[4] = 0.0;
    }
};

template<>
class pid_step_adjuster_coefficients<H0321> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] =  5.0 / 4.0;
        (*this)[1] =  1.0 / 2.0;
        (*this)[2] = -3.0 / 4.0;
        (*this)[3] = -1.0 / 4.0;
        (*this)[4] = -3.0 / 4.0;
    }
};

template<>
class pid_step_adjuster_coefficients<H321> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] =  1.0 / 3.0;
        (*this)[1] =  1.0 / 18.0;
        (*this)[2] = -5.0 / 18.0;
        (*this)[3] = -5.0 / 16.0;
        (*this)[4] = -1.0 / 6.0;
    }
};

} // detail
} // odeint
} // numeric
} // boost

#endif
/* pid_step_adjuster_coefficients.hpp
eGGbQDmtCBSR0vWwuJ59u1ckZjwxD1eN3MMBkrkLZthTR0/XI45Hcf9Mkf7S72z+hpGErbKHTLvbxvbc53W3H6xdpl97HsE+zO+0Oi8RQh1WxxrO7S+XPRgV/8F3Nx7h+Nkc4SzgZ1Pxoc6c8i12k3eDMd6HUbUhrH+1D8+b5W2RJWfKtgphO+v1uDPUWXl+ngfUhfXWx3D/uWs9nghDL+CyHvpmnvBM/ub6ZSYMlJ5CvGkVKGRRBygUm6frVUEXGrWnQZktltr+Y1HnrXTOB9ld1AXT9Zpwp0KrvXTzen2YL2/19EFni4i6UHyUrgcj1uePqqX10Z1jV8Lc6F0gT9gqa075B7vZFux11mALOl91fw+VHbNFrIu+1WlM3wcIFtgc/sNK+Is+JjPCqUai1ZVFrci0XsVXO931QVHHWaBn4Pq09Sg2irmYFJLrExWygs1qPeINT5B0F5DxMPLzPui0pfq/D/RtPUNle249OECeF42eoeuDe9k/niTKZmROaM4znWBZj8nwPHvugudNlNoh9s/KI0Rze1kc+uyG1Xo7WU7bqzzMVzEnGptuZhf9WJUQKqLBdD0YTtZSZvqg9R1rxUPu7ERpvVJmRMXq+G7S9QbFX4UygmE+f0Us/ZzkYOiG4feoCaPtuayHbasV23A2PD+0UmTZKEpifk+rTIbntFn53508P9EQ92Mf7lTpw/MwtpHFwoQplBmj
*/