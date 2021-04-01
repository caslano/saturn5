
#ifndef BOOST_CONTRACT_DETAIL_NOOP_HPP_
#define BOOST_CONTRACT_DETAIL_NOOP_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// Following must be expressions, not statements (as used with if.., etc.).

#define BOOST_CONTRACT_DETAIL_NOOP ((void)0)

// Following always compiles but never evaluates cond (so check correct syntax).
#define BOOST_CONTRACT_DETAIL_NOEVAL(cond) \
    (true || (cond) ? BOOST_CONTRACT_DETAIL_NOOP : BOOST_CONTRACT_DETAIL_NOOP)

#endif // #include guard


/* noop.hpp
rrAuQtDBKUeub1Ns3/T1AZQn/pDfkS+EuwN6T3UdyRw3rfbmZfeLgLJsQxEoNvZj3CwpYaT0YF1598gjYsrRlRg8jGr901ENlSX1P8gbI7Wa2uLsRt1NLpHk43wpw9WjAbrntW8xDe14Xbuum01Nam0a8PDukmb8ENWhlaOlULs90KCNGm9J7FJgQ9JK4zwpSVp2rWeHGVX/R2djjObrny48vFKayCLB/T4DtuxDrDwv6ldNnKfosZURmgS+H7S23kImilfMJkkGZOYJENtINg4oRp5VYDOUCNvKGelndugGuCBwHnnndT7xQoHTlpCX5YoXCoRZl/lOQJ0ZGaZy14+Ev6gb+XgBnhNVWbsZrs8SSXkswmJm+1u4KZuERr8Naa7FOJy06FY3pbeCUGKksrFKMP3hHrv58EJ6QG7aCerNRfbRHfXViNxVEnuGBp3ho9bJRe3DsWGwPP1I8zjml+Te0pj09heE/3hnpAvBVZ7Kkc5MVBmEfFSDtc88a0O4zh0RK/hZ2eQCdEGh8ffCuhpEvuJ+LQpgFZvU4YkrLXRXIo1UJM5GuOpk2A==
*/