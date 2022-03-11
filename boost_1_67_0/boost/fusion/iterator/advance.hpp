/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ADVANCE_09172005_1146)
#define FUSION_ADVANCE_09172005_1146

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/detail/advance.hpp>
#include <boost/fusion/support/category_of.hpp>

#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    struct random_access_traversal_tag;

    // Special tags:
    struct iterator_facade_tag; // iterator facade tag
    struct boost_array_iterator_tag; // boost::array iterator tag
    struct mpl_iterator_tag; // mpl sequence iterator tag
    struct std_pair_iterator_tag; // std::pair iterator tag

    namespace extension
    {
        template <typename Tag>
        struct advance_impl
        {
            // default implementation
            template <typename Iterator, typename N>
            struct apply :
                mpl::if_c<
                    (N::value > 0)
                  , advance_detail::forward<Iterator, N::value>
                  , advance_detail::backward<Iterator, N::value>
                >::type
            {
                BOOST_MPL_ASSERT_NOT((traits::is_random_access<Iterator>));
            };
        };

        template <>
        struct advance_impl<iterator_facade_tag>
        {
            template <typename Iterator, typename N>
            struct apply : Iterator::template advance<Iterator, N> {};
        };

        template <>
        struct advance_impl<boost_array_iterator_tag>;

        template <>
        struct advance_impl<mpl_iterator_tag>;

        template <>
        struct advance_impl<std_pair_iterator_tag>;
    }

    namespace result_of
    {
        template <typename Iterator, int N>
        struct advance_c
            : extension::advance_impl<typename detail::tag_of<Iterator>::type>::template apply<Iterator, mpl::int_<N> >
        {};

        template <typename Iterator, typename N>
        struct advance
            : extension::advance_impl<typename detail::tag_of<Iterator>::type>::template apply<Iterator, N>
        {};
    }

    template <int N, typename Iterator>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::advance_c<Iterator, N>::type const
    advance_c(Iterator const& i)
    {
        return result_of::advance_c<Iterator, N>::call(i);
    }

    template<typename N, typename Iterator>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::advance<Iterator, N>::type const
    advance(Iterator const& i)
    {
        return result_of::advance<Iterator, N>::call(i);
    }

}} // namespace boost::fusion

#endif

/* advance.hpp
49FQD44aWSKLrPnKqS5X4Kleni/Gc5/nwxnPc533IwbUqUvOM2qWcFkpXw+OUuRpCtAq12bJhDBMBFIRPgrmqhA2eiLS/CGLpSfj0SJKbMvjJpqj5jS7KMaj9Hz24fz9gpUllbQUSzTvmnZpt9hTq/qWOuNct1D2tTH2aNTItjNKKxPMUr2aKfiUli9BtmSG3XBf/Txn7Jb26nMn/66D86kZ4v0cpuJ0JkX6Qu9xglNuS3d6FqEDTYSHRPdJzfusQpPpREASEjNJXVR93tIxxBI360yU7R4uirPZrzYWx/VRyv3dLZ/1tWizJUsHVatwf/T5vsoy1OMiTV9O5zAzxjxJlteHrQGlg7/m7MOOCgGPYYU75UpOw9LKsfK9EotJmHk/t9e76Ix3hi88xulQ5y7t8aHBkPjp8AElLabFUgy56hNTlieXIZOCt8Jfg89x6TZ8BwfF6gtCZuSxw2Ej57wGbTsYCtW2CR3HQVeGy4gJwf6lsdm7qRljjYYWjE0a1mxHroLbmkG6Nnku8zhv5QHeqrCmPp4v6gy5cM5oKR7RfrH1rSBYWWY2IXpfijImXRyZUfxiWg73Ke+j/t9TfEomo5/VzinoN0CnQCxSgVcPSKepzV6BF/mCOZMvFUsFCU2A8UKsGR45StiKSx+N5TGj5NXtMY8DuwJxlJSJMDSkxKlDo1Afy2E8HZW3Lo1Bx7wKP1pWlmlj+xn1i1dGgMFO6V6EfgXajBThCRAaxcjrrjTzHZPEFtcFvEiYG/FtNEy9g2BOQtu4jUV2+7YqRY5Eeyx6NBCnts+KKGskKT+/NcnjES2ZwYPNloUuW+Y6DrnzydQEZXp92fJdjlPbNr18IgK9EbHtoVidFL5DQwzkF+qgUM20gXHniEORjMwP0iMDBLbgIxRYBdg1DdWGAdY2bayqABIs7dMcx9hP3YuK/q8Y5NvoBivOJYJPz9YitZW0afbVSY1Sem4rWmrJmNCj8kRUUWaewuCacVAddSHSUquKOXZf6OY08qFaBLpRrOoHia+Y4HltuUNlcCVxsAvuk9+WXuelVmZZ1RCUkVdTWOiuB2Y14D4Ux8fqsbg9FROMxAPBaBr3d9r2yp3vruclxAgLbTrNA2QmR2QPh2erAGVeYus72zGZICKfKJpKOC7zLOYJMPbYPPu+WrcA/N6uCZ/K8BQ5Z28/2VJuvhLPvol30NjnOnJ16guI/W9Fvb+amhAlt1ixRjxasWYMmvSV4ZFqU/b9fVERKqaBITSuOUPpf4OFZXK7/NBHSnX4jmaGsREANwfnQIXbZ+Bep4hwT7FimVda+iDqYw2lGgewYUzzags7zojl7jdcTFqaDngNO0cksIwRCvjDDAqmefotw0QYVgZQIPQIG009XP/JzqwayzO0vHKgfbW8Ilifj0BixjPB0dHzSKQl+CzwuoMgGsxKwAVXSSeqUps57P08YlGlp9fCFGtAX+ta5SDLiGdv1X4Qjye+Zp7T+ObExH1oYUrgz2/KNIZaMtzSxIMlwg0Rqtl0enh44tD1GqthTkib8J9UYrG7zbGvYe8UqaMM26cF69CcV663X5jX0COChPU6bKxJnWxoLSUWwJSZ+/WJrQi68M2+tuOflYdvngOUpVEfc6LxfMHLwBtEwwjGqDnjCMVkImvJ0icakpqYea1EIJ2pzhHoW9pLqsqf30YQEb5oZPMt72YbyDWebGjMkDXQJ82Tf+ckhJTDmUv50/u5UxgCGIS+Qy+nuIEUOLgSJt5nI0aqrUwl7Ht9U4LRKTX/ruWFs/C2w14Jx8cfvPLvGRt4EFAUPjnf6ByKMgQfYNKhxRs89dxjJgJSFp6/OAYwm/VjNBFgVwama/eI1VPQYmWscDIAxqOAVBQo9dXrVlCYeeT1HGRiYaQ34BSgOoEYKXWacXBsfMxPoZRkyWok7lsjpBz1/UC/oMYfGr5QRw5i+m3tCLaVIb598XptiPlWchL/sCwZLcdKHDSo6NEmqKNPVX0jJTa6Nwv9M5J27dtZvgqgnQxWkfcKEEIDbkjM8CT6JqhcnNNUrUoy1EuSmOW66cuX7fAHLOiH3qFPJnQXyzjX5P2KFpVz8xM7+uBruLcCwVICl+6yMLs8pHPQE/Qte1NWJOtcylCpuFiPSMW+iO5SyvQ7dyg8h/VnyMrFZdjs/XUovO76BUBLwsNXmnIxAks4ihEHE75BVG+qpBCfgyJgH9fCGB4DJ7ZTAPjWFPvucBX09bc3YfwNFRpJjIcrEhPdY5DuGbCV8+FHdu66m7c4d776GAtfULV6ixiQQtaWDgKIfiPL6npHvXiYXEVv7HY54ADCEiJjmT8tR9Qv84p4l3DdPwn2YWZisWF+oKo4s4ZCtHBvtolDSe6D01QjUc+8uQp/kOZey4m2OuW/OSlhypLOkHSX+dcvnFHheNSr/87VWSQSKbPjrBQ53/2xPKCIe8qlJq4oIm7lgQF7QxExSCzi7VlyHlFtTx9BBBxZyj7FPeLlEnsci5BD7o86oUwgSqtYLYy3Ox6aMDIM7xWxIMx1fst/pXDxFIHqCRDb0TvtKR7LVn0H8v4q9HFtt2k7hKCfILwFRTP5aA2kzslOdC9xFwc53vkT8B+N+6OpxxCy2iAY+b8e+2DYWkod2TWzBQ/6YN9mCXILLxNsyrF/aWlm6ZY2fCbwF/N+B1DbM94aaq7TMBaNK0gK9IzP9fQkeGlYAwYe8cdWsnmSGgX/tQfA7plMkCSSeUGnWnlh24WFqfebFMKQ2aL6pZeDjuCbMbynq1EpjtM8Ik06jAw0XzE96JWH5JgiS6bfniUylAwHUxpkF8SyBcrgQpk0b4qIHUJijozlzfUzmB4/unL7E9t35cwJPGJof4Y94hjLcB/vJAhxq5Kz64p2vs7gTC30Pc2TpEpVaVa923NO+VveFvRUN7t+uTmCbW6XxhNkHMRuIJKNrrY1HmG4UBgfhDnY1625lIBYF+Y/Eu8udoV3u7Kzm9aPnU/hFJoT/GcZHak2pS7my6B1/kPnJ5/R/WgRfOtiwrB9zSdtrlF32/xRZHD23/UKWIMfP0AKw4AB84kY39kxdlBBZA/I6EKvvHfgKR18aG5fwE7Ptg8WplBKTCl2U83B0PQBXjkh9/ZMlGDNXYBALPM9Eh6R4zRuwFIHpFTNBp2gZ+iM0yY8iFJ+afbxK5M6NeLCTu55HWtxukUss2Wu5JPNg8ASUrhhlh0dEm1IBo5uqJcH9FjnhPhpZn6ezsFySSaw3LvQrnj+QpX50npTHGLVOn0LAuoF2zd3IABtLGYyQmhUnwaQ9rtnM09WOJcexMWatavCl9MnBKlfxA5YDxDKTj+gy+TyPIx++1w2EzlQGX+4wazTsmWWaCZOCJy7smneDeuuQ0ZH5621zLSqBepBOyjSZsWn1rl7fJSjXPI27cO1G7t+5O41KNs6PkxxydQ2zzSNIHA2lL+M3x45U7y57u5lb98QvfhGjEvZcUg8fUcWvPHh0PBJpjRqKJ07czaEJtZhyiLG+fbIsgurr9kiuDQT90CsWkDmz1UUkENgChmrjqXSEBLnNeo7OVRyLWYHm6SWN+tEjWw5gVPafI+DvnY5TxEFKlSWRHRw+1wo0ZLjBoqFkig1snVNyAl44s1/QU4s17g1fOrdGiBtc/+ZiW5tH/UnT0u6t1USPCl+yuE/IRogz6WFms5vPEipfueuVQjfCZ6pPF4AjQ4rVFKyJWjvSpKOLCcI5rp2PkLnuv+ETNSSUxH3T0Yb0QCbM+t0pfvRScRw9RqjIls/dvF/TrBL5z+/44UvIy4xQvfDbsKuQ7ZHml3mbI/NjnFsuyqGsgBO0+fJr5nH0J7P7Kx4TS/W+eboewfyaxICer2cgkopOdnDVSQGynT7dTS3IbHP4BjyHviBhIwnAKBNEEsxB5Nl4+UYsrfYiawtmaNY1iRxFmrl9NZd3hBlWS72qrGubooIsT1CSdrWUMO3OuVYdOPlBPTK8DClAErdl6/+p8XkaYxIyAmKPfXW3wkMxMPJ0gGIecPZaegjwJEU+mQpWoBEkZdXpWcr4+P4tBCa7AFpmPWPKnGKaymX65lF+RCi8jBYKQ8O/r+68BuWfIZB2X+YI+QSVwebNbHXwYatPbb7DsbQxPk5B5GtTYmeMuNPWa9SBnItGik6kXseAIK+UDa/JR/JF5MPU4FtePJ9qRQ3rOPSl8PX0rNEcnPO/injef1kBwOVE6xFpHSx8HAENk7DltU5M8DwYBysuvoCpyaisS5LEJgegjl6NXqa13acFeniNZ5+w+sKyDnyHHQieYMliz15tppdldlKhDAldluy8by76yuR0JjOYSWoWVcn8i4mwZoto6r48jUbSgjkqJMsGq6l/6WoSBR84zK0AogwegrJ7Qj4Lwb34PtInAmIwRMBlzYS99PTB9s5l3lo6MmtsXf+gty31skQ6z7BS8uDTWleHNsFQlR/mZY3btM+pmO13MV3eZLlyoIkHdgJinDyQtXE24dxdftIJnCRpAzaDKAt6Ydu6Kw2vDSYZo8hWm4itDkXtV8jp9p5Scl/sKaUdLxHjKN1IIHeGjIuS2CB5Y6OIXs6kdqa6qM8FushWdl7oHp1A+tWj2EP3NuRjnzf65GZz4q+DBfsjJ8WGUoBHUvkxKTxjSAsNv6cAJ+b3TNpw5aLsBaHJ8+EKUS+n195Whdb+pGYSlNB+/UoESkryenG6NjsiAgk67wbUJx5tV89mMluNM4kY9s+3TyGXxaOjZGqV3IYiMIxaD5VR9rlHgtRi0gM8jIZxoG49jgGSO6yHN2/3Qe52CDRiydD0CyPcFByIjW996JGTgjhQ5K4CeT2VayokF+MSLKK3gdsfOO0Wkoh+rndzUFp9ZRS7hESQxdpG0oYRnmsF6WfSSIQMfeMbOOnI4L9wpP0MYEi/69HJOf/e0RIMv4DBGMyIFmQYbAatigXA5bgClDECBcyGeyX8QApN5JVbqE4FUBBkiAHzu3CLO7t0RomUtWu0qg2aGAMTxMxBkyAQrFaWKzj5l0TExWAzbXnfckQF/Dui9uNm/C8el33vm75p3fZd0f2eWqre1tPT+Og5TIvV7rl8qXHVEJRZ1NXF/yvzrZI94VNZtB1U3DHXlyeCe+Q1n6TfMWtZqpALT6hxYbGkw+vX9B1aObzHo23v9tB20ROlT6yE61ANH+yi3HhgMdDcwO18UwBPEvf6mRzorsyMi+rTwkUbk5vlUzOdXs6k8seEs+edXA2Qsq0AewaSupf/gqQi5X3y9wuir6rrnGO4fo/ayMcFMyIiIShJg5DN256Wk2n/26Xg9v7yyxms/tX5r/gvy7U/pPRi6dcjDygJoEMIiuJ5vx9ovql8J6ZF2pclePRVrRqlSbQNsGOiTlbtofdrNR858s4WNp24AleC8TXcbdcGnoBFGdUhofpaVd0K6va9jRR9Ntag0t9Ab9oTFeFwE/OYQB3rhgBrKVQdmzicBQRK+cDl+WK2q+tz0QBynmDzlrAYDskp2zlIyfsK3xE/YFfH9oaBfO2SlVtyzsfF6dmn53f3rCOsHBt5mm27GaZPSxxpNWKaG+BNILNJMjh0bDVi5bn2egH4MO36Imcm7Hp/JSpLlYBBzqiDBYW4iPSGb2kuh7T6cc2M6/b5qEWPDIePgzxrtmHXjqw9tD2gd2VgZ2JLUwOdSRFaLpArKZwy1He2vtH1zlNjFcw8kFFp+JYTyLvo/oQc1snm5s4x8THKiWrnlm2tZIsVwAh2qLNIVWZM+p6k8gec5mte+7WwAIA0ee5YKoAiLkzD4QIrUtacjBHCu6bxw5L50letGj6IuscIaWulEFH4RzvmAMdKXMpdI4gvUwnPIVIxcY2Aav5T4Ga16ijyQR2Ifm79zXzgdkt65TseYLWzkEP7Nr2alvPHKx51XY2vzAqKdLNcAGO7kNLb1nl4V3BSU5pgm6BvcTAzgUL7VIqZswDzZxvG5WOG+S/G7/inYlYR8egnGpDcXAuM/sVL5+3Xw/cLwJGfGEe/LrTueypxwalt66pb88YVFI/FmQG3+MWPdv6O/wwzH8qSgfu2JqjOmWcMm9xKZ/OWHPU96fp4b9AzLUTugev6bcGodsn+oQpjCi+T8NyD4vUPtCqn56xt63M8qUO67RzB6dxBNojMBTVlTSLN1foiBOl7MBvfI2B7dx8w5zMgwG+CLpuhTru1rkPCdv2/sv5XZPiRB+gd9OYLx0EoQqiMwDxAHER8VacpBoGR+2Lk4Ju35VrbF+jApVb4fy6bkTD1UShCa6xNA7DlKOOezadP6EPoo0kzz2E5wIpCScpoQhFrvst2c8zQv8hrdH+ArwSsLlM1hBD7RF1MJyFYXge+TDdHY3hUxBVvYqTs4zjdiLCAgcAndXGsz6g7pHdQ4SJB2BIYcnhBVydSRw8YwD9lwyUkA3Tuqc1fCI2wdLzUa5+Tc8RpoV7adjulmvbjsfP6UatEi32XIXvzpHIJPgB6PZRq0/dRzW92DI78HO6oH8Xmq+v14vZYfVdqPFfeT8l685yacy9WM9PWxOrVX74nhZ9xB4T+zaR0CctarKFDvE7lk7GYudvdsKpkAnwjUzsS7h0BAykf4h1K3o2bMyaBdk+BJoC88OUueftLMfQBz2m6sU5VrmuiidHo1qG6+KtE8hBPs1/1Cs3/FIXX3wOCbMGYCEPt3XoAQwcH6W0sA9tDpzKLnM2+ueqjQ2aJGDTYU7H2BEqVfplxmk3DIQAvQ+gmV0hlzUEXGJm9hVcG9EXuPKstnj081TDOXK30m6zprY4RRFHVg3McBhOhpuY5N7NX4YCQYQlf18aOZYD5dSIZLhV6dp5vQw2kBDnZG47aWPPOCOo+STMJxANJHkdTn64uezRxYG5n4CtDzMd3t9L24u9sSojBJ53s6+tUz8vcbAmSTa/QPb5TFaa2w00flSqvetv2izBAk2V4I+ZbRLC0gezvkLz8s20x4bGepxQ0RwqbpDB99WNxgfXqcV1XidQq0R7cVBxG9hcaIQvjHWq4UtptXSTiI4QD2eNCkYJWrH//Ly4hPrWsehMKSNS5xNMRTnhbDkQonRLQOEeD46Ae9OI5MI4KRRTMijd2xIC1rXV4azB49Q/6w8mFqBpqKf44kuLflYURAYrmWcy9dN4xqISY2O/ObtXI+hhfxFdhMJRKmPrVL2FOP0sLvK/j5RU2Jdj0iH1X3pWzy7fTR/GgCPujwK/hMnh150O7TcYLG4MWXzUocFT0d+zkzhpxD966GhHAK9y2bw/MH6KHsTrKjBdau/wS3TTlEErjopS/ZI3nXO28bILf904Epv1Jsd4G/TJVU9CjQJacd/nU5sQ+kCPJgPWQu5hzH5XLaOuqfaaJDuSwb1U1iF3w7zcKFCE6I0g8155YDAUSX27DghMYcLFoJ2uL9sJAm+DBpTGYOWVdBgx6/GuyOB736LGDug1/gI1Vqa/amLkP955Hmtb7VBiO2zv7Mn+uHTIioBTxbLysQmSTdqP/tEIEtA8xNdl8ZZNLe302sRy7+UpklUUNVbcO99y2JanIR78yCsdwpQZS/gm2zDXlnTHShMxdlRQpAEWxkOPiWjjJZpoCg+ZCSAFE38lgsabiEUta+e7xu1XQzcX7A3CD9PVExR+Er4fuqZBnmOfa5DX0llBLRWKY+spbckyRqTU4V4eKVdPohUoM4uH4doHsbhUSPppFhErqImLM8spG1H3+h2eQvYI8WEO6R6yZo50k2Bx8T0WnKiz+s91/nkSbS8MsgwBZ5+Oa1USyesqoFYsG0XCK7p0N8rSntIdxTxdfQouR1AWXbW9cJd5RQOssS0+KjdmoUfioffmYpjQio4eJM2SmbeoaSUb5s7ykdbOg1eJQyPtFciz0benr6cWlSy4Fzly/6f47K0kM+v1348uoOjswciXupbHlbKuuFUR/112rbzG1lonJFqeBGU53qbufzW4h0lcJhxaPzUA9hRBHRhRk5SboxKc8mYX3xIEoK1LcX6xeMums2LU1x5B5OOvzHb1PXkglnzRw+FM7f6oEx9oT/Gzdu+MEB/VsaG6qPJaHBNa5Dd41mv/6U0Jxi3YWNi4RcEvXd7kczJphOXCqqgzWMT4gLnZGVE5jq1IwKsSog+uGdFiZDBLULFph3CCx9nV5h8WRro4xQeWAwAE/Qn+89+fkD+hf8L+hP+J+BP5J+pP9J+YP7F/4v7E/0n4k/gn6U/yn5Q/qX/S/qT/yfiT+SfrT/afnD+5f/L+5P8p+FP4p+hP8Z+SP6V/yv6U/6n4U/mn6k/1n5o/tX/q/tT/afjT+KfpT/Oflj+tf9r+tP/p+NP5p+tP95+eP71/+v70/xn4M/hn6M/wn5E/o3/G/oz/mfgz+Wfqz/SfmT+zf+b+zP9Z+LP4Z+nP8p+VP//+rP5Z+7P+Z+PP5p+tP9t/dv7s/tn7s//n4M/hn6M/x39O/pz+Oftz/ufiz+Wfqz/Xf27+3P65+3P/5+HP45+nP89/Xv68/nn78/7n48/nn68/339+/vz+AawAACCY6+o/BoXbAh4NOTLXL+E0I+LaL2o/qlY3/aLYoxCV3QyzE8e/nTxQHvYrR9glBQ6+ViaztXrnor/RzygcjOhVpfM4EU5x1fLlCsRLzH1dnug70Sb/rTQlJuXsmlRvdheFlEWszIidQOE1THClzewOE9Zgp4FdbIAGATuy3w2AdijL1TSTZdLvL6qrW8hFfyPTMNFwS4N8fc5oPGGCejvYLDAfUTv4bzj0AByyPFbYO6fa7yfuBeO/FAAWAFZnxzDzOteby3IWDCgXQhL8d6WY62CR2bNiIIr+eAGfuJu6zjFsbw6/B0E5zBP0+Qjg3j6g76EfPsVoO3LdOkPusSpneOwxMkw13LkPVMAz3+JHmV0XlUfPjHVAvqF/5A+BEelyDuai4+upVwNFRLveMcDMrdTjrHzhWXoqkeKVxRbryP76Vn1ta/HEYTI7kWWagaDlCzRhjc1Re56WEyjj0NPHCCqz0aFdi1b5HmtySlMIb4Sspd0LVfCj8D+HxxjrRmndoD+ZwgvGkJHwYcEPX4YS3yu2Ei/4pVZxc3oJgY2GRsLQ85jhTGRSPGxqk8W8cOS4eF3W6pTcvNjOEHGABT1FDc9F9c8ppBgtVBXPhs/P78I7s7ssMmFqcv9gyaMRmfw=
*/