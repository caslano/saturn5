/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_07172005_0831)
#define FUSION_DEREF_IMPL_07172005_0831

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>

namespace boost { namespace fusion
{
    struct cons_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        template <>
        struct deref_impl<cons_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::cons_type cons_type;
                typedef typename cons_type::car_type value_type;

                typedef typename mpl::eval_if<
                    is_const<cons_type>
                  , add_reference<typename add_const<value_type>::type>
                  , add_reference<value_type> >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return i.cons.car;
                }
            };
        };
    }
}}

#endif



/* deref_impl.hpp
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
*/