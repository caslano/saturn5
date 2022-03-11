
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "lambda_no_ctps.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template<
      bool C1 = false, bool C2 = false, bool C3 = false, bool C4 = false
    , bool C5 = false
    >
struct lambda_or
    : true_
{
};

template<>
struct lambda_or< false,false,false,false,false >
    : false_
{
};

template< typename Arity > struct lambda_impl
{
    template< typename T, typename Tag, typename Protect > struct result_
    {
        typedef T type;
        typedef is_placeholder<T> is_le;
    };
};

template<> struct lambda_impl< int_<1> >
{
    template< typename F, typename Tag, typename Protect > struct result_
    {
        typedef lambda< typename F::arg1, Tag, false_ > l1;
        typedef typename l1::is_le is_le1;
        typedef aux::lambda_or<
              BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le1)::value
            > is_le;

        typedef bind1<
              typename F::rebind
            , typename l1::type
            > bind_;

        typedef typename if_<
              is_le
            , if_< Protect, mpl::protect<bind_>, bind_ >
            , identity<F>
            >::type type_;

        typedef typename type_::type type;
    };
};

template<> struct lambda_impl< int_<2> >
{
    template< typename F, typename Tag, typename Protect > struct result_
    {
        typedef lambda< typename F::arg1, Tag, false_ > l1;
        typedef lambda< typename F::arg2, Tag, false_ > l2;
        
        typedef typename l1::is_le is_le1;
        typedef typename l2::is_le is_le2;
        

        typedef aux::lambda_or<
              BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le1)::value, BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le2)::value
            > is_le;

        typedef bind2<
              typename F::rebind
            , typename l1::type, typename l2::type
            > bind_;

        typedef typename if_<
              is_le
            , if_< Protect, mpl::protect<bind_>, bind_ >
            , identity<F>
            >::type type_;

        typedef typename type_::type type;
    };
};

template<> struct lambda_impl< int_<3> >
{
    template< typename F, typename Tag, typename Protect > struct result_
    {
        typedef lambda< typename F::arg1, Tag, false_ > l1;
        typedef lambda< typename F::arg2, Tag, false_ > l2;
        typedef lambda< typename F::arg3, Tag, false_ > l3;
        
        typedef typename l1::is_le is_le1;
        typedef typename l2::is_le is_le2;
        typedef typename l3::is_le is_le3;
        

        typedef aux::lambda_or<
              BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le1)::value, BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le2)::value, BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le3)::value
            > is_le;

        typedef bind3<
              typename F::rebind
            , typename l1::type, typename l2::type, typename l3::type
            > bind_;

        typedef typename if_<
              is_le
            , if_< Protect, mpl::protect<bind_>, bind_ >
            , identity<F>
            >::type type_;

        typedef typename type_::type type;
    };
};

template<> struct lambda_impl< int_<4> >
{
    template< typename F, typename Tag, typename Protect > struct result_
    {
        typedef lambda< typename F::arg1, Tag, false_ > l1;
        typedef lambda< typename F::arg2, Tag, false_ > l2;
        typedef lambda< typename F::arg3, Tag, false_ > l3;
        typedef lambda< typename F::arg4, Tag, false_ > l4;
        
        typedef typename l1::is_le is_le1;
        typedef typename l2::is_le is_le2;
        typedef typename l3::is_le is_le3;
        typedef typename l4::is_le is_le4;
        

        typedef aux::lambda_or<
              BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le1)::value, BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le2)::value, BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le3)::value, BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le4)::value
            > is_le;

        typedef bind4<
              typename F::rebind
            , typename l1::type, typename l2::type, typename l3::type
            , typename l4::type
            > bind_;

        typedef typename if_<
              is_le
            , if_< Protect, mpl::protect<bind_>, bind_ >
            , identity<F>
            >::type type_;

        typedef typename type_::type type;
    };
};

template<> struct lambda_impl< int_<5> >
{
    template< typename F, typename Tag, typename Protect > struct result_
    {
        typedef lambda< typename F::arg1, Tag, false_ > l1;
        typedef lambda< typename F::arg2, Tag, false_ > l2;
        typedef lambda< typename F::arg3, Tag, false_ > l3;
        typedef lambda< typename F::arg4, Tag, false_ > l4;
        typedef lambda< typename F::arg5, Tag, false_ > l5;
        
        typedef typename l1::is_le is_le1;
        typedef typename l2::is_le is_le2;
        typedef typename l3::is_le is_le3;
        typedef typename l4::is_le is_le4;
        typedef typename l5::is_le is_le5;
        

        typedef aux::lambda_or<
              BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le1)::value, BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le2)::value, BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le3)::value, BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le4)::value, BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le5)::value
            > is_le;

        typedef bind5<
              typename F::rebind
            , typename l1::type, typename l2::type, typename l3::type
            , typename l4::type, typename l5::type
            > bind_;

        typedef typename if_<
              is_le
            , if_< Protect, mpl::protect<bind_>, bind_ >
            , identity<F>
            >::type type_;

        typedef typename type_::type type;
    };
};

} // namespace aux

template<
      typename T
    , typename Tag
    , typename Protect
    >
struct lambda
{
    /// Metafunction forwarding confuses MSVC 6.x
    typedef typename aux::template_arity<T>::type arity_;
    typedef typename aux::lambda_impl<arity_>
        ::template result_< T,Tag,Protect > l_;

    typedef typename l_::type type;
    typedef typename l_::is_le is_le;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3, lambda, (T, Tag, Protect))
};

BOOST_MPL_AUX_NA_SPEC2(1, 3, lambda)

template<
      typename T
    >
struct is_lambda_expression
    : lambda<T>::is_le
{
};

}}


/* lambda_no_ctps.hpp
rL13xn/hPuvB27veugYaHzVDbABXss901JGSl1l9FJsxeOdc5fLG5iGERtTcX4tHn0TSx+ZdlQr1kbUDkxIoYDdNz17ZA52GvjwxcMsXlxgtt20jxPeRdTPuVLU+6Xq4JsijWysFNQwfD7ZtN+l1oBj5+2sTddMG5dHtlWmBpCE8XWoq/xeMlKYpLMisUIFhMIgrXFLpYmRF899AuxrmjJjbz9IcAZCDWXac/onBaAv7nhz3T6ra6dswy02yvBJLMm8xxxj+zE1swxJXP2wErm+//yWkGwxuoZY6wfoSiucGUUitjsqNTwDAkAO+Pkl5xDqCC4/Ns1NMVkTVCA61s8aTrFcxQkztti9fch3jwYJwR055YllP71xPHZWP02GahvRY6+pMbV6nD8FXQB+NluDDBLOqKsablPGbSlKKlXi+ZZnMs8sArT9B7SBcn4GGu7rXTYdiBT9nctArG6JPMhab0GiGiA9mah6j4Lkr5TfdcTkozRSZO7sFneqNRn1xljC9dkJa4eL0ldtT3kdV8+iBrpapE7m454XUA5hbV/jviGtQ7gTX6HeQW99gB0senAsqkZOBsIRRRwo3DCx0r2/aUy2ac2ebxwt9X3516dz8m18/mNfzePhxUVwf/6r3IbJGAldmc3CYWNJJ/fOFOpFdlUeMG3UP92ZPXPtg3pVj9xI0fvNmWBmBn2uZojdS6z5Juyunb1MZ1sq40Mbr7iCdnafkU+c/F58LxVZO38eM9LHyZ+hM1uEUm2YyeKgDa7T1+EyjrNiyl0t1y1xWnqwedY37pgxZJhyFIOHJtr3GxN6ouAtmwuHIbljqAVqvNvcXLqyVRa9a3WQ7FTw5+lk3XdZUsa4zcnkabhUTaG3wXBGY/IBbxsZXkf118JdtAWBisiBdolwLrUO+QjCfaL+8E7yFN/aqoIbBtpb/utb1zEIRKq+9sJN1PHQotILdqqLe9mljyC/F7K81ND7E1pOPB92TxRVHQxqgqwm7GAzbWsYZy8HmOePpPH8PoMkywpq5z1PJZRtt7J1IxdIUN72cmbEakIc+6CEYb0BIWGgSTZ5h3hquRFpfOE1f/ilZuYrTVK80m3h1GKAiroXWbEdG4Qv5jz+PrkkuCawXbl6mqZtA4pDBa3QvAtZPrupA75zzw90emXtjxuEv0G3CM1qAS/GwgqtGF5VGfGrsEQrO6Z7ELKNfPfdayqqf0/Pe8lWQ6pnFVoUPbOLMkCMKY4LtlvFGKHp+Quyq0i0W5NmiUyStQ0omhhRGk5WmsTL6UBMvOdlHGX3nku2yufZsqKpU1HANnnlH39kMgCmrDOluCbmDXHYuz7vTaJV6On0iTMgPG9HO7rIwiFrZ+1Z2LM5mzSp8DghlF6cwf8WZa7qRIiWi8gj1WL1+B1ZRpc9HF5dtuPkWpGmo9yxlJ4Wa2W+MBACX3i/h2PkUsmz+Qx8tamCivpiYzk6qzpHZNELwflhDK4+Z/lkyINal2miiCJoFdi5vPsQuoNqt9mlXkGMv/b4y2U42PUKnth9Lz2KOOonJ7kKrXH4YgPLDADddfDrjjw1uXJxALAqzejU+1XNl6wPitspTtDWmFUooPDF9K91bkv2kXGWOpiRG5P6m0coeE3ojYfGVwyu0lYg0JbW95g9Uob0EEhDSrslp72IP6W57/ZfWo3s67ecK/3IWgQ+b80tzf/z+kFege/n0OFYksTe3CCrmRneQ3ZN2hoC0pp2pIpaGlgDi8R7+UDtVNxkXs61dSQ4L1m6ROl2igWmh9q1lZykPp8PJx/pjTNb337HZdJsqhWUkx25mOkDuPTjjKLWNtXX42khwQo3vfVAhTw8NCCGeFh65Mz8EYL2E13Gl0JJCiG1/xzqkg8M4TCJJIHKmCNS4fhdA4zUCqHwA8ovNTsFltR1DSpb0bh66664+lXD+Kqy1iwbA0xUvVdwCSYz8gTRcfRnziAypeWZors91owmTJtlO/5YJIR/aVTy7JKt0p/u54yaZK83J4N7FBZ0s2XbcFIve75XSYTQyMNXKfs0EP6opFlG+FXOgKCFTjDp8y2b+4LxX2MSg8zabkEb0433kljk47q7qKByHFxuyFl/ofEV7/pQVfBxCVXypIG5qOonqNpVfjIGyPIF1JXFCHFUQchF7ZmXl0C5/VzsdT6Ds8XFz/RDS0PnqCIXkFUJLOG+GD7h3WoEKJXZpt0LXGq7W4EfZ7TylfF3Q6wuShf3J/bSxeo9oZ+0vWj456ZDeN7zQdUg+pZzQkR8KGVHh/F3mvR4e0wT96V7UriGWfcN/w1UoA7MnmtlGNidZ0tUtG7yapx+Ki/oenhAnG+McWWC1HmwgQHDI0Ne1BA4rEquCVVWlq01aDR4v3FjKWEVWfe4rs5A0ItzW/b22SAqchdEUNAMnuaMzd0hsZSx4cHJoXRk8hJJtk3LpVd61hx3bB/omOrrh/HmkaxLn5J1OuRT55FjcCraaZommP3S0vr4/HN9b/00mQOmVnwaJHs2D46yUbi+OqVB4LQhPP3UtBEAyHb/3/tw1nRaruTy2pGWBH7YRbeN2N2YibD+ODy5Jld8UByhC5KCfjxZFNdp7yX4QE69O7gzYaPwI7001J7BsWwastcarh4a3Qcd83456j4WvM4+0EMJZc+fCoUx6+v0affmKT2z/cC8QsefESg1DPakTfcdwFe+qcj6T7/A9y5K+vg8kFjysll0OzX2ZhhMLmwsuDKZNUSkUwxjpcSTj1NkiRUf4vXY7uy/UFig0DClJgOX+S9x9ffSGM+LrZM/Bo7dMo9oq3d0ZFJMIQXCU13rgKW/A/Q8YPrL45HTyh4uZfDJyiMMjfO2/xsxiIx/rGHSaZZAtdsICypsf1R2VGyagIXpheAEt0oX/on11wSJek2CiL/E+fvusFPkZH69gc/a7lRyWGPL2xugACtTkqb8gh4VtDxgafEGkxh6eHI+DLJXwMRb+hRwtyqpTrKBEpWEGibQXqskOi76lCgfA/V7pfWff6E1vVl+qDuoZmdwSXu9qCoQiCkVop9ijzy+K7UJ7+Yc71/fam6eMM/Di1l7Ng8mEtbl5MKLIWTFbioGceXjzznENv55kmDxx5+186GErNrE1ZWSQX9Fs/vr6sHl0So552E99YVnO3hzjT2IcqxB+veixSza1Ov/H3M3AjY87CM2ck6fjhSeGkpKnQ1izMXNfNy2qbtZgnEuFbsJBzu9XkIuSP/f0m9KXpVY/aL+RjGeVhW8S12IwzWQWLtu1SXqdi0WX0rxJaPFa0lxrqsfEmPEyg3MlF13mxBATfK+QyIE+d23BB3LH58qNAQ3kwyZdBpcmcmXArT4KLOoKxGtyR64F9mYHFwnvhF96HDZpCCGoE0/S4YtRwAebFvFfOgJh9xCIc16itgR34xxlbUry0SyT35s/zHFJs0hY497+v8XdVTq9NGD4NjgcDVcf2P22JrXo9jEsJGYI4pUMbbsOzaJP6Kp2xTDJLdUqiqqXKLGbeJifirdEiYYNpfsRoREvFPhoeqnbfYIo+rMitA8trcjeXWKhSXoU50+2qnxy2ybEFmW7prxnPCQXtUPAvn/JK7HnrvncfpzhXIw9eXTnPhZg/2JXvy3LsH1byFPgI/b8ml3judCevSsX+08sgKJKZJYTKUIqdLaHr8AJcjRUzr0EcXVet8y++jF8+TukulYcM7GlGw2iT2iTYclXTDvPZm4OVto441JcGS4DUq/At1azj/B8U575tV6AU+RSHeGtjoH1ijy0hoFlbYbxXwSiW8Idy8rUMOcz/Ugdciz+GfLiYTVI7CsWfJjMvDYcwH5wy8LQd82i4YG5Fco9OdtuRBU6hz+D1XawXf/zQt2fM2G7ltTSozpaDa1hnQvG617NLjstxpHBdrCH9GJfjXRmSuAV2mM+xGbHfrsyHTWb05yPyuXdf4hvtcKlLXhJZuhlq4hEGKkhmfhoyYMF7q1kt6UEfdq/Hg66SDj1e791es8TOrL+YjmMe6kSm9mPa/XpsZH/QbVrgEDDfHY2ZsU94IFXSgt67gIPLbRzPSeSaW+JqI9o05tNSEim5DSAf3phf1dsfOkXk2g/xaoMD/ghCIY5Snge4qWrxfX3YL2J9TjQqOiyzmK+uXRAxEDZy7wcfbzzk9LuVh0bYcjpn4RB6vbS4xxE674GNE7iBDGlI7+q4S+La/S0h9SeDspGbbb4kUDvUcFcFn0TcEZGb8xozNvkNuYuJC3ehTJbJcjcANIJTkEWrT8dEKjRKBmIQU5Ruli7LYm92/1Z4VRturFFq1s00eo78YvkQOujO995Ss5eDKDZZzb9AkMr5FN3ZIqfz/qHjfR98YLLq5/wjpiDS0ZmnBmQhya+TPSIx3TUxz/VkNVjxhMp44FOULd2OVXv2w2mJrAhomlYLlz1TdiKhaChKlqmQWIzhXWgnYUH2ibmKGKR8oKwD8ag+m+N5nt44y+LYMntirM31c7O1O0QWl6nh27RYM1XyJqTlJEWJCTnVan6sNUA6EUtptED/g59ECbh3VtVLcTOR0wd3IA/Ymf78a8U1XekronsBrnoT51cfrnB6kjL97TS+BNDkSU9fyQCnuA05Ses0+VtH3M3VXO06WCKhQ0cy/ClS7Abn8rsZo518LtXQQMTQfK53lC+YZxJWePH+9EcMlMsk72nG8I6tKk0H23C1GeY2SXj0LlEOi26KcqxmLDnEOcmPuI+YYKTgthFZtpqSqYenhEkvKlSPyZZi4uhzMme74PsY3qaJAJtdPGTgnsPAzOBS6BHYg8J44plNoyq9+i8sXCVLm+8/g4E7pkqLMZU00Jnd8ybrxeYL3SPWNjb0y1xrmi6ZD8R734LZrrprJsjxBzm5MFP/Us91At+bxz/trz119dlsyDEfr6P2vNWIAkMCZiIXmShemsFKc7zl2YLRoERMwCfEOTYYK5b4CM6pb78hAe5wAmGN5521K3T3A9Jnqglny7xoeR1lNq3e0Eg87CGuuRuwuHyXActzMPlShzPlxHjYC92/Xy04I5t2z24Xr/02SS5JPfyot05wi47L6R8cz3Glvhnv7I0q0g5OA0cf2hsgdMf+empc21Zv/046hh1YSWmfEjiynwemtZZR/5qKpe03dzDhQGTy0XXfX3wrDNG34jhKjvGVewQU5tuWdun9rbBC32d4Dfpf8++ilwQ1bxIN0xcRIA+up/69RlnAXrOo6tbwp1tCr9QWvZFGT+AzcR5JHB9dFrOJQveKzOVq5li+e8HjJtkjLcMFzauEWps/g5CrSyxhVQUy4OvZB4WnBHOhdTYxAYrck23gnzTKniWNIBlxpzQVnqYm4etO7isdCWjao9I22wHG9SR/ZD6nF6ZO40t0yResYSlj7S2yGnvwcXDVaQW4ZHpftCfQxMKBGY1AziF34e7a81uiJ44uMmw5NUWZwOHoVxXGmuHOAQ4DgPxbNyVmFjiLVE+tcrzDqB1YXXApeMQxwiCktiLGaAyf5DI4+JbgtLNGk/i3h7D8r5qp4YglPurYgjsuWqBCp/apCh6tFLsE+v25+zUtKTwv66YIybWxpiwQcpuZ7kdQqrOt9aovVayW99/q2jtSdskcYftwv9mnVj4dVC+ty7M1/7DEtvfFKAYDWx+8I+HQ2glGb6K4Gq4kSiLWJMEdyU9EZQG8WbjhA1sA7473C448vJmXKI3Z6T0MEy7UX8gamBV4aLVexjS1tRNg4+bTTl3Lo5qOThdqEAuTGPueLgU638U0pH7odqI0xsUgH05g11xqSPgipKxmqfMXrKVcndQIjhe1/FLsVLrwNalU4roNdIOFJUwZyN7bsUPSLzjprtN9TjOPXqQJbTHnOt7F2iqvXhHG22fcsWBEgYalTLHTNE0MvZjyM0kytu43LaT3YoQ45GZ7xBnT3G9r0CKKxIIf/fIBkrhbcPrAy0imyL9ehv40YqANg/aw+nJaf/978u4vxzOT74L/f48/NAhUhx6OqJtNl0F0bQF0NPwPl4G3/9o+s3GDh0mp9fWn0pf9XD4QV4Icc0yArUE4F7k/FA2qBdFgj5dx2CkoagBegfkqd/73b/ofi5tjxvG+HlIzKMsUlX0JcvcO3a07L77/M3z5TfRBjbGXAt2wsP7PU067MlT5df9ofulLQXWM6dyJVArlLhlN/ox2XB6Ic0217fX2/tsgWJFdcE+1dib81lkQCHUjEN3pu+QUlPfEEHj4zIideIDlMSZJjugHkhWSUoZFii8T5PKNNJ5RDpBYosFOLFhGeqjbEwou+q3JeijLafpN/vnY3CX5SPK3i+sOaOxzy+Q+SsQU5BSOM2Mo6KpbU0PNzG0nzSNf41qxYuWDTZxdm/XctysCI8rzdtV/6104JlCr+Ofzq7dmfEXif/AEg9P5hS0VgJkoBN4F/f5RoNvnJceiwUp55gPR+aUW/VuzQ1Iq2IeaFRtrVX/LqzVGf0N8WlpJyCRPYuGP1yYQlgY8nvf6Vfc5YE0RtQyrNX7Nt253T/M0CvDDwjCTmNfd5adQjWb/eq7XP2Izg+JnyVmj68FiIN+6KUcjOGFFmL2DHntVBlZTSseI1PDRtUxstkJACZeNXrYfz2cRlaFvL/3QZypZJsaNDKYn0imdlBNEqu2lZy175+K63dZPruSr6vKJzv4CLM4x5TpOLBFnGkMh8Gwe/MjXONoFPoNWNJsQCtk/W6BweP4OAyXqYNnM6zWMoHI0Ubbh9bQ24ywtNqr/lVe19aloZ33FfezCKhtwxCkYcNcstJY0kgBNznErh2ay8uXZQZKecV983EPSy6ze45Doh9ZmjGjpSZ6/Pciyen22ES7bwE5Xyuy0W4OB1QOQzC8y0oX16Ww7SoZntyMZB/4/3WT3ezWmfU8OjbSuX+80InUeK1uXnFE1te42JSDPU+GEbT8p94pIlcKrNR0ocXGKtnJrlbm1RIjHjhf6nO6r6jk6gt3Bq5Q47ZMR1NT68VCMlD9jSWLW1UVH0Z3qe1gEpsD4KAkThl9E21kkWJQp0trleRsSa5KiNdsocP5sFb3gZDxX0taUV5p5opLDMDhvdRHjVu+Nn/WyL/yopYvozXXqisKMrgcLiYLPefV4U4Ua5oAibDv+e1DapOxjayqOWg/Hp7tsxkLZ/b5M1tnnUpbFLfzOuyU9DhqN5h/dm9UQva3xIyXYs4Tl4rzOsh3Xm7+YArKlKeF72o+LRVzZko/nV+lLg1181roD1qOEXUOY3O0/wJydDlT9WnZVuq+fY7LlpwvvjuXSDoRbXDFjGc9CHt8km0JvnjYc3V1Wnwyt0qlfUzyYkKiEnb4DsAmVY3SJQ3WLaORWtAZxut1dHqQ9jo9r1l4q27zX/V89nBu9UB0PoiyR6p9hy8Em3KL+1zNv1mk2pGXlmndP8C1jFdcfasYW61R0BnVjQHuAbLpdtGNllQ0VyaDLg3ye694C/gwMLPsWoqPUwxqHqsVlScbfgv6joVeymJIegnV9BD1a/OtUe25IIlNGx4koQ0zZ5QXaMDQGER+u7Y+w++JfKVy9MpnyB0WVyw3pCE6W7bYwIT1fR1OvGpMtzhz8SkYTBa74BsvCuR6f7fuG9x/4gqXkmt/PXc9LgMa/xUqeMb4Q4ojmfw6g49Uv5J8V3edVC3t3szn6iyQS3G1oUnji6Cca+jjLBfxWavgt1bAb5LaKrnZnvZxv9lF/7YyxG1XoVIvrEaQnKoqQdPGVM/Ckvhv3i4YCAJiAuZWmnHstk4cRmxyO3z+Ah4kzjqSC/7vEYgWAAos9dMfaH3l5ZYXaVNBMCYGQCR+SAeU6nF/kaJ+Dv0hI3F3mCljaTBoQOsGPy7Nqh5mLGsyHjJkTlvZ4kgULWHhDUP6tgUtGgFGsuBdkH1D92bRiEzNDa+FCCwadsh4x5+WlR0zPAl5r1s/H2nTl3WzPJ8Xo+vntxXNmR1l1aX1dCI6+INNGPq+cfoyhcODxgg7lu7uXD287LU3hN6o+4fvL0dPw0PTYeOa0JRilq+Mhyj4Zbjg66f/4sJ1ntaF88jPmjL4ZhfMwH1cF05FPq4KZnU/lmQG5Yh9Ms8WpfMwnzIk8ozIDITDHNzr+02WBBZOCrfEslUIK0kR/0u0bJsjZyRoGVZYUly72cB9ighr8BStrSTEPIzmaM3HvZgx/agunpV56gjhe53T4XHwXNYthI2Tf7r2efom/IgVlqq92Lu+3j8l88HLnx160hDLo33ySObTOn/k8SFC7Zd93qHyDCvaX8nVzpI5NCiZhXzTUJFta5k/NabKkzxGJvfJebo2/N5lubY6thtjhbeBK4zebabSTZ+vuJHbPrpaTlUA91YTHZLcsCtW7H0pV44rAaM6hk6VLLIHuJIrUOydqHiCV68sU+xlLX+qeW4WZEUz/E2KsK+NqaKDiffCDA/T7knRClkYsorp5K98WB/i1Pz9h8MNYzolA/W03uY2VBFLlC/WAd2rxH+Ucp02pif/+bC58+Zuc7aWdWazss4uVN+NIVKol3JsHvn4iopxAN9ETsBGFIjOaFbUeELryerD0SxHHgbnb4y1AV3nQR253B2xbcXJzTKU7xAqz8pgOLTZHt9y+nWkAOgeRMYrFi5FVpqm11NSLaeoH1vr2ceFh27c/6Znft7OLyA0vcrBsbi+IC3Gqjj0gL/+SA7iS3A73OuF7CLI6OFbrPZiArVcdseaVfLVUxHRKG839BVvLd0ArkljzEcteY9eYmB9jmERkUA7nZqajlCtam06e1D6CFCE/8pVr/wKimr+YePkvg2SDu8+p/Q7FST9H/xF2Q3eXK53BK62E7WkmiJEA9bkunck6bfdPxLZRrl+dnxQ76bIuwsPVYq7MgQ8rMjV/NC4QHsrPpzBWt2TNy97emhK83x1uUp95teH82BwtHzspLgryBN15tSgGZhJgcCAO5Ae82BqVnsR6JKz5eaeW+tYiySkpsC+qurcVAReg9mTOtQ64oE8K/KFwT3pQNIz0MRnNtiIld2LH0VA0ukZdqgvELJpWbb83XZOs/yvscHcBDtjdFNCJ2MPJFQaHoMtlIWD5+pGnneY1G/f78aquMslyISRO3JtqbDIkgc6Y7zQoGSIHo5g8ahbkQvaFHaEgy0UVdtm5R/uZkX9CHkOBK5I92LEDmk7c1ft1nGMEqGhMt5dGTG07heJF8A=
*/