/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    remove_rvalue_reference.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_REMOVE_RVALUE_REFERENCE_H
#define BOOST_HOF_GUARD_FUNCTION_REMOVE_RVALUE_REFERENCE_H

namespace boost { namespace hof { namespace detail {

template<class T>
struct remove_rvalue_reference
{
    typedef T type;
};

template<class T>
struct remove_rvalue_reference<T&&>
: remove_rvalue_reference<T>
{};

}}} // namespace boost::hof

#endif

/* remove_rvalue_reference.hpp
geeyswDK8nc01vITmx7vI5/EtknZCxqV1HVOQslIzFiqxYttIOpCYdKT8wKKsnBk3UZydFudMK2F9AEFP1n+rEvwRdLD8Mdcor/VEhNPCceTKGv0vS0tSovWeh50x/mTWMe+c6NSAsGZF95fIf/BM7DsBbS2Bho1/KqZUlfMZcf91hgWG4K/speS5ajpz8ZYdZPEhnySyXtRwiKfGpN0F1G66xqpfV3SK26ThfZkb+pAP0h1JmcIq3WVEXdy1nQ=
*/