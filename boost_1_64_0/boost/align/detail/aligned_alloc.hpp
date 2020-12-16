/*
Copyright 2014-2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_HPP
#define BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/align/align.hpp>
#include <boost/align/alignment_of.hpp>
#include <boost/assert.hpp>
#include <cstdlib>

namespace boost {
namespace alignment {

inline void*
aligned_alloc(std::size_t alignment, std::size_t size) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    enum {
        N = alignment_of<void*>::value
    };
    if (alignment < N) {
        alignment = N;
    }
    std::size_t n = size + alignment - N;
    void* p = std::malloc(sizeof(void*) + n);
    if (p) {
        void* r = static_cast<char*>(p) + sizeof(void*);
        (void)boost::alignment::align(alignment, size, r, n);
        *(static_cast<void**>(r) - 1) = p;
        p = r;
    }
    return p;
}

inline void
aligned_free(void* ptr) BOOST_NOEXCEPT
{
    if (ptr) {
        std::free(*(static_cast<void**>(ptr) - 1));
    }
}

} /* alignment */
} /* boost */

#endif

/* aligned_alloc.hpp
SdKwdrBgVd/PtI3Evvb6SrT3TxwyJk3XtfmPVr/1BDmKml5rzxNkG/6oy16xwS2xnXsC+BPK29r/QepHvd+g3mtRoc+doBaMEKlSs7JL29cyKdIxr+oXLwbjnWIf74Lm/GJPT0R6Ogzwpfrdac+vzz89G9C3fQNfGFt/ePMgOHtRcmUN/zabXJGOpKeenduyzJXgQKKc5GVRHEsqtvOZxkriTW4VNdzyVm1d1jdBGCQS7Pn7O5nnEB/LITlgsJoPpp+8K92owpqeThmMzarZW7zAkaY7Gou7y7+VItGwTL5WXTdJgtCP1+93ztXXhvlLXdhffoI6Yvv52n0vZ2GbnKEmjaLa+oLbdXPgb3xWwcUOK2xDjp7PAKUGsGt1L1TPUSyFrGf4jQ34zCvCdKzNyFXQt1PBrYkqVjK9ueZf8+P5PAvgaFnt2NNmjKxYMeCgG55kIzxPhUPumdySNvPo/g41+V6aLBXh91fiE833Hu1oNndGVeqjd1hyiMfXdvz1PPr6gnyV008Hw0RiS1ARoGmMkytvb3jM7A34zMMumjSMZyIVoSsHc0j3MbwZyD/LuHgF2Y8uhhC7cuqIavZPcHqah2dSqz2o1US06i9z+4Y6U6/M/aYiJbkSZWCzOGae34pxp64eH5WZum5iC1fhJbJxH4Hyas/bKAmrQ5kz9cLcbSYYK8kmxcuFixvpRY2UIit3oOBaXlgYbHRAxh4l1XsYRiKHBFfhFdJGBIrTGjgLZZlaTsv9YCf7M/mZ4w8mP0ttnhtTbVLSxhgnIYavwrivIG4XU9YnIdKWnAlB8BIwenw+oVNdXfFjp82z9gkH2C3gYK/zp/Y1fuXme3Vr6OmOp3i30aohybGNgDz/Jg6RgHSetU0aqndIAUoKPto7uvzLafjSU5Nz/9qr69Tr3bquvMsbhnlSQ1bWGWuOrixGXYlFy175AKnc01aTRdfc90QQ3qo+97KAPAw4YB4w/FfsGXCemYv716PJqjDPubrJqmpNxgaaPKI23MfizLQyzHlgpw98nlEl8YX0ggmdbMGskv4z0WCDzvOTPsxpGYdlGAufkmHEbN0Ni6/r07AIfD0DS5Lp878MH1yyF63CKsnf3sc3nNDpTHJYG6x2/VPUR0MqrUNtT0bQpBmMpieDrYxF66kFiao1ZlUmlAZOzjOa81xeKX4Q3USSRn1Po74sBJy5YwjL2Jy3dwTluVAEgEltRBTrwxkaZBkrOE975MGpSWNpfmXMY3Sdc96vETEzfFxvqi9DgoO0Wp/pi1yZlbpqUpQ7tWzC2KzU1fRUOmFEVuo6elo+4Xfu1GP0tHnCde7U4/S0dYLbWEascvqUhv4VeSuO+4uNtV1XYD/syiuOSE8tyT3sc4U/03Xpxir38A2YZyXfRpLbUkm54yf3W+6S3Y5M4wg+4AWXEA9fAe415UzNzxzuglYr3EYD/uMvQVLu7kxE3PR1q3QCdOPA8ul+IiLhf1gLz3Q9tIyGCBapzOFbVMEjekQ6IBcVzDCW8Y056V2x5z6+PBLbWopY6tim+gP99Dz98jZAY5M2OBOIMuDMUdMv6+h5pY7YH459vqsJf9Mvbx4dkz8JTHN5ZPMwX+SFjNO4f8QRa72Gg6jdqMEh+YZkn+Fr3Y6S5ENsbXFQ676p4TELo2eu9FwA/E0/0sjbJMO0nUOBjHyzndOP/M4V81Sx24//lnJm79a02UmZqcdj8tcjX1pKj5j85VyAHTYKIo9lGqBs9Ss0PcRNtkBnBslqnNxh0RfgqfWvi+k6EtqN7PzvPNlSogzLGT3RktiBu/EgdeNPr8tnWhOd/DmXPj+Cz67CKVoObSV2by8+oncBnYHWKCVY1u8=
*/