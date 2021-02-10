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
VrT3BlJNDRUURoUnwGtL9cgo/WAHSPg/yyLOqwShb2wiVS+7PFhiw9SuoWWW4rpJX4KVTsQxMUxLLuJHuVwy1K/GleEMIkqxlLm0ZJPdfk0UGclm5Frn9R2+xk+VpHbvUOB179Wr3ik3XyzV2m03VSMLy5RFZ61k4rX+aQEMb+Zj6HLOeXMXq4QBDVy42+to+vG8Rc8c7oUbIhRmG8lC2o7HaTLt8LIHjEgnWBdCtM5z9IboQqywdrUwZqN0wlo4bg9l0NIr5UB8xzqdLaKb8Ho+Gfxx7UObYdqO6mjWbBCGt9M5GbFtMKZOc96/ZYnKZkpLI/iQAJlgYaXdQufrjDZJ0IkujPdMseEgHEeDm8WHP0eO2tnqpLHVoYR3SscIs/FgNHEymDCudTyPaTx9P5pENBtNJyFRMemFwzukcVbcyDw/MBu9juIB4az2/m57yHGNzOfuy3xMtKUqX9KhSUOvcWEvVqvg7FDEDHWqdE3FMnYEtbv2NGUdV5tonz7MMP4b6Amg1kqbXTrZjRF+2hvUa9U/aWmpyeNph15WSiGV33N4kFK1mLyFX8x90fZb3/4oHtRutaNlLu9A1SDfiK2BOEdRVOX3PWse7IoB+MypVD6d1OSwwnoEeN763PoCUEsDBAoAAAAIAC1n
*/