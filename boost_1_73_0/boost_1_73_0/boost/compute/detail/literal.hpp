//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_LITERAL_HPP
#define BOOST_COMPUTE_DETAIL_LITERAL_HPP

#include <iomanip>
#include <limits>
#include <sstream>

#include <boost/type_traits/is_same.hpp>

#include <boost/compute/types/fundamental.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class T>
std::string make_literal(T x)
{
    std::stringstream s;
    s << std::setprecision(
#ifndef BOOST_NO_CXX11_NUMERIC_LIMITS
            std::numeric_limits<T>::max_digits10
#else
            // We don't have max_digits10, so add 3 other digits (this is what is required for
            // float, and is one more than required for double).
            3 + std::numeric_limits<T>::digits10
#endif
            )
      << std::scientific
      << x;

    if(boost::is_same<T, float>::value || boost::is_same<T, float_>::value){
        s << "f";
    }

    return s.str();
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_LITERAL_HPP

/* literal.hpp
pqvpbJ4maRB/wxuhctkWHMc+etdm1Zcgtg29TRDmFTN4+5hngOFfJIEVHdbpJD1ZJPNlMpsGi56eoWpr2grDWdH18Y4bt+Rzp22vSbU1nVe/7Xu1vq2srjmtBcJZvxHaOKYcNSJNFVe0OJDiP45Zw1Wanu/BhnEQXHWHT9c1J5jWes51mTwWnwlV6sHRcF3O6WBbRwr/6OpYTJaXiyn+GZ9fToIxGi2U871Jx5FkSnngO1Qo5httV87uBPelUeMI+mT4jwWjNeZEzqTcBnTTeZe0acuSAH2BdWsdlHbY0GfFcP9y2/nic7iJO0FhOplgfJ7OyOtvC/xWBEIqIwx+AlBLAwQKAAAACAAtZ0pSrdep7AANAAA+JQAALAAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9jdXJsX3ZlcnNpb25faW5mby4zVVQFAAG2SCRgtVprc9pIFv2uX9HFVm1wBsvP2E6cmVqMcawNBhZhZzKVKqqRGuhYSKxa8iOb/e97brckBJYdJjXrqTFG6r7vx7ndsb/U2Ou/7MeyiRz74c9I/z/CDz7zTf04+iq8pHrDaPSdmf+w8Qs+N2C1w5a7vo+22Ea7vrO63jXKeL2nv0ejDdh9ISHp1w5t/jKiP/HE7Mz2t6LFYyyn
*/