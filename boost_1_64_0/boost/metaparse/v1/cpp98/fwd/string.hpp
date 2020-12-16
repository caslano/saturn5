#ifndef BOOST_METAPARSE_V1_CPP98_FWD_STRING_HPP
#define BOOST_METAPARSE_V1_CPP98_FWD_STRING_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/limit_string_size.hpp>
#include <boost/metaparse/v1/impl/no_char.hpp>

#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
          BOOST_METAPARSE_LIMIT_STRING_SIZE,
          int C,
          BOOST_NO_CHAR
        )
      >
      struct string;
    }
  }
}

#endif


/* string.hpp
8rzDnkC/9yMvexD/jGxecBy+6hVyzrewl8dwbv40urAWe4AeVA6DF6ez9wNoO4EYEJ3Z/VBocAO1IeKuh8fhs6bid6egK/D45z8g/i5Hht5hH4upld3P2P8gjkamdnoJ+vD/m2wOn+HP9+Zgq/FhdXPhQRyZfRlbTJxa0RgjnyCeJT4t8PeD1xNn1SP70G7Vqdwl3BefyNn7TdSU943hk7C1t99B3n8ycQr56HXwfxoytwu8Ho1/+Yr47oE5zMG+74dXtfT77c7oSSV7fgi7Tp74e+zqt7Fvt/2SWAK6DOBc71Xik07ots/D+IBGfNir3AVnvn+3Eytjey4dRT73V3K5m5mjDzZgd+h9XF9sGWcm1CtveB6Zgs97jCLm/iM2uZP8jfE3r2LsEdCZ8b99CTWqXeELddON+yCTH1ATwk/fgh89dhk2Hd3+cmNyvlpkdl9y+VGsB599KDb0wFuQD84uf3wXufUxxLbEBo/fTJx6BbV91rxoHLVesW58yy7Eaqe+iX8jAW0bjl+tJ9d8hTxmNrWfUdjt0fiAj7GzH/A3cnDoLsSzmxO/8/fTd5EbHw/P0JfTNsNOv09OxJ2og5K0D2K/+LTNH0IHsTkXkaduhJ98eD6+nlrZcf/izP9O+hxATQzZabsQnwuv3jwDv0R9+mRs9fuPE4/Az2tWYyvasQWHMi+y//152BT2vJL4+ezt8HH4r1s4s72BOxVr8A11zcQu+OZTGPfgbakTHIu9fxmZZB1HvUYt93X0kjG+IG8efDl/bsAmfYI/xY8Mvh8/cjc+/BTu/97MnJtB/6fxHT8jZsZfdMCn54hxt0VOZy9BDvDDT+1G/oj/f+B3yOlX2EfqaX9oINfAn/zzfmwnPvpUYscPfsb/IyPP4P8H1XEncjvs9GLubGMjPsLXX/4EdRjwfvsy86Bvj9wD/hPQ7U1k8TVilHuRG9Y96mHWnsPXbEu+/gZ+6u/cYX6OUGgl+6bfwdiPqfiD3Hzs6kvkRLvhk7Hj89+hPlRA/ojhurFRI9D/P6Dv44dibw9CJ8hzLyc+6P8B88HrR7DFlzyGy9kPvVgNf/AtmxIzbzmEGBw5v2UENiqLL0Mvm6k3LsOmzYVf47HFiw/CXw0nNu3G7kGPaTF8Azrb9TT5423EB3/DxqFnm+M3R+WIIX9OvAE/sxdjY3dA1lZBQ2qBhae4c/0qceRRxDAfE1PjLz+aC3+QfxGPbnw7tpa8dXv2tcXz8J447bMlxAvMH1uAf/+QWsI95J6vE3M/Txv2tooa0YvXoksL2Qc+5rhG/M7nxGXkO4OaiNe/IEc4AZu/NWcHyEX6NGgG7NPp0HguMk4M+jhxRf2m1FZY9yx0/Ml6fPcxxMVHI2PI7mril7MWcZcc/3UJsjtoHHr6OXkeucX8OuwL9D8Ifpw6D59xapBDvTwMXd0Ef8V8Mw6jTxoZ7MTPIiv/uoq6HrZ/y4cm9cGsUhjDXsCzC/+2Uezavl9/vVEMH4A/ET873iX+IAN9sEd3x/jBZvA0S1/8GdWWzLJkriWfzDXkkvlkuhBbQzvcidrrMoUQ9D4war0KVpNOtBVSS5Mx0d5Ptc9JLE9193QzltEO/tJEV6o9tmZGbNNBGxO6FuTa4y1N1Y3xisrmmnk1zYfEGxqrm6rrKqt5X1XF/L1KAA86KLbmumgfzQ3xyora2ukVlbPBqKlvFKizambOYm3sxw+vq2+cU1Eb7suPU1s/X+7DD6+pm1dRW1O1TpzK+pa65tja99dMj/bNL7FvH3qway9I7PlWuWesWf30eP30g6srm+N11c3xxormaqaqa26sr41X11VMr61mzmBv68SdU7EgPr2irmp+TVU=
*/