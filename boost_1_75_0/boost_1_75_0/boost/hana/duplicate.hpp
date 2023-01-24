/*!
@file
Defines `boost::hana::duplicate`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DUPLICATE_HPP
#define BOOST_HANA_DUPLICATE_HPP

#include <boost/hana/fwd/duplicate.hpp>

#include <boost/hana/concept/comonad.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/extend.hpp>
#include <boost/hana/functional/id.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename W_>
    constexpr decltype(auto) duplicate_t::operator()(W_&& w) const {
        using W = typename hana::tag_of<W_>::type;
        using Duplicate = BOOST_HANA_DISPATCH_IF(duplicate_impl<W>,
            hana::Comonad<W>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Comonad<W>::value,
        "hana::duplicate(w) requires 'w' to be a Comonad");
    #endif

        return Duplicate::apply(static_cast<W_&&>(w));
    }
    //! @endcond

    template <typename W, bool condition>
    struct duplicate_impl<W, when<condition>> : default_ {
        template <typename X>
        static constexpr decltype(auto) apply(X&& x)
        { return hana::extend(static_cast<X&&>(x), hana::id); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DUPLICATE_HPP

/* duplicate.hpp
KLlDwq4ToJ2ry0K3S9w0CaK5WExZQkm+yh1R0IBBn44W1zqt/1JqNgjfpy9UW9UnGGTeB6bYBJf0Tpl+1J1QejZXHHNJclDy40orf4pCIGgCakjht7fb3TF9d1HgF81mjKfkmo3ELuIBDgllpIRb/t30ZAGoF3SyLng87i/NL6NOmfzStaAs5+fCiAtLWxHrNXgB8WV00DmaYwFpiT4TaxlJZhnRfKHyGptBhMSA6ZZrnY4zSdZAoJWMRcZnTuFZ0MUL3qEngoSitKjz+r9OUWx6Kt159nK/PaecY1T04+Yl1cB85OpSnIs2VPtlntr796od5gCl72xNotFigSEgRZSSTJgMLCjWVZferyfsumrGy+eCAHevL60xetNEj00SYjpu15fhNpnlJGsqtwMAhtXDYkTGTmAm0oatez35pjh7bPvQL2ei+x/EObh+3nbi+NCeJzE/Nr5Cmf41j3yzi9lirZJum25jRMhrfui3WGC2GGe35bDS8uiYpclvsZexyXqXNSQ7G6bneb70hpa7ricXkGQ/zDIRNOGIEubmV/E+STDmwest+jpNZzlC4EqWVmw13WrEfSVGDa7P5PF90ueHvxKp/DFq3okKlIN8aj50RsLHk2Ky9PBUyhf5bOGgs/0MpLYppOBB+Plg8b7zpP3jHiiA/o5f1+771A9x9IDcuS9be2o57N1yh3+pkytr6KeTz2HHChVX+fr3
*/