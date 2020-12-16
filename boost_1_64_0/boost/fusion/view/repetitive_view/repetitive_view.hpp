/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_REPETITIVE_VIEW_REPETITIVE_VIEW_HPP_INCLUDED
#define BOOST_FUSION_REPETITIVE_VIEW_REPETITIVE_VIEW_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/mpl/if.hpp>

#include <boost/fusion/support/is_view.hpp>
#include <boost/fusion/support/category_of.hpp>

#include <boost/fusion/view/repetitive_view/detail/begin_impl.hpp>
#include <boost/fusion/view/repetitive_view/detail/end_impl.hpp>


namespace boost { namespace fusion
{
    struct repetitive_view_tag;
    struct fusion_sequence_tag;

    template<typename Sequence> struct repetitive_view 
        : sequence_base< repetitive_view<Sequence> >
    {
        typedef repetitive_view_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::true_ is_view;

        typedef single_pass_traversal_tag category;

        typedef typename boost::remove_reference<Sequence>::type sequence_type;
        typedef typename 
            mpl::if_<traits::is_view<Sequence>, Sequence, sequence_type&>::type
        stored_seq_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        repetitive_view(Sequence& in_seq)
            : seq(in_seq) {}

        stored_seq_type seq;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(repetitive_view& operator= (repetitive_view const&))
    };

}}

#endif

/* repetitive_view.hpp
jswodjT7aRG7MBn74F4OtFdifLbFfcDJrcdLKhb2hxgvwuR46TY8Ec0lrB0MHsj3f86LeM8uxlJ7vB6FzenZlc6vLxkhP0i7fHJrfrqOodVnNiRjvD/lmSiu/cJulRrRgfK8LO7LhVmbBD6ia0cqa3b2BF3HHP8ywgiWZ+du2X/QvvGKEeaAtLvVx5yjawdaQ5bu67kZY+k6dg3vW0Fa/a03t1B8aGmZ0ef50OC62hKLdLpO181UNjDN4xrULmgOZknWk+noOo2WhlnrpjU+KRaHNoHZhVpNv9H174Y63dqi26ZSfKms/Xz53CIGrQlrl/TPHtemet40wkiQluv52z7ULmi1mVUqNrUFpbtlhPTMhh57UJmu/WgBzJpvepGGYkebp2Nt3f/3+mR3xJ5S2OkDlXxoLKWympPe16d6prISlrVrabzcNcIWZpZ/Yii+JDQXsy0Rgy0UA94MzmJW98E1PfW7B+c0i6FTN9tjqst93DcyW6+ba6IYHhohG0gbvaw10NhNZfl9avxG9Uxl0flOZaH4HhmhErMq/wouRTGg2ZmFNG5Qh8YEWmZmeXbc3UP1fKQub8b6PPeonqnSec4VP0H1TGU5hmz/k+r52AhZmbU8MZLmnwNtNrOoLDMiKU+0vMzoHAzN/sQIg1hbR34otVEx+Ld67C6us6ExtQtaaWZ+Ie1/pfmHtlhYB7yPdG+/QzG4/xZrlrCUz7qLNkNLyyzlc8aizVLZiKiQKRRfKuNrSMAztUUNvdmP2iyVpZwZi3UilQXmLORHMaSylO9siTGRyvhaF4/WntnJxP7dqC7PjZCbWZbYXwtQW6eykNqVz1J5qayt/5UvdD+fyty3DmamNktlb/96LPcyL9QWO9+ylNollcWNivahtSeVnS7dqyzFjlaV2Y/bzWi/CS/FGYSwlDMI8V2Ml3Lv2xEiIlbuzzKansehLWOWeX/5G/R9C7zw12HWrwXMVcz+2gijTNKqjY4fpxh8EGu5sI7pJ1tpv4I2gllihzzn6fskH42g10k7EfL4TzpT/WSEliCttzNsNZX32QhdmOWr0vMsPcNE8yNTP4uMQQuVJs4uRJ74U8gDmGX7bC1M6dCW+Erb8P74EjpvNZroPisM/17WbaB77zi0Fcxa1g6k73e4TSaIM0jrO64jPT8CiwkqMbs5blUE7avSmGC5SdqggTPk95IzmaAClafek7jRSjD72GzoEXoumsp6Xd9sp70aWh1mawJ2Pad9R2YTNNJJO7q6E1lSFhOOQWkj21R5QuVlNUEUs1XnLaPo+x3Z1OnezbzoR/FlV6fr3nwo7WET0fykqfc5aKHS1Pu/HCZoy2LIOXvecGrrXCYoppfWwffINyovjwnqs3TZDj40UlvnNcFOZgunfClMYyLQBEZmdXUz3lKb5cc8WXlvZ78Wa3kXSCxkonfYdIII+PFy/a+KJeDLC84xq3z/y2ayINF/wmhOo9mLmKCaj7Tqa0KWKpZUygTdQdp888/8irlLm2AEM5rTaAHBJghjtuH92xaKxaCNYhY9xfRaMUcZE7Rgtuzft5YoFofWhdnltu1qUgxlsd+liX4XeaKFShP9LvJE683sVs3AjZSunAn6+jDrPnSiWAvAWdVE71vrDMWh8lYYr1hkNRMM0UlrNnT5Q2H4vU/RD8LY2goJaI38pG2bEV5aMXtDEzQFaZ9spsOKxaB1ZPbnuBELFAtoJNpM2JxrPS5QOrTKzL7W2fdaMQ9aC2ahS9dGKuZqjG0tTbS1iA8tlBlbWyER7SlrF0evwkbFHKHqei6x2vopFo/Wiln3pWMLUbs0NcFKZgsPR65TLAktjtnfu+uJfVU4JPwqrQv0hco=
*/