/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

// No include guard - this file is included multiple times intentionally.

#include <boost/preprocessor/cat.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>

#if !defined(BOOST_FUSION_CLASS_TPL_NAME)
#   error "BOOST_FUSION_CLASS_TPL_NAME undefined"
#endif

#define BOOST_FUSION_FUNC_NAME BOOST_PP_CAT(make_,BOOST_FUSION_CLASS_TPL_NAME)

namespace boost { namespace fusion
{

    namespace result_of
    {
        template <typename F>
        struct BOOST_FUSION_FUNC_NAME
        {
            typedef fusion::BOOST_FUSION_CLASS_TPL_NAME< 
                typename fusion::detail::as_fusion_element<F>::type > type;
        };
    }

    template <typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::BOOST_FUSION_FUNC_NAME<F>::type
    BOOST_FUSION_FUNC_NAME(F const & f)
    {
        return typename result_of::BOOST_FUSION_FUNC_NAME<F>::type(f);
    }

}}

#undef BOOST_FUSION_CLASS_TPL_NAME
#undef BOOST_FUSION_FUNC_NAME


/* gen_make_adapter.hpp
DCsBBfH4tt7u8tFs5H9+rgH/KsnHAiyom3SDZDhDby1lywMMjxPjMT+x1V1RKyC4hBc2VsGesEZrI6/srgy9kAtkMPtlUSbA5Yi/e9mGfcevrDnXpSc6J7YfVQjEfUNnKfio92IuEVRqwATBTmLaPSGHO/UFS4SaJEvu/f9Hu6Ah4A21ql4c0JiQ+KLAzEpGpGl1RsXCc91+wU/LXdEWyk/dl0oyEf8WVhtffhqj7KduP12yZtKLf92o3Qhb3gUJNnSvkFIuZEHF7o9/ydLbsVjNksK+GlqjRhxZ9SylC99addTd/wvlrIEOFvKGqrNEM+LNOJbHW+96bQsAFEFCt/S/JESEUB79kNHyTKeNQ0pZHsifODN/HVUSiHe8xlhUtnXMLdzn9YE/iGcenbTcWswis7SLC8P4eOcbjb12AgK29KspMhkjKCiTUjSio1LAbKnvyQy7VHpX65C44K5AFryDd41rkFf5qTtq5usLAglX9aOPFURuzK/C0DZryCjCcLtI7MUydh+OmvbJBJt2jbTwNXeFke8GXvH7kflQBhlyyICP0lj/YkLM5YJxj0vq6SS+S7jj4jJHkiKR9MJm0NdfRpkIcxtduo3y1i2Sgle9QJY77Jy37pstOyb3FfnNUcNQvkH3QU2nKrex
*/