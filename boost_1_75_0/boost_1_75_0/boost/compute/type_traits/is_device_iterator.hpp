//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPE_TRAITS_IS_DEVICE_ITERATOR_HPP
#define BOOST_COMPUTE_TYPE_TRAITS_IS_DEVICE_ITERATOR_HPP

#include <boost/type_traits/integral_constant.hpp>

namespace boost {
namespace compute {

/// Meta-function returning \c true if \c Iterator is a device-iterator.
///
/// By default, this function returns false. Device iterator types (such as
/// buffer_iterator) should specialize this trait and return \c true.
///
/// For example:
/// \code
/// is_device_iterator<buffer_iterator<int>>::value == true
/// is_device_iterator<std::vector<int>::iterator>::value == false
/// \endcode
template<class Iterator>
struct is_device_iterator : boost::false_type {};

/// \internal_
template<class Iterator>
struct is_device_iterator<const Iterator> : is_device_iterator<Iterator> {};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_TYPE_TRAITS_IS_DEVICE_ITERATOR_HPP

/* is_device_iterator.hpp
ar0u40vClYRrhHfcFoqCP7iSKtdR2UeFebExw4vt8X3cFag/0JF79bC1TneqzVazoV+uTLjnRJlwit40/OQLVPkFlbDlzqkTa7EI/b9OD2hC33fBgwgcpnESavlbqndXR5/VE9arepxWb8wy+sKqGsIPhdkTztiH88PDVtTjec6hm80W9sR5VjTA80w5d5T5YUOD4y6PGqDBN9MrRhbaT5V/pPIylbgTdiWfsaWeQmxgoycFMc8PAeUYSUTR2D97X55Yc31Y9dvNL1mdzoWR86NNsc3RzkhneMBuJqF7RHeE6yPNJ8xVmS64uJLm3aXfrq4rOT6P1mutSu4xu3jK1Xa57V5ZHYUuxx2Dc+nm89UYgw3V5ZaMfZNa8qWQ9ZCercvzOHniPN5a7RvPO+nmbxnWN6uD4/mvIYdk+19AQp15vb3kh/U63cyyAevdCljVWp+hZZ3PKfPubbbv/W66KfH7/Xbw/fv0lKeDiquaIx5vvYl+auSPL1DlCio322bNd15H82XW/LUesJ2xG8LqXR1+2rpLbSFpbYB1qCR7VLbtqL9tP6SbX3Dbnqlo2wPOVbTulpp1Z3jXGNHruSoBva+BFZnl2zsNdPNxKu62aZ9ltk03/adrd36OGve69m+a/Zb9M2txSDVq8E1pe6SqzoaMsrp2IjY2d8Tg6JcIR28jHD1extHHG7pmE797u2qq+oriXVCmS7fR9w4Q
*/