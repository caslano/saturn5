// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_CHECK_BORLAND_DWA2006429_HPP
# define BOOST_CONCEPT_CHECK_BORLAND_DWA2006429_HPP

namespace boost {

template <class ModelFn>
struct concept_check;

template <class Model>
struct concept_check<void(*)(Model)>
{
    enum { instantiate = sizeof((((Model*)0)->~Model()), 3) };
};

#  define BOOST_CONCEPT_ASSERT( ModelInParens )                     \
  enum { BOOST_PP_CAT(boost_concept_check,__LINE__) =               \
         boost::concept_check<void(*)ModelInParens>::instantiate    \
  }

} // namespace boost::concept_checking

#endif // BOOST_CONCEPT_CHECK_BORLAND_DWA2006429_HPP

/* borland.hpp
/Alt5eX190PKM0EfE8c+/frNmg6+ckyA0e8/sUVj9Bs6A4Zzq/kraAy8NLdjIl9F01a6yqSoh0mDTCL91VcFuu3pf0i/9Tihd5cGdNzH/N61Cb0MGzR3eJBLsxz/uu4IDp59qQwPZW2/AcXQ4AHDPMkbA852ND9Mi21DOnEob+bn1E0tjCqaxmA6czezMWXNI/3SmyPd9AeB9N/egtJ1EkiPb0PpWjzW66nbGvTjs9CMkPdat6c0nTTS/TtSuk4a6V+foHSdNNJv2Ea64Xh+mLc/TwJd8ajZlx7ckfb0nUOanpSj3rdPAY060bDrZnWXjcG6wf2Jgy+ENXetQ+wyvBXuTzTjDivgyjzMLzV24kVNWB3tSHNgTOxmPPRolHvpixHX6Ly7hfmAs9JG/JE6/JlGPImTirHCWy9rwo864yRxhl/eFCuc6vx0Iw51vlLl/Vwjtl7nE6eb8aDztsatNeJsp0Pge0rr5RXr8dSG2mlVvOOvbOQ90sCLe1DsVaO84KcNdhxwn+r1oxjwl2ZiTtZgtEsxrJuJN4xiLPdhiJUNWIxcaZRh4k2jWDBYinSoksfeQjC291/Spk+/lWCbPO1iu5Bvq8Gjf+ZWF/tsHQ59MQ9xa824ORWdqHuzCve4UZwO4z1XyTpNMCMBsrqVfk4+ysDVhwY+fP2q39xfx45/aPeSvnoCXC6FqrZ4F00rW+3iYgc8lSjfhEV17nLQuhebxE6Sxf9XjP5/w9yJ6KB0WomY248Bpq6NG+v1yyGGtCGC2YIYqx8YsbeuiJi6ukPc+66EuLo2gzh5FcTVtRmM03X6qgp3EXb1jtX6fVzxbWjcGeC/h/jacQf3Bf52dYW74NindXENhd3QmKPx11L4DYw5VZ7nro34uvEa5e68jsJtYKzEdrWV4qnN0/Eor6cwF7R5ep/z+ohtsnmI3X4jhb2gPRtg/Zso7IbGOb3O3daEp3W89aaNOKzju2jsWcBe5BiFbe7mjbygQEzjzdsV7iLH0HbVpm6peDc2ZqNeX30rxbOBcaKozsseSM9iMif3Y8e5WNNH3rz/C9O3PdIPcT/dRHHU8/zQhlzrigTX5JUdtVeNB+d3a5t/pNRUH++QAO0B1N4nDk9FKvjFFvq2Rpn/ue44pepHz+XvP4bYdQLo6JiAgL+8gbfFmjFBNyPOHndxXb7tSoABx1edXA01uD7ZedXh97me2jTpDnn2jw9pl5wY3P9qqXXc6S/CPsjR9pR6USMHuSpp55XdXAsuAzS3t7raO9aectUCG2mfIbRdhHZmQNvf60/uBoJKHmlnh7TpinZVdU6jtjtgZbVrZ2e1dUX195jK22HIvxHD9R+tA2U+TVulntXg98p7crl5rg+uy617rYPpzYA9dKz3kOG3uSvAt+6Dj88s4rfbX1F9U6l3Joa411ffdgx1uv1K5bdqvMfv/6q+Q1LG94mr6O9g6Yzvv8XvKw+d6Q/Xm+evqr9DgWZPQLfQPMBc0qoxAb9v2Vp+xzZz/SqNOwy/72jv2LVrl1GOtqYtdY+Y+jpTfV95MGIf4eK3tlnmLWn1/fisme656vtqryyByXOtHGhHVJ5AgQbPPfX3/o7+DjCP/TbSPrPXpk2ivHftq2htmDrh90vvVX2fhCrF7y+4N34HPKbBDuB3nXoLac+9b0lDy6AE4vp+/n6atnJoRrmwU5ouD7S6Zpn9DmBKXyOT5vfWQfy+0/y+Vn5XFTMDzmiH+bj/DHxfnZktzeii8hhn7El1gXZJ2Sd0Xiozg+cwVz5Si9Gu6hcOle1A9dnLKrs1Xt6jnjt+7NiJoQ+TL4yRt45BBr7MvXS4H71nWkVpm2zvUU9LK/87iwvqIvc=
*/