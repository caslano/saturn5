/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SINGLE_VIEW_DEREF_IMPL_05052005_0258)
#define BOOST_FUSION_SINGLE_VIEW_DEREF_IMPL_05052005_0258

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal_to.hpp>

namespace boost { namespace fusion
{
    struct single_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        template <>
        struct deref_impl<single_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                BOOST_MPL_ASSERT((mpl::equal_to<typename Iterator::position, mpl::int_<0> >));
                typedef typename Iterator::value_type type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return i.view.val;
                }
            };
        };
    }
}}

#endif



/* deref_impl.hpp
F1my7SIf0aOj1D69tf1ufxtlkz8pPmoPf8Mo7yXpreK4Hyc+FvTEGOChOnnu+BVPy7c+W7453ehNOQlnXMFiE09zXmZpR7Ldq7yILsgp1hf5ZuXs0J184hTG64EnLMOY90pnESnA+uX3twsQp5XsL9kh+wdYXTxgPqNXzLxnXlF+P+Z0WuojX7wdVg2Mw6r7Nup5mwCDswVYujmtePp/W5J7DHCJ+GauT8+6yUO4+6JNv29ED31B1UW+JVkb9AfnGYT6p4sv96BWtaQdIePaHP59rT9N6byBNqzTvoH/61I0vl/8IXDeU3ofg6xGXl/1/R1fyf89lb93JrM8Mhj4YK1WxmcgOw16dk8SrEEfEN0guX6h4oMXPQZ4gU3rFYp/x1ilWWtpgyK9IfKJfZbPWdPNpDtlS+tRd66P9YjZC2U6thi0BidmTavtF/naZJMLebnkzq71D/SW+7e+m/2gQr/IVrG/ZZTSf7W8ArLivd4fnWi77GIVxeX8GV1eJvmJxetjPTBtk+I88jm7LMSgfFTeb9Wld9rITyiShqM+b/zBkD6jU7y/pfOwBhioSZmiXP9tQc1iD2dNW/kWnyZ+2wIEGwgN/INeO93oLKEPznpylSQs073opRlz+TjTfdLuflfGoxMjEt1ZJ3LfjWad4tpfxh2lQ4r6QqV4v5H3yv1oAiTMIq9qTc/KJ+XnD43QKwZ2/0f5yvnDR/qk
*/