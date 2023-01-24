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
PCxWrr9s57eFLw7xSLllEUeh2GsVd/Qiq7crcpvgjyqkl3YOd3Tcvo1t/9ANOqISHE/gbQ9QaUBm84wIE/M9Q1GtaAFlK9a77IdAL4HNFR18M6uTy6QhBNezu1c7amyXJ2TQSfndP3MhTuyt4Nci612u8GyRDGcv8eNzxOiu03XGxU9qoU4s6wDS0HBTJZDMXVhVZnicD7HAEZ1f2nzR79/PVbPiHzpKs1QNdK8ghnAPBBW4FG5hgnANCtdN31zsBsaTvhZQawYwhxZf1V56C+T+FW6HQ9I27lcWVOFXWc5kImaVX6D9GlTNFjZ9nluMcj0pIYtbMb1kMSouzlejJ2q4oG7O1qyPCkzxKDXH+WdeaYLMYvwr2aVMBmfBicHzxziSy10q5zhSt9IrjcllkTJCX68+VMjWFCrTdjGNoHcgutP8PLJcoOqCKW7iwOYl18B/kl2OwXWASxiO7RPbdmOrsa1GjdPYVk9s23Ya27bT6MS2euJ7f9/7693ve2ee3dmZ3ZkNpPNwI2l516wHDF/fPxYqT3CgCTvTOczsjKGj5N/2uF6kU/3wuXTtF1W8FiBXBzdRsSHZiPfiOlIwenh2eFtdexdJjq8PJXvW0IkMu5FhOL/w7PlYHS3QnTFFnhi5Aoe+xim03aJ98Ho4c63fXOGruz1F1NS9t3xlbZDEVUjmfUBDP4elVP4MNVI9RCZp/Miub3eKiXjx
*/