
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
+M+qlsTfXezTBccXyH50tp+6F3tE9GN/VurdCwQuHEV9FkPdugg/OGZg4D0Dy6JYT93POqGN8Wv/ZuJmI/y0F+OvZ129AX9KMnxPp3+jW4C78XPm/zLWU/lr8IOg3wkU+SIEnn6ZeO0jntQzMHcwcQN9+VOph8SOwXU0eSZsJ3Z8zOir7BrquG+oS2aQZ3Kgg9zRA9DPO/Q360qpx1mnfeatp71zHoGKh37ySObRRYyzkvoO
*/