/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_LIST_FORWARD_10262014_0528
#define FUSION_LIST_FORWARD_10262014_0528

#include <boost/fusion/support/config.hpp>
#include <boost/config.hpp>

#if  defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) \
  || (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
# if defined(BOOST_FUSION_HAS_VARIADIC_LIST)
#   undef BOOST_FUSION_HAS_VARIADIC_LIST
# endif
#else
# if !defined(BOOST_FUSION_HAS_VARIADIC_LIST)
#   define BOOST_FUSION_HAS_VARIADIC_LIST
# endif
#endif

///////////////////////////////////////////////////////////////////////////////
// With no variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_LIST)
# include <boost/fusion/container/list/detail/cpp03/list_fwd.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace fusion
{
    struct void_;

    template <typename ...T>
    struct list;
}}

#endif
#endif

/* list_fwd.hpp
nr9yLud/b+Gd06VsPgT59jJv65YwnzNQiCm6D+J5RjI9xXIxfkXHyhbCOlTVcJ6/cxq/78vsTJL10mTelxLhfc9bPTkfTvTkeSL68X51F+Y3NML+wMHCvtYWgt1LFeasVgn7V4vY+hQeWwtHXyc2ZPTLvM4E8R1MtuaI3wdcu5KuqVUyXUuxmp7nc+YrhLmpmjmchmAmC8l6KZ+31Z35P1gvtu24Rub5K4fwer4U9OiEsL/ltJCuekIYR57kZWWGbeT/FPD8pbGchpI4Tiefm0L+fBqnufckLpcSYV60rfAOBY8ptNaYoXxPozyb13NWiP0Hl9ntY+zyFY0rtw7mMl08mPO5BXvvL8daIowppcJ+ib2Cn3Ypire1KprXs+ZNnr+ot6DXgo5fEsbfzGSe7pTM80QkK7LDfvLK/1Ib3nsMz+MlpLumcJ6L7xqk/n2b9WVvplIn9qM++Ir6Myfs92hlfC7s81yr+OdUZ/OHwLEdwqEJ0UY4Y+uyZJ6mhqMNQk29VdlJW71RA/Ihc4K3TffhUDgFIQ6OkSmraoef4CPTjPg0LJk8kPC5ZXDqx4fouWZ4saaZStMsFk6jyW9f5SO3N8p+9MiIPVJqSaLZe0diTFlmC8nUQ5WVxs+6uyS3l1JPSF4noIe5khcctIW0KmbHVMmYWrJFTWqw6WqHIKLyirMehWP7UjVGs/d+FTwzB6qiDlq+CvNTobuS
*/