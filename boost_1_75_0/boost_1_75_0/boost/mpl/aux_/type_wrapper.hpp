
#ifndef BOOST_MPL_AUX_TYPE_WRAPPER_HPP_INCLUDED
#define BOOST_MPL_AUX_TYPE_WRAPPER_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Peter Dimov 2000-2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl { namespace aux {

template< typename T > struct type_wrapper
{
    typedef T type;
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
// agurt 08/may/03: a complicated way to extract the wrapped type; need it 
// mostly for the sake of GCC (3.2.x), which ICEs if you try to extract the 
// nested 'type' from 'type_wrapper<T>' when the latter was the result of a
// 'typeof' expression
template< typename T > struct wrapped_type;

template< typename T > struct wrapped_type< type_wrapper<T> >
{
    typedef T type;
};
#else
template< typename W > struct wrapped_type
{
    typedef typename W::type type;
};
#endif

}}}

#endif // BOOST_MPL_AUX_TYPE_WRAPPER_HPP_INCLUDED

/* type_wrapper.hpp
nNCF+NtHSBUccvUGhs3gg90px54PM+gXuWk+BMCMHin8cp8TntF5Y2DgdMyzB2PflGnmxGbKKexDrakWMdGCgPyAIsjB+sF6/e8dSH6SjHXRW7+0kEmjjUf/R2JzP2Q+nsL2VcH9PJephK9kzmQK9DF9k+YkG6T2CgObh6O4932Gvx5OrG5MhUp7BMYtTgg1guFAnSbZHOfeJPcRY1f+u51U5ZEj8dvsaYDWBIzH4rYd6Ngh9NHvfDbp7q6IPaBGftSl9Dxu2dwbAUzvehzKnqAiqDcT5IrxPq7kpqVKSv9q+dVzXqW5BlN28Pg3jOgQpmAxMKJsN7teRvJuyGVhqntP2qrwO0o5l1WkpZnva989JQ7t5JI2+Hlpmv3NXtHvyGFToQpiMapPYeWhm2lu25A5bOXIA2w/D6+uCE5aNWt8xhxL35vGG99X/xs+SXav2aCxtD7oJNvtFH9WFU7X64hbn3rF+Bd88iSj/mY1eUtP3OAAl1NDYg9PwXJPfBp8QF8EAy0/0eR2FYIohciT9ZE8KlyK+lwj7cjgTX/FJ0U+7HMwGjCV7ywpaf5hvNiVEoMt7T6voBPx5TBdT8ojnhpzJJ/9wFrOo9XlgWumNH4aU5b3jcV7l5hobUMudZvEhG+nu6tSQC7vRWVyLoUWLRkUAvdNuCva7Sr2Z1E4oh9RzpT4o2RbxBmo7+L7MxniAacQFviAG6bH0pAE
*/