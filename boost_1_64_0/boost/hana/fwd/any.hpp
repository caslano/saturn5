/*!
@file
Forward declares `boost::hana::any`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ANY_HPP
#define BOOST_HANA_FWD_ANY_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether any key of the structure is true-valued.
    //! @ingroup group-Searchable
    //!
    //! The keys of the structure must be `Logical`s. If the structure is not
    //! finite, a true-valued key must appear at a finite "index" in order for
    //! this method to finish.
    //!
    //!
    //! Example
    //! -------
    //! @include example/any.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto any = [](auto&& xs) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct any_impl : any_impl<S, when<true>> { };

    struct any_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;
    };

    constexpr any_t any{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ANY_HPP

/* any.hpp
Yd+w7ZQryNo4/uFhwv5kzPljoxHQhgLa4HnFYWkIjupvPfRtTHqttrzpa/grF7W4KH0ZPFtBZcxOBZA5+JmlzWj44OBY2A1RE+8u1VjJicnFWblZ/k4LjlpKiwiJ9Q3ztqMO26ljuX1T+KH4Px0vC83SQBU3/qNG1xA5gVN3vOnFK8T5Ft4P5V2qjOR7LAV5oiG2GsTWtRLrPueQTyiT6qRrCIem2bN5ILbjkDjeXe5R76JOyBUfSMemz9gqriMaLqr0gzmzEBlygmFXMfkPfRm9YL43SVn+QaAsj7fKWcomCw7kIRy1gx8OlW+fgg6oEDn3BI+lBcY1ShfMWS7XbwOEOTly/c/4d6pc/wP8ZRGWQiezsDYYv1Esb2/Pf1++8/Xu4hdixc/hL9kPZ+I487Hmw8jOl+5+5HJw0e0/1V/28+XOe3UN0Ak01k/THHdvfd9gCza/dU3zVaEFmdFsI36NLgktsEWHhxZYo9bQAks0PbRAippC5vnBY+ny7XOwH0eHAERam5lrunbOBdMCk4vz399UAtyUZ8DTc4V9Eow9FLmDGwsvMBbPydtwMP8Z/yQx8MCwYmdz/vtgQfku0mtOjj9zzlS/rR6q588BkuZH5jt3gih3tRQ73woXY40v0ZBosMjH8t30YrgiHdDQ3W70tAskYkd4bcHroyAIyRLq7MLpz1qSbxW0qPk+HkiHTd/EAMZjPAHL5w7YhvHQHTxmCWTAK75fymkJr24wzA+2moLHBtd8AxvIGPnnjA3zGcrVadmCiaglVwAd2lJ6jGXVluXvGWxX48eHn+vxE8DPzfjZhJ9d/8VJP5/+xcP7RxwWDmkaBTeXhqeCZ3nfFKXD+9IVVPKOL+dxjVsfT2s5zKVC48eeeN7iJBMadwpqMTzYuQQQgJ7sLq9Q77SLavmt/s/Q/ycOYVk8U7jDUr6rQl2DcnrIWgN/i1riGwiUEfZUrl5ZkHAws5sTOP72SjwPf9nD8/CF13afh8f4stgBrQoBDGXNRf0dhpsvST4MH8axjRrZkEtO5jCckB9r3NTfCSqT2kt8oE7NRejhNUb1S9fElBCMF3wHcq8gjtRCmoUWQo07hib1bV1a4gw8dWKMgv5JOO+RvuNyOsyddHniMIwK1niFwGswM73l8wm4Qrk2w0HKLp9YUf1JdXgYfdyk7xvXJNsbLmQftDe06LhbL+yPxJVlyST+HrZ6kviHrpMhsc7PcoXQZqnKpjmbySdwcE3SugCpc0ggPzhb2nSuq4ybiEsdC0ucrhKermQ6lCdBKamOeNYGd4N864euHRQ8qq1PU3YQDg6PH8l2viHxQA61RRKAe9Zl9LBvyD2XuDhs9W32zX0nqT0LEvGoTycq9IU/PL0f+LRf4hxucSs3SPBB1f2NytAk/srv8NuczQ2Hq+S7GChIsRq5pEx9eCrJS1XYdGRvXxv+AS/K+9D359CAY4wpkRw+ExRwEvNp8z+TmByvKTHeGwib4x2g/BXzQPQ2xem9UepDb1MPelf2rtBk5XgfuyT5fGKhG0bYSITpfTtJAqWCJt8tpZuXzrDID+ywICZLeTKjPfB2E4tzWkkgq7nV5VFNuWTOmBSDBn8vmBXPJ8DcPcc7nLzBdgPw332DPppedX3Ku+2/XIkUTpg+/nWp7yE7tgN+n4+8pkte8y/DPNcdpc1pvR2Te0xbP4acceTF4HOGIy+ESqSQTehZnOiGPYGsuqPkhoCNlUI2lIfnG1nmHUzrlu1KGG/2C6dEDGg24OtwR7BJT4BeW6LRX5DFlhQvPy2KiZfgJ9gh+pMnj7mEPko3i2XdJO8fDT16fQW/6P+I97qC3XI3zYLDyVIZy3DLnmbPKnk=
*/