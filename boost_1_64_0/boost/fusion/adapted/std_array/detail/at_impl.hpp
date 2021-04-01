/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_AT_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_AT_IMPL_01062013_1700

#include <boost/type_traits/is_const.hpp>

#include <boost/mpl/if.hpp>

namespace boost { namespace fusion {
    
    struct std_array_tag;

    namespace extension
    {
        template<typename T>
        struct at_impl;

        template<>
        struct at_impl<std_array_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                typedef typename mpl::if_<
                    is_const<Sequence>, 
                    typename Sequence::const_reference, 
                    typename Sequence::reference>::type type;

                static type
                call(Sequence& seq)
                {
                    return seq[N::value];
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
r2y0J6mDfB5SrppglJVY6qO0gfNN7r6KxUg4CY2KgkjnAr6CK3sdqdBcM5vT9uAnU5Edoq9BFExnvvg6fT9qYsHyLwFQX/Ialliq2M8yJgOoFfDxwqT9AAEDMjZ4O3V3m+85X82wp9JuQ4OBfELmlooMNw09bSVnyeSOuBHCV+Q/Dj9Cz63mbD+cljtEJ4xVuUln+ZkMtuP6m7Ub8v5DcYSwYMMgrUBtlDhB9dQQA8R6ZmbaBNhptjZ0eIywKugOMX6WKbZISITuzRztq02aQOJliKPFCXEfnkQ3it+zHtdswqf61nOVKWmD+2JOJg/nawfnYLsyBgVBWjFrNMpjTIHEnMkfx2fhAvl6l0wvXlZfmK7HYzO8Pj3zOJ7dPZFSX5XwjUF2DWQAYH033uLy87cDExkEH19IEFmywiykItNjVraaDhLxkEpR7BayZOmgiWI37vLdvbB5/SIRgaHMv+mDxMJtRHc7nvv83t+5mh03rp+Bb6M6kYxEEA0Ec9rZT0qsOk0gPOf/y6auUAgLUd0bPmVTKOPdZo21PhLkW3p8Q+XIxM/uDpzUew==
*/