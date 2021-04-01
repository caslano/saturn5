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
JL8y6JEsiGIMr10dkmDrXFD/ymiRxAnN/LohcP6q0WL8rG9/nVjL/aXx/3zi/TKKJkiHb+cV3jOT+ZCesW+Dgc1841bqy9zoSYBubaFYbcMfbboHDaGwdsjNwD4bpejiGkaL9Q/4+IY5klMP2zBfkI5N04qpGP1jRt3AaAFEceh15kZSr80MFnzhnjsqOzwwdmy/Bi9QzlpHLWvw7zJBWbJEsTZwiHDTf77JCo79uDy296jKvJEKBTBIiN49PmwbMtri/9pgGAzJtOLjz59wfgvWAt+iWhBszbFrhXzcZjgvglPV43XdznRjyk0PK1MB1B5b785C1zBgXjHtNpp3MgM0NiwETbuJxZj7A1pMqjO0LnsHoqF8nVgXlWDII3sf5XFlva14hCievECmIhen6TVR5csc63LBTNc3YVIzcYejjy26hUJ/RRHWwR2/qHM5N0Dr6+Fo5FmOxEUt0b/2LMRmfkPbfFm8oQiSrAspB4DimEUi+v0yZMImIskUL9HBH+dnQQThFubKZVmd+S/tClXhQjJErRqCSSwJCsk9118kKpYVmxplQBiZYQ==
*/