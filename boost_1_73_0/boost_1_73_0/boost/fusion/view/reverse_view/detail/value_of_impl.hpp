/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_IMPL_07202005_0900)
#define FUSION_VALUE_OF_IMPL_07202005_0900

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/prior.hpp>

namespace boost { namespace fusion
{
    struct reverse_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<reverse_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::value_of<
                        typename result_of::prior<
                            typename Iterator::first_type
                        >::type
                    >::type
                type;
            };
        };
    }
}}

#endif



/* value_of_impl.hpp
bgS+Ft1FRvK2Bt1WJL5TkY3YqOyad0ZD24yJrw3VQjbasq1X4oQDbwCgG4pVvra4I8vXX3y4RT6xf6m/QVOtfZkC0aedTMLAz9A8vgHvU6YbTd21/aR+pJTLWm6gNn00MYenqT9sFqueeCNscbhlrJhM15Tl8LMzql69nBwfPf7GQT/bGtKx+8T92hqrBopRKtGuFCZyVbYe8SAZZVHAavdLrUOrVRqeod/CUPL6Ccl1qtCSJsOkYg9CZXQ1Itll4vC1nRZV5OhOzDYT+4bRWLCUyWxEIQFx4yfyL/Ri0fn4v4O4lV1laqcxcGCpysQLBRWe5InaNfmtk4KgZ5eU5hucAtqOWp6v/N5iIovUJNd20InMyEgGvoEvK8Ga1psdBgUPGGAgbDssyvgmcxBDJKGDX7mGwfeslCo7w0tsO6lk0T9ANTshkD4qSIGkWGCXi5mKcjoKw6c0G+D6qsjCdeyzIkfcjZUD1Tk+bTqr5MwvltMTWwordDCgtUCJAmSrCs6OeBA7jyJObFkcwmQPYLc4Mtif4jhIcZ4CwLfm7ZGDKaCNb2SAxJiWqSD2MxpWPYAjyP4ueT/ofcQkAhw40tnwcOKJxEOvO81aFanT4DVypwBiy5UQ1vjQtOsaNPJwRGWYd1eJSME9hGm/
*/