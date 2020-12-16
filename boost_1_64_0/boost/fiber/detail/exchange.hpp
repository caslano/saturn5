
//          Copyright Oliver Kowalke 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBER_DETAIL_EXCHANGE_H
#define BOOST_FIBER_DETAIL_EXCHANGE_H

#include <algorithm>
#include <utility>

#include <boost/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

template< typename T, typename U = T >
T exchange( T & t, U && nv) {
    T ov = std::move( t);
    t = std::forward< U >( nv);
    return ov;
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBER_DETAIL_EXCHANGE_H

/* exchange.hpp
acQASkPewyTtC8PP4dJrOFPGpjJlDHPV1Gb8I0mpqqmtvlKVkuUrHVLa86WwlJZ+qVFKcv4HfamuqXd/qUdT638prqlfVdZGU5dUqmIwtlIHBt0rhTGIqtSIAZRGZict8Bkto8KmXu7NpjbRZFPHnFSV0pMndUjpupPCUrp4QqOU5PwXnVDX1Dkn9GjqgBPimtr5RG009Y8KVQwOVejAYFGFMAYvV2jEQNCmRnqzqY012dTy46pS+ui4DimNPi4spR7HNUpJzn/EcXVN/fGYHk39/Ji4puYdq42mPnxMFYOYYzowuHBUGINdRzViIGhTG3mzqRGabGrro6pSCjqqQ0r7jghL6d0jGqUk53/wEXVNveeIHk1tcERcU78+XBtNXXZYFYNxh3Vg8OBhYQyuOawRA0GbGu7NpjbUZFMzDqlKKemQDim1OiQsJcMhjVKS8198UF1T5x3Uo6nPHhTX1K4Ha6Op1QdUMThyQAcGSw4IYzDigEYMBG3qZd5sagNNNvVguaqUPinXIaUx5cJSerRco5Tk/DcuV9fUn/fr0dT1+8U1ddr+2mjqI/tVMWi3XwcGf+wTxqBsn0YMBG1qmDebWl+TTW2zT1VKwft0SKl8r7CUVuzVKCU5/0P3qmvqfXv1aGrDveKaWrWnNpq6fI8qBll7dGDw8B5hDKL3aMRA0KaGeLOpoZpsamaZqpSeLtMhpdZlwlIylWmUkpz/TbvVNXXBbj2aOmi3uKbetrs2mmrcrYrBsV06MFi2SxiDUbs0YiBoU4O92dR6mmzq4Z2qUirYqUNKGTuFpZS4U6OU5Pw32amuqb/u0KOpRTvENXX6jtpoas8dqhh02KEDg+rtwhjs3a4RA0GbGuTNptbVZFPbbleVUsh2HVI6WCospZWlGqUk5//5UnVNvb9Uj6ZGlIprquOL2mhq/heqGEz4QgcGj3whjMH1X2jEQNCmWrzZ1DqabOr4bapS6rdNh5TabBOWknmbRinJ+d+yVV1TF27Vo6mDt4pratzW2miq31ZVDCpKdGCwvEQYg1dLNGIgaFMDvNnUQE029egWVSmt2aJDSplbhKX02BaNUpLz32yLuqae36xHU4s3i2vqjM210dRem1UxuHmzDgyMm4Ux2L9JIwaCNtXszab6a7Kp7TepSilskw4pHd4oLKVVGzVKSc7/8I3qmtp9ox5NbbxRXFO/La6Npr5XrIrBxGIdGPQsFsbghmKNGAjaVJM3m+qnyaZmb1CV0jMbdEip7QZhKQVs0CglOf9bi9Q1dVGRHk0dWiSuqXcU1UZT/YtUMThZqAOD/EJhDF4r1IiBoE01eLOpRk029fh6VSmtXa9DSuPXC0vp8fUapSTn/4r16pp6YZ0eTd20TlxTZ62rjab2XqeKgXWdDgz81gljcOBzjRio2FS8/56QKbwaqEiuazE0TBkaJwVbXIJNcFjPIg/xyyGUOVUebMZgV7L+GOxKNgDIBstDAknEsJpkLRjsSrYOBruSDQKyYfIQOOwXXpNsMAa7kq2Hwa5kQ4BsuDwkVMDDu+/xPb7H9/ge3+N7fI/v8T2+R+/j/vzjS77zj/+C848Gb3N2Rk1zdvtWqo7CP1ipYxQ+cqXwKPyhlRpH4YrzjyvVZ0LO5uuZCfksX3wmZHJ+bWZCHsxXxeDGfB0YnF8hjMGOFRoxEJyzM3mbs/PTNGfXaoWqlCwrdEhpz3JhKS1drlFKivOPy9U19e7lejS1/nJxTf3q3dpo6pJ3VTEY+64ODLq/K4xB1LsaMRBcBzF7s6n+mmzqmGWqUnpymQ4pXbdMWEoXl2qUkuL841J1TZ2zVI+mDlgqrqmdl9ZGU/9YoorBoSU6MFi0RBg=
*/