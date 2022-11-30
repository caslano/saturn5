/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_TERMINAL_HPP
#define BOOST_PHOENIX_CORE_TERMINAL_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/is_placeholder.hpp>
#include <boost/phoenix/core/actor.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/terminal_fwd.hpp>
#include <boost/proto/matches.hpp>
#include <boost/proto/transform/lazy.hpp>
#include <boost/proto/functional/fusion/at.hpp>
#include <boost/type_traits/remove_pointer.hpp>

#define BOOST_PHOENIX_DEFINE_CUSTOM_TERMINAL(Template, Terminal, IsNullary, EvalFun)\
    namespace boost { namespace phoenix                                         \
    {                                                                           \
        namespace result_of                                                     \
        {                                                                       \
            Template                                                            \
            struct is_nullary<                                                  \
                custom_terminal<                                                \
                    Terminal                                                    \
                >                                                               \
            >                                                                   \
                : IsNullary                                                     \
            {};                                                                 \
        }                                                                       \
        Template                                                                \
        struct is_custom_terminal<Terminal >: mpl::true_ {};                    \
                                                                                \
        Template                                                                \
        struct custom_terminal<Terminal > : proto::call<EvalFun > {};           \
    }}                                                                          \
/**/

namespace boost { namespace phoenix
{
    template <typename T, typename Dummy>
    struct is_custom_terminal
        : mpl::false_ {};

    template <typename T, typename Dummy>
    struct custom_terminal;

    namespace tag {
      struct terminal /*: public proto::tag::terminal */ {};
    }
 
    namespace expression
    {
        template <typename T, template <typename> class Actor = actor>
        struct terminal
            : proto::terminal<T>
        {
            typedef
                proto::basic_expr<
                proto::tag::terminal
            // tag::terminal //cannot change to use phoenix tag - breaks code.
                  , proto::term<T>
                  , 0
                >
                base_type;
            typedef Actor<base_type> type;
            
            static const type make(T const& t)
            {
            // ?? Should the next line be Actor not actor which is the default?
                actor<base_type> const e = {base_type::make(t)};
                //Actor<base_type> const e = {base_type::make(t)};
                return e;
            }
        };
    }

    namespace rule
    {
        struct argument
            : proto::if_<boost::is_placeholder<proto::_value>()>
        {};

        struct custom_terminal
            : proto::if_<boost::phoenix::is_custom_terminal<proto::_value>()>
        {};
        
        struct terminal
            : proto::terminal<proto::_>
        {};
    }

    template <typename Dummy>
    struct meta_grammar::case_<proto::tag::terminal, Dummy>
        : proto::or_<
            enable_rule<rule::argument       , Dummy>
          , enable_rule<rule::custom_terminal, Dummy>
          , enable_rule<rule::terminal       , Dummy>
        >
    {};

    template <typename Dummy>
    struct default_actions::when<rule::custom_terminal, Dummy>
        : proto::lazy<
            custom_terminal<proto::_value>(
                proto::_value
              , _context
            )
        >
    {};

    namespace detail
    {
        template <typename N>
        struct placeholder_idx
            : mpl::int_<N::value>
        {};
    }
    
    template <typename Grammar>
    struct default_actions::when<rule::argument, Grammar>
        : proto::call<
            proto::functional::at(
                _env
              , proto::make<
                    detail::placeholder_idx<
                        proto::make<
                            boost::is_placeholder<proto::_value>()
                        >
                    >()
                >
            )
        >
    {};
}}

#endif

/* terminal.hpp
LhKgb+3ha31VgmCd2bFjQSu8u8K8Qr0LNyUUQXG0XXExvQrjLWU54qRZb5pe1fIjBv6y48cARW1TCbHYaE9PXVzo2lAvY9qMucH5NRs4hRHo13Ambfp5Fx76uJq+ZbtFpkDO/QWUu/Uk6wW8tcUppw7Cm/+N04gYzYWcZecPDvdpU2C/2ot6uX5F5giko41mGsvqqtEFMu7tJTLSBAjpLr+lyYKf3fWhzdpCrp9BfwyseVfi/pvw8LpoQfh4+5aqP13exY8gsAaN7x2+zfTz1/lq9J0P0x6g9/qFP/wz7vDHuO0P8/Z/0T3G7T9o7O6v80y+/yWzXueqKujqpte9hcV2g7i7u291gK3tIwGBwMo5uKfvo+UgbEPOjbF2dIPD47n97ei76+dW/V0pn6m4qzs22qnVVmsWn3rscua1rv5NY9LprOmL+xlb7rpVqpUE7zvfRRKzWDfbKbMC+UXeKPcB8nGBA+6oEmLWmNjCXTxkxMw8uitpeTVKoMHl+JoBisuBedzrEDI25ogRh1roa2D6Jc6U7dP62/96ZiedHqrycsLlvftYDGPWRh7x57i+Pff0Oe4wer49k0TxSy2A65JpfwC6UvCPTpqaT/zzh3bkJKz3CvIJHVtt0iqY2glqVZRourO2vJeb1ioMtlsgXpkTq/cAPUhP4rNn6pcGCd7mUbQPt2Ql/KfacJVTkHYHiCySBW7koT7tdPg1K1qD4W5cCyokYvvZqCwrJLgTTx8nooC6ZnUirX5mT30ubv7YcMb9GK4/DZqKnJrk9DbO39Kf2cHj2kil1dXYlDZ2JW++1F3wRB7+7wfG3V5Z4AeMKjiOHDsHxut9haPlye+tipIlXHxQGdBtfhhjwJWHH+5FNd8uB3OM3z6NV3Wmqny5C+fqkubdFu1CTTUjXgqRWIpUbxrAcCD7obGQO+l94DztMmphQdHh8WW6XlfqjX9sLZv2UX/x9VWoNym7tdt1NE2s/VJXTsbn9cHfeiK8hIGBzMrnsWcLEQQL2qfsy6kbniy9RZSyoKStYxwO8l+xJ9LTE0l6CvwkGniBC5tPOOXpxddUunNkR9gzKUYWn89JZGI6NzmehBjrD1iHv4LeOoCwBVX4agiOIphBXnQsrq4BUhm1Paclz2NTvZOypnb2dQ+kTzgFrTzCIwDVP6FneAWiHy/hI4tOkrfQLWEwSnKNQIjLHDT0G/+Ele0IXiIKee9YEvwskUnOqEo4EercCzHbiVhpQqqzRBOqLCEaA5NlxM66miRTqNVJmaYe4CrBr4VdSSEZbBIb4480CL9oWGemZkbTflT/FsjsTruHrhIp6a0Ig7FYoglr54OXPx083LXhWItkgsoaxlCJPqY7K5HlWOXvWqlFI9IHpugUAR1IZAvcO0bJO8+w0/7BqudEeA+vDrqr+kxZfn8zu9aD34xW27XbwAKpu/L7+GxVvCJkQVHfneEXxOurnkhAFuMwUFWFDZZ+W4/EoBFMqEmJE4Re0ut5J8UM5qYpYcCOiWUit5luvjOeL+PmaDORO35sMoMYCZ6Ely7c0ayMXHEzSxIt+wMBuFRAc1Zf571GrFPQfsvI0Qd3uBA/xo3C09qS8RGZw4nAeQquSCi1WEXoyIeYLLqko8MUfqLI+MnYf58VgSbNrr15e/4Tqomvhd48AHGAHMTIU6vesSuUrutih5xdxRC2vAP7hYtv3dDpoO+c+Rol49qxaNzXslXMTxSbLmz94p7b5oqVdrBtx7PJVO2lrTHtM/V1Mr7uYSVJRwqHW7oGrNypPoZHC2R55/IcE0KM0SsMSrTqcdUe+b5DRparm9G1BHSOFp81dLLlCQUdujTehYI7B4rZ28cER7Ved17ejEjtCSl8H7lc411TYpE3w561GlFjs7xPh0JBHEv3qVljzTWjXQowMESlay9ajBUFEuvsFQa6A7qBDMSikyYuJ9preOosGuYen+DVrnJ2Uvu9yFRSe/XWSB/vAOo1A/fQ/xKAqRLfKdmFlJp4e7vbP4X83caqw4rdeaC6uHyLuaABRtl79sY8NauUy/POWvAFxk30mBnyytaowoZ+kPNmezyJwIzaFGFgKoSmHT3P/Wy7Sdsb98VTAzlT9K9siRiilqazEhCFiPH+pR5fOZRRfNbTmqVQeQHOTKD/aE3vwsbQIHYzBJ+7WrgbJ5sTYb3Qv7xcRoFShpKiUiavZCYhITFq9UtqctVuxySaVPWSXvp5EoiL2i5TkTOmFTQ84da4fMDqyLSyjqLBL9sn2FQwUXHjaTSxhvXOr54RxawFLZhxTKcnWCCM9YfC6AzxKI9sZsOGkKuPL1X3Mke1sTe0oWu3umAQa18PaA5MLCwGhpQ9pE4Y9vdml3CQulU9FpXm7tK0Q9L22IeKTneBr30WAweZUMs5hKoV/0aqx33kPxE8Wlds7OWAA87/WsGdzitQYKhNcLUDa4MhK/FFmZHWcm9iA3B346Ndvz46hDOizduAVwrQgzr5QOKEjbWUODgpdIFISppJSkkJ9kN9A74VKaBlCPq/fy7YPwIguFt+Wa7kLeYgjnskJyUpjI+NmYVFQKD19U5j4WEhCVy9efUIZuWGc8W6f/QGFJHcFtL7I0QQ+h4doZO7Xxti6/rFvuD2yd9+fn7KePESJnKE4BIVhaAHbqZC47C0PAdKOzhsVtIY9JsrD6jleaBBwImsX8DHagNkKEot07h/CJPOtpOxD1R8w1UDoDDebaUM7BsoZfI1+ZIHplrQr/eZeK3kGUe2ELR4g+QVd0rpLp+dmfN+ZcNL7wC2qObwwavbIy1uxGzuKzz9KFbLdgWgJWULR24friSJ7SBMiLztE0RdxYhr0DRaIeiohoMKorziC6Hu4SovocdMJ7Nh2wGFb6vuh/9LMi4I0o8V7+rYGL1D3fmGHaTty9q0hvP09IQLszapa5ShwJy+mSuRnH6KGveEH6SEwdSkQ+Jcj1ccOFKDQJsJTP+l84XO3D5z1hfCAj4EhFJiGWd+vp1edbyUYrcoaPd2aIGjzTa+TH49Zlvmb/D58wGGevH3FAkkaSsStJ4GZ2LmMvyqqL4calfLwhVs6EDZCWgdSn998cms+rOi/cmfawcgoIY0hQQoYJs7k+T96AcjHQjvv6yj0FzWUs4loLEHHQpZIwtAeQMT26J70BjW55nSK4sRIiKUcNr6RibLEaFYKQzrT1ZGVjZ0SdHWzBT4lAYIjdmsibOzLfF1SnNvetsYBpZEIFbsTGkciJz+HFwaKXWJsEky38SnAgiBWEBA7UyWi/uHNeGLEgNcGnvhZfDAz/ElSfF+UfGUIrBLDNXIFD7nFqPzTRICpFownMhBndmih3HUm1DnJkL8fZoHMfFv86ELLYhTBDweQX7DOysY/g0HtLtzbM/C2wsYk2xTq99fewUNNfqLZs+zwONEs1zt8pfAcHusljM52VFnbuIeLC24vuqlfeHUr3TG/WRnIuVxyo3Xpg3JMIzcoVcACCz301BnBjegjLBOTXR3lloUe9Rmn1oy9aS4rO1HlkSnr/gmIayyINyiRY+mnWsXlC2koHBygb09PrcxsF6f39MVqtNb0gonYOuNW7uV8cCk1v5eUGG1sRoLV3pbrHIITfYHJVqxk8J5nR5IYF9UwTiiIrwGJSkK5l046ncWw0O5iOnPwQ0s7ApuxQjPF3FIWhtz6AwzQ4pJ4k6bi2/0NvlRt1+BmbDUYaMaKMFFl61LPz+/isg+nhLsCx1ZwjoTvm4PqGEIdIi4imsUnkHaFfEWeia/7AQAiEObsTekEajQq5F2/Ba36ReNw+ILOoCFSTk96/X01/913ujhr2YwCZh+rL8zfzD+V1X9p6vNanOzg769Vl/h3tHTrPSr1eELffkZmsbrifjIM8Xcm1h+2NPVzvy8jnPavUKcKRefFb9UA3MS3t24w/Z5NGLfGeucAzyBpMGKwb13An5Vd9vWn5FbdQ+zX+PuuO3VNvf39eW1tdauB5U533MmEmIwHDLh/JGHqQTi2bIuEhpWEBlwZwL/J7LVOV/Yk0j4Q1B026js54kOYltEPO5gBkD8zBRXTj+HdYsHvRHjQ3TTkU1KHu/qfLOENpGousWl4+Z8/st6q2q3bHQC4lSfxV0Ro8fjmrjE6VdxZCTzDZtJ/twfS4eGEMZxxKcyLMO9JkAZXyFG5CZGO7oFKREMl43hdZe2vJKmBZhfMNdezV4714s8sTLpV7jL7T3e/3pjyIuXBSmv8nxsxzkKrCZlWSKOvFBkm8do423zpTg7H2uWZrbusOfSmbtTKcb1HWuNXcG6TM+vXObZaAsYhP2x6aJdhWHKHCnJobgWHzbNzTT5a2Fqr3KRFDJC+uRRhehMATSx6EU61LngdXoiM0sqKSHh4JwLQozkq9KYUcIxonS7muvrjebr0Oafn/lLU9XF/vsikXM6vw7qb9hXs7NaDNXZye5k0DL4h6ddpZGpnyvxP865S0BSTnA951vECwLVfBrgm+Ft1TwUtaH9SSQVTZ1NHTzAnfYWyNcQ32iARAuvQzJpleiYfbVazluzET94rf4TPT+55i2pXjc/JSPq71z4BSK29WjW72UhZHgvPif+XtdFenfeANLXi/V6p+IGQf0V/A29FLmSQxulyxLcBjRsWcGv0n5Sfktn7m7+/3yQdSj3wGrp7R9DGw5pwID9ZgUNaYMWQkxSDKxJvOqs/nPoUYB8FC9SJ22jM7kz0UMsrJFyr7lVKJxHA6HoILFZEi3K3liVowi7N2EDJ1Ke/lO3j8UqsHd1cMdXnOPZiY0pT07siZDJJxrZ4mdRJf8dS6xYvjB1iV03qB3E6rEStjK+95R8ivbqU/8cffKYhlH4Li6SDknCIcHzW0xXZR6yea2ooroni83TdTEsE3HDi+TG3AW0LtqztqZmJzSEFtcSKxnl1con4uPN6es0rFO1ldEpmtCt7TSFBlOZ5fYkf2ye18TUGQ39ax5RM0x3SEOBipUqpGhn+kBuNZUw1Iqveele2ABmBwkoMI6kdnHVeSYQrtmbmhqX1wftNqohVziEpFDZIhufgwfP+tET71VlQcfuS+iRuv7MlKDRJCONX/rlSt7GUVzg8NhglZEF2Y1FkMcX7T9el8dJVLjh24NwdRD21xXD49VZ9dVS5q1+N2wi7+JsWejLLFM8VZyM6PmJQqt30myCtIfJ7I5gijZQ2ffnuT6e0bzvRMJ/nih9Fh3045z4izHy62iXbzfHolbZbKJ7/gqCI3z5gsgGBaspyNDedGTlTjlLEYRR3//8fE6b6IVYfzkcEWIUcLkAzyHtHXLbwkMKeyJl+3HCiRn3CaFe0+g09rA6oH4Po/Xsecexlcwxl7xXkGBW9f4P3/YQHQi0pAE4tp2Obdu2bdu2bdu2bXRsdmzb9uTN8p05s/jq/qe2tbm1KKj5fyTPLmRWgw+KrZO7ojpNg0zNbibcUQt4mLrcINxsCbwVstFZCArOmjs42t5o856jrmOhsy63OtwXZs6etTeqOD670X3Z/SaMODWKeE2Z32ZPYxGISJVhLZM5PJARFYsZZDf4XE8GkTaV//QHUMvbZeAuydFdr44SVbcLPo7ukBiDjXK9hW67txOHQ4B3QqL6PKm254t+rLioI4ZLStt83IIw3maKpRoK5VTxrJuyu1bcqKSalaMEeq++92j3vqmua3OWvf3LzpB2zpuu1wXmqUM4Wt4HStsjMQ94cxXq0h7u390j5CdJN4Y0a3EM8nL7xoiJ7ojM1K/U4/ZWby3FMNqVKkdglB+N1qIiGh/JhtGwbMwuw191MHhXXXW15zRjMDDf2Fd5nA4SjUGTCb+JDHniCKQkBhdwtw95ZLa3a+Mc6eEChRaLPqgzhu4LqAs/Oq2dqBq6m6ETE15w2oBKGV4Qs0z29pruo/cjOJHEKirhwxoUzjjIf0Z7d+kU//Q9BEQzjtr92SiW9qe5/oRLqL9crZlwE4J/Uv2rQeKEcj5dUHjpg+PbnqHZeRNqg67ApjwvH1/rB27eE2SF5aFRRN4t6hMEuT7fmt9wgNh5iDQOmyb/zeifR0bOJo7M2YOO9KkhM4xNRZtF3BjoXlAt2Uv7dh17pmXoJfkvy6EyDiEbvi9LFwp8huZUdIZGst6W3QBvEdQksxCyjxelxgnrRxUd6V96gApseN8tdrftAY7PWWWqfOnXtxZD2fGgDSUVlMafKszVc+HOPYaPttGouxJx7LOiGVJ6MChCAPEF25Q23Sq0rwcP4nU+2n9+Fyk1059Sfmlfsz/nKRQSB3gOJPZCKi3ope1uhp4gu4Oo2+Ai1lWGgZuy0RYT8rc9CGzGOa3l5BPpfCQPVZipJ1JU4U6sJt053R0MDg9zrotP75WWlHcROlSjXUoQKx+2ecg849Nng6ptLk5X5456Uj70ubQjSSlwH0s2HiZaA7IOs9Fe08gkcONhhqnIy3/EX8pgR/fqaoQLDx1OJlegSbBQpdChuERBcmUC7Er9ZLQEkcN8acSwbic9TsFJ/givG1xF06Z38eeJ6svMXDpFB4vUHMwC9xi0cyckujWVL3xnf5oXAIR23aqSH9dlV1dadtPrnULESQ6zEGSsF1VX5Hf92xNjh8nUuIwfWrUuHcTtvhuH0rWnLQyUC4n0Wspv6U9PUYiWEeWUedyM8OxdEh5iJYXlJdjFbx7MBAN4WzEe+/SUu3bOcU10JEoDfXTPxydQVzMuERXlnmqwH/nKhLHQdaVGjZYiFSKfvGvMVCpFdjS1tTN0+2NkuvDFsikmiK9kjiwxUm3WBfnsehU/Ald7hsVVhDtwIJrZkK6iCXRVF4CdDQmfbBWDUkIsOHt/ExAIFeby5rOqi1qKSt+ws4T2lh7J0ZhMmM0YpfyQjNfmmqUgdbRwVA8FWqxYGpxxSHjR2c+Yazy/uS3wOeHjwJfH6jsJCgDIV4ZJJZ/tp/H1U0l233c+zhKxoKmIw3a5yUU1oO0XGZrfFzEX7x8CwEJJQ6+XI9QClqIyRoEBBxi3WIoWMwMUAjXcXbCAO+zPf0IVFofni73U8DJskjt5OBh6qlOWoqvJQHzPKR4EeV3QaKbmInFYytKgbpAEphApbC0eSRdtAJY8ak4liQ+H1JTAd4K4/Y/DVJbsm3rglSOAygR5hcN07T4s2CD8ReV4TfOY5lAeW37gSRyHVdFxToboYmP8hliA9qlhLSD64ZsnoifXXdHIQOXQNbSAUDoEGamFXMOImVq2OV4I3m5Q1djmBOWvem+XTsWtPF1f+NlXAIy3SAt+9dDSavdja7RQn8FZCa0g5pWRvVj8+G1O5kMpuIDdY/s4bCVwXj8XClw/+MtL5EZ1idwP+sXPOXr3O2id798qvdv/jj9C24jgzp8hX2tMyac9++kFWjoTjMW0fwVSqv6VRqz5jzFRA+KHsFFH1L628kpoq5i4amVFtwcC+f2V6Qj0Oln96ORPY/fDppU8SO75t1eFqIrDYWssRTcZbgiXlQ+hzRA4y8NrIA3ytLCRXK4DkAdgA8X9R3d1mLsGJY6njFW/l4faTONgbxF+I531gdYEw6PHidQzfQ2g1KT01arTi04B2PfZ+1BPaBxMLuNNJXE69DICowK6aOiF3Q7PmCzAX5spBi5XWiVajdTP5P7/Kj/D
*/