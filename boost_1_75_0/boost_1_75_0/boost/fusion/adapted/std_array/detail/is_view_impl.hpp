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
TDRzLAHlUZbYUKd/jYRZ04tx+9LKqlQD0eliWVggNANB0vCTP3tQakUSHZXXC1vXI8lCQZPmmPHPnpPdN8T8q/9zZDzdz6G1/s2HCw8tpNC47jnTv1j63ISfONheOeM9Hdwn7R4kW5po2dJEjJx6lhs7yWW14co/WmmcjcqTJ9tPJhEaaX70kgcYGY69OawmbLQpUIoTu0s/AgWy8Z4SxlUowS8+OUnN2REpsbdADpsfVM5rEO4wMGtX5wcawKbHmZoJeRiUhWv97+Z366UfcQE8WU0lxiGYcw1i6XHqJ710EooRa/CHuSpWXjS/acYaJZt3k5uAdIj7Nlo3xedK7ttgY11VLAUlsZiaLZ6vlV7pO5eRECltK8/cnKniX5b4l+Mqc+ZdiD9d4l+2+Jlb6sxzXej0uC6cCEtAcSmlSzldptFlpjnr8Dnj8USubCI6DRa9A6sqMedYARMT48KJMAO71aPazKLhHm1t33YxDClK1tuy//zmPHzTRPOKsTC8GENLshAjxr9RCEYxk557p1lPHPRkGj8pt578OxKflPOTUuvJAXpSyk8KrSdr6UkhPaGvisLvMYcnFw5PLWh48o+I1YqGt9P4G8keH635v9hj3K9Udv5zIP/nAVMRxIJtj4k+6QIpdSEOvmAcAB/BGov73hOwW46uYW+V22l6mWT0n2o3jaFe/BRY6KINfrdYJ/orR6b0chacgOXX
*/