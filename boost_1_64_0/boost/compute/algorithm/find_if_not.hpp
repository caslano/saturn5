//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_FIND_IF_NOT_HPP
#define BOOST_COMPUTE_ALGORITHM_FIND_IF_NOT_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/find_if.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns an iterator pointing to the first element in the range
/// [\p first, \p last) for which \p predicate returns \c false.
///
/// Space complexity: \Omega(1)
///
/// \see find_if()
template<class InputIterator, class UnaryPredicate>
inline InputIterator find_if_not(InputIterator first,
                                 InputIterator last,
                                 UnaryPredicate predicate,
                                 command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return ::boost::compute::find_if(
               first,
               last,
               not1(predicate),
               queue
           );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_FIND_IF_NOT_HPP

/* find_if_not.hpp
Y7ztd2bzTdncR43T2nxjqfuaOW8DO9/exV7Xvp/67Vbvp8ZvbMb8BRJ+qXkHjxH735Cxz7JC7NPXNFqa71m1JM73VpB9+uYZFidhvhD7MJNGM7+xmUukywTQzP/aSZzLmf9VUjdap7itoH4XS/7mx3lloxMmWyoL9cU7UWI+Gq9zpo7i/wpPk2a04WQz7uuc0n4n0jEs+Rzv3ammzdj3K9Yhv/Hcg7LvjU6FlA93KZ+2z5Lzz8TXzPzTsV+vSNtdPKaqmlaed/RD0u4YMUQsm3Z5aj+PjhJqPyeHIP7f2qT8iSFlk87r5Tcpeb0krlcY5Hr5efm61cZ8RyUM3dq0dY2n8j2+0fHbE2PizGkTzPzXhDHf8kqRZ9PPRT7nvWa89nPi42ZfR/S+aPn6Ni1Zvg6ksSFY+WbOmBy6bL448WauS5/x1/Vn/M33xx9ZLu/4BaVccg1HmY4HKVM74u8zZeozdEj/9FG9Bo3sJ91Ty9Q2SJn2BeT5wTLkua3JszN/u5uVzF8nwh4Llr9Z43JmZoXO3zFT50b+mzkbmv1ZAfkf/CPz73xmyDXM/qtD7lD7mkLtywq1rynU/qVQ+6N+vn1NP9c+pXYVPe4PVK79j6/nWy07zRsyLn3nMUa/PpLP7t8mtkz7Zu7ibZeMqX2y0tIFzEMreNyL/3R547syHqhyY+RBV/w3m/eE2k8Vat9XqP1OofZHhdpPVfZ9bqH21xVI/hdtXv3mhy8kJS18YcTs7Js3nSz7/quy7tM7IPW5/43Rf70/p96JH27d0PftpjtP8Z1a8lNQ96avFw5bNebG1peti+5U+XiofXol93cVumR9s8huUvn9NuYrv99f2r9FdtMVNiL81/ZvWW8W4fLuwdD9Drp+TdbO4efc7zBU9yENh7XgSNgYjoIz4WVmfbauvdI8k45jffYYXS8/FjaDV8L28Co4FKZDrmH0/He1dE0STJL0nPtUYsO867trwBowDraBNaFZL67x62MKXT9tvfhus36FsUby49zvcNjlLd/vYTN4BPaFf4D94VdwEDwKR8N34bXwj3Cu+l8P34dF8CN4BzwBV8O/wI3wY7gVnoTb4SdwB/wUPga/gPvgl/AlTfcUjHDrOgxdl0L+mV8wZkJL97vVgV/DlvAb2Br+HZ4Pv4PJ8AfYT+1D1J6q+9DSPIBjoBuOg5XgVFgZytm7Wr5ILU8U3AzHwN0wGj4FY+AzMBY+B+Pg72BN+CWMh99oPK5h1YZcQ+x1YT14MWwEe8MEmAkbw0kabjZsCm+FzeDt6r4JtoL7YRt4EraFn6m/5aZNwuqwPYyBnWEC7AKbwG6wO7wI9oA9YSpMhsNhX3gZ7AfnwP5wPkyBK+GlcD0cDTfCMfAROAC+BgfCI3AQPAUHw3/AIZA+YA2FDeEw2AIOh20h6eg+FZW767qEiIB9Knfq/s2V8Dy4Gl4M18F+cD0cAu+GI+A9cCzcCKfA++AMuBkuhFvgvXAr3AK3a3vdrPf3Mfg23APfh0/AD+GTmt+nYRh5fBZWhPthdXgA1oTPw8bwJdgFHoT94CtQdKCZ/aEq61Q5a0TA/tBvdf9AF7e3H18A+8MLYRq8CM6A3eCNsCdcApPhStgdrha77vN0q/xLZHne6w3l9yK3frAhXEM4ALaBA+FAOAgOhh/BDDgc3glHwvvhKPgyvAwegmPhm/BK+C28Cp6BGfB7OB566m8CbAozYXuYBbvAqfAimAOvhLlwPMyHc+DVcDGcDpfBa+Bv4Gy4E86Bu+F18DU4F74L58EP4A3wI7gIVqbsN8JqcDGsD5fARHgTPA8uhclwGRwEb4bD4HI4GhbBbPgbeA28Fc6FG+BCeDdcAu8=
*/