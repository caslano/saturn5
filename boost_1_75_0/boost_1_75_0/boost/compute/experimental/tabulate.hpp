//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_EXPERIMENTAL_TABULATE_HPP
#define BOOST_COMPUTE_EXPERIMENTAL_TABULATE_HPP

#include <iterator>

#include <boost/compute/algorithm/transform.hpp>
#include <boost/compute/iterator/counting_iterator.hpp>

namespace boost {
namespace compute {
namespace experimental {

template<class Iterator, class UnaryFunction>
inline void tabulate(Iterator first,
                     Iterator last,
                     UnaryFunction function,
                     command_queue &queue)
{
    size_t n = detail::iterator_range_size(first, last);

    ::boost::compute::transform(
        ::boost::compute::make_counting_iterator<int>(0),
        ::boost::compute::make_counting_iterator<int>(n),
        first,
        function,
        queue
    );
}

} // end experimental namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_EXPERIMENTAL_TABULATE_HPP

/* tabulate.hpp
2Yclf7F9+FCJfWiK98r0wJcq+zAE89XHsg9DwI8q+7D8T9qHLtA/de3DvOeY3/5h+1BP9JyWfw/wv2Yf6kOf/qh9mMTbJyrsQwPI899iH5qjnf/X7UPdv/k5La9f8Zgv/m32YQ7vxxGNn+wy4T7p32Ifxm+v3D40BRoCE9OhbxHY3wKZSIpaQD2gAdAk8o/Zh2I7rfQR9qW49Hcqef8hUTHdA+kzagvpLqBni+jmoOeK6PyVqua5b/4y+Yf5zagiv/FK+A1XQg/6h9uXq2b7fPF9WmXvM6t7Hl9Zfv48vrL74vP4BSrK479Lquy++LukGhMo8u8Tid/30f5R8ftE/Hs92WI6rvwq6o+y+pW9z/RH+Sqq4vtVH0se5WRbZ1ATQBo9z/M4G9gRKREbKghK70ERUCkREZAakSbSpIZQEhUFBAGRJjUo0kvonUQE6RApIdRESggQSIA00s+7m5u5mfuxu99882Z2Z3+8b+bNe4D7MvAG2IiSYIbDECxyjgoXOSOTleAF6tVvCYPsad6DyRUNcDJHbWJbOlwQATwQV7EbscPNrfO4gw47vksjCAeOZ5asRBRBE73a3Jz24DkFjgVXNgYMoTxItPIxXLnhLcnnjwGkHMVuxcm/AwwMpSP9NcS4D3qqJBf5F7Zd/zKJTAwy3xMkXltqzT6ldMFvW5qn2VxDaP4abGu67Snom02ZrLcp2urndEwhXsRK
*/