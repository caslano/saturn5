/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_SIZE_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_SIZE_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct size_impl;

    template <>
    struct size_impl<struct_tag>
    {
        template <typename Seq>
        struct apply
          : struct_size<typename remove_const<Seq>::type>
        {};
    };

    template <>
    struct size_impl<assoc_struct_tag>
      : size_impl<struct_tag>
    {};
}}}

#endif

/* size_impl.hpp
KHj1iZhSeJ/IZ1gk04B/thF+NewRTGmHOlmx0esY1pamsiSw8ZGjgpM07bxh1NkdiyJQcbYQkAer6mCsN1DXBhAleyqDViITyo40lyDgRJVV8fhaRSSQZkIGNaPgdiCdAhPmyjk7Qp0Uz5WMhTiX+5wmSyf4DS1kgfncWXo2CA4KnvjCfZ1QloEUvm20E9xVGnQQquweR0w4xwUFx5ORifvAvySmkIAsJVkSsG8Zd1kHjVCF6kANvUc011FD4quWGBK3t8SQLLUl4F203Z1yXy3GRYB6pPEWriPiLZwiFiUVxCvESniF6EQoq9UIIYrrt7KJTUiUnivizfU1zii2uWUHEbKIJjEJeFqTCJ9fnVAx9bBRNTolKnAhURp1unxtaoopcdRADOJcrHUhBhG6ru0RdJKzkmi1Tu+oIP8HXzCkMvGVkBkuJ4Hb15YIRa5WIiN47lUpOxFbNaAsEdmg/KMhBuUfFBwHZ9l8wMw5r0ipKjPR+3Em5AiC5Iize0OIusDK1fmTLHdcqvaJJXhyvvCXyXpEOcrI3KlKFqLJPYIxmZUApXKdQ52YQHIG76x1djuxOF0XZXRGQ3dFfSLmhrct0NNMBs2oQaiazDCiTAb42jOhXAhMSuUj/oxlhm/xpLE+HnOlE+ErFp2I
*/