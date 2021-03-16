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
FWygYCMFKxfsMsEmCXatYNcLtliwnwu2WjBPsN8K9t+CbRVsu2D/I9i7gh0V7IRguP7IWLZjsFLBRgk2QbArBPsbpHA9PEs16VRAdc4w+bplmHwFgl0gWPEEdIWZ6HpfNjc1Lx14GGbn4fqagj2lhXGac2jXl5DPW9pBh+nDyZa3gGYfbn1N8ZE9e6Hq6p7h2JjCcKy0wI1NKDYTl5W4t3rYqylwvZpiCm+aMTDedBakQtVTsQCar6WXwX7Gu7E=
*/