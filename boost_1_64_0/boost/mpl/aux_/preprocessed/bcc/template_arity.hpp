
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "template_arity.hpp" header
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
LlMgmhjtax9beCCE3COEp6o0FddHBeprdjp4seoLad2YdXiPX+dTDmmf5gu5j+td/KsEOfNFp4LOgewl6x/E1bY1BFomlLBEXrer2S86y7COn4a+WX0pi0/b0dBAPqjfqWIU2/LLqZnRjNX/U4yTU3NbiS54vksE+d5/unTH9MmfBoEdx66GvfwGSljDUQBKW3+I2S0RbeAYbbEWlYXSOTQGp4r9V5aeKH+12eBHLGF1isKE0w24zPUBkPqnNErvt/mHshHlymwK6j4RbFEX4VisFm4hyS7OXd1pVS883/+juQYo+x8UdTgn3tMBKTcL1jFu6RZXXRiGEjWV12eaS+sWLK+5rDlevHNUTqThH8MTBe5ZtuyGP7g6g2AS/DIiwCE2JX0oB8+tsunHgDkb28Rtm6LGGejgjoxdBKle9l2VznN5GtY8vWRAeoRFEklOzdXvIYc3Ju+SBhURKbWkHYWVlSCQxDuLihciH+KpyluCj6eII2gVJBJ8rf7Lu/fMvW0aLvYpnx5HsmOUUoeSSdDk6dK6bvdnXyK+uYC9+Sigg3dDBhmQ1zFLrA==
*/