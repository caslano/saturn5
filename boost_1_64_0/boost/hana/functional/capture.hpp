/*!
@file
Defines `boost::hana::capture`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_CAPTURE_HPP
#define BOOST_HANA_FUNCTIONAL_CAPTURE_HPP

#include <boost/hana/basic_tuple.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/functional/partial.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! Create a function capturing the given variables.
    //!
    //! Given 0 or more variables, `capture` creates a closure that can be
    //! used to partially apply a function. This is very similar to `partial`,
    //! except that `capture` allows the partially applied function to be
    //! specified later. Specifically, `capture(vars...)` is a function object
    //! taking a function `f` and returning `f` partially applied to `vars...`.
    //! In other words,
    //! @code
    //!     capture(vars...)(f)(args...) == f(vars..., args...)
    //! @endcode
    //!
    //! @note
    //! The arity of `f` must match the total number of arguments passed to
    //! it, i.e. `sizeof...(vars) + sizeof...(args)`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/functional/capture.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto capture = [](auto&& ...variables) {
        return [perfect-capture](auto&& f) {
            return [perfect-capture](auto&& ...args) -> decltype(auto) {
                return forwarded(f)(forwarded(variables)..., forwarded(args)...);
            };
        };
    };
#else
    namespace detail {
        template <typename F, typename Closure, std::size_t ...i>
        constexpr auto apply_capture(F&& f, Closure&& closure, std::index_sequence<i...>) {
            return hana::partial(static_cast<F&&>(f),
                hana::at_c<i>(static_cast<Closure&&>(closure).storage_)...
            );
        }
    }

    template <typename ...X>
    struct capture_t;

    struct make_capture_t {
        struct secret { };
        template <typename ...X>
        constexpr capture_t<typename detail::decay<X>::type...>
        operator()(X&& ...x) const {
            return {secret{}, static_cast<X&&>(x)...};
        }
    };

    template <typename ...X>
    struct capture_t {
        template <typename ...Y>
        constexpr capture_t(make_capture_t::secret, Y&& ...y)
            : storage_{static_cast<Y&&>(y)...}
        { }

        basic_tuple<X...> storage_;

        template <typename F>
        constexpr auto operator()(F&& f) const& {
            return detail::apply_capture(
                static_cast<F&&>(f), *this,
                std::make_index_sequence<sizeof...(X)>{}
            );
        }

        template <typename F>
        constexpr auto operator()(F&& f) & {
            return detail::apply_capture(
                static_cast<F&&>(f), *this,
                std::make_index_sequence<sizeof...(X)>{}
            );
        }

        template <typename F>
        constexpr auto operator()(F&& f) && {
            return detail::apply_capture(
                static_cast<F&&>(f), static_cast<capture_t&&>(*this),
                std::make_index_sequence<sizeof...(X)>{}
            );
        }
    };

    constexpr make_capture_t capture{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_CAPTURE_HPP

/* capture.hpp
ZsZimmbGWMk0MzZpmDLmMGjmmrOmmX5U00y/B+0h/B47y3vq7bU9Byby9vdgfi0yVS7zvOe68Av5/3o+3vBffP79PI078mrPu+/HP1L73h/+1IZSZhv+OteQajxDPMYuxGPsQjzGLsQjPg7xyJOGeORJQzxi5hCPmDkkZcxs0MyYOcQjZg7xiJlDPGLmEI+YOcQjTxriETOHeORJQzzi3hCPuDckZdxr0My4NyRVnjSZ5oce5kICOhg0cw9GiEfMHOIRM4d45NpDPGLmEI+YOcTY09GSthxwkmnmno4Qj5g5xCN2DfGIo0M84uiQVPqfTEtXXLXlXUOuMmvaZoNm7CW5T8uqy3Uz6jPsCbR/Q5/VGZUe3G9I/ECP/Gu+wD/F0mZs1VUZgx6JcXGuY4yPT84t5qKtzQZHqF/ViU9oHOv7OZAI5Y4NuxBAOSOGxJsNc71STLz2AvdizaD75R7sc/IYfupeJsnLvoR62JdQD/sS6mFfQj18Q2hK32DQTN8Q6iEboR5jGfoQe4V8vsG3Tadnr7gKPVOMX5lA0x6b+4DUS0t6n1sfN+5O7Vcbe/CpsQefGqfiUzKtaHFFy+ok014IUDYjm3WfZvApmVace4fQ8pqSTDN519iDd40fgndqn9XgxIG+jVYpeVfd4F1qv9DEwy80SekXDJrpFzTN9AuaZvqF+zTTL2iamQ+B9hCxxP09Rzr+9Z5D10/We0OvbrpyY8TNKXnS1IMnTVPyxKCZPNE0kyeaZvIkmWbypOlD2L77/TfmJN48aGbwIHVfm3n0tVnKvho0s6/NPPrazKOvzTz62uzfGWs9r9M9TdHPyAf2s3mqfmqa2U+DZvRT08x+3qeZ/dQ0s5/Q/p1+Mn9I7mbK8ez0wH628Ohni5T9NGhmPzXN7Kemmf1Mppn9bPHvyK45b/Qc05jAB+1rCPOw62Eedj0slV1PplXANi/jCZjx+7TK0I5ACzVo1UyaB9/DPPgelpLvBs3ke5gH38M8+B7mwfewVPF1Mq2m2eaU/t6gNdDlJho0Mw4PSxkXGLRQj2c09aC18KCFa586IiSZFq1pzxu0AXqMhhn3jta0lQZtJrSaSEoPg7ZK0x41aO9rmtmP3Zo2yqCd0c+YbNDMOUaYxxwjLOUcw6Cd1TwYbtR3SdNGGzQj/r9P+8mj3FVNe8yg+ZVQba5v0DKUUOXGGjRznhCWak6QTMus6ytl3GvELvdpWUso/pnyYsYzYQ+xnyK2d+chT+kfuPT2abMMu2DmsIz42ivbZpQNKOErOyQm+ao7fyDVNdz3/V6vuKClh463TKnjBs3U8ZYeOt7SQ8dbeuh4y3/Hh5BB+2sfsviBPiTco5/hKftp0Mx+hnv0M9yjn+Ep+6nvDX/Yfv5lctPLn6x5YL9befS7Vcp+GzSz35pm9lvTzH5rmtlvfW/jh+13ygSt5zive6D/jPDwnxEe/jPCw39GeKzVRnjwNMKDpxEpeWrQTJ5GePA0woOnER48jfDwixEevi0i5XqrQTto0jzyThEePiEipU8waKZPiEiVO0qmHTGf6+ETIlLacINm2vAID3sdkWrdM5l2znxuShuu7418eDn9yyUgb9v+dbLMPkRMqXNA96aDRno35Xx4/5/mw+Xu53b/+fpLSv2J9NCfSA/9ifTQn0iPfEGkx3hFeoxD5EP4g3t8MRZCPd7FOpHME2MtNXeJf20tNSVfojz4EuXBlygPvkR58CXKgy9RHnyJ+g/44i74pubL+Yfhi1vFA/kS7cGX6FR8Sabl4zkD3L3lkkwzeRXtYW+jPextdEp7a9BMexvtYW+jPexttIe9jfawt9Eec47olDbYoJnzi2gP2xqd0rY=
*/