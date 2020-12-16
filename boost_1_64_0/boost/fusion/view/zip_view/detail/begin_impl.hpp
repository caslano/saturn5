/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_20060123_2147)
#define FUSION_BEGIN_IMPL_20060123_2147

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/view/zip_view/zip_view_iterator_fwd.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/fusion/support/unused.hpp>

namespace boost { namespace fusion {

    struct zip_view_tag;

    namespace detail
    {
        struct poly_begin
        {
            template<typename T>
            struct result;

            template<typename SeqRef>
            struct result<poly_begin(SeqRef)>
                : mpl::eval_if<is_same<SeqRef, unused_type const&>,
                               mpl::identity<unused_type>,
                               result_of::begin<typename remove_reference<SeqRef>::type> >
            {
                BOOST_MPL_ASSERT((is_reference<SeqRef>));
            };

            template<typename Seq>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename result<poly_begin(Seq&)>::type
            operator()(Seq& seq) const
            {
                return fusion::begin(seq);
            }

            template<typename Seq>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename result<poly_begin(Seq const&)>::type
            operator()(Seq const& seq) const
            {
                return fusion::begin(seq);
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
        struct begin_impl;

        template<>
        struct begin_impl<zip_view_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef zip_view_iterator<
                    typename result_of::transform<typename Sequence::sequences, detail::poly_begin>::type,
                    typename Sequence::category> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& sequence)
                {
                    return type(
                        fusion::transform(sequence.sequences_, detail::poly_begin()));
                }
            };


            
        };
    }
}}

#endif

/* begin_impl.hpp
U2iqLuZ3vuXfM+ugacD4fiOefvSkXMCKM5s1rVIM5QLmyGzZmPPBaLFgvL/u7u4P0AxgvIci5e/QfUkC4z2UcrGmO58GpmbWsG90J8oFzIfZ/EF3qT+F3vycu4bMcqRcwPhZ6ut+JaAFgNkz+7numx3lAsb7GznEmvbTgXkwGz/iUW+0ODBPZp/eP7mAZhSWs714M7RU0cOgBqqVaOlgfH6Ts78No1zAbJn5PQwpjZYLxrOuEzu3HJpNV/PeK2wsNg1NDebF7LZCn0+5gPH7En/xVBc0PZgH72/HHMosAcyOmaNDaEm0RDB+znIX/CizZDA/ZgGHrr5CywIrxWxo0OwjaAVgbswGjgqIRFN1M98vqoX1VbRAMDW/88szq9PcwXh/3gtTv9LcxZrT/mOi2RrBXJlVPr/wLPUHxs85Uf81neYu6rpVL62kuYPxGU0pWmUF9S7O8nKQ1UaabYR5D5Vmv7Kk2YK5MNuRFHabehc2unbVu2ixYE7M+vmXPIlmEPsd0pXPQDOB8bvUtn1vPfUOxntwURV+zsoBc2S28eN/mqLlgdkxmzFyWTSaorv56/yG1jE3KRew8sxarfxIPejAPJktclqaTHMH82X2fODiULQkUada4ZWDliZsxXPfcJotGJ/7ga32L6k/MCc+W92mmWg2PcwteuOvPmgaMD6Hxze7WKOFCBsx5widJQrMlefp0CYGLUHUxVXIK0+9g/kzG5YxqwxaBhifbcqkkHJouWA+zCrPXfQRTdXT/LX8btNte9ACwEoxs/x0cSrND4yfs8W+bV1ofsJWud0cg2YE4zPKc/30f6uuSAXD71ztLOIUrb/0qoiWC1aZmd298ofQNJGWiorMMq9qM/D7ux4M12wP32/7f5s9HM0IVobZmPdWHmjpwvp9y55F9wVM///v4R0seimuRfZ7ipb+F+3320pVW/Mv2icw/PNNMMXAd8kjcD9F78IeOsJ+71dfWvDH+ihCwLSKP/t1BjsV7fcJzcSsi8VAxfz7+VfxNwhFn0LTQ13R7kNWokUx62rRT7H3+scVfyxSkc6sm0V/xc+R9sXwO7MmutAiIOu/vwTjf0tdYQBLtPhj3S1GKKqcurD+jw1W6GMK++thMUSxuGjX/882WmEEwzV7wllWD5lQ64+NVOSCYZ5RsN/kHY/qo2liLRUtfpvutzV542SLlgBWi9XZXRs0G/dLA8Oz9LKoqXh2KkuPlgdWjtmZg/P9/9hAhaZf4W8sf8H8qoXsL4qmY9YbbOq64IPYu4FZH/gNKUi7ZRFaKpgfsyFvY5ugZYPZMTOlDw9EywWzZ9b7plsntAJR988qr+g/Bv/eZ//C1+Ro+PfOTn6zKIUWwiwGLMy+7320BDDMLBZsZ6nTVvj3AFOZ9YO/B3h01IP5aLnM+oM59DyagqYZUPh75ACwJpW2NkbTg+FZBoJ9mxz+N5oRrOz/bRDY53/DXqGlg+HvtIPBusa+34aWMYA+F/y2zVYNc9BywPC/Uf4/O7RzrDv1MJDO+dtuLEuZRj0MKvytawjYt6phz8kGU91v65V8tDZaRzCL33WqkDgw+EcF9T6Y7stv0/5Ia4iWCFaZWff7HRdS72DK/9swsJSIyhUU+Oc5YKX/byPhN9wmmfl2aIohhT2MAmvdPPgpWRw9D7+tQujaALTAOPrzKjDY4/PqxmhBYDasrur16Uq0ULCirO5zp2eP0XSizqOI+320KDD8bJMAdmlOqhHNAObOzL9r8C00E5gLs3lXep1DSwNzZBa7sOhqygwMcxkN5nN82jWyeLrXv619zbNn0KyG0m/wv+31lPZr0FRgSla3aW7pmmgaMBtugz6nU9ZgPswyW2w=
*/