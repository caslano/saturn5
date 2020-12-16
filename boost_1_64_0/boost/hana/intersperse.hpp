/*!
@file
Defines `boost::hana::intersperse`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_INTERSPERSE_HPP
#define BOOST_HANA_INTERSPERSE_HPP

#include <boost/hana/fwd/intersperse.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/bool.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/length.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Z>
    constexpr auto intersperse_t::operator()(Xs&& xs, Z&& z) const {
        using S = typename hana::tag_of<Xs>::type;
        using Intersperse = BOOST_HANA_DISPATCH_IF(intersperse_impl<S>,
            hana::Sequence<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::intersperse(xs, z) requires 'xs' to be a Sequence");
    #endif

        return Intersperse::apply(static_cast<Xs&&>(xs), static_cast<Z&&>(z));
    }
    //! @endcond

    template <typename S, bool condition>
    struct intersperse_impl<S, when<condition>> : default_ {
        template <std::size_t i, typename Xs, typename Z>
        static constexpr decltype(auto)
        pick(Xs&&, Z&& z, hana::false_ /* odd index */)
        { return static_cast<Z&&>(z); }

        template <std::size_t i, typename Xs, typename Z>
        static constexpr decltype(auto)
        pick(Xs&& xs, Z&&, hana::true_ /* even index */)
        { return hana::at_c<(i + 1) / 2>(static_cast<Xs&&>(xs)); }

        template <typename Xs, typename Z, std::size_t ...i>
        static constexpr auto
        intersperse_helper(Xs&& xs, Z&& z, std::index_sequence<i...>) {
            return hana::make<S>(
                pick<i>(static_cast<Xs&&>(xs), static_cast<Z&&>(z),
                        hana::bool_c<(i % 2 == 0)>)...
            );
        }

        template <typename Xs, typename Z>
        static constexpr auto apply(Xs&& xs, Z&& z) {
            constexpr std::size_t size = decltype(hana::length(xs))::value;
            constexpr std::size_t new_size = size == 0 ? 0 : (size * 2) - 1;
            return intersperse_helper(static_cast<Xs&&>(xs), static_cast<Z&&>(z),
                                      std::make_index_sequence<new_size>{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_INTERSPERSE_HPP

/* intersperse.hpp
MK4/Cca1Rn7xU8Z7Z7+ckGg93ei5+IZvhETbR+QT7x6MX9PdD4nm4T3BvPwsLBof63qn/EuD9XUT4mdfJp9Y8lTbxa8F/b+0ImjvD4P+vES/xes+4rn4bOtyJ/9J5YqHxz0Xv/yLkKi+KVG8wv478bgoPunBIVG+YH4u3rKf+Pi3eB6PPxfF7wTHzfeHpMf3u9sh0bw9Sbr40/fdXNSeMlF89CHbxa+lBMfHy0XxvmmieNE97S9e8pSwqNx7yC9e+lxR/PJqWDTvPcG6vzosGq+ekMhX5ROfeeSQ6Dhski5+PBjP1w4H9Y2GRMfjHeQX7/4tMf78dcHxfekh0bq4tRiv92L7ixdnBOP9A/nFWz892J4bErX7U2FR/+8kXXyJ19I78UfBvL05GK9nyyc+r0a6ePiVIdHx9BjbxUP/DNrzNc/Ft6WK4n0/mlg/onjRm+wvPu1monjo/vYT//4Zz8WbtkOi9jzDc/GbBWFR+88E6+5YML7lwXhnBMfNlaL46zHtFl94bTA/26L4weFg3LeCfnSL4pcvC9JfHxwH2YdE6Q3BOG6GRPPWEJS7bD+xoka6+IuysGgc7qh+seFr8ovVhdLFKwbtJz4+75BoHJ4in/iXYs/FP94jOM8+yXPx5esh0XGQYrv42rmQaJ22BPXdMWjvnCh+qlcUDw2rR2wpCInG5+Weiw2Tovjyv4ZE6VcG56Eq7RAvuU9I1K+d48Tj4Hzx2acG54/h4PgbDLa/OyzqV5YY329TFF/yIvWIj/p7MD4P9Fz89aXBvKZ7LnprWrROXxqMwx/Don7USo/ne8oh0fF3eVi0/l4bzHttcJ64nShe9MVgXTwkGNerbBc/dc+wqI6j9hN/ui3G92sI1l+TKB5+VXBejAbn4zuFRe2qPCTabzFxnTwkyjceXL++K4rvfGzQjreFRNv/LoqPyj8kWt93kS7+6ERwPDQG4xWs/99NBeeX3wXr7jHB+D06OA9dfEi0jh4jil/+WVjUzpgofmRDPvHjDwjm76/KFZ/5/GD73Q+J6v9EcN5qsl2svq0o3vTi4LwQnL8unfVcLLzykGgcg/ofMBKM15QofvPH8olf/nmwPRjvc7bv7P/esGjeU9UjfuH3wXngYYdE7b4xaOfNgvU2KYpvG7S/2PRxz8UPfioY5wcF15XUYP6XRPF3l9gm3rokOF93i2LLh5Qv3uuDwbp6lxjfPyin5Oai+OwvBPM9egtR+/OC468t6NfdbI/Xfz4sGofrQ6J8LwiL6ntGSJT/PsF8F4qiW2HRPK0H+z9Ne8QrXh0cFxPBfPxSeny/twbHz2e0S7wkVRQ/7jjcye81sajcYF7rgn68QozXExwvj4oG6+BHonjfN8gv3itHuviqy0XxtanBcXEHz8WbvhicR0bj0b73Q3zAI4N193BRvOi7wbh8ThT/eCIYx+PB9eOK4HjaCInmOWjHpz4fFvX/C9LFkksPifZ/uufxelLCovi0YNyC61lDcFx98H3BuAXj9PJ3BvPwNM/F83cO2vEr/RU/e99Dovht6eLj/xCc/+4uio9+XdDOR4VE83guLKrnBcF56qaQaJyD+6R3/jAsmq+f2y4+r9J28ZmXhkTr/bmi+P2L7S9e8sVgf/9OSm3xVXVHDzc3dDYfPXx9Q+u5ps6jh69p6zh6ONbcdPRwZyTkfw8O3e7ieGw2HjcPHT1aXxypzysoKi8sriwqq4u0nelsrz/X0XI0u7AwEh+WY0H+ruT8RdWR2rq6osKSwrJIXUfL2djRw7t1H2/qbG8729ikzsccrzqaXVzR6T/Hdkrbr3voYN11pSU1FcdKI7GOc52xtnOxRN1NpUH+sQN110Qqa4s=
*/