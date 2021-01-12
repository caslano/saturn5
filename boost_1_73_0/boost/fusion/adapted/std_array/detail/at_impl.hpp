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
5XAiPBueClfB0+GPcCas5zxfMAOWwO7QScfj4K2YT4K3wdPg7bAaroPnwA3wYjgdXgFPh9fAangrPBveCa+FG+Eq+Cgsh0+q/0/Bu+C78Lfwa3gP/BGuhzQtJb8mQK6n32jS/b5hXyT+G00vh/gGDnwdZsNdsJWaO8O3YA+4G/ZSs35rSffS5tr+X35raSqVJoeFMAeeAVvAObADLIc9YQU8Fs6Fw+E8eMLf2TvP8KiqNADf
*/