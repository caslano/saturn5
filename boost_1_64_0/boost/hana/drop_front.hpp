/*!
@file
Defines `boost::hana::drop_front`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DROP_FRONT_HPP
#define BOOST_HANA_DROP_FRONT_HPP

#include <boost/hana/fwd/drop_front.hpp>

#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/integral_constant.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename N>
    constexpr auto drop_front_t::operator()(Xs&& xs, N const& n) const {
        using It = typename hana::tag_of<Xs>::type;
        using DropFront = BOOST_HANA_DISPATCH_IF(drop_front_impl<It>,
            hana::Iterable<It>::value &&
            hana::IntegralConstant<N>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Iterable<It>::value,
        "hana::drop_front(xs, n) requires 'xs' to be an Iterable");

        static_assert(hana::IntegralConstant<N>::value,
        "hana::drop_front(xs, n) requires 'n' to be an IntegralConstant");
    #endif

        return DropFront::apply(static_cast<Xs&&>(xs), n);
    }

    template <typename Xs>
    constexpr auto drop_front_t::operator()(Xs&& xs) const {
        return (*this)(static_cast<Xs&&>(xs), hana::size_t<1>{});
    }
    //! @endcond

    template <typename It, bool condition>
    struct drop_front_impl<It, when<condition>> : default_ {
        template <typename Xs, typename N>
        static constexpr auto apply(Xs&&, N const&) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DROP_FRONT_HPP

/* drop_front.hpp
O9+R+UIyZfnl2VI+rVCmNpOUR0+U7U6/wHo/kOnZ33uNp3vWCLFQCHHRKcsFMn9ImCLb65H5bqSx3+tkvhoHr6+U37elGWS93jKdb/MeT7cOyXoc2+T3rHSDTFfLcjOflt/tRbK+hGVyvnb4yfxL5rG/FpnvfKIc/5RXOZ9rZD3KOtm/U8OyXEmBvD79vCzvl+EjJrrHy3pS58t8FQNSfozzf+OEvH6O3y+ahWx3luzfwVIf4SWEOMl5nOGU1+9k+ghv93y/I8vnFMv++MyQ+U4XynzTOQ+KQ8q3f1/IcXJe9r0i0wOVQjzgrm+PlJ+8IMbrv8V5jeT8VbDeHeEy3cr6jwlZj32Q45+E6+PlOV8o7+MeV6ms33xWlncVsP4kIdepUt6+sp1TZHuXZLrLwnl7VJarUWR7M7l+2w95j8/T1ThFXv+8tyy3gP3YIMdf4Su/Rz8jv++ok98Dc33kuFbJdMbvvGR71PctnOdLs+X1HPZ71Xfl93Mc/8nDXJ/32Q/qS+Q7cj5f43ydfZj6HirTOdS/I9yfA9nyeoKN+tUq6z3fIeS8lMp81x+R16NnUl+4Ty85uN8uKnK/TJD929Ig010zFZn/PZmeYL9s1Peck0KOq1z2fyBFznMg13eKTba/daNMp1P/anJluo37cucaqac5GbKeMzbmmy3r8eF6mtmfIzsM8vrjsj+XOZ+O3d6y/2dken6DTE+h8sfd8/knmW8R9eYW5BCJOfy+g+XOsp4Zk2U7y/l959sst5v18pwp+byQ+TNkv/e8LMsdoX7Z18t8uypluojlZ3YKOb8TOA8R8vodVV/WCWFy94f6NWedlJc8Lb9fKmQ/r8v8l8JkeiRLyq+mCJnfwPNivZSf4r4MrOR5yP4s/7hMQwp8ZL4L3rK/nAd7jZB6yHVx1QiZj+fFKu6TJTh3fN3jYr1+A1w3hxAJ7nwsd7OZduQRKTcXSHkkxzeN+WYkC6mf/J7A9Ibg/ub3aKY53Pc7LrD+RxV53eklx8nxl7Df23Pl+XmC+c4xPdDDdQjnPijkvo3kPqQ+nsqgPnMfneR4X6PehRgMsh2e72doN29wvx5ZK+WnU2V68Su0Y6vlvji5Qogl7v558Tw+6zV+fcsvFLmurMfOfpylntjflfLUF6R8jot6TL0NtMn0XDTtIO3UHOqNwva2VMl8Poeo99zPJ3fRP3ib482W1/12ynJ7whRZ7xyOk+fPdV6/Wizzn+vn/pvI85P9T+X6nP2YlG+Jp33LlHbi0myOj/ZwXznHVSrTm5VifF0XcT9eXS3bS10rU1cV9ajKS9ZP+Y5Ojov6G+LNcyCV/W2U3xX2Z853uW+zeF4ZuI70BxI+K1M7293zAu0j/a8Z73P+aKcO0s7Fqn6WTZaLLKW/w/k9SPszhXow85tcxwW0l/SvQqjPrjWy/Gs2KTc7uS7c3xU8dyKf5fzly/RqptyXyxdyf9O++Kh+zFtcT54XU2bzehHP235p1w5wHgbSuL9XyPTmWtrFWfRHaD/ttDs36EfeyZP9yKEdfG2TTK/z/L74eVlPLNc/h+t5nvbcRXu1bS79hFNsz+kj9YTrfAt2zMetD3ZZPktdj+W00+tlfSe57xLOUa+T6bfQTu7Ll+VX0a9QmumH0l5kFcjz/Rb3xYzd7N9q+hdFtNvrZVrSJMufoF4etPHcKWW/5lAfeA7ZVnD8y7kvD0j5NqePLB+v0C5R3w20W7TfLo7Hj/pu53wFvivlkRzX1nW02/ulfNcsKY9VZLnDtCvbuT9vlch0C8/P7ZzHgxsZN6xnv9+gP0x/7U6VXKc5G3md83IzW8qnf47nY7Esv4t6OYNxxVaeA9uxzya418k=
*/