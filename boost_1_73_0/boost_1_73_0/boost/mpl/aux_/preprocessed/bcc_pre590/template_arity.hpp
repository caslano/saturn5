
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
d4zq+4DhcFU7prr3wdunG1VstOFwVXtSeS9S/LoPXy31VGnRhsNVtzPVPZ/+6xajGhltOBJbrOdbkkL8pJOfmupo3EcrvjB+1kcbDlfdwVSLjq3ZYFRek3WHo7qTVLGKN3+BsOrwVjGGw1V3CTu33Hf/Cis/Z8QYDld1YKqeUcnnjKooxnAk9rHXzDrp01HYJff5it2tnLAlxnC46m6m6nKwxRGj+ivGcLjqHmHXLROavh8wqmtiDYerOjFVuzU=
*/