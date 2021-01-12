/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VALUE_AT_IMPL_09262006_1926)
#define BOOST_FUSION_VALUE_AT_IMPL_09262006_1926

#include <boost/fusion/support/config.hpp>
#include <boost/tuple/tuple.hpp>

namespace boost { namespace fusion
{
    struct boost_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct value_at_impl;

        template <>
        struct value_at_impl<boost_tuple_tag>
        {
            template <typename Sequence, typename N>
            struct apply : tuples::element<N::value, Sequence> {};
        };
    }
}}

#endif

/* value_at_impl.hpp
1f2dvxP+gbU1/465UnnovzPtee84ztPwiB3PeNK9dbW82D3Mkt9L+t57EV5H2jebKOWFTI2N9lkwrFQzSucMAXjNH9FnqFLczrd7e8+NxW/zXLvmfcfyWW85/zBr5K6y9ZsH6uYlu7Pd3/ilevMMVdeaQ56vDaNYmd5K7KaYevhTk6Qd6VVWqL+6r66MyTo3bfw0Ye0m9irsEPMjvcoI9cfVHpAYLJxbHvv25GliZ7kdJiRj
*/