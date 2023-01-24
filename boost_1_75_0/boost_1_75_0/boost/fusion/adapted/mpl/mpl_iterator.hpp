/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MPL_ITERATOR_05052005_0731)
#define FUSION_MPL_ITERATOR_05052005_0731

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/mpl_iterator_category.hpp>
#include <boost/fusion/iterator/iterator_facade.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/distance.hpp>

namespace boost { namespace fusion
{
    template <typename Iterator_>
    struct mpl_iterator
        : iterator_facade<
            mpl_iterator<Iterator_>
          , typename detail::mpl_iterator_category<typename Iterator_::category>::type
        >
    {
        typedef typename remove_const<Iterator_>::type iterator_type;

        template <typename Iterator>
        struct value_of : mpl::deref<typename Iterator::iterator_type> {};

        template <typename Iterator>
        struct deref
        {
            typedef typename mpl::deref<
                typename Iterator::iterator_type>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator)
            {
                return type();
            }
        };

        template <typename Iterator>
        struct next
        {
            typedef mpl_iterator<
                typename mpl::next<typename Iterator::iterator_type>::type> 
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator)
            {
                return type();
            }
        };

        template <typename Iterator>
        struct prior
        {
            typedef mpl_iterator<
                typename mpl::prior<typename Iterator::iterator_type>::type> 
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator)
            {
                return type();
            }
        };

        template <typename Iterator, typename N>
        struct advance
        {
            typedef mpl_iterator<
                typename mpl::advance<typename Iterator::iterator_type, N>::type>
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& /*i*/)
            {
                return type();
            }
        };

        template <typename I1, typename I2>
        struct distance : 
            mpl::distance<
                typename I1::iterator_type
              , typename I2::iterator_type>
        {
            typedef typename 
                mpl::distance<
                    typename I1::iterator_type
                  , typename I2::iterator_type
                >::type
            type;
            
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(I1 const&, I2 const&)
            {
                return type();
            }
        };
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Iterator>
    struct iterator_traits< ::boost::fusion::mpl_iterator<Iterator> >
    { };
}
#endif

#endif



/* mpl_iterator.hpp
Nocee5WBY+/zzzrT8q7ghA5t6ri90zJCzxXXfRZ6rqgKpHVAp2hd8WBQWheE4A3fyNDt+s6nodu1NpDWuz7tDK1/eoPS+sWBjmndd1Xodg37NHS71gfSunlTZ2iVg9M6OAStl14Vul0nbwrdrg2BtPbtFK3PlQWlde4vHdPqvTJ0u76xMXS7NgbSesfGztDasjQordt/7pjW768I3a4nq0O3qxpI68bqztCaGZzWs0LQetEVodt1YnXodm0JpLV3p2hdviQore6fOqa1ND10u75aFbpd2wJpvbWqM7T+WhqU1i37O6b1m8tDt+uxDaHb1RIWQOv6DZ2hNSM4rWeGoPWCy0O3a/aG0O0aE0hrj07R+nhJUFrn/NgxrYvTQrfri+tDt6s1kNb89Z2hVfUEpfWzfR3T+lVq6Hb965PQ7ZoYSOu6TzpD6xXBaT0jBK1DTbQGIfXqTzpsVqDUHkiptVOUPvpAUErvbERKaZ39/Mh/uM6OCO43Vr86tsO18VHQdvA9AvtId7jyNSvn/qt6WtTb809p5dxIyINmQwmeRnqQMqcHRqZ3DY9qoAcp7nhAwGSUrcG7O984q+yzHd/Uw6LuY/NavvfuHNk3L0Ogo2i2Ax+BBsYItnNZuxTgCmd/HWup8cDNQ1c0TtxkAozyfGq/Ifhd0pzLQvpTefSjgHUzosnBBdr4DPWtb2Iteo/N/Kgzi+LGRR2t8nvs
*/