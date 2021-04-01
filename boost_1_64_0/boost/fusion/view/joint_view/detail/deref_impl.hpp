/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_07162005_0137)
#define FUSION_DEREF_IMPL_07162005_0137

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/detail/adapt_deref_traits.hpp>

namespace boost { namespace fusion
{
    struct joint_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        template <>
        struct deref_impl<joint_view_iterator_tag>
            : detail::adapt_deref_traits {};
    }
}}

#endif



/* deref_impl.hpp
JtV39x3JUQPx8a94tDlg0kyLhEOeMwW3PSMM/f+Hf4gsqPIuXCgVsIE1QurFa9X5i8YziiHCThMbLPb7z6tnKpxfkug3LwsXXZeg+1+itfpT8UlasoX+urqn5Z/7OkWdwiL4aBCFJPGCoZn+HZk3fTiSXHKIvD3oHcdKE9eVlKRltBalM/+zY9zU/HaVTNL9qhiBryv0MWmZp4xi0l6YcJFfjUBD2LwQOoWop3SiKzZY8FxczVGmtEKo1K7NVd2CJTkvegtlS1QXKYr+UPrWg3kyJCgf+DDCoIcRp0TF5gfkX+d2Leu4Ry5JX+LBIB8iCDuJBDhyVrSavhGb+Uef4lGczB0N/+dHuJAaBLK3HGh21EqAQnS/9mWCKI1oo9bWD0BlooiymJMqgse8OlwBAYxxjrgm0K+dtdszMiWN8TLAEVBU5rjA4Vn5uqQ8/G0A16GuT3ptxQpDMkaUwm2UQqKuWlm1QYQlEeL2l53DdMaZ8EEN3zNR4Wdlu1w6ClzwPx9Q70Y+lL3lFnm0B86NXo0DypYf3B6ZjhvGdZQO7emXUoaGURw+k0IXiw==
*/