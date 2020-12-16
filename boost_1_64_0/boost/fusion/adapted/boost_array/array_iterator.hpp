/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_ARRAY_ITERATOR_26122005_2250)
#define BOOST_FUSION_ARRAY_ITERATOR_26122005_2250

#include <boost/fusion/support/config.hpp>
#include <cstddef>
#include <boost/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/fusion/iterator/iterator_facade.hpp>

namespace boost { namespace fusion
{
    struct random_access_traversal_tag;

    template <typename Array, int Pos>
    struct array_iterator
        : iterator_facade<array_iterator<Array, Pos>, random_access_traversal_tag>
    {
        BOOST_MPL_ASSERT_RELATION(Pos, >=, 0);
        BOOST_MPL_ASSERT_RELATION(Pos, <=, static_cast<int>(Array::static_size));

        typedef mpl::int_<Pos> index;
        typedef Array array_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        array_iterator(Array& a)
            : array(a) {}

        Array& array;

        template <typename Iterator>
        struct value_of
        {
            typedef typename Iterator::array_type array_type;
            typedef typename array_type::value_type type;
        };

        template <typename Iterator>
        struct deref
        {
            typedef typename Iterator::array_type array_type;
            typedef typename 
                mpl::if_<
                    is_const<array_type>
                  , typename array_type::const_reference
                  , typename array_type::reference
                >::type 
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const & it)
            {
                return it.array[Iterator::index::value];
            }
        };

        template <typename Iterator, typename N>
        struct advance
        {
            typedef typename Iterator::index index;
            typedef typename Iterator::array_type array_type;
            typedef array_iterator<array_type, index::value + N::value> type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& i)
            {
                return type(i.array);
            }
        };

        template <typename Iterator>
        struct next : advance<Iterator, mpl::int_<1> > {};

        template <typename Iterator>
        struct prior : advance<Iterator, mpl::int_<-1> > {};

        template <typename I1, typename I2>
        struct distance : mpl::minus<typename I2::index, typename I1::index>
        {
            typedef typename
                mpl::minus<
                    typename I2::index, typename I1::index
                >::type 
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(I1 const&, I2 const&)
            {
                return type();
            }
        };

    private:

        array_iterator<Array, Pos>& operator=(array_iterator<Array, Pos> const&);
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Array, int Pos>
    struct iterator_traits< ::boost::fusion::array_iterator<Array, Pos> >
    { };
}
#endif

#endif

/* array_iterator.hpp
i/V0feyvotwGrwKWhPwbKk/DXlPugEfIEs+hPMpdlke5D/a5ZIkPUR5h9jeUB5wkOX9asnCD7dYkf0oeIs+Qh8nLXghukKvkw8k18kHkCXKdPEk+hNwmH0p+jTwq7F9PP0z9o/1g8g/ko8gVts8YeRXyiPp30Z8bL3976i64VHG8vNi151JFeS5x/XupojzC7J8FzwFLAu+lPIj8DeUO+GzlCvJfpVwDz3Xrg6fd/sGfgnP3V5cq3BY72x/+X+raC/5f+jfVf22htYvxdZn6D56j3ACPKLfBLeUp4VmZLNcDhKX8ylVwFywG5P9JuQZ75XKtb9irZLn+U3BNGOuDB11+cEO5Cz5beQZ8FVgStj/X5QdPOzv86Sj3Y/0f3PbovzDnC/h/hZYf9lWUq+B+sPwA76U8SP+VG+BJ5RZ4CpwkGd+F/TXah8hd8uFgOfEEH0FelnwkeUNygzxIPorcIo+RryKPkB8nH6r+kOvkH8ijYNmAm8/gD7lJXoU8TJ5DPog8Qj6YfPZVf9P4+BuS76e0/wJFN3ra9SdhkZXb4Alh9i9hqT7lKnhKuR/8mtse+AflQfBPyg3wws+447Gw7EZ5ClxV7oLnKM/QX+Vp+qvcAZ8tzPEE/5Ub4LlgSfDnceUKuCPcY/5E+Wg/nPwT+RBy5VnXX4Xt/4MOIvfR3iBvSD6MXCMfTB4kH0qeIA+RJ8l18lzykeTXyEeRu8/+8/33x2WW33Wv5xgXd5ZCfXyI5eAnWHawlAMal/PP88dS/4KLFu3xtvZP8CrCnP8XLbIpd8GDYEnglnIFPKk8A267/AsXPOXyg6eVG9j/p46x/ozyJOwLv+PGW8HLKveDq8o18BzlQfqv3Mb2JpSnwGe7/OC2y4/1p5Rb4NeEef4N/8FJkv6N8tB+mLA/Pg4XjsbHov74OIQ8z7tufKD85GFylXywcDQ+FvXHR5081/o/6ovrH0He691/fjxk04ush30qGBf7YtnBMg1vh5lvuPLnxks6flYsxsv7rr8IiyzM86+Ca8I8PxOWbMoN5G+B5Qd4UrkNbitXsb0pYZ6/CcvCbR/5P3V28A/KXeT/yTHsy36g45XlcYz8GypPsTxgSbCPKPfDPqFcgf1s5UmWx9mR/3HlPuTvKFfBXbd98IxyDevP86Ey7BXH2F+fchf5N1RusDzKLbYPWH7A3hDmfIj2cszyuPVZHuVJloeceR4B5aP9CPI8H7nxiPYhj5I3JA+T55APIg+Sm+SzyQeT55IPJ3d+Ye9MwOQoyjBcc+zuLARoJOCCUQYJsgYkE4m6YNRBoi4YYEKCLhJgkByTi3Tuyd0JARZISIccLBCggQALBBk06qKgE0RcLm0MwqKBDIqwYIBBUVe5/Gr+7581CSr4oI8H/Txfvv+tqq76q6q7Z2ePCXkKuUzOaT6PCLvkFHm8jk+eQHbJE3U88iRy1yP/oc+Tt3k0PcqfS13I585y8dQKcT1KvrB3sZa/+VFc+/frna2HbVffr+vgCm+OCvcnP0o+lPxz8mDyFvIQ8hPkoeSHyMPIj5BHkh8jjyL/gjya/Dh5EvlSJj2DfC/r55OvYv1S8v2sX0Z+IGr+qWM6lqxyfz4n/awjF8g+uUgeTda/d7+Y3MX6gNxDvoqc/I3wTHIz+SKyvn7PIudYP5vcSl6h+ZFXkTvJeXKJPIdstgmP0XzILjmvvx9KTrN+MjlLXk72yJeQffIFZP36Yyy5nfXjyEVyjhyS52r+5Bm6nuSryYnnhc/R/SAv1fzJ8zR/8vk6X/Jqsr5/WEbOkOeT9eulBbpfPP8KcoF8HjkkLyR3k6eQ9fexLiTr11uXkX1ym67nC3L+ueQkeQ1Z358=
*/