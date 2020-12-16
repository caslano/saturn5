/*!
@file
Forward declares `boost::hana::find_if`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FIND_IF_HPP
#define BOOST_HANA_FWD_FIND_IF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Finds the value associated to the first key satisfying a predicate.
    //! @ingroup group-Searchable
    //!
    //! Given a `Searchable` structure `xs` and a predicate `pred`,
    //! `find_if(xs, pred)` returns `just` the first element whose key
    //! satisfies the predicate, or `nothing` if there is no such element.
    //!
    //!
    //! @param xs
    //! The structure to be searched.
    //!
    //! @param predicate
    //! A function called as `predicate(k)`, where `k` is a key of the
    //! structure, and returning whether `k` is the key of the element
    //! being searched for. In the current version of the library, the
    //! predicate has to return an `IntegralConstant` holding a value
    //! that can be converted to `bool`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/find_if.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto find_if = [](auto&& xs, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct find_if_impl : find_if_impl<S, when<true>> { };

    struct find_if_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr find_if_t find_if{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FIND_IF_HPP

/* find_if.hpp
OV7lpa+ru/qIAOrL/eAb6btIFDVeeqq/onpaUNTTelEbaH7S/uFVDl6pzirlV5vFF7pyvYDredJvkzNLJfhHmT2vw5JA91QibJtwuYJO5Ejepk7PadLB5PRpSL+Y0r+sp1+hNbqmRW10g9pqvHluskP6bnJeduQ1ivL6nt6wW+P60KRlV39a0bZ/2E9ZXSfQOhdhDfqT1a725gTfpQnNt6D5o9djfU8Q/dgkbRINH7Jeg+kDt1qHn9OA4jHVvlZD6u3rr0Wnk64s3Py63YNvvl5GMnh0Tp5Ky2utE9GK8eX12UFaw/KUgxai1QRz8oPZJUftrTTZ5DngUIHHEw2eL0M1rSvHS4cvM7aynS/bDUYogQc+gZcj/zVjMBvK6GVXjtmVCfkmp9Lu1W9VNI+oUw7JAsxF7Rvu5zreif/GYM5FwezAzk4X350oqbesmUl0PcEvqeV8Vsblg6o+oOWz8hr/lXwxHvHNz5g7w/gO4zv/Nb8XGa3tQIP01myagJnNTUD9WD4IovQmakN9tnoH1BwRl9DoW/8ieDS3T+5kD4ogd+BN5B28itr/uZe5WBN/y1sBC6AKm3XzyDfxiP6VoO8qGtE3CCQUtfvsNdQVym9bhPFYDGxt42a5HnYfoMzUZS15zT73NbMLt/7qlGMv2Q1EG6ORrEcvXFRvQ1p0mr8y/6i5GwIZfc1utwwv0qC7zKm8PUc3ItF8Bh9jMxmfAnVv5Qi/rdMl7jvU27pvp1RsY4E+qCsPyBF20+69meiJ3jrK8t45uv5rNcuOsMiyZ+Uw/5PmV0tO+HeY384/0f0kpvTc9+bjAiZygZjc6TTaIBNLc7sHlyrF/IPazvW7Qf/Z6Z7HxIBNx6K6juqB1+OPMUEJM2Xp82xYSM6djTVWFHXTLQ9lxnpW0EBnlM3yHBv4v9fIHtxFM3scGnsUfhdx+SU71p6x0ebYMHTGulJHut9WVuKyrXmDcLbudJaOLAM/ePdFLpu5z+hy5CsowEHm6zBF7pc7d5oNYtZGJ9ISUQfv0tmx1ZRFh2rFu4F7GtGxpsb4zwwHbTIyUoexy4uFM9CSOM3TX/TfjZhMfI+L+i/TIy/P9bZWRvnMGupbtWIJJDDdnSyB6cSLq6krwgccEa9sA+/m0PKsVRSTvwjGoqCvGuRkF+xym99ttZw1fd2kdLotWvmM/H7Jc2ve0mIjIWl3l2c4ieoxDYVrdF/g6s+2iD50xGLbuvfROiuZGvyENBKxpS0A6F7lz5v0pYL7p7S1jdYCyT7Vj28WMkn1VoKreWpbEIIxUBa9wKc1brheENapvIA53DmhSbDqK0PJ5JOkrpaWbPcZ8jD67k6FH3AmPNmAefJSK0Idt7xvQPbBUSXDcCVxklaNWmU61VGhOr7lL6d1OoXjeUpcFn+NNCUW8exYYwKlJUutMB1SpoXWKX+4idsihYQXUyhvxl42Za0gfKgwE7V3EADa4R8nVWpR3cp3kJpo/9QbS62JgxpORSNwWWk9CS1Ls2KJlolETkqEfugM12eqE6BBnQHcaaHVBBlXk/SqvZYF80mGlZ666HKnYl5P861PmcvYRo7e1WLoK5CM7IbZbz96XGRwC9NkrOQZLMWWJ3YVN2X1lFtkZeGsHNjrbn8RqcQuR2krY2mbn6DZpNaTP0XVuU43hgS5uk/UhQCGD0aLfIFaJShpYmcgc0OhOfn5ND97y2KUVxTVGtG42fKEyXEenjCehTtNji488/F9Id4X430Yz+14rsVjSDem889ktqSk/2N+qYnONCv9H7L3/z/8PL6LeWZj1YyWY/aSLvVNYG+J1mVnKv1XWgG0edpb2eZHMUfwKPVLdZsfvklxiVwWTuU=
*/