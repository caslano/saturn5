/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_VALUE_AT_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_VALUE_AT_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/remove_extent.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct value_at_impl;

    template <>
    struct value_at_impl<po_array_tag>
    {
        template <typename Seq, typename N>
        struct apply
          : remove_extent<Seq>
        {};
    };
}}}

#endif

/* value_at_impl.hpp
zChTmcpUpjKVqUxlKlOZylSmMpWpTGUqU5nKVKYylalMZSpTmcpUpjKVqUxlKlOZylSmMpWpTGUqU5nKVKYylalMZSpTmcpUpjKVqUxlKlOZylSmMpWpTGUqU5nKVKYylalMZSpTmcpUpjKVqUxlKlOZylSmMpWpTGUqU5nKVKYy/a/T4uuu2JpXlhUul+ZyWS6X47KPyxW4XIXL1bmscrkulxtimU999rNWXw3bOwTLyqMrYX8vYvkTl52XsJz7MpatV5jv0JWLZffQVYrl5AD0GW5nnp9h75XunmeeJWaXja3g75vkFvkt8lXkIfLj5IPIr5E/JnfJdfI8W4MPIS9MPpS8Cvkwcj/5M/II+XDy2eQj1D/yfeS55FfI0+QG+QfyveSfyPeQK9uAR8lVcpO8F3mMPEE+hjxJniBPkY8lf0o+Tv0hH6/1NQd8P3lZ8hR5Q/IJ5Br5Aa0v8oPanuSH1D/yw+of+TttT/Ij6h/5RG2/AfCj6h/5Ma0v8knkOeS71D/yV+oP+WRtP/Lj2n7kr7X+yE9o+5Fb6s+24C+1vsinkAfJp2r9kN9Wf8hPqj/kp9Qf8qfqD/l79Yd8mvqzHfhzrR/yGdp+5DO1P5G/UH/IT5Pb5He0/cjvkjvkjrYf+Rxtv+3B56p/5Ge0vsjnafuRz9f2I7+s9Ue+QMcj+Vn1j3yh9i/yezpfkC/S+iO/r/7tAP5A/SN/qOORPElukJ/T+iNfrP6QL1V/yJdpfZEv1/raETyt8xX5Cm0/8kfav8hvaP2Qr9T2I1+l8yn5Gm0/8vM6H+0E/kb7D/lanS/JXfWHfJ36Q35R/SHfqO1F/kTrh9zW/k2+iTxDvlnbpwa+Rf0jv6r+kF/Q/k2+Vedz8h26f/JLun/yt7p/8mvaPjuD52r7gNPUvyDqdyPaB8E/KDfA82ys6y+G8ik3FsP2lSvgOcotrL+XchvcUJ4Gt5Q74LbyFHjKbW8x9E/lLuyfKk8uCf+VZ2D/ye1vcdTPJro+y6PcWgLlUe5jecCSlkT/cfaF0H7KlSUxvpT7YZ+rXAM/7va/OMqjPLPYEoXs/JH8s7LyJHjhTdUfrN+nXAFvqDwIrilXwSPK00ug/pUbi6P/K9cWR/0rtxeCv2AxgLtuf0ugvpU7i2O89isvAX/JUhKMD7D8WAzj1/GS8F95ENxQbi+G+lauYHtzlfuXhL/KfbB3nR08z2ZaXnCfchW8ofLkEujPyoOwjyg3wJPK7SVQf2592F9TriyB/qvctwT6L1gSeJ7N1d/FUJ/KtSXhr3JnMfgLFgPb363P9nf2JdH+bnsLwn/ladancnUR9F/lQXBHeWZx+K/chn2eLbS/gJdV7nK8KVeXgP/KlUXhv3JtMfjv8sM+ody/KPx3+cFt5cFF4b/bP/g1Z+f4U27APuN4SYy/LbV8i8N/5Qb9V55if1Fusf8q9y+B+V65tgT8VZ5h/1GeXBD+giUthP7j7Iui/p1/i8LfrdSfxVH/yl20R9XZkX+Ocgc8WHCZyvTvTK8daP03x7+3b7em5yvW63telp4++QK4Tb3zotktid5j/f4Xf9/6v5Vqb2G9aS773sZy8mUs+8lTr+a2L/bXaOey8jqXb2BZJU+/+ef8a7/D8kXLVgfLGeUPZJk/X12naIfTdL4ETyoPgucqN8CPg2VFcAcsK4J/ACdpeJ55xC7pdNgPIi9LrpM3JB9MnnP6X5sv+3Zds1f5+4p6vNGdfxQ8pVyDfVp5EvYOWNIiBXeVq7DPKLfBC7dd/QlLeZVb4FWEkR+8ofIguKY8BR5xjO1PuO2Dzxbm+W3BVylPY/25yh3w48pd5H/NbV94Vnbrg2fc+gVL4KY=
*/