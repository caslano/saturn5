
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/template_arity.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< bool >
struct template_arity_impl
{
    template< typename F > struct result_
        : mpl::int_< -1 >
    {
    };
};

template<>
struct template_arity_impl<true>
{
    template< typename F > struct result_
        : F::arity
    {
    };
};

template< typename F >
struct template_arity
    : template_arity_impl< ::boost::mpl::aux::has_rebind<F>::value >
        ::template result_<F>
{
};

}}}


/* template_arity.hpp
AY9Q6dhuGwX2jJe3zDWW71UEYMviPjYHdcMNDtul7S73aJI7/QGDxOczQsQebfmbrj7fU88kk+3iqmkHA5fcTRKz4Rpk80q3qdh0F1WMFM/6mldKaJoJBtWWjPqHmFDTojMkprg+dhPoEEfTX+hPv4cU9yuPzWxXW5PD/B5xuROFvOL3dYyJ1KpYVpeZZdB/R/KhinwusCePLd6UdMyEYwsa1zyDV3VYI86qh8kjbdx+Go8Y5NqdeZMRhuyOULaKCp3j7faCTZUkGsPiFjlCXtztqB8aeL/zfTrshqheoLRitnZA0PIRm4tUh83gXLovgp4aiR0Zjj+0obGWFdzDDthHcWiUin4PFt3J5eGh52W4Q8DUahBhTrOMwi9hhSBGhrWRT5N+eQuiKgONxUfKZTMvqvwylAvHCjZx3EJ9EKSfEW2p55YGmVz0bMFC18b2bega3ZqLtvfWUzjfnRqzKCEm2Bxq7Yoppzc62VIs3z4mBL7LW0bBUp4WG+sMvNe2yKxP3WVTxOLy9U7mLpEwO5l2ci3JYF7bYHQ0aKv3W7VWz9bNzyR8vyYhDA==
*/