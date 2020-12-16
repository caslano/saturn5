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
Gi9zUo5HWioTLYYZzz3Ay0yRn2GVzK8YmvweLtaHlo8Zzy8RrTmzWZfzlRbmR4tjxvOzrca2MJPvrMIy0XiZYzoXtFCZaDHMeH6GNbzM0PzsaEcVs6Gt69H1JdlavM9h5sj9mdriQWunkdb1WKATtXM9fl7FLGOXlZSff4MZaoO0Isu2ain3jfgMXitt557bR2gdbTaDD6QlV7WtpPm5BZ+zM6v6cNpbYbDVDNWZDWiweh61E83BbP6sgTmonWhDmT1ctswmzLnNDH5mdy3Vs9H6226GJcwqbZ1yQZhjhxnczDwZZ9ygMdpphgrMjr9p0ozaiVaSWfc/Rv5D44AWx8zy8H45yv13fP7Cc3iX/gmVicb7rHP3azWoP9F4nzX0BYtRO3eF9tmB7NYNlDvaXY200vumG2mN7cHPgZhVTns+N+09+5TPehRLN2j5EmHWA2aIYNbs0JG5NF/Q0jBrXuf8EJq7aLeZ3Zzd6jTl7jPDz8wcTXfepLagnWJmm3b6A9lBPENLY2doLPMQ3muz/MqeOJlE/XlYPlNFY893sT+P4PNdaez5LuaAVorZi0xzrgpzo1VmNmbyTzmpr9GszE6ax+Wl+o6q1IfWj5nJ/MNhKhNtK7O9FYvMobV5DJ8XMKPnBWhBtLbMhlr39KN1dBznhFZapvh2P1OZp/BZJUh7v8S6ktp5Gu8NmdG9IZoLLQ8zuu9A86rEBVXMdiZ1c6I1U8a9OFr23PV609w9J/fkEinPiv83jbQ+b6uVpL4+r6xbxdxb5tgodz/OQWZ8DnrRSjG7e7DpeGFwAZ/NRH6zkmg5NqbvQXPplhmmMlt/vfhZYY4/zFAWpNWdUeg97T1oRcKlpeutLUA5/GmGTSDNuq7FPzS2L8zgYlZp4IJW1C9/maETs+6HtqWlMtEimdFnS2hBtHhpoWvzpRl2KfPsB7TnX8t6aZ9/bYaWEdIiy37aS/3yET//C5fW+lx0XhqH/8zwJ0hbWvr3sTQnvmIcs6Qa5xbRnAALdGLG8/OgRTLj+Xn/bxppb5u6CwsDrQVeKHGl0Dw/DE9PczfMAleYDTU0uEI5hFvgZ2a+msOpPj9azjBpOy1/zKbxi7SAA6S1ud7+b6ovnQUaMjuZtsJbyg+tEzOeuzU95seM525D26yMX2m0vktOzaEx0lngELc7f9envc5ogUCYtAGf292j+ZLJAutBWu8OL59R7pktMIjZxm7DatLYZsEcmPEcgmiRzHgOkNUC8cz4/HSiWVkO1fdfKk39kgPjNNLWDi+eQO3MaYEIZlkHHtVTXLQFJrAy+0+OS0NrOo8FlrC4o70zFaK1ktcCw9N9szJo4z4V+0DzpZgFSipxZdH88VmH05ywWeidceXQjpgbJFFccQsUZdZt3bgMtF+j6Znx+0YPtxT3Tj5uKZ6VBLileF4AJbiF3odbQ409Q8Ic0Loxy6p5PovGAS2aGb8XhZLcQu/HbNxSPH9JRMvBbN+Jh+tpzvO4FM8nfCni6Pc00II8LsUzAesPoXFpKy/KSPMFjcfRczA0F9oexcqjNQz74KV5XcoCtZilq7UkmvoM7TYzs+ftfGpnaQuUZTZAW9VC41DGAoYwaRG5upgohwqhcdVXTrlFbUErxWz1gP7Zqc/Q4rXSSo1PpPXgrWyBfiCtcYHGOuqXKqH19brp2k9zFy2WWad1A2i+BNA+Mrtd3KrktynMGmeBLYpV0GwKG1erR4wwqJq6BdAKa6VNGDP5nTBPDQsU10irdwVWU321LDAGpBXOd/mcMD+aJVJa8vCPrYQF4y2wgZXZJve+pcIMjSygDZeWp+qGmVRfcwsYWdx3d/tZhblaYH7MHiaO6E05tLI=
*/