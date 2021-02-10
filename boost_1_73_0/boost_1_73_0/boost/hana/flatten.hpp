/*!
@file
Defines `boost::hana::flatten`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FLATTEN_HPP
#define BOOST_HANA_FLATTEN_HPP

#include <boost/hana/fwd/flatten.hpp>

#include <boost/hana/concept/monad.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/detail/unpack_flatten.hpp>
#include <boost/hana/functional/id.hpp>
#include <boost/hana/fwd/chain.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto flatten_t::operator()(Xs&& xs) const {
        using M = typename hana::tag_of<Xs>::type;
        using Flatten = BOOST_HANA_DISPATCH_IF(flatten_impl<M>,
            hana::Monad<M>::value
        );

#ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Monad<M>::value,
        "hana::flatten(xs) requires 'xs' to be a Monad");
#endif

        return Flatten::apply(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename M, bool condition>
    struct flatten_impl<M, when<condition>> : default_ {
        template <typename Xs>
        static constexpr auto apply(Xs&& xs)
        { return hana::chain(static_cast<Xs&&>(xs), hana::id); }
    };

    template <typename S>
    struct flatten_impl<S, when<Sequence<S>::value>> {
        template <typename Xs>
        static constexpr auto apply(Xs&& xs) {
            return detail::unpack_flatten(static_cast<Xs&&>(xs), hana::make<S>);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FLATTEN_HPP

/* flatten.hpp
IDTYFIH5gaFuEuz6JxkMeL28+Uc0mwV784T/TdKb/cOjH/98/OOf31grAYeB2HRgmnc8GXDgU8TB9QMbVKwlgC+0gDWb80s+a/pItlopfoEmC39DVdJBQA1dgLkiwlcAkrxAvfJsUdjA80WePrdCDOhaE0m1G8UZTD9uH4n3HN8/N4jRuhpcULAdf+XzfE98gFcrhR54O/h3QwcomFtOIZBhh/5+DedDlGc14cZOT+tqydFvJpMjOm2/dzVCpeKyfdkbfOQzD3y4+4aDDERghBERIXCPw895jTHEv3ff4PAb1BY2MwYRS+Og3eF7tfWgYkXz1ILVk4dWFAww7H2U3xr7AkfFgAJB5JZbCQlrZFZaewgxQ80QNImGh+SNeVUmHFrDsgOZGR9yLM5UvMRYT1JEJDTRZhzEuGdMOP6LtRcKXJklGe0Wjhnm6BcclM9Q5ARjpJEII+RIox38DZ6usdfQn9Z7v3f6n+3WyG9dNEF1URTZpLFLjWmwVjoOUGitXHLOICVijff+6Wmvd+GNP5Hm/RqfSE3ReMlHd3qrzt5WWAtGs2S/AFuglWMM8o2mBp9SxC2eiLzvfpOhNfjcH8e5VHUV5UHcoQb+Gk7pYlQ4+L8I5iN9uEmhIqfNs/PORZtevzJfw8v+oHd6
*/