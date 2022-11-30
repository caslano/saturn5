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
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
*/