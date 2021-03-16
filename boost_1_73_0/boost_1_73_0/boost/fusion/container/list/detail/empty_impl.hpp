/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEQUENCE_EMPTY_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_SEQUENCE_EMPTY_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/fusion/container/list/nil.hpp>

namespace boost { namespace fusion
{
    struct cons_tag;

    struct nil_;

    template <typename Car, typename Cdr>
    struct cons;

    namespace extension
    {
        template <typename Tag>
        struct empty_impl;

        template <>
        struct empty_impl<cons_tag>
        {
            template <typename Sequence>
            struct apply
                : boost::is_convertible<Sequence, nil_>
            {};
        };
    }
}}

#endif

/* empty_impl.hpp
5j2FFyeoVLPVswPeQZYKJX4u77WjuFG3sRyCpEbKdWst363OUEBThqlhXTDhePG0oxjhzyksYY5BdXX+QNIxxnNDCEE8t1oB2ZKH7bE2eRDDyU4uvyeS0YCm1BpOlUbXOuzJahxom9NK5lsAUhycMx/ObkcuWUnRpG0GJT8c9jRa1Y45nJK0tym0shMqQ6MdOxT1nTNyeUjNmaAgiCu+G3dg2Qj4CgfHrMKS21Boe+Q7tE1wx+vkxR2zmu1KLfA=
*/