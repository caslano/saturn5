/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_SEQUENCE_IMPL_27122005_1648)
#define BOOST_FUSION_IS_SEQUENCE_IMPL_27122005_1648

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion {

    struct boost_array_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<boost_array_tag>
        {
            template<typename Sequence>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif

/* is_sequence_impl.hpp
+n9ljJxb2PpILW4fQ9JBV7V5Otppb0o8QQLMpaaZpNKEIQq/67tYttb2Gel0gTEUy4z3574jt/qAu6qAl+1M+nwHqnsSOW3b98ocxi9rNKuCERRfIY2+jfMNKny2s3yR3YeqmgwS+XyK6FMyiK2qwAjzXA5iy/TYrX+P7YltEYK02i946JIbw2yTsml7KTcDSBgnV7rOCkledGVBw4UOtTz9xBzpkPAmxT3Z04waH+7u2Jj32G57ZTyoAHvr+itOZDn2G3tHqMzFmsUK0U/WCRb5t7KEntVFmO7NPlDIiyEgaEtGjLH64sJfu++HrsjwSI/w7Bg/nluCUxHfy2O2XAu7+3GW0S5jeQPjo/liwd7oP2U6Gghy1ODsLdtcZLZYmXuw2Wfa7fX6RKZMrMnmq+UcQrpNE/RjOvjIS6IGz3D5GJrCoYw5UADeoB9b1m/3QDtlbfshQ9GwPeeSxINCrGdybsiClz5k1fnUJPcOvBmaY0Z7GfP9GOV9de5a+4mOvFXdywdDjqZ0dTCCRtXjkFhuGVEvyzkLKR2ot4fT+jbp0FK31Z7ZyxNzsQ==
*/