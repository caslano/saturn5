/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FILTER_VIEW_ITERATOR_05062005_0849)
#define FUSION_FILTER_VIEW_ITERATOR_05062005_0849

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/mpl/convert_iterator.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/algorithm/query/detail/find_if.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/placeholders.hpp>

#include <boost/fusion/view/filter_view/detail/deref_impl.hpp>
#include <boost/fusion/view/filter_view/detail/next_impl.hpp>
#include <boost/fusion/view/filter_view/detail/value_of_impl.hpp>
#include <boost/fusion/view/filter_view/detail/equal_to_impl.hpp>
#include <boost/fusion/view/filter_view/detail/deref_data_impl.hpp>
#include <boost/fusion/view/filter_view/detail/value_of_data_impl.hpp>
#include <boost/fusion/view/filter_view/detail/key_of_impl.hpp>

namespace boost { namespace fusion
{
    struct filter_view_iterator_tag;
    struct forward_traversal_tag;

    template <typename Category, typename First, typename Last, typename Pred>
    struct filter_iterator : iterator_base<filter_iterator<Category, First, Last, Pred> >
    {
        typedef convert_iterator<First> first_converter;
        typedef typename first_converter::type first_iter;
        typedef convert_iterator<Last> last_converter;
        typedef typename last_converter::type last_iter;

        typedef filter_view_iterator_tag fusion_tag;
        typedef Category category;
        typedef
            detail::static_find_if<
                first_iter
              , last_iter
              , mpl::bind1<
                    typename mpl::lambda<Pred>::type
                  , mpl::bind1<mpl::quote1<result_of::value_of>,mpl::_1>
                >
            >
        filter;
        typedef typename filter::type first_type;
        typedef last_iter last_type;
        typedef Pred pred_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        filter_iterator(First const& in_first)
            : first(filter::iter_call(first_converter::call(in_first))) {}

        first_type first;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(filter_iterator& operator= (filter_iterator const&))
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Category, typename First, typename Last, typename Pred>
    struct iterator_traits< ::boost::fusion::filter_iterator<Category, First, Last, Pred> >
    { };
}
#endif

#endif



/* filter_view_iterator.hpp
gDKTqId+qNezdW6nkuc5jblI7okvGUzGjs2/d4O3Xx3UTuL6Nc97YPcA8Ncb1j7EKaM01nXcdc1l21FuMH5HRIUTBXWi9JB1sIPxybCbY3yVCKIoypqtxeS4PdY737MbPDZ9GeaU88jYYigGrOdfNPF3d6MkD6hTiK3HH+N18s0N6/1CSiM+jHyxOa4+B529z0WrTcIizcMs403bHVIO9N0nsDW+pHk1jbNYPL7bA9d0O+x5gnU25gZFkgWqD/PgV3yczJl8B8o4KuK4jiipx68s2bYsB1kaoSjdmGqlzHQa48qE/TzjjUUV+W6VRbJMfl8+PmVTG2+P44w3E5lbe5WTyz46wX0xL+PrTf57hk4RxkVeyW6iNE1ug21iD3p17tWek0mssUul+Qz7eKtcQR7WZV4Ght7SzZgRJ/pHJv89itRPfTeO5OiRN6m8HL9g2KyqqzQqc4Vd0FjMR6zMURl7Zdxsf6hpNZjWAS37bzwfRV74iaNkbzzJzse/WJ/x/Cxy0tppR7x1TjWzaZ2hJlUUVePsN3k83L2b3Defl3l5Vof/973fbcmu52M3oLGfk7zuXdqg/4T54bDX4J5MuI1C4zDGGfAOhPv8TYmhVDh+cMqxkFlXhGX7eQZUtkcH6Q78gsJRznVYZ0ls8/YFmWZN9I6v4IWlo8OjjZ93wp2j++r4AWNxW8dbWX1ZznEY5JzKqfMEXDfOTP+YAgM790Bg7QM6jUb6JzSWHZKRtb4EGe3xZ+D4gZPO6i3b9j1xiOMAkPXSypo7LDH85EXD7tLm64vAjD1E0XDg5x4k8ZMPMzSDrKMfEv408N0dvi79HXQbPVhj7R31qJ72tdgLwPLNrd22Zj+pH8Ll626iMV+8KeW3g4EopH32iMZM3Kh16m3vQyXPpM2WKh/y+iXKx6mHsnxg/LA+9TCN4TsJtLHuU8BhjI+tqLvovvVwjbcVYjCwdpt7hMZ3lFSNRV5OAzte0bTreu6RGj9RSUT3uEPbzsfRhmMVQtnkaJfTkD8ea7fj7KM03lYWgUY/leU9AfxELU83PvI/Oz+xzOiyd2nH16Mvg7Xn5rlHazxTklibqvXDxEHk+P6ysaCxTDmZ2F/2HmX9ZRwYY/Ygytetg9u2dXDq6FiMrlfgHr2ocdxeDXWkbVboTv9tk2ONAbc6w3F8/jdslYDrrp2Eg7ylqxJuchwA3M3/FrjOeTnsxh59NWD42mnYYfxiLIaEGJjDV9cYbs9i2t59F5hJc/EKs6WrdxF+8nzEbNbOd7DIADDxbmAsW2HD/gCYifEiUHfiGhrLxghrq3PAjLU9hg/Z/dck3GXnL8WCvH52Mg8SgI3QLLCTbJvRTp8FduJcxOvhWl28Foq8cgyfD612v8+1gR2rOxAc9ftFhmVrChtb97kOw3UKj7IDN3HNZvUqrqvxl4gXo/MKLNfZJOhmup2uxzGSyGIVgc70w8aOHfabhJm8VrE8nQF2ct/ZewNgJvoOh60vsJNjjyAOyB7CWnpn+4Z8FCPmhl2MWV9nQGcx/9Due2/E6JvWYIKcN1s4nc71ta/qGxO9ifdAU6Phcx7f5V5TEUF75000jR42NiTIW7opaJIL38/fTH8fqO/wyZ6Z+75EhLlfFVX9f8QuXFgUrU/g96m4xY437x0+0vpSho3jW0HRIdqpPLofTHE6eawA7RyjKf+wGKO338Zo0pZMR1uTjwYg4zTHkRdg09c0aMpthRlz/hcjmnRPAZ6L0/j+oI0lHif4RztAo4Vx61jfaBtxFUk7tvD4/vzj15r2hC3mW3qyJpVRYBP7Uq+jUzZN2XKC96Kiy+g1Wzor4H3aNklTdtRSgK540P/M6ariTf4=
*/