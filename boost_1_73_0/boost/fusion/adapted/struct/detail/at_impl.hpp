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
g46ZNdgeG3ZuwMRCmmPpgJozC8StcuY8xkeKw2OX1sepG3bG/RtiNtluTPxPRx7G9DGrnN4TZouZ18RMNTsLn7xnNYnMX6YdeVDMtbYHEA8rkLfo2yTaiWI+KawdkTOV3cOnbpYM3+OOu6gIn5TLp0Td1DZxF97uqJ3B4vYf+AYvke82O5o+V4HoR5k7E3dLXRvqe3+AmjqI30Zt6qGY8zh3t/S+l8k/po6S+iU83cU8DKtT
*/