//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_UPPER_BOUND_HPP
#define BOOST_COMPUTE_ALGORITHM_UPPER_BOUND_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/lambda.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/detail/binary_find.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns an iterator pointing to the first element in the sorted
/// range [\p first, \p last) that is not less than or equal to
/// \p value.
///
/// Space complexity: \Omega(1)
template<class InputIterator, class T>
inline InputIterator
upper_bound(InputIterator first,
            InputIterator last,
            const T &value,
            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    using ::boost::compute::_1;

    InputIterator position =
        detail::binary_find(first, last, _1 > value, queue);

    return position;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_UPPER_BOUND_HPP

/* upper_bound.hpp
M54SxuILqF8ZY6HPqFUFY6luDiobS3M6V1fO71Or2sZiH5M1UB1uXppqvUeZy73GotvYj9bydfPXRrW1IYso58ZkTyhGOuN2NZa5jDF6Gkvs4t7vo1zc+6OB8k2SDZZ++3lvHGYs/SGuN1p9c/tjnLFIR/ZykuK+zX5MEytNrV5Uz6vmAJurektzrhYqxjD27VXl4t7TJVWHO+tbpRgrmd878p1L9qH68Qs1WKu47l62Ufk9xVw+U23uM90X6kc+sl2atfKMu9/YBfcbLYc145tZx3H5fu7O/5RzWff9P9Xr3nN+r7mqT99fjCU3csYzNRvu3cRV2c3ide26ZqMO67gpXSaxjuzNLL+SvD7nMRY6Rd/bjWX+wHrvMBb5gHUUNxZz55il5fsS+1beWEpHzlAlMXcWVE25DKYutYyl3UtW35j//NFEtd3D/qYo56XM5X7lPJ46P6xcFnJvPWIsUJ75PW4s7j7jdFG97vy5h+q4zh711no1eb0fYCzq9Bsku1eZ31DZuXpHSZdS7NHzYgsYd6Lyc9eSqcaCY1nvLGOpboYSxsJBzssCY8nanMklyq8BYyyX3fO0e0N2O8jeNpao4c7/jKW3ZC5r1KNCzGWDtBrGereo50nqvE25VOds7FSMOdR5nzSYx/wOKedtnL9j6q97X3tauQxiPzKUyxDO0Heavwbu/E+5uHvZb1ovP3P+Qxq0pu819Xw/ff+T3Qjqkq25nv9YR+7mypn55TcWdO/9ChmLTuTcFzMWWejO/4ylHqBvOWP++0h3K0Z99/sfxmIbOENhY6Fj1KCescyjvJY0NpYxjT1vYSwtytpaiZUme0hx3Ty3V1z3Gfux5tKUrLOx5DD3+x/KpS/n6inF2MrZ6C/fKbR7Rjrfy305RPXezbgjxZqzl2ONpbtrSVw9GsjaXjAWz+V+/1c5D2Iuc7Te5uxg82/1jT1arLkq7s7/FNf1baVmLQ9jvHWrH8zvfbGZ1PRj6TKQ9a6Xfu4z9mbZXaDvVuWSINuhnHe4//9PPe9A/dI1zw+SHVUdC7jeKcWY7H7/Qz3/nPpdUNzVXO8nzdUL1OBXsdPs0e/SviH3/t/GEi253g2xscwvawvTdCJj5DIW3UOWT3YnGKOgsRT39yRFjWXk5RyUEotzdkPGAu5acpexuNtbVYxF3KzVNBZrSLu6xlLrkzWS3VWy5oo7irPWUjF+Yy4PKpea9G1nLOnq6GAsWNX9/a+06kRduhkL1ec+72UsvS6vV/2US4jz8j/l7M4sY8rP3aNGKMaLzG+M8nN7a4JiNKHdFPme49zPEHNnvrONhasx55cVw53bviJWifUuU9zCrG2F+raVvm9qXi5zTt+TBr3o+5H64c6R1ml2d3NePlXcdvRNk11jXje+VG3u3GKPejmAvTwo39XU74jsppCdlH69ud7X6lsd2n1rLLMtc/lRs7GOdpeMJb5gj64oxjTm95e0eoRx/1Vto6hplv+zdy5+PlZbGP/NGGNcJqPcu41CVBhKJbeRW8pligqRcat0wrjlkssgFSpDRbqO7qeSSSWFGqJIGNfSUY06ulIjEYrO8/WuOZ21z19wPsd8zvns3udde6+1nrX2fve79jsmXfMj/Pf/hGUGnJYVFgu+iU4Rlp4T1P/AevpYVheW97aXOxsdwbeXNYWlBedqdRkvqHvXF5Yb7IcuAhvpubqM8Tp5Tptjy1qPXSEsI87nc3thBcG7aUfGe8Hzcg19G3o/rsfmMh67UVjqaV5HJjZ39dwPBFvk7bsNWxpVdthQYSnP+5iPFFZ4tY/5WOSuinPYRHTs93qnYvMj3uZ7hWVf4LH78bep1zuH3Fjm4zsPW973fjw=
*/