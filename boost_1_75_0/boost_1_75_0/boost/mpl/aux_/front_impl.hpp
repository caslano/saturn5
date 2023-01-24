
#ifndef BOOST_MPL_AUX_FRONT_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_FRONT_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/front_fwd.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>

namespace boost { namespace mpl {

// default implementation; conrete sequences might override it by 
// specializing either the 'front_impl' or the primary 'front' template

template< typename Tag >
struct front_impl
{
    template< typename Sequence > struct apply
    {
        typedef typename begin<Sequence>::type iter_;
        typedef typename deref<iter_>::type type;
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1,front_impl)

}}

#endif // BOOST_MPL_AUX_FRONT_IMPL_HPP_INCLUDED

/* front_impl.hpp
E8lk0vUigge2f3CgOZKPq4anJgSInbpfzyG5/EtuH7C8h4/5OUE6Vzk8M9ibjwxrBNF9xG6REpS0lJScIzzqvdwucm9vC5ivnX2C0a9bje39kV0qLT+eIk2ouxgdcDwqUaOdg4sDMNLIEj8Auw7XV7/iLSiZhNp9Rq177qRKjuT6zizISJeFE3RWwg/mFNo4Oxy2k7MjVOtHKL4WW0BrQ6t62vqtNLKI9Bu3KSdHrj6D7weZqggeu3okN94d3SCHz/RvTlQNWT14kR9d1kVsloYLuhNWSbGzZgh1i4T8ND3bCNmrQH2Z3mdzkLestNyUAwBTAWjJKzUFGRhS6lWkzGGSx4tFFVsjg/IdxW3QmssK2uxBpslOWLHTryRAtSnp6Ix3YzmSZ0owIPoYKRQr/Bf6Cu4xbqEFbmGSNle4eil4Bemh0bmEZZKhZ0yuSfhMEwYK/64tMTjNN2ZMnWQmjtJEdNILv4NYLqcQTnEEYUfBZlzTD2+VtzsKi6eo1KV0YA9T6P+lJ9vyIwNPi1kZiAgrqcIeoJBRK552Z3KINbjzfBbuj5Bixjr0JfL5drNXgSimaR2wwkBhk4feBJ32ztXoLMsNF0Dwz7zaIIYuaDPglvr0C8AJBqh/LU3F+Sa1h22AgwRSgoDk8uEbKlFluiOQj+G+SSUARQa+RXrlWbIP4Mt44lka6hKVmnzKkPqNQGzw22duMfcFjdmM
*/