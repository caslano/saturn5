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
mQO4Zz7KGntDe2dR4I7PRx8YbuFTjWo8Lp9N/tJ8lLdlA5YqrcNeKvmIKKdClv1nPbsH7s3Byzs1F+vUZ28LszmDKUdgrqQn5sBK6fbAFY6fwS1A+aufkV+jZnrfTNSp5mJ7eYaYd9XoS+W+eUKegQMcdjqlMR+Az58DWk1PyxGIjWNOhM51d6okB9ubOZCmYS7ateM47yexpOP+E8WdYX3e/D3HcfdDwE8mMTlwRmWzOeh2u8jh8LD0EcmYl6v/pqKbZ+k8mpUzDTSMj6fZYX7ROkpLcTrFcTYl5JH5CVwWxHst9uvkrftpfRlDAxY1D2N57QEKo/qcuaLYwy8gAFeTBFzsSlYXGWHgykahTzObBOvRJLluCDjEBYyfiD3T5O2ib7w+AcBVMXlWn40KwAsasAwEiCF/S6ca3hqN5GM1FeNeeYvTxu/LIp1uNuTwd79jUuH99ESU9dh9GjefHCwN24O8vFPjxu1yThmxnHZi7VauHdKmTrQtuBu7cxJkYfcW+T0W5DnF5PTzN0mJEcNQnQQ9rlQjyvFdOROLKOIsVSvAG1Ov75BG8AbSXFqAvk3fA+OWL4HRiLiHh1Woa/17XFb4DvSAK1RhDXzgCcz9Yg0OmK0lVsrLwAWzvf1VHOdzeWW4I7Oxv1SWMJxwwmflLUCefuUMLrt/AFwi7FaK779mOLbb4PD6SYCnTGfwhdynDfCEVMgy5Z8M
*/