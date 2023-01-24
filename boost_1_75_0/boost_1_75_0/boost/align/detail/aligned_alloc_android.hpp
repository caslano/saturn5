/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_ANDROID_HPP
#define BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_ANDROID_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>
#include <malloc.h>

namespace boost {
namespace alignment {

inline void*
aligned_alloc(std::size_t alignment, std::size_t size) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    return ::memalign(alignment, size);
}

inline void
aligned_free(void* ptr) BOOST_NOEXCEPT
{
    ::free(ptr);
}

} /* alignment */
} /* boost */

#endif

/* aligned_alloc_android.hpp
fw7RpZ0H5ZHXoFw2H3us4DsKO7ls+0B0IHnMrB2RxvUMmc/rJ2Od/HnTm0JbP4f6LTsz049cMfVCPQyuZi5ILPpiIzO3Nlb+HvvwDjVftHWKd/zi7qNzhDTwA3m/OqodD4xU/Mpu9+wi3Yvj7wTKRLK/9eMNtD7Od/wH2Alx4C2cBxdh9AbiQFcgs+IB2CmAHqcU+ONtuvUs0RaVhF5I6maqqsinKcqA60541D+GYlvichYylYYcAZddAImte1twyDeZsXlDeuhxxi658i6HTFBPNGdbaFLDQCITlDoUt+FAfQsdzIINh0T4xQ56Uw8RUCCgEX7hoSG4DSe4iPfb/cHP1xKis4PPxNRDLVSPoX8lugakXnwififPK+jgHtVaa9P1adlUaAg/TzAv7LLuyny84mr0181Rx9+PfDFJYvZruwS1z0HUv3pCn+Em26G9WffAq0P4faD//7829GQJJN6HaiJDr9Zxn1dCynyLoCGBZddlbXq9qU8BRiOol/m255rNcowt/nebR5noa3x37OS+7OF80HRK8OiEcGuLx89LEqo2ZM6Y8lcMd/MZcpsrOxbkRJJNUMU7uhSSp6odFp8+6lgRFK+AYqxVpIzsfJ7EZqY2b/b2PkrhBOM/89829ecs++4Hjzu9s6OMJ9GhraSvzBADQe1SVSLx5FEAgSi4yuWQw3LvOUqo+TYM/WLEfqcCfyVnmNoqQYPK
*/