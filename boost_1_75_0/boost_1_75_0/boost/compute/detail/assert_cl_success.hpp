//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_ASSERT_CL_SUCCESS_HPP
#define BOOST_COMPUTE_DETAIL_ASSERT_CL_SUCCESS_HPP

#include <boost/assert.hpp>

#if defined(BOOST_DISABLE_ASSERTS) || defined(NDEBUG)
#define BOOST_COMPUTE_ASSERT_CL_SUCCESS(function) \
    function
#else
#define BOOST_COMPUTE_ASSERT_CL_SUCCESS(function) \
    BOOST_ASSERT(function == CL_SUCCESS)
#endif

#endif // BOOST_COMPUTE_DETAIL_ASSERT_CL_SUCCESS_HPP

/* assert_cl_success.hpp
Besn4QPjDPi4pgn3fXSCtW6FcTLcyz+YMPbh4xoF+stz2U1fqGc2XIYOrwz7brK6qsYmw6c66YDrAXeXvvwh2cEgzKg56EoHKE/OhYp/pmcuhDoGG/ofK3MttJFdJjxu3Lma7RPCusHYNBe36I174A/e7mG3B+FPvfEN+NUTxQGETUYcZ3f2Id8L9xGYFgI+x906XdloY9Iff1ZcFWJpUh5cwKTzy3r4Y9i2bHShTadzzfIlxGAxS4prmj1zq7DR0p+cKA0tcNlH9CZW2b2J20RP//SC3N3OFGlSoj03MC9eGm8yBOy5/nkm0b01I/QV9B96QCKd3IvSdZV4FQ982Qf+xhCbptQxGq08IN/cF+cDzAlXfdAVJz5t3vM49R7godKx4XGcOg44Y6v3uBLljkc7cTr88VHOYpE0B0X0NSgMMvgAMOdfcAdVoIQySavgsezlbYmCFUTg1kj7nvwh2p5gLeo/0ao0Ms4NjjutyiSYh0BIzE0V+USkyoosh7qRyGVFcduK4tYCkBbDSUqAim1+eyWKH9FAUqkQBAaOh4zQ50wcMau7k+zFWUxsaDIDVWbDcr7cP7YMFdvTy/C2sbZvrI7ZJ0VlRDs+QwmGgnLTQB2W++8yNvTJkrrzKtxnRgo0kQ6LLlweYwEyELlzuf0wPI0HkPCS8QbGV396zEgl8+D6TXjTYKyEJ9hsg7H8MabtNBiX8SufCSXT
*/