/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_SET_FORWARD_CTOR_09162005_1115)
#define FUSION_SET_FORWARD_CTOR_09162005_1115

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

#define BOOST_PP_FILENAME_1 \
    <boost/fusion/container/set/detail/cpp03/set_forward_ctor.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_SET_SIZE)
#include BOOST_PP_ITERATE()

#endif
#else // defined(BOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////

#define N BOOST_PP_ITERATION()

    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
#if N == 1
    explicit
#endif
    set(BOOST_PP_ENUM_BINARY_PARAMS(
        N, typename detail::call_param<T, >::type arg))
        : data(BOOST_PP_ENUM_PARAMS(N, arg)) {}

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* set_forward_ctor.hpp
2Kbk06ba9czRT0TS8zk5Ds9Ler6IA7ACh+M6HIfrcRJuwKm4EYtxM96Hf8GHcQuW4ytYgVtxI76GB3EbHsLteAZfx7O4A321ejHWxZ0YgG9iO3wLI3AXdsfd2A/fwyH4Po7BPRiPHzjyFSG2u3q917+HOEr6a9yKftgZO2IX7IJdMQa74SnMIFTI+hbL+mrgWFlfH+lv0RdDsB9GYAwOxdtwJPbHfByAU3Ag3oO34wIcjFLuc4/OfbkfJPEPlviHSPxDJf5hsp4Ki9xvwwaSH+rx/ydlPXfL76N5GIAl8v17MQHnYzouxFm4CJ/CxfgMLsGXcCm+g8twNz6I+3A5fokP4y/4CJ7DFVhVuz5iLSzDOvi4Um8I7Oa+nG8u+99C9r+l7H8riX8bif8tmIP+eCcG4H3YFhdie1yCHZz9KuVeGXpLeqn931IlvdIkvdIxCjNwHE7AFMyW7eXgXZgr27PiGpyE5ZiHmzEfP8YC/BQL8ShOxp9wiqTbNLyA05V8YpX4djXJJyMlX8ZhSxwl+XM0RuIYZz8luSeFM02uC3+V+upn2AcPYC5+jvl4EAvxEE7DL3GvN/lJe2cx4VJ9i+hXpPYnUt4//J9/9/Cf/d5h83cOX533DevfNax/z7Dx/cLte1/5O4X/3fcJ00fkqrxHOLQzfSoIdxLKCDsJPxDqd+G9yoQCwpOE9whnCf5dWZ5QTKggfEKwdKP/BSGOUEKoIBwkNOrOe38JdxIqunv6XHgmz+SZPNP/4uRDSLvK7f9zkwu05v//dtv/NUrb/4HyrGISO9AcMzFdaw/byuwZITEItj27q1Q7/Bf8L9kOX9pi/7HNRpnFMcZvUqHj3XblzueBDByL7trkR6LrOa2xjZXtJVDG9h7G9vJF3I/Rv/tO2tOwZedz2OBWtvm5edkyhrShvUiCSXsRGVte1slwtdoapd1NsL+uHb3z+JyvImM6Sx+JSZjCMicD3D7DDc5Nrtzx6dGpcsfH13h8DPtf1/n+H/0xqzA5ZptNjpmkiRwzSU/D8ckwHB9pJ+d8RiztoozHy95OrxLHRvKOfD9/YqbVOA53YX5qiraw/Xitbu88Xro2EO9J2/jnqnC8cA0msszeQJPjZW+VyKmZl5rP2nUtICrZH2JM6KX7Q2jzSkzOsVJXG4h4/ivHWj1P5FibHK+BxnNMN7bzNJM+LUWm50iG7jiY9asp0PqFGI7hNNt431qBu7yq/R5y4xDXeN+9sYUtHqQIcmxsx2tssL7fyuPB+n4tP4bIZ0P7AvN2BFf/Obl5+4Kr347A/Dm5u/YCVz7esXk7C/fP7c3bX7hvR2De/uLK2xfMy9LmL5oz8ptPp1gX+QyvFdx7zgsXr7ydhe05qrdcT+U6e5b/dNPKdrRoyv3737Eteks7AR/silUxEa/BDKyGs7A6LsAa+BDWwvVYG/fh9XgI6+DPWBcbss16eDM2wNbYEAOxEQ7DG3EMNsFCbIbL0A93Yiv8GFvjL9gGL2IAVmdf26IftsN22B6DsRN2x0AcgkGYjMFYiCE4A0NxNobjaozAcozEHRiFx/BW/B674inshi2qcN7iLdgD22NPHIa9cBT2xnzsgw9hX1yJMbgab8OD2B8P4QD8EQfK8/1BWB+HY28cgX1xFN6OY3EMjsNUHI+ZGO+4v+gt12+5rpMfbP2QUqQuNlvyw1zJD3djMM7HWFyABXg/TsVSfAAfwFW4BMtxKb6Hy/BjfAiP48N4CldhXbb9KPbG1TgUn8QkfArn4Rqcj8/gg/gsPo/P4WZci9vwRXwPK/ATfAmP4To8i+uxBvu4AeviRmyIm7AfbsaBuAUz8BWci1vxVXwVd+BruBe34W8=
*/