//
// Copyright (c) 2019 Damian Jarek(damian.jarek93@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_TEMPORARY_BUFFER_HPP
#define BOOST_BEAST_DETAIL_TEMPORARY_BUFFER_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/string.hpp>

#include <memory>

namespace boost {
namespace beast {
namespace detail {

struct temporary_buffer
{
    temporary_buffer() = default;
    temporary_buffer(temporary_buffer const&) = delete;
    temporary_buffer& operator=(temporary_buffer const&) = delete;

    ~temporary_buffer() noexcept
    {
        deallocate(data_);
    }

    BOOST_BEAST_DECL
    void
    append(string_view s);

    BOOST_BEAST_DECL
    void
    append(string_view s1, string_view s2);

    string_view
    view() const noexcept
    {
        return {data_, size_};
    }

    bool
    empty() const noexcept
    {
        return size_ == 0;
    }

private:
    BOOST_BEAST_DECL
    void
    unchecked_append(string_view s);

    BOOST_BEAST_DECL
    void
    grow(std::size_t n);

    void
    deallocate(char* data) noexcept
    {
        if (data != buffer_)
            delete[] data;
    }

    char buffer_[4096];
    char* data_ = buffer_;
    std::size_t capacity_ = sizeof(buffer_);
    std::size_t size_ = 0;
};

} // detail
} // beast
} // boost

#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/core/detail/impl/temporary_buffer.ipp>
#endif

#endif

/* temporary_buffer.hpp
s3P0bzzTac413VQV3HlwdXAvwG2G67uqm8qEy4OrgjsP7m64DXBNcH2v7abGw82Hq4GrhauHU9chDi4bbhHcCrg6uNfgfoUbcH03NQVuEdwKuBvgNsA1wfW9AfeEmwNXBXcR3N1wDTcE7DEFrsAVuAJX4ApcgStwBa7OvTrF/h/2dHeU/b9jk5Xe9+ym/b+z4XbgXHHjUKWSrPb/cHspTf7SskUmm/5F5n1QTJOkz97PEn8x95P77d8nfZre3zNd/PncM0R6OZ29+bz6PYRmsfhLdB6p3O+nz4bT+5ImS/yB4p+p6VMcvw27TOJ7qVjsKeqimm24rwMen9z63jbDzhXy8LNzlcRz1cx7hyATvd8/1nvmgGIY+ea+OO6VM3j7d56j1t59Ru3dN7Stzz8bUmSEL4jfd1zxI49WfnHmhCMO6Dcytv023bf1PiD7/VN/3/4gz1wq+x3HmRLrXKqcN58C7M29JvGcc0/mmtgOwKOAKcCswDllbZoDDNgw37r5vfbM7XXIvF4nzell3xiYLwtcgStwBa7AFbg64uoU/X9RUYfp/0eb9P8S6v/nUP8/mvp/wYsW/R+399f/qc9T/2cak/5fI/7FtmfS5ZDerP+fLv4CZXcmXRzwFIkvEX+JTp/qf84cdf/jJT6fuj/pW9D9333RWfdf3kbdH3k46P6QlZ/uL/Lg93D+57LlWc5gC+j9f4feP0/0/juP2XTqKVndV7puSI34fPzHIwJ6f1v1fulzwHPaofenAA8AJgKPBg4I6P0BvT+g92+V3v9QQO8PXIErcAWuwBW4OvTqDP1/TP7CCndVhjEFsNX6v9uk/4/uquQ6KNhzhvuewI3Q2RofF/0/N2fy7DH5uZNypkzLyM/ea+JkkJjsc7hxLKDW/5lmlLYZkvKE4b+R9vlc6mXxnxjUQ80K4ho/82he4++pvPnkij8G/ixJN4U2rFzqOvHfFbRIhQU1zy1UFpYhQ9jGEZ17gtD0DaYdHuY5T/G+pOd9aftqnKTpL2lKTWkidJrSqiLaIylD/B9CHxvUfAY+0/Ace3x7Kfd7R2zCeCzZg0TPjyRJ+gbTOfjW9HFMr/dCeIqr6TN96JNc+tx82nNpps3yoR3cnDeuKp15LOdCPpWyjQ0ahi8x+wTFmOZMFrpBqeum+5OgQz1460aJf7+g7ghrTrNkkaRh3ntK3sHiX4Ike4k/NLi7pj9I20O6RfLbxxVt+HX+eUG3IMygT6Ytr2ie2z9S8qoPKnYVuSIkDBw/bYTNknoeDeqpQtMr2OC/QexKlcCGcX6Vu8xTN/u6ECI0r4APkScut56nGipxaZJ+XRyijLqtWuLGD5FtrtSxOe/mMyxfkLTFQSGqh22/MNKV9BWekKPk57FRxvMtN2CwORftPTyo5hzDMlNI2HZhg40f3ZW/TSragTpZ8u9Hv7f/9BH6apEf+wHr9ASJTxY7TzMwFxZt1EiCUhUQdiWcgVVw1XCH0h0Gt4xhZn+V2XEObbWyvSYbbaO72jlqpcyDuWQOrFF5bezIWCP7ZJr0XJkeO4QWhea8mowFQhvqElqGNdNG6nCjTwut9Df0VYTpvirhSZqW3YR5oA9xbg99zbSHB20CYbpNaFtDqFe5H0ItdhpXhtIWB+dgC+G+QdvJesZ+DM6fnT1xpPM4zHSD9ThTIv7JqoUxl2l21HbOisSfo/zGV7bjhRI/S3F8ZfoU+/GV7apAaKaJv1SnSfIbX5vHU9JwzHKrlsfDdB/6Zcp5PMz0oa0xaNHWg4DueNgVYVvNaoMdM9/2mefQPguUf/ssUfbt06382+cyZd8Oa5S5Hfqcycnz264Ez32BJwFfNM7wMbetQzPQvKY=
*/