/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/block_size.hpp
 * \author Andrey Semashev
 * \date   23.02.2016
 *
 * The header contains the \c block_size keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_BLOCK_SIZE_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_BLOCK_SIZE_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass interprocess queue name to the queue constructor
BOOST_PARAMETER_KEYWORD(tag, block_size)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_BLOCK_SIZE_HPP_INCLUDED_

/* block_size.hpp
m/sGeOTcnTkr9RS8614w9bgsBIUmecojx8pm3vtBcTOE/KBnZe9X4a91jGj66e+JfaqMZ+4hjRZ3xh3x5CYPHzmY08q9PLZDcDyjdxJrusWrGzpKb7umRaXe53e7puNvoc1uGLeFpYXOGUSlgxnnNhH+I5mt8dvSAP/supZz3EwTu3OdU3AZuttJv+jpD6YL3/WiA9dyV5CZCzpS+PxGJ/OP5H065z99kWNhMw6fLDwnkC7JZgxdKGajyZlBMie/oTN505UxE5ie6Ev3J6clUt66p01M68oVHQnE05rHWeAQ8SvZGqYu+L2rC3nRNZjvxndyv5nkvi3vXWqn4bqna/Aelh+hG5r/MXRDZyv/9q7BO1gK0xNYa7CMb4XvAHy7M+BLv8BWroWnAzL0scvTZHpkuTY8w+H5zOVJrTJj1/3K8330TXvHSaP7CC96BPBf8Rl4a4wMexf6gjeGOTHLdK24m+CwlkXfL0XXkIL+zTByrWba5zW6AtX70Jik4EW5u9x3nJNPjfqYre+MP/HfVQCvrT4xd3+1le+d60sn/F2dHFeCfcH1q45id68v4n40c3fZu+L3h778gG5ywpvgu9c30MwL/V3s3xf3mfJtia4pR/3F/5t9Z/lSvPevmjmnK8V+JP5nOGXUFluc0aYv+ZXYXYBpb6tO9iPF/kzfUKTcrMu+ZPTpw0Os5T3d5NlgcbPK59FzbfybL3Zn+z5xBkW47yhpWxSI37SZnrq6g9g313fqCHlPttYrsidFvlHqS/ANkHK+mHIwpWeonKenNXULeQsKeTLFxF7Hq7tVPbWMJ5yVnpKenrjk8PSUZukJ6dZyrm429tRy3qyqKj2hRWQ5N37v7an34Pqq1rgVSOJYbhCPNYembub0ot7vgpvuVRvbYbYfP2ZitlvuJn/SvbmIuKXXuxcsODb8uaTVYcxY+U36PihmafJdb7xW9TL38K6jAosZrxr4kqR/+FVaN9nWUECYEtKsa+0RbhM56J/cRe4CGySV6vFUqvWkCYoDNE2WnOGmSQrviyFJkyVnNjhN+rwUnSYqc/Jd77dv4zsp7rebLhkTKz1qe2t6LNnsSY+klDrTg/o5pYH1c7b3niVTJ9rv+fD2zTaoMpVrtV68BrodfwtfNvr/PXsy5fr0mH2S08XNSvTCNbP1SfDTut5m6rK1Yj+MWfU21jpb3VvrqmqxO9k5GhN7X0XHGcLnN3XgT+X9VOdYp1VknWLqoDuEJ0Xqk3F9yO880ydJS6ZD0tN0SOz9kRzwJ+JHsvW7Uk8dThzzQvUUPks9pV1RJ2Z/RMM01NyjdxxFp457tZV/Sp7pj0SV5eB7apdDu5vCu77m7T9w15w866Ak6D6o2RD8rrHInOwDlutkYspda3E3wOlrHw/gr739zlb3x4t9JTnMbrAw3f4SdrMPIEf4bpcdGQPx+UbQ1r+eIXyTWMlq4vFrbgmRMPdiLq3RO3HhaYtpsK75hZgzhjTjRLZclpZXjJgzY/6CWRUz53rkcrHwJon8bCQ/x/W1y0/HGPLTTt1V9g2u54yX5ZyBLOdYZUf51/QNrtNMi5KdYL3W1B1LQ0Nz6r3rwKwn/KGm7vUD756BjPzo+7zegndvuAwxnCxhl8Cs6bNKF3h2adv3R7cE94v7vmZ/tEWe+Eb8+7cNb1j7E//9X+0k/oSxjj3XJwb3zvRXD9SjE6APcJ//Ssw0idqBGWvP4UDxY6wtPfC/7v2YM1+JuR8Tt/Xvxxz2Ssz9mLivez/mya/E3I+J23r3vNabF4eyhzJ4p0KBHjK4SXX+Xgamu+tOUflGaxbc+CKZFl0ndtK9II+I20n+Z9j1NNh3lHOZbyT6/dJCd9M=
*/