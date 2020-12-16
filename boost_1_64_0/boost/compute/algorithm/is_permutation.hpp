//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_IS_PERMUTATION_HPP
#define BOOST_COMPUTE_ALGORITHM_IS_PERMUTATION_HPP

#include <iterator>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/algorithm/equal.hpp>
#include <boost/compute/algorithm/sort.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

///
/// \brief Permutation checking algorithm
///
/// Checks if the range [first1, last1) can be permuted into the
/// range [first2, last2)
/// \return True, if it can be permuted. False, otherwise.
///
/// \param first1 Iterator pointing to start of first range
/// \param last1 Iterator pointing to end of first range
/// \param first2 Iterator pointing to start of second range
/// \param last2 Iterator pointing to end of second range
/// \param queue Queue on which to execute
///
/// Space complexity: \Omega(distance(\p first1, \p last1) + distance(\p first2, \p last2))
template<class InputIterator1, class InputIterator2>
inline bool is_permutation(InputIterator1 first1,
                           InputIterator1 last1,
                           InputIterator2 first2,
                           InputIterator2 last2,
                           command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    typedef typename std::iterator_traits<InputIterator1>::value_type value_type1;
    typedef typename std::iterator_traits<InputIterator2>::value_type value_type2;

    size_t count1 = detail::iterator_range_size(first1, last1);
    size_t count2 = detail::iterator_range_size(first2, last2);

    if(count1 != count2) return false;

    vector<value_type1> temp1(first1, last1, queue);
    vector<value_type2> temp2(first2, last2, queue);

    sort(temp1.begin(), temp1.end(), queue);
    sort(temp2.begin(), temp2.end(), queue);

    return equal(temp1.begin(), temp1.end(),
                 temp2.begin(), queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_IS_PERMUTATION_HPP

/* is_permutation.hpp
sxuzH3MEcwKT9Or/53qXr2b/PzKGguovfP6/R/Z/SRJxeZi7rTyuKwcLiPsC3I8OEfl+zqKBpbmXVxaIbJ9vibrvDn+XmRfJfKcdJpt4VmUD2YHsiMwqqNY9kQ1lZsRx7pF27rNT/5ZBZepFxr+recfv3Yg9hs69kuSnwV5J8qBuGU75tkN++Km7YT0UUA9poeshq7DckrJslrJiM3VBvFPURdop6iLtC9TFZik3+TnNuvC1iXf0HIONmBa63mORR77RsC4qyzj5eSIXcO51sffNrZA45dYiez+mptPar25Uhid1o/5cdZI1zJzF+5a4RQeVVRbBVeJfEiirNLL658S/qdqd6X3iO2O+3F9Wb84Qz/XUEH8YOeyNEneQ2l3WYU3bvrZ0QaOHfIP4d1e7L3yEubevNOIccp98c1WAHLTI3FutQ3XLCLjfaWbvppTTcb/76P7zc7XtD8EUc7/jq+R+zxuSNjxr2pipE+wRwAo1BmicNPFvlSjfIO190ca/l0PunV9Qyp8q0zJhegTtG8XGv6tZO9OPUvT3yb0asXYmcKyYBMkrbt68JjvkXpo/I3cOPYacUOHwFt1rdzWmzNNvgtejjiCBY4hZJ6Tx1rKna0Ko+tQwbc1e2cvFvtI6R3YxuoLVs4SVPX0SttrqJXKI1lr/miahAutfz7dW/5War4D+pmnvlTAJpp2wI1PanU9/xzXiP4T2FmvpuQMi++mHWRrvuZ+NXwtlxrszdD/N/teY4PtfU5Y3fv8rYU+6/7XL8i+6/1XXPukagN4u3GEqPE5eM5fb+1+RFxXnZxWVVVB6e+wVu+bXF76l6N/pLCmWLytYnlcktaP5ziHcyxIOWbrYXdZBsd/L3GmFPXZK2nZ5lxBvgYTr5HKcf67yqF3i97zEj4z3xffKypJ1LM2WMG1cJ3BJcun6AUlnRXF+ZZFJa7WE6612TvtYgZ3cOcdoux/NlfCpajfhTylX0u/WOgZLXTpkSfUq+0p3M87ClrDCM1+T9Gvyy7Jyq3x6b1JEh43aSX4eHFbtCfdLVzst/zli3+YqZXy8i7NknrWe0XvnS/MSyxuWJ+zlHvsBxoK1rL2I4R3brfdGr+O5NXqtEbC/pP0bV6LUmS+9T1xdXAesZHHzpfknrv4Nq85q1fAMFtIajD1F0jqqZ9n70hpnJWs7aCn+T7kO86bc31Wt7cNlvS7p95F0OweM/TkmnXSxl2CPkXROkGfagdTfZVVllQUVvnJlwBES5oDLp+MnVey7XU/T72JdZZLWRbjPkWuPoo4I55eXKKk3wuC2WdyWMC8617n2c4W97uqg3s+cJBl3y9C5ZM4yGiPXflbyMoO48WLf53qLmhnoKiBN3J3XNtdJC7jOIez2WUA5yxb5rd2aKOk+7fLNQQokvfZS/zOxR4r/QdcHuI1yLdZ1YcGvmx5w3SPYHf1Xx7KPJc0uavelxTzHrBHKs3qrLPJ6CfsNelhTKwHTiZRTac/pcCz2meRL52LEl77B7zJJew55ai/x33PZfuUqi+Rbp/j91GXGIeYoOgyZ9XhtJMwHEqazN8wy/zFukQsXCeOmzrBTN9liv93VArc/q+6XSjOm2+ee1Ui5FzCKjrHaiRtxxe0q6rUfz+We1hpfX5QPQlWVhd5ub9YOm7zjZ/qppj9W0upEvoKl3cc8T3/DwPQmZnACRp+n5adY61lkr/UUnUjULXYyp8/RveY5asYPCVsf5Lyf/dg7289WiX/QrLvSfqrxD0H6C+7SX8TtiDlfSts2bmnmeZ1HerrmT+KZOnSMv3tUlntc14W+jakm/I6VvvE3v0rmJWauU6LNwMjNNWx3ub/J2H8i9mXMmGLUjbY=
*/