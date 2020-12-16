/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_IS_SAME_SIZE_10082015_1156
#define FUSION_IS_SAME_SIZE_10082015_1156

#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Sequence1, typename Sequence2, bool
            = traits::is_sequence<Sequence1>::value &&
              traits::is_sequence<Sequence2>::value>
    struct is_same_size : mpl::false_ {};

    template <typename Sequence1, typename Sequence2>
    struct is_same_size<Sequence1, Sequence2, true>
        : mpl::bool_<result_of::size<Sequence1>::value == 
                     result_of::size<Sequence2>::value>
    {};
}}}

#endif

/* is_same_size.hpp
To3ynR3ZEZavwkZb5lbyN27u9fV50JWvlBcheZDv6/P2rv5RMupdAPm+Pu/C8s4paVMua/md25v63N6M1+91+5d2SeQSycoeeW9wz1oHQEdrxqdb3AtY8dQX5wnfL5D1ZczthTgEMUJKzQPKqbn61AToHXjPrFjkw50ko5k1ufMkZ2s/NXi/wpiYU7Fec8h/BzGgGsxTn97lk9OaSRlw2uMO88TvI54idLI5WpyyuOfBGBM8F1znhiervj3PwRhvvPM2J+CBWE4NZhdjBDPSpqTb9kx4DMbkZAozSrXtmfC8HGMCk1Ybk5rcf9P+OcIYnaQoqeQmed+0f16N+8fG4rVIpuGZ9s8DzKNoYcUp2fBM++ftGJOsyFIV3vBM++ddGCOFSsUwoGm6Z8R8AGMcz7Z46dv2THg+1fHkLDSNriGa9s9nO12LoqUtsUlcOO2fr2FMKCUlbgrkHWz7B9qD+0dlKWVUuuGZ9s/PMI/lclibFU753M9tjPGWam8E0DTd08zTH+A+1TYUWmjDM50/T8UYSVWtWQxte6bzFGNcVEkWadv2AA+8R1YMjsUlSxguqI+qfYEdzkL316lID+eT/JIIq0kwrIhIEzEVe2cH0JDptXsDXnTcvkhbTHE9d6pfMJO3645bcmZN0n4bd4MnkAMD4T2RSXpjIpu0e3Zy0sZmBJtjhE/EOp+KVXwb/1AGivBY8eCj37WDCUq5dRLXYzCPgs/EMX/3D/G7i5R0uPcS2+rQ4sE3vcXfKi6HJAY7viYG2cWzN+Oklb3JrODMFXL/4KT7Vn9hK7fjLVMiF0UWxydwz3cBd6Oo/oIkqa3J1K6k4dOtjW3yLLDLQlhFuJDKGK467PopB7+PvA1hGYlOJWpFXGFXH+T8ZAbxl2CdbXGRiBCloIqvYHp4o5q+m38AcdGl/Zm2wZNjWq9gL+p5v6lia7+HcJ4EGaIerCwPqpmZvXd2fjG320qAsziua+Rc8eJL20SIxQlncYxJXAsu7RpTlm+3gAG70R+157ASRZBsWEIPlk+XXfy8VnbXSSl8KqzeORzcb8Lij2Pp6a38LekVjyoXUm1Rpra4z2llC8m0SCFMgcLrVTvkYwKbnR91fWOpzSwIcqH47o0by7R+ZQY2DVdwRm9xeyxzrXX05DDtt1ciTc4oxCNJLrSYxPPqtqVO7ZMhsznqlHGsdnUM3lgamYckh+sc0f1b3rsQThGeU0hGWHI5GB3ON3d4LSlwfgphOSlBeB7teuxc3JudHb+l+cylEHsC9W8sgxfyenaA5yLY8HQ6EULlWDkGb49NmL6T1jui6uTZmz24xd6MTugsRCIvsQKvb/9s5W6HIgO3XpL79Y5+Y1J0AvZjP8b6MsJa74QdjM0H6+S6fR3mFw+G8nDv8Sy4v/gxtof2oRQTyWlzP3kIb0itbCZFJCWzCeTitQd1yMUKec35eirDfbBYtHEvkhVOpSHXyzbfBdKWX0ihUXHpC3nt7I3nQ4/PxUU1BOm+OVtMIGK4X00qLydauj9kDuj8Qlv5HZGtEsVTsjg6h7z8kHN+0crucV50NDIu+6BZYq+NvqFIlzmLHFyk5GibP/DbW9kXuBK8KKaQ0+H6flNnmA+ofwWJcnDPkBkWiKkfwrMgLiXuMyasoIxygN49vjqZd/eyn0Z8lGiTg1cRMC+ty2kTL4vA2Rf3XyUSzisGuFXaG7yOPYq4GOFZeaEcYLrgXATG/E86e6cSqA9pOHuczu/WO9Tao2dzGAGoX5/ZYvdkZEokz9e5ZWewHt2Hcd/KJ8Jl9jKoQpbhs9Cwv3YB6/NPcLuCCZRxW0gdOFfx/HDpFTYaPlP4JmxxhUgepKPOIRh7c+c=
*/