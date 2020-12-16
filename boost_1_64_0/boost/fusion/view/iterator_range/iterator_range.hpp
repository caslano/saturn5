/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ITERATOR_RANGE_05062005_1224)
#define FUSION_ITERATOR_RANGE_05062005_1224

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/iterator/distance.hpp>
#include <boost/fusion/iterator/mpl/convert_iterator.hpp>
#include <boost/fusion/view/iterator_range/detail/begin_impl.hpp>
#include <boost/fusion/view/iterator_range/detail/end_impl.hpp>
#include <boost/fusion/view/iterator_range/detail/at_impl.hpp>
#include <boost/fusion/view/iterator_range/detail/size_impl.hpp>
#include <boost/fusion/view/iterator_range/detail/value_at_impl.hpp>
#include <boost/fusion/view/iterator_range/detail/is_segmented_impl.hpp>
#include <boost/fusion/view/iterator_range/detail/segments_impl.hpp>
#include <boost/fusion/adapted/mpl/mpl_iterator.hpp>
#include <boost/config.hpp>

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning (disable: 4512) // assignment operator could not be generated.
#endif

namespace boost { namespace fusion
{
    struct iterator_range_tag;
    struct fusion_sequence_tag;

    template <typename First, typename Last>
    struct iterator_range : sequence_base<iterator_range<First, Last> >
    {
        typedef typename convert_iterator<First>::type begin_type;
        typedef typename convert_iterator<Last>::type end_type;
        typedef iterator_range_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::true_ is_view;

        typedef typename traits::category_of<begin_type>::type category;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        iterator_range(First const& in_first, Last const& in_last)
            : first(convert_iterator<First>::call(in_first))
            , last(convert_iterator<Last>::call(in_last)) {}

        begin_type first;
        end_type last;
    };
}}

#if defined (BOOST_MSVC)
#  pragma warning(pop)
#endif

#endif



/* iterator_range.hpp
tPPK01pspBUFXhgktU6RdniBd7yZVnhdo63TIIqsuC6XRxMk77i17Lktv0MNuTQOAzdKwrqxI+SwIXemKeeVrmMVTiX32GV/kcvBxwiT8wV1ryxPHKuh/KawgB81U7YUlE+/TKFjRw+bQtAxLpPYfu7bqV3XpbVgyCCPl1keXeGR9qdBVtdl4OVUlSkE+XjwZ952RSTdDXmZrhZHvm+qbcTho+g5vE6yMvaLKHRYetETPXcsLLTsvZmsS501c3I7qPP6uGgpQm22fK6IRrpu5rq+ncd1ZvOIHhNY4iVFOZ9mypbCof5QhlFeq01WmkLwSWnKPCwPfd8pk6QSkaa/ePO7ni9eGEp+q2PqWSPmlXMjg7fMKPh2deh7+SjFqfGOaasKDApfb1mDc3kiR0UDzonpSRw1CQTngsHJSpYUOzNocsyzi3MT8OZcszNbczBi8zKPgBuDQ6PMv5rIQZlhl9Tm8Lc5vzjm+EZm8D2f3w+8oezc9vWDe/IoOtM27MBePJUx8F7Z4vH2wHlTi4c2QVxn5iZzmmdKPwMPo0+r/dPrcU6z/b/C8Mntf/fr1xx8Mbht9RtauKpD4HM3aOIqBeCrCkfXbe0tXGrgpi9ocUOOUcSI9201hhmalDTa9uCNgLc+9mZ7vK7J41WNupy9cZOH6gbneS0OqhzpXQan+RHjOnziJnvxuA7/YE8et9dePNjmNfXpgxM4pj4dumkbb+rtWXCaY7Gxdm9zGL5xMwNfbo/Dl4Hja97qG+XNOafZNy4yfHLfuPctxhxzPIIOGvgTSq+l23O3ZDjTg1Vg/APa1IOf7cnjenDiVnvxeH/8ouZhlsH7+/1v3cR5fz/Xwrme/QU4Jnetb+TGbZqc9jfyV5zDGgi2/7cFh01gmuPyhRavPS4/5HaTOU39fpPi8YVRs3xzt29y2uU7O5HDv4eXKw5Wbs23rtM7NHG+B/alJt6YY9zhjoSrfSAqtzkXMTifaXCyEhRw0jsZHPP7brTVrxin+b0d887eeRKvneYdDjEevm/sHN3k4PtkvDdxF4bLb8z4+wusNZ6Dc+au4LAxkX2H7jaZo3OL/QzwWmMnyhPeHRxjbDTmDMD5uMZs7u6hORiXkNe5ezKsMY50xvuL4JnjgPGtuRdw3n+NerkEDu9zzXbeuLfmNfqK0c6z9wFnrOtmn5W42q/cW8/vcF9w9tTzc+Dsred3vx84f1fPPzqR107zIfcHb089vwDOZD1ffADwlp5fALa3nosHgrOnnn8FnL+v5+mDwNtTz38AzmQ9X54Hvqee/xictp6fOAzs7+r5ZfAm6/nTjgDfU89/Bc4/0PMHa97een4FHK7nuFP7TL6vnJSp46TuVXsG0xvL0kb7h9oGZokukDTOCh8JBFdkqLw4KwSO6zGDgX4eBuV9wwQe3oqCzWSLoxbsZnqjCRyiDDZ6/B2033Aem4sNZjg25HlG/Z4Y8PoNvSQowuSa7TCw72rG97AyKH3bzl3lJ8Wyl7x8mXkWGPv8PTfgezmOFfhJ4NFbyA8mhfCO5xa5VJQaD8+a/J3tC0y+EFHqlWnkOoKuZxTH5Z1mvUdOEdTuX1eV+9cFfVPkaPOc8WcD5sMhy5zCKgIhIwjTMX2Ed2FM/oKXB3ZhR6GQSSlnJSSWazH4+Wb59oWdR1EYhr547Bbd513p0+3sVTix5K5h4UPkg48z85mUke+HuSdojOF7UG8yeYtlkVLjZI5o7NR3rvP13twzud1tbDmJH9pmgZQ/2MLXjcJqZgP2u2Y8C27u5k7sUTTwyikjivneZWnKZCLwCj9z40TYRUGKoFWJ768OTJmHRn6WlrZVCmStlVhn7Cf2rClre6JM0tg=
*/