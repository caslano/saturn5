
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
6cT6pZOa5XZm/Kl0rqeNvJPlpZdWhs2uVJvN8yxttNbeW84LkofA9t6JUu/hZrweO2Il7IS1MQm1duOFLOdWWU4XWU5XWU43Wc5tPsspKGQ5PWU5vWQ5ybKc3rKcPvpyOG4vvZz+spwBspyBspxBspzB2nKIspxGQZYzVJZzB0biMKyGKdgAh/ssx1FIflJlORbJj1Xykyb5GemznAWFLGeULGe0LCdDlpMpy8nyWc7uQpYz
*/