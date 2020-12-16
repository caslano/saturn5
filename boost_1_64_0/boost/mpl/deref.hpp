
#ifndef BOOST_MPL_DEREF_HPP_INCLUDED
#define BOOST_MPL_DEREF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/msvc_type.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/eti.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Iterator)
    >
struct deref
{
#if !defined(BOOST_MPL_CFG_MSVC_70_ETI_BUG)
    typedef typename Iterator::type type;
#else
    typedef typename aux::msvc_type<Iterator>::type type;
#endif
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,deref,(Iterator))
};

BOOST_MPL_AUX_NA_SPEC(1, deref)

}}

#endif // BOOST_MPL_DEREF_HPP_INCLUDED

/* deref.hpp
ssAtIQU2a1mgWWSBfcoBdAFvbZOJiMjJ84IrHsVkQIz87nk/6GK0DliXRT8gvxSLIyVr5cREbOS4LXWayeXjw9p3dcPNem5JgSAMRCO93H4Lm2l6tlNkeGNEYVNN/K+7ReEui9TEb8bqGYoHimxDxql6SJf+WLukshA5E7Nvr5gKvPyQhc4me//CkzER6NQrdPa50Vm6UKFDen87TfpEGLFJOTnJecrBCiY8c6ZdTpbHJUMV9S/Ut3+ueadVmCmM+Ev8xBYbelDsyO5CGfYD1zom9qnaUdj4NtfaKxfaK1L0IhiLzedgfxvJRkbUgGO11HfRU7oBz7FZYRzeWXa9mPsPoWximva6B3WV6Vr5IIi0nUwvMURxoRUV1bwDjeWL9I7ENmTQjirbXsG+Cauf6GK8Rn93bepifEB/vZmeCf7Lk12MvvSe4OkgjzfR167DZ/O03/W/+djnf2hgF06WUZKQRAGnb4gxZ/1yDHsBZ6PdApbGJ6ZiJKfS3m7h5cgIZgdTRdkGb/zi5pCcE4ZASOp2ZO+NJ37/g73/zUSn79e7EqXMWgI6dNZgkib9nGp8K5wHRLFTv170P8ph3AWCohraVxeeIIq2/cdDbv6/5MsxyKXRgILQLeMFrTfla3r9cWx2z1xePW0HIKJz/ql+kMtvsvXfJW799zXx9d+4Lw6axabCIBImrENTxLLNJQXQYEG9whLzdE9aPs4xXXgd6iAXxJGmWJy53K8dRjbM9diq32atlWlJx4U0kceitK8jPFrIshd2hkf0sIbWw9KLkudMCJJaKxojQCbnm89WaN1aX1XDPmt1DdWFk+q+G8ciNAAFWMDmrhAjdUPc2EZDDJ/naohz0RDTZCcUp8KMYrkkrx7HxdKpAtDtRSZY7aHXv82y/o2sjqdT+sun6sBN0zdP0t3VKX+YHgfD/ud+vR9jK0o2JiriXH+Hizjzr26DOBcmyor+Ql7dR4kW6HRylbbELdhXQXKnUy5Kvv/jUJHvuWOb7Y7VwrumyxZFl/bEH1fo10T1tVuAsRzD87A9oGmTa7Wt/yc9xFKvJYNMSMmYmFo8S5S/WHx+ZVsa/STupDUj4tSF81JQyTryt4MtPyCYksvuQs19s5zKiiVBkQc08qmRoF6zpKZPIa+4Iux8rdAPPWxllVZmZOg1jj/OcJm8QpehYxm2aBLpKxpb0d4o7fR+LGyaG75BNWkYKkMVC9S7NqDtjHQ+i9iEbYymJX72LlWwj9JyHvtoYZ6nqkgWoJBO0InJeeanZXrgnq6UZdetQRWIMK7yKDV1PQ02aJHqtRapHgNYtnykBbpS3aSpwhNSGmYqA+u8lMSCJtxQmcKLbspwCZQ5YryikaKYWlzTeF1v4dVX4fXaauAFMnEyFF1MixQjSgTKX2iaD+T9gtb2ba9Vgb03khm9Zu00RNF0c6KQtV6zxnKwhq9QCUq8O0vQBMrP3Gsr4DvJlhHpvZQOfm9V9t7PC0P5Fz+Wv+px69zz+TvFLpb1yCzneg7ManPsSq6spInNf4IrbrMWc4EXsJirf14t5gxL2gpYit3kXPN0kbFz9WEOPTwTYeSZUvEyihznjbPoW7XGWsv09OrNxyMu+mbZKUxPNJdtY2V2lp1mi+cYV1nvrbbSlLa5yjr3Q6yyhLVilWU2FGCVpZSXxZNtx8Q2a3Lsquk2XLxMszK9aWgAMVLVcn6lMXXKt/Gr08PXYLfNbxCkhIe3hY3G1K27lRa1mLFGFKH3ybI8zFrAOkEs7FFy8cGrkVVkIR9CKGBBINe8c4GeCs0iEpvZueWEZOLf5XckixCZo9gQhaGSk2RQq0Yv6sJ515Npm+Qdp7Nvvitqhbbmyuc=
*/