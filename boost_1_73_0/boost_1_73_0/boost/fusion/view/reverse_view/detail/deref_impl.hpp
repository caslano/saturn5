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
QBGsm0BLtMVNFgWSSuwe333vkZRvO21Q97AsvvP3TrYaP+5TgwY8+Ynsvwg/+G05rpT8l8dmNXUUfQH3B7k+4vdTSlowZfkS1eFpli8QWJbIazmk5yh6StFHso3+axHnx4ge8Q2yEWdXFmMlBqmBoFuHvVevfodtaO+2d0M4YrngGdwYnve4GoRwmNg3f6RsNNrR/E0I3ADLdryo21Ro0LJvHpnigM+ZiHmueQJMQ8J1rEQPf4gcTMqhLzIO3cur+9OLdyE8piJOSchYlqBTWWYJpOyBg+IxFw9ORsGUAdlHdhSeCG1QYGmEzHdQNwfD1VCTDFLPMi2BPTCRsR4qYgZSYwq932rFpcrQ+lYiY92KK/d3UjOceHKPRgzZGGRhwEgoNQ+BKEMYykT06RsBwZdF2cuETsOpNagqT1pSgeZZRrKQT3DtzOZw4+EJiQwKtFgY+tIy16TqMZXDOULEkaT0S5WjIsQBiRKJMIdQ5glXlth6XqnwmFqA14Zmam8CMkdjYKtzA6c3W9BjWugQPpzenlze3cKHzvV15+L2Hi6PoXNxT8LOTi+OMPQClSngo0JxjcoViGGRCZ5UOq+Pu+293V/hjI95sn3CdCryAfSR8BwZ2IBDp0QRuRExoyA6th/3adVqL0QeZ2XC
*/