//
// Boost.Pointer Container
//
//  Copyright Thorsten Ottosen 2008. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/ptr_container/
//

#ifndef BOOST_PTR_CONTAINER_SERIALIZE_PTR_CIRCULAR_BUFFER_HPP
#define BOOST_PTR_CONTAINER_SERIALIZE_PTR_CIRCULAR_BUFFER_HPP

#include <boost/ptr_container/detail/serialize_reversible_cont.hpp>
#include <boost/ptr_container/ptr_circular_buffer.hpp>

namespace boost 
{

namespace serialization 
{

template<class Archive, class T, class CloneAllocator, class Allocator>
void load(Archive& ar, ptr_circular_buffer<T, CloneAllocator, Allocator>& c, unsigned int version)
{
    typedef ptr_circular_buffer<T, CloneAllocator, Allocator> container_type;
    typedef BOOST_DEDUCED_TYPENAME container_type::size_type size_type;
    
    size_type n;
    ar >> boost::serialization::make_nvp( ptr_container_detail::count(), n );
    c.reserve(n);
    
    ptr_container_detail::load_helper(ar, c, n);
}

template<class Archive, class T, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_circular_buffer<T, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

} // namespace serialization
} // namespace boost

#endif

/* serialize_ptr_circular_buffer.hpp
vrYEwU+8hQQBf5sPyLe09oa7gi3diZYuchyEbPFB7XSrZOvKUF9RSUtruKdl1YzillWzSlsqagq8S736GyObMR6Zk+RQLXyxSKUqCtqiUdX+YKc9AwRifBapRYNCPjMWBuDYXSY7KLDyGXxF6UC/v6i4dFbprJI9Zs9sibQeGFNzo2Jrcmi/3cpvfZG1gORHlG/wFUSDfMPwGzP29Lb86dU/iWHUFxMuYNhYKNFivnqYtjP+64d5nT9UGE8EO6PRH6nR9sM1KiI9bY1Ng2p0BXo6AtFwS7inras3GMJHZVhr32TN3p6gSnxtgjOx3h4i/ZDq78drtIRnzCr9ERZT7cdrpO+ohhmXNVTba0u/N8hULNBAT+EEW0R1R7w9thzQwU9urGbV9+82awkkurrbBy9cMsO7CmXg05C6eV0oUbW0pa+kYOam6xDKtIdDwYrGJlNHqnQw1BcM9+nhe4JR9N4tB0za9BUNM15lg199JTXSs+nxFvtMjR8crS+efoS2SE97uEO0dZXDpE2XxdvEyOlrdP1QYcisQ9WBFx8aOUi/m5uSDrOJQvzSsyA996wPbcVbigpb4sGVP6Ue/1nlP7kBijXAx+w89t7/aAdLTAcruzdrg39cPH5ABNw9yHLLE/l9swr9jRUNsVC0pTxGxlx9cVSN/h/4EI+996nO5N/U6x9VXnyU0z31omQcw20tkcBKOqf58j3yp/dEuiIdkfzpS0r4b2n+9Ppi/ovz38D0/OmV/tpyf21Zg/netyKg8OU1lVZRhU/9bmyq4FdFhb/R62tqrLa+qulr8FbMLfJ8YtZrVVBqvnTp3CLVajEd+ZdU180oVj/rmubKf6ifSxtUNV9TzWbUKqupqV/ir/VV+Bd7G/211b7asqaKBU5JdZO3sYzPlfsrveXN8/013sXemjTVGpvrmqprvf6a6vLGssZlsoYeloZldf6yOtbOH1Dr6n3exsXVFV6rRuUM9W26fzprrmqoZ7UW11hKZXW9v6yxvLpJ9c7sK72aT9VV1d5GxcpK7+KiQnsw1WzprFK/7kB5JP0Hq25u4C9ducbqXPKncFVhaWGxQ632KtLsQtMtNUwvfAqe2mpf6usqq60vobKymuq6+Vav/vLm6prK2rIKvhrPB+PnLuZ77/U1vsqimY1NtbqPyspqxW8fbeda/2KEWUkZ19u3oLpB1dV8V4Q67xK/r3KRHqK+qqq6orqsxhpJT6bc21Sm/6haqreyobF6cVmTV1fwI11zKyuRvhkzS5XINWtR9NYt9lc1VnuZ+7K5jcC+cJfVnj2sq1jg9y2rq/BX1LO19Le4rKYZjmjx1ayY342YexfE1Q80orYJkg/NaJvTzxfMYv6E/rudz5q3kT6jsJH/gvnTm1hWf7CkcOZMsV4IRTOL9e/iwiLrd1GJ/r1H8Uz9e3ZpofltlZcWzrB+F++hf8+aMUv/LplZan7vYX7b9NnWwLNpX1UdDLYGenpAnJ38q8KqUUqPy7v4L0qT+VX8N8DCGpSqW8F0PNAeAu6oTwXToqikuHSm9buk2Po9s8T6PWsP6/fsUv17RmGxwtLFniFjOHXUZzfqjIWYRJ9bZGc7uXjy8DrXrvLnKj45DR6pPJ7Vz6xZ+vfMktn6d2mR9Xt24Uzzm/E6evm4HPMIxNo651SXoQ8sd7Phf5A0blvCrzvxd4fj3eqDdIpJ5eEeWLOUdahzwTHkhrKt0ysiXU6vdMbMxDwN/PWZOXXNMrTF0KoyeL4iw6I1mr2vnNOCePRYZ0bWn/Gu6RrQTy8qKCoobJ/eF0cm9kiWYZenx5EwPnMcC3FwFA+ZGp4qp08cX4tpt7iipUmvutbHn0UlBUWFBcU=
*/