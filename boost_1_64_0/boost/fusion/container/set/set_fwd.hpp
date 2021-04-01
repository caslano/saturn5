/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_SET_FORWARD_11062014_1720
#define FUSION_SET_FORWARD_11062014_1720

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR) \
  || (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
# if defined(BOOST_FUSION_HAS_VARIADIC_SET)
#   undef BOOST_FUSION_HAS_VARIADIC_SET
# endif
#else
# if !defined(BOOST_FUSION_HAS_VARIADIC_SET)
#   define BOOST_FUSION_HAS_VARIADIC_SET
# endif
#endif

///////////////////////////////////////////////////////////////////////////////
// With no variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_SET)
# include <boost/fusion/container/set/detail/cpp03/set_fwd.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace fusion
{
    struct set_tag;
    struct set_iterator_tag;

    template <typename ...T>
    struct set;
}}

#endif
#endif


/* set_fwd.hpp
M65uDg835urYuIl3Xb81n9TvtlETnTCHEcaUyijLZqY3EeLz7NnSOubszeO1v8L16o2IL7x32yJ6hydxm3w0zYSQQ61qhw7S+Lfh8ZLeg+2O981BO5awNAbHHP+oGp0UgRT2JXK2JdqJD0bKm2wrfLDWvLe5UkOgJzzWJXBS7SzFQDr1KQ9ypHAcEu46lWKCMFJnLpSeDSgzyDYVq6w2M3n9HqFtdChQ8kJwF4emJpu/jkBzp+DO6Y6lyWvGqtdNqd6Z8KeO+vH2bULrHCriDr54tyZKaSKyqHeR19UAFxviJTrHQb9mjKnxbpx3/paEOefhcLp6VtOeZxRKRj+IyVEKbiLsvD0hgF7VsQ1bkVxQGfrXk22wvMVEtp54xSCgBwj9PVbQZzC6wZr822BZ1E5UjJbrJCNwfXn176g81QUcU86gX+uD8/JHjOgGYUm4S6swkJTk1hqT/Q2jxrDj59tghieiino2N5Qx/BF6lcRSepgRCIxSGH+laNMhczInFTFQUpDlg53ZdCAtxLAQRtOTEZy3PCCDb6Wg35Cfvy3CnwaeoPZcc7l9Ww==
*/