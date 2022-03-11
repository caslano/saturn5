/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_AT_IMPL_05042005_0741)
#define FUSION_AT_IMPL_05042005_0741

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/container/vector/detail/value_at_impl.hpp>
#include <boost/static_assert.hpp>

namespace boost { namespace fusion
{
    struct vector_tag;

    namespace extension
    {
        template <typename Tag>
        struct at_impl;

        template <>
        struct at_impl<vector_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename value_at_impl<vector_tag>::template apply<Sequence, N>::type element;
                typedef typename detail::ref_result<element>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& v)
                {
                    BOOST_STATIC_ASSERT((N::value < Sequence::size::value));
                    return v.at_impl(N());
                }
            };

            template <typename Sequence, typename N>
            struct apply <Sequence const, N>
            {
                typedef typename value_at_impl<vector_tag>::template apply<Sequence, N>::type element;
                typedef typename detail::cref_result<element>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence const& v)
                {
                    BOOST_STATIC_ASSERT((N::value < Sequence::size::value));
                    return v.at_impl(N());
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
1UI6hqlQbpGS+0iV3UaAPAOnQXrIn9q7/LoPxnkerALw4Br9Vfv+D5Do//jWzdcTw/LxHp+ACOUjPdjmstdPhuZEfIgf/4hPmfwHLoDRfyvEPDP8W9D/O/ybctE1fMD5jCtSzA7t7N9CxEfZn2cecj6j52IT0VxfjklEfGAsJLvsJT4xu6yRZ9SWybcEnDtcAedLUcAeLYgEDVwBxkQgPV6gyEjsfmePC34+wJ9u/Hkff07izwkXyYpTATzyZoru2dllz/Pjssv28kkSPOelSXmzxbz0UI3PR9VY9J01On5Ija2MVmOa6E7PLnsWa9yj1TiH1jg3VOOzUTX+88J31dhx4QfUuDxU4xzRPRdVwU12xeg8Mu5t/HhLUrHvE3FWY3eLU8Rya98mRGuCAfv61VE2lnOARA85rTVuaUAs664vGxHLgm3OTiSiYtkJLk4s62p1KlY5vs3ZhYtxfRk0uNtFPHWawdRps07XiBX5nVZ+7FmnVZcbi/yys5sz1RQqNSji9hgzWpChb3oFpUxuYQE3s4BLI5cjrI9NSFKICd0jUlngWCLdVvyAnsQblCdB2xguDovVQbH9aIwJbLtsBIEQuDWftTSjmbsW/q+A/8nwbxVILv9cdskgcJiis1+eAvInLoFyCtygsl62wA2+CZRRBtTa+ooOBa3DB9AE1nMICZ6judrOzYTJkO5o4ybkoLkstzwH2Ckdf2Wbk9BSlsMNejeQF8MNreCGHB2sstzcHJ0Zl2DHYW4Wuf7b0BtO+zb0hl9a8A3pggFZKZJALNyoG38gLg8g4fW3ceOlxKy7TNazx6YX2uo6tkCaAUyzJ5cbW1uILntNtYWDyN8Jhf2wdlvRgDeucmBPGhenxjNywh4rF6s+WMnnc9TT5magnpeT5/C8XJpOnELqzyGpslFMf1RR6vrWKOp5m5wn8Agh8KIDbdgtcEMCzk5gpvsVfhCXz3dFZw+Utl4qHEQtf9P0dkc7nwGfTM/NqL19EE1WaXbIBXkvzXitdM33HZcfCVE+9hyuyh8HsWWiM9h3uwkb0qOSTlhIFv2XZUgDsBIEcScJs9Fzc0P8C+Rh9LWsQ9hk+Rmkq2YYrblyHJ6MwIHLYOprSO2V8FnMUieiioQtwkube8ylDTC4O/T1NxtMl8RDdGCRIb0mraa+8ELN7RcK6gsVvmqouYat+4MBIYmtBu4en6EYys+chvZ0aPN4np9IWGhTbRaekuCWQuSRNkXpU0aoLyY8Z3hNq3NYR/7QpFn78hNB7ryMHye1PbkMIskydX8QBm4LPTJ+DXn38lDIi0NOBaqfCdUfwhl6QAcLvR8PqEjO7ultfExcoVU2xjmBV7dOb3M0c4soijw3K0eXC5dp8GRQnwzqkwkEXngy6fgprc4RvWwDIa9RDzOBDoJ4CDPIJvjVaXOXrXseWTsF2pErVvay/qdVA0lKF6Y342m6XLYOz6zlUCJxr6OZ9W+laYijjd3+cz1dGzclCUHTpgwElfOvRNCpg84Ru1LA1k2BhwLWn48urZ29ygiCpPWNpV4sPR7oCsNBKhQmHOaOemjAmdcVZfphhC0D/hQtmn3GgLMX+zHvEO1gDN9Mz8oYOB8MC9aPm7K1lb1fvnpIx6/At6b2/loD/64u3uz2O1FQC5rYBzzI36m1172u1c7W3QShagvuUQOnH4aa/Hj2uI+h27+9M9DIJ2cEMXsug3SvI/w06flGoyAiH+xbrUePOPCS/CSPzwBpPp+qfWlYOIHO0+6fT2t5R42Rfw3dgi33GVdKLRltrsCiHPq2BVTeplAxdfWQ1Rh0/LP6NFAKGNaIJCFZKJKECqsTWKRPb2CuLhyp+bB6DvN9KfB0vrW5z9r0YWzNR9Xxb9RUXtDVM/zllJhPwlyYNpxRzWWqYdJGEZIqSki2hGdtiJT4jEhJYOigs4NqPIOupDxBuZfIqfP3gPh8bz1AGK4hs65AILjfI1zbNdJbUW9BCYhoSpKA2LiBatM9QPIpEPWjvmTvFmRMX7RFIFF4mwZ4wo8jOYMhIh8fS7U0pUD67U3ZlYwGiZJdmYocVvKM6hHVGiKXe0OsHHU6FMeg1ErKgpp1exhlI4UOtR4oxogLygZoQ4tdgfqzK3u5mdmVPWrPhhGQtPeJvPHfrogAo+jpAciIgoFcfpG+PDdqxxiPYCB0YVNt605olkcsaxedR0XnEdHZJIzksTusBtwORp9L7EMm9CeyECZAAvtAEOdsZfIE9oEv6J3NwT7QS+9S4e59emfVszs60Qzb9DQ1YSkYlnQZzYfQKAaNmZxS6wzVgqZAaB/ORVsq39onV5497z/OjwtspxY00j/xkfWLSC3K2oXzBtZfqRY+mX1oI9wZC61aOWLhidFFqeY4bKiot+kjA2VUGRXnCfKpCy3Ej7rIz4s0hmcCtRk/4iJiKCSGhjS5yLOhkK9RzN5OzZbOKr61K306L5osS8FAnvLk2fMZ9BqxVIr98kmpSyzplFqfFEie8L5umYsEPoCp2CU5O8cdFp2dkvPEk9qTXfH4bK5isg4S4BnJZOn9Jz3Gdmq9XUTcWqhtVGguhhamooF4E0QYg+Pel5rhAsXSg5nt494X+f4CoTJNTw8EJ4eOCHeLhV144gYVVkLlUR03PuDsAindpZqlM5LziFpam/SOnBraX0IjWDLnTEgwA5ksoTO8bfPFs2F9W22/bRTQsPAcAvPp8HBtzlMwjwNPI3Sf1OLyYhcr70oDtSNoSVC1IJCn9xlcop8guOmZWWElAEsODGC1FKRuSJ7YRqH+kHkBuTWhWHkZM2BBdgUCUiuE+wzX8WnsfqMQvHUDIwR/sdkoNPUEtjTJCeSecEnC67RdXGwxiX0RJe3CYTxRh2+T9myUqtRWTPd6CUk7hUcZmNrzuE2/6VappZkw7L72elSh9teXXRhapJ9s4sfU4MmfWLT3QaV3i7wS5uV6U6Aw6DMUoZeQ4SLqVk1Zb0EcCnKWHiRMh35vBdE+yO4rPEexvOXxUOrQIttkKxfP7quzTUZhyyC1aMUXDuCG0cqO6F3Wxcqlu6xWav/0Pu6MD9pPZZcz/FhN9XiMnpyk5//R5ORNPo0s+zIsdk+Bb5hVNhyl/5bvRBSdU1kTucUe3H6d2WBl9307tOjaySZuwnVjeKbBpb+uSM8lB1z6rMu4ROmwbLpuDBeTm2XjT8B/MrtPP7RoDqSOWQCF4A+/fzUEIsmc3qxWpto6lUe/F23srFFYT2gWMfcuU8QaBnWdo2gb48HDYfBpDV7c638OVZM6380Bfy+awOlcRPg9oqVisKqEDPjnXFDBJqgiUvT3INZzoBt/H+uiuM+I+Cy+jJ4yRYrTXLHjsSC9BPrphQJDV+zwH6GX55ro5QXEVH7qIQpXKTlhGJjEAKKnttH6UE+qjnfpxmExgEiVeNI/gO2C9RZCaFv6w6pRH5AbVR8aoM12qRpRYButfugq7aUTEfpCVYWvJMW7NORen/7gBJOuye0z0P14eFf3KJ2ppjlWMufeFeXrwlim9Fystf4P1FKG6EKbuqcZBZYYxlrPcDLHggVl36E6fAc1sNk2tu4Nqjt8RtMdll2qO+ztRyVF31+idYe16E6letNYsqs/NGBD6kODh3xwR5T6sLo/NN8j6sO7wrnItXie9t+oDz9/Hrm062iGi9SHK6n68Cgm6Fs6Wn341ZbR6sOQzo4C+mpKOxO7f4yAWjvh258iZsxWYMGT9lj5eKq2q/D/W73dtF0ISKvp7eqoEu6NrWG93RYacGBrWG+3jgbs2RrW262hAb/a+gP0dhoxmfudKoWjqkqhE1UKJ0IqhRPRKgUTp62eH/z3VQpvfRYSuF/8LMSLVeFU+f+MSqG/L/SGb/eF3vAppAH/B1QKv06LViks6wupFDL7wiqFK/pGqxSe/Q6VwtH/lkrh6H9bpfAaHrgnD5OQSqHiv6VS2EQuUSnkkB+iUvjJ5P9VKoVqqlLYE1IprFdVCh+NiVYpvPZpWKWA0t69+zWVAiLDoFqhC0OX7w2pFC6rECq7onQKI3eHNAiHNZ2CMCYUsvf/7zqFv7xwkU7h6ReidAoPRusUvvpLWKew6X+RTmHOC9+hU5j0wsU6hdjv1Cnc+TLOgR3/+nc6hSfZsE7h8GidQjX773UKg76ITuGB/xfoFI5+l07h2Yt0Cv7e/0qn8I+JqFPY9e91CiVhncKjQ8Ab+ZK9T6BOoYz5bp1C38chKr9vCKn8/w2dwqr/Sqcwhfmf1Snce9kP1ik04gAU+pMrkCWqQ1CMYtU0tp+c+TsKHf3SkmT7KZAuUmClCBQcqhDOTdxsqhCaQD5rkhc3Up5Gj9k3TqFghPeq/MJ+J1PKzZYePIrm6PtMejktUDK8DGhbCbPMVUTuuFdDZMOEHPBSzuGssiAKEIOXCBAMKYoWjKAd7H60YQIei7tCKrOw+x3S1xV+hRsrvY0Y3zah1cDuT6IY3xTu24rcWDe1ANLK8D5DjRGeV1nkFO/DH1Iueo/6HIN91lkWwilgqIfCUgxM2QspjvoY4lhKAYYZUrpE7Ws3OTIT92Ld5FEDmsYnf61A2Nlj+DuyHkMwi5uYfkJfvDwCPweSGVo4WKUkfwdnUI4JrSYHb9nQH+bdcp46abTquIlevJKGDaqUH0/bg0GlpPq0onjXv2i0elfAD9mlqOaF/HK3x/uneAj5C3R3owviDi6Hn1Ip6GjdyEqxqis8oc3kGNlwRsh5CY88ry7nJnnxjqRpNVlgjUGok5SXqN12WYsvzduIs+P6GOrJ+KdLtAMk9qbc7BjvXQhHhORyN6IuNTitv18DV7TxYv3PIHeR+TyUI2VSaKSTUhewn/5TnFfJ3APBEBAUK08glG1ll/ClCe4d5zcsJnf8WKfLjuU+h4f5yrWYjSyHIDFWeUctD4NCRWSXdSNj2sUlUUjcTtHZRUuVyjrlPwNx5KAPgLrXwGXjGHqcUOsIZ69J/qTN2VNHE/TUawl6Igl6aAJ1nqZRazirjp/VRt8aWSfojvyb0XEATgUUSNFOjoHQqzC0hRSZQtBG0Kl6KouNhKCdKaQs+Z36rGGGVb6tUHiMVpiMper5goMovPl0XuQE6VeBfrR3wEx6rHk3Yv1LzS0h0H8dGtvMoE4JIoL3+ojgrWSujxYVWTru8ZNHTNJ3PQNd6vYllyOAFwWpkc2O1spYqXU3xvhMLmpTVlq6u2a9Cfm0KT6TW8zEOPLFhOiIGN9lK8pb7McPrHEhBPwuDBYtBqE5DT0CnENE+G2f+UbKIcV6SOGRDke4PelbbZvfFIuoKYyjlUPoJ4N4FWS/ofZcJ2TY9tZqe1N5C1mcAFxFDo45dPc2YT2OOKyLfPhb6MPIvGvEdjgGNkyrHWmCujdfJr2VQYlqs7WIrFwMDMASC8o7pXK80JoGonYjytgRIiQEkyvHC02wBv1kMbXCry1Q00MSxDxMc6lZIjnomzuaN0zNoRXaatdY0MogoxlelBZkuYlmV/O+FpW3kMEizyVXjtPy0EaevvG7kxfR40QIn+55FbuV9W+gMBhZsRrqzE/cZLZ6P8JNc5M0uIcmuDVsSGoECksLcr/G2FJUWg3lpldzSy/B4r/SqBbIx9N1pA8NCiBRvZMZnS5GS8d11TvjKqAn+r5F+CVoIOt/lx5Sfdocadoj5kjT/ObRTePNlzbNBOzuIxS0Lf+SFkoGtVy2Di316p3D7L4mF7lfo2xzL0m/UkvPjwN+c9jtIvtwPaNvJxf4DPXOC6s9qGqgpy+eXh9mqChWDzl+CkUNxPXtk3Ea55lGtlig+P16RDumFUz/ueoQVjuk7W36wGBdq1CYSzxILa5LtwbgP6Mn5Oj2Kuew/W8u8Xai8IgkohEfkJACzgEViK9FKhwIu5pVvQQXhQ7dhXWgdLtgI2PPxDI9khmEfZ2GQB24z4q9nSgtMRnftluyyIcPwsqP2B6M+nzsQSonQk9XsP6Jemo6GighYvGwtBKxKsXCfuH8CLc6cKMuYFop3bw9ObBouxUhBlGSg1UtWXqXvGTR6aBSvb9pS241nuaVuhBa/a2aSgWkaMk8ugnlWhPctAnXkSW0CYPq27Wo2gGd3AETozYbz4Dzs4Qc60e4TKZ58Upuo5j0CAbFSiWMT79MScFw4QgjFVoghCy30EmbvcLCjfWqnfKO1E7cFu1ETVAssFzcqvbA6FY1BlQj5QIGXvAzoDuv4LfJLrawdahR0op9k+ih0L6JEXw3em47hex+L6zHuqcfJECcFNQjBVv3JdUAsP5P8WrgEoT2NDHPQqUQoR0dU/wR8a74ODfpuAdJVAx8LNGsbLIpmxg3WWqkCFRv/EHViCJuDFsnUbEFZsL96ty7ny9ykxmhmTnHTSYatXmX7nETi3H0xBs2RE+81ZoLj4ZcU/r98+7nY5FWwnpYW0U9XwCzCK8x2iEGrFZSEsw3bQAELPvTriUjUyz0WIHuxeVZ8BSp0K5E1FU3u1W7o3YUB3J9aeVu8swYXE3sHY5mnkGDMhb3tB5GSKXd1BSM4tI7Dm+8RmiKEQrOKxVtuYouXiwwws1UXXxr7uXwYK8v+KmUSdn/ptyA63xtKxbgOLnh78WeiuzCT9i6JE0SbWbrjHhro0DUw8aWg5gSXQx8sM0gfZBN4XYr7zpUBxdsIdGN0dRzRQL1BpAWqKc5Yh3NG6/S2iSsMepq1kytEdbYdWr74DctHhr3U53EQpOMb0GjHMc2HAemTK1i2+9ls0Tv7Ir/VNUGnDn4HblV+Kk8UuFwQ9xQs54rHGpm+ARXSF/C5UhnQcKhxnIg5hjnqusoZhbNQEcadPV5Ju8zIDIG8iyQ64hm5oTm9koeIziDpnzFOew4v+1B+ynpayyCdhtOCQXGI9RtrlliqpHvbc0z1fpPwfI+tEKODyyk0o7Q9I1LO5qJhqLcDcCdz/eE22afQWEy5qvqmCWmsDpmiYm5pE3cbGiPHI/J2sw4vxYK543sDsRGVOg3V1KakAVSUbIR4m4IjbEPqV4HIP816oeAz3B5YL1FqMJTAbCcH8XWxQqtuTEYG1gy6Gjf8JFyLXnlcZg1P4aZ0GaqVZBx2HZgdQQAksLqffaP8MTdRyB1uwIDNze0/LqpC5LeBG0lsZJX/xG2O4TWFXoQmho3RjS3FbSLkJlHiRZPxSHP7SJ//gcer4YMk77fe0WbBhbdhez43nN0f0sFi77lH1TvR66Prrtv58Vg0XYtmS2cjPR+qig/BCx6XcL3wX4PjUTBfh88ES659QSt7LvAo7PPIbgFgke/lBAWXos1Fz1Se82HRvupmnMGPvePiBHJZQO580jzM4J+pWq2x+UmZWiK6SJjblGVI208C/nqmrayQs8FdNETi8h4wpvKasiIxEY0l0stK6M+GBBkIKa4DpfKP3WTbShCaXjh8tSzeRbUouHZyUHqjOxpH6Sj/sXxe5VTF1JB/AazQZqnCgOxstunJ8kL0Ay1chgx93oclCtmA6j2o9xvwLQ3O4srl3RDuRaBc8NrPPMNSm724zeIJcM0iWTaKxVYhpoF7qfZJQw/xkVQq0Qp9hTEEJmYXcnwyUPNBo51kZ9qUbwxzgny0zBFFMmT61B50EOLU+budZM/0kpaQp9grHqoRw+fgTNKzm7ywllEM9GTquupjKunHoUudprETQH6fhmsNqThUUWprbCcPY/7PKWiWYSVKM8UIeXWXfNgDOHOkcQj4qdYNiiWBdFJhz6vZn4a922Ded6t3Ox5G7hp8zZzE0jgeHhylf6L7h3lAaV/FTWOcoJQOKyX416NQx1h4bDB3rEgr8HsqQPChWAAga3Vr1B1ZwdbZ6M6wyYhWMw+9CgqWqsFksbWDeHbkgRuWQG3UCA27kqBxHOXC8TE+hv0iMAZZP1HKSgL2knohDetfS1wTfhnH1LGoRZYk1+g4bnUHF5T1vc9SSMNrP9hOqCHhY9HhJ5h4U1DQhu8cl8N7eOgjufC5abJPxfIcu4WgSRxzgJuDjYqRSBm1o/Qc2dbdE2wcjoT3pfzEQWFd9TePqwcgp5ReTb5Kho6I65kOBQyVcszpvZNFENktpEiZHZxJnuHbEjogo6CfvL3UDDJAR1bh00NfQOf0e1t/BD4JvO60GHYKqHVGIqumZ/D/1xLGeN9je4+bfKFUiYIrTFQKaz18vU+xnuERnuioxmMNujkNF+st5NGZ4WjxwutsRit10Vq03Fjib8zPA6KPgaSlOqtoZAb1gCCpfDAf7d2h05jovvPaUrMFhR/ncn0iLTF3iEWmERGLIC/VNyVLbBSvhvIZdpMmKq19EQfnawwxn05qsH4qJn6RvRMtXErJZ2Uiw7DCv6IPcwvCORdEILWzWMDeSC8VczTQAZ3hnLR2fb3MzjbQpOZznQLzPT0rzA4T34ENRO98m2+LPILxBqUEqlcbHrR0cItoWthKKsq5qlrIg3jx0EFJOFhKEgVplP3wloRSoiip5p13l6kR6stjvPc+No7qIwqrjaJqxlxqrg6VVhqDVPjBOpbiTz/NRJj2i2/cIxG8EArEBU1Khnxn0qWuYqKvM/IYRlG3cQ/Ii5KZ9aKMzSpZo60AkFKZtsnSrD+joxwDihjrvDtCGdyfLXpJ4G5mwKr/tMqJcBHE+4z6fijXuo4ZCFD/gqj5ADdMYOHI/Ag7137ED02IxyxwddsoedrFphAKtQ1UjQQO0VEKWDs7eSy+xWgQF6bsp4Czq9PJvM1KwSaBl5DNDTill5LCUKSSLOUe1OVe23KvTNJipbwsElX4vYUS5/Zm2CoHLcP2RXl2Eq6rfqZdEZqhh5ifbh5DbEdEK8on9B1Cwb/Mm9evwGE9I/+gzohKINK1qUzy4oULj2ZvKwpfULQyiEqaT9eHKKSJYNiSVAsGZAR5KBCgHlxlvrqvRVIRXADN10IIrFc8/fwJJndQ4nlrWFimWg/dRG5pIpRMxBNT4XjMFt38iKSmUr9hf7PkMxd/w8hmRP/95BMtb8qcPu7O0w2UYfpS1utfpfs+VwQaWcX0s4/3hnGV0HXykKrOZIIvmAOz4ezxHh7KBns8kZRyXiNiC4AItqv2gBER1s1IjoNiKjuI4z+dTh6ktCapBHRyHixK1jZWOJ4MzxIYj/4Tkra+Wk0JU0DGqoRU0pJkXhuMYlZ4hZG3JIaoqNhqCgPiPSlqgc=
*/