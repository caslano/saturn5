//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_REMOVE_IF_HPP
#define BOOST_COMPUTE_ALGORITHM_REMOVE_IF_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/copy_if.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/functional/logical.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Removes each element for which \p predicate returns \c true in the
/// range [\p first, \p last).
///
/// Space complexity: \Omega(3n)
///
/// \see remove()
template<class Iterator, class Predicate>
inline Iterator remove_if(Iterator first,
                          Iterator last,
                          Predicate predicate,
                          command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator>::value);
    typedef typename std::iterator_traits<Iterator>::value_type value_type;

    // temporary storage for the input data
    ::boost::compute::vector<value_type> tmp(first, last, queue);

    return ::boost::compute::copy_if(tmp.begin(),
                                     tmp.end(),
                                     first,
                                     not1(predicate),
                                     queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_REMOVE_IF_HPP

/* remove_if.hpp
//MnTyn4y/v/m1qN4lv4lb6xtoXZwwK+jYNujWrcuoa6YfxumaFuzWrc9gl1SxK34x3ptapxc6SXUuPmSK9djVsgvSS/W8cat27q1jJOFmjgNiV/cpEl4xi7h+gxYO5e5GXWjbSGg+BA/NeygEHHMY4v2PYYhoZ93H0Mw/jvY/YFJHznt89pMNs+yMdaQBlTcBnfkLWijSXsFbaOd2hae+kaZtua973fflFUtXWlrfr2kVKqhPLrOdqTJMzFvg3WsSHnbHO2tK5ZHCz+Y6P98QfFid8E/jNr4oaKf150MP0Sk35TWPCz3z+dvtRI4rTAbYXEeUmuewJpdJFy9Ay9Rn/zmnPX14t/dWgeXQN5JMA5P/n925FHjMRphtvkH/xu8eas8QmSxudWSB6ZoWl0kmv60nesvdUKyccR5lfJJ93kk4Rba8nnNMnnRJu7RfKJCy0L3Td4ZvXt4r8itCwZoXl0lTzamjwKSXOGxEk29fWg5Nnfbir+gXbO8zWz9vc1lTDqxj6WaHuYLTo2/qbxrNDzJ1bqvp+f9H6ZrPdLxq+B+6X2Mb+asIsi3S/4O++XfLEvaXCxPbbW++UYCXuzuV9Iy3G/YOPf/KjnrTlu94u071O/+UNFR+exktbtfrlO/GdHvF9uFP/prvdLAlweZeO/H7WaYvryarku1r1qf1gk1/2tFel+6SV5bIh4v2zwkR6rfRoSI9CPL5A8ppp+fL3k0dCOdL+cJnnsFFVlPWZHul9GSllyJJ/Avd9b8knzBfryGZIPO2TEP9AG7S3tx2rPp21H+SLdUz9KGg9FvKfOkvL2l+sIPA/elDirzD3W2pb13bXqo/mr90pgj9yihpbIAT7WkcF+cDBhqxqYMfKSgtLA78toSaCpuWfKSgqmDAk9t0XjtQiOdQfPtqcOnP45LvfG0+Lf1af3hoZvGtrHCiYVB9PbIv6DrUSxs8NA7NG+KNwutKaE/JYUWoG2HrCTP8yd+hxjt0CMrHh3Pb//HUkvwZzf31fi3md3sc6ym5rwJaVjSssopWXiPSfxdlW7ycPo4E2Ns2o9Xz/R0cZa18F21rF7qd/geTMR2rmjDlmvbEA8uAL62/mS2NB25rlYx3auiZdg9lXdLPanGlj23b6E6Ln6bLOtB3b2u58U3h+0vTQdruob60VfbDT3sLgH4g137Se5Jv84SWc49kqxL2lQavfxXRTdgXRwN/mvk7qOraWu4yLUdZJLXae41PVWyGVEWCtd/7mTSHMei2Ru5sbuHzw76vzX+408Ib7wscPHjvv71z7Xd824njev74Py/sqrvfO8+ZVRnDcP18EU2C2atZGwN2xHpGyYDw+BVXAofAoeDztEER5mwt6wDGbDuXAg/A4eAn+CQ2Ei79HFcDIsh+fCk+EqeDrcAM+AfbnO6XAQnAkpB98j+jsNf9JytMAs0XI003K013KUwo/gqbA9kSrg8XAWvA/Ohq/Ay+AqeAM8i2fvfMiaT4k/BJ4KCSvxH4Lnwfho0oHN4WyYAav84eDDcD58BP4In4BxXO+TsAAugZPhcugv19XmmSy/AVKuOMxMLddaljA2hZ/CFnA93AN+BUWfOsyGG+ERcBMcD7+G5XAznAW/gVXwOxhj0+fhCGhrfewE+5B/I9gPNtbrm2rudfqK1ntnDO84IqeSTgKsgAPgDDgEng/z4AVwCpwNy+DF8G54CXwBXgo/hZfBLfBKOM7//gQnwbmwDF4PL4HzYFuu7wGYDt+CXeB8OATeAsfDW2EpvB1+Ae+Fm2EV/BHeB+Noz4dgInwY7gYfgbSzpP84fAtWw8fgu/Bx+CNcBHeifRfDU+BSOB0+C2fC52AlXA7nwzfgIw0=
*/