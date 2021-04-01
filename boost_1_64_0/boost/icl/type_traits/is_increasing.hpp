/*-----------------------------------------------------------------------------+    
Copyright (c) 2011-2011: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_INCREASING_HPP_JOFA_110416
#define BOOST_ICL_TYPE_TRAITS_IS_INCREASING_HPP_JOFA_110416

#include <functional>

namespace boost{ namespace icl
{

template <class DomainT, class Compare>
struct is_increasing
{
    typedef is_increasing type;
    BOOST_STATIC_CONSTANT(bool, value = true);
};

template <class DomainT>
struct is_increasing<DomainT, std::greater<DomainT> >
{
    typedef is_increasing type;
    BOOST_STATIC_CONSTANT(bool, value = false);
};

}} // namespace boost icl

#endif



/* is_increasing.hpp
3+G/KOuFT+plMvKHna3Fe6EXSUJoy8qz+nrDfUnrPmXjBkYhTKA/Fz+LnSj6TjzU8eHFv/ozG9ldPReN4tXsuAO89BbHHgsVGuD0C9UZCk/NhQyPDdXF6gKMJ/tBP4CyuhQ2SpxMCT9PJbwISrBYUYp/cjGcR3IE6uXPvOlG0yweDRJzTO9XBe87kCQ7idNLoFv3EqrRrxzKicfX3CSpDYSvZJK5NTa4UlhABKtvIa8PY4Oe6bWY2GaH8K9vKdPL0fY2aR9uczOoDjUOp6izXjj6dAIEY0rEbwhekjUEB1K6/ihpGUVk4DWHYENXDRfGjRBbMlNNcwZPebkx6QjswyxXr6hXrN8eyhV5zz6TPpQa686VRtKOmkedLKoT+J7icwPhdoFPnB3Y0Q6+I2vIiFzgkaZM1rrS5FpM7WxY6gWNAQ8ruzFtpPlk4IuG3pcDqkvHOlQcEdEm6L4xFFb8VDvBk+LCwXJUMtrngEdMYNWGpz4hGjH/ch5C1U/p//sOs2fTxQaoWgxa526XhQfsFHUcg6K7ga6po+LXC/Io3dTppRIvXk42zrDfSQ==
*/