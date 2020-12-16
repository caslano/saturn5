/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ITERATOR_BASIC_ITERATOR_HPP
#define BOOST_FUSION_ITERATOR_BASIC_ITERATOR_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/iterator_facade.hpp>

#include <boost/mpl/and.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/int.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion
{
    namespace extension
    {
        template <typename>
        struct value_of_impl;

        template <typename>
        struct deref_impl;

        template <typename>
        struct value_of_data_impl;

        template <typename>
        struct key_of_impl;

        template <typename>
        struct deref_data_impl;
    }

    template<typename Tag, typename Category, typename Seq, int Index>
    struct basic_iterator
      : iterator_facade<basic_iterator<Tag, Category, Seq, Index>, Category>
    {
        typedef mpl::int_<Index> index;
        typedef Seq seq_type;

        template <typename It>
        struct value_of
          : extension::value_of_impl<Tag>::template apply<It>
        {};

        template <typename It>
        struct deref
          : extension::deref_impl<Tag>::template apply<It>
        {};

        template <typename It>
        struct value_of_data
          : extension::value_of_data_impl<Tag>::template apply<It>
        {};

        template <typename It>
        struct key_of
          : extension::key_of_impl<Tag>::template apply<It>
        {};

        template <typename It>
        struct deref_data
          : extension::deref_data_impl<Tag>::template apply<It>
        {};

        template <typename It, typename N>
        struct advance
        {
            typedef
                basic_iterator<Tag, Category, Seq, Index + N::value>
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(It const& it)
            {
                return type(*it.seq,0);
            }
        };

        template <typename It>
        struct next
          : advance<It, mpl::int_<1> >
        {};

        template <typename It>
        struct prior
          : advance<It, mpl::int_<-1> >
        {};

        template <typename It1, typename It2>
        struct distance
        {
            typedef mpl::minus<typename It2::index, typename It1::index> type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static
            type
            call(It1 const&, It2 const&)
            {
                return type();
            }
        };

        template <typename It1, typename It2>
        struct equal_to
          : mpl::and_<
                is_same<
                    typename remove_const<typename It1::seq_type>::type
                  , typename remove_const<typename It2::seq_type>::type
                >
              , mpl::equal_to<typename It1::index,typename It2::index>
            >
        {};

        template<typename OtherSeq>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        basic_iterator(basic_iterator<Tag,Category,OtherSeq,Index> const& it)
          : seq(it.seq)
        {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        basic_iterator(Seq& in_seq, int)
          : seq(&in_seq)
        {}

        template<typename OtherSeq>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        basic_iterator&
        operator=(basic_iterator<Tag,Category,OtherSeq,Index> const& it)
        {
            seq=it.seq;
            return *this;
        }

        Seq* seq;
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Tag, typename Category, typename Seq, int Index>
    struct iterator_traits< ::boost::fusion::basic_iterator<Tag, Category, Seq, Index> >
    { };
}
#endif

#endif

/* basic_iterator.hpp
aY6p0Sd0tscua+Q29fd0/bF4YLzPEg/bGeN4tvPsPFccL5Azsjlje6GxsfYi8/xia5Dx2Wf8Z+acDVbP7/teDqnSZUIs7Pte1tjlkAptJhxe0mswbWpXch8zUlf2vTTbZClQp8eMpL+1XmYbe034OwJzwTlkKNJkSvKZ4iNNniZDIsa9wCYZSqQ8x1vay8lHIBfRl3sOkJWTWEYfVOiSdH2ZA2r0mJF8jjXDHsfU6BJoI8kKRU4ZE82aCwpyvSfH0ZeKx+MybSYknqdvtjmkTIcpC8+37slRoUf4BdrkHI6oUTfnAyLGt8EBReI54+AcGgw5Nd9TUuLJ02DAvLnfI0+dIbFDY2KXY2oMCL9EbGySocgpi8a3RY4yHWakXmae2CWi70W22Mxq17k6A8JH4mCdPfI0GLJprg7IU6fLhFXzWnyF/hkRfaX22WCfE+p0mBA/lm/OIUuJBgPCr/LcZo09jqjSYfq/PSCW2CJDkVNGJP6358M2Ocq0CfLGzyrncECeOj2mLIt7iwPa1xTzbUJB4bXyTY8ZideJ53+frS/+zPObMbl3GgNnn98+4ITJ9+Tx5wz1yzZZ9n/lOptvtiZpMWX3LeaBBvNvlTsO/vdZwiYjYr8xds4hQ4k262/z/GNNDIX3//fz92mWvq8umz1tcPS/z5eefaa0y85P9M3KT42T7P8+r9kjMK4UDbEOiPz6v58xPmjLQ9+Y2OOEU6YcWwcRcSxwxNI79E2GEh1mdD6pJPm/z6ovsc0RDUbMyV+ehHhXfmwcZCnRZsLhe8RLj7A5WWCPKh0mpKviokaf0IfUY50MZZqftSab8sERddpfEOOXxdjSPzvkqNBhRuor2uGAMh1mpORpjX2KnBL/mnGyyQFFWkxJyekGJVpMiH/dmmSHYxoMiXxD/GyyT9s8H8vlykfV5YgafcIf8zzkHBqE/rdPQZoT6gyI1NXjHHKU6RJYx3VOzH3b51xm5iL5Q32x9iPzw5Qja6fHjORAm0N9/1Id6vQIrKEUU22lffgzL/YaPWYkv6lddjikQptiT45H7nm3tU2sLC/s0CEw93NMfqOd8X8/43pzziFLhaq1ePPPWGPkqNAlbN5vzjbHjFhuyjOxzzlmjwIdgs/LPZvkqDIkZq0ss0eB4FRMbLDPCS0mJL5onKQp0GHG/Je0S4YSXULW3zybZCjR5v+fHY/L98rAWOX0gIWRvNTP43M9+qVImxmpb5kP9inRJfRt97DFITX6hL9jrbJFlgo9Ql312eKQOkNi3xUHaQq0mJJ+u7HTZETMcz9ZUpdj6gw59bo1ZuVdzjMhaq5zn5JjBmx8WiyUrcP4+9RljwGRivxQpMWUhNfBVdLUSX5Ae5TpEvqg3DK0viP/22sjcyG5YUImIt7vexzRJqm7yaV1FBFnTXwdBtrNel5tflI/VLm5edkeyMPwf58pJzYyxr/KAet/U5e1v4ufCm0qfiZucY73bA6p0aER8jMVCT9vLXNCg5Cfu+ao0mX1gr5HZPdC7icU8X0cK5dwnhZjTmN+XmPe94RrZxLqU6JD23tEM+au4F4W/Gy3ziEVIknnSJMndSV9U0uJg95V3U/aPB1x8Ga5e4u5YEjY17Ujn+kL1I2Zz3OKckaGAk2GjM9ybc3MscZuydp7p5L4u5QsvFu71sYOi9qKXFDclC+kX+3nSZzFUZZ3dVuMqXicO6vH9KyOeJcq1qq11GDLccgaWWGbvHVSZcxm1XxdUA5Zdt8WSx92nn3yNOgTfMS6I/dDsZrzY/NcNJfH5isqxvIllOYgJq8hOcxoK3T22l2TM2XR2hqSskaXWbiQ+aKgXp2QPA3kM6nc/IFjgh+p/2M5+ak=
*/