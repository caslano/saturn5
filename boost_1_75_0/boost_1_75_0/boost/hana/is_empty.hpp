/*!
@file
Defines `boost::hana::is_empty`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_IS_EMPTY_HPP
#define BOOST_HANA_IS_EMPTY_HPP

#include <boost/hana/fwd/is_empty.hpp>

#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto is_empty_t::operator()(Xs const& xs) const {
        using It = typename hana::tag_of<Xs>::type;
        using IsEmpty = BOOST_HANA_DISPATCH_IF(is_empty_impl<It>,
            hana::Iterable<It>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Iterable<It>::value,
        "hana::is_empty(xs) requires 'xs' to be an Iterable");
    #endif

        return IsEmpty::apply(xs);
    }
    //! @endcond

    template <typename It, bool condition>
    struct is_empty_impl<It, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_IS_EMPTY_HPP

/* is_empty.hpp
V/7/5n3DnnaTwUdJ2HL+O5IUAbH1D6xF73cY7gXNgT8aGYR5hVaGrb4VesdLY7RfWN5Led6oXWX9zIPfl4mi1Ubz1VEcLcXxfSDRvM/xpPmgnazyHCaxqvSfknR50qv89vKsj8fz9wnJ3XCen4PruEwyjVDV8i7V64Oo9bxXpDQMogXLe97/xpgx1WIyZWt1+Q9qF2lCUyuvk+p6Gm+d2r/Tv0icsTPa5W7kayO0eoPjNDOT1kD07tqT78GvXKeV92bjSInKhHLNuPYYDwoN15pYrMWmM6QaCiyFBpZkERYMYzAZHLSlgYXX9FGNW+2jUmv8VVYwM8Hd8kMflQtMhjnfbCkyqw3FOoPVQXvLj8ieZ2v1aq3JZNFp6WHrWl7PbDZtidpsKFKbDOZcB1+IngvPTF7h5OlzmgYzFUydWQJgLXzXCXcWYCCWGRB1G8UCZwDWBSwVz8sA8ajVKuHeILBCpLdHxDsBCNNvdkk8T2pEp9ZugBtPX90W4e8C+uCDOKbCubm/wIA48q8r3CqBTQS2iCO6Owh3sAjfVbi7C+wt/PsLHCgwHBDPMUYLd5zABIEpIn66cI8U7rHCnSXceuHOE2gSaBXPHQKLBU4S6BI4Q+BMgXMEXfMFlgr/xQJfE1gWR3xdK3BjHPGzQvDlAGATwGvCfROwEfI3nqlaI98AH8XyC7deuGcI9wrA9lifgK0wHUA11ssQpmqD
*/