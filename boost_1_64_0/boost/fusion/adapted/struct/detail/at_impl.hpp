/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_AT_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_AT_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct at_impl;

    template <>
    struct at_impl<struct_tag>
    {
        template <typename Seq, typename N>
        struct apply
          : access::struct_member<
                typename remove_const<Seq>::type
              , N::value
            >::template apply<Seq>
        {};
    };

    template <>
    struct at_impl<assoc_struct_tag>
      : at_impl<struct_tag>
    {};
}}}

#endif

/* at_impl.hpp
0ThcfL1eQTayKc/6Flfy+9BbSlTwMnpWfQUzZ6xstqc4PmFGhYymbIhxtZ50KdbhlNecFnokXNGfQMbWFEvWJrLwewnMJcO9tL3OtPCPDwoYHjACDnbs2NjDI8goM3hERM4rDGMVfHuMe0GmyEzI+UuXXtCj7nnAQmgXy/wGPXJ3cG7Y7k+MXbksuKtATcOx33KuFdv9Cw8Go34DedrsVvHmSRtGzjSbbtqtALZWUOJ4pp4BEK+DmIPbiggDfE3phkShe1NK/6Qk6H6QHKNkWPXH4JN91Yh4ybDcxMEInmhCCQEuWf4Bc/aT11390KVKqp0o8w9zSSrWFGQYwh57fQ6YIspf5dPhYYbjeLBnuX3CvbN/wDtFeu78yz9QXmO9N4MT6tc8R+BmGomVFeJloQzOhXLYVbOVCBCPBmrsaEcLBKUkOL192msZaK6l2KtC5nXYLBLmM2V+yXMAFWosQPVpe0AmRIvRJeQ6ZfGp4JEFKHSoV+cQ6P9yXLFfoj+3QzIooK0dvANwyWsUduqZ2cNL4h9vQJ5D1qj2l187DjZGon4+QjxZDKLqkA==
*/