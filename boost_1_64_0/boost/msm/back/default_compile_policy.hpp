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
38QM1rk7Eq8D7Kfk+JuGBWQTSuNXzCX3GOuMHHqfSv75HjK7gd+J1WkZFxgn8EviwNOMw7lf8RfM81x8avAoYgi1Nz7Nl2WTU+CZuFfYiC3fjg6orcMp9Mi6TRwzgPyL36yjxvo+Pp9GRm3o4B1i47nYzD7Ywj6MsQpcKzwn8a8y8eZ6fuZgQ+yxFG4Gvzc6OB8buBmeDkNmDdjGevZxp26NTeOz8vytGxk/jt+y7xQ4lHx5MnkFnyvIdz/xixLP2IgZo9g/wG6pqcNyfxWbFHdi5/NYr7BHUMkTs2See2xb4gv1wVrsn3gRiJN/2GMoUkMFiUll5BPh/thG+FhNjhhIjqaOK368DXtVzOU/gr/fgozYsyv/Bx8gN5VLyPZmcvRabHY9+mWuYkd0hZ8U2dfL/Yoc0AF/r5BPzsH3d8cm4CM2aBjX0QlyDP4G290XX70D+d7NWnwi/nMbtk0bvoW4VcR2rqQ2ljXqOrB7EodX0PcQ4t8BzOcebI5+A8TzNJ8DJWIeebUynVz/HWqhUWOo3cC2wSv5KVQcxTXi/SBkT10mHiU+/RhZPIuMx2NrZ5A7z0APVyGD49HXFdQWMfjYGzr3V/lOA/4GP/aDXj7Cv2Xdcwl9PQofzK0MLng1+YcapYCvllmPFDcy56XEW/leNHkt3ckYu6OX17lWoh8w4b2IeRPIefKs8Gr86RnsmzOBNDV5pZEYwRpWfEF+GyOf+SdujUdmLyGbS+mT2Cv2H0Y8QcaTmONmbPhi5PQr8sgA+DkDDPwVsJFqhZgLXzliUSiBHMhZoTL+8CT7Yb9AjzzfV9kDO2MdUphE7H0pwD4Idc025Gtpr/hH4TniyAXogz0EAT8V1qsF9FVCPxX5fA/+E7wY7Ivw+2t0PoU5EuvLx48Dw/qF2r7wW3LDteCWkyvoq0Q8LNxE3Uc+Dw6h/znEB55FKTNe7E+sEd/Exu+gL34vpuFdyppzOkHcKRADWWrxDQRffim+/vf1v6//ff3v639f//v63xb/NfDO04c/50iLI99BfB7Aj9N+yb8JQ/ff/M68AaLxUCHWjq1dX7kLLe2ZfE8lrfiMv+lBK4ZuHkrL9eeh066ZyXXan/G3dGnFi8+Ap33t9iG0bC3zbAWtOH8+ONo3Vf/jL96Gln6i3Ed730O0tD99i/sF45/IZwGf7CXTiqtu/wYt/d3G/bTzjqGlvX3SgL42cTIt7eaXuU7b/C/uE/R7tqCFryW0tCPmcp02/jP6o32uk+u0F32h+n0dvmhnjAcn6OdN+hXQOvihPXQfPtNOPgT+aP/yPnjaJy4bQst9q6HTLuVvl9GKJU9ynfbRL8ALrp/JZ9oPlvCZdvYA5El72Xz6p313MPIS8Pl7rtP+oIf+aI85soEWeR3NfbQt+9HS/vFTxqF98Aw177sU/5MELeMJcLR7fUF/tL2/Y3yBfBdwXaCPE+lfoJ/rG2iRPzVvH/5Q6ILxRiAHgf6P4H6BvC7kOu2Jgs+0fCU0Lf2eQD+Cfv9HK+D/h+AE/W5S8zsWvgTz/obCPcw4tBzV0aK/uVwX8L9vAy12dSZ4Qf859CTgawN02oOexj4E/O0NX4L5H8H9tHedAJ726RvACfT9NzW/y9V4d3GfQL8f8lnA76XcL5DjcPoXyE/Ja+WRyFPQz1GKj8F8FuDOBk+7A3rtGzeHngT8j1d6O5Z5CuwiL2jRd57xaf/3Ei3tLYeBF/jX0+AE8zmK6wK/+Rbj047/mxpvJ/qnHfP2EFrs7U1Bi/w+gW/B+O3cL2hbuE6782pByzzbFR9fcr9Abk8ofd9HSzsoAP8Ce3pgCC18/Z1WYFetyIX2nrMELfp9l8+C3w9rpMU=
*/