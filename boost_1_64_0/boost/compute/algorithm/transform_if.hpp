//---------------------------------------------------------------------------//
// Copyright (c) 2013-2015 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_TRANSFORM_IF_HPP
#define BOOST_COMPUTE_ALGORITHM_TRANSFORM_IF_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/cl.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/count.hpp>
#include <boost/compute/algorithm/count_if.hpp>
#include <boost/compute/algorithm/exclusive_scan.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/iterator/discard_iterator.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

// Space complexity: O(2n)
template<class InputIterator, class OutputIterator, class UnaryFunction, class Predicate>
inline OutputIterator transform_if_impl(InputIterator first,
                                        InputIterator last,
                                        OutputIterator result,
                                        UnaryFunction function,
                                        Predicate predicate,
                                        bool copyIndex,
                                        command_queue &queue)
{
    typedef typename std::iterator_traits<OutputIterator>::difference_type difference_type;

    size_t count = detail::iterator_range_size(first, last);
    if(count == 0){
        return result;
    }

    const context &context = queue.get_context();

    // storage for destination indices
    ::boost::compute::vector<cl_uint> indices(count, context);

    // write counts
    ::boost::compute::detail::meta_kernel k1("transform_if_write_counts");
    k1 << indices.begin()[k1.get_global_id(0)] << " = "
           << predicate(first[k1.get_global_id(0)]) << " ? 1 : 0;\n";
    k1.exec_1d(queue, 0, count);

    // scan indices
    size_t copied_element_count = (indices.cend() - 1).read(queue);
    ::boost::compute::exclusive_scan(
        indices.begin(), indices.end(), indices.begin(), queue
    );
    copied_element_count += (indices.cend() - 1).read(queue); // last scan element plus last mask element

    // copy values
    ::boost::compute::detail::meta_kernel k2("transform_if_do_copy");
    k2 << "if(" << predicate(first[k2.get_global_id(0)]) << ")" <<
          "    " << result[indices.begin()[k2.get_global_id(0)]] << "=";

    if(copyIndex){
        k2 << k2.get_global_id(0) << ";\n";
    }
    else {
        k2 << function(first[k2.get_global_id(0)]) << ";\n";
    }

    k2.exec_1d(queue, 0, count);

    return result + static_cast<difference_type>(copied_element_count);
}

template<class InputIterator, class UnaryFunction, class Predicate>
inline discard_iterator transform_if_impl(InputIterator first,
                                          InputIterator last,
                                          discard_iterator result,
                                          UnaryFunction function,
                                          Predicate predicate,
                                          bool copyIndex,
                                          command_queue &queue)
{
    (void) function;
    (void) copyIndex;

    return result + count_if(first, last, predicate, queue);
}

} // end detail namespace

/// Copies each element in the range [\p first, \p last) for which
/// \p predicate returns \c true to the range beginning at \p result.
///
/// Space complexity: O(2n)
template<class InputIterator, class OutputIterator, class UnaryFunction, class Predicate>
inline OutputIterator transform_if(InputIterator first,
                                   InputIterator last,
                                   OutputIterator result,
                                   UnaryFunction function,
                                   Predicate predicate,
                                   command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);
    return detail::transform_if_impl(
        first, last, result, function, predicate, false, queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_TRANSFORM_IF_HPP

/* transform_if.hpp
etVYYAJ1ThpLuBirpEFr9vwdY6kuvw9Vx4/u/E/a5+UcbDQWK+C+/yc7d1/9QjHa0W6XcnbPAvvl63I+rDr2UIPjxuIbqf0ZrefqOK/8enCff6/ZqMP98YviOt9MY2mOXZV+br3rYp3Ibmo9d2/Mfo/l3ICa5jEWaO3O/4xljuV6dxjLcNfO4sbSKlGD0orRnjqXN+Y/f1QyFr3C61o1Yyk7WW8tY6njmUt95ew+OzcxFnbP2SnGIu77V/cbG7CIuTxsLP0g+/uINMjHGI+rtpuM0UUa/EnfHrL7k7X1Vs6nqf0A1daLe3qQsdiDjDHUWNL9NuUo2TVjP56X3aeMO1GauvcuU2WX6c7/pF8vxkhIv0LUaoGxUJI9WiKWgz1frv4WpH5vKG6Q7G1p8DDr+MBYwrE18v3Anf9JA/f+cot8Q7xGbFOPXqQGO+Wbwb7tUx3uXnZIrCzn75hy/pTXsNPSbwnzy5B+9Xid/E65jGF/f1Zt7tznN613jj36Q74bcoNdk10T5vKfajvHXmarYjkPp/a5jYWWcV7yGwuOYn6FjEU20q6YsYT7HHqnWIRzUM5Yyqv0vdtY+s+st6qxDNfLsLH4+7Srp5xfIWtsLDaHtbVQHe79USvlspI9eki1vUXW3ljaEMZ4TL7u+b6zsfC79O0uu2Ks4ynV+xRnrb9qO0D2jLFAHc7pEGPRd1nHSOncgTM5VjFKUIO4NFjM2XhBc3CNMzRTmlZzf/+r/LKxv/O1XlvGXSzWn3avKb9/qNVKY5nfso63pNUu3j/el90M+n4sDdzfp6xXfqWo/WaxrMxlq2ZjB3XeIZ3d75rvVS8X0zddc+DOVI9Kq268vpxS3HFk57Sey/mCdCnLfvykGFtp96t6dJZa/S6tbtD3b2nfmH27oXpHcA6yVrV63fvGXMYyDuQEyye7K5yNgmLu+a+osZQIcy5lLOnOJ0PG4hm0u8tY5gCyKsYSdZlzTdl1Z851jYXd36U2EnOfa5sbS3fP/C2Vn3u//6DsyjFGO+kyj3PQQWwS8+tkLG0cc+mmGPs5z72kX1f2qJ+xaDv6/k/11mQuMemyn9qPkPYb2bcxxoLuPGKCcsnNeqdoPRdjhvLbQrvZxiJzGeNl6exyeUVxO7Pny2QXYi4rlMtK6vKmYgzMAvae+uHOvj7SDH1Au3XSai/X+1RxD5ClyW486/hSOX/M9fbIzt1/D6rn1Wl3xNha9/8PnTQWcnvra81GZ9bxrXrelOv9KLu9nI1L0iDK9a6otue53l9iE1jbv2Lu70myVLNrSRn2I6exkPt959uMZdbi3g8aSwyjpkW03mLGKCm2jrWVNZaewbmqaCy+jjnfoxjruF4NYxnu+5N1jCVLMkZD1eH+b/VmxtImk91nLObe5T+gesdT57bGwu5d6qOqY5Q7/5NdnHU8qbi1ea+IKm49at9X9brnxKdVm7uOPysW4nVtuOIW4XrPGQu6XMarH0nWO1naV3R//ysNnKYvSdPbqMs82TVifotkl8keLVVtbjZelwaDuLdWG4tsYS7vql533081luI+v32iXJow503GAis4p58rPxd3u/Rr577/p/WWU6sDyqUd2Ve3auN6J+TbjnWcNRZ1e/Ub2e2m7w/q0bvM+aJiuPeIl8UmcL0/Ve9r7vxPmnbibASqG8vHGcohNo7r5TUWrM5eFjCW4WaosNijnIMSxlLd58syxqI7qXMFYykjWW9lredyqV5dn4/Y89parwRno4GxWC3W1lS5uM8k96ret935n2LEqHMbY2H3N7wR5efeKT1hLPGa+/6fYhxlLj2l6Qpq2kc5T2B+A40FerG2warXzf0wY8lv2fPR1fWszPw=
*/