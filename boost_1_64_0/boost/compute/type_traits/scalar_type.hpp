//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPE_TRAITS_SCALAR_TYPE_HPP
#define BOOST_COMPUTE_TYPE_TRAITS_SCALAR_TYPE_HPP

#include <boost/preprocessor/cat.hpp>

#include <boost/compute/types/fundamental.hpp>

namespace boost {
namespace compute {

/// Meta-function returning the scalar type for a vector type.
///
/// For example,
/// \code
/// scalar_type<float4_>::type == float
/// \endcode
template<class Vector>
struct scalar_type
{
    /// \internal_
    typedef void type;
};

/// \internal_
#define BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTION(scalar) \
    template<> \
    struct scalar_type<BOOST_PP_CAT(scalar, _)> \
    { \
        typedef BOOST_PP_CAT(scalar, _) type; \
    };

/// \internal_
#define BOOST_COMPUTE_DECLARE_VECTOR_SCALAR_TYPE_FUNCTION(scalar, size) \
    template<> \
    struct scalar_type<BOOST_PP_CAT(BOOST_PP_CAT(scalar, size), _)> \
    { \
        typedef BOOST_PP_CAT(scalar, _) type; \
    };

/// \internal_
#define BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTIONS(scalar) \
    BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTION(scalar) \
    BOOST_COMPUTE_DECLARE_VECTOR_SCALAR_TYPE_FUNCTION(scalar, 2) \
    BOOST_COMPUTE_DECLARE_VECTOR_SCALAR_TYPE_FUNCTION(scalar, 4) \
    BOOST_COMPUTE_DECLARE_VECTOR_SCALAR_TYPE_FUNCTION(scalar, 8) \
    BOOST_COMPUTE_DECLARE_VECTOR_SCALAR_TYPE_FUNCTION(scalar, 16)

BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTIONS(char)
BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTIONS(uchar)
BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTIONS(short)
BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTIONS(ushort)
BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTIONS(int)
BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTIONS(uint)
BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTIONS(long)
BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTIONS(ulong)
BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTIONS(float)
BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTIONS(double)

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_TYPE_TRAITS_SCALAR_TYPE_HPP

/* scalar_type.hpp
Ma5+ss2ljo128+423utoX/7hbp7dviae6ubZ7evAe7p5dvs6/t5unt2+8iPdPLt9Lb2vm2e3r+Pv7+bZ7Sv/QBePty+kPdnNtdvX2tFunt2+vjnVzbPb1yvHunjD29efj3fyeftq9uJPSi7z67lGfKwrJp4mvO1H8icUrvZiZHz9Tw1kvn+KMBUPLdqxRnj+gyzcdh0InviQ5NE8GUUogjNx5euBGrwDz3TzdHbA+9kQnp66g/fyh7t5yh+dwRMf6eY16w/subB5ZC6yvMidrPAfdB5p7il/AfWKOQMtWFH38WgXh33CEd/klha318SHeRzjoPsMvu9jHXi/N4JzZBvj0LxD7wvJdLDXzTjofk/iLmgbR0rmd3kn8aTm1OxNl2dmg+7XrdCWIfyj7iKeCpeEQZ1NWHWWRlnu+fED15m5Dvs88o3hcbCHsaUL7xcLd4u3co4aOs2z8m0duIrCmIds7+KQemg2PMjv9LjJw/CLtM7sauHIL/bsdzMODXuQ39hrY6hD5GFlH+Po4dDYQ5rowK3yTjzMOPZQif7yzP7X4ek4y+b9khneNvzci6PogZeFrG0sq7Q/rpLVhwhI7zpLLxVB6Qax79633+4mwceM9JZUeqel2lVqDPtcH5N3sjh2Z9TEEqaTJSuPuR/7SZje975yVx4XVVqVFLLzYWI8H7c/y8/DEi/Pkiy+7/OwJh8fb8YBs1xuLcogrfLSc9QFF3lHRh5Er67LV0cuqPMvT4WqH05sXqQ3+pQHU9x/GZxDTpvx5iILnCKpcl/Uao/72RMZLK8H7xHEpkwhStevqqKWMrIPyzHNFHoW7zTzdGo38kq/jkTdWMP32medC4N+MNujnmneW9nC8L4B5DzqTb7vyPHljR6wWxyjKQH66cg2G5tZQxaNcf1XnEfTVkZ8DL4FGI+dO9wdb2Ez5n3sV3YynJZzKP/xXS1sxo8H+vl1F37aGeyf727jgUen6IM4Ht/T5jxnxHGzjatTDMKQj7025yjL5619HTilgT31Fo58Io6JNofy+f4Gf7iF0y0Ofdgyv7aq98zhJ2i/zZ/RzvO0KRV8t8P/pMHnexg/4Ji+BcKaCuI59wbGZfsl/+XY2rrMcz+W3mAd+aYuDnVKfl9//s1tnj7UGqyn3sI4vdlLC2amwXv0cc7T73KrDme2g59YPLsdHHwbx+128OLbbbzdDu4e5By7HZx9wsbb7YDl+Z02X/vkbvbpDnXitDhBnb78Ls6hs0HYUzzJMClr2BK8m2Gb5KVl0bwncphwzCvpzBNr4sea9c1TxCEcecN++yvvlRitGegt9BnnzJnnEvdjZwLziARz0xePEFd9R9RFK/h0sL5xWe2lkVPct6/FrvXEPMqMuZw8HDX2wq00XT8LEy9+4HMJM805pEnzXaSJ+yt3f0l3ROh9+RMzl6ZmajfzwylaLixfUosP+HZlectFWGdRGnv3f1bbzxviq1l8sQjztMg9N+u2gZH5kUti0xBGWb9oO9otcn+kWSG6gVxb5XgQROE72jgeBKHz2jdInEAvqeNAuUrt21hdl/uEfYXUznNOoeLa044Lj5OQzLeVTKAl+Pzz/KjSc6NkZZiDvcbtnfgMvXFtjm8vjRPPqK8AlTX4fu/mHLtO8ebAhOQZ+w1YS3+G+zPx4qCO0+SB55lh067N+IJY+HmZOEHpdde1URMyyzKaqbBZE5jx+KGIMr8Mszr7v/EsX5qheMx57yx03X84AGfYo8CYcs0x4+524kBvrI7PjRrp6lcFnoTfcY7brwrARmtrwyv8Jg742xqzMcgjH/42zaGSactrc+w/tN3A9Wef+d3eoXGaHmj582Twu2D4jBk3ODo=
*/