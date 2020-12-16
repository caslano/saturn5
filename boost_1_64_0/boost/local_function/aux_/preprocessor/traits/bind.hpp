
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_HPP_

#include <boost/preprocessor/tuple/elem.hpp>

// PRIVATE //

// Non-this bind is 2-tuple `(name_without_type, name_with_type)`.
#define BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_INDEX_WITHOUT_TYPE_ 0
#define BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_INDEX_WITH_TYPE_    1
#define BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_INDEX_MAX_          2

// This bind is 1-typle `([type_] EMPTY)`.
#define BOOST_LOCAL_FUNCTION_AUX_PP_BIND_THIS_TRAITS_INDEX_TYPE_    0
#define BOOST_LOCAL_FUNCTION_AUX_PP_BIND_THIS_TRAITS_INDEX_MAX_     1

// PUBLIC //

// Expand: `[&] var_`.
#define BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_VAR_WITHOUT_TYPE(bind_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_INDEX_MAX_, \
            BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_INDEX_WITHOUT_TYPE_, \
            bind_traits)

// Expand: `[type_ [&] var_]` (EMPTY if no type_ specified).
#define BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_VAR_WITH_TYPE(bind_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_INDEX_MAX_, \
            BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_INDEX_WITH_TYPE_, \
            bind_traits)(/* expand EMPTY */)

// Expand: `[type_]` (EMPTY if no type_ specified).
#define BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_THIS_TYPE(bind_this_traits) \
    BOOST_PP_TUPLE_ELEM( \
            BOOST_LOCAL_FUNCTION_AUX_PP_BIND_THIS_TRAITS_INDEX_MAX_, \
            BOOST_LOCAL_FUNCTION_AUX_PP_BIND_THIS_TRAITS_INDEX_TYPE_, \
            bind_this_traits)(/* expand EMPTY */)

#endif // #include guard


/* bind.hpp
6cLlqgfn3dQ3z3pwN6MDV5D6bznpvpVumvt+VPVx0xVJRJYj25DnkLeRi009+m+e63/rukXr/8MbRxXc+r/vCfP6P0HL+v/oPKz/R6Sb1v+Hk+DGUbmuTZrXahPd7AGgZYZLYvK/Vqul532tVkvP+1otbnM+ryv9r1ur3S1nwE0mYl/hSepHW2GUo+tarTF/5GN3Q00k8vcZ5H3kI13XzuuWehSEaVm+KrwSMErZt7Q1pNTiGRG8hK+PeZNdrte2roMVef/OX1uR9+/8zW6/Ns3bRcq8XaiyH2wbyEzBDuQl5FXdi71AvZ3XScVPaRig/IywxZGnx5HXEdyzP6iP5Rx8zZXqG35jbvFzdV/Ici4vlLsIFX4vW09qdyPyPPIC9XCSdLWlXRV3OZdrF4kcw73j/2Pl/JDrJTLNdxtrknn9ptDfDr4bcF5/vLgya/3x4EpjDTHK+A5/Rfbv9WeuyL6umIyZeV2xs3EfrfyUWOmyrojZeMNNw3w9K/lZZ0yTjq0noiM9HOdxpRnPj9t1xvuVm845rTMSjmVbNObSdyj7aJe1RszVWlzBrDWmFs50OEryOFLyGGjkMee1xmFp7tcaA93lT/xWttvT60e5rDVuL+C1xiFSIDWQwkh15G0SkLHcyGPSlNSUXH9DcO+ydpFCmzGde6nsI6z6M8NvEfKp5t3ykK+c59FTsrXXFrKmasOTP/zdS/ZouNvIp+uaqrGGelq5+YfXHC2B8fhXNov8E47lGqqxXpmh7C94FaWUz9EmvPS7bPu9oqzKg7DcnFdG1i+yNrFzCfY8miVw7Xge+iuzmaTQW8xIsTJ7xVZTW2iz3BPibvdrrCXhC8r+opc/Yabjo7h+wHbGqwhhYG+Ef8AWqq21BZC2L0nbS+LHCNP023QVe3ft/RPl76TXIS+Xs84kf6OX2e3LWeRtBnEbvyPG8xdsv1N+wvDDveHniK2Ytsbm9Nsj+e2j7P2Nb9AbLOWeHb4P6eFGOf9qd0OcjdmZO1TKoeY9meuzQdodfDtYVurcEd9bpNHLFm2rqI2zNdWeslWwzIN5nTZU0p+s4v9Za8lzM4G+Lsw1H5TP3aygvam/bawLZ9q9ZwpvulEeP6rwQuWe1V1VPr6Z5816q7cho7xnKrffaJGSVgmXtPZScX6oD7Xnh9QXNvlPMp7388p/XaNsU9X9ZMoGe1Meqmt9CO9N1gWCNfJBfK5tayT2J5X9FXSXBto6Z3sXCJU4vlB+9ugjqcMVtNbyVmGRdgnHWK/8RrW9415ZZTbeWHPdq9LdgpZXEveYmcot2PzcxI6YlDAya++K4yrOz2z+1PhpyijY3CYwi+OkFsda/Ull9jH3RhsYxx+jLnar+IZKf+TU3ihR87rpTClv4ld+2knZGPVHGdxuO2Arm00/qzd8pIx6J0JknV5kJ+bYIZn310ooM+P9qPQfWO/Mba0+2Gmtnj5EzuS6vMz5TK6GDr0gWbev7o07WBW+VI945hv9u9W6vVHG85W7fVa/bYSR9/P9cGu1Bm/oN36wwG7/vO7LyphFn4z/nPVeFir74t49bF7aWS/O80X8vL3kPSL7WvsK5d7Hu72NvbR4mfsO+c2lj60qZdBIpS3Gy5t38w3IIb015wj5anW8fLQOiKPfumeReicnD79ZrsX3VuHU9prAr9x8/QvtI1sTQ+dnh/IbYrHvh6zjq/Terh/SJhh+0har+Izndb3dDblIpg2XdWnDu6QNi7BG73x/Xu553zfMaMfG/WNl3Pvtmyd9xP+99f03e+iY9xi/bpyXV1Snc2cmdW102993eNb3/9PX95lrcru+31rW99tAH/g3aJx7le5+Hb2YLdNfcegPg2A=
*/