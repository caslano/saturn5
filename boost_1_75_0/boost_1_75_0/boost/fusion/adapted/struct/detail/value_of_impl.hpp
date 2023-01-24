/*=============================================================================
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_VALUE_OF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_VALUE_OF_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_impl;

    template <>
    struct value_of_impl<struct_iterator_tag>
    {
        template <typename It>
        struct apply
          : access::struct_member<
                typename remove_const<typename It::seq_type>::type
              , It::index::value
            >
        {};
    };
}}}

#endif

/* value_of_impl.hpp
adGoLCmNKCtHYxLXMCCZrqNUWrZKu/W22IqaJeZGaahZamplvi2Xpt7UXlHLnP95lnPvnWFAev/fX5/k3jnn3LM+5znP85xncT50Ulv2Zbzs0lIWjZXte+YYQCRbeRErahWgXp/DQLKbgaQTZ1SIDOdDG5u+bB+EjLC0AiHh51uuBh49xCeBh/WOd5xD6xlvCYOQO1tCyHUIIfLLXbPpy6/gahi9f2hZJzhrbYw25FdF0nIzaM6OFR1z1pn1U4NMloP2x+YQ4bGNCQ83Eh7bQub51tm2U+3A0aJIDS+prt66iL3GUoVB+0BszLLHy/KrHDFn5jyJRv32tw91ZLHVddPQmHJbVSg0wm8dGhUUl5A1tJr/CoKjNRwMNZ1yg3/doH3aLDpNIQkgclm0iVu23JxsMpw2xbNCt46t8imBKYP2e0R6Uw3rkLZyEjkrg96EnMrfbJW/mCMC/IY7iAy7IJq9JrnZi69/dIJ0ouC/7mTQfmwmBVAGtpSxeHAtOGSCkYr1gnBQLtF9M6RlUhrYnRdLDWJtPI/NJCjZFGUysXscuVrJt2aA0GQWtCU91MD5Db50DUsrDfnrmfqwTxBTwb5RzFwmM7zM5XoZ6Y4iFEREmR6zbK3v3v/MAH8+0q7Y40Zla1S2TBE/wRddgQAQYk/QH12RgKcpGjwNeElCB4q5wkBDj544fgZhqC1mreWJM2xGgBgjf8IYg/bh
*/