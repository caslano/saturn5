#ifndef BOOST_METAPARSE_V1_EMPTY_HPP
#define BOOST_METAPARSE_V1_EMPTY_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2010 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/end_of_input_expected.hpp>
#include <boost/metaparse/v1/reject.hpp>
#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/define_error.hpp>

#include <boost/mpl/empty.hpp>
#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class Result>
      struct empty
      {
        typedef empty type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            boost::mpl::empty<S>,
            accept<Result, S, Pos>,
            reject<error::end_of_input_expected, Pos>
          >
        {};
      };
    }
  }
}

#endif


/* empty.hpp
hJ+Om/r9LPwR4Q/i5q+38MuFN33Nqb9dw/lr7TM8pN2fnu2Da/XvRwLvobQ/UrgaH4LPVva/Er/OMfl8vo3XCu+4ysmPdJ1+/DTeXPEsfpPS/7EE/4syP3gzfrbrMv/u+Ehwjvb74Xtq/ct/5v3jomxf4Acoz18CP0TZ/hj8YGX7FN5D+/7hTbX8HvhpHOySgsn3Y+p6vf6Uxm9w9i3npyQmUv8U+aE/4YXE+k44778bIsH1+LhK66e/zPzCgsf/QnyCE18i4xdOxL8P+D5WWh+9xn5/T8K/E74YD5nxU/xL4aG19motwlPCR+HF8bdJkeCNEu2TFub+xSfxLy2tk//T1t+X4BOFd+5j6++P4VcLvw4PmfYlPlb4u3ixfnQbz2eJ/q9YoXyr8J4hzDrxOfzPrE+DHyZ8IG7iU17EuwufjVeZ+Zt4R8fl/OW6KXwflPJdgXdQyjcOr1bKdyXeRilfCt9VKV/DHXw/lPW7f8H7F7aNlsjvkL+T+zMoX3/8HP9cGT/+Bv/Qcdm+a8DfV8aPt+N5Zfw4lqZ/v8T6bu0L5TsM3164Pnjx+u9m8tvj3wgfiDcx/T/4Z8Jn441MfnD8A8fl9c9Oo38Dl8/X0YXyvYvPwbu43trmL9+KzxLeso2NH/gCv9NxmZ/hS3yK4zI/QzCd8jv1Szl/cg98Ay7Hp836VC3xl4Vn8Sqz/gy+UnhQzd+F8u2DL3Nc5i/I3+eJb8f3VtoPTe7nScNl/k8Tf7UbXiGc8hfzrzfFA+NO+VsU/mqPfxlYl+Wvm0n7RRt/wns4Lvt3R+IHOS7jly7EY67L/t1Z+vjLdlwbf0nM1uvvdfgmJX/kcPx14bd1t+MvI/E1wr88ysnPgS8T3quX/esu/D7hs/Bi+3IO81taWZff99vxwfglju94wZ7/FPxU4b1ftOW7Ax8kPI0Xx//wvsJ/wIvrry0rPX/J5GRdjJ/PP0dYZ/69/X48jQ92Xc6/X27iQ0vHn/TH7yjx/m5S2P/x+O0l3t+7FvZ/An5riff3LoXS/BG/UXl/B88Qf6aNP+DTAiV+EU8r/ctH4Ic5Luv3efxAJ35G3h91z1H/Vta/HI4PdV2O3+HPOC6/v1/g/Jwi/5GTf/N5xs/Nu6xU+eq5vwtWyoMVxB8q46MhvL8yProL3lvpn6vDj9fmJ+Da/NE8fqVyfqmV+vnFVkWCqNL+SeAtFK/zbJ/Cd1c8g18SkvcvVvB5+CjHZf/3fPwivFz9aAE+Ei9XP1qIj3Bd9n+/SP+dUv4JuDZ/PYfvXWFdvj/exvfAW1qnfWDbL+/gEeHXHGe/X+/iVcLfTtm7acNL9D+EdvZPVjnxYWuIz8Fl+Zqb9zv+Gd7GOusL2vrpFPwT4YvxXcz7Hf9I+A7c9O9Ow99zXK4vGLzC+KE2PwK/t3BvGz9rgHP98ZuV7d/Gr1a2T62LBEn3+sj1F/ET8ah1+led9RfxE4RffISz/iLe33GZv+NO/FjHZf9q7au8n7X+Hfw5x2X742F8SYn84Kb+lMUfFp7rau+/JfhDwmOH2vsv/Vok6KblH8AP1Z4ffL52fjmeb8fl++1veJ0S37wIP0uJb34FP1KJb46t14+/P64d/yBcO34Nrh0/g1dWKOv34hWOy/iC+fhvIeuy/vgyvkl4l+vt8T/Cnxb+6EpnfHQj/VsV5ddP6oU/X2L+uynf0fizwkf+1ZZvPD5B+FLclO8z/OdgZx/rvP8aNjP+otSfmm0R9SsZn4yr8zNxdf60Z/uMZ/usZ/ucZ/s8vrviwRv6/mO4Ov8cV+e34tr8yaTH0x7PejyHa/3TDR6Pvql73OO1uLp+E97cnR8l59fhjSr52/G5Nc78Ojw=
*/