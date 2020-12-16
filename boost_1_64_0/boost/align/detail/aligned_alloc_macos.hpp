/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_MACOS_HPP
#define BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_MACOS_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>
#include <stdlib.h>

namespace boost {
namespace alignment {

inline void*
aligned_alloc(std::size_t alignment, std::size_t size) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    if (size == 0) {
        return 0;
    }
    if (alignment < sizeof(void*)) {
        alignment = sizeof(void*);
    }
    void* p;
    if (::posix_memalign(&p, alignment, size) != 0) {
        p = 0;
    }
    return p;
}

inline void
aligned_free(void* ptr) BOOST_NOEXCEPT
{
    ::free(ptr);
}

} /* alignment */
} /* boost */

#endif

/* aligned_alloc_macos.hpp
/l93hsT/JaNr4j/XqfHfv28d+I+sjv/Xh9SB/023Vcf/dTH/GfzX1K+K+5ZE3jzzIfv15FUYjSzjm3TjWLrxk1FBQ9LFVRgtQzKkoQzJeFkwrMAaTZBcbujQ9ee5CltI9i4NtRIN2bNsF6i0QnLFrRgiyttW8h5vILrvNpx3n5W3HeVNdhtyDIQNBb9nZd45Um45yqlvr7EMQvdToU7htptTXkEOF/yVff2K1JWjiJFcIEWNBsK/4+fRxwvl40R8JE2Igz92l4+30UcAt2cufUySj1n4iJ3KTnwjj54rSUR8SbwFWHrMNsoM86jHZhIaoMixi4/h2rCRoHY3JUBh2c80hmJnfG9ipjEBhuUHUeLv4oz2r6GM+v0C+l09c3dPFYIphlsFe8VvglmICKWfq3C9MOekKELYKpXZT/Z5SRiHdlEyFTciC19ZnSjx/+/Rq6O2c4vNw8XnD/lQZoZRQiCQdZ2wBSLB/FbzmiFZJmlfOJ866cqZtjegNR3xqwvLjUB8H5Eb+3TSN1yKM+ult1Sfmh83lqnJ0ZnQKINyeswvtvNhMuHenKIXuqVAYPImF825/XxhhquwQuv9HDLRGmVaftIXAYU7HILCSkbhPSYKR0LIF6FZawYlGKy5l3GxWwnTJJBn29ToPU2Gz+UnAZSxzAa4IUBuoLbfGFqWdE2D9Br/bq5tje+D00/sIlAynrzWyQ6yeVFjjhh5t77r5b4bacJlC1J2Rch8HfnkiY3ytl8ewhTSfRYSh0DHK6hFPowR+Ph6iPxN91PQkTsjBOdzeL1Jld3xpernu2oIdeiJO5M90S4ouldLWE+JT3FCBMeXZQmrqEZJsUXPgO7CcPpX5h0Jn/Sq20iLP0UZ0Qj3r4Aj16QoDsSAjtfAR4SJj8TSWu8zjXrQ3Pd0Ir9yOtmgWvel+RXVEh9qVctY9v8HzPgd8awT2nezKaFVb07ihYSCP9JwdSIXMUqsJT0hdHppDfqL4s6i07b3+KB3Z9B7UtB7QtB7rO29ITlF4LUGOLb0+BOkO0+QnnSC9IQTpMfWkq71f/cLU1/Jo5WI0Qo1P/ZONvdPmAQVbPPO8DfCviq9WjChi/CNqL8986mRJp8qviOI8tUFw3n/n0gF01Cw6rgU7FS94CwUhCOBsIHPkYeVa48F1UY+X2eBYCccNQn2znQm2NvpQ4GjwgETYTU+k47pjowN0Ej3ild+27asHuunRuKbkzQSw92+C65Gb9hVKsfJV7SS/XdaDBKuQAIWuvKfUeQwzOjh+poMTwzAh0dRfiNUtRr7Ugk8bhxWq9PZX/ViMvj1mhzraUcpMESfP5tEKofc6+jy58QiU09K8y9Xf0CZ1H25a6iMjrZ5LnL5NyGQvGc8cBMPUL79lUGpuAvPi/XzUKoAjd4gjWZJowmes3WjH82q3mgCVXg23TKpWz5LWi6raI5a5+hao5Yc50M06KdAlEgQNUMVjJcozpPn93svtqKlVwqHXfxLI3DYj8Fhj6rBt1Pby0hGQ73iVLkL1KIX+P/w9RfugqYbD8eElQbp/73V+eWfBmIG6vzNyb2qpn5qGJW72Wud/1lp6adyyOV1O3v5lmcaxa6UJE+Lh46baqFi//LpKVAL/ZO9K4GrssriwHvAA9EHKorjhqlJ2Sj6UkE0eQn5sEdSpjltWpZDjZUZL61wCy3pk6xmmqZpm6V1WqfFkDaQBPetcq3UNi+CplaKWr75n3Pu+/h4PBWrWX/zfj/lu/u595577rnnnHtu0VXJx5xlB7saEaSNup8uANVHOO8FD4sPm3PeLBYPnctGmr3KrtPj3dPGHg4w5OcfxZB7UlTNBDl6XYj80Ji6UTm06eEBfbI=
*/