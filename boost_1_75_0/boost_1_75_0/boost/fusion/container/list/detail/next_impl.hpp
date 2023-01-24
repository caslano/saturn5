/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_IMPL_07172005_0836)
#define FUSION_NEXT_IMPL_07172005_0836

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/add_const.hpp>

namespace boost { namespace fusion
{
    struct cons_iterator_tag;

    template <typename Cons>
    struct cons_iterator;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        template <>
        struct next_impl<cons_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::cons_type cons_type;
                typedef typename cons_type::cdr_type cdr_type;

                typedef cons_iterator<
                    typename mpl::eval_if<
                        is_const<cons_type>
                      , add_const<cdr_type>
                      , mpl::identity<cdr_type>
                    >::type>
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(i.cons.cdr);
                }
            };
        };
    }
}}

#endif



/* next_impl.hpp
b4Kn++HDwUnwNUPQFjLf/waSNsyFdmYrjyiSALbaCgBq0EAL3ABusyVt09e+zT/a2rV56hn7Ngtg4sa+2Ra02V0qodkWrFnCl3Uq0rBkWagG26eofTNiMsmUJDMYGJ8lDypubjoLkAQrQWIb/P3biyRYIe71SGSsMqNpsDIaDEYbiczcpfXBhmN0H3LpBeNQueV2f3z3sgH//NMf36wkN3838G8Ti3FI9Up3cUjQg07ikPWq//s4pImbOGQ9jUN6Jbmz6E1cxSEdH2hIHLL6Qv1xyNFYzOJfYp3HIfkrXNrxL8Kc2XGYNLEUJdnb8cywhtjx61ZndrxzbB0/ALBw7iN3WPAMc4KF4v8BFnzdYKGYYqHbAHdY8HWFhVadGoKFZZb6sbDvKYyFXU85x8KsD11i4aOOzrAA01eWDQPssTC+Y0OwYK10hoW2T9WLhaMfuMPCjQ5OsFD2P8CC2g0WyigWHjC6w4LaFRb8OzQECwv/qh8LxT0xFjb3pFhw5HHWcnc8fjvUCY8r/gc89nPD4wrK4x1Pu+Oxnysef9a+ITwOP18/j0fFYB4PjXGub03fd6lvj7R3pm+wWmHpm2CvbzX3N0Tfpp1zpm9fPlmvvqW/5w4L8+53goWj/wMs+LvBwlGKhe8ld1jwd4WF9+9rCBbana0fC0k9MBYMPZxjwWOZSyx0vM8ZFs4AFrob7LFQ1a4hWJj0pzMsrIiu
*/