//
// Copyright 2009 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_JPEG_DETAIL_IS_ALLOWED_HPP
#define BOOST_GIL_EXTENSION_IO_JPEG_DETAIL_IS_ALLOWED_HPP

#include <boost/gil/extension/io/jpeg/tags.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

template< typename View >
bool is_allowed( const image_read_info< jpeg_tag >& info
               , std::true_type   // is read_and_no_convert
               )
{
    if( info._color_space == JCS_YCbCr )
    {
        // We read JCS_YCbCr files as rgb.
        return ( is_read_supported< typename View::value_type
                                  , jpeg_tag
                                  >::_color_space == JCS_RGB );
    }

    return ( is_read_supported< typename View::value_type
                              , jpeg_tag
                              >::_color_space == info._color_space );
}

template< typename View >
bool is_allowed( const image_read_info< jpeg_tag >& /* info */
               , std::false_type  // is read_and_convert
               )
{
    return true;
}

} // namespace detail
} // namespace gil
} // namespace boost

#endif

/* is_allowed.hpp
yPFPyzp4DFnmtQ0eQ+n+sGhz57q/Wedx1wn1xvQkXdb5t6q2PVX1N29DvAyfGPLj6/FwtaIHXSedd+PXsLwoP/pkO25XOEFjYYfCCRrHOhUvehxbJ2mU2NPsVjT0ONaj4vX7NH0qPqR4iKp4PQ4OqHg9fm1U8Xr82qTi9fh1jIrX49U7VLwer45V8Xq82qxkHDRebVE06pQMh2h8yQtd/4hYN3xQ/F6g3h1MIq2BxdQ5yXGAe/PJh2WZkDbFOs9hxq1RcenZvBYAndJrgROAR+0SNCYeC3Miz8uV3WRBxDlq7r2DZLVztlifE56j1iO7CfdEhbsL4ZPw8TwauCdTeL7gwcMHDtNe5dmuiviFiD9NzZNO9/ozYW/Edxum++vjXaK8Cyju3Do37mwvH4oD3FfGc714ogs4pXfjzxfxh5j1gXqz4ELESzvxvFirAAZ62uZ6irNX6PwjgP004A2LS4juI9qWiNK8VdnuvFfweYaw1QFtG3+ZGmPqBb1ewBaodvt+Qe+igPckPkC68daQ2m9Q+v8hKf+AfD6MeFmXd4VK2IuUuYdiePrYbD1fCprP4V1syjsnxl1OQ2U+s07OB3DnldJUazlS2TOkf28lud9AcvpoAE/XAHYjPsnTpwl/rrT75z5B2tZgDwKwZePbaZh9LhYVQ2gv8/PE03z2ISDsLtjeAKIV9wlvni3PVaV5xBh7iXHsSAyK2uiUIPl+4+xx7ue+jPtFt4OevCd/my2PyVe8i27D7qVkA7sDOCF6Z+kQOjf5opBD2JZHFsSWIPi97GBc18YWNGVbuo104yu0XrmTdOMuhfcV1YbuJrx7pM4R3lSj4/oNScK/t0gXvAi/x6r//6alo+xNica3AnAzjnovknC/G8BfdQB/DxL+9wj/yyVsAb6K+FpnEHvGxf3hr9m6M4e7DofDsCPGsXJ6l1PEmefBbLXTnU3AFzqpdHwohsfVXdi3AWs2d94ybvgBhJc7yVwMW8NbsP3swVY7+XQsWXyr4PuAdVparn3yqyCIh4QO9ZXZJpZNaPMW0A6pHn8odZ/at5Tfj6z8kCLnCNsihGPuswvemeHDUvfL6GtIF3An1dUHqQuPuGO38YPP+vZTpd8/U/r9c29MoTjAhS9EvLsJmL73ofcLf0n5fl7o+a8oX4P369lsR1yiHWdzbKeAn179yL2ZI1UbeULMBfNiP7BOzQWfFPx7vOv5wR+oTfyWeJb5PqVk/CemJ/JU9J5WOIADT729KXFKvHf0nBrvtQz+pmQAnEAZ/F3VYZAMXlB56XL/U9EIKvdLs3mPhMtTcILmC9VORSPTY1zIwUdvSqNbL6cG3AHSsqgR9ECHyynp1QKHzvctjiPs+kxZasX7NpdPt+01Ds+nzkpqq69qlG2V3r6JwddmfJunvRoofblgryjYl8s00C11v0b1YgyQ43q/sJ3er5F87SDPWlC4ZXrxTuTH8V2Hb3/ghBr1+rvWmU7yrnNpsG51zuR1k6rHKmdmY6k2HUumceRnuXZ/Mr8Niv6sRvcNl1W0r8BrG9API47wME6WxmtsZP0FPeAo/Wjy4omOjj+gUc3Jp/v3hvU6+bWE/0l1jhNS4Tp1TvNhFX+lCl9V4iwF6Xz5v77RH3+lij9UxV+l4t+o4j+p4t+s4m9RezGLVPyNKv1iFf8ZFb9UxYdU/GEk3zohb28MW6XuiqxAnNwb3cHrCg7LtTnvZS+kdcVKSt8bYnpyT5/7L7mP0kppCk5wHvrcrl3ol+SxToVXiTWqx8OqEvuUXY0Cp8Se2hFCzsABvl+u6yVfVHbmQ+4riz1aOQ4sDtgLjDb6cd4cgDPQWOJ+5CT6VeunlPoSWcajGtU=
*/