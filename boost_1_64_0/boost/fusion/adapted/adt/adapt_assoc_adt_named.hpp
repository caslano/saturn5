/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ADT_ADAPT_ASSOC_ADT_NAMED_HPP
#define BOOST_FUSION_ADAPTED_ADT_ADAPT_ASSOC_ADT_NAMED_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/adt/adapt_assoc_adt.hpp>
#include <boost/fusion/adapted/struct/detail/proxy_type.hpp>

#define BOOST_FUSION_ADAPT_ASSOC_ADT_NAMED_NS(                                  \
    WRAPPED_TYPE, NAMESPACE_SEQ, NAME, ATTRIBUTES)                              \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_DEFINE_PROXY_TYPE_IMPL(                           \
        WRAPPED_TYPE,(0)NAMESPACE_SEQ,NAME)                                     \
                                                                                \
    BOOST_FUSION_ADAPT_ASSOC_ADT_AS_VIEW(                                       \
        BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION((0)NAMESPACE_SEQ)NAME,  \
        ATTRIBUTES)

#define BOOST_FUSION_ADAPT_ASSOC_ADT_NAMED(WRAPPED_TYPE, NAME, ATTRIBUTES)      \
    BOOST_FUSION_ADAPT_ASSOC_ADT_NAMED_NS(                                      \
        WRAPPED_TYPE,(boost)(fusion)(adapted),NAME,ATTRIBUTES)

#endif

/* adapt_assoc_adt_named.hpp
Zv4W/lb+Nv52/g7+Tv4u/m7+Hv5e/j7+fv4B/kH+If5h/hH+Uf4x/nH+Cf5J/in+af4Z/ln+Of55/gX+Rf4l/mX+Ff5V/jX+df4N/k3+Lf5t/h3+Xf49/n3+A/5D/iP+Y/4T/lP+M/5z/gv+S/4r/mv+G/5b/jv+e/4H/kf+J/5n/hf+V/43/nf+D/5P/i/+b/4f/l885rmQuLC4iLiouJi4uLiEuKS4lMgEE1wIIUUuLi0uIy4rLicuL64griiuJK4sriKuKq4mri6uIa4priWuLa4jriuuJ64vbiBuKG4kbixuIm4qbiZuLm4hbiluJbaJSTEltosdYqfYJc4Qu8WZ4tbiNuK24nbi9uIO4o5iWuwRM2JWzIm9Yp/YL+bFncRZ4oA4KBbEolgSZ4tlsSJWxSFxWJwjjoij4s7iLuKu4m7i7qIm7iHqYk00RFO0xLrYEMdEW5wrjouO2BRd0RN9cZ4YCCWGYiROiJPilDgtzhf3FPcS9xb3EfcV9xP3Fw8QDxQPEg8WDxEPFQ8TDxePEI8UjxKPFo8RjxWPE48XTxBPFE8STxZPEU8VTxNPF88QzxTPEs8WzxHPFc8TzxcvEC8ULxIvFi8RLxUvEy8XrxCvFK8SrxavEa8VrxOvF28QbxRvEm8WbxFvFW8TbxfvEO8U7xLvFu8R7xXvE+8XHxAfFB8SHxYfER8VHxMfF58QnxSfEp8WnxGfFZ8TnxdfEF8UXxJfFl8RXxVfE18X3xDfFN8S3xbfEd8V3xPfFz8QPxQ/Ej8WPxE/FT8TPxe/EL8UvxK/Fr8RvxW/E78XfxB/FH8SfxZ/EX8VfxN/F/8Q/xT/Ev8W/xH/xUO+C8kLy4vIi8qLyYvLS8hLykvJTDLJpZBS5vLS8jLysvJy8vLyCvKK8kryyvIq8qryavLq8hrymvJa8tryOvK68nry+vIG8obyRvLG8ibypvJm8ubyFvKW8lZym5yUU3K73CF3yl3yDLlbnilvLW8jbytvJ28v7yDvKKflHjkjZ+Wc3Cv3yf1yXt5JniUPyINyQS7KJXm2XJYrclUekoflOfKIPCrvLO8i7yrvJu8ua/Iesi7XZEM2ZUuuyw15TLblufK47MhN2ZU92ZfnyYFUcihH8oQ8KU/J0/J8eU95L3lveR95X3k/eX/5APlA+SD5YPkQ+VD5MPlw+Qj5SPko+Wj5GPlY+Tj5ePkE+UT5JPlk+RT5VPk0+XT5DPlM+Sz5bPkc+Vz5PPl8+QL5Qvki+WL5EvlS+TL5cvkK+Ur5Kvlq+Rr5Wvk6+Xr5BvlG+Sb5ZvkW+Vb5Nvl2+Q75Tvku+W75Hvle+T75fvkB+UH5Iflh+RH5Ufkx+XH5CflJ+Sn5afkZ+Vn5Ofl5+QX5Rfkl+WX5FflV+TX5dfkN+U35Lflt+R35Xfk9+X35A/lD+SP5Y/kT+VP5M/lz+Qv5S/kr+Wv5G/lb+Tv5e/kH+Uf5J/ln+Rf5V/k3+Xf5D/lP+S/5b/kf+V884r1QfuH8IvlF84vlF88vkV8yv1Se5SznuchlnueXzi+TXza/XH75/Ar5FfMr5VfOr5JfNb9afvX8Gvk182vl186vk183v15+/fwG+Q3zG+U3zm+S3zS/WX7z/Bb5LfNb5dvyyXwq357vyHfmu/Iz8t35mfmt89vkt81vl98+v0N+x3w635PP5LP5XL4335fvz+fzO+Vn5Qfyg/lCvpgv5Wfny/lKvpofyg/n5+RH8qP5nfO75HfN75bfPa/l98jr+VreyJt5K1/PN/JjeTs/Nz+ed/LNvJv38n5+Xj7IVT7MR/mJ/GR+Kj+dn5/fM79Xfu/8Pvl98/vl988fkD8wf1D+4Pwh+UPzh+U=
*/