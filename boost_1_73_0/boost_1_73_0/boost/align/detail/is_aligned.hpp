/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_IS_ALIGNED_HPP
#define BOOST_ALIGN_DETAIL_IS_ALIGNED_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>

namespace boost {
namespace alignment {

inline bool
is_aligned(const volatile void* ptr, std::size_t alignment) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    return (reinterpret_cast<std::size_t>(ptr) & (alignment - 1)) == 0;
}

inline bool
is_aligned(std::size_t alignment, const volatile void* ptr) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    return (reinterpret_cast<std::size_t>(ptr) & (alignment - 1)) == 0;
}

} /* alignment */
} /* boost */

#endif

/* is_aligned.hpp
4OBeqCgELLwPg14XUJNRe0+9ev/26PLk3VucPaN7rDNQvsHCyTTdH6CeF/eUaIyF6j3xscBTu6hnCeopQGBisDofZhl3TffegQUBj+s3W3nCEfGgb8Iw4nna5+kPMM8d0jynmbUPIG+S1J+4obVRw4PE4uFhaH4EFqSkxOsdK2EKkg3FU5drEqU9SQXjFe2Z1CyCbj5PiwmWWtAiDJqqXWMNkLQD0wIBPblcycBDM8SW1iE/kkWIU6lEy+0HcLGcci/K3K8B6FVswnbP38ioUcSQICjDogL8NQjEOrJjuosvPjiJdRx98PDw0ci+OYu+b7Q2BPhAH7hhd7p8waBH6+LHrejDIftTm7RYT58yOYt0aEPOL7LTsvro2i0N1sxsSc1MMWLzMxe6vWTL/fLeoVWgWiB9nTF3ZpfRU9phwFxms3WVL8qp1YUuEWtSIVpd484H3JCFYM7G+A5gsKD0sLlm5bGQ3qVro9E1oo3LKuZBjN+8HMiPU/y4FJqohLBs1P3EABFAYfzm6xmksDpVwzYq93t86AiDwquteZG+xjcXfzo6v8xm8/keE1msT8jEECaGOXlPh6R987e9I4Fyn1DoWO3HfBPo2uDHZlAY9KjubJYNX4JYfbi4PLw8OTo9eYGl8OCOXp0efoNy
*/