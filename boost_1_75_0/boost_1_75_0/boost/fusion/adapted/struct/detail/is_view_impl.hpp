/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_IS_VIEW_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_IS_VIEW_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct is_view_impl;

    template<>
    struct is_view_impl<struct_tag>
    {
        template<typename Seq>
        struct apply
          : struct_is_view<typename remove_const<Seq>::type>
        {};
    };

    template <>
    struct is_view_impl<assoc_struct_tag>
      : is_view_impl<struct_tag>
    {};
}}}

#endif

/* is_view_impl.hpp
WkKbob/yUEqLE+dBaDOoMC1l3MlADMOuSN7EPLphczRKYF5tV2AokfJ8zMY9uIyUCfMZ2Oy7KPJP7gJPCMcNfe89vJuWXiiaGPaGCv2O7rNRirgpCvnceFoU4BVOKIwsaO3yDiwld5PKTfStHrP4ND7+HRsFajsh0nwQaR3q3U3PTFeygcpZkJuenTSfnbSObq6hZ3PNZ3Otk4gL6dkW89kW64DATs9mms9mWqc4p1rgsyrzWZV1vvILPTtsPjts+Q5vFc8QSLcNDT33NTvtLzdOPmoHZAPxUju0SRnelhkUrZ3ZLs1buQhCQ5z+2xOBwmtEPZaMF6R7oIKx6d41ixaHIq4WlHuCylUGl6uEcsuscoOpXEVwuQoot9wqdx2VM4LLGVBuiVWuLZWrDi5XDeWWWuVONCd7jlhz+xj/MSleo3goAIQI411p2IR1LlsQCqD1mzK8zRhtzptGeHZfN6d3f2DsR0OBwaNMJ9711lsX3kRvlTZHXPYJ0yZcZQJe/kgU4q+Mh5AAqDbdd5NN9BWgDc3tQy8OVvnez3xfBXx70yNNiLyoAN4XBvO+uS8Ra3Vu3jMjrddGpNNrP0cK+wIJBsW8A/V0Oo6HmGgwDTINHod4O8phlNmO466Y5WpmuQc2dVo9Tb0QxM2q9GLm9fHIhnmFd+mtTOXNr7iH0iKxdU6ek9XY/5nVxQGseriP9kY0ziq9lXnSerMF
*/