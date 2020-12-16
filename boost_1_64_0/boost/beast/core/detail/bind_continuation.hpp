//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_BIND_CONTINUATION_HPP
#define BOOST_BEAST_DETAIL_BIND_CONTINUATION_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/detail/remap_post_to_defer.hpp>
#include <boost/asio/bind_executor.hpp>
#include <boost/core/empty_value.hpp>
#include <type_traits>
#include <utility>

namespace boost {
namespace beast {
namespace detail {

#if 0
/** Mark a completion handler as a continuation.

    This function wraps a completion handler to associate it with an
    executor whose `post` operation is remapped to the `defer` operation.
    It is used by composed asynchronous operation implementations to
    indicate that a completion handler submitted to an initiating
    function represents a continuation of the current asynchronous
    flow of control.

    @param handler The handler to wrap.
    The implementation takes ownership of the handler by performing a decay-copy.

    @see

    @li <a href="http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4242.html">[N4242] Executors and Asynchronous Operations, Revision 1</a>
*/
template<class CompletionHandler>
#if BOOST_BEAST_DOXYGEN
__implementation_defined__
#else
net::executor_binder<
    typename std::decay<CompletionHandler>::type,
    detail::remap_post_to_defer<
        net::associated_executor_t<CompletionHandler>>>
#endif
bind_continuation(CompletionHandler&& handler)
{
    return net::bind_executor(
        detail::remap_post_to_defer<
            net::associated_executor_t<CompletionHandler>>(
                net::get_associated_executor(handler)),
        std::forward<CompletionHandler>(handler));
}

/** Mark a completion handler as a continuation.

    This function wraps a completion handler to associate it with an
    executor whose `post` operation is remapped to the `defer` operation.
    It is used by composed asynchronous operation implementations to
    indicate that a completion handler submitted to an initiating
    function represents a continuation of the current asynchronous
    flow of control.

    @param ex The executor to use

    @param handler The handler to wrap
    The implementation takes ownership of the handler by performing a decay-copy.

    @see

    @li <a href="http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4242.html">[N4242] Executors and Asynchronous Operations, Revision 1</a>
*/
template<class Executor, class CompletionHandler>
#if BOOST_BEAST_DOXYGEN
__implementation_defined__
#else
net::executor_binder<typename
    std::decay<CompletionHandler>::type,
    detail::remap_post_to_defer<Executor>>
#endif
bind_continuation(
    Executor const& ex, CompletionHandler&& handler)
{
    return net::bind_executor(
        detail::remap_post_to_defer<Executor>(ex),
        std::forward<CompletionHandler>(handler));
}
#else
// VFALCO I turned these off at the last minute because they cause
//        the completion handler to be moved before the initiating
//        function is invoked rather than after, which is a foot-gun.
//
// REMINDER: Uncomment the tests when this is put back
template<class F>
F&&
bind_continuation(F&& f)
{
    return std::forward<F>(f);
}
#endif

} // detail
} // beast
} // boost

#endif

/* bind_continuation.hpp
WGHqKksZqKvMfhty7KC+Mvuitd/yWUh9ZT0eQJZCjgeQg5rjQVItxgO0t7afcMq7UG9BY8TGeryDG9SAum9PYIx4ebp1jJBvyBxvjCB/H9vfZIYf9zeZPLa/yQwP9Zts6Z/kYx+o1L+LekzSes4fCN8QjI2GpQ8Gxl+m2Af98YPe1yeIv0od93fL+vsmcphBwav5HQHa9NjIWkGI36kSm9+pWSF+pyptfqeW8bfHKsNVtCvSMsznA4EVkgbLGWRvVELbnGLKVj5tPjOmVNsbYcJZK3tPiUN7z6dD2MDlSvg4FY/6dYkd4qmx+ezNsjTjN/Nm054wjzaf+wPLYmvvmSDlID9SWYYc3Q8tzQhjsJ3NJ3ntbT4dV8i3zozTVRRuFtE2n4xnb/P5vYSPNbqhfP0M2nzqeK1ZxzVtPo9JeKbRF/8ONYyAui5NMPHns/v0y9xa2lm8Z/hk7m3afe6YGtxO9jafqf51h8R5xjhHvrbtVs+CvLBnGAFaCnoIRPlk+ok1bEFTZfxjOHI1EO15K04w3wS1MmLURNCtoBdBwTahHBcZt4mKYzu9Jv6XjY5Iqz3aIIJ34Pymmd9m86e34fT3k/0NlLgyntMW0YYzqSig/k9ov+njb2pnv8nwWG2/mSb+XMzmGtjab2boeGUY5/vVkPM4pt2Ta78zVaIerydyvB5/gjrMDlGHBSFsNUtsbDW1XWNsaFvNwwUB9XhCO03HlBp2mkwjruZYynlg0ymnzk7TZ9Px49+FU1ed//+wdy3gURVXeO7uJgESIIQQIEQI4RUgYICAUQMEQYiAGBAkYjQJSSCBEJZkg+EhBEEFRZoqFnxUsaCC0hosVaxYo2JFpYqKSlVqVFCssVKLSCut/e/Zf2fvbnYhtNrH9+3o4d+ZOfM6M3cyM2ceZ/v2zNnuBQh8VuLsdfLXyVmMiRP+9Pyqbp/97LZrBy19ubSgOpiu/oc/O3O2dwgFOfMSZK9EsLMtZ38Gx3zjh5+QrDGkm3/f+I6PXs8A/jLAXUKvca/9m8AivpOwgPaFtG8EvqPPeHDexbl2ut8Zj8959uErnuU4DpzLveQu7iVfyb3k67mH/DG+d7EfaAe+BQwDvgsMB4JX9oS3N/h+AjAaOALYHjgFGA9cDEwArgZ2A9YCE4EbgD2A9wF7ArcBewEpH45pMS8IIJ9DPAvTwDMqR4CjgR/zbMFh4DS682wFx28YCzI+69mKDMY3nGcsRnDvyEjeQZTJ+EYBi3m2ZQ7tX3GvTgPjX0T5d1VoG4z/Yp6xGcszNlnAUcAlrJdlPJPi5HsalcBVvEPpLp5ZuR9YDXwQOBP4KLAYuItnV17lmZU/8szKlzyr8hfgPJ5RmcyzNlN51mY6z9bkAHvwjM1I4FW8u+gaYBYwDzieZ3Mu49kcjAMk3wXAS4FFtFMeHDOgDgLI43rKeyUwnWdUZgLvZPlv5PtUNwE30f0B2h8GruF7IDcDG+h/xLSz/GuBHZDmrUC0NfHvRXs/4I94JqcWmE//YtrnAG8z0wfeDtxkMH3aHwbeAXwB+BPgfvq/Rfu7wI3AD+jOszf8u4+69b8Di++9RAPvBcYCN5n55Tsus4EP8/2i+4HltDNe/i1FWwwQ77k80zOYZ3qG8EzP+TzTM4z9TDrwQrqvtyH9quad8dj5UOicx79yzqMINPV//JzHf/qMRz3a3AHQMVDUwgiVApoIcoJqF4b2yIVMyIRMyPw3jQM084fT/5srCf+27j9ORclaZTQmR3ZV6ZrvdMol2vFwTwJuFXdXCXb6F8HXXMcQv0cwMOqkw+SVQCmJ6CrN+GQNM1H8zCxin3/hXBUDd3NsFSvuM1EapMG0k7WbrI4=
*/