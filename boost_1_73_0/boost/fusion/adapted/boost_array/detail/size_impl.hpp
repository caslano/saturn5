/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SIZE_IMPL_27122005_1251)
#define BOOST_FUSION_SIZE_IMPL_27122005_1251

namespace boost { namespace fusion {

    struct boost_array_tag;

    namespace extension
    {
        template<typename T>
        struct size_impl;

        template<>
        struct size_impl<boost_array_tag>
        {
            template<typename Sequence>
            struct apply : mpl::int_<Sequence::static_size> {};
        };
    }
}}

#endif

/* size_impl.hpp
1E+L7l5fI3s534yuJu6xj4afuxxEb77B7M7/kt4Py5u0tGy+9jdcD88Wf5sw6bk1fWtPYBc9mmtFfx3zPv7C975vtPJ8Jaa/5Tw5tyTk+Nk1h/ugvTeXAqIp18YovzsGyrVDY8hLC5D3/GmUY5zXMK8eIekQXM+VlwRyrEcYOPgi0FjK3N1cw52HAh1pdzppsoyUkM3G01L4E0DlOa7n6B8ZLe8YNUffg1nu/hSz51U6fF7s
*/