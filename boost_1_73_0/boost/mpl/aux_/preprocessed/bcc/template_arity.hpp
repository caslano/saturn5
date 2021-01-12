
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
kI04jS05ne35CIdyJq/lbN7Ox3gPH+cUzuUf+CTf5lPczHn8ExfyYy7i51zMr7iEdZwQvcjGfIntuJRncRn7cDkT+DKT+Qpv5qscy9c4lSv5KFdxNt/gU1zNZ/gHLuFavsh1fIVv8zW+wzf5LtdyA9/lRu7l+/yBmxh3uPMiluQWluZWluc2HsOdPJe7eTE/Y29+wQR+ySv5DR/gfs7gd3yCP3AVf+Q6/sRN/JnbWDhynsY4
*/