//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_DETAIL_PCG_HPP
#define BOOST_BEAST_CORE_DETAIL_PCG_HPP

#include <boost/core/ignore_unused.hpp>
#include <cstdint>
#include <random>

namespace boost {
namespace beast {
namespace detail {

class pcg
{
    std::uint64_t state_ = 0;
    std::uint64_t increment_;

public:
    using result_type = std::uint32_t;

    // Initialize the generator.
    // There are no restrictions on the input values.
    pcg(
        std::uint64_t seed,
        std::uint64_t stream)
    {
        // increment must be odd
        increment_ = 2 * stream + 1;
        boost::ignore_unused((*this)());
        state_ += seed;
        boost::ignore_unused((*this)());
    }

    std::uint32_t
    operator()()
    {
        std::uint64_t const p = state_;
        state_ = p *
            6364136223846793005ULL +
            increment_;
        std::uint32_t const x =
            static_cast<std::uint32_t>(
            ((p >> 18) ^ p) >> 27);
        std::uint32_t const r = p >> 59;
    #ifdef BOOST_MSVC
        return _rotr(x, r);
    #else
        return (x >> r) | (x << ((1 + ~r) & 31));
    #endif
    }
};

} // detail
} // beast
} // boost

#endif

/* pcg.hpp
NHv70s+gpqH8FkuhIaDZVr10Sa+89HKklKDHQV5RemWZ1jdlE02edVUl6+uUbmuax+gfJWl89ujwTp+7tIfNcZFOi/jHB/x5f20Tm+Up97SNlyqS9LhRrijQ3GzoKYQ+/Mc9qNDlSNlo0cecbAmnFPUR4Ok0v+x7zPLUeUXc8NNx28o5d1hwvhaAvzlkvtCXhswT5Xhe7jzmCRKB95Ye5Mffl85jfhCvLS+zeDZAGiNKBeWDtyVkXjBwCpkXyvGMv4XMCySYFx0u5Xchw/l5mPVV8/QovwuZX8Stx/YX0o/3s9XVwuHBelgC/vZQeigr57bM0LpoZz4SEX6xL6+UksM8qBPyUSeLbHyGDece6CSZOrlY8m9Lg9bNIluYvb57U5y6AS/446ND6qa28pryEHqhnEMvIuFLEvVCPuplqcmnqBfhOYt6CaRB62WpGeZ4H9w5wr3O5IXSS3l1p3UmL1g3lDLqjINvkY1vHd+TuUf37OnHlo5kW70x722vO8WpwX3lpZDxuuuIsYfSD+XYV1I/pl4Q3vO+kvmVeM28NLCgpfvn98aV4G0MkRd+DwmVF8oNM8vaJ+FoB+STdrDc5NPlrHnOKN/2cmbcjnaw3AxztINd6e56aQ6lFxy1UbJR4gn9TGR+kgO6oZQ/ZdQPebV+7LwBW9Y90E+qTT/OdDh1pMPt3ydGOnTEvqI1lI7qKtd3pJ/W4LoDiWDdkE/iWaT5Anpp7YFe7PXGfv8E3T/oMLPO4H0mWB+F4G3vSB/4/NDh89bQySpfXinleN4a9WW1jc943p4Fvaxi3o006Lqy2hZm7zPbRwXr5iPgV31D6OYaPJ3WbQ6pF8g564pPwtbPkI96udzkU9SL8PRcL6wvZhq0Xi5nGO9r+x6dPtq9DaV3rJei2vLSGvwNqZ90nSenfihp0xP52TctcuM3v/v1QF8ZNn25pylVtzMXHkc/vWRM8HjlSsjldaw/qZ8hdEfZNNEF25yWYhKpN/JyzLLGwavHLMJ35mOWVHvbc6ZFj1vWOMKV49tDxVgl1zKuG5gPKoKM10VXPGsr1DwOZYbrs2BvF/dU5NBjyPheq/k9mTLD9PmWt4p7tEpBGlkWuFgW/FZ1n/CM0t803uzGPB/nhFzOvJZ02epRXlbwvEGJ1Xe76aaua+/1PtlI6Xte932PpxDrj/B0b/7A7b0eccOPcTvGqnHjgvNVas13uear8/d6keN8yF8lTyIQmOfqQX78Y1XECz+J15aXweOVXANAondQuRhmcMtL5+/1PrkBEh4p4SLAvOhwKb9ohvM1m+1a8/Qov5HiJ/fWz4xo+vF+9jm7CcF6WA89pLvqoWvv9enMRyLCj0q5Usj5nDB08neTz3w+9EAnydQJ0gA/Wxq0bv5uhjnqe352sG4q4ZfnqpvO3+vzgvUiAkHPAUMvYYMDfLZnwFnUi5EGrRfcV4c553nLJrrXmWJXvXTtvb44SDcUctSZ4qA6o1+ttW6Kz5puEHfIOqPva6szOZOC+8gN1juwq246f5+35NhHUi+GPiS8532kL68Sr73+Tw5e37DR+j7tmpfO3+d9cn2NMvYJOOs/+aSMjxt8uv4LT/fWN4QuY6bBUf+PG2FB9T/HXS/Nrnrp4vt8kG7sr9H6Xd6pG81nnEt11nRjT4PWjS3MXmeqpjh0w76hxVU3nb/HtwTyS71AwKET8kgcf9c8AX209EAfiTZ96HsLL/sC+tvryC1Tg/VQY33PcNVD197fW4068o7kk0K2PpJ81Nlpk89oP6090Im/jiAN8GPcjj7ytA4LXpPYfE6wbq621nG66qbz9/e2oLZje3WmXshHvZw0+Mx+pe0s6MVXV2xp0Ho=
*/