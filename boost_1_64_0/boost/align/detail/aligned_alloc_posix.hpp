/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_POSIX_HPP
#define BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_POSIX_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>
#include <stdlib.h>

namespace boost {
namespace alignment {

inline void*
aligned_alloc(std::size_t alignment, std::size_t size) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
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

/* aligned_alloc_posix.hpp
XscRTCUS5dVRBNvvJCpdRxGMm4BbswKARUp6BwtgjDxxEh8u5QTYNhK353MLsL+QuC0cJ8DeK1FVEiXAdtP95zgB9kGJeoKjBNjtgOyhAGRRtEQlzx2fN0DHeNbSW3xxD4ckXolEE+y2vKYlIVsSBPaOEtfPCvtpEtfZAvvvJSq2Afbs2RJ16DMNeg5Z3+BiIxNBI3uWSacA/JvwQfsExJArkBlpDxHNYnoFnRNoyy78W0j0iShTDvRxFcrhXLQO98vwFY+Ot0ZolOGtiLZtAErORS3wjoO0JMLMKM5aZduAiGSNqus8OiKFIuwcUc0RqRRhQ4RtA3Cf0XJdBMC7CTcj02wbKIilHAfpR4W3Xy4BnYjmCA6UEdiSLBBFMUQHdhJE71sBAIBWADSIVgAwEDehQWl/o6V56T4AzHQuqhYIoxtAeo/0UGiPADFBSraAFMkgjdcgWSEIGgJzTBwMRE4jIEwAqesMQgCkKgEpqgGkZwDS1zsYpGQTpBQLSHYGadUODZIVgqpGEGwKhqDaCoB1zKKk/wDJbYIU2QDSywDpcgEpxQQp1QKSjUFKZ5CqLBB8GAxBVTAEApKgngbJgnsCkjlx9gaQZpEcfjuDlCqzQc0SSDnGRwRSBAB6ljNYIchpCkFVMATVVgCso2SX/gtI7wtI0JavJ6gwFYDqIUDlEqgc1DDuCTtyKuqsOB7OQ9UKmQTm+JyKr5MD0MjoJdk25FTsTTEh4shkgmpvqgkVF06hyK/TGDgTVCtKANCltg3Ygiv2cJcjCFYA+iaWK47Td38aE0akkLJdwCQB5A/rkPonn5E0+vJpJ9yQT1um+Rlh6GQiYzeBjBHpctnXe1yVIEBglnLheSv7vZyiCgfRLZi6ejNyD7H40feM1/C97DVmzPIa18Jv5A1vYjerRgm/c8EnB0kLkftrsFFfew0wXq7N3uIOOca59R6X25FDAn+3g+/EuKpyXBEIxSPRgcSkHFcVgkkIItGdnOOqRjAZwSQEU3KI23WnIJiMYGqOaymCqQim5BQtyUQUrkwsYU6y6IZp4SS/gcgBWdKc857/zk/OCsF9Wj3k/4fog///+//vVH78XvcOOkjdf1HgNDj7afM0uA4puSSW6txmIyL55mKOM3szH+RhPVv6LBXd84oNUsAqjiTP809D3G9eQ6oRfSgOiahNDon7xrO7T2r2VN+WCLKnD3J1sfpCsSB9mC1rjR3ecH5Q1X3oY9jTu4u+iHYXfQWmah/7Ej/sTefUW7qUeODUid/rvs9TFBbuawlDCk9RucNTdBi+5LLnfQGRGblJyyfL9nccVHfvOu2vhuJ/4BegK90Vypad8a1zbj3LlY85nHcW4Qv08qZw/Lca/6IzN+xxG6s27MiMVaiyICETJBfxazYotyMrLbM20j1/clpmUSXa3uvI8Ve7/eVzjtJxfGpHT8klmW6WmLCz6Qy+sT7ncxLRUVV3sNjZ3XtN5oYvuZLiJ2gUai6FHAwt9EWzSDlBo7ZPzcZ87Rs39uVguR6/jYrHBzfkOqib+hoi4FI/vqg02nPbPvmgHndM3KdFwxOt22GPpx6Bbei9T7fTCtdHwqmFIrTg2qbruQf18MA+iRC8a0Nft9dTsSfGAxFitwZngKNQxlPxZQySbF7bD3O+oqGovb6UajZW9q6Edw4YwGUcmDoAE+PpfcDYjIJGRRZJqEZlemzLVJ+XbGGNeuq1HVX16QRKbSejAjhNOXNQHLlRWP3woi3M9ql0WCZ/3uUY3yA/8FbfEKck/fj3/6z64VkXmPf1jK3GPfJiyHI3hrVoZ3RBq1KK+KAeKJSQiTckqvBntttf4S46nHzrIPyfecsvPCUjgQc=
*/