/*!
@file
Defines `boost::hana::replace_if`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REPLACE_IF_HPP
#define BOOST_HANA_REPLACE_IF_HPP

#include <boost/hana/fwd/replace_if.hpp>

#include <boost/hana/adjust_if.hpp>
#include <boost/hana/concept/functor.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/always.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pred, typename Value>
    constexpr auto replace_if_t::operator()(Xs&& xs, Pred&& pred, Value&& value) const {
        using S = typename hana::tag_of<Xs>::type;
        using ReplaceIf = BOOST_HANA_DISPATCH_IF(replace_if_impl<S>,
            hana::Functor<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Functor<S>::value,
        "hana::replace_if(xs, pred, value) requires 'xs' to be a Functor");
    #endif

        return ReplaceIf::apply(static_cast<Xs&&>(xs),
                                static_cast<Pred&&>(pred),
                                static_cast<Value&&>(value));
    }
    //! @endcond

    template <typename Fun, bool condition>
    struct replace_if_impl<Fun, when<condition>> : default_ {
        template <typename Xs, typename Pred, typename Value>
        static constexpr auto apply(Xs&& xs, Pred&& pred, Value&& v) {
            return hana::adjust_if(static_cast<Xs&&>(xs),
                static_cast<Pred&&>(pred),
                hana::always(static_cast<Value&&>(v))
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REPLACE_IF_HPP

/* replace_if.hpp
oxi1QTS2LG0f7WO8fy70I3DYAKhOUNuGtHyuPZvyuKsWypSt7hk/4XJbnOdldQlmuFayNz5+8end7cn2GegmFKJVrKJuKvtGtqq1kH3PwKUHaY8hLhulhalc6qJ0zslxn3gx7tfwoU6vTuWvn1Jejnl3OF3XyfYNAy6j3jeVu/g1I/9z03Sm6Bzq4fKS6+nM+TOtbwlqKx1IbmwEtbJwDt9iP5nLabzuJUzeLtybAcE44NjdBXRj8HMGJpUtaLQB+2S+J+u60qrrS+afKO6W1CZrG7uwfYJZqT82EU+Q4jq7jI9mtTDetbgnfGLnZ1hgLKezlMdx0PgWDRcl7JHTLWMPYz5+crSGQE2hYEHmcsq/33eeTnkc63hZSjhHGBAmb4Rpfc/L6oP13wmQaUTUi3QnEnb1eQC83HrIeoSJzfWeb876p4RteFVLXx88vI8wdN836p+qWlHXpaD1UdRSWiHegUY8Ot0Lx7UcjxH1Lp3kbYbNOcMULLuyrYRmpzeJHIRzktJyb5sstVPd6NknRKSbWynGNs3qbIuy6mqnYc3PqfMIpS072AdB8uOVHlXKi7zCGR9Hl7VdeP/eQvKWj8aKIOOC8veh+/7E8XZHmS3fHuV1tNcC1kEpmfdcSvVi7KTfFEmeAFF++mS9gW+Co3Y1QjeFVDzJtZ4pOuxjGLFFhBD1lSEGdDZWFetsW6qyb8KZT4cnxrIf4xt/LPsuspV1VUjB9h65DfvL6Lt8btTuuoFBUK3XLe+sTmWXIyghQMdxnwIMW9wXKZ+lyuqq5J0e5CYYeMQJunuag5/OfRh8HNiG2+mcj+aQKDkR//3DtOxFSha60U3LAN0Xg/JP7ZA+PcJcUqUtK46xt+KEQcPmuwp5ggaSo+8v98/qrVwFDa4b5itFQQTfm7N6DXOlaBvRWEYQZv6tGELqfXr27tO3fd8Z0bDh0Ij7EZ7h2bgKJiTnuuAme1+CeUeEjXN4LmdlHWtr2bcgbeI3AUGNzgOq+h/byX4t/0al040rSy8r+jK53HEhq5d7zKi2aZKuHibAbEV7OO9o2bs1poU1Z+K8w5qIj9DlPzPC5K1KyatGkD7Or5PEq3hE0I1aJ3sfAXfig6FugsYb73h//uqgC15dCZiltmwkP0nugI8N5UMeXF1kJUNwjWn+E6f50IZzK/tbOxApc5r/7O/hHbEwlQ2ljxCfyBd8j+qXQy6WfeU0Dw6mjbUQrYTgSb6O8D4JYKvlfU7KCLeItp9vmkMTakFP2Cn25NsOpPXn4PRu+p7vUX3yDK4k9u0TgQ7WDYTRKrpcd/65LA/Gjoz5V1LeIikIuuRU9luYj4XxPf37Ma8VipZG/NWfknwsTXTZfyU6d/96HPofejfVGbzvRXBvj+dLvJQi3uwC6gxC3mkfb9ZDTyyQ/l2W0gT+QEju/lfGfKKKwnZM7VqvMZcOvxfSXe8AupVB3bGAGK0H0IFT50MiLc6VWx5Ae5eg6lhYS3S3P7CN3k1vgm08ciDdzhKcx0h3/EC6oHvDtXEPQoeWxZOAj/owxCslNHHhruxcFOBxH5bqq+fSwL4ayKZj3M+hA6/ys6GXhO7kv/22U9uwv36Z0EUrbJglmP9Aygf2BZ9J59iDv0/3PYBcXtzf2iD5Z7J8yFsEGpK/OZPvoepx34JFSur3S4ysgd05fUw0qfx5SgNeKatkT348fZ+D/LHNzJW/gm99WT6uwedcgurdJn73nKzs3GWRtPHiF45odgIRzPTpW+dLn3sQDRmH13qaoPqLKANTH00X9glwuAyqwYVdxEnMzjXJai096mmd3iHgRKOPEYjbh/6KWfmCCVmXXIkCfOWDGD0o69ZAMOblGJM=
*/