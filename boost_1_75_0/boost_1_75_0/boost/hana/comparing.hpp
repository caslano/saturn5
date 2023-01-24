/*!
@file
Defines `boost::hana::comparing`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_COMPARING_HPP
#define BOOST_HANA_COMPARING_HPP

#include <boost/hana/fwd/comparing.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/equal.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    namespace detail {
        template <typename F>
        struct equal_by {
            F f;

            template <typename X, typename Y>
            constexpr auto operator()(X&& x, Y&& y) const&
            { return hana::equal(f(static_cast<X&&>(x)), f(static_cast<Y&&>(y))); }

            template <typename X, typename Y>
            constexpr auto operator()(X&& x, Y&& y) &
            { return hana::equal(f(static_cast<X&&>(x)), f(static_cast<Y&&>(y))); }
        };
    }

    //! @cond
    template <typename F>
    constexpr auto comparing_t::operator()(F&& f) const {
        return detail::equal_by<typename detail::decay<F>::type>{static_cast<F&&>(f)};
    }
    //! @endcond
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_COMPARING_HPP

/* comparing.hpp
2ha6SmWWJBzcbDacc35vxgucxj8Kxz6NOVsReAeo9bnozUHdiD+3gr3mbPh4J/02efzzrZ47+ULGoK+HxbKT0tqKmMOyBa6/l8EkJa+u4tNc8ByJFq9FW/VZQ3TzV5ozCl3aszOKDfioqp/03JGZw7Un+DFJ0EqiSGIq19RSAYC5Qvn7droxvcGXx9Z4gssvc8FrxeLO0hfy1piFFVLOc/aNWvwxmJI1nu9jGu5zFSuBlXHl5Gnw3Xf5JNXrWjsheXSRpJlRSBrjG3ztTGlxvK8hcnvjE2dxIcCMlgYkl2WyJn1/k1fU2kYJbsgczg9+6Zod5PeWqaWmTphCTAOu6Ymfwoib9Q6oOoNBf068QZF+++7PkZlX7OHJECfsP3OmH7FhOTRUXub9XPToFVB7tyw6IBRI+55LG8mlPN15TgVt+uR2X2hr3NtujTSi2cMq2EDYp1nEz9UoRYyWwu4MtXRpinxWy+NRtMQ+9Tu5MZn0dszYbXiPMWtJDYGwJa46cEO4gpJi6ipLOYfHu6WC63mmNZXszitP2O6RQ6PcI96U42mjEGpSa6ZJlN4g4KiScyGE91NrxTTGNvWT92wLJ0BLTI1pkoyN/ajTJT17+3LU11GGuvwPeWjle000R22Smxqzi+E5Tlmhybsi5Hsks5vt7d/sulNsn73PW4Xz2bo+jeWx68bdpp0Vjmve14x0nr9DtFnylk6AF48q
*/