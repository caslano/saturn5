/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_FOLD_UNTIL_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_FOLD_UNTIL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/fusion/support/detail/segmented_fold_until_impl.hpp>

namespace boost { namespace fusion
{
    //auto segmented_fold_until(seq, state, fun)
    //{
    //  return first(segmented_fold_until_impl(seq, state, nil_, fun));
    //}

    namespace result_of
    {
        template <typename Sequence, typename State, typename Fun>
        struct segmented_fold_until
        {
            typedef
                detail::segmented_fold_until_impl<
                    Sequence
                  , State
                  , fusion::nil_
                  , Fun
                >
            filter;

            typedef
                typename filter::type
            type;
        };
    }

    template <typename Sequence, typename State, typename Fun>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_disable_if<
            is_const<Sequence>
          , result_of::segmented_fold_until<Sequence, State, Fun>
        >::type
    segmented_fold_until(Sequence& seq, State const& state, Fun const& fun)
    {
        typedef
            typename result_of::segmented_fold_until<Sequence, State, Fun>::filter
        filter;

        return filter::call(seq, state, fusion::nil_(), fun);
    }

    template <typename Sequence, typename State, typename Fun>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::segmented_fold_until<Sequence const, State, Fun>::type
    segmented_fold_until(Sequence const& seq, State const& state, Fun const& fun)
    {
        typedef
            typename result_of::segmented_fold_until<Sequence const, State, Fun>::filter
        filter;

        return filter::call(seq, state, fusion::nil_(), fun);
    }
}}

#endif

/* segmented_fold_until.hpp
eCv66erDseWkR8Le7+ADO31jODYYh9MEEIY+Df+yhAcoRFiNUFScwQ7mcMMYLJ+KixqaZA5WfuUHWLYhf3rx1mZakRlZ6m6OiZ+SNpGpz2dXT2SSS6MMbBPQj7dnBDpbex/D45H/YGYeyVHqhfv6aQraRJRovnBv5oq9d8YK+5rC6iQYB2zyVYFTGald9OZR5eOq+ydH65mt8hpSW0JbykqUMFMdoVVP4Yib5/YvoNhDEj7nOGv1dMIsKP5nWBebSs4H5wTCmNX4J3MuxEL7Xe5ZZeVeHRf86MgizPjO1W6rR8pg6TCzrgymVevysbg2ylnT9f2Dtk8JQEJ39KVG0z7TT8EfiBTA1aV6zbtJwRwqm0Ecj96VUEfj3gjlEXfVZ9TtXU6aA7mP3WEvK9vCZyCbtLMu7N2zi0978NVYP6yle7DoEL0AXjbNRzSHuKkrpjUUeYQgahGTERE/UqWomrmCF+9r1lotNENi30nRcUeNj0y7saLXYvw9Nin5SoG2Y6V4VYtO214N/j1IutPbL6WYVLcJKv6b2dEkv/2xKxzgwcg3AAQjJpscp/6tp/uLgKcQg3/tLIRScQ4qbIcDfa6/JBxamBkm+oUvlk0nfMJtF/Dbx7+6XuUGXla+e2UZ+LytTxN1wfSRRvzdxvWNqwlseHSkdG+4rc0WyHU87uxU7Wxeuekh76Kn4IMeGJesxToJcuaMp+423rNGA0bxVwn6w/2+GFXA0SJ7zMTRbyo7dkjDBUfdcL1p/aZ0SqTMyVynkXtdOl7sPsFT6tibyxQSCwgMrWMp0TAm8cairL77OAkGNZp12e6+IORXTE5VmxqnhIhekdlafEHB5u6uDy4pkb9+sFBjIKUBaOoLuYc4FfnlUKHw8SA07vFm5tcMYTKAqd7u5XmTXT2vlHh6zkvVDuMkMUuve6Z8NvYOm3KrwCbztlmrr5PbE3ex8jOF2t5n9U1ucBzd5uiqibXH1xcX5SqSZKxT9I5wA5ncj2frSdgdyT0W7HJNM1UdPVN8MpoNb8N0QyiqYXRucX7/urltRCT5XOIfXz3c1YtgK/4zhXY15JO9A5YnBqzL1LXhY5MbfG6IEnDbZWM3qMOUstmLMU/o6huUOp+GuVJtoDodxc8RYeL1yDSf+JWZOU4IZVE3LjVDVhMrm2lS9RqYtzDZsCVeVDP94OoJbgTQ+AWGuApPVXO1NY1IWeEmuGwPM2OTxQ7mhwrkB4TS/VjQPxIa4E/cTFDLPvQ4Z65ny6zuYyaObphs60l/FA4wnv8CHlcrwybyDS6pEw3nZ7gUPNndGrseInthj/oMshTn1Bg5d0GSE0wdafIGjPbHph3siorOBVfmG//7aSyjwztzrkCH3TJjogxJIA8lYXXLV1YrFZPjrMLjR8yJMIrMWg+47QK32SWIWlgVgFwWUxUzRhVFKzEWrc4SCZ+DXD+ed9mdk6F3dqQN9Q1sWmVX6TEHCVzTFUfci01m5QqRZKLBZXIKxEn1gFsiYwUe1503rcFvJckUoHBL7ZegSvjH7lYA6fnb/xggIvkDXpRsKcqrNXXBW4dS/7gD1la0H9dA5Ki0aawh1muvFwwoPsnBkvXw6NVDgr18oBeNHKBEtwXpzZlcRGvobi/TL8sIq/GLILUfPI66kXyXqSLIlEk/FHh2ga2N07IlxJLJvz4/maTvhq3PH7oSK2Ela6Ka2mgpfshBxtw77KXWkjrtkkah3oR7RQPFaHSYWYtaJ7dIXaYEIv4Et5TmMcteHYcKalR6tHXPhhjpk46/dQdhcEYUcFBCLHiNBsvhyozrxRCHgVQytJbOwGaXxgQczvWPS/H1hkRmHtQqsAfnZUXUPH4TP1jyDR1BoYnov+x6kGHYX5PIzWtB4GSjW1+vKnRpSPZwHC9o0yJuBE7DhroPPs7QdZpI2vLeCDbnbn4EeZMSBonFnU0aPA4UaQYMbTmwXUBHACkQ1wB8vVnWqdVKmymcfoylpm1Vypa4WTTOGyCIjOuXtIEojIXYpv3KAZ3ru9VEfOlxsqRu0WVIxE6nq6xNRHFwcgPychFImAUbADjn/MjobENO8Rzh9bganFRnltLh6mAHj/mCkDkSOcAnuO+SudYKIeJemOxkogINZ5ENxjmBcQGPWsmEyVJKtGa/6Gbu3oKXfhzu65rsYmvbf+0cPoSlqS+XuYBTFl6kwHPtg5+CQcxax3Opwy2mwhvPG0zSxUVvsaP8olbl6aLIdL9yYLqExxR9jApWuo37R6ZBP7JA8TSCSRQgLSNh4GZCYYG5rxORyVo2atnHVm6w/cVyFcsnnWX9dlxfE/vq/XT+svm/ey77W0ygbsHXNd5Mh9Eq7eSo2PeTUoWRXlAZ6INlCqIieSGnJrdPxYCMQFIykTZ/TapKNYpAReDUGsJOVr0gAikjyGdEH8+/hSG6iEhXzrJk1BzUTSKt+1ndCFAnAW4doiZkRoXN5xzhad4t16hQFoTiFy4GOqZ7kWcDoWcByPWd9u6asmRx7i4jkvi1gD4q7cA3myxaRw9dmmtaZz/XOnRhvyF3u6XlhyCV9pQvUhFE2Yh6xXDtJbVkQGUnBQGTyB1hjuCDCQ9osWqxGs6tndg+rOkhcOweh//G2pF8oISBB7w0Ra19cp4FjfRhhHYzKNET+z9Sx60jdLUBckv583orarU9CGqGwhtahgxV6no5VLAQ4Hi59Ebf+yd7ZTW22X0LcCTu6s08C/yvR9JbUbkjlJv8YiX5bOK8aGtgVGwe53J120qFUWKieNVJsrADmPrLU4M6hcTXIoREVUbsDxkD4dW4NQWhLSIgMo7LNaAwifJtc+BOsHR4313MBTkC0+JjwhiTOXHezIz3djMppec0/hgUGbCDqywWoppkeNnQHOs0fIrneuS3PL49v7fxWU9EBwC7IBj+B0s4QS7A5WSKa/n4B1KBi7/ENQtMgP9tLZJ5cb5iyCukopcgdHxs1EeBLIqYNIXvGxtYua4tcRd/igkBAiLexB+xhHu28gideG9gULEh0DpMMkk8wKYI6skFPKvo4L2PP2hljaRZTk2XKq6IDTw0Vrw8gV1u74c7tilFD8Bcb8wOZvAr/+/z/cYvAb7P2YCWPsadnFdp6sZR9Mb5cv6WKz8YGbh7i9JuyRbcV5xVvPMeIYOWRDFmHmYP+r+NSgW+t7FSIJ6hdcQRCY4KPMv1Gh2cZ9wX8DdwecVYdWwrHhxAog7TFoXA3iDQ5ft9pJ9zkAQgzSNkfTxUzNSWMcP9gqCO/XHfwi38cDX8E319NylwvJyKsAxOBJiU4izEIWLnOfWXx51ZL5c9vn8XF4Tz5D/UZ+Cmddmht26DXoFlxv5hrblkhmJO6p+3HwXXfIERtYsos0nyWyJSb8E8SyGHLb2BYuHFQj71+lJm+p0P+t2dEqsUg0zlrXT6/CXLLhCjJD2PKc2lWzZ+9wWTrGwtAPnkDzeGRo436NsHtlNQXyR8xtI2FAEM0eDwg1dCccNpWmDJkFfng8lSb/745DgB2b9nlE+5fHvPz5S1EoeEkrwT3mHzUnfdzN0Y0Q8UKqduETsGpO4og+yFc1b2mNx0SwyP8qRLDAzov6do1/JQaRMkm8fsKmnsP3QlnSAoGUYMAOBsWsTXpy0JsNv8fpbBY7L+QNQJP3WpvMut/XAL/2LZnjIwkuwp9KXGB8PCykZVuSf1CDY/5QyJ6bZmllf3EnOLQs5D6hOBj4fJXFDeR2jwFRvT+pvp+GmdC7JWJjJa0eZPgEmEeyMD5eG91mXpH8O6RXhTT80taxnqGYfruGOycR/chGHdnHhz6ZdDilmJyoNuYXr3rXuSE2sHoFhl7n3NJLypdX+K79CGax+RjNSdnWugp2W3iFJ3R39HTJbgPbhTGN3jp5OubwvtXYPU8rfNKLURRtOt/g18kzC44+p6osPsFxU0hxp0xxSLah5a4jvo9HAALs9xrwkM8n5BYeBg7dYSFtDA1tHl8vLIT/ZBDP6XXCyDCQwj7WJRxNx/RhTjgGP4IhAuTBucQGIZzQIzxQI35FNJfwWxVxWaaaAw9owkGCypAZ0nU0ThpSOi2OiewfW0VnKWVuMDVf9vHYmT72x0s8Ze+1w1DI8Tkv0xL5F0FiAahaNusl4sgc8UehN5j18m+YMlncDa+37KNzFjk43QopupsTtH4NnI/1/jv7tHXvKxfNmRmMcLSgN62JD4JtlcIA2rp9m5k+AroS4wvYvTG3kQpYH4hbnupFkAx4DR1TC58+pOjJSU73A9yw9E1tcftJ4m3CogtdvDLni8i6a9TnzldfyAzfK60TgxHAr/QoBvPnHUVmxMEetpj3nnxky6MCvz/tl/weONpkzKnwOg/QCm5D3noUAXg1a7E1eD+HwhL9SfXvhkZkF4NgHiA7md8HbsPpHgIg4qKeP/bdxV99RIp76l0aOSIF+S2cvHs3IyTq/91Eot3DwC5519gOjyi0t5tADQ9S6JFxwsyA+/leWdER8XyrUO5qHBfiFjM1R4FCHYDEPNN6dfAeMoFXOPml+eEjezIpUIsTUVR/oZOaO5LICSDD/1sDmb5WQXq5AVBRS7rRrvkoVKz8EpAoDlU5tlxvvnvy0x52MuRIQ4d5+5AVIk/SOe7tXmKZ0zOjvY1KeAAULoANxXHo3aN1hSlA3LpvO+ScBX3ovl+un7NDG3QsB1lA7Fdt/8HmeusPkht3iZLa5U0ZPgoKr2BGziAmJx0VQXZPw5Eu/kGwT5RKS1M4hBx+ZaKgWz4YacbEu6cfjE2h+wn4/K4BMxz3xY6G1i3Bv1i8HiZG1zg8YziK2HBA4w6OqpNtsoz3Z0KZZNX4qTo8fGFn6jNGEbkNem+EijPcBCk6+kT7Ylh7pWq0kNCVMELkoQrWLP91Z/tDFQE1S8uXzgVSchNSnt3BjhD+P6iX9cWvHsMRUNcH7dFqkkFU4figT4rLDpC9bt6ugJSgNw6qvUvzpjhceL9jYRmv2vnzjtKtY7WVu6ZMbARJIpcEB4A/+9bccckt9Tlh24LBY3dkkj1VKNbRK1GM8ihc4X1CUyMVhnfKegaX3+C56EJLBl/oK5ZU3RRCV/UjV1DWQ/62Sh8pNFgGQZA2DBgOA0x3D5fsHDp2T5G4hZvZ/IghUZnfUklPYx4YDl1h27xU/LNESNs4KUgNrRt69wud3YrGYBttlMY7beJiiiE+28VH8isEtWW1ir/x6zXQ/kEMEVfLFHPZ5UEa6EWdE+n2uOsUELrvkq9P39xSMdfxlS+h/Rxofo03vAfzpKd10bD7lMkdtmFrW+cuUz/xVdgO1QBV8MDV/Z4s2ol/jZ6zE+SD/qDeF4bHSl7V8eHN5BMrdy2CXd9/PcC1r/bjS/9MpeczcRB/Gk7Wf1Ep5nyaupCiKBaAi3soimAWgN2vRytGYDGaOu7mim+esaxCz4qzvIH7LXSAndroOBoBgQLxS4wQjUCRWEKO9xb15Lhem7Es6xq5dWTHf7KWuvlUi0iKknwFfob4pth/HPRvDTR/Inux36kG2d4Nydo3LtqRVtEuGgu+By20q54sSXSatZ5a9pPZjJJk+1KRRdimxeDuc130ZuQL6ul6cr8Vf6jwKGLO+5lk9HwJEPYnmTK+JsaBBnalGb+on56WOIknXZI4cmFFbue06uKJOnU6h0qrVv4vkLcWCexK6ZHy5QaKycKfCaxrAda0V+q3bm8oX8DEU1Z6DVhLsIKGvkMnypUiNZm1ZgoKuovxg869oZP6/VOltpgVND1f+MjXIGBFcL5QPkddn3//bhBVe067G1Uptj+HHQZndRh2b59cUeeMH3Jfidzv/uPAyufznIypUeiz/2YPVRBHTOHbVoz70VucLmWN2IBoWh6y3AEePzTNVZYN2INea/8r9guSfxNyqlNrJI/MJj1Nn0jht0iR009Oymh/Z4xX3zTFqUpLIAliVYVTrch9VRAlTep6Q4Ejk2U2EHpKMDcOJOIvPJwEKHSdcenSinGwpTRmd3AkxLR+2tmeF2XfHHZwI/ofNZybVkyIjEOwYMbNspAL/6Je4AAiz9069jCBShSKe1HChPGZ/aE33DhbWx9o1G81fBM8OD0ECEz2yIXhWU8UqH5uWXDFlczg8uFvW85OtbbZEt3W6SD6r705whvl8ROawSd3z1HphBQswbGx7x66Fymdx8l6Mzy/mYF3Yma1bscpfrYA3Z5xW0PMKvCE/6ml/4Gzvx1peYIIhhLdg00/3rzTJtVUPX8pjt/6jh7v0qz93dD03ALQVhWh0cTRPpoZZ+SUWmkNqXl7Qwc9mIUOY6ubZU74HOc38Gegu+WIMSb2g+mog9O8yjixiKWqrq8M19A0DfDLlDpsIaqJcqmtb9safTbGTVEQg3w4GiGOhIiBPPAgd+MsqqV+xYkncLHY7UrS7MQ+c1Fxu9Fy3XaGp8YD7O3Z50Inb4bgicC+H0oH6Hl3+5+LHnJLBtHu/aFoq3XyfACS6yWmefmaoGXdgR9wwkhcHWKtymo1/CHw7e6rpxr7PddfxvqnK/YfxxR805We/gup6/6VCvlbiCAHrT3W5cE0dH8cg3KrgDAVEhtfgUDzlVzelJULeKJoB5q0m7qtk8Ra5GbMXSWitGuIpSTpoppLSJFc5sYIijs5eksVhESl5AtOxdHmwKyf627bABdquxTJeagnwQj8OXmLuTSB9lI08Ennr7ewr7Fa96FX6oB5of1fBXwJryK8KnylTAYrHMiOcQuCHE/vFyaFrX/rGrveCAeb+H9fqnMxXwk4oFCfYMnEd8Ei11bdXNiNx4+O2An0KdPr4V3IgcqOF2UJ/lQrAxZKpwVRd0uwPMd3XgVuxtG6ZX8y4Lunf4TnkPPWRXfv+V6ItJJzogP2Jotmr1YesxyLPYl0/sQ/e1Q/Mgzw/yKvvC5PjxHsUxXto7h2904b+wASaRA/0NbZFUOvEjQexELd1q78YTJ6b0A0oavA5VJbTEqkHv1q0DTqz/aqwLqlWSaesr2owsC8ZNobMrW66YjgvXQMyeXakOv80BMMIsCIxWA2wpl+E4kju92R5O10wH85FyLtC+iQyGRqv4B9u/2wDsqVzR2uwsbt9QZK0SnH3SUCTm4sYbGjgG0ymPGaF/6/6Fw2MU6UOULdEmbgQZxo89yOhfGDxmc4hhWHUgZ5hMebwlCOi78aQ1MQXYveuHgrk4mzOOSZnMwcIHzhxh815O0yfZFU+x2zjxyzbK0Iuzk9PFldAdjks37+ODKuDzIy9S7gX6EU0karLjB58Ig/f0qdhlUejHJ9TTJTzI2sqyqSd2XcWoY4OL1+W2I2WIq/tEYv7q1O9S3OZxJ3zMVqimmKsO52jKebCyzSre4h2HNobAqZYUp4Yb/vMD4zDMpXHG0xdzTc/69Q+wPX17NkXzuXISwBo2S6V1psJPpo1flhzSjdOFGUpwS5WmJdzPCVdvvXbAxJUnI4NPF3Wu53yX5tFncv/Y5+SUj4pmSyKWhZPs5l+voP2VukzOni8aXyuqqEaKy4SHfUdrgMb4BuX/2aen5PjBoCCKtpAj14smoDVYyf/XJk5vlXw966wAoSmtmSTbUVM9XjAj4fqPyLnMGsxMUEX83oEByaFIp3A33E+zhBYjUQKPzLj+qKEOa32WhliM/ufRAkOHVAyIssxw1ozV8U63Gr+65EJ5TqJbLNfeVmC1m7VW/BeiiOKqkKUshU3RBBZFEwV7EM8JKNRT1kT3sEYdTWId807kYEIKOvOC2gVSptYbuOaYInTc+kwWt95sY8DIFRGB7QOn7CTJ8JX6cBINrQq9iaf5AnrJ0HL1G2Nr6BYkEt/MEmYuMMrIrDl8OnGX9bUmaSFnV5GFRy2QE1FJ7vO/sJbywJ0i/prReql/tLIdCU4d1I4eXvw4lv90Zd8NV7cLJZxP5ppKuAsnr3BPaWl8EcxjYw/RnLqerEXaWDMGW0UTnFS+9ObVwon0W1j2SuggPEhoC9v8HBhsf6fpWOz1jwfb7HbBvUZ55kQ/pI+Ar7PozT7TuvweWkmDbjfbrgzFuYweMg9YVcke6XgjQ5Z6w12/z5SrftF6S3/R/iuP4z3pO/7hDBzo9m+NFCJXnytj72MrKAu0+t4pkmwsqvGZPqlOzp7GtQpQ2uulmJhsfJfq5ma/wjX6shTJEosQpxubdPyRW4ET2RW4ij5bQtM6XteZbdP3T/C/O0uX+oJmQZ77bg3RhFvX3xYgZu0rbYUp97DhPF6Y0ODLSBWkjrVezamzPSYrShFRPf3tuphLn6oc/n2sxDUWw/KWtLyzoffLlIVukiLppyMyvVkXjzmUj621FZfDlHuv7l7dCqC3dAhIHf/qVy2GxTa0Ud+f+E7zGXIpczMb7dV0o7oXUXzp/FfMQ2iF6fMYReFk3ixaFXfP7wcEvm1ZHdWfUFjjTqpkDCIamfQBzZABzHtqp/FAUj700XGdF0TRojHkSoj7PbJgeFAhlgUJ64B7QfG07u0TDtQ9BNX6X92uzi5a8oNaJIQ85XdZUQ1qUOKZPKrEPDvegB6PGlLNzb7pXH8wWXwgmqEBindBP3RPTImoue0NIZL2tM1gHYx065Z5lLeskPAsu+fYyfj8wo874VYYCnznKkfjosqK0eyxgPPOXPZcASUDdC5gdzloU8pHaDpODvksYYgvbbMyf8YEmEsLxghOcJg91XIW1Tnl1rh/tk2CWFmxlqaewutkVDmsN7CIXelYGdpkRAdyCO3SRL3tlonzYMJKTFRA6yCfweSwGDzOiBsSfrEtSp+arCtpDbihmzb5SLqHLnX8G/6HQcIn8eYhCqP48UXX3D0HFQXcfd7oUGUwQr/ywbb441zqxGrQB6iS292tftBOb/2FgO2LhE2vnmN9T1JF9rtnPqgNa+uE2wjC10EFSvpXcmq0m7G/yC7W2STtuY/iCRbu+T46Nq5hzdJOgmkf2y6F8sL0nYLCWeberBKPZIVEqB1sS+i0TJjZ2+C4fBvttbySx/a/BZDDOmOuI69VEpBD7Z6gBvnmEULCezRCXpmRZPNNSRYRQKhonbpNyauWnGK9TdGBNtnxZjvFh29C3HgxyGKWSNUhes9e9bhWIyJgm09GT+9sHDLPIbcp3SrGUNFfzCfFgWZZ0rzDZe/2yvyqz70Lws5O/NqVhWWjdi5hdYrbDCZ/dfNc7ELqqZs=
*/