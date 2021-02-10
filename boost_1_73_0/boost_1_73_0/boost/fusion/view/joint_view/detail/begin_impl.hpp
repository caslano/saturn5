/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_07162005_0115)
#define FUSION_BEGIN_IMPL_07162005_0115

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion
{
    struct joint_view_tag;

    template <typename Category, typename First, typename Last, typename Concat>
    struct joint_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<joint_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::first_type first_type;
                typedef typename Sequence::last_type last_type;
                typedef typename Sequence::concat_type concat_type;
                typedef typename Sequence::category category;
                typedef result_of::equal_to<first_type, last_type> equal_to;

                typedef typename
                    mpl::if_<
                        equal_to
                      , concat_type
                      , joint_view_iterator<category, first_type, last_type, concat_type>
                    >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s, mpl::true_)
                {
                    return s.concat();
                }

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s, mpl::false_)
                {
                    return type(s.first(), s.concat());
                }

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return call(s, equal_to());
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
BOo6CtkB5F3KhCdZaW46qKOp/k/jcnDVwzhAL38G4yAMhtcDesEqxDcv8OH+HNVPW+QrIefr19yqA77ppTK/BK1f8j367xHa/zdQSwMECgAAAAgALWdKUo1EFeQmFAAApnkAAB8ACQBjdXJsLW1hc3Rlci9saWIvZnRwbGlzdHBhcnNlci5jVVQFAAG2SCRg7T1rc9pItt/9KzrZqgQcsA3OY2LH3mVsnLCxwQX4ZrKbKZUMwmhHSJQkYvve+L/fc/ohtaRuSWCcOFthJgb6cc7p8+6X2N5c32uDbJLCl0H/GfCCd9rj3Pf+Y41CdWvD+EbYf9DrC7wXIdkmcZdvRpUUd/lGKrSLwbG8w8+GUYToC9KGf7ax5xcDP0IJdMOeR9781revpiGpHFVJ4+3b30idNHeajRo5Nl3bcsggtNxLy7+qkXdjWvKPqXlzsxVYhzVihcR0tjio4dQOSOBNwmvTtwh8duyR5QbWmJgBGVvByLcv4YvtknBqkYntWOSod/65031fI9dTezRFILfeggRTb+GMydT8ahHfGln2VwZjbvoh8SbQHYCP7SAEgIvQ9twtwG2R0PJnAcJA9KYTeMT8atqOeQmIzJBMw3Ae7G1vjxa+A9Rvj71RsD0Sw9+ahrNoJJ+BiJl5S7x5
*/