# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_REPETITION_HPP
# define BOOST_PREPROCESSOR_REPETITION_HPP
#
# include <boost/preprocessor/repetition/deduce_r.hpp>
# include <boost/preprocessor/repetition/deduce_z.hpp>
# include <boost/preprocessor/repetition/enum.hpp>
# include <boost/preprocessor/repetition/enum_binary_params.hpp>
# include <boost/preprocessor/repetition/enum_params.hpp>
# include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
# include <boost/preprocessor/repetition/enum_params_with_defaults.hpp>
# include <boost/preprocessor/repetition/enum_shifted.hpp>
# include <boost/preprocessor/repetition/enum_shifted_binary_params.hpp>
# include <boost/preprocessor/repetition/enum_shifted_params.hpp>
# include <boost/preprocessor/repetition/enum_trailing.hpp>
# include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
# include <boost/preprocessor/repetition/enum_trailing_params.hpp>
# include <boost/preprocessor/repetition/for.hpp>
# include <boost/preprocessor/repetition/repeat.hpp>
# include <boost/preprocessor/repetition/repeat_from_to.hpp>
#
# endif

/* repetition.hpp
rZHyc5Qlp7Lr38dYcpP49t+Wls9jLfShpPyH0P6x+n+cJRNZ/oJPIDzD5SVLOV4f4TwAzvQHKYf/4DR/jrfkdUNVP8FPRvlj+wsoh/+Uw7+PcR4Gf0hT33+arrfksfx7Vft2iiVHQD6o2D/hNljyBnl+Ua7Rkg+x76dtsuj+gFy71Tt/8V4fCuC/Xu6i/rL50emWGNA/1cAfPj68t/x2WlJJ+s8k+IMC/wxf+j75VMySfZF+ALyyH253WXJWP+3/kN78B4/k7fP5//1psBvRsPD+8nUWxho78+nT8R+4hv/d9Zb8Tnz5XyJvbLBkrI+XyifAz/PGT33yc4ryN2+00Pb7eKn+MyxZ9Pb23xtPZMBrWPsKvh/h9pmW/ME3divNP+cs5D9r/8FtNj4CH0N4Cpxef6Ic/oP7606p/fYnLP79aeCzCE+Aj2Tzd/CxzH7wzeLbf1JiX3iTJS2+54uV8hx4BUlfzsb8h/gfBp/B8h+8lvBu8JmE2wm0H4Q74Et9+9NKy28S/ACmH7ya8Bz4MrY+tbmn/a1V5K/7SeSP5uu/S+rnEedYgj89Xlo/c+BTWP9xLubHbH0MvD1ftxT2yXmWrPCvf5TGF/wA3/yiNH9T4LR+gc+DIzMV7W/wUz31a4WifCXBh7LyBX4OKZ+hLbz9cMFPIf7lwNn9WfYFXv3eqX/Tinw0eGn52xjoSy0AvkcJ/26gL5ohnr4cR9NH/Hj6kgT3+naff0N74wc+jY1/wR/SEUef/LK9BG3ysAJ3P8vLRwLcv7ZXmv9p8ApiXwZ8GpG3L+LlJ8C5OJTDb48r2gfKER+a/vuv91/vv/7D3rWAx1VU4dnNUgJNYZNssWLFUCoWaGOahloqYtM2pYE0iUnKQ6PLZneTLNkXe3eTFlGroqIgVkXENyoiKioiIi8RFRUVBRURFRXfiCgPUVFR/GfumbnnTnY3N231+/w+8nHp3nNmzpw5c+bMzJkzc5/6e+rvqb+n/p76e+rvqb//r79/P/Tvh0L49wblJNi8frRQTOedQqWUTLs/neyqsUomm1q1un11e8f4qmmns2P18wxux7q1q5zJRCmdWpVKj1UmND6bGQN62+ZUeynt/FfoptLjIrl+tFgqTJQSubbxTDbttK1AvqNGZzL5VGHGaZvKlJ3R1R2jmXwyW0ml8bO9o31115rj1rR3jFZyMl2+3D4pUtXYI8ZG8VM+8WwhmZ0jLRVkwMg3ZxaVrJwop3P0T/vkPqiWU0hOdbbPk9uEk1/dHoDdUjpZKKXon/Z5FpIs7SyWC/PNVZxKOs8LmimTL6dL+UR2NJXIp/dSnK4Ojs44ndC3fUYrUwS1oNXRMthxbMdxe8rBsR1rlXIkS+VRtFoa/8ZnypncPhJPJp9IpUrzrVA568ypb3ae7GTCmZxvpvR0cb5ZnNK8s6RLpT2VJm8e1SoBemExkZxKl5VZ2tNi7UZcuyetOFYZH0/vcc09q5XL5JF0LOHssU5WUfJ9SCo+45RTmXlbrrFMYU+Z8DcP0kLDCnsraaIm5Vx2UntKjMvHKZcy+Yl9QUlLOpfOJYs7486+oIlG2/MWqMacIhhPFvLjmT2utL8tIMBENjOR31NqNZRVtsp8tdVJjKedMizLPuGlvLM4pymrNsrFp8d37gsGcokszON8OUjusdXwjBnG+HKymJlzDKFhMC6Hm6RYPtLRtjw9Vmx7Af7JFNvke1fbMW0vAwBwBaAXx31ZB+wL2gKUsTpeSufTE+3J+ckiPW/pyfabXjPfXOhOc86HqB5YAcy3FoWkg5bYY/G2Le9cQ6+rFH7vKXUpUkGbLr2j3J4MljKf3As9MuytWRuYPd/aZV6LJDNNR+M=
*/