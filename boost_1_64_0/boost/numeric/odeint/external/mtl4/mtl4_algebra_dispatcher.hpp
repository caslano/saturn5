/*
 [auto_generated]
 boost/numeric/odeint/external/mtl4/mtl4_algebra_dispatcher.hpp

 [begin_description]
 specialization of the algebra dispatcher for mtl4
 [end_description]

 Copyright 2013 Karsten Ahnert
 Copyright 2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_MTL4_MTL4_ALGEBRA_DISPATCHER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_MTL4_MTL4_ALGEBRA_DISPATCHER_HPP_INCLUDED

#include <boost/numeric/mtl/mtl.hpp>

#include <boost/numeric/odeint/algebra/vector_space_algebra.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>

namespace boost {
namespace numeric {
namespace odeint {

template<typename Value, typename Parameters>
struct algebra_dispatcher< mtl::dense_vector< Value , Parameters > >
{
    typedef vector_space_algebra algebra_type;
};

template<typename Value, typename Parameters>
struct algebra_dispatcher< mtl::dense2D< Value , Parameters > >
{
    typedef vector_space_algebra algebra_type;
};

template<typename Value , size_t BitMask , typename Parameters>
struct algebra_dispatcher< mtl::morton_dense< Value , BitMask, Parameters > >
{
    typedef vector_space_algebra algebra_type;
};

template<typename Value, typename Parameters>
struct algebra_dispatcher< mtl::compressed2D< Value , Parameters > >
{
    typedef vector_space_algebra algebra_type;
};

// specialization of infinity norm calculation

template<typename Value, typename Parameters>
struct vector_space_norm_inf< mtl::dense_vector< Value , Parameters > >
{
    typedef Value result_type;
    Value operator()( const mtl::dense_vector< Value , Parameters > &x ) const
    {
        return mtl::infinity_norm(x);
    }
};

template<typename Value, typename Parameters>
struct vector_space_norm_inf< mtl::dense2D< Value , Parameters > >
{
    typedef Value result_type;
    Value operator()( const mtl::dense2D< Value , Parameters > &x ) const
    {
        return mtl::infinity_norm(x);
    }
};

template<typename Value , size_t BitMask , typename Parameters>
struct vector_space_norm_inf< mtl::morton_dense< Value , BitMask , Parameters > >
{
    typedef Value result_type;
    Value operator()( const mtl::morton_dense< Value , BitMask , Parameters > &x ) const
    {
        return mtl::infinity_norm(x);
    }
};

template<typename Value, typename Parameters>
struct vector_space_norm_inf< mtl::compressed2D< Value , Parameters > >
{
    typedef Value result_type;
    Value operator()( const mtl::compressed2D< Value , Parameters > &x ) const
    {
        return mtl::infinity_norm(x);
    }
};

}
}
}

#endif // BOOST_NUMERIC_ODEINT_MTL4_MTL4_ALGEBRA_DISPATCHER_INCLUDED

/* mtl4_algebra_dispatcher.hpp
f0LoZMbSoSzes5YO5YjGJktmGUsPthDeVlFWlSjrVKus06rxWGV9kGicLmiUWXU8k/I8Q/bzLMpztsVf2NK57YR3bnVJ5zK9LaQCO0uezTuPecXdzvz7WPH7fvo9E7xNErFS5yPvBXguxHMRHmkns+Q1XEx8XyLKmWbV9TKq6+Mkk8spz4dd3yXfN7eDMVJF1rSLxuCYO1Or/XP1K/Bu1ie5HfT52GoeH7L6MXhZxtPcXV0t/Bflb8trq8053ZRJA57a6aTjty8e62OWzoEn7C359zhvZH6QxrFf0+V3xsDPzSTTW6qL7IUW+N6gvo9U5zM0b8NvJb6/crvVnldYunsHvQNO6yrEM8sZfAfXOO6u5vWknJEVxmODdwrJnOs4QX2S6nivbWPHB+PjON9u6n7K94Al7wAu5P0g4T4UaBuLf+A+QrjvFbp/trUm9Cuy/58hGT1abfTsMfyV3/6dVehs+Yj7gtgjEOV/o9KSDcvWPOP9svki1eFLtm9ETz21ndS1JynPl3UebkOTh9uhPqCnE9RXKe/XTF5OM/3G1MHSNyM7nh98q1r2Y7N+ZvoN9+PvVKsSz9aVdr7sKc1TsNyn8VeW+4zFG/RZxGoanGdZ701fVvzUcV2Ab2T2HMnleUsnkdfCHat+SLgvWLiGF7LD1UZ/fyxsGPL72uKnROdngTKDfeYXhPui1W4ox38vYTWXb2wb6yn4C/Rhxt1NvYS/hgfGk33xZeLhFdlOBfV+nPo94f/BtglVzDfGSE37Vbd+xfYFS4wT0vcdFlsrKGGf+41iNr7AGRMn318K9Fc8BfvrX6nub4n++jS3n06DfUea3+a/XW1oTbds/jus+9Qu/PeUPOX/k8r4F+sW7sIQdy3WMPxyAR9Xk7+/glcZ/w0J+vvIsKVXE5GudTQgp+A4s3uN4XUPKpv7JfenMpMmy+S7L2jMn8xlos8G7YPBNWWWU5kVNdY5JstmVgmaWTMuoR7As8c10KypCepItoiO1BEPU5gH9BVui71rpN5x+Tmil8OzT41/72hqjdQn9sPw+Pywadx+2l893roTtJ7oTvf2fFgnvlCtyw+c+9gfeVAH+M5chwMs+c5kfs1aFPOBNKZZTzbkwBrOe791T85BRAtwj0fg4i5zLn+uVf48q/z5XD7oB+XQwOnIy/wBT6cv0Onkd+rv/pn3nM7P3wE8vMY/V8jxmM++suvH+fRkkjqC9ORIoiHv7nkZR+3ke/lYvJu8JJMRY3v15Ke7dXXnSvraet4Udw++pvS7s/yxHgXSiG4j0V1ccN8SQX/NnS0i7N8Gajt/V5G7tw4250njG/RlWXymuCz4/QCsQQ6FM9m+VDScjfnv1UrEtljwJeB4iqKro4luE2BTlffRvIyL21xD93rqGGBz11ZLDdd0Dn/vInCHJwOL7dtvIVRrZS8ALnZWTReHwDJxB6oAybXBZdRuA5C7Wz9l6sf3glvtUG/ulfbtkSxHvmpl6PvvK+PvRZh7JkwMRZuQ2VS+E8WSGQNL+O7hu5B5Yx9uQMCNNOscL5iPQQbBHENbUyzuvq2np89R6uBeZDCF5zMdpfVNGbFvPp6dP8njtYvoynkXTLyOFViKNG8d0+3DtCe3UrcRJCj63xyr/00BbIHKuHtx3l5ti8IuTCwNRTLt7sKXi7OBq0C/XYU3umfcO/HepeLRlGL8Xuc9xHmyTmurOG8ECz09weHVOYvb77cF6/V6fYgTKc+xKC9KtsOl0w3YoMoMhg8JOet7usxewE7TcVL8rZYz9bvZrHdh2524qY1mPlsOHe8TOn5+se/gFL8raFOY8/A78vyyiK2cYmxlYO/0YG0Dub3c/jzVsqFrtJ0=
*/