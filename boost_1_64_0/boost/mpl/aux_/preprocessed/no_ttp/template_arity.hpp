
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
R4gXoPXynRpfR8ByShpZLbfIWKMuJ92LxbwBlfH+3O7N6B8DFh8KIfVdXTJlEdnAqI0eKDw6ucgBBIhHMEW5SlqSGhP16bQZhZItmOJMUCMe9mwbNhkDkJwDL+HckqRZVgTwpZRoqHK82Ltn2AnHBGL0JP6JiYKMen9KnEykbSwcS+JsECJ0NYNlfz9xRTo9vbfAKW2zhEllKiFsH3srrjx/zMWyrlmumSwUzQScguUVy87d2M/9W40lZCe9KKuRfRHSfpEWXsTzuXQ2rUyZFyfZE3AEFBSFWvUgajOSNH410B6STvZ7bBghKCkl+p99Egpqo3/F14ELtDkrgr8cMnbZTU8uuGAeJvRJE+fmubQGV3q5wtvKLE8QIx8XPFe8TOKSzbUBPfVvCAq2pTj+ODfKerbRWBHvp6T69/EVEvETT0/B7+9tSys+kj8y0TDQhY+LJJq23UmoIUmCD1ub+3VQs4S55uu7+SlNdfOZ8C8FWWS61597SXNsTVe3oJbczKDcfbB9hJGL98BJ2Be/AS4daZBBKlu3/snoy1cBxrL6LuQf8htUDGKT4A==
*/