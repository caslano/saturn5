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
cv94DT3r4PXbkVZeXlhaJffeSf3w0SuOHm5suqbhXKsnTve7ZXQkxjcjuYwriiuLi8ujrt8715f9KvfvnXOS8+vesYqamqKKwmM7ddrn/1Wc6Ge4KJTUz+ryopri6sK6+H3K3hJuS8xpmrxJc+pCVOFFhdxXuUNpiJ3rMKTtDR0Ol5gzr7OgY+foQ6/XlL0OHE5cI8qT21/jcCiprSkpjch5pqm+/dzVurD3uihR/0n77NdfEakrKyyuLi8pi5TG9wpOxJV23DlH7N5WOO80BqdnZe3X3/OsA9eossLq0prC2rLIWQde/cHrWltizAcO1G/Mq2urKsuj5e5hXIivazobU9G5jg4PDi40F9v42krM9cyBua7wyjJaXOQYbrVr/IXAhfdqC8n5o7WRoqK6YyWl0eLd10mWrxdKQe/bO9qaW65u8QLN2cMcKHB/rrtvODDXpccKy4sriiNXNzSa7t1K9++le5LrLIuUVxdVm+2aSHFbR8e5dh1sbdi5eTmvf+7hD3Q46f7w8suT6swrrqmrKVJrJDG2scT1fKXr4PXcQetA9yqj8Ox543euvb2tQ68s5ZZr3RPuXe8ellhPPcnHg3uuYveh1W64z10dH9L6+LsE9W2tjYnjKHGvdrrngjVVXFFXVlJcsnettcsVnbHzrXoZf31fHRW8wnfD2nkuvsoVHG9Ioh19B9rhvFdSWVNUUl4Y2c1/YTsqEu0YOtCOY5HKaGFRzbGiqv/bjqCD8YYk3682lyXPdZUzYEl5XWmk6ey1LWebLngd3i5v8uvSyrKykpri2shjOlUW7OFu1av9zparW01HQ7y2jsYbGhzxbhXvGpTjrTfl1Ne3XNde3xBra7GpJJGWE95Pq4+1XNf0sPzQPaR5u9p3VuLvLdXWldRcdVVVfedT69272RxJpNdcmL7zZo+fzgvST/zb/k03KKO11TwnynjChXmu6Whq8toxUcbpC9Pb29p38+yXcc2/5TnX2ez8lEhvPZge62g9034+Kf3sty9Md7BIv2uQfuPO/sXHH193ojaou+FOQdrkTlpRRZDQlNg+v7fd+a5zv6ylA/nrnSFCDYm0B+7vE19c19i0l9avjdJq6l0Q629o62hMasNdF3fTgrZ1JLZ/fXl3+25xoY5Ef9+1U1bhVTWX1dcWuT0/EbQ9kZ67uJdeUXOipKzkeHzm9tMv//f0eAF76+bKnfSWyxvqk/OEQok5PZZob6ztYA5zmshT9+91yF1UE0qa99ss7eU54W2i3W5alokxy9lJ18X6sy2Nl3eejU91Ii1/Ly3WFbu87eqnJKWdWkyk7b6OS97vETv7lTy2rr46Wh87394kLTHed/peIq2zueGyUHtin56fJLbXVZY8vr6l0T6JPrziYNq1TbG8+uNXFe6N5Xd/8e/pUemJsiNLyem783C/IK30YNqZtvbz9Xv3AZ2haxNlPOGH8Xxq3S3eJT5Un0j75XI8LXogLdG2p++MU/wFSP1VJ2qPl+ysEusykd5zQXri2Em07wffuSA9/qLyetf4a87Xn7k6dO29E/P4vQvyFZ84GdRVn8jz4P+UJ15fUp78/5Sn5WxLTJ4HBnlWfvEf2hTcphm8WHNn6Gii/avf+Q/lXSt/U0dHW0co9uAg30tX/1c+pbfHmmVrT+QfXfwv+XdvYkSXdPkT7fjZL/49v3Yn8sUS+db/W75rWhuu7QzFHpho748S+RKzoaCgtU6PjrJr99bnk5f28h4veXSQP7R/Hvz9fp3x98v21u3W/vbdOwen8UTa9Uu754/G+p30q1va9tP+sb/fGZcsV6z9885z9tviXJFo0/55K/zLA+XWPabIYbF3ntfvg32Jr54=
*/