
#ifndef BOOST_MPL_VECTOR_AUX_PUSH_BACK_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_PUSH_BACK_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/push_back_fwd.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   include <boost/mpl/vector/aux_/item.hpp>
#   include <boost/mpl/vector/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct push_back_impl< aux::vector_tag >
{
    template< typename Vector, typename T > struct apply
    {
        typedef v_item<T,Vector,0> type;
    };
};

}}

#endif 

#endif // BOOST_MPL_VECTOR_AUX_PUSH_BACK_HPP_INCLUDED

/* push_back.hpp
+gPi9yrk7F7W+wjWB3GbTxrreTbXY+9yMrhuJv0ejl/yi2q/D/bVwQ5742hW/a2Fx4F3K76OerN/4CcS13VP4f7F8BGe6OMRtB//zwueLeUL4mjsc40vdmcrvPJj6KtdyKcV8qgn7ug0qfsEwHvz3NzZluo5+1nnY7nvvfhFH7G/90b0XTj9eR95foY42oL+f0A9jj/9CtMh99S7og/N+O/JJehFJ/i3KvJa1zBObvBDZvimL+BhryduCLDAX0QPHkL/rINnnEW9yW7sPO1IK8Sfbcd+DkLuTNTp3Uj9qCPygd3e74mf3sI6P8Q6Ic5fFYz+iGMf9Ff4G+HwgXvg88nXthyFB38QXv8I/JGnpbIHZeSVn8aObMRO/4D84Uel2dP+5ezTiMLP+go/fBbr5xz1D8x78r06/Dj2rS2F9ynFLl3HPB9j3f+qxuHYm9SLfK7DL2FekceKeWbVjrvgU77VUx/GunejXRr/9SN+7E3cz4067J9NSk4LmY8FrHfydx3XGZWeXYNe+xI/jDyVDX5SVwT6eC38F7xBVzI8xXXU6VHn4BDPvsAHmMcP8F9epR3EMfnwNzUz4Bm64V1SqF8cyLwMhV9lf2aAM7zdGOzhWvi7jv6qPc+gVzYgH1Pg86i3zmWfYjH+XZEH8Tz7/PdvZr3UIy9fMa7wbmk5rJ9E4pkbyBPr8XOHMN/VPH8n+zJup17gNurnPoSXWok8T2JfzBHq2R1pJ3xkehd+Thzx8QT05T/YL53H+qL/oQ9i/6wt1PNWsr7cqK/UEYfQ/ko/+NwGs7ovdqcRu1OCfugKJa4grvTgecnY127qU4+Uqd9Fv846OMynDXp0FHxDNXYugPwR760ofhe+kbhWD3/iVc3ndcRpb+L3wxPmcr+OUvgT6kS6TjO+7xJ/a7z7MvZbUzdU4AU/FIe+o50BW4hfGO9w+l3lBC94LftCfeFd5mt2mbpMnleRyv2J3yrgu20WE++TZ9d74dc8Sd5iJnUdK5n3P9X3dsQxyVcx7wuIJ4tZ107kz/zxK/+JPltGfO3APg9beHp39o0N1WPXsauPEuc1kPelPiTdjnVejR8a3Z+8J/7GLubrLnVd99vc/zh80A3oh32aHYJnGIGe20Y+0pl9e8T7SfilKe/AI2+ADzmHnxdqZH8Z43YY/oR5sSUPn3IL+3jZH1p3G/b3beo2DqJf4RM6kvHHH2W+2J+2/074I/KmNcfQL+jDTjvs+Ej8Zl/49pfxv46T93sDuxeI3u9H/m0AfpQF9Xoj8VPvpz6Ifa0pu/FDEgcQh1rih7KP8mHydLnUCwykfzew3yORfGAH8oQf29IGv2BhSVxMfE7eKOkP4j3We0ILdhQ7XzMZXgge2e81+GrGo/JL9ODH1EW8wPOfQ79Q91F1ivdINOD/VhB3+sIfOJK/8KWOdgrrJIF8M/x9lQv244z6f4U/88l4lWDXG7Ko/9yAPzkW+YIf9UvG/y8jXrwNHhf/oRL+1WcV/lAZ8lKKHqzWwbuyPygavTOQ9r1owr4Tv5tZF/DyDS/g707CX4MfdOF+XviVtoXohRHkmdZjl5qRd/bNlRJvph8mz5mAvV1PndZo6s1cWXf4J3boFSdf/DHq5pyuwT+mPrZAy0sdZD3tp/4qinleyz7yGOTxdupcH8X/Qm9U+ZDP/4N2w9c7L4eneAK5Gkk8zLzmEy8VE8/FTSAPvgM/BP1q60beeqOO+BceOl5Pnpq8laYn64jbsC/7Q7V6MfbHbqffyYynF/xsG3U8GdQVWpGPOYN/+TzxEOPs58V43ER9B/v0l7GuSjT+r4n4zR/eI64ffB5+STp28wR6hXXrNZ88Yxnf/4If9is=
*/