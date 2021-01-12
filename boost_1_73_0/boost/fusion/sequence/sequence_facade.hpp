/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SEQUENCE_FACADE_09252006_1044)
#define FUSION_SEQUENCE_FACADE_09252006_1044

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct sequence_facade_tag;

    template <typename Derived, typename Category, typename IsView = mpl::false_>
    struct sequence_facade : sequence_base<Derived>
    {
        typedef fusion_sequence_tag tag;
        typedef sequence_facade_tag fusion_tag;
        typedef Derived derived_type;
        typedef Category category;
        typedef IsView is_view;
        typedef mpl::false_ is_segmented;
    };
}}

#endif

/* sequence_facade.hpp
8TjjfZ18bwDR0WOfEWpCJwYRczLf4721zOE2JBEHIY6ZHKcupH3IQSkaMXD8PVeR2/g6n/eU8DoZSZw7hBLU/t9nnkaRMJm+QiGq0IweJHL9LBQiLZ288koUf8dhTJB8PC6Zg7HIRS19UcZxmGM3WpB/EePJsYpjM33WO5+5cQ5zhnjPQByKMMr3hz9L3oinbbwu4z2ZxGgu+s9gMOLof46FxNFoLvNgKWMZzc/5nVZUnEUb
*/