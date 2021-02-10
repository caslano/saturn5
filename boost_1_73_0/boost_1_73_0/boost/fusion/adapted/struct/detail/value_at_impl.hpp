/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_VALUE_AT_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_VALUE_AT_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct value_at_impl;

    template <>
    struct value_at_impl<struct_tag>
    {
        template <typename Seq, typename N>
        struct apply
          : access::struct_member<typename remove_const<Seq>::type, N::value>
        {};
    };

    template <>
    struct value_at_impl<assoc_struct_tag>
      : value_at_impl<struct_tag>
    {};
}}}

#endif

/* value_at_impl.hpp
MFgOwmOwNKK5QfeHGhrRXDh3R8UuRieUCg4g4DQN82o5EWWweG4SckhVLScL2TYbMNUyQkprnVMnlATnwybBRiz1lWMsBHjziSovRM+DNf5/QFySMw7uFg+wcKwgefiCyU7EerXGTLMycJ/RJ1S/Cwc/ErtWBQWVTYtqlFEYmmvN+kRBFthpPm1EODk3iJBu2Ah/3dVNxPTJGITT/ujEu4oF2ql0ojFY8YQq1IZE6IQMa0ifiGgK04hWZ+NztY6Iz9W6pDnetsfYBQsxyJ83RDDJMYigspvEkPiqzYh8/cFWoquDx49KEYUvuDSI4P2ojfDfj1qIwL2JSYTiZJMIxfs+wh7vm0TIXpuEqurThEjXNloInnmTFifhTFqchPNEWgm3g/IQ7kzKRbjVxEp4s3orIRNaTEkprdeRdsKX59iJtmFtavWkPgJiWIvhMgmR8dc/nmYSihPPRNOQ6zJ1bsK1I27CZbgsRFfGmdmbX3uEu13AQUS4Zo2A4aRsFgrcNcKdMtuJYBXVRgTLJRoBUUzQR/eJUB+OSbStzkLFYlGdHDE1HCtRth2arus1DxHRZaHaSmckVAVwEJGZcFQDtkmE2gBMItSAbSP8DdgWomnHlFVJY4lGzX0h00uCY95WcX51DslGBKJ2jSDk
*/