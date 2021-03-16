
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
wY6WrlheWpMiI5kuAzZo1YpYPEJ63GKSddOToih9aUviwiOQVkf69oezHN99h/emq98MJ6trauAeYCdFqvsgVnKziY8CB973jkxkn6r7zA0jG8u78XwG4Zx0IiQdooLTg+czCWdU94mTZnAyZRHOepZzQ1ndvwlelpTS0kxAiHxKU6Q6aY4my4eiOCeb+ODrJC7ZZXOfLaPrIZc5h3AKHcI5m+hkn1zCGWERE91nntB98gjnMyR8cjWffMJZzMo=
*/