//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_BUFFERS_RANGE_ADAPTOR_HPP
#define BOOST_BEAST_DETAIL_BUFFERS_RANGE_ADAPTOR_HPP

#include <boost/beast/core/buffer_traits.hpp>
#include <iterator>
#include <type_traits>

namespace boost {
namespace beast {
namespace detail {

template<class BufferSequence>
class buffers_range_adaptor
{
    BufferSequence b_;

public:
#if BOOST_BEAST_DOXYGEN
    using value_type = __see_below__;
#else
    using value_type = buffers_type<BufferSequence>;
#endif

    class const_iterator
    {
        friend class buffers_range_adaptor;

        using iter_type =
            buffers_iterator_type<BufferSequence>;

        iter_type it_{};

        const_iterator(iter_type const& it)
            : it_(it)
        {
        }

    public:
        using value_type = typename
            buffers_range_adaptor::value_type;
        using pointer = value_type const*;
        using reference = value_type;
        using difference_type = std::ptrdiff_t;
        using iterator_category =
            std::bidirectional_iterator_tag;

        const_iterator() = default;

        bool
        operator==(const_iterator const& other) const
        {
            return it_ == other.it_;
        }

        bool
        operator!=(const_iterator const& other) const
        {
            return !(*this == other);
        }

        reference
        operator*() const
        {
            return *it_;
        }

        pointer
        operator->() const = delete;

        const_iterator&
        operator++()
        {
            ++it_;
            return *this;
        }

        const_iterator
        operator++(int)
        {
            auto temp = *this;
            ++(*this);
            return temp;
        }

        const_iterator&
        operator--()
        {
            --it_;
            return *this;
        }

        const_iterator
        operator--(int)
        {
            auto temp = *this;
            --(*this);
            return temp;
        }
    };

    explicit
    buffers_range_adaptor(BufferSequence const& b)
        : b_(b)
    {
    }

    const_iterator
    begin() const noexcept
    {
        return {net::buffer_sequence_begin(b_)};
    }

    const_iterator
    end() const noexcept
    {
        return {net::buffer_sequence_end(b_)};
    }
};

} // detail
} // beast
} // boost

#endif

/* buffers_range_adaptor.hpp
jrHMrdpSv3IO9SpXAxP4XldX4FpgInAHMEmfK2S+dXl8zxW2pR4kGhgBbAeMtsydSjB3Wh2aP4VMyIRMyIRMyIRMyIRMyITMD2D+M/P/wu9N/9/Tov/f6+B7CjbRealWwE8x5zx2mXfeWNhM/b87zAjRG0+HfWC2af+N0UW9Ch7TDdrJybwjNPCeAMZxodivgL2/xPG+EWgPAPXTDDPUyIeeOJ766WwJ97RxtRoD1zZqsDEm4B4B7glgHKl6T0CihP/M8N8DEMMzCmPF/0HjdYSw6PkZD1ZCMJV2avs5to3YfTfPKG2q9+feh14S3yeGV8fPsNTxV5vl1XeM67rQaaf78df46f/jqP8fLOn8zngDXI823QOg97jfJXwfw/9FcWtvxiJuhpGitvnq+3k2I1n8X5WzGYniV6j3rZ4Qv3C91nJA2kEnvX++l9iPwv929SjcA+wJ0Gs9OySuL8D1tHZ3gPaL+zGs+PwaeRb563aANiBxMl+F0m5Zrpcl7bb+enYtiyqJoxGrS7/R7xcl9Wj+ek92gPWenAC69PwguvSSILp0ZwBderVVl87wNfrud91uGD64Tv2QrPt898y1Py7Zn3HhjV81rDzReXKSe93nqG5r0m+IiQe9D5I88967rsAs7p+dyXWeOdS1V/Beo+3UtT/N/bPvc/+swX2zUdStx3DfbJLBd9uBQ4DnUbc+EjgUOA54HnAFdey3Uce+AzgC+DZwFPAQ8CLgYeBo4KfAMcAvgRcDTwHH++nkt4TWlEImZEImZEImZEImZELmPzf/n1n4Pen/u1v0/+kc0jrDMC4nHumHsfpIPf83Uz6j/t/NP1DFcN4+SezfOpbZHP5zff221QTh2eZYZOOeaB1P/+B7/jVPsj4nnSX2FvbVStmSeK5zvzv/jgKcipttTIBPjXrPlq/uta9ouseA+69/KWHekznpZJ3OJMftmOXcYm+t4nk+YF2m6f6cvZeai5nwBHWR0c3GObrPmQGZ6/EMQr7EdczhtHnfx8kRtyrbVUiTaya4G1PezLHNVS9Z1xWYF0P2MtRoe2rY6dYEUsnnWY9YbQk30P60Gu1Yy3m2nASRCuUe9oDz+1wJO8qI4Vn6g5LXR41q9RR5DHW9uE1UwoNf2ReZ9r8ZHdTNRgzzMEncbLYOxlrLnLt6Pk5TSzzzDFSX8Iy0uf2Zv1Sl1yIOS17GGQPVHSqG+ZsrYVYZm1QvqcOOOv1vDQd2KLyhfqcs8aExpur1iF8I39V6TWDBaNPu4t56cEt6uban8bU/j9i4bsH4la2F+iVWuV7XZ4WPSvgSv/QG6fh3SLgZKp5teonEP8HxuIpUu41INc221ZBz5ZY0otUjaBVv6zPdL0kaN/nKMFWJf5l5vkLqopevDAcp5h37QyTNSvtotQh3GSfbPLIdIPFmYP5t0/cmOCUPd9Nu5onv2rFOCyXMF3yjjusjms785nUbFQVAOmMQj8WeTXuMCmv3kaShek6cNGSQottBr1uqx+1V7Tb4fI/bS163dI/bM1638zxuO71uwzxu27xuQz1um71uaR632FHabbDHLcLrpvP8t0ztpvP8lXYbpPN8xOuWrsvrddN5fsXrpvP8vNeNecb6UoB1qJIA61DOJutQXFuy7keiW41lDUox/Oog603WMxzIgM/+pQa+oXwiwn0PzfPAbeA9drFlHxpja2W2Z+lji/j3x8OXqteNE8ea9hci2Nf73BsxQfPHi/1y2FsJ/3jLt1RVZt0btvFS+VugLuI6at04035dWKyKUkno//4M/A74qhGF1eqn1CP4m/akbY/6sT1K3Wf/Hf4SRal1jt+p+WFR6iJ+820lzYKIDaodvuxxymE=
*/