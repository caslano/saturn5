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
KR0zUBnT6J9Ho7xVNVUyKmSuR/meiqAym2+qWhGaDduBbAwYCa1GH6y9DxtZ8NLeiSI6bNp1zXXlP8KihKIYSQUa67oPR64cdVcCQtKz5VtLaAg9N/ampdA227aSmyeGRGsfqGyVoHREC9kVkoj3oRUFKmfviNhn6Vl2lL/QskfsBUhBqGAQJhAlA1gzzbUPV1F6ES9TuAoXi3CWriA+h3C26uNdRrMz0ganrArwrlGoCYUCvmlqjsWT5N910r0gvYDxcjGN52mWErLkfLJIJ19SOIbB0Qn80Qqr7R8HMKj52jYfToLjk+CQDuyvDJneZRqNbTN9SFGagiYXMAs/TbxnI1+/JWn+3aKmUSDC74zlyPZDMaFLIqCkys/TuQuTrGbxPIkS7wcu8rotEE5t3k6H1QfPpcglnX8LZ2jfwJuKFFKTUJ6D4kMtxY3DcPCLS3c2ScaLaJ5G8cwL7dSwDZImSIlOxUdkW9faqYP4UEztenFDmIyjyGob9/gfCtK+x4U2yIq9sgosWVtT4Vy4EL1hAOfkuuXi+B3oHXmQFknYhSTlC2k6FBV62hSydYD6ADZt0KmyawLkJME1EjI3wNsKxUMWxfuaoWCGeWs0W6TX+4RbUiHpuSRLFAZuOW611XSOyjBaQnlFrOTG
*/