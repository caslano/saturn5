/*=============================================================================
    Copyright (c) 2001 Doug Gregor
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_IGNORE_07192005_0329)
#define FUSION_IGNORE_07192005_0329

#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion
{
    //  Swallows any assignment (by Doug Gregor)
    namespace detail
    {
        struct swallow_assign
        {
            template<typename T>
            BOOST_FUSION_CONSTEXPR_THIS BOOST_FUSION_GPU_ENABLED
            swallow_assign const&
            operator=(const T&) const
            {
                return *this;
            }
        };
    }

    //  "ignore" allows tuple positions to be ignored when using "tie".
    BOOST_CONSTEXPR_OR_CONST detail::swallow_assign ignore = detail::swallow_assign();
}}

#endif

/* ignore.hpp
jsF+mInxOBkTsBD74w84AD3qqfdU3YMD8VEchJtxMO7CJPwYh2AAH2YyBuPN2B2H4Uc4HEv4sqXgehyJe3EU8j3h+yPHJTleKakt2U3q5hcwnTfeg0F4L0bifdgPKzAV78dsfAALcAmW4FIsw4fxr7gMt+JyfAsfQU/WtQJvwpU4CR/FubgKX8XV+CE+hs34fj2BnXENRuNajMN1mInrsRw34DrciG/iU/glbsbT+Ax6sd9bsDc+i3JvnfnYwzHp8nvrRku5pEu5TMCemIHxmImjcSJOwiychpNwJk7GeZiDa/BW/AJz8QJOxR6sPA8HYj7ejQW4AqfhJ1iIZ9CIbuzPdGyKxdgCZ2AUzsRUnIXTcTY+gKX4DM7BbVimLBdvR+UYXI5emvYCI+0FS8iVeruBnvSkJz39V9MfG/9n5GWZ/plE/K7UAPz++P+QJv4vkWvR77Azfo4PhxILnFfj/7jk+HRlzel5GVOz5dn/Mrw8udzRWPr+i8RkF1dLGz994jGcOX2SwXo/v59pmqKcWdnWa/FppumKMwrlmt7DMm+RxHvWaXL5uwXjWqHRtKzpRdnpUk6yTIPEAMmW9w/UaLRNnm2oTf77d+yj9RpfllM0S67xLdMr5/RleOl76/SB6KdZNtOzzT0bxcgyl1OGyvAUu+FFdsNP2w27sA7tcLwMJwepw9s1w6zT8jkelOujxmxrIP7ERCtYRuUP1s8xNz8jy/Rhyue4UGJkZ304FripfTjWpx7iwR9Ny/HPLixU+2FwY8BUB2Et72VuqD6nMdOYXWSJu0ob2dZVxOJeX2VcUaaM08R8hdnaez60caCvJsYz9zExrjPD8t1SymdwtVo+o1qqw6ky/JiU5ysyvEaGm5v2i+XK9KsZlvltyjdILrU2KYWAS7AFF2VDf7KW74zCHGO2qYCvvXzfvHj18g3UlpHjspT42Xm5NZPPRJbD7yWdVUpfFPJZSR2S0zJeru6z4UkpQzd12w3rZdgow/W91OGtDGvLNMzQgLVQllKmw6TuKIm8hz8K1Jg5vchYyI+LOkL5vvrg5cnXct8R+yllxpz8bVu/wqI0sXuqK9vfQIm97nk7em7gmdzN76xNutln3u4PnL3z4c//7g7H7+hw9k4PZ+/ucPaODmfv9Pjvvbvjer3L5YCpjifjxU/+0SC6uku9/v0Tvirfs9v5O16U2PWUQc6hcm4NJLfg7yPyrW3pQuyMrbAbtsZe2Ak3YhC+iSH4HnZDdxbWHSdiJC7FXvg+RuFhHIRf4mA8h8noybpvxpY4DINxOCbgCEzCFLwVR2Ip3oIVOBrX4Fhch2n4Ak7FzzEPz6nbKecaOQeR/fibZ9BIaqwciLPRdE6QWH0OxuNcHIzzcCTejuOxHGfgfJyLd2I53ocPYQVulbqPF6TuYw8uxU+kbqOW1G14Sd1FG3wcB+EaHI5rsQjX4Sx8EktxAz6IG/EJfAo34yZ8DTfjPnwa92MlHsAteByfxX/iNryAz+FP+DyeM102yTlEzi2Baj0exyg1vch0/vg3DMcd2Bt3YwruwbG4F/PxPZyJl3Ae/ozL8Rd8HH/FJ9GVz+0ldMOdWBNPYi08jx7yfauN9bAOBmNdjEBP7I31sA82wJuxIY7CRpiKjXEceuEUbIoz0BuXoI98fxLJctw3nQ+qlG0iR0s5HGS7G+MhbI6HMRg/xgQ8gkn4CR5xMVz1fS/VZK+oq7/35Ua/8yU8Sn3vSzzav/vlWLGr4WzxH/cOmNiZN/49MAejrv4umMVcfG0iv00+HaTXeenpfyvdmPg/fUZO3vWJ/z/QPOefJOfnTuSW5JvI5aEcx7+1xjXZxdl5RsNvfw+gvEd/SBE=
*/