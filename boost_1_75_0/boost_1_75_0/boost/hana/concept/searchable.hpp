/*!
@file
Defines `boost::hana::Searchable`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_SEARCHABLE_HPP
#define BOOST_HANA_CONCEPT_SEARCHABLE_HPP

#include <boost/hana/fwd/concept/searchable.hpp>

#include <boost/hana/any_of.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/find_if.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename S>
    struct Searchable
        : hana::integral_constant<bool,
            !is_default<any_of_impl<typename tag_of<S>::type>>::value &&
            !is_default<find_if_impl<typename tag_of<S>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_SEARCHABLE_HPP

/* searchable.hpp
kdIzN1t8eTD9VJGLK/s4hKRv8dmrs2hpYHp1Fi0VTNFPpo9uGHaxnXSYZgoqQA1kQEvGpdSKHhCOxAdfJVRA70mJfgcIGilO2vCy43MkyA4iSKCaXhgFWUVMlKt0ggwhQbZoBJmiEWRL5bIsx/7KpXiyl6O94ROzHOgxNdBU5ouvugfko8v7DDnSpV4Dym5p/oIW7AI6jSK2wk24lFQ0gIRTEAKq6SWqGYBCoQ7rH+Td8vO/caypRWhsUheiaLjRn08nStzZZ6xCbhsHU6F0s7rabO/LavRl+BdZto6fnyxdWHPUN2ZriTB/pSCNAnELhK6ao1InHkapb/dCh9XpfQlGAGG0+C6ECbnPIOCD4BvZZ6DXRp/J3pcHmUAmydG5LVQFJewdcXgMS2Y/EkOyvQ/q+AaS85vIDjLXpUqTq+fTUs6F1fMvgc72jVGFKY1ZzeuH9+WmCmLtHwHLfQvN5b5LMu82izW/hsdMCej2Cbgp1Cgpg4IrWLvw4JrMu63SRQiCj5e4zLtTpFEAzqPmakOkjBcozZfvtZnWz8m8N3HjFerCFHUd+gJOFXc40pxENykIHh0+sSdW6MI1DAv0gE4lH8a0wkhXrWC/orNDU2MwoC14zjkeDjfHP3eeBc+XaMHzOW3BU1vc9Oeaney9XnKNuzBQMhig0zqyPR4UjCx4TitSbidavEnDGUDTdoUlvCnZ73jVye79nEQP
*/