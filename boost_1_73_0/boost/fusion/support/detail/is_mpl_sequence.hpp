/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DETAIL_IS_MPL_SEQUENCE_29122006_1105)
#define FUSION_DETAIL_IS_MPL_SEQUENCE_29122006_1105

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/is_native_fusion_sequence.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename T>
    struct is_mpl_sequence
        : mpl::and_<
            mpl::not_<is_native_fusion_sequence<T> >
          , mpl::is_sequence<T> >
    {};
}}}

#endif

/* is_mpl_sequence.hpp
8qRNny0yW26jm23fd4NNTrq+6b+zNZK+9Ta7yLGmULaWk/XJhu3lTpHbdHRixlupS2S2PTox7V/IkZUhAl0Sa25J3/44TnRxz+Oxycp0YrZNwku6PtMfT7cfZQpHDOuy6zWZlzwBTUamJCMGJC0dJM2656CHAXc6PSetezqLsHHGyKKJdZGP+xinsq9a9ocYG60y/lRGE6hj39Hbo1RbdU1b5WpZ32mCyr4Kq0y/rTxtJNFX
*/