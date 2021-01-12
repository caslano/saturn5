/*=============================================================================
    Copyright (c) 2013 Mateusz Loskot
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_IS_VIEW_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_IS_VIEW_IMPL_01062013_1700

#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion 
{
    struct std_array_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_view_impl;

        template<>
        struct is_view_impl<std_array_tag>
        {
            template<typename T>
            struct apply : mpl::false_
            {};
        };
    }
}}

#endif

/* is_view_impl.hpp
1d9vajq9DeWMWhgD39P02g1TRK3hgDXgXlgT7oG1VX0cbg+e9wn3azylIJsRvZtA4qkQVodFsDacA9Pg3bA+vAZ2g9fCXnA+HAkXwDFqbixcBA/j4GL4HXTUp1X9q6rv8aCG98El8BG4DD4J74Tb4Rq4D96t8bba1rMcwUINRzNkubaTo+KILzgZtoNTYFe4DQ6AOXAonA5HwzyYq/oFsAjOhbPgAjgX3gavhevgAviyql9V
*/