//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_FIND_HPP
#define BOOST_COMPUTE_ALGORITHM_FIND_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/lambda.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/find_if.hpp>
#include <boost/compute/type_traits/vector_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns an iterator pointing to the first element in the range
/// [\p first, \p last) that equals \p value.
///
/// Space complexity: \Omega(1)
template<class InputIterator, class T>
inline InputIterator find(InputIterator first,
                          InputIterator last,
                          const T &value,
                          command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    using ::boost::compute::_1;
    using ::boost::compute::lambda::all;

    if(vector_size<value_type>::value == 1){
        return ::boost::compute::find_if(
                   first,
                   last,
                   _1 == value,
                   queue
               );
    }
    else {
        return ::boost::compute::find_if(
                   first,
                   last,
                   all(_1 == value),
                   queue
               );
    }
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_FIND_HPP

/* find.hpp
UaGA7vFMsxgK77MGtDzZMPQDWWPd+exCaUDVs7kJUq8koihzN3AteUhlXWQWdCOBgUpFj6o9ythQCrZ3GLq9L/lw4jtdMNjnpn94nw+gR//110f/rXoMlLvASylgrNArA+uuzpQUgGX/wgfjcAA0vkyLaEZH7rZszC9VqYTReohvpAh9t2+n1VPT4yXpmt9o0ib2VsuOOyO7cWScL9oDlHvLOAyp2ZxiVDpzQg8SDsT3+H0HGgkON+ApvKKgTQQsPluqPXvDLIWANBQaPlbMLIxzCC12wkvOHxtQye2f6AsAzRf1Q87qlND92qeQsFHoRfIUlQg682kfBCiNugEb6sY/2007IZNd3M+ygVTaahSGsEoO1AgLd7/C995FHbUSfi/CNwCOf4Ei3/XoQrO4UPDxXhpKmkVS9igvxPoWXHUrfR7aMlwYVzavlKaw5rK6ushnE6Jx1g51ExiAVw1K0Xxw3GfkgmfZfC02ojo9+uk3HIuFS6YdPk6EnACYecq0bRui6k5Dk3hJj/UK85zXRN9unYPe7tpbntsZsQX02w4OxdugFsauzKhd5w==
*/