/*
Copyright 2015 NumScale SAS
Copyright 2015 LRI UMR 8623 CNRS/University Paris Sud XI

Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ASSUME_ALIGNED_INTEL_HPP
#define BOOST_ALIGN_DETAIL_ASSUME_ALIGNED_INTEL_HPP

#define BOOST_ALIGN_ASSUME_ALIGNED(ptr, alignment) \
__assume_aligned((ptr), (alignment))

#endif

/* assume_aligned_intel.hpp
BS0Ksc77SZagglInZMn4PAnCK92PU2nVJtI6vLaZqDwoZJBt5QtzuwR4Uw3f+tBeB8CTVWgQ++lBhuBu5FdncC72jTJDzwcfhPiWQmjhdVI8inqeDpdcaczfRW5TQI32cH5Rd2AIvaOnWP07QiSBDunoJjt0VQiveUQndr0TXz86YgaI9/H5yI4AtsFUgO5TdtHqOT1ri3n2ZFI1ngEDqdrv8v67kx1l0w2ufzjAMlybHAR+bqj/XYLUilzszmwhIaNe0TWMDhQnZ9sDPz4uAjdH39/+VMbzeZpYiX3DwWOmEn6CIIMceOcA40cvzOBYBHPRCZngameEaZ7uB/u8lrsgHlXApS7dppXNP7IfIRU/TV543ofPyuej6G/rr8t8HWuU0CiNGn5P3hnZVVsk0gNMDNNIeiJyg0ZoxcIABbSgNM+/QcV2X6b/fL8mCgOY4mExS3u//wW4BOXBwvNNt8qFnGWeVC/GrZUhKnsoDdGNHOw60EOXzfyu86lRkQkHjyyxx1sjS10PdIHIlqq1XYfOf76FbYUripiScEPS6pSdCQfgtSe1XofbpA==
*/