
#ifndef BOOST_MPL_LIST_AUX_CLEAR_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_CLEAR_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/list/aux_/item.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct clear_impl< aux::list_tag >
{
    template< typename List > struct apply
    {
        typedef l_end type;
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_CLEAR_HPP_INCLUDED

/* clear.hpp
AnDx9VG24FP9mUfAE/+Pl/pI3o9/kv6IjiUZFsSBHYnmjMPZf/YdfetPTjIAf/wt9MRBPGcMjtsA71k/XMcCw0Bk8RCk2fIdm2d0f8zeP830ZcxpA+GMQ+sHBXeyrzmeOf2xAv8kEW5chADDcezP362/FvSmhOZ5YWm+sXBSQ/1zo58Hzd8KhdxlRwrP5r2CdF+HjkqM32LjpM/MRVeZwIq6IymUJPnTY0KpP12OFUnqxWnAi0fm3b7pKK/7bJuN4CCahI73P7o++9rWzlDZ8XCXGpX9IYrFNJ5ZlOd/9EQEuyQRMMxh1dFms0t7+E1qUaxRbW+CNcio/YMJGSMwzuXYw3t6JVi8SXUVqStN/boB0CCrI0IAvA2bL0sdFO8oydG8jLCPft2uCEs98/G7S6OMEGRhvezYc2kUTLOrWplJccDrYOv0Gnr3Dv3WBNUQnbtzNjiChA5Ds6Fqr468YD2Qfy/sGOmvRM4U0g432H/oh3qkEt0LLPQoDODWgfb8KWu9s+0a/EMCQUKs3smYHhZytB19fWYArdUuWNo+b4cLv6kfeEm5opb4qAN9Cr2WdIRSOTncvNtQblPPPQkOtdf8CWpI3buJ/XZk50PLkfoWi7oT9OewfJy35bblV6fNd//r5g8zokAJ2qDmgj9BIz/5F9M+1z/1YL8pXg/DAQGu88k+K9sByPo8b8PQINFr0m35AKIQwVAqDgWs
*/