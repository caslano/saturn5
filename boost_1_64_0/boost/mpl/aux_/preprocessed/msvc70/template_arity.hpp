
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

template<>
struct template_arity<int>
    : mpl::int_< -1 >
{
};

}}}


/* template_arity.hpp
JT4z0O4gydG+iOUouOiU61e2jOuaJPz2s731Gu2HVqsCHD8ZV+1Hux4bggrA2poPXwEj0R4pDItqPE33K4SMAE2rdPazOuX65TSAuvNnsD2iGwYDkI1Y2vWTmKkVjCgC1hFMhWOhDInN924SWDZfA4jqAxF8PK03sIPtpxS2lnxyBsd6IIPoPPjUbMYSNz7qZ2mXC5hoGIhdy53zRhlCN98SINhoEogbzf41bzC9qISN5swAqcb6TVnupGp63nmwNh8BICs7Ajku6bT471ZKrpMBd7Nvp8qhUFE6OqoPZ3FXonXIarDHV1Cnu8GKroua1fcQBmnYgp3rN9tHGBY2KLSX2d1Ot5N4u9DUSJCs4gHYG14WsT1Vfpxu7ghx4dQqBcz3g0i6C30cCnCAzgPZJ8gnBuIUoBuRqH4HAgpCRmfrFtZFIboho6m+Gp7Ek+WJ3umGpU1Q5F7mCyKBq58KWVsrh8JcjcWLXQLRKYGbQsSlOfkND2Ca3yQfpl7j1iZ6OlGg56uEI4JfTnJeSa4QulG5e3qtHrnHexsW4yKFPm5ryvD4oyT/hWjM0Q==
*/