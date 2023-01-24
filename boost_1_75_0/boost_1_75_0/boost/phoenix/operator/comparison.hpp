/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OPERATOR_COMPARISON_HPP
#define BOOST_PHOENIX_OPERATOR_COMPARISON_HPP

#include <boost/phoenix/operator/detail/define_operator.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/proto/operators.hpp>

namespace boost { namespace phoenix
{
    BOOST_PHOENIX_BINARY_OPERATORS(
        (equal_to)
        (not_equal_to)
        (less_equal)
        (greater_equal)
        (less)
        (greater)
    )
    using proto::exprns_::operator==;
    using proto::exprns_::operator!=;
    using proto::exprns_::operator<=;
    using proto::exprns_::operator>=;
    using proto::exprns_::operator<;
    using proto::exprns_::operator>;
}}

#include <boost/phoenix/operator/detail/undef_operator.hpp>

#endif

/* comparison.hpp
Bwf35f+BNN1/gzQPpyD3P2o1S1MLR8t/EbQeug/Zqqa4d3Mj3TnOejrg1pyNsZFcv9WrRk7hMLJ5Q1NryctA0VPNgDaxxdx2a7mWu4lUVz43wcbgo4Uq2b7UwGSpiXQBzs8F5I2FMDgkNCQSCltm9l/NX1RsmOTfJBUWHWBvmVsN3cns89ehdw9511ObHe5XYon+Vz2gqSt0gOHdAkqe3j33NJN/Rdz2lPY8jTKpOpOCWIiUeF/WLGjrGII9ia3x8kXlTze7+r1OggjgHu0fxnA7kQ5mNfwKS6daiWmCtwQbTGDSVAFBrVg9E7ddn5fLnTWzqTr/bvA3SPzOJDDeJtio9+phwYvd3/Ja4IIwC9vTusKBtSxIYZGp/1P3G9WwvJxFdPrnYRXlqYFgdFvtC6FV2nsnk8hSi5huf+Nmf+t6djeosL8ipm2c/dTq+MMdqHoleTLYGGQvRl5QNoh+LOEMdaaue397jI88KFD3B2BdGvwF86xAYofn+E8w0k2jMzJsZnIvm2AkePv1vrFv8wjWO3e8nTsgG6oc7oRZe/5uN5vuK9+A8HoPbUioDX4HRqOBKieDHWcr5o5uTm8g7Xh8bF9hStjBQUHu2rvWQoDk83VYR63Ar4/wNqi/OI4spQgKj+hm/5LWXodQi1wLvy23AFqFX0UUgPPc/W5C64J3w7A73c+wa7Vvn21TReJMegUMme4n78/tJ8in
*/