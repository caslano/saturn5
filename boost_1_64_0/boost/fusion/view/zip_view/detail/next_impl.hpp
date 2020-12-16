/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_IMPL_20060124_2006)
#define FUSION_NEXT_IMPL_20060124_2006

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/zip_view/zip_view_iterator_fwd.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/support/unused.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion {

    struct zip_view_iterator_tag;
    
    namespace detail
    {
        struct poly_next
        {
            template<typename Sig>
            struct result;

            template<typename It>
            struct result<poly_next(It)>
            {
                typedef typename remove_const<
                    typename remove_reference<It>::type>::type it;

                typedef typename mpl::eval_if<is_same<it, unused_type>,
                    mpl::identity<unused_type>,
                    result_of::next<it> >::type type;
            };

            template<typename It>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename result<poly_next(It)>::type
            operator()(const It& it) const
            {
                return fusion::next(it);
            }

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            unused_type operator()(unused_type const&) const
            {
                return unused_type();
            }
        };
    }

    namespace extension
    {
        template<typename Tag>
        struct next_impl;

        template<>
        struct next_impl<zip_view_iterator_tag>
        {
            template<typename Iterator>
            struct apply
            {
                typedef fusion::zip_view_iterator<
                    typename result_of::transform<typename Iterator::iterators, detail::poly_next>::type,
                    typename Iterator::category> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& it)
                {
                    return type(
                        fusion::transform(it.iterators_, detail::poly_next()));
                }
            };
        };
    }
}}

#endif

/* next_impl.hpp
BYo1ve6vH4kWAqZkNuhduUS0cDDe+5y8993R9GB2fLa2O5fR3EVdraWdF6LFibOUbPH6Bto40V9G9Wdb0BJFf7ruBVfRFon9Wtb2obtkEvul+s2egZYi6mqrvligpYn9TlglzUY7LerG1PEqj5Ylctm0aifNNkfUbWkYthItF4zfJZ+qTVqiFYC5M1MWO5uBpk4136/9hpAyaAFgvK5I6UEuaFowvt9Lj+29abai7vO+vApoCWA8z79abh9MMxJ1P40ReWjJYDxP1/YHB1DW4iy9okY8RcsQdVtXTn2Hli16LzuhaT3KE0zJ7OCbYj0oTzAPZsdX7o+mPHeZr/lu6lMryhOM1zWtaphOeYq6iVnq0ZSnsL2NUrqhxQo7MvjqZsoazJNZsbB/hqIlibpr9SrcpaxF3beC60bKE8yX2YuJDz3R8kR/GV1Kq9FUu83rNr+9TWcJAvNiNn3dnEDqHYzPwX/uhDHUOxife51pitNoBjCbPDCF7rdltp3zFc14zcqsLijHm+6LCcyJWVhe5jO0NDBHZqEjMx9TLqLu3bF5c9BywByYnfhrVD5lJurGFL2oQLO5bl7XSXdlJ5oazI5ntsaTLADMmZmufPArtBAws7v7YP4xtChhxdu3PUN5iv06Htj4jvIE4z28qF/3CVqyOMvAYpPXoaWD8TnkDnyTi5Ylej8VuecQ5QmmZHa/rv1QylOcc+S4CBOa4oaV2efkrwsjyWyETYyPHoimAuPfDde+ClhGWYMVZ7bNcewwNC0Yz9M/vZMDWqyoWxnQWI2WKOq2Vxt6gPIE43m6xex6THmKutejBmopMzAvZhtnxS+nXG5aKUow+5A2dBGaBoyv+bJKM9ovRFiyX88CtCgwntm+sNM70BJE3aGYx6vQkoQtXnAiHy0NzJ1ZpZRri9Gywfjcz1dxOYeWK+zHHatJaAXinNPCc3rT3G9Zmb0OPmq1vAVaIJgvs13BHZeg6cF8mNX+Zu+JZgBz51k/7XMPzQTG5xDospzOmS7qFK22v6TZgrkys61Y0Iv6A3Ngtj3WXY9mc9u8Lvf2T8pTA6Zm9vHZg080dzBHZvpRFa+g6cBc+GxPB+5FiwXjs71p7JmMlgjG++v58kcDtGSx5q/iE0pTLqKuV4PdaZSL6C+yaMM6lIs4S9DCtZlo6mzzNR8HeZ5BCwJzY1Z1+9r/UO/CNmRtbEe9izW3VVevo97BnJiV7esaimYC41mXtDmpQUsVa6asP2xCyxJrXhi57i5arjhn6+R3ZIo75pZ/f2F/ygWM7+eV0zKbcgHjeb6dE+mKpgfzYVbTMrM+mgGMz+iiVYv1aEnCon9erkW9i3PO6vR3AFoGGM9sQNdeu9GywbyZFf/n1XXq/a75a+Szcw9bommEvWmr24cWAubB1/QKrY4WBaZmlrAh7BH1DubAzOX26LloRjB7Zp5rL9xEM4EVZ3aq/+69aOlgdsxefLA+gJYF5sRsmtJyBFouGM/6QMsfHpTLPSuFitnDId2eoKnBnJkFqN79ixYIZsPs5KFPNpSZsD5H4sl0YC68h/zHDdBiwfjclxkH+1CeYPz7X8XH1zajJYLxXLTW25qjJYm6pONxRsoajM/Bf4uxNlqqOEvB0ztr0TLAvJhNXZ52gbIWvb9TxuvRCsAcmfk22hCBZnPf3HTjrEfSHMD4WZ5Gj4iiOYDxufe39l6OpgVzZzYq9dExylrUXRjfazBlLerCDGnxlBmYklmtNcGUSyoYn0N+u/xFaOlgDsz8dkyLQcsSZ3HsmfKJ8gTTMPPe40M9qB5Ymf02M2rAKFc0N2F2m2b7Up7Clszb+B3NW9i/TXp+RtOAFWX29l7lf9AChC0=
*/