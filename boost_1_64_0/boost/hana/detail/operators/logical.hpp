/*!
@file
Defines logical operators.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_OPERATORS_LOGICAL_HPP
#define BOOST_HANA_DETAIL_OPERATORS_LOGICAL_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/fwd/and.hpp>
#include <boost/hana/fwd/not.hpp>
#include <boost/hana/fwd/or.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Tag>
    struct logical_operators {
        static constexpr bool value = false;
    };

    namespace operators {
        template <typename X, typename Y, typename = typename std::enable_if<
            detail::logical_operators<typename hana::tag_of<X>::type>::value ||
            detail::logical_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator||(X&& x, Y&& y)
        { return hana::or_(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename Y, typename = typename std::enable_if<
            detail::logical_operators<typename hana::tag_of<X>::type>::value ||
            detail::logical_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator&&(X&& x, Y&& y)
        { return hana::and_(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename = typename std::enable_if<
            detail::logical_operators<typename hana::tag_of<X>::type>::value
        >::type>
        constexpr auto operator!(X&& x)
        { return hana::not_(static_cast<X&&>(x)); }
    } // end namespace operators
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_OPERATORS_LOGICAL_HPP

/* logical.hpp
v1zr/eU9YGoXpM8FwHymBlaWwIQtTAMyTcpVYWEmU/rLdTg2fnVCI6XnqhS+jeVdYG2PUBWwR6jOY4+wNo89wjrSAGnoAy1svbvva4HeLkbbKD18ChulDXlslI7NY9uwMWDbcFzAtuH4PLYNj8hj2/BIZc/0qIAtzqaA3dKj89gtbVZ2S1vy2C3VBOyWThAwbTd0ooyjWYuLO0nGdSe6663K5unkgM3TKcq+6dQp7JtOm4Z902OU3dLpyp7sscqebJuySXsc2xVTzNM8w8FiVSQUW1D3tcC3heMRtd42akdTK8dRnbKLqnf2Sz1J3zdIW6nOTKaBuBl1763R2pPt2sXwdsHjDNTAdlge3eVsVpqUrcmZeWyidk5hg9KcxwalJWCD0qpssNoCtlbtAVurxytbqw5la9WpbK26ArZW3QFbqx5la7UrDpuHkTKel+6286oha9TUTdaX+xOUzeAT89gJPUnBs41QgTbbNE/2vLsmpvkUx+9rbPxT89gzZZU909M4Prras0DEuGH79+axR9oTskc6akNw1IZg+VEbsaM2YkdtxP5fbcSMbc2bKF89f830bGukXcZuvJ+Y543pgQMjg7lsQG0WjKGc6Jk8y8r3yfDvnrQuHJdPIMNO9OAjveP7fRj4I8OjiE903hNjcXZS7x2/f5m+q1st7urWURd+oTgXb6QNib21IixJNJhn8yc6XwxRQxN2SbVPsNsn6Hlqzfk0k8VLHuYEuB3n1c72TH1TY5Pfx806bBqMv+0dmdhyiGlmHzYNJnGmoxn7Zfgweuhp7LYRhWxusKOZNOY8FBqYOiEakCMcjgjGcH0m2w1aJ9REPRi3hRy3F605bAvbkXwYJDO2z0yNM4hIMCSMQoGyE+sjOWB7VBJhBOSGMJidK4F7vWzluVK2Mg07pMO82S6NTGICwRjOp4vXTOsdeKkEFzRVDGleQpp72VbPj+tnMh6Ly2RgL4hlTi6hmJto01y/eYLFwJz9TX9ub+/E4HhW2OF4WGusR52LdrxUzsVpyMZ6WL611N9n9/YeGBg8L87jYyWxN/MsoCO9/Vti2NIIZbaw3sGBfd6u4OPALfG4NZHzEfEiUZ4LIyPz5n354dHefWxGBYzLFXwn9SGkN7zxMsoOLwRvPIv1tDL/fXsheR/Pje7t7WO7G9wiA983OjwxYmGfMb6CDWzvAQxlwJj+RQYG1dnYaF/cJi9B2ssNbGxwwPBc1xeXi7qXzIoJQzI6iHzjcktAXGbtv6xayXBfRrn/yzm2XN9VK5uZCdNHCJubhC6+BGMF803we4SB4NJcAJrV9CXRyPK/Qo6lI1irtk7Zh+iBrTa5AHh57ZWs47pp3JXcRjuWV8n2Jg/pHRwZEnxEA+P88tgR1re1Z3B6jdO5QIx/WXrOoNicNYhz8NkWHi+ybtwUEHdw+Byj94nhf1+Celi4aQOPW2ZhY33DI9ASW37xmjUKDrO0CeiDt3Idfq2o/+pptPMfUnOiB6wJXcc6XBeXq314eNC29waES6L6wVzv0MTI9mSOfAnwshS8vneoLzdY3zs4uAfs0Y2vOYVmfHVgvjUMuj3Gl5eYcVXbNz4w2TuOrOuHMSfPte31dcRtjhoHhsBlzrexpGjzvQnxp0QTMe7ckghyKBffbu/anpfM1zOizoHzc2bdmhvb3F4t2mlHlMXxv5623xC69zR1YCPXc0LcZHni0HrCFiLoC+IaztU32HGM33NL15l+Qd3d74LV2FuyD94Ul+mJw0PkM2+Ow825ydxgJPqod3Ai5+3f3iLqUTDFeA2+R3SE9TZ1eqtbL0Pz7gjuI1MvBVuPpB0/xTca3uH0VtQL6/fQ3wUY9c/en4Q=
*/