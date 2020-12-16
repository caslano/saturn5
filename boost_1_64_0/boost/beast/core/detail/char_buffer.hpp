//
// Copyright (c) 2019 Damian Jarek(damian.jarek93@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_DETAIL_CHAR_BUFFER_HPP
#define BOOST_BEAST_CORE_DETAIL_CHAR_BUFFER_HPP

#include <boost/config.hpp>
#include <cstddef>
#include <cstring>
#include <cstdint>

namespace boost {
namespace beast {
namespace detail {

template <std::size_t N>
class char_buffer
{
public:
    bool try_push_back(char c)
    {
        if (size_ == N)
            return false;
        buf_[size_++] = c;
        return true;
    }

    bool try_append(char const* first, char const* last)
    {
        std::size_t const n = last - first;
        if (n > N - size_)
            return false;
        std::memmove(&buf_[size_], first, n);
        size_ += n;
        return true;
    }

    void clear() noexcept
    {
        size_ = 0;
    }

    char* data() noexcept
    {
        return buf_;
    }

    char const* data() const noexcept
    {
        return buf_;
    }

    std::size_t size() const noexcept
    {
        return size_;
    }

    bool empty() const noexcept
    {
        return size_ == 0;
    }

private:
    std::size_t size_= 0;
    char buf_[N];
};

} // detail
} // beast
} // boost

#endif

/* char_buffer.hpp
zAQ2AouAW0Cn8DtqENIDTQUVgZaC1oK2g/aADoAOg46DHIORR1BPUAYoB+QCNY6GnMZABqYb0AW6B7QbtAludaA9oPdhj74YceJ3NlANQXygnqAM0AG45QOXgtaCtoPqTZ6xKCMoC7Qf9gbQcVCLNJQN1DgW4YETQWWgWlDCOMjupghVA9wN+0HQUdBJUPRQ1CcoFZQJygc5QblZkBuwFrQbYfeDGkEtVkeoZNAYUBFoNWgLaDfoIOg4KGpNaN9tyITM92EcoPIfXP+f55xX7Cr5vvYAtMG8YjDn5Vt5h9dK6lDKQd+2x5h+sJ6XY71gdjlmxjInP9K+yXoBeZMsa98IQf8J2r+X1k+GDXGft06izr+HJ4xHT865/ncSbqrqSr1Mto6rm6R1h+RlntaFTtb+/SxrbWV6LS1G0u2EOovR57nixM0m8W2Us/AliM+7nnhK4itQvX3e4C5BTr3v9rWSOK7U+otO7WTNBPrw5usvIFf/dR+up7tlGedZ96EbZaXXfO+Q8G5ZME6us0teqfvhm9zc93ENdT+TQCfxI79pneeVcn09SN0zzDkB62OC9o/X6++LxT7aX956feda8c/Q6zn7ITwssoku6J2z0AcFkqdVRpCH/gZOUcF6MeUxCPQWfmSn8Y1yV14VlwxZTn85kJdrhuFN1wzp31nLoVTs/S1riIXzq8pdWg6zxD+R7d4TPq6p3Jh+tfg7tB6hM0q28Cza3x0B5BUedN1R8urTpt7n/gcnZVgMasSPmlSRodPcqSENiwt8wdsUw1j0iT8R+5VB28y94j9RxaPsZjZ2U5fcnXr4Z89CDshPwPXLMRwybWX5fgr6I35ED/ItHzd4WMpWVOk+W8/9HcK/Rs5TzgexzIynsyVcZUWh7kPpb93jIfZ+cDEscpF9FJonW3hmq0t9eIp8+rerhCdbpaOP7Qr5hYMjtofIUKgKFN4O/M2479LUB9w7qIkOmjJ1y4Fti24oo5+cE6mXXsf16zUgBybEtUP85eyqKAvehsgfLeWcAvsmsc/CHLUl36nByVP5ZmItuj3XImexvhuUcXS0+DsHWe6epf9ClcW/JyV+cdrDJcxgT5jJljBp1DFO9guTKVLw1Y3tY1ma/I1iWbeI/wzMa5NYfh2n7g8qWY9mHaY3Q6/o339maR2iyMhPr0i5UK+IcsNNyu3TR0xspcTcyrpdDYpA3SaeG6Bu8ypdFcHrl2Hasy4xPRP7YuFPjvatywmaP1qPE1LFfp2Ff2FBWVUx+1sP/61afh93xPpox+brQQL9/UE6PvLL1G6Sts93kMw9CivY38wHfYof+/1kxT/QQeREfku/8YnY56jLlNG0PbGPOiU8WWij4T57dCqSzm5fU7C+1EW9/iTqgrLM+MF7zL8vxY/ZxeXBykb+9uJ/sJ3pbwb1liN8MHXt+JftgGHiLN9aCcJ493Z2lTAdaDdUa7Hbgn57dvGPw3izBfPFMLCz7aBXhNz/zbELygc3KZ/WTx39L+qnguihguitvj/9VGC9zA+vt3owwXRPP5K0tO/2xx99udL5t9h1EVCQjJb4M75J7jP1xNKbto+b0akx4pblSu0JM92ffyPn821lXY5+d9umMe/2+CUWF/8m7nUfX9n9zvyHW90Quc+IO/HQk1hTF/2XK37N1ysm3zXjhn7T741Oa3kY9Sv8768sWvdgx7/86miHmR/uXfVMv/89fZlL8rPqobvfOvJiauqKFy+vLr31wcbvT1/2lYwtOb/jfLUEPyKBRR49GvUG1cBuwEXUFywBDgMu5Xr8DcAs6lsupb5lCvUss6lfKXfzUV/BeQznTCV++oq5XJcu43r0PKY7n/oaJ3ASsII=
*/