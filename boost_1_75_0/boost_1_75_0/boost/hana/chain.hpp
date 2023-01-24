/*!
@file
Defines `boost::hana::chain`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CHAIN_HPP
#define BOOST_HANA_CHAIN_HPP

#include <boost/hana/fwd/chain.hpp>

#include <boost/hana/concept/monad.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/flatten.hpp>
#include <boost/hana/transform.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename F>
    constexpr decltype(auto) chain_t::operator()(Xs&& xs, F&& f) const {
        using M = typename hana::tag_of<Xs>::type;
        using Chain = BOOST_HANA_DISPATCH_IF(chain_impl<M>,
            hana::Monad<M>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Monad<M>::value,
        "hana::chain(xs, f) requires 'xs' to be a Monad");
    #endif

        return Chain::apply(static_cast<Xs&&>(xs), static_cast<F&&>(f));
    }
    //! @endcond

    template <typename M, bool condition>
    struct chain_impl<M, when<condition>> : default_ {
        template <typename Xs, typename F>
        static constexpr auto apply(Xs&& xs, F&& f) {
            return hana::flatten(hana::transform(static_cast<Xs&&>(xs),
                                                 static_cast<F&&>(f)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CHAIN_HPP

/* chain.hpp
XBJvO4li5SZ/bo5oRs35lKzpvt2NP42+jGaFIYmkLIphJGCEZ8RpRGUkso20zSzKuP1p+92VAxmfIdH5RgDxJ9w/jv0NGoFIn4vB0D5plieRkHtmUdJpjIc/51I5kl5ib2tH+6DDGm4mYAj9GN1+d7AbtS3MO913UfGzxiLZMdnkihNnJpU7vvufDwFt01fr52LdQ8ICu467hRf730XI/Q5W5hQZOpPqs/PkjD2In6ZCfa0w/O6Ta4eb+zod8LIueZovWiW4hpteZvxZM4dP+wUhTRuOuWtUY3gF1PFjG9I8+xZ9V2e/pm+kMXKapZV0ftPXvnsy0Kj7kgtGjwk2Gps6uHVJh8y2djNymsp6KV+U7FjJnj+NVwEZJ1aLYN7kIphyeG+f85MhKVS7KQAry6Y08x/B/mt4oo9p+7j7VdTPafghXBeRKpfYKd7AjGkY9dINK3u8+w89QYe+t87atmqkf+Iu7p+p3DDFWV2Pd8+xlPDqPo0WNHa8++7g/cmu7Zcoab0eOfGyyLR/1ZobVwFogt+lW2BPt7+/Od3abf1TY732zyYzg+aJcQPgn8OucU+NfhgAeas60+/WqXlMMQ5crfYdXUowzj7VGiX0+s5NTOXQmmZabhOmvxiNTGTzBHfGakts8QuLoO6GuW86/BRsxoJDzxLE139OfdtMVbWauSEKmn57s+4yRnZ09WIsd0y+w1g5PasRF/PR
*/