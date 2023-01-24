/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_VECTOR_FORWARD_11052014_1626
#define FUSION_VECTOR_FORWARD_11052014_1626

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

///////////////////////////////////////////////////////////////////////////////
// With no variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
# include <boost/fusion/container/vector/detail/cpp03/vector_fwd.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

namespace boost { namespace fusion
{
    template <typename ...T>
    struct vector;

#define FUSION_VECTOR_N_ALIASES(z, N, d)                                    \
    template <typename ...T>                                                \
    using BOOST_PP_CAT(vector, N) = vector<T...>;

    BOOST_PP_REPEAT(51, FUSION_VECTOR_N_ALIASES, ~)

#undef FUSION_VECTOR_N_ALIASES
}}

#endif
#endif


/* vector_fwd.hpp
WyGAowxeHvwH7slaSg63NvFbiRDvQruX2MRcjTpsmCsJ4Syvbsa5GnQY56rz62yuuj/A5+rd8Lm6GuZqakpV6VxzjP2RKslfbA6ZqLKPDBN1kNU+bHMTE3XJPyETVX2IDWbHFm2ivnuBTVQ2A265uYmJ+uZvnKiwWfJCHQuhjuAmbZZmwMs3/8ZZmnSo8Sxp/gUG96XkHPl0jsickSk/mBlB7ga5/ov2ZbO9l6jc3I4il8D9Y3k5fR/KpqhDjUtuS7d8OrK9tSIbbh7Tneu8Aj39W7TqGL3dapKfy0QWvYHie52EqG2Ub8nmkuO+Ndx+dPmu+1ZdAqWpNflxiLuX/vGCHt4dCT78IfmXQ7wIJRA4qdJnUL2/gl8I4h/BCNFw1se4/S6fHS/x2bjqbYgvlEymBqZUj/8his4CEkaN1iYG4h+l65dbc+TjmFjgqCQfSVHTNkI7CydLshcHlHZVgydb3FUdDC038HvriTzeCEPK7TmyPbvnbiZHD7FviLI5e+4Dn6CqiCyGPEfLD7j78PnqzoigWp2+GZpY8AzY5/j11g/KiaYVab0HXgBXmOS40y4fBR+w6blLWF1fMgmKSMvGPcb1HwVJVPzTu23Ub88t6idE1r54W8qysBLlVBWEQZN3fnuTpyVjqZCCSJn/u6oG27J3TEygCN/0PshYCmVcfEhYCUrwjxb2sglC0sjEP9q42+Ov1SR34C+3
*/