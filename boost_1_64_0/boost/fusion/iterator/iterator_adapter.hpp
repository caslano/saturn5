/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ITERATOR_ADAPTER_08112011_0942)
#define FUSION_ITERATOR_ADAPTER_08112011_0942

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/distance.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/iterator_facade.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/prior.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion
{
    template <typename Derived_, typename Iterator_,
        typename Category = typename traits::category_of<Iterator_>::type>
    struct iterator_adapter
        : iterator_facade<Derived_, Category>
    {
        typedef typename
            remove_const<Iterator_>::type
        iterator_base_type;
        iterator_base_type iterator_base;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        iterator_adapter(iterator_base_type const& iterator_base_)
            : iterator_base(iterator_base_) {}

        // default implementation
        template <typename I1, typename I2>
        struct equal_to
            : result_of::equal_to<
                typename I1::iterator_base_type
              , typename I2::iterator_base_type
            >
        {};

        // default implementation
        template <typename Iterator, typename N>
        struct advance
        {
            typedef typename Derived_::template make<
                typename result_of::advance<
                    typename Iterator::iterator_base_type, N
                >::type>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& it)
            {
                return type(fusion::advance<N>(it.iterator_base));
            }
        };

        // default implementation
        template <typename First, typename Last>
        struct distance
            : result_of::distance<
                typename First::iterator_base_type
              , typename Last::iterator_base_type
            >
        {};

        // default implementation
        template <typename Iterator>
        struct value_of
            : result_of::value_of<
                typename Iterator::iterator_base_type
            >
        {};

        // default implementation
        template <typename Iterator>
        struct deref
        {
            typedef typename
                result_of::deref<
                    typename Iterator::iterator_base_type
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& it)
            {
                return fusion::deref(it.iterator_base);
            }
        };

        // default implementation
        template <typename Iterator>
        struct next
        {
            typedef typename Derived_::template make<
                typename result_of::next<
                    typename Iterator::iterator_base_type
                >::type>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& i)
            {
                return type(fusion::next(i.iterator_base));
            }
        };

        // default implementation
        template <typename Iterator>
        struct prior
        {
            typedef typename Derived_::template make<
                typename result_of::prior<
                    typename Iterator::iterator_base_type
                >::type>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& i)
            {
                return type(fusion::prior(i.iterator_base));
            }
        };
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Derived, typename Iterator, typename Category>
    struct iterator_traits< ::boost::fusion::iterator_adapter<Derived, Iterator, Category> >
    { };
}
#endif

#endif

/* iterator_adapter.hpp
C1X/8diQxBe9n0OOBlMWvqQ+RfrEvuz/+yBHk3Dr/MEKB1QZM/eV8wfb5GkR+qrv9zmgwoD41/TNES1CbXsdsU+VEXNfNxYK9Ij/m6S7jW+rqgMAfOYyLJC5bOu2bOu2bItasWiUghWnVh04YUDRAVOmVi06tWjQAlWqRq1atEKUAkUrBCgQtWLAqlWKRqhaNGqECEWKRg1StGqUilXry1P98PzSJPfe8/Y/5557k5zeK38MMEW4T9uSZowq8YrjMsg04WeOSx9FFmi5XywwwgzxB+zDIFMs0PZl6+vMyAsLtD4oL+Sp0+Y7GT3UaX3I34xTJzWrnCyQelj+aPqFNMhSZv8W96JdB01SZ98K91GrtmWCJdrdX4tFVrlH7ncK/h7fFvH/ZFeFur9Tv1ZXTBB+Iz9kmGRp2fek8X1lJDHpuEzR+Q3t8nXpcfA2dXOrclOhY0xdM/5FaXNoVL0Sucnx6aZyo7Qp3iAmcvJ+rToZUr4rPL9MG2w4IiQ+aV/66PmEcy77L5UX+gbE1SXq5iKxdLHXfE7Z5bH0I33F48yF2sN7B4gfsSrse7d0mWSOvT3Kwvzb/d1tf+rsO1+5mKftHcpElbZ3qnPm2JOWF2q0XaC+KBF5lzTe6v1Dyvdq750jDUbJ3+Ozg7Ol/yrHPE28R80dyDBNbPUR4SADlIk/5YjQSZYSDWt8d4E+JpinJWYbRigTX3tE2E8fBRZoXue4DLJEer19aW30N5PM06q+uygQ3SgteihQI7nJGMIQ0yzRFncMxqmR2Gx8IUuRRVq32I8cFRq3yg9Zpok2HRHa6WGcBVq32YcRZmna7p49g5SJ7jgi7KGPceokE/ahQHSnvHGYEaZJ7VI+xqjRuFsZ6WeKkJQPBplmibanep8iC7Q8TT7JUyX+dOVlmGkizY5BN3lqHHiGOqNI9Bj1xShlGp6prBxmiDJLtLZoV4YoskjyWPVGP0XmST7L8RlgkgUSz/YaGeokU/ZjkHHmiD9HnNBDngoNz1VeehhhhthxtmOAKaKtnpNhjFkajtcWHKZE6gT1zBDTLNLyPPVEliILJNtsxxAVIs8/IuwlQ5E6qRNtwygVGl4gj4xQ5tAe+zNN6oXywDBlIi+SL3oYY5bGF0uDPsao0diuTPQxTo2ml3iNfsaZJ/5S8UKGAnOkXub4TDJHaq88MUqFppPknzFmSZ4sNihQpfnltmeUWWL7pEs/EyyReoU0GGWO1CmeM8ocqVM9Z5RZkvulSZZpYqeJBzJMEDldOeghT52WM+SDLBUaO9QTvUwQzhSTHCZHlegrxTp9FJgn8SpxyxBlIgcch14KzJM6Sx0wSpXms+WXHLMkzpEXhqkQPyj/ZJhkkdZXS4cRpom8xmukyVMjfq796KfIIq2HpM0oZaKvFU/0kGOW2Ou0AX1MsEjr6+3HCDX2dcoP48zR9AZ9jCGmCW+0D2kmWaD5TcpJgRpNXcpJliLR85wP6KfAEm1vVneMMk/iLfLBMFWih6XLENPE3uqYDFAh8jbHpJ8ykbfrE6QZo0JTtzZikCJLtJ6vTsgxT/M7PCdHnaZ3igWGqNGUVh9Vn4d7nKBG8wXqn95n+D2zxyqN75I/sswQfbe0OMwQ0yzQ3KN9GWKGxgvVOf1MES6yHz3kWaD5Ys8ZY5FUrzZknAVa3qPuGGWOxHulwQgzNF4iv/RTYpH2PnXFOHO0vE/+GaVC/P3qjgHKxD8gn2Sp0JjxPoNUaPqgNBimROOHxBpDTBP9sPahnwki/Z4zwBTRj3hOPxOEj4oR+ikS/Zj36WeSyIAyMMAE4VLPGWeR5MfFJFkqLNH+CfXEGDPEB5WBDAskPmkfspQIl3mfXoo=
*/