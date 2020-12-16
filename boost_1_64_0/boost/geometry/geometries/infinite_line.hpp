// Boost.Geometry

// Copyright (c) 2018-2019 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_INFINITE_LINE_HPP
#define BOOST_GEOMETRY_GEOMETRIES_INFINITE_LINE_HPP


namespace boost { namespace geometry
{

namespace model
{

//--------------------------------------------------------------------------
// Structure containing an infinite line.
// It is written using "General Form", a*x + b*y + c == 0
// Might be conceptized later. Therefore operations are implemented outside
// the structure itself.
template <typename Type = double>
struct infinite_line
{
    infinite_line()
        : a(0)
        , b(0)
        , c(0)
        , normalized(false)
    {}

    // Horizontal: a == 0, for example y-3=0, y==3
    // Vertical: b == 0, for example x-2=0, x==2
    // Through origin: c == 0
    Type a;
    Type b;
    Type c;
    bool normalized;
};


} // namespace model


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_GEOMETRIES_INFINITE_LINE_HPP

/* infinite_line.hpp
L0L/Yde+52UpsZjRd3/wbFczxc91qKPx3RF7Y9JkfXBKIBVdiWjNyODzoAY/YoKR9spX+x/n2ouvaRxZbE1jVth+pMh1WUbYPQzhr713HO3YY3uohdb3NX32HT3Hh/x9fS+X9JRyx1Glocb8X9bzuPUDj9YJam9Oaff06Puq7jnaSWJPuu9tqTl8Z91zYOK6muiP9UW8D03Ph0wTPck+731tTjmZKO920q+c75aTM6IWtMLT+H9fm1Ni31npa1G1rS65FnW8+In9QSnha3f2PGp7oBcv02F7OLAq7cVlbnrqdKis3OEQ51GTS1m7o2Yqu2mxXuQmvlr871bKnWGY0T5caMxkJostzWqINO3X3SV66vmq4O+OmjfGu2arWZHm66hDpGw8KHoyTfqWWGfl5L37Rc9lViJtdy5PyTm+UDvXc5g9DpnhnD0lchPL7NiozJOFTtp/8U/xtYyOHWfEvVru3HotseN2J/+on71rgSQFTJToXbWkkZgZgK446xL3XBe+dES9YsQxhSvlXc+wMYUoUesfNqYwSNQmEco4sSeYIn5w74psKe+nm5UM2mcKuZtFno+RdWkl5wtXUwauL/ff90uN3M2zfigtbG2uN79QH5Yy35dZynyfM25Q8JztgT+CzCEo+1Gv5V5erBzoQt6S+d/R29n9bp4p8tqgJ9/rfeiO3jzfBdZwa781xR0/az9S7OAEh1vc+J4met9G52A3vk+MljZV8toKywpbE6B9XOknThSzH1jNiZVR5HHHr7HDZV5a7XP809Zdi3JQ5HrBslaloHFjjWV51iJLHOg3uWO2vXsGwRSR1zGfXc+61OoWNucyx1MOOosfAu4YXleRe+q+Q3aaiDwnarCvk3WafXajArO93/Hqrk/vt3Tkw8HHAtlWWrGyM3bSKBm3ddYtLxK9y4POuiRygFzqIXWsxt02iWNaPlq6HOrzC02Z1Pj7XMzvouZaqGsbNE1cPY7/W2NfFfGj8XOUHe/BmtakEmuk00w9LHaUdc+1PDrCyL2JgcslftOQckXPJ1Y19LWxEtz9di0k7/zTP5D26GnfbG/ZdcdLhou/dwQj1U3l4Wx5vyJY/J4Y50zMW+T9bFI20Xsu+KwJM/NHO5HcSOvt+aL3Cf/NvqD1rM9vvczzFs9HPF/yfOfrb3XyF+j3u+P/d/2x5P9Q+nHG4IQ8VsdNHZOvaWOC9JHYfXtUT/Q+7N/GHv0Un7xz880vgRirMblyU+Arfrn9ezFXIdjAGuqpn6dOtLzrM8V8effb5WWRnwvEWrsCIX/psj2dV6ynYU6W9KrmC5IzGtIqtNA1V914+vJstwIRw1vGbcOmM1oyRc7KD5h+lti3TNqXZJ5KPFk89XnSjB7ePi16DmJPgbXCaucPjTle4a7DKRQ9bbVeCJkpZ+VbV1sXiPu97fTWdV9aBsSPsSXKk+wY9qxNLRgl+QJfJeLPaCtV77n7WtQ3oW+5c8+ouDFiTOhO/xNqVmTMzJL8fYu3/TPO0ccJfZ+sFzM5lt+TTu+J2m7culnXxLlmZ3j7jKtF32AdryzhR42HOXzchOKhjfgpQcZ89tJnSn9a1/AHluyWi0lrs4y/tHvT1Uy7p531+Ev2lViLr3oKXHuv7ieX/RcuL3V/QB01M+kZxt3k7Nx5CfUZgurNV0YmnxxR5uMx09I7XyK3ySX7TqH9uBsk7Qv8Jdana1v1sLxf7NytrPon+StYr/ki9qGwt9Bjb2n9oyPyPtvdd5gi6TOX/nc0Kd7N543TNc84cXp1QfE4dfTseUbvkI1dqvEeisMM1fMleu609fycGKhTapw7dsY+67i7zCrurrNmKo143kQcr0qxn81p8pA=
*/