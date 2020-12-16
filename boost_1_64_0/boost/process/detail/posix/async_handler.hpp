// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_POSIX_ASYNC_HANDLER_HPP_
#define BOOST_PROCESS_POSIX_ASYNC_HANDLER_HPP_

#include <boost/process/detail/posix/handler.hpp>
#include <type_traits>

namespace boost { namespace process { namespace detail { namespace posix {

struct require_io_context {};

struct async_handler : handler_base_ext, require_io_context
{
};

template<typename T>
struct is_async_handler :  std::is_base_of<async_handler, T> {};
template<typename T>
struct is_async_handler<T&> :  std::is_base_of<async_handler, T> {};
template<typename T>
struct is_async_handler<const T&> :  std::is_base_of<async_handler, T> {};

template<typename T>
struct does_require_io_context : std::is_base_of<require_io_context, T> {};

template<typename T>
struct does_require_io_context<T&> : std::is_base_of<require_io_context, T> {};

template<typename T>
struct does_require_io_context<const T&> : std::is_base_of<require_io_context, T> {};


}}}}

#endif /* BOOST_PROCESS_WINDOWS_ASYNC_HANDLER_HPP_ */

/* async_handler.hpp
ho2VDzrje26h6CwjZe7X9pMf1+rNzD7UvRIut62/NIcPVyvcbeX+D1oZcmeuhj2RG/aKcG32/UjhSFL2bpX0Wo87Xq0jdmdgrL41CaNWSfWD1JPwXXRtJBx1mJH1HsbNbK6FmD0Ya/zRzCqtnIpbR7H7DbldipmUg/RtfK/mMZLzMsYat+IbUYatKKtq3nBrsXfaFcnT1ZBe3acpiz+xMj3CSkezH7qoxLWcOU8qYHe+Hkpsq2iZ2AyU7wJuks899UTTXauvxSprCXCt2PFqIfKcIDPdX6gH3OmkrfLf1eeKGx/JPLFhYzNzrXX1e0S/nlaC5y7CGgvTklS4ekn4j+vxzO9dTDy+1AiPGc9hUlBjle7XotuFUNd0SD/rLCSbnnO4TLf68m3bmCd+kKx7r6faqHvi6IPj92jVJmzgC8zPbwg/555PfTN8jWmk2uKpUJ13gX0M9LvRGDMhLiBvonTvxFxj/ZZ2/LVXsKZX5q5I/WatkaA+stf9Ipe6wJRL3oo82nyHWnVBEnIfJE2RF3y2sSPpKvfM9A4Oj+RVYbpSxw+XsqBpR5MC13nqera6fkhd/ynoTAbnvfYL21P/v+9Mhvx+Es4kT606e/bdOyVm8o6IF2p5/v/OXrjSszX+WWc1OJ/JUPjZC85naBR+JoPz2QuFndVw5WcynOXWdAx/ssYqhfye4QrMH2wJyyAPs35L/9I5nfDye6Xt91Lb77W2349Zv2UPlq3wbAj1kfodSfrlwyq6sU+W7N8m98phktV38K0h7JsPb4N94O3wb+zdB3wUxR7A8b27NCCEJIQQeigiXUogQXoJvQQIPZRAAoQSQghIlRbpJUCkN2nSpSkgEUITUFBAREBEmgoIGooCCvJ+N5nb3RwbH/HBe7737j7M58v9b3a23N7ldmZ2pi2Ow74Yj6PxLYzH8ZiIE3ANTsQknIR7cAoew6mYgon4GOegdSMWYhach564DYvjDCyLc7EyzseGuAC74hKMwaU4HFfgVHwX38c1+KF8/pF8fgjX4We4EV3Z/63ojsuwAL6DRXEF3lV4P0y2sXb4qMjj9QopQB6vneTzx4+wCO7BqrgXQzAZQ3EfRuB+HIIHcCoexOn4MS7Bw7gfP8fP8SR+gWfwKn6BN/Au3sRP8B6eksf1NLqzbV9iYTwnj995rIcXsT1ewbF4FSfI55Pl8wV4FxfiddyDN+Vx+xEv4AW8IvNdxa/xkYw/lvEncn13xWdLjnUiz8FkLEByksexKvk8sA7mxGDML58Xks/LY32sjg2xFjaVx7k5dpHPo7A19sY2GINhOBC74iAMx8HYDYdidxyOETgSI3GhXO9a7Iu7sJ88n6PxFA7F0xiDX+MAub+x+AgHYjZTatwfh2BRHCrzdbWNQ4ENSMmkTCTOGfEYZ2F+CxyPeXASFsPJWBGnYBDOwMo4DWvhdKwv43exnW08Bawn1+NGss3TddGZn7V4CV3xMvrjFSyCV7ECXsOq+B0G4/coy+fe//TLPyXLPy3L/1KWf0aW/5Us/6ws/5ws/7yu/NF/Uv4hWf5hWf5RWf4nsvxPZfnHZPnHZfmfyfITbPdL4xpZfjZSvCx/M/ky43bMhe9jHtyH+fADWe5ODMFd2B4/xN4yPgyTcbRcbizuxtmYhO/gR7havn4Xy6r39Ip7icXfDQsWkdtVi/fXajAWwgby/Z5ou+8Vx8v98dD9DVpE+VlwidyfZVgS38HXcDkG4AqsgiuxJq7C+rgam+C72A3XYn9ch2/ieozHDXI//Ey2ey05FvLz709yN8lO5my3BzbEMthInt+N8XVsgrHYHKdiCCZgC1yDw3ATDset2BoPYRs8im3xG5nvqsw=
*/