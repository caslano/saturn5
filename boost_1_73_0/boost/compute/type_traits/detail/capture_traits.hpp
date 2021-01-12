//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPE_TRAITS_DETAIL_CAPTURE_TRAITS_HPP
#define BOOST_COMPUTE_TYPE_TRAITS_DETAIL_CAPTURE_TRAITS_HPP

#include <boost/compute/type_traits/type_name.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class T>
struct capture_traits
{
    static std::string type_name()
    {
        return ::boost::compute::type_name<T>();
    }
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_TYPE_TRAITS_DETAIL_CAPTURE_TRAITS_HPP

/* capture_traits.hpp
HPI98isSYgswCiElkEpIbaQJ0gbphvRFEpHhSA4yHpmGPIo8i7yErEI2ItuRvchR5HPka+QK4uAj/bxIEaQMUg2pj9yOdEB6IgOQIcgI5D7kAWQGMg95AVmGrEO2IDuRA8gnyFk7X01wnkKZO7ImjEFaIp2R3shA5C9INmLWgYmRUr65VVHVmZdlnPgeVfbDs4ZImKyXqNdcOUt4p0iTiHwr0ec3rnHomg+t9F7P+dGu7vHU
*/