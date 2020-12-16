//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_MIN_ELEMENT_HPP
#define BOOST_COMPUTE_ALGORITHM_MIN_ELEMENT_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/algorithm/detail/find_extrema.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns an iterator pointing to the element in range
/// [\p first, \p last) with the minimum value.
///
/// \param first first element in the input range
/// \param last last element in the input range
/// \param compare comparison function object which returns true if the first
///        argument is less than (i.e. is ordered before) the second.
/// \param queue command queue to perform the operation
///
/// For example, to find \c int2 value with minimum first component in given vector:
/// \code
/// // comparison function object
/// BOOST_COMPUTE_FUNCTION(bool, compare_first, (const int2_ &a, const int2_ &b),
/// {
///     return a.x < b.x;
/// });
///
/// // create vector
/// boost::compute::vector<uint2_> data = ...
///
/// boost::compute::vector<uint2_>::iterator min =
///     boost::compute::min_element(data.begin(), data.end(), compare_first, queue);
/// \endcode
///
/// Space complexity on CPUs: \Omega(1)<br>
/// Space complexity on GPUs: \Omega(N)
///
/// \see max_element()
template<class InputIterator, class Compare>
inline InputIterator
min_element(InputIterator first,
            InputIterator last,
            Compare compare,
            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return detail::find_extrema(first, last, compare, true, queue);
}

///\overload
template<class InputIterator>
inline InputIterator
min_element(InputIterator first,
            InputIterator last,
            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    return ::boost::compute::min_element(
            first, last, ::boost::compute::less<value_type>(), queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_MIN_ELEMENT_HPP

/* min_element.hpp
S0j0J5h3CHIGpdxXkzRst2DYFmvuDw8T1MdXrDLt/1CW/psy7ptdZNxvga31OTyCjLvpI1GqyOhmnYs2Yp7mjz3l2kecz5eh7W3mlQ8k7DrrB6SrfUbjt5Z6XR1+TzT+qaaPvCf29ewe8DjPOg1Zi6bBJvLddqarTPtM8Ys2epfixD7HvCuwAvlogM5D6pD4zjoswL7ajGcNY+vYcdRpXEuLH/H1fYcf8yvqdPM8rdPa+uOuOuxseOpQw7d2ngNfbK/rSNKECR+HhXZ8u58eWt7DvI/IhtVh56/nmvlI81C/nozcx7rvQO7jLpGb6Nuz5z23fLPg1JQRY/pGV3a/9P9PHsRdl1BkOZEum0XXUtGAE5/aMG3vHRded++oCZnT/3flRD633/PJs1Ue4V61ZH6WMzxuU/n2PPPeWN6Dix/RpR5V7ENkOxbClrAKtoZL4Ui4DAbl5PdoOje6nANXSLgAp8EMtbeHJ8Cu8CQ4DBbB6fBkOAueCovhaXA5nA1XwWK4GpbC8+EcuBHO1fywttD3rPyt+YmDk4I3FS3XONgRHq/5KID5cDw8Hk6Gk+BEeILazTlzp9jnsuV9y3PZmDv0PZy885T8TgnUXyCy6sHpAnvBHJgNx8AcWAD7wamwP5wJB8CVMBeug0PgfXAUfAiOhrvgGPhrmA/3wHHwdVgA98EJmr8p8FM4FX4Bp8FAZmfAZnAmzIQnwRx4ChwDT4Xj4WlwCpwNT4TFcCksgzfAafAeWAnvhwvgTlgN34HL4D44H34Ma+BBuBx+AVdAi7paCePgKtgengE7wx/A4+BqOBqeCfPhWbAU/hAugGfDangO/CFcCy+A58Gr4Dq4GV4Eb4UXw3vhj+ED8FL4K3gZfBFeBd+BG+CX8GoY42PehHHwWpgBC2APOBHmwklwCCyCBXAWnAAXwiJYBU+Gl8PV8EZ4HrwJboKb4M3wOvgIvB7uhJvhs3A43A+3wE/hz2DgHfvPtb3Nc7a+P9gQpqdrn+7L+BhOgv+AS+E/4XIYree6xcC1MBZeDOPgJbAJvBQmwGtgHvwZbApFby/8pdr3wDT4LkyHB2Ab+BlsDjNkrhb9UJJOX9geDoMdYB7sCMfCTnA67AIXwq7wHNgNroPD4C1wOLwHjoAPwZHwVU1/H+wF34d94OdwAIylngbBRJgLm8PBMAkOga3gX6mfwfAgHArzdD5Zb+nzJrxD56vmkLqT3y7CJ8PfwFT4WzgS7tF54Hk4Hv4OToQvwenwZVgE34Qr4Fs6L+yF5+j8dIXOT9fo/HSj+h+ErKn1uUbqQvKVpOtlfnJuYCa8C/aE92i+tsNyeB9cAO9X/W0PwIvgg/A6uBPeD38Bn4aPwL3wUZ1vHoOfwx3Qo/rXEuDjOt88AbvCezW/ayxdY8ObtR6bwtoQ2cjWsDUUnbdwCGwLx8JMeDzsoPnuCFfDLHgu7KzzaRd4Ceyq9ZYON6pdz1XVdSjXcjlX9Va9H9wG/fB2mKL2LUcgO9mpQ4K1A46FoTKUZdjrdIcdW1nKtVwnqo+bTrAjl6nMfuvwcpVbOiQckWzlqW8dG/nKi9/6djKWQR1cOzskfO9kLdftTbC2YnZj9mOi3iaPmLGYMsxazJa3G+UwG3+Nv8Zf46/x1/hr/DX+Gn+Nv8Zf4+//5ffd7P+vmoME2FHZ//9SiOw/j8Ly667fKjthCgKyKFNs2Wy5MqkUz11SvUplKmpaqIyx/b1S43TCrnvTkRMx33xt/4iy/+pvf+8k/rwly6qCaVSGpdFRwlSV1ix0yP8TxnGmnvn++Xv9/llwGFn/Qkj5HLJpRUbugjLV2xNAOfQ7aYVxM3k3+wI6irvk16ELcG28SoQ=
*/