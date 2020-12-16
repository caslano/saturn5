// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ARITHMETIC_DETERMINANT_HPP
#define BOOST_GEOMETRY_ARITHMETIC_DETERMINANT_HPP


#include <cstddef>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/geometries/concepts/point_concept.hpp>
#include <boost/geometry/util/select_coordinate_type.hpp>

#include <boost/numeric/conversion/cast.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename ReturnType, typename U, typename V>
class calculate_determinant
{
    template <typename T>
    static inline ReturnType rt(T const& v)
    {
        return boost::numeric_cast<ReturnType>(v);
    }

public :

    static inline ReturnType apply(U const& ux, U const& uy
                                 , V const& vx, V const& vy)
    {
        return rt(ux) * rt(vy) - rt(uy) * rt(vx);
    }
};

template <typename ReturnType, typename U, typename V>
inline ReturnType determinant(U const& ux, U const& uy
                            , V const& vx, V const& vy)
{
    return calculate_determinant
        <
            ReturnType, U, V
        >::apply(ux, uy, vx, vy);
}


template <typename ReturnType, typename U, typename V>
inline ReturnType determinant(U const& u, V const& v)
{
    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<U>) );
    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<V>) );

    return calculate_determinant
        <
            ReturnType,
            typename geometry::coordinate_type<U>::type,
            typename geometry::coordinate_type<V>::type
        >::apply(get<0>(u), get<1>(u), get<0>(v), get<1>(v));
}

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ARITHMETIC_DETERMINANT_HPP

/* determinant.hpp
6o8a/nRQrDiUPJTsNj6nRAzUJUrkjyFB0XBsrD/e+qTdOkWv/cRr5V9Y/R3NfpM5QCSFhCQuecP3mazA2l8L5ddZp/k6R32DUBgDV5Vx4+GvBI83+jZCeDu9msY/cYKiyJxPbF+y2ZfKn0pCUvjcHVr8VL0InITnOz/A79jr6o+IXxdsHP2R8J+7cKbQ/h4Ua5VojC26yiEaY0fAosZYRRhWYyPaiQ5iHDE+pJ4VMgvbII4Tfyn4646/M/HXH39D8Gex2uL/X4zdEffc1228ioLSBeazvjLIj+bK6cbRXDeVwLLj0Cb7oix/L7DlcdEkahQ8VRZNu6uXT/XwdbfqWyS+aKefLrJa4CErKb7/Rb879Pt2/W7T70+H3k9OgxL1YWghvb96Qi8nRbpaoUwHaOaaLyAN2l+EwFgoJ6qwDTc7XiSrBi4zZcV/ztifHgyiLbqyl7yQ8Zc4zFUUD/lFG9F/0Ox1GetfGAFn0V2fIVP+EsxFoE+S8G8t1OHrQWcQz/A9XMaStxbDGWMj9WO1A5sZe0Ru5ZjQ+ksGPuQknMOvNNBp+Xd/YMnNjy5GoURy6IfQhsPxKtuxxddRFSW+bI8irR+A0W6Lgw+tjFcXy1WZSvYSlWzmh6JPREjcmzi91OmVbhE1XEsVTpEyLZSKne6tLkvi2twTeDHoHXyQ0nfC/AzC87cuCfOE3G5tUwcCF8lu2et8onNm7ayVI7tk+Ns6n/DGW7PGW33tyNCX01BmNg8WdRvVEz6j3HtX5SXWwurzv5Sltaf6Ekx/W12V8WYwVW4DNiVzPVwNMg/7Vk/Oc2UG18BePdtLZpF341mpADk4/M5X3IqdyPpVUzK3f1yd1YigeWO/sOA3FWDGPS2zFuu0paBIKsA43Buzih6Hd0vDPfz4Q1Qo7ERP8SC8TMlu+07fqzIlT3hUTclbOCVfhkNlmZLXY0o2XpH5GO1VzcdbH8Jm/IHnTsaQHluvvy/4fTQdr8cAy29bL1QziIhxCEBsKWPcedNMa5gBqckW4h8KbNQ3DXL3kmeN0KM2ki9BJCkOcC4daBWKVKHixHsar1lELroihUkSzzCPEqUiRtoX3dK4IXvXEiGpNJBs6MZH9C2FbnzUT2ieJ7JRScyHtCon6H7FL0vktOYHNJ8rOlfRNWE6siryHxk7qZV/PBykb4sc8IA4wRJSYmnfQyiZWej/rolIA3/V/AlO+3Vg+YI93FVPSQwZKsLMTTwjysX4Je+ZtYozLcodPxd6+UpDyL9koun1+z/G9hFmRTwgWoQks3I2sQlE7Oj9K3fKFbHcKm2zhC/TvYomm4PLWjqX77LBOUqt2WT02Ipd6pozokNo6U8Z2tAf5t4F8mGC8ZHr+R95pA2AjQk1XwFf+QpFrrWWBJFpdWHLy6jIW2CtvFn8neU25jAOANlz5SL8NnvLKziaw9kDhJWwme/4bgmia+grsg2csMH3aDn03Pa7yCHmbmFpfX1CWB1qJ5asxQgjd1QPXqh3uL4UFqi1MHdeGN7yTlHCdzt152j+MCZV0ZedPS1LPNPkI04RFlpn/g5zTHvsL02EminXwrfw09/C9ci+3B5ceyzA7jbNXyC1fCZ2tglrT5e9aZtRqf5ha7vbyVJXqlnquoNlrcSq1AfmJMpyvh6PySLPdzeA8+7AwCGbv3fFF5KKP8H0esnUM95LElD95U00NdEIh0xHSvp1f6fo7yX6vLT+2yhKFTXm7vitPvP4uVQTlHbNWE/1ydDQAJWgELyPSdn4swtZBr/LPyrek0oMBHGxf5fFgodD/qGFxoh0d83Vs5TBSaxnMKT2N6W59zVJF60LOpSO2vMg6645yVt9rXVC9YgnL6w=
*/