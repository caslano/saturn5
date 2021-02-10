//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_DETAIL_NVIDIA_POPCOUNT_HPP
#define BOOST_COMPUTE_FUNCTIONAL_DETAIL_NVIDIA_POPCOUNT_HPP

#include <boost/compute/function.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class T>
class nvidia_popcount : public function<T(T)>
{
public:
    nvidia_popcount()
        : function<T(T)>("nvidia_popcount")
    {
        this->set_source(
            "inline uint nvidia_popcount(const uint x)\n"
            "{\n"
            "    uint count;\n"
            "    asm(\"popc.b32 %0, %1;\" : \"=r\"(count) : \"r\"(x));\n"
            "    return count;\n"
            "}\n"
        );
    }
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_DETAIL_NVIDIA_POPCOUNT_HPP

/* nvidia_popcount.hpp
owjg7upSWMeWpmbK3ptR1HPyQQ9a1ttu2VoFY7ZFitOfphZlwm3jXwxjAybLp/dMAVVkFIaQF87A4ewh95yZLchN0dJMwXM3Xo35NJTY8SngJ49IzY84oGUvxN8eenVipiSx4os6nIuj/O9RBM6GsLEQAE3O6bIAx5DLsxSQE9rnrdYxRZqlAceT5Lw5IEJBNlCDAHIbCVmzPbNstnQy8HCUc00mQdUKJnG0rfN7MtARg2rhOuNTEZPwh50X0jPTuQRs3MK91quAT3J8D0zIlZR8CQnFiJCcjdV97Z1DtuPFLVPUWearHbgIW6F1DGtESPNizYx0ihDF6fUxuzEyGVZoL5pAYQR5YUupqeqw8wg7d+6QWEvRlB4eGmiD9cIzbP+PzzKu0w5z6L9uJmfTm9vrm6v51enVxUwdGCw6eohA7s1pz7d5jaeGPUdcoktWSNAaUWf1UKrzfavGAqwOfkvgcAkPCH0Wz9mWt9njaB6/oZCEDFdZbNpCQF6mxS4TxCTlpLWYzMKtQUHCePohQY4VPEAbR4WHqJUQD1+9/sv4Jf3v1RFEpL8kdlLQcs1R5ghKupFvdsvlOF3lP8gv/gsLE0JsRA6Lqmq2rc6mI9GUEdSTGNArORELPs84eM/cEwdwzt8LN5AWsnA8
*/