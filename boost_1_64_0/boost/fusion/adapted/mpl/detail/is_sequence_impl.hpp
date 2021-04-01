/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_SEQUENCE_IMPL_31122005_1505)
#define BOOST_FUSION_IS_SEQUENCE_IMPL_31122005_1505

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<mpl_sequence_tag>
        {
            template<typename T>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif

/* is_sequence_impl.hpp
740DMQJk0eddscOYpnnGe0s4ILfI8Gj8LqlISskRC8UpU4tEtY+Q67mCHf8Yqdovwt6YnlM0IRBancteUBguiTnBkTSagbf+oO+Q4zUslCI0tCZCmnDXsUGacj01MW/h6SeMND8sKojdeuIjMD7XQk6f1xPaBrz/vzWxNvHpMS27ZdazJs6KCgqa2dvfZnOB7nA75Kd+hSAf43p89UwjxRwyLyr8LK/DyktuhkXpCKC5STKnLU/O2lIQ1wWUN82eyeHCdjb4sD4OFuIWklE07p69pX5asCcZro+gohC9fXiatw5pQ00xH7vlUZ+llbMVN7Vo7ta5FQosxwdc/l613BauypNjW6dsr7k+hvU5fV8GHp1VzzmReL29ob1DGFfzcNnBIAGHJLfN8n1Xzt7718UuLPxaYZUYYnMu+UtGhGc0RBrI95G4geuyVhfXkcVy0zWNsIbRaSIyq69TPxsbAmHyhN8X3YMLvRGtpASf8yRezf1j96dIyPc/jIiOA/iAKbMOkefJulHrNm2TlVuDSKtah3Ub9K/hIfMAdCu37G2yDf6taSxLwe9dSw==
*/