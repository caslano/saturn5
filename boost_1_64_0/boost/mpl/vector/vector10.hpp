
#ifndef BOOST_MPL_VECTOR_VECTOR10_HPP_INCLUDED
#define BOOST_MPL_VECTOR_VECTOR10_HPP_INCLUDED

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

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/vector/vector0.hpp>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER vector10.hpp
#   include <boost/mpl/vector/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/aux_/config/typeof.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   include <boost/preprocessor/iterate.hpp>

namespace boost { namespace mpl {

#   define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, 10, <boost/mpl/vector/aux_/numbered.hpp>))
#   include BOOST_PP_ITERATE()

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

#endif // BOOST_MPL_VECTOR_VECTOR10_HPP_INCLUDED

/* vector10.hpp
0ivi0ZuNu/g9xKSHlftH5IcL1V+9+XuwzvBm9Pca9eBy72sK8tbfjgXje1sc3D3ML2noI969Rp5D/bNkpfFS7UH65a7XPcpxvXqSc0T/fgd7rNF495SkhGT25ZJQ/6yK9HxP/UHtX/dn5ZfEF/2ulTe8Tv5mOP2wj8Ynj8oLPqY80R7v8/sNjGeWeDHKt0WvMI8/+D3grFBPdNJO1nr//TL1aL75AsXIFePZo/7NMg50p/hzZ9x8SvWf9ygt+Y9684B6YbB5/fD1jJvnGede+YGWbeQr1QeU7HeV6zMvNcxzmicfMdn87Sx5kl7i8rfUV6PNS9zueVBfx8gj5n3P66FzHcf34s87tR8jxZ83Gj+7Xj+xMKzvdK96Q14vtkgcEeTftKDdNOXrr/JXHZLMR5CXud/4xhxK7h/1e0T1SeEe9VlLedefyT+bj1uZo/8jzi1PVI8vMS4gT1R/l/En+uP5I/KUH5jPt1A/qbf29nn3m7go7ZE/zfMD1FdvUk98Tn/tuDzhm5Tk2xsv4jtrSvQl88cfZfyXqney5J3w2+n3w0h+bH+C5+g189076H+c2iJcv6Heg7BZHDxL/DBNfJct/rxX3CJ/XfOC/sUE7wsRfxUM8v/sN+P7o/r7sHr4YvNKf9IfHIheC8YV3R/8B+ODZ2mnxsmvzEqVt3K+5iGWvi4eAidTP9d7c94zHqJdytnguaWknVr307KHeZZVlhXy3cXKfRm8Eu1WKm/yF/2C8SYwfuIO1H9rXoR8wlcvqleNu+Rpdw8Oc33vVF7u1X7drf45LYrDypdc7e9e/EMe6c3wu+L0Fknec6X//qb6slZc8Y36bb77ule7PFd/GP1C/RjtQi/qya+RZx7rusxSnrVjfbFv9Kf9zXmVevIoqOc+K/nZIeKvz+W5eokDzKssSdBOFYpXgvjDqljw3Fn6o2OUJ+53YzzGhxv1vxvMZ246oR2Ez2Je8Di87/dojXeZTwWepD//ntbe9T1V3q2r+mqbOMB9n1qt3PWhBG9Yur6V8l+xLHH+Tvt7Qbt/qvz6ZNdlq/Inf5jzhXbMdvpViWM+97wRN2SfnpQv3i8OuoB+kEvrg3z2OP19YDzT+0mz5hg/1O7lDZE3UE62dNNv/lKcrR3tftz40FRxxDnaFfVa0ZvK9Q7jFVfgN/HdqPt+gefhLcqgnvgK9TP1s64I+z3c3vVvbzxmgziDfB7eT9UPxJ4wvyTH22h+jnqpLMhDjvOe9rVstOsDHmSc8ODUa+dj+u3pVdqBFe7XAPVRYB870t4C4/7F8rRbzA+Vvz9kXnBOkfiVuAQl92LS3xTjq9rdgg7qt87KQ5L+Xrnfsw+S/xtPyXd/5jNE98X3dF3uj/JF9avIy+W9+frX2r+aj/3uqtnzfULcrV0cme65Fhe2P1c9dZ7xTPutbWl84O/yB9yzwHiHRL9npf1Bbmj3N8rpDMdfEdZ3r/a8DtKfOtP18F6QVfi3lOqjgiB/ux37FMU5xA2V4vp+VxuXju7r+6/3sPcVZ8pbjQ7ioG14Tz5jyafy3GNdf+eZ5/pmROuX7HlQXxSONd/rB+3LWPPG8fvptyQuvtO/on/mMd642HBx8Cuuu3Zlhn5WLueB56coRwEPlshzO8VH1eKCavmbVuqtOuNS7dyPmPGbOfZj2fiFfvfURPGYvIZx9din0T4pb3OV30Tvdfpa/8R9W3Yx/YMP9CvNW+k3Sj15I3qY7yzFY+vVr/Jwhbc5/uGOf57273p566mU+KviO/Pisxr046N7xuDF+fsG+Zwgr+iX8WBfvlHPqo8Py5M1bdQeyf/EPtGfJv+J8Q+TF7lZPuqQ95AwD9qRF0x503wNy+4=
*/