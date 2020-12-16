/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ALGORITHM_ITERATION_ITER_FOLD_HPP
#define BOOST_FUSION_ALGORITHM_ITERATION_ITER_FOLD_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/iteration/iter_fold_fwd.hpp>
#include <boost/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/add_reference.hpp>

#define BOOST_FUSION_ITER_FOLD

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/algorithm/iteration/detail/preprocessed/iter_fold.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "detail/preprocessed/iter_fold.hpp")
#endif

/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#include <boost/fusion/algorithm/iteration/detail/fold.hpp>

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#undef BOOST_FUSION_ITER_FOLD

#endif

/* iter_fold.hpp
v9m7E7gqqj2A4xdBxaXEXdMUDQvXEFFxR8VERSVXLJVFUFCEG2Bh0ot8muYWLpmVFr00yCXJJU2trMy0rKjMzLTILK1naWVmpvZ+c+//LnNnhnvB7G3czzt9H+PcmXPOnDmz3LPot20tfVvSJEtb0j8qj71Sr39ByDfrHy4ODP/q+ZLbjOaYpM2GtOXYTrhOzkc+lrGy62M2tse/YT7OxBu9iDu2xzk4GB/COJyHM3E+7sKHcS/m4glcgldwqXMb0gccbTC3u7QN7WhfT9pJoK+sZ9R2tUi217SE7Z3yknYK0n5BWa+rjLOsfMYx5nAtHI+NMAYDMBbbYCKG40QcglPQjFNxGabJ3CbTcD3OwGOYjb/ifViXff0Nu+MDGIUzcRLOwXW4AA/iIvwUl+JpXIZ+xHk51sUnMR2fxuX4DD6Bz+EmXIcHcQNeweexuTf3MngLbsLOuBkH4RYchVtxEr6IybgdZ+BLmIu7cB2+gtvxVdyBr+E7uAc/xjfxB9yLF/AtvIz7sQL5/x42xCLshB/iEPwIp+BBnIUf44P4Ke7Dz7AIP8cj+AWewGI8hV+ivfzMNS5nnUyyHgvNst5mOS+aKetJufhDxgRnBcoFSLmoIOWispQLXykX10m5qIH3YB0swLr4OtbDr7A+8l3TDdgICcwZwL5xCt6EZmyF72Jb/BFvxfPYEasQ1054PXbG2tgdW2FPDMcwHIW90Yx98CHsi/OxPy7FgbgKB2E+RuI6HOyUn2cNz0fi53w+zjc+Hzs51qOwGx+fzs7r3WO832DnMewXyH7dbM9svF91m/IS0nuT03qFjv0abi+ChcWynp+UM+UZr7uUs20yp8UODMSdMgfNLpnL4hW8HV/F4fgaxuHrOAH3yJj0e3EmvoUP4T5cgfuxEN/GbfgO/ogHsApxeBcb4HvYFN+Xsd4/wF74Id6GH+EQPIhj8GOchIcwGT/BTDyMy/BTXI5HMB8/w+14FN/GY3gUv8DzWIwX8Ev8A0+gUs6/xmr4jeRngUl+85XfgrdLO6GVku+P8c/18Alsgiulrf4q7IFPSb7m4QD8B47GZ3AMrsFYzMc0LMA5+BwuwrUy3sU6GSt/vcw5tAEv40ZU6hby3DH3Q66jr8N2lzkcTsr15xQOx3+i9XvyGy4m6HxvRgXr97IxBh9A+R6/wxrvb7jsb4Tsb7R9f/I7Kj6v871n2X59zMfnsNCxP/n9E3W+F+Zt3V9vbI190Db3hlm+lynfc557YyDrWZ7PMAAj5fuDsTcOwX44FO/AKByPt2MaDkPp0yG/NVIXSHlx7tMxR9I1F7vhfByKC3AMLsQ4XIRJmItmXIwrcAnuwKW4B5fhQXwED+NyvICPYjX2vwKvw8fQHx/HAHwCb8aVGIirsC0+hcGYJ/ntX0F+Q7T+tkh6UKl3UPnsZ73G+Da2w3fwNnwPF+L7+B4WYW3lvMUmeFj2/yneikewPX6GXfAoDsVjOBM/x6fxC3wWv8RteBxvJS5fYQ88gePxG5yIJzEJv8Vs/B7n4w+4Ac/iVvwRt+HPeAAv4W94GWtQwK5gH/wDR6KJ452IXngMK+Bx9MFfsSKm+dCPGhdjZaxSkToea2EVvAGrYQTWQDPWxLlYC3OxNi7BOli1EtdzbIsNcA02xOfxBnwRG+M32ARrVOY6j4HYHIPwJgzGAFyLt+BGbIPHsS3+gu2wqS/nGD6K7fEN7IChVSjb2B1D0X5dfFr6bLm5385VrWd83S5WrWd8nQ36h/F6Ic5z78h6B3TO/++lr9UPGCNzltwrc5XMl7lKVuLP+KTMVbIJz+Nb+JsjPvL7FHnlJh92q9czvn9ZLeu5yYewEtYLcZr7JUc=
*/