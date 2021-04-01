/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_BEGIN_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_BEGIN_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct begin_impl;

    template <>
    struct begin_impl<po_array_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    po_array_iterator_tag
                  , random_access_traversal_tag
                  , Seq
                  , 0
                >
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return type(seq,0);
            }
        };
    };
}}}

#endif

/* begin_impl.hpp
eF/Xs8IBmbJzBeYI5H7Y1GDa+2Bvhjjx1wy/1Ofi/t1FaiFqYa9iqrLSHpVRSziFhlGFWIKB96TGrmgQyHdsJMQpxSRorEiAkJi2plGuCFQe3coDzsSHqoLSvu45ShCDe/ru7r72kx5e28UsxqUJTFQtIztGNTkF141q3McUuRWmKL3vXlQ+mQZORMMp+fOXXghCKDKjXY0zvG1Vczu8+di0XBsB3rZuahy9FkjmQ3A1NmCL7O+doL68i+w6l+aM7ibKE63YQTYuaShtNzdTBAW0cV9QWn9UgdIsczrVrdd2iuoeqP0E6vg+bmQDdz+BXc7TiHnX0hZX4MXNn4s3rhnSRQ7PRZwlF67ubp/jJWzvw8aNmcrkzUrqeDzbwv02y+l1LOJr2+iSI0rb7aDA43g7L6EShwaTVxfjDgNi/XZHrqpYX4kLz9Fpl/JaDMdBQtwRVn42gPGgCYNR70RGD3Tc5Gzb1P7s0Ztw+vYW5xty8JNYfi2axRJW3kyRAvS2wNVmS8IfyPU+JiP8VI7Edb+ZPZPm6lCfHAV2Ic51nMKwqwuvSp35lEqtJA==
*/