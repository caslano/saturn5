
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
zsGquABr4Hr0wo/RG/ehD36Jvngb/fA+1sYfsQ66sT/VwzJYH72wAfpiYwzCZtgK+c7kvRw5XyI89l5OtOyPMVgW47Eh9sIg7I3tMAkTMBnTsQ8ORAOOwH44Efvi+zgAD2MGnsdB+B1mYg4Oxgc4FJ0d+B//FcHhaGpvUM5ByLpq2xvkPMj7LDgWa+IErINTsAFOxWCchh1xOobhOxiLMzARZ+IgnIXDcS4uxHm4DOfjCvwA
*/