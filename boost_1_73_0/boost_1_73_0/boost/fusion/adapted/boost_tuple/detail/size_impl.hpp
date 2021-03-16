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
cEeZ6XekscyFRe5OY2mFruYbOZelzRdxhT/a0TbFe4It0+VY3b/WV4/wHGQgyyWNNugmOdoI/ivZLoPECtzHDhKm78wVpo+tAPZzYDRK5IEHRQzigcdfhDMD5nKL0h/Fclp3i/0ONJ7dGzvIuKmy1BF3JzYF5l9UCswy+dslvFNgJqXTfc2nwPxKpcAMyd87InEKzG9VCszF8ve+YP9CdC1D3BSYZmRjMsv/a2kw6Y9qZRrMLvobLxsbM/G01vY=
*/