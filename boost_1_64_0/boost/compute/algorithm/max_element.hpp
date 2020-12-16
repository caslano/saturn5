//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_MAX_ELEMENT_HPP
#define BOOST_COMPUTE_ALGORITHM_MAX_ELEMENT_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/algorithm/detail/find_extrema.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns an iterator pointing to the element in the range
/// [\p first, \p last) with the maximum value.
///
/// \param first first element in the input range
/// \param last last element in the input range
/// \param compare comparison function object which returns true if the first
///        argument is less than (i.e. is ordered before) the second.
/// \param queue command queue to perform the operation
///
/// For example, to find \c int2 value with maximum first component in given vector:
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
/// boost::compute::vector<uint2_>::iterator max =
///     boost::compute::max_element(data.begin(), data.end(), compare_first, queue);
/// \endcode
///
/// Space complexity on CPUs: \Omega(1)<br>
/// Space complexity on GPUs: \Omega(N)
///
/// \see min_element()
template<class InputIterator, class Compare>
inline InputIterator
max_element(InputIterator first,
            InputIterator last,
            Compare compare,
            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return detail::find_extrema(first, last, compare, false, queue);
}

///\overload
template<class InputIterator>
inline InputIterator
max_element(InputIterator first,
            InputIterator last,
            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    return ::boost::compute::max_element(
        first, last, ::boost::compute::less<value_type>(), queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_MAX_ELEMENT_HPP

/* max_element.hpp
f0eI/r8rRP+vC9L/90LaKm60VY2fYfYE2G0w2aGX1bQTs0aiq7hrG2A9RCepa2QZvjV0On68HKcyzAhkY8o5hIkvt8cPefxpm3lVxnKO9rXHDQ07SPf90gcvk/3g7s+tnWZvUMixxMTvJ/FnYx8l9g/cBXwoDjmemHjnWMl63fPE/i33H9G4GOvO0nGGlWLLZF9JyOfkDJNWqtljki72T92L3Kx3sfdg5VTm2G26k5Qzyn2jNdZljz+alo4hO4I9L3Vsmybx33C9RD2ZMSgg/q4gz9B2Op5cI+FucQ92ZVuPu7KsEe6+9vM1IJ06v7EpxjmWyfiwRvJyh6sLX5fb+fqsuFW7ltKajlgDKCXps5zUp5dttaTfRN1c4jZN6nqiWS8/VcIcdgcZF81ekekS5rfuC9zNG8wBEnVsnChh3nVf4la9BAHjZwLsJ/ltI/XTGnuNxNntjmLvfDd3d2u5e4DR/fGUhB1CzXW33sYk6zr6MeL+B9cR3PJdKQFr5HUtobe9ur9vvYRMiHYm7r52FqP5c4zR0icvkni/cvvvOeLeyPjtjGOX6RLJT2sJNxj7XMbFJL85TVfoMd0wf8T+OSbLbyzsDs/G9PAbD5N1PMRgxzRCp45nbOTe+o+N0q9flXkJ44GOSRtDjI21IcbGbSHGxh32Xjvtc4yjQeZGdc65UYO9n4SReqsMGA/PkXqV/Iv9dmO314sd/ArO4c6UdUyvX5V/7b2tP3n0aKvcN/ev/3Hv01+XFHy9Vaj1X6HWYYVeF3atrM/aNyenVdWPe41796lucTPH/ql5qHVnodY9hVq39b97nnfw9Winv/7rTJ3zLeuZfO9e+u4bE7CeqUr1Eq+Aw+DlcARcCRfAK2A2vBLWwNVwI1wDN8F1cDdcDx+DG+Be+A3fugQzj5f3Frl+b6/cVH7fJpzHvhnOh1tgJbwRfgPeCq+D2+Ft8DZ4F9wBH4R3wpfgXfAQvBsegQ/A38PdMFbX2STBR2BH+D04Cj4Gp8C9cAZ8AhbCergEPgU3wKfht+AzcCd81m+9zc91nc3v4c/g3+AvYSc3YwQcDN+AY+FheCF8Ec6CL8Ec+DLMgz+HJfAAXAl/AVfBm+AO+Cb8AXwLvgzfhofgO1rf5WZ+I/M7qe9z+Dtf6ztF5b2d4VDYBY6GXeH5sAeconLjEpgKq1ROXAv7w9vhAL0PQ+F3Vd77PZgOfwTPhU/D8+DLcCR8FY6Gb8EM+Ec4Bn4GJ8B/6nWiXfRt2AlOgUPhVDgZToOL4XS4Fs6F18P58C2YBY/DRbCJm/YHE+BE2AeOhaPgYjgRLoELYQlcAZfCK2Ap3Krh6+A4+DhcAN+EC+G7cAbcFNG4s5uDyLe/lrLt8QxA81ZH/Edk3MffjLRWce1AWXft6ogvRd69h3RDybwPrI740uTe8cdDy74j10T8R+Xfe+47QzLwNRFfmRx8P7Lso5i4w2GZdvgX/oV/4V/4F/6Ff+Hfmfp9NfJ/2cf/hfX/e+T/MX76/FPd5pwY+dVjXmjJ+/AiW/aRiep27wmS3u+LzcwZ1xUq/9DwqkdwJvZUsT8euC/WfNPtLv6tVI+IxucrQxRuEgbba+IWhZ0wxh7t9z06z/5GLH5LjI7LTLF/w2JWLBsU/L6X5wzx0x3eVcI96edfOXSAn+72c8T/sUafvxfp1besen4b7Fk29X5A1128j+nisWNOJFIPRcHPD7AcOtRz/c8O0DipRn45SeyPW82MDoXl4jfZhO1u5LETxL7Pr05Ljd6VLPEr51tDE60vtEuK2yB/mYCRi+aI31XmfGi+uhgZ9lLxi1a5Dy1H7JdbE+XMA9XJovutVaed0dd+W7y9n7zmFPo=
*/