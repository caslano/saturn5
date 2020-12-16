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
Dya+l1jGlTF/EL7LPu7X/k8c5J6KE65JHL/jqjb88l5ucFqg/MLVB+FLfZQ/247P7kNRTOXTcW352m+seTkZ1f4rn1fpWBWkaupT2tyDeIrWp4zKe/Pfa88lfqxU0thu6gQ58+FgfDKHKz4wn2u3n+nza/MUx9sxMjBVHnYGNTms8/7eXwmH9qaOz27vUH8Scqaa+WgfeM8h8ngqe90T/+t2vHH0AHPx5FKMuFljV25XW26zLweqzCWMyLstV/vd9WU9j0vHrHbcpiz8ePz2PD5/emtnyUKW496olPb8vh2HhqejqXAbMs4SmxdLm6jR6O7RIYalTSOTvI3CICLc2g0+FyXaNwmRGWizgJSucc8XAm6zpd7aYYixh0zXr68JsCmnqNZOJsWmvteGpzaiY//bPO7qaHDz5lCzX/R5YZ0XAiysc/1FPqZ1cf0rz8rv8HhOCbzzK5K/eXi6CMYTnHGW23jt0cun9nePp4RRWWP+R4BXmXkPTClR5yerbEyEVownhHsVXec0xzpsGMv29vzcuNS7TsjprU8Vv+xjzZDTi6E1Pw2R/OdGd7O4DK66/jZ39wiTaEx9SNc98ziqDTI/uVc+j8y89+Qch9MCNE4TPLlviDv7k7Xl+1lcohCdv9ePc9juluyk/i9xssOZFEMHjQ1K/Qv/8nlq4JAmRdY3+Rwx+d0yd/1KgJdthN3nv8NX03LUuVVMn8w75gOcIcSb17zdw7L2JmUU/TxSewv2lxVvDnBsrqL33mIxFvfpyuoA52z4e2sTwZv9G7RR7fbfPse1Ueqh689+XlrYkKxv3P+uDicLb5/3A/3r+IWWHHQeNMc4KzhjaOoWBqq8N18RP9eWoweEyZh3+cG42zY+1uMmB+VW9wf752IuuyjL1XJaU9YlXJ7zEU+Pi9PyRQdzuDbDQZdfYSbLiZqubT8Yl6L9eX9vOy6mMo2hiE/6gPCqeIBxf2938mDXtyz3Ou/p+3LKcHgsYb/eszEv28M6Vv8XLs0UbscVB+fSwyKPfp+b7eGSy3Mm5mV7WJ9nZLjawy6/uZiT7WFt+8G5FK1c81Tl5vew0bUQ1496LMUeiXFPDDGxYG+9pMFZ53C2bdHNPnpO3boAow72hQ/jndGY5eBLveesIc5MXMfFhmJOBdPzHPz8TxUOT9aIBCxDYh7FKbv1porKJsDC9/j6td2Xjo0OakxxXnp9K2/l8zJmsEe/eH6I8RBC8jO7HBa+lzVbluvUYbWcYMigtpsJKdvyvX0bu3yufanCk8XsBQHOk4Bm8Kp47+MV17O29HyEhd2Cj6anS+muCODdlocG5fLSP+HJWJ7Pow90jOrI5bAyPpUGZhLz5fLShSDf93VlePpUI/CReTwtV5/7PMHx2AznvRfTCK8HejBzYYihB9qHWq4tFrfFszFZA1Y8Txw6Zikvr/r6PlfMq6BTPMsb8d/tHIk5aVtFL0Zz8VQ5Zczjszfm4aBaOXnP5cccx764wyuO/j7ErosE1wM91a/o866A5476MuPy3H58lQHffk5pcw/r8L3b9KSPSfEvI3kconp/P1VePtGexrnjDm9xdvX2bSut7lxPqy+ZYh4idbl/Lo4Aho3GUhEHRuKtTXc9OMJdDv789T5HKafvrO3dGzbL+TY4RaJxbx6ax8XJsh7CFF/PZJ3P8oLzcOCqnuRzXdl6Dst9szx00hKV15vDg7I37Ublzbbj0U3G43XcL8sj7hmGzIjhlZvHm57ggRwLAB6vkcOreO0VP9iR5WEYFOrpfZZjD1do8rx3Lz0eI/7k+OgQHkTnf8l1hynO0zNUxc0E1U4/luHITE7G1U/4nKHxJmcAbZM8PpnBKSd81tA=
*/