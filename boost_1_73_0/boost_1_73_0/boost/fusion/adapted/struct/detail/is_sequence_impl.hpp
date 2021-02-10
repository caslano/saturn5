/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_IS_SEQUENCE_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_IS_SEQUENCE_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct is_sequence_impl;

    template<>
    struct is_sequence_impl<struct_tag>
    {
        template<typename Seq>
        struct apply
          : mpl::true_
        {};
    };

    template <>
    struct is_sequence_impl<assoc_struct_tag>
      : is_sequence_impl<struct_tag>
    {};
}}}

#endif

/* is_sequence_impl.hpp
u3AW28h5Sh8fPcV6LjANNPMsUZByBUok+oFKBvic8YgVisVAFcRMRZKv8IUXoFMGCc8YDGbzm/H0owsPKY9S5HgSFahUVFkMKb1nIFnE+P2GoqRSg0gwG7ljrjTyVZqLwkNpBprJXCGFEaeZEkDvKc/oCmWohlTrUp34flTJDJ37sYiUH21L91Kd11XcoIOcPoEoNWgBlWIuGJwLuYh5Yu7YCgyW1SrjKnVfrKBQEftCgmJZhlSYxpnaWGawqDvjGhSU6JZrc1OiUEbpIRX5DhBbiCRJJQuUwRYgJhbYYBeqImbSYm3RW4W6m7a1P5mSF68xiAKdQLO/gPGiCSuquHLhyzj4NLsO4Ev/6qo/DW5gNoL+9Aa5Po+nFzjfHJUksMdSMoXKEnheZpzFVvDXXYT0r4PZZf/zMJzNg/FsuoAuJEIyvi6gEJ2YlQy7UETYYUJ4EWVVzOCS3jFbPQYIyWkRXowXwWXfZjstEzAvJ95R1zvyTDPahHwKLifz/sfhDzBmWSBifjH6CaCMExwfTIb96Wg8qRH/E7bxZZvbrlO3hjBt+DW46tvADnEbBqaOCbpTnn7UBIOHhrMLUiQJrppOB7Exl10PnDPoOeeELK5Ho/FXa8A7AmucEPN7smOIEKzbhknDaW2JMYyF
*/