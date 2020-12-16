// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/vector_map_adaptor.hpp
/// \brief Container adaptor.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_VECTOR_MAP_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_VECTOR_MAP_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/mpl/list.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/bimap/container_adaptor/vector_adaptor.hpp>
#include <boost/bimap/container_adaptor/detail/identity_converters.hpp>
#include <boost/mpl/vector.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

/// \brief Container adaptor.

template
<
    class Base,

    class Iterator,
    class ConstIterator,
    class ReverseIterator,
    class ConstReverseIterator,

    class IteratorToBaseConverter          = ::boost::mpl::na,
    class IteratorFromBaseConverter        = ::boost::mpl::na,
    class ReverseIteratorFromBaseConverter = ::boost::mpl::na,
    class ValueToBaseConverter             = ::boost::mpl::na,
    class ValueFromBaseConverter           = ::boost::mpl::na,

    class FunctorsFromDerivedClasses = mpl::vector<>
>
class vector_map_adaptor :

    public vector_adaptor
    <
        Base,
        Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        FunctorsFromDerivedClasses
    >
{
    typedef vector_adaptor
    <
        Base,
        Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        FunctorsFromDerivedClasses

    > base_;

    // MetaData -------------------------------------------------------------

    public:

    typedef BOOST_DEDUCED_TYPENAME Iterator::value_type::first_type  key_type;
    typedef BOOST_DEDUCED_TYPENAME Iterator::value_type::second_type data_type;
    typedef data_type mapped_type;

    // Access -----------------------------------------------------------------

    public:

    vector_map_adaptor() {}

    explicit vector_map_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef vector_map_adaptor vector_map_adaptor_;

};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_VECTOR_MAP_ADAPTOR_HPP


/* vector_map_adaptor.hpp
Ubd3bX6q1PUup+/J+zBx35P3V3zfk3dGbN8TNWtPKM+oWRtjatRFqRHgiHvQNSe1rLBdhSv2bO3i9o49ATaJ94avcO5F69A57q8m7Lv2x1jC/uuI10L2VmRG2thPTX4LLWwxaWT9Cbl9WtJ1zr7A1uBl7vhh8p6Q+k1uP+Mbu0PyFPfspkteV93WeV4D/hCSX4lKpB82Fr1wO7vM/B3thiPwZkh+QjDbyQuqr6Fw/FbvNPqWb9gZWh73znLbiObm3prA/EBr9W0j9schD7cZx1l4vlK/b6u2dYG5UZQZeUdfbWEqcOMfNP19OsPATSc3fOUWvu8GFH/5d630GZ2a/Ov+41i1X5nmx4/cMHzwarh/3VnxXG5pvjG9tZPOtxaLnGnBaufspOXBP6ZcG1Q85c83PX1jhVV9nm3+fWO3X/ZlC8PwzEh5mGTp8BTuZJLilU6kP/YPc/OMjC8n93Hap5warEjr7OSoLKwyO3dSOtbr/RYJ15HR/nZcuKjj9c4qyFV/66dvh8xVMVZIChwTOCran45zY0eiPrv6tx0tbhvdcldo6Xl5Up4zBREu11NN7Z30E4jvCKdH0sqkc1LcvnScfzsP0H/fBy83Pwe7efrEHvWhlb5nm/5Y1atIvWkd7VPH+bk7Qf99P+aONbeud/3qavIs168Xze+Wkssv9N3+cZxfexL03yfDk83tK9y0PMHk/ZPTaJbzVF5XW5vwfuoi5+nA08FvBx5OPsodn+a/FdLbgMrrSRH/J8f5vy+2f+72RU81uzcgl1t/MLcsbLsxmWP+/iDd23fPU1mq+J3FOekE50hSvSL4ePBk9es5CcXq8Eup2c4tqfF9927qq0+2eM7K3BC417ktuDEwMfmN4E0ZPZ3tGUnOrzJSnDy1F5dZGL+V9Ayu/91ZEPxGUlB9LsJr9SMzpZvzWnKkb3KrlbtOGZ7+uTsG/JPpvWjxWWTxqbS45/DriD1mj3KInF/brK5cGuzh3OX82VkRqNef15igj6XR19Lj+9+RsrP+9+jT8rRQn73S4j0l09NvNr2d/Cowt25O9/SZXXcmm14vN+8utPAuUz8/8t64lHyukZlIuVyDPDw+mWZmyiysXzf3qyxTOmsu71YLW4fMQYFfBtOT+6acTj6Mz+jurMg40tywM6TNzNGZfv32atxYYeVicGof5+bkJSlJzq0prdyzA641u8d74l7jxm+4ha21G78X3lK6qc4lWX60cc+M/LqZL0mrdNYmR+r83/TuzIkrzyn8RcY4PZUmkbmYMWZncbraOx5r7+ycj0idbG3hPj8zy+mdGdu+9coIt29fSX8nvbs7F1Vq5qdbGj3dNnZsgUa9MUQnpf9vzc1J6b8MssGDXGqZnuoUpqfUG0+EnDzdyv6pgbA88l5Yp7nasJ92yIfn7I53LFxJ5JW5oXZlB+3KTGddcEDw1eSO7njmvXD9TO+TXBXMMfOR+naz1bewOY+a6uAk3P272X00o6FxzQQz81zGM8E/BXI0rim1dmNqWoqzjXbDmx+OO14eZfYWZXrHOJ3VpuwP50n6vXwlemcw0ylLesz5ekpFsFt6UHMESicrD6fRt+SxNHgkPX6cU8SveebXOZnRsNDT8Zwv85KFt9qJ7zP0CUzNPhNzrbLD4x2ng80T2xxxSZYJG/vcf4DxT/z4w388FDv+Kc46vGOgH8KuxOMoj6hqa+7VGwthXuOfeOrMOAnv+C1X57lMPsAYqdAzRpr1dnSMlIOccmzyipL51fOWOWamaE/suGmDd9ykM0nucMc4Y02+yZWfpXFV/fHStgTjpe0+46Ucja885zZpbOU/htrdwBhqj88Yap/PGMpBjTbHM15qll0=
*/