/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VALUE_AT_IMPL_09262006_1926)
#define BOOST_FUSION_VALUE_AT_IMPL_09262006_1926

#include <boost/fusion/support/config.hpp>
#include <boost/tuple/tuple.hpp>

namespace boost { namespace fusion
{
    struct boost_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct value_at_impl;

        template <>
        struct value_at_impl<boost_tuple_tag>
        {
            template <typename Sequence, typename N>
            struct apply : tuples::element<N::value, Sequence> {};
        };
    }
}}

#endif

/* value_at_impl.hpp
QmoHkjj5cGTCHOBnf8JAP2fCzNQDnR/72Z8wws+ZMC/zcyZMydlhWspwpZ/TCtN1GnRepQc4Q2VJY/prZHlUX/9BlsNlSe1P5/Spw/VA6DlI9nNKYscCmwBsHrAFwCLAVgF7ANjDwN4AtgvYYWCfAKu1DLbcMtg6YOuBZdUPskIdPY1uaNtHiJ7i2hgZ6KlLWuY5FVfChdJyk+ZYllfEtCin94xjvPkU0i2BOu5j21zoGc/MPhSibySVZB8KNQo=
*/