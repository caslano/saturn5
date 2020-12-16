// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_CALCULATE_NULL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_CALCULATE_NULL_HPP

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

struct calculate_null
{
    template<typename ReturnType, typename Geometry, typename Strategy>
    static inline ReturnType apply(Geometry const& , Strategy const&)
    {
        return ReturnType();
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_CALCULATE_NULL_HPP

/* calculate_null.hpp
dwWVR9zBfrWQTeNllR6uRRmQzQdlQHVsL5wlfJPO2+HcEPGCXgv6mkne11T6wIlM/xuEK8/1b/X4/ga+kwD9RsOL/iVzWPeisJ3/748P8NjL6q3U66V55f6e9ObgrahvhfqN/nn6Rnqova6DN4wpsBxnrC5T517p+051cDZU6v8G+MMbUY9Pl3fFyLtA9B4/HkulKUviLDXgpRZu7lBxtN8l/jF3Z2Zfb+hOkvhIn6Cfh7s2bxI6mO10QAu3nHmEsc9PrrvgzljsiwjWXgC3s85iXPW90LhqOEE+3SEiJQnheU/YyqwIX3Ir9Pl96FPgkxyj8W8H/h2yHRf8pc/4AXB/CFxZv/T9zuUo37tB8yPQSL/wuVK8dS7baMFvFvMV88loo+8D3/t1PkHzk2rIgXz+FPgPAD/PfUCUZnid7LZqW0dOSSeCOZA7rS310ryIewf7LgrXer2pXDbjIZ5spnd9HOF7KDxX3Gl1L4UXynkVwBareZSfEYzuwuoZGuo1c+6WwQLMdTwo7KbdoyqtpjokhOxmrL0dy1to+rS9rqNuuaWOgKM/9XB11FqjXFcM1lZM+BGjP2f7GfueJ3zMo9LHOLsfJH0GF3hJEHyL9JPkY7ist6pz0r8g3rAljUvlK/BhS48RfmA/9EXUq18r30umbX0d4Y6yvyfg6/jeCKJ/kmBNRZRBc2NdA7Y3RUWwj/1ddVHvLS9pweEWAWAev4+o83oe8hmd71LvlX0Jf/Jo3fL3VpnSMVnEc4rP3p4nyxO8osvzxXz9/0J+Gf3iP4l+8UvIL7c3E2TejdxqDraa77hVuLJ8MQcr+hupAvclvy5s7eXS6Ls83xB9m6eqg3jCt2m9qcZLOv5tEf+yiN8fsv4TvpF4h/zw09qXgvYdgkv5vKlBX49o5FiSNmy7MMHlHStka2IucGq4zz6RwrJdmDQV8oP/5aXhvt3OKl7b7BQRT7y5DC6FfnYlmNTvy4p+d5G/hWVhXZUp2jeUbBWOlupnkN8ql1+mq4ZMssymBnytz9xf2WKNkGkC4h6BTNMV7YFqXPVeyPSwkGkvJVMtZJJ2sjfo3iwL6Gaqspulym4fIcsswbMZPPcDfgrjqepSdV93RB9ljs8T85Evq/n4A4QM2v5HCLdf7RE8iPDlevVWfb8KpXmwSHMR/Jm8Z2Q+xZt1k3GmNfP7yHQHjvm/o8t7xcBLJLy9o5FmqdrXkh5N3DgZB6dv4ONHwx3Za45ugoxvqOuqc7E2bqdQem2dXSJuYoiubUWjPW80ye4lMXr7wFS89GI6DpmseVXVutTVh2goOVaSRfb9TsI4TfftDyWedk89bKYJZ2sXUNjzLDv3Zq3tM/TmBjzZf6cw7gcP7swnGB2vkf38mIHR8oqE7WHvLiag7Ofb3GGDjsCd5eA0oYL59an2/mK7iEp4DJsLmFu2D+C0Dp8bULiLAWNc5LGZ1lW6SVyZfruBKfm7DCzIp9XrGoLZaS7stS6lcltEafn/1nnUsrs9GUtWNnXXd63pdk3iaLBt/3lftOVBvM01SiJftAbk5HcRvLfnCJFmaZBm45ruppUr6jv9hjgqgvsdxH9UO3PUVPfJen80hSUO0dEXxqmDj0oLH1UP/vZswVRuh6L7wDuoN8O/aWqBMyLvUifN4Cnr1VLkl+pLqF4to7Aae7H+JF6r8GHEi/DU/PUoPtCx4tM+FXMUWi58sq/WQWF/b6DrG9FYAHZFPlTuj7G8SuWcBGCxYN7C+pbaYI6C69Jsc5c11SU5Zu8StjnX8e3J8b2eQViPo1cL/05ha1erpubpc47B157VQFma32vF7+3qrqzjp4bm5ijepX2CKJdsPjwqlxPhXw8=
*/