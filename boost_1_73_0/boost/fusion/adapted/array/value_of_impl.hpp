/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_VALUE_OF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_VALUE_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/remove_extent.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_impl;

    template <>
    struct value_of_impl<po_array_iterator_tag>
    {
        template <typename It>
        struct apply
          : remove_extent<typename It::seq_type>
        {};
    };
}}}

#endif

/* value_of_impl.hpp
D8mX4qa76ZdvJvan+2JpUFYrDS6S88mmrG0t5mlWE/JPa43/q0T3pb2COP0dcZ9I3J9GnF+JPIXId4iNvT32n3E71A6SE3O9ynWTD+fL/UawOYk1hWvc3w4mjWJhrOf4S2i6Uu5GLFkTh8gaOZErDONE64+ZXv0EnmsApPwzdR3KMv2Wb2ydTrXYk7JJ1+mozpQ52sds9KYsqdVPMPEIS35P2JRh8PdwFfZX9IqV1bRj5pZL
*/