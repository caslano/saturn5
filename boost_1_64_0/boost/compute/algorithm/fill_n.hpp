//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_FILL_N_HPP
#define BOOST_COMPUTE_ALGORITHM_FILL_N_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/fill.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Fills the range [\p first, \p first + count) with \p value.
///
/// Space complexity: \Omega(1)
///
/// \see fill()
template<class BufferIterator, class Size, class T>
inline void fill_n(BufferIterator first,
                   Size count,
                   const T &value,
                   command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<BufferIterator>::value);
    ::boost::compute::fill(first, first + count, value, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_FILL_N_HPP

/* fill_n.hpp
EzOgAffUPR3S4UTKV5Im6SHp6ifDrN2yfx96vg7jr1efkyUy/ehzUqLGGCetv/Q/sWUsaXE8CwboWskO6ikXM4uKUP77SN7k1Gt0zWyDXFpRLLtzSlmvC61X1LIO++ngum62AdTr0vZn1aUsMAjSu6SNpOEnIyNttKb3iviNPj3dRZ8+WvPYrn58HmcHxwJReRTtq1tO+chvj5i8bjtJXrlu8jqIMn6t3j+X1wrPvDrbzIEGlnxe1fNDH4c/5creqLwy4Cnkp25xUUX8ulPNn8r3NeeBJr6CnV2ZZC1pksibcYr2Leqnl+n7feLnBjtqT0sU4iH5AiPfw5xR93ex30EcRj6sKzfPus9F5hn2EUkUf1NNOJ3M+fVl+3Xdg7k3y5bMX0MYur/lpyJ/rV1q11U3VimInzGsSmzvPEMfWbNG27GmkVoi6dJz5CSv95CqJB3LmnTErts0fW22+Jlhi93I94n+rWvWYHYQ2WU862aoGzkQt095hj+KH7PmzfiZK9f7Uj+6mbPmh4nbRHkauoUj9dekJdFtfaHZA7Sp+BvF/cIeVYad8Odce6hnlklZPs+98+nzKRxP5/C94iO3yqwTaSRxDCEO7FFxtKAPHU7b6kjbziNjDeSsnn1p49M6pI3ivJ7hNDJ/KqfHt0lbltYJh1FJCcHj5CcnJfgzcRzBqC8hNXqNv8arZfeSxNvVrHe1JN4tPINacIcGiL82Mfe0BLHO4i9P10tH0tuOEqlj/JSafuJJkZ9tZWm554j8d5FvhY45x7Ucfyl+7qUUA7Hl6BjjzDn5M8Ksy8K/Y11LgcsarFkwU57f2vbN+wVmT1bat75fYNy0Datsuem7pE06+q55jfgT9e7rBMzTFFLOH0zfpf1W4crSbxZ7rjHSdw3UX0/adIK60UuI2xm49NS67VwXr/dF/U50WyvFfTXXXddkZ8D2cn00vxJsjUfXDkqXHRkPTBW5umq3rbl/qNlvzabyXPBcO+T87aR5c+6VK/lxvN/BIl75yG3Qd6jnBseoUeVfvqqCrYCLJN/r4p8bKtso6rdAuRm/XyzXMk6at0zn87089n2g8ib6zruNO5T9o7hp2xzpNM84r7SqfGuzlvfxf7B3JoBRFWcAfrsJEEiAJIRwQ7jDIYZTRIRwGjkDBEREEyABAgmJEBCUIygWLCipoiK3ioACGgEVFBUFjyoqWrRUsaLFSi1eeNEWtd/++++8fZtdSNTaK9Hh2znfzLyZefPeP/OP2Cu77pa3HlfI9qVtROPXN2eN7RX7XSHb1WRzzWgzPhS/7XuXqhC0rWWbOBHStqZi3yL2DXxBjSQMbqSTIuncEHStnnmemTy7zFl2wb6rfiFhLrP3YIjdfGfVa52v/mrX/Gs7pwB2G/9W24TvG0+UhO/u30akbMPJ430S9ivrJdLrxvgeRcUeIVJNGd/3M6pXrBg5EFQIY1hvHdkMFeMVoipWkGG9ZWRTRvkwhvWz3oOnNL9B7oGzPrT+X5U8fefnl2Pq6hqJW8uU9Tdi7xa0bHniN5arNC/V3E/neo5+UFf6cOh+nxCi3ycGWZOYVGJNovOcjk51g8+bE96RfpaO3CTYy0Gw+bLGCT1fVv9z6gYv7Xy4g5bhmJahviZSD/MZgVO1DFQfkTq2t0Lr9New9UPq7h8u/nVC5t2cl6B55xrO77Wa1+OayUf1u+V2zFjP+PuOWfcrc3e9s4Fzd/N9+RYJv9Gqyr/nmfPINR1sZj7uN4cdaPxTGPcjdE7vslaIG3Yz759u9vKkmjiPhpxHvSX+rSVv2Sb8SrnGKKunzq/0Ooydbvbp5Ou3rWxz/XsIPbfknEvHw6USZmvQ+dWL4jdN7aY=
*/