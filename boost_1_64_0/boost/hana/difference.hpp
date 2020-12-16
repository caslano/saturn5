/*!
@file
Defines `boost::hana::difference`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DIFFERENCE_HPP
#define BOOST_HANA_DIFFERENCE_HPP

#include <boost/hana/fwd/difference.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/erase_key.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Ys>
    constexpr auto difference_t::operator()(Xs&& xs, Ys&& ys) const {
        using S = typename hana::tag_of<Xs>::type;
        using Difference = BOOST_HANA_DISPATCH_IF(difference_impl<S>,
            true
        );

        return Difference::apply(static_cast<Xs&&>(xs), static_cast<Ys&&>(ys));
    }
    //! @endcond

    template <typename S, bool condition>
    struct difference_impl<S, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DIFFERENCE_HPP

/* difference.hpp
lvqS0nZ0nhM3t+D5yVG3t06sG9msTp5tqkD5/0zxfe2iZ399aODZqbWve29dWMo2q7a2WUk/nDShoJ7DS+SzwpX2cygaf++HSP+cFPLPkc8HBUh7CkRHf4+ETKT0hyHp9Pdv5KszWdDagdYSBeTjlioA8uXwJV+OIPLh6A4uJt+P+8F9KNwfvJR8eB4Gn0u+HrKcTMfzOng0ldMJkk7lvEq+JWvBvcg3I4Z8Ms4EbwIPAL8NTgC/A74Y/C54OPg9cCJ4G5V3u+O5GvwFlddZ1gFC341X7TkdfCp4IPgc8HngS8AJYFnPC8ATwBeCJ4FHgmVel4GLwaPAFeArwG+Dk8DvgK8E7wTHgw+r8uk5E/wghQMhJqpPGurdAZwBHgLOBl8ofwfPAOeAZd0t4HlgG/g28A3kK1NIvk9G8GLyySm2++SQDxE9o4AjqXxXH6JZTt8ZuqeDYymdq+9MGX2Hbhm4C/noRJBPThT55CgfMMc9ku7ZBXRvGkr5vE/j/TG4K7ia5tNn4FPUmNnHZQ/llybnGOU3hvKT9UgSBC/kJ0mOK4VDKNwb7EPjrAHLeRRA4xsMtu/lR9dputYXNNrLLxTpfMnXKhQcDl7gYlMutsJuDCHbsfLnqULYN08j4iFxEzQiFTwbshzi8PHZg79zwfXgEvBy8vWJtMH3x+Zue061nWh7zkWcq/15HsLSBl0Glnbo3PE4xtbwrnc1/m7sB3SgwRfI1S7ttElXgmtwnKtNOhPS2P/nAETapEW+RsSma8TQNPf3vn0zT7RRhyGtwxdoUP6J/kCjECdt1mngeZBySBUk5AakhRRAyiBrbmD/IAaDwfiTvfMIuRqIovDYK3bsiB07duzYe+9iCVFHjeV/IYldEdSFiIKgoIhtIYIVFy4EXbgQdSF20ZUKuhARG1ZQ9My8m/jsNdbzwXCd/03u3Ezy4puZMxNCCCGEEMOvXP8/F4UwhTB3slX//5j238x/t676du//Mu/v/S/z3/7b+Rep3Lyq33HfmZn9yr3/+0tdxz9S15Ev1JU7A5Gz3hnlHVNojjs7mXcQPwXsnFVR9eXYzJhw0WTdduzv3fcV7LNjszU3zuo4+0rpps/CcufXblnbUt5XIHV+6n0F5WTPufKw+WErwH7NcZXkuMpyXBXYkua4+YXUWKRV89k3J4QQQgghhJDfTRrr/0X/70zV4awo4//wOoC0dPVVqqhkn6cdovHuJXuetIY9B+FAuyem37tK+vrToF2d5nqzldWv9amp8JlRZSdabilfKdmXbojNd1Q1kv3x5rshWmby3OnTIdX1IdSFLFQl2sPeT035GpLPp2bbfFFVMda9KasgdSZDpokMynUve7WQUuNsPXXzGX2cLZjo0Bz4DxbasqIX32rLdpN8PnXN5ou81TjjnHBMZrbjT0Em0QiutuWO2nOpndWkL5iifVuJn/HMHRPij3Y8oyusiaXQe+UCPSUTTM2WGSrjI+VsvLKln9RXFnaSnLvNJ21R1vq9VyuOUy+IxGtc94Ns3dJeOjQiXC+cgeaeFrhztG2zG4WUnPd2e94FCmf3pMubOhvlprqRm23b22/LWR0j/qG6FoD/Kkbf2PCddRHVqmTHcI4V+pwWvmzZc/gc9w7GcMy9Y7Xw9hoiXvzt3etbG591NdbqAD/e3jVES19Iyrzf1vjctgnaDJ+/12Zy/I2k/g/bC/HZdkAb4fP326h92aW2fXBOtbP5jZLvL/mrkh8k+SbmOso+aiY/SPKd5fOxkq9f+911JAULfeq9n59YhzHfywuiL4+r5daB87SMlGfjEBlfXPluHSG2OMzDdcI6JN+P16pUsjfc1EyYq/EXDeh6e3yhRIM=
*/