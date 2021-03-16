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
A997k73p72/AVZztzkf+NhaYxmKcDd8lwHzPA99VwKzxwLcVmN+W4avE8Towhz3w9Z+C+mBK+fE9F5iWYpwNXwqYy8vwkbxrgHnAA9+zwLzkoX8fTvE2vv3OgT2fU75/Ded44/MBFy7Dx/HPI18OuFUe+NZ65NsA3KNl+CpxvOKR7x3gPvTQv5MbvPFVATemoTzfBR75/MBFy/ARrtsj30rgVnvge8Aj3zbgdniQ902PfO8C97EHvsFTvfHVADc=
*/