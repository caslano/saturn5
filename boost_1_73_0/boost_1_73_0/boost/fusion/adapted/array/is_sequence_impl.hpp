/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_IS_SEQUENCE_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_IS_SEQUENCE_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct is_sequence_impl;

    template<>
    struct is_sequence_impl<po_array_tag>
    {
        template<typename Seq>
        struct apply
          : mpl::true_
        {};
    };
}}}

#endif

/* is_sequence_impl.hpp
EmylYLcKdqdgvxLsYcH2C/a6YIcF+1Aw+OQxtsix2HrBrhPsWSXNc49KnOtMcaWfTmyes8OzGlpzbU3RHnpBBfcHuyqBr0G+zq7HIF+OUj/QiaGTcWLAnSc6fGeRKt2yKr4DVY5G2MNgLxkvhn3GeyEkVRfSRTNVsIsF+7lgqwR7R7BDgoWaNubntOEZEjQUNqW6ZGU7p6phfn1FbVVd3dLZrcv4QS1kvdY3qYzfanzVVjxDcDstubfgGYJrUKY=
*/