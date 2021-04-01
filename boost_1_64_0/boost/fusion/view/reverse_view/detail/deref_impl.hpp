/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_07202005_0851)
#define FUSION_DEREF_IMPL_07202005_0851

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/prior.hpp>

namespace boost { namespace fusion
{
    struct reverse_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        template <>
        struct deref_impl<reverse_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::deref<
                        typename result_of::prior<
                            typename Iterator::first_type
                        >::type
                    >::type
                type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return *fusion::prior(i.first);
                }
            };
        };
    }
}}

#endif



/* deref_impl.hpp
sl/ICUI8h6SeTBnDgciGa29SMc/TmaKRKv+qsPEmOBiLXoHABgBL3HN7CuL9FlZ1+/6T3UVdq8Uia9AWVMXlg/gBFwqukO4MIQh+ON2QAF/OSWOXSfRiN2LVTYryybuOsQ76mV6G4q/4tqiXd40cbtQIpgdgicVeVXb8gdRN8kT048sLQ9Lp+3GaWcJzNEevThvfwM4dj3k0f7SAeaPqL4td9DQOUSu4lXfwFQQns3KFWANPTL0Ki+1gH7U/ZnWQ5+DoMno6aq37oZC/uaDE2Cd90MrX5vLnJpxPjdYJCbhIbPP3flMA4Bja75yWUoGIHju9dDjm/c0hczWXXuoVzxCVGai27pSueRTF2FZS5yO9oghWjcsCVyQtIeRjiAu83XfBcMcGgwXQuEj2Yu4wqS+uHwpaGRmHBtaEJtFiWpOkS9u/CGvh7+9z6WCnJLlbLkSYxqX9XDcaE7NmzwuMpX+zp9DCP5K09L1K1/PiSfkVf73bUqrmKNYfGzJfCKGq9ka7ksjriuTg398TUSlZ14RPqLKfs5YHOvuj3crBD+x4jOH0BwYZ7Bc/5Q==
*/