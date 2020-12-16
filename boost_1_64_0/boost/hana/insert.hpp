/*!
@file
Defines `boost::hana::insert`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_INSERT_HPP
#define BOOST_HANA_INSERT_HPP

#include <boost/hana/fwd/insert.hpp>

#include <boost/hana/append.hpp>
#include <boost/hana/concat.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/drop_front.hpp>
#include <boost/hana/take_front.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Set, typename ...Args>
    constexpr decltype(auto) insert_t::operator()(Set&& set, Args&& ...args) const {
        return insert_impl<typename hana::tag_of<Set>::type>::apply(
            static_cast<Set&&>(set),
            static_cast<Args&&>(args)...
        );
    }
    //! @endcond

    template <typename T, bool condition>
    struct insert_impl<T, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    template <typename S>
    struct insert_impl<S, when<Sequence<S>::value>> {
        template <typename Xs, typename N, typename Element>
        static constexpr auto apply(Xs&& xs, N const& n, Element&& e) {
            return hana::concat(hana::append(hana::take_front(xs, n),
                                             static_cast<Element&&>(e)),
                                hana::drop_front(xs, n));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_INSERT_HPP

/* insert.hpp
HTImFrxZ+cyrq0r+QWZZ1r4Z5/oB87JM+NfGh26myPZdlbRn+aw3VfniMPOk9bh20cMEW2Q/Wx0Ms0zac1xD6GaGLSLPdZ1mnGWye5XLCItkPs85imEWyHi+dcUAs6S+QBn0McUG2X2ub4ywRuYLnUcYYY2MF2kXgyyT9mJ10s8MKf3KZFN/c37j/MUIq2T81vqin/wPWIu+l3Pkz9YB82RtSWec1iPm/1HWi8fZfzG3jJNt+xQhaeVUfVBdts+/PP6dHt9RtK1bbL7S32Iw53H63+zPGGsc2baOj7oPEudJ/7t6GWXR9gwfOp9klGXS3UNsSBvyG+FH/uE7h0wR/qf1Ry+TrJMZcr4h6ncR176rT47P1ddYB9+zRohZQyOkLTse6WGCDVYvciw75w+T4152Scz2++knGGGNvB86JzPst26mxfBd9ZtZ+bc8z1nRn2KPf6T8H+vna3x/jT6P5wn/xDq9wjoQu5l/hDUnrjLmNytPX+nazRIZq8bzRt/xfJbvnH3b2JC1ZL6+I/+C7/GJ2fq4/gXj8EV9P2+MxBVyvuS+mRlS5n0Pmh7m2CLyZX16u++iiQvEYtZgn3m41jHyFeXRuG6diUuEvup7zHTR+AHflRPDX/N9YtqZIfXrzlX0xbXZT8z4hm0MsUrmorXBFFvkftNaY5wT7zBnYua31E8PqR9XH2NM3uDvcMT8T0hjLMPxK4Y+qb+0M8RkmjEQ5z8lzfrcnjQnn7YGWfqgusQtop8xliyTM2t/pkn5rDYzwiLZn5PGEDNkfd54MUf2nLYwR4Z5OPVR65j0pzq3aW+MFOtq3baobb1+V22BlE/4DuGsdRj//laX70wywgKZvrdRxfq8dfAxY9zhdRp5E76jOm1syPI7nsOF8e9TWf+en3y/vjDH/Ov1T8wbNraTxoNy/R4g+0PGmRHm2SL7w/rACgVT8rHGiY/oC93Kqar1Wkfs7/U9NjHtJmXSxQwbFLzHPuruZfl15k7cfq+x0+4x1mjV3omo70ENGWf35jFxhtTXWqP0ssA25coYZEs5SyPyvNn4Mkaj42ZFTHuLvtPHAplvVR9ThEaNAScZZIW0t9mXfqZYJe3tjgdiLJDzDuPBErljHrNEzjvVwwoF71IGq+S+274s314bn28MzrhOiquOqW5xjBz3IYti2gvsS6rXOD3iOPO/8z1WMdqn7WxS4Ng88kLjywibZL1I2XQzzhKZL7YfPYyxQkq//Rmn4GLPX2psGWCFnJcpl1m2yRkwrvQzTfjlxoNe5kl7hfmnnyUyXqk8BlkmdVA9NDPMCtmvUgfz8b+/FtdZuF5dNxgrZlgjr8v8MMoC0fPqYZJtsp9uzTDIMinPUDejz9QWZt/te2o3KpMJ1kh/lvbTyjCLZPbYj37mCT/bWDLGGjnP0Q7GWGXcfd8iuc+Vjx6m2CJ6Trlk689Gh3Xa6Xmz5zF1MsWppyqLJdJatYfuZzv+xXm2iV6nXOYZPassIs6bc74XPSeG2z1ngPCIcwRLHmc9zRpmnPJrrRkmWSa3WXtZaNHnp8hHepNyiF5jHOn5pnL63TM+THsZjPuJa7V46kmutw83FvSxQEaBfUl3j9snLpJyhfGkl3m2iT5C2cyxTfkjrQFm2CRyxDwxzQYFj7JmmGCL6JXSmWad/KPO2YyxSGZEfxhgkXChdUkPmYe1XwwVqZcuBtPdE4kpxcqih3G2yI7qO2OskVNi3Ni4xHEqhkqVQxezbFBQpn7GWSKrXP0MMk24wnomxlidejjyaPnZpuq4vCySeZWyGGWdghPaxzRbRB5j/Fkg+7HyMsYm+Y/TLibZJnrSdvdGA+IS2Y83jwyyQNoT5GeG0BM=
*/