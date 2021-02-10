/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SINGLE_VIEW_VALUE_OF_IMPL_05052005_0324)
#define BOOST_FUSION_SINGLE_VIEW_VALUE_OF_IMPL_05052005_0324

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal_to.hpp>

namespace boost { namespace fusion
{
    struct single_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<single_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                BOOST_MPL_ASSERT((mpl::equal_to<typename Iterator::position, mpl::int_<0> >));
                typedef typename Iterator::value_type type;
            };
        };
    }
}}

#endif



/* value_of_impl.hpp
w8NtDT2ARZgHqDJWWrN7uiR5VEoYxUtB5ZuVisOpiRV6sTcUfzFRBvyFhCEv11kOvunvXQFtD5JiDC+e7x9fDL3ZVND1QQ67f62TUQmR9qDHo4pCHSYKZ4Ter3nHjqoEzz2eSpJNjWPRVORFqb7Wl9lQuNT1IcWSo2reHQ6sgblSSmhxdGZceHxeyxR4z4pMOUV+irSt04mFtas4KzIFLNLKM17NUTAIT0/Co7OLFUOnNovREFk6RSzX+GUiirChdHTnqiolevowNKGz3BT8PVVbtw2pre9TqoyH5UAldoewfj2cOgDYl3WxVH48zh+8q9MkvLsLhlUgBHuwX9eCVkNhnGdAgtgM2fMho7s3Os6tIYyzFJAgeMDGRhGsxHUeVcZ2MKrQHHNRJvx9Z0uOp5LYsAplmwyRnG8taORTWaj26GymLF6r66okXpe6H6d5gI4ivdqNdZNZEoEWUKPN5aD302e/Hzj/9av6znWBKfzmaafPiJ+YSWGqFr7SmnLMJOlm1DtEsaWpYmvHLnoBbLYWwGYJdLYa4Nny4ONDqDFHhtlxoF44TqslENni4VtgwnjBOIvzOcAhBkN4jy/SNqTR0/8b4Y1mU5fnr4YLUYI2/e+NDf4+7z9m/Wa1/ZQXUAo6BwgAt5j3Baeg
*/