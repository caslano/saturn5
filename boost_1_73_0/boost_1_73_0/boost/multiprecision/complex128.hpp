///////////////////////////////////////////////////////////////////////////////
//  Copyright 2018 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_COMPLEX128_HPP
#define BOOST_MP_COMPLEX128_HPP

#include <boost/multiprecision/float128.hpp>
#include <boost/multiprecision/complex_adaptor.hpp>

namespace boost {
namespace multiprecision {

typedef number<complex_adaptor<float128_backend>, et_off> complex128;

template <>
struct component_type<number<complex_adaptor<float128_backend> > >
{
   typedef float128 type;
};

}
} // namespace boost::multiprecision

#endif

/* complex128.hpp
cJQj5O2HadKB5xTrzFx76FXinpMLAcMHU8pKcrlGGRzT+6AjPFCO8kF/gzKZinlO6dGgf/QyK4uT7Hg0/OVoOPo1TV4VBTc+uxZ6zi6nuxVuSl4b7Vn77IL13C9yGg5fRpvmwkujcyqUcbyNmq4ajhU++t7C1yr5PWi9yhYsUBc6x3eSXBjLNcnGhZpKo4wlJz2Jmv0BFUY7ILMPlkQpG+kKqefESsLpuEQCsQyuNiVuqRskS13IUpZBewqelLgDPLHvoJlqMdeChJKfgzikW0+sZQ1sqmX8ZYmjqA/oc5AOQ3LehpL4kW0hvYgdUlBK1IXpkGOQdDLe1ELKBsHEAoXXqMl0DeAqf0hvIqQInknagEq6XqUmCMPygnXJFo3DsDQqNLiOUQ46JXaOqZBKbRhCQ4GqMJfCk44FUSMsDsEe0uQxTo1DpBEcmKIQXCCuCI2M0kMGumisgSh1ZDEyhUuLoBoR+yZTVbKQgkqGqqK3NiqWISJBEnS4Na+hhtwjZpT9Wt6t7l8rGaff6b5oDwjpNHqWLLxvkLA5jiuOlTMeT8l3YZ6gtscVAnZ2pEJOy7Pk9e31xWx6/mFyOjjuDm8mv92+nd2c/zk5HfYHo874aXJ9c3758bQIVmVBS5+1jyS+jgx3OsyxLaAD
*/