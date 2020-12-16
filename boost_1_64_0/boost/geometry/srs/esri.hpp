// Boost.Geometry

// Copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_ESRI_HPP
#define BOOST_GEOMETRY_SRS_ESRI_HPP


#include <boost/geometry/srs/projection.hpp>
#include <boost/geometry/srs/projections/esri.hpp>
#include <boost/geometry/srs/projections/esri_params.hpp>
#include <boost/geometry/srs/projections/esri_traits.hpp>


namespace boost { namespace geometry
{
    
namespace projections
{

template <>
struct dynamic_parameters<srs::esri>
{
    static const bool is_specialized = true;
    static inline srs::dpar::parameters<> apply(srs::esri const& params)
    {
        return projections::detail::esri_to_parameters(params.code);
    }
};


template <int Code, typename CT>
class proj_wrapper<srs::static_esri<Code>, CT>
    : public proj_wrapper
        <
            typename projections::detail::esri_traits<Code>::parameters_type,
            CT
        >
{
    typedef projections::detail::esri_traits<Code> esri_traits;

    typedef proj_wrapper
        <
            typename esri_traits::parameters_type,
            CT
        > base_t;

public:
    proj_wrapper()
        : base_t(esri_traits::parameters())
    {}

    explicit proj_wrapper(srs::static_esri<Code> const&)
        : base_t(esri_traits::parameters())
    {}
};


} // namespace projections


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_SRS_ESRI_HPP

/* esri.hpp
LLGLbT8xYbmAVZRmeaYJ82AXbtfLFbOwHsBiiGnPH1qNz0nBi/CJxALrXSmL7QWsPrE7fd5WxGvf0OL8iY3bliTfvQeDoGg3T/xsxjjB3IkNmVkmEZ9VAytB7NKnwSWxXKA11iG2fULbWtg+wWoSm+Qcm4L1ANaUWnT4cGwvYB7EptafVRPzBx3TiVjbqw3/wDID20qs+Y/t4zCdrZT3baUlL9r1NdaDn/K+lbRr670HYbmADSDWK3LINmxnrdX2k/ZsBpYZWDots4wn0zF/MMblIeZ94tXHGA6sPbFyW7aPxvJsC++LETvabjXu1aBUejGSv7B9qb0xne3gnXYSrulysQbbZwBcbSJW9eVhPV6fClCnc2SkfwcslwB1vd//7P4hLGvIwBtiFW/5F8I8QAxRJJ0XpqStx3CB8GQ4TWfzSqlYt2ALiG0Y8e0ZLDOwKcQ+K336PtZtJ3gnm1jixe5xWC4mGFuJDd72bFq2QR82yfaiVfpmrfSXNoMBC9ZI0qbf3GwdPyHqLnLs0Yl4OfaAeYGVlSbHELAwsIrS5BgClgxWX5rs72CZYC2kyT4NpoyW7tJknwYzgdWUZumbeDwwD2my/4FlgDlJs/Q/TAtYZWI+F5pusZlrVyhrYvFN61e1mQGsFrFvGrwegOXSVR3nopndi2E6u6rKU55zwNLBNhA7vve7Ixiumyotst7BUsHcpFnaIMbJWGbOBpdxcjYDY0bGwsA8NdI6Hh2zE9MCF/nhf9DKzPHojnmAr2jtIuE2xE+JwXC9IU6ttP7fdnqA5dJXiAck3L2KX1Wy7gdmWXePzOetAYb7XvnnOYuD/fIp+2S3gb4JD2nsU95rqCvnZm6KWa6XREz7O/M1+G2xynof2lTQ8c8Gh8M9dvjbIc+J0rj/eg4kcA6kfOF7SjPrU4vujs93hOOeBZdRy/q2G2MFjrHKmeWOda3toc+VfMfEO+ZJcBm1zLf6HKF698VbPK1qfQumUK7kOz4uwTHPQ2Pc2M7t9gmVaxlLB7hfxHqNroDj8x0TmTBgaIRjXgKjcf+HPRHhz8fCL5/1WeRc2O/APGx45HDHPPYvo5bt3G5fQ4H7Gio74F/VW5/dy4X+HQefUYyLCFHeyPMODR+YENPPMW3+L48j24HdnowC92RUdux7ARMZyzmvSK6VB/wVOqTfKOUjCN6OLI9/O85/2uNQmQ2et72EUPL/UB7xdXOnPKzH+cu9+OBv2158ykzd4Gw9H+bCOGFNJ/xYNzR8eFRUpGPeiczhMHL8UO3dB39b9+6zfKUrrLF1/HB3/HtDNKHZPzu8PMhh4A+/Hxz8qS70BuvztQUcXx7xdUP7hzvmHVEZtcy33T5q8tqiskr1L5n9075ceDc2vq7D3o2VUdPnCGFF1cyab2WfvPEeI/dl60cirIX1ubvyuZJvR60LSNTwB68la0Rd63mykHJ2PBSYnq3VcN7gnBv7h9R12LoAo1a9EwyZts2PC6vmx1XF0+LW8S5fLvTv7C36/vakwLY34IFJeUvZ9gY0vYa3GbRy38Aa12fNs5nXO9hTW0jz8xs+wWYC7t27k3BR64o4Z1v8UHV/GD5Q6Q82ywIrRQzvFYC5ajUwfkjD60RgRrC8xGaKkeE2M4G5EcPrL2BmxpIZS2Msg7Esxlx1OZsXWA1iwefzR2MewLyJ+TVI+RrTCVZGK63R6SeDbBaWRyN6aqStWuvbFNPirBEVnaUFTR3yTyzrohpRnoSrsmFEDzweXLxuSMK9WnRslc2UQHlIOuX1cjge2EgSZ/m+KbLMKsD+9yTcb8cnfWEzA3z8rgWxTevvVMNyAStE4pzz64CXWEewR1tfEi6jeVoNbC8=
*/