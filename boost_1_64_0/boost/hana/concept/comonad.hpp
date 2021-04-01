/*!
@file
Defines `boost::hana::Comonad`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_COMONAD_HPP
#define BOOST_HANA_CONCEPT_COMONAD_HPP

#include <boost/hana/fwd/concept/comonad.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/duplicate.hpp>
#include <boost/hana/extend.hpp>
#include <boost/hana/extract.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename W>
    struct Comonad
        : hana::integral_constant<bool,
            !is_default<extract_impl<typename tag_of<W>::type>>::value &&
                (!is_default<duplicate_impl<typename tag_of<W>::type>>::value ||
                 !is_default<extend_impl<typename tag_of<W>::type>>::value)
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_COMONAD_HPP

/* comonad.hpp
01bvCX7NpJMKvp8iSEQpFU/yxU6BQkDB4S9iV3aXd/yCmEOq6CylKZvKVoqjv2vb+T8fzNPYbhIzx9PAdgTLbiQfhXxQ2NS38YBSN8ogPLSM9cVT9dnLL4vi/1crHekaYDQYF2aebtd75ImXTs/cRFfKMjZ9I1RQsHxEX12mIK+TRybxQ7L8So98z0MYlrVzSnYVEVNqa7qnrzQ32K5ziEf5bGm3lhE8Vkooe5NL58nUMuVJLK561KJbUM8vNgtZ/sQHe3/FOsWgNVO4IRwtwi4vry5QvrvV1VzL0xM4RgvW78Hg2RqEG5R/CVQHY9u/HpR/syF72rsvfgbdQl6xiGZQZA61YhaN/IX4BcUI4djSmdL7H6R5XjVssbnhRwVF2xzOl70QCzg29OiLSWJ+Pi+L+GhxrrbIGWW2LMkaS7grlpWXo9L3T7esrxji3Xpf2RxoFJ9Sj1qcE5xAJFrsMF1+4EV3AOF0BXdm2lnTJnr5AIO28PZYq6lk8PPozfp8AMlcz7T9AinkS0quhcNEgs69DNU54YDmalYvg6f9ixT/ZaQsP8IrluZgMg==
*/