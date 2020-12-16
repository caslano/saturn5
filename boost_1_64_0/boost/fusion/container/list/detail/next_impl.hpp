/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_IMPL_07172005_0836)
#define FUSION_NEXT_IMPL_07172005_0836

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/add_const.hpp>

namespace boost { namespace fusion
{
    struct cons_iterator_tag;

    template <typename Cons>
    struct cons_iterator;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        template <>
        struct next_impl<cons_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::cons_type cons_type;
                typedef typename cons_type::cdr_type cdr_type;

                typedef cons_iterator<
                    typename mpl::eval_if<
                        is_const<cons_type>
                      , add_const<cdr_type>
                      , mpl::identity<cdr_type>
                    >::type>
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(i.cons.cdr);
                }
            };
        };
    }
}}

#endif



/* next_impl.hpp
tgOPNr+/yt91L4fD92zHvmf+bIfI8O6NUkdzpY5K3jPqhgXfJq/dcNQRMRnqSPxM6yhnUrZc66oj/ORapZ6CCN/fy1FP9p31q6dB70s9ub0HtnuZrw8per9WWRyWtSGDPjCvo/VtZH+87N/dhtxLfPkfGPQSc731t39rcn4b5W6soxgpR/c6ijOpowT3OpJ8nbPLka9897PdjjEv78JdZvlq/vdur93m7924tubPhH23qV5ibbnx94Lr2cjiZeX+bGTJC0yeDZM6srvXkTwbUZRvRFvHsxH4Yf2ejW/lujy39UkH25rXVcJHdZVJ89fZtx8566xpa4DM18r8f9cGWWuAHGuA7r5C8ffadHXIH9eesDBm/spLq7o+Xdy4NUApNumnSBunv5uduedQrzd8Ho6B5XAafBHmwAp4HXwZroGvwBK4BU4UO2y3wNe0NRLSH4BPmayReEjWSDwMR8BH4OWwBE6CG2AGfBzmw1J4E9wIV8An4ANwE3wMlsGN8EnoyK+0+eEck/z2FHt6veBoeBJMhr1hJuwDr4Z+cCXsCx+C/eClSnxwJhwAJb+0wT3nd5vk903Jb6Xk923J73bJ7w7J77uS3/ckvzslv+9Lfj+Q/O6S/LZpIW1taYP3R3rx/++S/keyJuRTmAX3wDvhZ7AIfglfg1/Bb+FeeBB+J2tjvod94A8wAO6Hw+ABOBL+DM+GB2E6/AXOgr/D+fAP+Cj8Ez4p9kY/gm1hS3Q9Fh4D28Ou8HjYF54Ao+GJ8ELYCSbAznAK9IZ22A3OgN2h1D9td8/3+3K53++FY+AKOA0WwRx4v9zvq+R+Xw1L4Bq539fK/V6sXxP0ruf6v1nqf77U/wKp/1ul/gthBrwd5sNFUv93SP0vlvpfIvV/p9T/Xdr9Lu1geKNJfkdIfoNhODwdToVnwivhSJgHR8EieBZ8EI6GcbL2aS4Md+WXtqbnNVB+kt9TYBDsB+PgABgPT4XTYQCcDQfCuXAQXAIHw+UwEBbDIXA9HCrpJ9ikTQnflvSPgbGS/qWS38skv5dLfq+Qco6HV+nWACbC1XAy3AaTXPmkjec5n2Mkn1GSz7Mln+dKPsdJPs+TfJ4v+YyRfI6XfF4g+bxQ8hmrq1f7bs/1OlvyOUfymSf5vEbqNV/qdS4sgtdJvc6Ter1B6vVGV35pJ3nO71TJb6rkd5rkN03ymyH5zZT82iW/V0p+syS/2ZLfHMnvDFhkrSmz1pQdwTVl+1kv1mkltkSQOCQPWY1UIDVIq/uxJYJEIWnI4vut9WWWs5zlLGc5y1nOcg11h3/+X4Z1m2n+f7Zu/r+DzHsr4xbD4Ctwjr9yUIs2rnyxmvaY1IzENMcYe7F5MYQTIXqccUIhPJ9DWtqzdzrYMT7nx9ZpdUy5xIaWunHmLviV6cfUJ82YYhP/cjjDZO5ji/GcPNUvSLs2PZ5LSdtwbpZxzoVwSurtZdz7g65qOG1NQTvKZBH0es01Zh+l6Z3DgXSmY+QzZRxfGxcva8S4uPk5Vs03Lm5+TpOn8fj//ji6+XlkDR9fb+g4uvl4/OEfX9+mjq+33/T95zuuf63g/WnbA9594NrPGze+3qGFvAfk/WBvqe7f47wl157AYbAzPBN2geGwK4yG3eAk2B1eDXvA66APvAn2hLfBXnAZPAmuhL7wZdgbboV94KfQD34J+8o5UafAY2E/2BH2h93gqbA3DIDD4UA4Eg6CZ8HBcBwMhOfDIbAADoW3wGGwDA6HL8LT4CtwBEw5qn7jOWJLWcZ1jDaUQxHj+I6ZrWSPdpLFNnL9x3vEDrKbrWMzO8fGcaAqGQvS2zQ22jI2HxcqNhkbMtot9jxOJDaKxT6x5zE=
*/