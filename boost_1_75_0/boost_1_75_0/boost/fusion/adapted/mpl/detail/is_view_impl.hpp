/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_VIEW_IMPL_03202006_0048)
#define BOOST_FUSION_IS_VIEW_IMPL_03202006_0048

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion 
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_view_impl;

        template<>
        struct is_view_impl<mpl_sequence_tag>
        {
            template<typename T>
            struct apply : mpl::true_
            {};
        };
    }
}}

#endif

/* is_view_impl.hpp
EWCyoHwoPQoHoLrut06crv6NJDaz0Uq0ssYufZeDfqwwhOYHgioUmiSa9KjlRpQvqs826thcFzqJKYPrL4QcWpZADUdOmuF+CTr28vD2HTvTburYweHYsQX/sGN/2dSuY59ejh3b2ImOBTth6Ngly3nHrgqjjuVtL2pdbqo1dmD2cgOeJLD/7gjrXP9ls9/u4f+w/2AUnvsbrGOJlI1PcV4SFEv+FJeb+1Dy78Nyc9dL/l1vwmYZK4oQt39sK5oCYSSXK7lcrp9Oq3pcGC7+FMSUSTnk1PskPl+qFNeLv76PovORSnwsWRdnUbuOpG3X3HUYdtc6+uYO/ZtK+mYGfTOFPdSvrkK8hTH0ych1ce2w3g0fcxMSdIlZbkhMu5/EvOlJ5J6OVuEfYMe3pOyBpfjlPCEr5hLQqKlhjBmJHe1Cv0/rosRnC+Cz1ga53xb5HDazNYcrW70PY7ulvYAb7W6eU1pRFC6LOVrFBDYT3ME+40Dws5fr7V3O2ztvmp9HMtBcsKPmQodY9/wKc6xVbwc6sMN2yIC+A4U1jv/1hJWfz2V6z3GmHEJ4ZVpr77qsFW3tk8HWng3CnsYx2k1RBB/MJuQXBOSxcSuDekdZylP6/lgKI1xOkI148geKT4+/2Aor/NsGJeEZH6VGF+NXv91KuNrllF6PpEZRf3m7VRgCsRFJEF1sjtsgmBpJrI0koZQE6F/wWfvz8kDf
*/