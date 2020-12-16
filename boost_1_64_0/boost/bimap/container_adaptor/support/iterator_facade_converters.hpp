// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/support/iterator_facade_converters.hpp
/// \brief Converter for Boost.Iterators based iterators.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_ITERATOR_FACADE_CONVERTERS_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_ITERATOR_FACADE_CONVERTERS_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

/// \brief Utilities to help in the construction of a container adaptor

namespace support {

/// \brief Converter for Boost.Iterators based iterators.
/**
Container adaptor is dessigned to play well with Boost.Iterators. This
converter can be used if this library is used to adapt the iterators.
                                                                            **/
template
<
    class Iterator,
    class ConstIterator
>
struct iterator_facade_to_base
{
    BOOST_DEDUCED_TYPENAME Iterator::base_type operator()(Iterator iter) const
    {
        return iter.base();
    }

    BOOST_DEDUCED_TYPENAME ConstIterator::base_type operator()(ConstIterator iter) const
    {
        return iter.base();
    }
};

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template
<
    class Iterator
>
struct iterator_facade_to_base<Iterator,Iterator>
{
    BOOST_DEDUCED_TYPENAME Iterator::base_type operator()(Iterator iter) const
    {
        return iter.base();
    }
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#undef BOOST_BIMAP_CONTAINER_ADAPTOR_IMPLEMENT_CONVERT_FACADE_FUNCTION


} // namespace support
} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_ITERATOR_FACADE_CONVERTERS_HPP

/* iterator_facade_converters.hpp
mXAmnAYXwXPgUjgD/hTmwYfgbLgXFsIP4HmwvYd2D38A58BJcD7MhWXQNx9U42N0DasOmQ9KAPNBAYyBUTBObnte8E7f/hdrf+c83gHodYapsACmwxI4GFbANHiB3B/CtchupedtxRcDVyu+Duh1gPGwO+wEj4cJcADsD4fCrnAKTIL58FhYDHvAi2AveBVMhtfB3vBu2AduVDwPw77wWXg8fFH+mt+tcRTso3Q653e3Qs/LNrApbAuTYHulO1r1pB3sLfeHMNfSmAQ4U/G2gBMUbwV6sXCR4quCw+FimAkvgqfCJXAaXArPkb/ON9/3w51v3DrfF+t8X6LzjdveP1P7d3PZ/3LtfwXsCJfBBLk/hEf834nhlWo/Xfl9SPvvUn15Hg6GR+BJ8As4Fv4dToD74CT5z4BvwEL4FrwYvg1vhu/AO+C78B54ED4H/wLfVTx/VTyfwo/hl/ATSF03/m3hizAW7oG94e9gBnwZjoC/h6PhK/Bc+CpcAvfCH8EvlH/L/kZHXpX/bt7jOuaNd4ar4Ui4HZ4Bb4Bz4Rp4DbwJroe3wfvgWvgSvBN+BH8JPcRNnk3674Xt4X2wK9wI+8JNsB+8H2bBB+BUuAVOgw/BIvgwnAMfgXPhXXAJXAcvgo/D2+GT8G74FNwEfw0fg0/DJyD5MeWw39K3Fjhb5eDN916Vww6tA/y8ymEPHO8NhxPhy3A6/D3Mg3+E8+CrsBz+CVbDffAy+DpcDt+Et8G34S/gAbgJvgM3w4PwCfgXuBO+D7+EH8CmpPEF2Bt+DE+Bn8Cx8FM4AX4GJ0LqudqLvgnAJJf2cp3ayyq1s9Wq/7jN/qmW+tLhIO3fBCZr/wz0ouFQXf9O0X4HLfVRw3KVbxdTHr4tTvP6u8NRsCfMhclwJuwNi+Dx8HLYD14H+8PVcIDKMR1ugIPhRngCfBSmwh1wIHwOZsC34FD4N3gSPAxPgU1I23DYC5p1n2EWHATHw8EwW+U8Cp4OR8Mfyl/XFfVh0m/qcl2ZqPxOg8fDs2AOzFW+z4Y/hNPhRfBC5XMJvAVepPz+SPXkh/BJzZt/GubB38J8+DycBffA2XAvLIB/gEXwHVgM/wJLlP7z4WdwrurZPNgOlsFYuAB2geXwWFgJc+AiRz0rq6OeLVc9u0b17FrYWW7bLkQdzwHNtH9z3ReOUTzNtf8af18JjDblD73H1f73oNcFboTHwk16LnpO1/ctuo89CKfDX8HZ8BE97zwGb4RPwq3wKfhH+Iyu48/C9xXfJ3AnbOExbuVP7/lh8pep/I1U/kYpfyOd9706yuefspvxBYyBX8I4uXVf5702/H19je7rN+u+fovK41bd13+u+/rtuq+vhefIX+nj/TB8+u5U/u5S/tbBOLkrmvnsPjxWXr99hwnzkWHM6Uf8Nh4Ozw/YeWh6ClKGTQMkB0nGba/J/nqUtQa/GsRv/yH5zabWXtwT0CsNsQVxpKy2PYg2w6FXFmBfAClA0vHPHM5+/L4TmcHvrTCczYh9CwJ2I6LLfbYjduH+GEnHPQEpRVZ6w5BDSMYI8oFMJb0fo18Fl+LuuhDbEbwo5iJeuxPL8esLx+C/Hh2nDYqmb2B3AW4gbBl+e+ER5MCIgG2KppmkqQLbCojfTkUKfvthZgX6MB+G2KzgJHJsh+2K1Dcc9isI24bfK8hub7pJq9+mxZEK/GF0JXEhX/A7E65E5wv08/nddSSSSjz8Hsbvqchufh9G/DYwEi7gmIjfDsZUfrd4q2mQPYzV+C1Htwa5E/demIJOqI2MGfjtRvcgMoN8HPKGL6IekqYCwi9FUnHfCXcih2RLYxfhxfi3GYiOl6OxewH74t4Gw9nYOEg=
*/