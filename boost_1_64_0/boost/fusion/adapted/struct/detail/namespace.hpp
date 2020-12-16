/*=============================================================================
    Copyright (c) 2009-2010 Hartmut Kaiser
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_DETAIL_STRUCT_NAMESPACE_HPP
#define BOOST_FUSION_ADAPTED_DETAIL_STRUCT_NAMESPACE_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

#define BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_BEGIN_I(R,DATA,ELEM)                \
    namespace ELEM {
#define BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_END_I(Z,I,DATA) }
#define BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION_I(Z,I,ELEM) ELEM::

#define BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DEFINITION_BEGIN(NAMESPACE_SEQ)     \
    BOOST_PP_IF(                                                                \
        BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(NAMESPACE_SEQ)),                         \
        BOOST_PP_SEQ_FOR_EACH_R,                                                \
        BOOST_PP_TUPLE_EAT(4))(                                                 \
            1,                                                                  \
            BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_BEGIN_I,                        \
            _,                                                                  \
            BOOST_PP_SEQ_TAIL(NAMESPACE_SEQ))

#define BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DEFINITION_END(NAMESPACE_SEQ)       \
    BOOST_PP_REPEAT_1(                                                          \
        BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(NAMESPACE_SEQ)),                         \
        BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_END_I,                              \
        _)

#define BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION(NAMESPACE_SEQ)          \
    BOOST_PP_IF(                                                                \
        BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(NAMESPACE_SEQ)),                         \
        BOOST_PP_SEQ_FOR_EACH_R,                                                \
        BOOST_PP_TUPLE_EAT(4))(                                                 \
            1,                                                                  \
            BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION_I,                  \
            _,                                                                  \
            BOOST_PP_SEQ_TAIL(NAMESPACE_SEQ))

#endif

/* namespace.hpp
uEZnNH+B18Dm8vvdRn6/h8rv99Hy+23q9waTHrwRPiL/3yvk//tN+f9+D96ms5NzAzqWGntByR/Vn3Cd4rWrJ57GMZ791htP4wzluzYs3tBg/8ROelHj+QgLFe9rF536u/R85sFcnU31wvvhWPgAPAM+BK+DD+tM06NwqfxvfwIX6fkshouTY/MD/GB57PpfmT0Tvn//Dp2vePW9YtHxitW3UCx+hf4qf78N0eOqisOPUEN9/Cb8+264f9/ZzyIHYSUh+TnkJwwkVBFmERYQVj2X0HVKXIkrcSWuxJW4ElfiSlz/3SuZULYJ9v9L83yVtgbAhukA7I5tw0IWmhYOMPtoOYMHDug70ntE75wcfOlj832it6rKszdxuhm/XYdFxhnqLa4qLCWW/ANO7GDkSQnxD9jMhrXul0Y6KyeYdZTIhGLxQWV8E2aSRo4lS0l5fl4JN4buBa9OcvZ/ttb+z/bG/qDPJd967QWH2gRsZe275YX6FWrkXs46t3IaaeMop2c95VyofNsStpQN96eMfxPXcmJ+NQb/LcF7V8ukM7CS0F5rrvdS/sxyK/3iTpO8Yc/QTn+de/p9SZR2md6K9KjDJGtvyZMUrrshu49JAT+HVryUJGsfVDoWJcWVVdSR9ETKt9F+sNEV6OjssW+fbn63XhVX+5d6noojXY7w9DqF1kl2svv+cp1v4+8vB2w9J7vv53ombpr93D6So1sTne837U3lfzqD9hCQI7LJUQclJTHUQfD+7TyXPfwhPMvRUfKJt55z0lXmsPL1c9nHH0bc2ij5NmQvnzYZsZffJsTOb2hd1LnItMT4vYoqE5Z+GyiPnj/vhLut31EuegVHcX9Khbss8bbFnPT626L/nZiqzvaaRnb7uAI+a3yr2H3upE7F4X1TLHZ+m7TKL3P01aTT4qpbNh2ea/twrarRb7Uh+mbaZ3fphzLD+qHcsH5I+/uOnksn6esE/6Z+LjugS2RlGdiXX/037stfYO2bt6xrMX3sHu/3+vaRLvdtVzqgKPr+u/u+efR9efd9/3/ePrv7fnq0/ff499nd9Rzi11v4u/brb7f2669o+fB7y68Zd9L0lBW3r/xqi68btl+f6tG4UuOwOcE2lbRPq3gaB9KPucQ7IHg/cj3p7RW8v6n02q4nvSKPxk1GTsVrDkcpXkftT3eSLdaDtX/YDVbA7nAGTNe+bg/4GMyAC2FPuAT2CpZfcu1m8kyKvk/qmaj6WG88fef1HVoXFq9JUlD9TlS+9cSrVbx29cSrizEe3yGVI3q8fZP0jdC3Yw5hdzPGSNKHQLY7+sK9YD89lyzZshwgG7mHyWbl4bJZOQjeAgfrueTAFdL/+Fn7yMZG0zDYHx4FR8ERcCLMhdPgSHgjPEZ6GqNM/cPj4K/S/0huRB3DfWEe3B/mw4NhAcyChTAXjoXj4DjpbxTJRvF4IzecAM+CJXAWLIVXwDL4XYz7z6OWGsNcxFsa3z70nvck9qI3ZC/6wfK/dz+63z3/zj3pgns27r50DemdbtK4Z+PtT8+7J7FHvTH2qJcupc4I275AvoRcwhTCbMJCwhpCyouUl1BAmPFiYr86cSWuxJW4ElfiSlyJK3ElrsQV27Wpzv9PqN7w8/97a+/fl23t6x+eNdI7fGjv/lnenKwhAwb30/a/va9f3METOJM80GV/fYHZkxpv1tUiE6p/jyx0j/3hjMg99sVRdAkWRsuzuCrmPfZ52RF77IGy7uuyx/4o8qVMcM/X2maPoazBeSxWHj2119mNsNDsq9p5FLCXFZFPLHn46/Mx1ad/T22c/EF7nDPu0PzGAdEw2QY2lg8brfu2JywyPl4nSAegYMNkezhMtvE=
*/