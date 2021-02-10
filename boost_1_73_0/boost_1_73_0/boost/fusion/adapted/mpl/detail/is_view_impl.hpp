/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_VIEW_IMPL_03202006_0048)
#define BOOST_FUSION_IS_VIEW_IMPL_03202006_0048

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion 
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_view_impl;

        template<>
        struct is_view_impl<mpl_sequence_tag>
        {
            template<typename T>
            struct apply : mpl::true_
            {};
        };
    }
}}

#endif

/* is_view_impl.hpp
5x6esxjAm5/2WI52By8+mfln+OC6N5o24l+aq/83yLJb6H5ouMD1FaHGcG91m43gVVa3MDRWWR/rRH9n2SvCLXSS+jXWxotMf6Kks+ztJ2Kza9iqUjCcjODw/fvf4R38enB4bMMZqRnlkChaL2mzsuGkMJK/KnJz40j60QaqgHDngcO0YhKkKNWWNBTwm7Oc1pIWQCQUVOYNW+KG1aAqCiXjFCbRdO6Hn2zYViyvej870YKsRMsLqMg1hYbmlF13bjakUSBK9ID+CyYV+mwVE7WD4Sko2qxl70YnQbgUQK4J42SJ4YiCSqmN/GM8ztuGYyXjQuRynO+hcCq1flTVHLNZkx2IjQIloJXUBq1vw1oUrNQrQoTCTbvkTFb2fVoYsC7GogFJOe/doSmjsiuBQtKjZWtN2GD2TOlFilrqaNtKrB8oIqy9o7JtagyHsKBeIRB4G9q6oI3RN0Dso/QoG8hfaNl97gWIGrOCgZuAnwxgSSSTNlz56UU0S+HKjWM3TOcQnYMbznt/l354htxgGLUBerNpqMQsGmDrDWe0eBD8p950y0kvYDKLg2iaZrMw9pI09iepd5a5Mzw5gsHhMfzd1prgvw1gwNlSMwCOnaNj5wAFepdRIneZpEr3Gv9IK4mekwsI3c+e9bz7
*/