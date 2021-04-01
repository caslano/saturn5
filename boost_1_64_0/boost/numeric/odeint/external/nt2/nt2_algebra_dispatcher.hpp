//==============================================================================
//         Copyright 2014          LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014          NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_NT2_NT2_ALGEBRA_DISPATCHER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_NT2_NT2_ALGEBRA_DISPATCHER_HPP_INCLUDED

#include <nt2/core/container/table/table.hpp>

#include <boost/numeric/odeint/algebra/vector_space_algebra.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>

namespace boost { namespace numeric { namespace odeint {
template<typename T, typename S>
struct algebra_dispatcher<nt2::container::table<T,S> >
{
  typedef vector_space_algebra algebra_type;
};
} } }

#endif

/* nt2_algebra_dispatcher.hpp
XuKgQz5ozFeTyMv2yQbbcJdXJlj7chU/F9DMUFGnSrMaznr0VcBBV4WDVCw1FJCterlLpk4N1j3eVMbLOy9WPddUP+4N+CXDQDabWQ+sCQWFhIa5+ikQQYiMZ6nvbrK2h+0hz7Z+FcpfcCxwVKH8ewfWRU4SnSrzpZKAh0HPuKk0s78x3MH6+zpuqPwxVtsXdmAKkl8sbrCjCrPDwGEpHVmL48TKtU4RYUTYeSNmfM5VFC5+1hJo6E4jRp7JGxoQCzEjPjVdpmDBQL3mfYxOh44pibnPUJVFPRdDnVU4w5Jlo4xei9FXJ0KJY1RCk5GP1yztt+0u+248gkciDUbTn6cMfw3qDe9HQPQbvDtZQ5HkitobeRrLoxbMvWjX9DxPAkLaUVHABDh3QJeV+vdd1hQ2qlQihjGzlB91ZTVMDTQfH0S0HdOydePLimR9tT6e85eXng1Kmy3FcocZ3jV5nyOo21tekbHTggdKiCvNkF90xulrok7MvLFwtpksYmaC80z8IF/cckdZLNU5Rm5L9cXpCTqqkRGNh/YuOEIKVpGj07MDM+KyrklyWQ==
*/