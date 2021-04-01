/*
Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ASSUME_ALIGNED_CLANG_HPP
#define BOOST_ALIGN_DETAIL_ASSUME_ALIGNED_CLANG_HPP

#if __has_builtin(__builtin_assume_aligned)
#define BOOST_ALIGN_ASSUME_ALIGNED(p, n) \
(p) = static_cast<__typeof__(p)>(__builtin_assume_aligned((p), (n)))
#else
#define BOOST_ALIGN_ASSUME_ALIGNED(p, n)
#endif

#endif

/* assume_aligned_clang.hpp
9FF9xxrwM0qAF2i8u1kzcN2rUowLJp1U97YrtsFujDfH1jDc5ald2jL24rV+xYuDBIpEsuiEa73/NRdjkk2X90uyfi0FQNQdqwvW8tAlcn9+8BippybaYoQnv3/NgGNkT1myNlG/+YcwcX+7oD4rB8nNquOunA31gSfpIUGQ/RFcmLKrvBSstsJ8PkAfh6bEYVnX0+tksccIOBXeDzKe0weW7JgvE0tXMDi6JOW5FsvNdW5eCJTVjzutGZhFiShn1ZYn/fiVUJjTisOrgTovpZosCMTSy6OokGu6EmWdUIQPJolIZSzebUdF1KvE2w7DPGsT4+342T77hRVm6rudqPRhnzyNkTfJObUNCFYyTKLRCgmYOkBFbwYt6rdxL25C10TGeRcFHtbja9AG4g8Wd5ZKPoSwXMMWtuyw5NAtvyQbsndjmRXcO5oSertVEKkN3IGVKIiKVu+zB3gv/sCpKUIhONCwejJkzbrmq+l41FVlssxKakJmcu//6Azj61feWzuRxqyCQhI1dq9QFANfYOTBU3BiPkDQhL7+zfmZnfgczkNmUiHGrwgDCw==
*/