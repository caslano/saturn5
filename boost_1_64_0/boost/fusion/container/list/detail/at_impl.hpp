/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_AT_IMPL_07172005_0726)
#define FUSION_AT_IMPL_07172005_0726

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    namespace detail
    {
        template <typename Cons>
        struct cons_deref
        {
            typedef typename Cons::car_type type;
        };

        template <typename Cons, int I>
        struct cons_advance
        {
            typedef typename
                cons_advance<Cons, I-1>::type::cdr_type
            type;
        };

        template <typename Cons>
        struct cons_advance<Cons, 0>
        {
            typedef Cons type;
        };

        template <typename Cons>
        struct cons_advance<Cons, 1>
        {
            typedef typename Cons::cdr_type type;
        };

        template <typename Cons>
        struct cons_advance<Cons, 2>
        {
#if BOOST_WORKAROUND(BOOST_MSVC, > 1400) // VC8 and above
            typedef typename Cons::cdr_type::cdr_type type;
#else
            typedef typename Cons::cdr_type _a;
            typedef typename _a::cdr_type type;
#endif
        };

        template <typename Cons>
        struct cons_advance<Cons, 3>
        {
#if BOOST_WORKAROUND(BOOST_MSVC, > 1400) // VC8 and above
            typedef typename Cons::cdr_type::cdr_type::cdr_type type;
#else
            typedef typename Cons::cdr_type _a;
            typedef typename _a::cdr_type _b;
            typedef typename _b::cdr_type type;
#endif
        };

        template <typename Cons>
        struct cons_advance<Cons, 4>
        {
#if BOOST_WORKAROUND(BOOST_MSVC, > 1400) // VC8 and above
            typedef typename Cons::cdr_type::cdr_type::cdr_type::cdr_type type;
#else
            typedef typename Cons::cdr_type _a;
            typedef typename _a::cdr_type _b;
            typedef typename _b::cdr_type _c;
            typedef typename _c::cdr_type type;
#endif
        };
    }

    struct cons_tag;

    namespace extension
    {
        template <typename Tag>
        struct at_impl;

        template <>
        struct at_impl<cons_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename detail::cons_deref<
                    typename detail::cons_advance<Sequence, N::value>::type>::type
                element;

                typedef typename
                    mpl::if_<
                        is_const<Sequence>
                      , typename detail::cref_result<element>::type
                      , typename detail::ref_result<element>::type
                    >::type
                type;

                template <typename Cons, int N2>
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Cons& s, mpl::int_<N2>)
                {
                    return call(s.cdr, mpl::int_<N2-1>());
                }

                template <typename Cons>
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Cons& s, mpl::int_<0>)
                {
                    return s.car;
                }

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return call(s, mpl::int_<N::value>());
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
Ob6Gx/B3+AvJX4ZFzv9wreSvM6ZK/nbJmDq34iC8DUPxdqnf3ZiId+B8vFPyuUfrayrne9hTlq/va/qhjHH0EfbA81q+5LwNl5rka6PMvwkjsFrGtNqMl+P3cQ5eh1fgFlyEN6BsT3KuRl2bbE/7pNz1GIz3YDjux4l4L87AA5iM92Ea3o8r8QFciw1YiA9iBT6EW/CHuBMP4i78Edbjj/EBbMSH8WF8FB/RxqqSczxcKPnWj1X1Zxl776zk9y84Gd/HVPwAZYxQOUfjb7IcbYxQudcehWvwMszHabgWV+A6zMJCrMYi2R6L8V4swfvQji/iejyBpfhbdMj2WK6VS86vcJVJudJl/16MsbgEp+BSyU8GOsfQlPMfOS8K8BhDM5D5xmM/+f5AtOMgvAqDpRxD8EYcivtwGP4IrXgUQ/A5HI6/xJF4CsOwCUfh3zAcw0g7AidhJGZiFOZgNG7F0bgDx+CzGIPPYywex3F4GsfjnzAOu1K2CRiMk3A0xmMuJmAxTsXtOA0P4uX4G0zE13E6tqOeZmAnTMaROBNn4ixci7OxEFNwN87BO3EePomp+BRegcdwAT6Padr6lfMuTDFZv5myn63AUbgSozALkzBbO57IuRKGmRxPKmS/rcQQvFo7nsh5D5SYHE9ulO9tQytuxzF4EybgDkzBmzEd63At3oI17Sw+jbNlHFur+Zha+caxtJqNoxVH8D52lnHcrAAZI0sZFyvcYzysWmwguMa+aiKYjXnlOd6V5xhXQTKmlbexrA4QjhI8x66qxqMExqpijKoWx6eSsamMY1LJeFTaOFSdk8kDoWZc6+NOyZhTMt5U8zGmstFsbCnzMaXMx5CqI8QTd562wD0e40V9SfAYI0obG6pCxoSqI3S4sZMliBBHSCPYCdsJBwknCecIHbYx5hMhgZC+zd/u6J/8k3/yT/7JP/kn/+Sf/NN3dfpW+/9L+3+WvSjPkX9xngH4KoR7ENKusEvupeyX9ou9hHv7suw4rV2BNow1xbQQ+Nw+dlPfZu1j0q7HkqStPg1HuOJoWtE/I3CF+v0iFuDZllSoPSM+RG0nyZe2cv24gfksTdpXpYwx0lZeLO33BYR60khsXsasgja2BZqUVZd/aXs25lfakHoZ2vGXSbtWOmFjX/I3Scbsc2SVq81abcgT6Zu3T2rtWlL/BOYrKS92mOTTWIfZ0h6/RdqfNhN2kc75WDWfduXpDbUipQHqm9ShMR/GdrBgaSs/JuvyGcJOpb7GeeaDhzF8yIPSPnrleK191CNPtjKHuw4lrqw01zOf8nyGcdu0Ncv7ecl7exKz4leEg0reJ3jm3VHKvdhW+9tIf5Bm9Zev7S+OSru8N8Ouxdlj9X1B2jv7GIzTj1dxWW/PcS69bxfb5ZmBWtl+ryP8RNkuJpqUKavMUdqGtlDPcsVjaICxXIla3IacwvI8Q30HXCr3/2WbvZNwM8u0emyz6k7vw7ZyIdvrEcnDJtleKwm3K+t8vEce+M+avOILzkMKNqrrTVmk5Etbl/kS1+zYqbX5nv0ftvkmqctJ+CJ8VPrnVTccnL086Fynbdeyj3dU4n/+SsYHDxYOPvv1zvrkN0c8yg3gf6jxje8uC7kj+6Gu13c7cUn/zx94nHYZtS3YMWjrZ5sX3rn8+sildwfEdTnT9jblNHX5b19n23H/gE8eO9tv1R+O1zwTefHami9Wm7JDzU/NA3e99t4LMTGbX7iyouCm+899+23N5m3l334b9OlgJT7+veFVEQd/+pMXy+z/CNzR6bULa4Outsg5jpz71FM3PdAhO9sGaXOowLFYiTPxGkzFKkzDjbgCN2EeXouFuBlr8fu4Ha/D3Vg=
*/