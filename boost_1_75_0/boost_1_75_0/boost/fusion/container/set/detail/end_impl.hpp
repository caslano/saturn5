/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_END_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_END_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct end_impl;

    template <>
    struct end_impl<set_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    set_iterator_tag
                  , typename Seq::category
                  , Seq
                  , Seq::size::value
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

/* end_impl.hpp
W0geAXlsYlQsVcsIoVvxXgX1/LW8S/L0Xumtt0Dvi6j3shKt5ws+2x3RM7J0zzt4V6Oe0Q7l8ahvezD8bZqk3qLEzyxBtTT6dcvcthxxQqzqESXEy8kcvZY1s6bwmYqcCPByM09EXg5YlUhebk0V8Ek/e8kX9po69tXl8mJRmh9h5SYzl28ODlJ5Wh3Z/1JxLBVpVPSgogsViVTEUfFXLRZ7qdhNhUnFV1TsoGLTg/SmdVyufJBsf/lyEZcLoFwG3vHm7/fD5xwlRgw2ULVUX0uPTebm4+lyHBU3P4j6rZxgF8FJ3RPTVTAW7+cFPTmDO5enBofGDfbHlacEh3oG+z3lnuDQpMH+pLKu/tCqvKpGj79qf9y4j9G7Y/WgxtVaDlqdRZyLa+Qc+JViEUnM3BLydb0OmDxpv9d7DKkZSoDVudGJHN7gUrJD3gKsna9qSxJTQ9OLSc1QEvKtvZbVDCXms8NciFSWTdX+62WgbrzvD36Rm/VGLXJy94HMsf4dIozP8FZ/i8EcykAmvphUEMsBQoAMJfudbaTVennbbkzAfS9iJKCwrtIqRoqAnBArVguMFfVlb0O/pbqMqaGBaYYYdJrYCw2ypCaL859dL/OfXQy1dGhCJrB63689E2SI4O7KBKmXbAWEphfcNCpgLbLwNue8c/qH/BcI4C9AhPQQuncchPps+6vfvk6++joZM9XuyXfmkiRbjOJK
*/