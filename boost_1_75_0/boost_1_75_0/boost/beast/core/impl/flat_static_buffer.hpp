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
4KImKNWE0zvlKpreCt30ZtL0ok80zG5RUyhBi5ZChTTbvKymqTZ9mMM+Ytg/eXcbm0JSpJBObTpO4YU2o+Z/eztntlX9hBWtIVIz9OZyINtFUotDOpt3VLHcdC/Ox7DhSMuBDxqqWKbciwQeVsm4zIJRRm+6G9s9gx3+LmQpgt09RQykd4X8oQRXQARw+0Cln9yDpKv7vSRW+BLyqkOzmCZYDCwyUqdg+kbkIE+RIX+NuokA/fJ2dSP5oqgk50jdAsnwfn0KUvTqbUaawgagh4rlAqLy7xdJtRQXqUE5hGNgQzlFk7SspO+o4XhcebAikZBYek8utjH83gW7qeoLErw9e0/YNWBsmooIA0XpJuAxnN/TFoCWJBDqpVP+OcBJzOkB/7qh4/0J6IQ9l8whRSc4fWhw46p1B4qSi6R6d8CpOKS6OmcfFNbrnP0YaZr0fWD5aQXdSXIdZAsorcqDL4VtS/p5J/m/H+L1+L83eMf4vzd6R/q/j/PaV32Pcoq3wK9cErpo1fdDIbP3MswzEP9cgn8u9isGb1bryHyDL9stOU/gakBm5ctVwKx0dUi+E6G0VQpyeL4E/9h8gzQyf4PB20f035sroFJmstHfdE7EnQb6EBgJ+3gSIK1rVi2g3EBEufGtKXrrM3rEk5729XOKQnqGrRloei69DkcZ+APEIKV/t2UmbY+wrrwbaz+Cp4BTgE9ZiqK5UQuy
*/