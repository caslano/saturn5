/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_ITERATOR_05062005_1218)
#define FUSION_CONVERT_ITERATOR_05062005_1218

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/is_iterator.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    template <typename Iterator>
    struct mpl_iterator; // forward declaration

    //  Test T. If it is a fusion iterator, return a reference to it.
    //  else, assume it is an mpl iterator.

    template <typename T>
    struct convert_iterator
    {
        typedef typename
            mpl::if_<
                is_fusion_iterator<T>
              , T
              , mpl_iterator<T>
            >::type
        type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static T const&
        call(T const& x, mpl::true_)
        {
            return x;
        }

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static mpl_iterator<T>
        call(T const& /*x*/, mpl::false_)
        {
            return mpl_iterator<T>();
        }

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename
            mpl::if_<
                is_fusion_iterator<T>
              , T const&
              , mpl_iterator<T>
            >::type
        call(T const& x)
        {
            return call(x, is_fusion_iterator<T>());
        }
    };
}}

#endif

/* convert_iterator.hpp
dxn7+bQgIDpXvSrZmVfD/U+h9FzYBEbC+SItBNf1+yYygyRf6yhfaPPmsYSrKG0PQWm1EFoXrx5QQEReVi81ZHKQFgk+lByI0QeoiNT26a3T4SmngR6mA/FmIYSNsavNKFJSp2uGux5rFfZ8Ygd9Z9KtiHm7Qsap5rb+lETCKxV3WcsFuoDiG387xr7lE/Wv6IE/hhEY7K4a7/t8BbxFl94ytKtFVDnTFbiU8sObcIYBGUSuqsGq33i6UAf5B+SSKiDMXspcZinwDo7udWWMMRiWLuA7X0EZmY+FmWttleYty79LRnkrPIqpiaFwURdhyQrsVTKNQWiKUgiJb57+48LKCRNfPn5YMSpzzp65rCe2AfKjy+ATfJI71ObZ8Zds2FG55oecuiNFRhiwYgJ0OH+V0lnKqBlNKvW4zRUo4r0WMy+2dpRpTHfvsG3N7ttKNDP/1ZxgoK8o8h3R2YNdavbfXIJtDL0mkHP/M8R1IjdcICjNP6W212keTXVF7PakoZOUeBgKHe5GOhThO1kwXccxFiDg3KALyldCv6Od1P91nSZhtFoIQlAuiA==
*/