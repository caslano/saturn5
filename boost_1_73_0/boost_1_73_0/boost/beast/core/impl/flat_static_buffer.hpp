//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_IMPL_FLAT_STATIC_BUFFER_HPP
#define BOOST_BEAST_IMPL_FLAT_STATIC_BUFFER_HPP

namespace boost {
namespace beast {

template<std::size_t N>
flat_static_buffer<N>::
flat_static_buffer(
    flat_static_buffer const& other)
    : flat_static_buffer_base(buf_, N)
{
    this->commit(net::buffer_copy(
        this->prepare(other.size()), other.data()));
}

template<std::size_t N>
auto
flat_static_buffer<N>::
operator=(flat_static_buffer const& other) ->
    flat_static_buffer<N>&
{
    if(this == &other)
        return *this;
    this->consume(this->size());
    this->commit(net::buffer_copy(
        this->prepare(other.size()), other.data()));
    return *this;
}

} // beast
} // boost

#endif
/* flat_static_buffer.hpp
L24vhn50BPsLOAJxOLQVXiPYRd3FIGVmfiHNxAc12yhBguXF2fMN9MBGU8dG0lNHTlExYKGynzXFyvkPMpeTZZ2hBBq4ywnAjKRM2K9hohP/p2xyF+dC7wK8paTwcS8yWEqrO6icKBJalJQHuO2dpvFnCsRvX0GDInnVDb11ytwFFzgf40YtCpwT4QnF8umuts44VzrMbDkTwSbE0ybXKXrMr7qYfER8JxiU5fuSsmHiqorMFaOU0fxMRNcDlMI=
*/