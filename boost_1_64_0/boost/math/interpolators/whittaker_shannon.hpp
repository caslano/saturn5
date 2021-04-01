// Copyright Nick Thompson, 2019
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_MATH_INTERPOLATORS_WHITAKKER_SHANNON_HPP
#define BOOST_MATH_INTERPOLATORS_WHITAKKER_SHANNON_HPP
#include <memory>
#include <boost/math/interpolators/detail/whittaker_shannon_detail.hpp>

namespace boost { namespace math { namespace interpolators {

template<class RandomAccessContainer>
class whittaker_shannon {
public:

    using Real = typename RandomAccessContainer::value_type;
    whittaker_shannon(RandomAccessContainer&& y, Real const & t0, Real const & h)
     : m_impl(std::make_shared<detail::whittaker_shannon_detail<RandomAccessContainer>>(std::move(y), t0, h))
    {}

    inline Real operator()(Real t) const
    {
        return m_impl->operator()(t);
    }

    inline Real prime(Real t) const
    {
        return m_impl->prime(t);
    }

    inline Real operator[](size_t i) const
    {
        return m_impl->operator[](i);
    }

    RandomAccessContainer&& return_data()
    {
        return m_impl->return_data();
    }


private:
    std::shared_ptr<detail::whittaker_shannon_detail<RandomAccessContainer>> m_impl;
};
}}}
#endif

/* whittaker_shannon.hpp
EI6rgVbl7VatSoZC32LWGkEugXoEZKuOP2kaUJrlW1uIXluG1cj2b75/3ceFsayVUgS9FJ+Bxu/5QQsAAtxe+kUZYu45n5XKZO5eg7QmRZSzpTkpTJqWhXjvbEV+qydd7B79GPXRnlv/gLeMgWCHiXMdLNEAN6MRkZpKx+a8DAd7qVVY3zkE8qP8LAgpzkvu1lhKHujYOU64TeUZ8p+AMlv8zo97kWRYktWDZPAi0q8bZ9hnD+VYQFZJ2EZ6FEmXEzlwFGM71YvJQhtKkAxAKew6Ht8iS0CcTVoCaePhLgEJzSmm9FMjrlgQuDCT/O5H86bWtDvNknpquBgs/6BT8duhsU0nEgHZ3DIJSBiabM+Q7dKge5LQ+cAPAEdjn+VaqJ/du4CHNl+Gq7p8Fd6S8ibeA6Z3QjMbyeeU5LO34fypK5pNvyCNUham8HFwh+KCr6AjGrEhFbhLNL2QEDZelMV6n4ecqqGiQGaoiOjLwsepAmA4ezCwLATGJFR2IUpn1hwICvh+Haosu5TFEfz70OhbssZglx0w1YGQIGl5jxjm2MYpMejugognVg==
*/