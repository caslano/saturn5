/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SIZE_IMPL_09272006_0724)
#define BOOST_FUSION_SIZE_IMPL_09272006_0724

#include <boost/fusion/support/config.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion 
{
    struct boost_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct size_impl;

        template <>
        struct size_impl<boost_tuple_tag>
        {
            template <typename Sequence>
            struct apply : mpl::int_<tuples::length<Sequence>::value> {};
        };
    }
}}

#endif

/* size_impl.hpp
RMRjjhz+HXyO3LpTHBvdPOfIqXtdh8JPw5NfwNL9mXQL6nvShpeK3TS7nfWGyaN/EV2WzEmS1dVyrXRfLnWZAlZx3EdMfUwtr8BeSm0gIvbSDsFeXN+waXPMniBrsSl3r1YdveWiayNz82JrrUuLqioK8uPuRuLgO30/VekzBc3cpw7i10Ke7eMIVz3TP7FC9OF4/2XatPHd9Vxmif0kuwfPZHLc2PAGD87R99YkiMhzizv9
*/