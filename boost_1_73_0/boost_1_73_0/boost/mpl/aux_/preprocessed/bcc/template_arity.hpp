
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
0aG/ZPZ7f+jQtkER+7xM7VOiOJ+s6bg6qTNA03HH0RnmQMevlCscQ0fPT7z9PlApV2d0TlHKFUtHL1c8nUf2q/116bbnU8pPov6ErfuV6/lO6Dy8X+3fSF5n2361Xyt5ne37I8dFZ3Qe3a/2ayWv8xh0goY9eZ3nhNJvrOXLqjNMJL4ee14ozy86ofOCUOphJ3ReFMrzi07otKnxccfXiRfn3Wp8OqGzR41PJ3ReVuPTCZ01lvgk2/7caIlPsjo=
*/