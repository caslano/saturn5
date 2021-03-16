/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_AT_IMPL_27122005_1241)
#define BOOST_FUSION_AT_IMPL_27122005_1241

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_const.hpp>

#include <boost/mpl/if.hpp>

namespace boost { namespace fusion {

    struct boost_array_tag;

    namespace extension
    {
        template<typename T>
        struct at_impl;

        template<>
        struct at_impl<boost_array_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                typedef typename mpl::if_<
                    is_const<Sequence>, 
                    typename Sequence::const_reference, 
                    typename Sequence::reference>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return seq[N::value];
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
K6KgZuMrQdsrFX1mAZsLLAzsNmD7gTUCk7R9ojW03eRNW73vtMW0Fd5a5UxpK65vLW0LNG2nadpO17TNBm2zQdts0DYbtM0GbbNB22zQlrFWWJLfJNn1/C6R2LfSzaMRqisr5lclCq/RWWpeM5I1teNZkn++pLWWZOcYD4p5fit8Jpa2Jn3ammyjrUmftiZXo2FWQ6GshkJhrAbYEmCHgH0MrG5sDhj+VeFOEZmkS2KYu920XlBd6kyI5k3yJLU=
*/