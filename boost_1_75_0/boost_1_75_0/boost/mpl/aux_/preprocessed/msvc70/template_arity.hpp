
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
9K9SekaVVfznB8THxYTHkBsEgTJETd0S6okpUsL39uS9mBeD+16IWGpHXEIiPoIxI4xg4k7z+qbxKsRdS4s7unnfYGo3XSVmoRbnqrQjPZkudJnggiwKGi0mtTPEX08fPXatEfEgdUTxM34Y0PdCES1cGh9AKrJC/lxDUc29ZgAm4VDBFUUvDTWoIsZQ+SVnMM26Utk7VDtcoQq0jLHGpmvFPxEGfLgJ2J33DV1O6Xl1343fDtt47TS9JE58hVChUV+ZMxiWgQXYnSGl4eFfepzKkVoc/XfBzz1t+olPS37UcPxRwOV0cNcATGC087o2sAsLjjAKuJFL8tzFYAT3vDGCQQCVLV9KcW/lANLDt2fJJGhtXpcykPAw+5Ur6ekMnN/lW/MMLYiSW9OLVhNaCgAGf5/fkX3m9EMZ3l3eRdQPlZ/BAIk2cP+EJl/zPSvuXYbUQucrreb3blG4UguDZkSe7dSFsaPm4tfySBC8wVNPZ4JBVhvvzwzqn0Woqnwnfhp7JdUau7+EKIPPKP8UjhE5/fRQkV77B0hMWXm03m/8lMF9ADxOBEj7CSM38vTK6TstSy2hhvA5Ay5XsMVCRPAcONBnHS4s8iPm+FJvSLdHo+rw78dkl4af/tlNM5FhV+fZ4XLC6TW4DyMBphQ07lcLP/I0goWQ1W5AU2v974bXl43aXx5TcztvuskcgZeOoLdY2+ntrsdbCFvX
*/