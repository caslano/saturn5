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
9GTLHdkq+z4IN6gloqDSWN1MEw4+Y/abqUF1MlVbnPJFGkOfLxrHcJ/SaQy68+rOXi0jBe1qEE5Qg4R3U1+AJWWQU/bRfosx2/cxWsKGHCj+3QPkAhEWGa0Ku7wgOZyrobCSkeEiZBfveLIyvTvsYZK/IOU1iJbp/b4oRuW1mN/J2Byte24ewJlww6s1i9jOTu929Gh8j5OxAbwXeB3dCxxG6AGHE8oT7+tchX/5gJnNEp+4NZSMR8U+aF8J+zDg1tDOb2iWUMRev209S1dHQItroENpoI3D8xwIVnvJpVqv3NNYjxaCBnqyerl3XFBPxvGeOLgrQ2wkObgXvZU2BK4w402EJnMYwFC9chsniBwuilz6DQ19rB62WGVorA62WQy2JQDbE2oInUkquaiuo+mEoE5bMHgj1zn9X40d3O+6+8HM+Ed3L2XC/QifejZA0EEDyufv66Br7bfN+prhz4Stuvq545I9N8Ij0QO7EE8CwpDmG2RUAc9ROnVjgOMrqsXTxjH3p+ooOY2iuufYlxuXGt2tdKuBI/9Hd1tGj3TmwHigcmiQ0cAmqW658e8NYdYkxgmnVaJuWiWrb5NDayP52shWqkV7+UolZLXglaocWIzwOLPUiSsV0Hz9lap8PiwEp4tpIXA8R8+b+fPbYlwY9vDPl/PX3fjzEnjSgjJrfqi1g1Srpsh71bWDjmBOw2GbZJcPoOMarhnC
*/