
#ifndef BOOST_MPL_BOOL_HPP_INCLUDED
#define BOOST_MPL_BOOL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/bool_fwd.hpp>
#include <boost/mpl/integral_c_tag.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

template< bool C_ > struct bool_
{
    BOOST_STATIC_CONSTANT(bool, value = C_);
    typedef integral_c_tag tag;
    typedef bool_ type;
    typedef bool value_type;
    BOOST_CONSTEXPR operator bool() const { return this->value; }
};

#if !defined(BOOST_NO_INCLASS_MEMBER_INITIALIZATION)
template< bool C_ >
bool const bool_<C_>::value;
#endif

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

#endif // BOOST_MPL_BOOL_HPP_INCLUDED

/* bool.hpp
2g9v/MRCvp2K1TarLOAyKtgyT0BbpoHGW/BqEW+E2jeQo/OSQqrX7Ld4S9YhEXljy9S3VcSFnmsuNG7KevXmtnQ5XdsnAHCH2hpofwN6k9Q+FyRUjxslZ/7kLSCcSA8d+VL1xisqMZGbtGbh1ZP30187D9MLWeg/789cZuMnQkZu+YYe9xsjxX1AvF3BTzbNVNn3PKvE979ap2lmr45Rdt/Slbjuo5EJyZvHOyqh9zljdxeBQgs/zqoGYJ13VFwbXAVUdiArmuuj+pHokmnvyrRXXOASpEYjnXuW0BO3wO1tSXBxsQ8e3fKK2HlVMRbQyrQ2eeIL20W58I1UxwRZgNrvnavVieuM5BO8zi3E3IgKv9B48Jo3HvvLi0Asq4I46BRjXySrGttbqyHr2ESlXebXY5g37ZhaJfWWwNTF4FGqq+Va7bVVi++ttn6Z86/rF8OhPWQxgrQNP5ofj9AOSh8jPGufDfD+Ef2dDKr3O5+f+vi2KuKdE0o66hC8no/cfLtIDpEK2PfwQpHbCiw5uwW6nrG/jRccCRUdoIny8dyVGiKXenhw1wsmeLZfGA9/BQJ85dz4Zc26ib+QxGgD5/pua8ejFX9bvxH6hhxuEGwwfLGTwPqJB/p1GzLWgcWbfiGITW2/EXLMtqERWWaLsMKyahvZoXFBhLOkh3cQEvWQ+rV6uT3qej5iLoi4wy75XTU/6ZoWf07MRHSc
*/