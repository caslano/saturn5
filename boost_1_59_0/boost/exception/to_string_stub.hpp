//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_E788439ED9F011DCB181F25B55D89593
#define BOOST_EXCEPTION_E788439ED9F011DCB181F25B55D89593

#include <boost/exception/to_string.hpp>
#include <boost/exception/detail/object_hex_dump.hpp>
#include <boost/assert.hpp>

#ifndef BOOST_EXCEPTION_ENABLE_WARNINGS
#if __GNUC__*100+__GNUC_MINOR__>301
#pragma GCC system_header
#endif
#ifdef __clang__
#pragma clang system_header
#endif
#ifdef _MSC_VER
#pragma warning(push,1)
#endif
#endif

namespace
boost
    {
    namespace
    exception_detail
        {
        template <bool ToStringAvailable>
        struct
        to_string_dispatcher
            {
            template <class T,class Stub>
            static
            std::string
            convert( T const & x, Stub )
                {
                return to_string(x);
                }
            };

        template <>
        struct
        to_string_dispatcher<false>
            {
            template <class T,class Stub>
            static
            std::string
            convert( T const & x, Stub s )
                {
                return s(x);
                }

            template <class T>
            static
            std::string
            convert( T const & x, std::string s )
                {
                return s;
                }

            template <class T>
            static
            std::string
            convert( T const & x, char const * s )
                {
                BOOST_ASSERT(s!=0);
                return s;
                }
            };

        namespace
        to_string_dispatch
            {
            template <class T,class Stub>
            inline
            std::string
            dispatch( T const & x, Stub s )
                {
                return to_string_dispatcher<has_to_string<T>::value>::convert(x,s);
                }
            }

        template <class T>
        inline
        std::string
        string_stub_dump( T const & x )
            {
            return "[ " + exception_detail::object_hex_dump(x) + " ]";
            }
        }

    template <class T>
    inline
    std::string
    to_string_stub( T const & x )
        {
        return exception_detail::to_string_dispatch::dispatch(x,&exception_detail::string_stub_dump<T>);
        }

    template <class T,class Stub>
    inline
    std::string
    to_string_stub( T const & x, Stub s )
        {
        return exception_detail::to_string_dispatch::dispatch(x,s);
        }

    template <class T,class U,class Stub>
    inline
    std::string
    to_string_stub( std::pair<T,U> const & x, Stub s )
        {
        return std::string("(") + to_string_stub(x.first,s) + ',' + to_string_stub(x.second,s) + ')';
        }
    }

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif

/* to_string_stub.hpp
OwOjMLJnfIqnqPSoZ6Sq9eHAskNWqJpG2j9XZqMPvv36AGTHGxMAvIclk8iY4WJrA+rsTyhdYXwKNY2ouMehbYqOniYBa2TKEO8BVxd9DkqcB9fL7ruFdo1rPQzPB1g7QeeXoqlZrLVz+0MLY/DrBpaNwvR7s8NolpScebpYNnyZXNoDrwM06QksxahtRnBxj+AK8zQydqO8qfYWwY2w4DbedMH6goNm3uJ4hX9y3B789YZ7aChSq9hHkIkFanmfn8NiDcoZg3QEoYRBXhCRjInDAf8GRkKKE+KhHi84UzI80/1nh08I9qv71dz9acHQmFDJubaSdtS53+89nJPo9uPXEhstcWOmYQ2cEuHlLiWaeQslCO1vfXDq7LXlQ6Nowd3EqLyxH8m+VXjAlxaYxpulyqwHP7DdgTobQhufNi1O59laiu3yB9sEowaTQaGwD2wuqFgkPNTvZmNf+q9gpduIwSdizphOgBSlsNnTKOGHovOJb9lKzDJcQFEiEXncO9s+xwND7K0pCCGiVaThy+acKcGSnDBb3QBR7p0clkVsFDL1UzcsnR/NuKycbLmbkboNf7TLB4b0k3cZgBxLIRmyW5kIMUj8LRVPePSnttSiYjah+MI/frySkhKg2+AV5hy03YtJ797vreASd/oJu4xhdNFB/ATRv1Lm9jWN8LHO6HljjMtsSFFrVngRc5FZOy9g6ktEZodGYuL7gGKUtEhJxvP4L6WlI8C1TY8eapFq6DU4Bw/DsJUtzxc76PiQO8iYC/qAF43K/lsZIZGU5pHHmPuHk2siP+j+m/XlNAkHOH8mBehh8tTkhVpeHbe91nRXhpnF6wpuqJ6yToI4c00GMX6vfFBmRaDHzekb9iIbtcpCQm7RjVzL3Y4p48Y1oyRgj+YKr+XKCZvd2wBKXyySZykAB60wrgi0TMP7dl/UCaLghdWGjYP6DdNo2dNlR5VpkQf4385kvVc6qgnKN+IoS3AInbWP8tAgMp21H7Cc1xo1my4ZorxwF6l8zl1pFmwctWEhmihZ4UarL/w3eNqoPHuDVQu8ciT51zXPUFlnYYY0x7QRe2tiJr1ZO1+T4Qx66PGp3FKx4ihMnO2/EImGYESSXcum/BIdUDbbf6hSRl5Y/Gmi1glulrbRAC9HafaREHewPO5AGp+b1y5O3s7EE/WYcrY4YzNK2xgOYYia1JZ7VbQcn7NIzkVG+Gh3o8tNJuuZtlAQrvZ1Axxf952VYytrAW3z2O5Cchu4Ur+l+Vjd3zprGkqabASFNMBNRdgaPCb01cU5vPJow1bJKTw+0xH7P8FN4Pkxr+RXdZitE101rQAILPfTm4w8ZOHb7I1F26TCXSmpZTVtEdjrSa3PID+tC0x2UTWU3niIrnh2JpygEyGdwx16aoZWY7osdFYT+6E9OtvVBwsS9l+rSt9+k2BAZ7Eo4WPXkJnmaumo8HjfYrwe1pe7bmr4KbfJzfV32a25GcTN8ZsXzK+0DKH/8gndlMuYhMUwVeQsnSGTUT0qcpz4CTNNRI7bHXzQty2FUdLKggRIRClcVoqUkUAD12MV7Xt5tb8sOH0jAXumKhGQ0u8FPquvknFkODXnR2nvlRmQCZHKgoZ4scAczX9kPf5TprddulSY/uL7TXytp2IiR7gkIU7RSK5pDgNam7zFTzXf6u8IWN6RdLGw73gGaoYPfm7Kysz8D2LNmElc0+k8FBMcPIQvV/PS3ZGS2mDayV2y4UpI968pjgmsv883oC6HdtPIO38eQZ4hUiL4Hfc37zMMYs60luVPlSkKSiebmWtxqbccUy1a5Y7ulK+W3kvX6e2yA6jqUap2dUZ/wn2U07Ry3tEqpSaLlqkti7VKY3dJqwBd06KT+3EZi6G2kGhHdw8TnMk1qZ/0oFu8dtWNs+3kgelm31bTXqUtVXWPbn64VMA/KAoZu8NMiHdM0PSqXxZgDBREwG3EmNxmahwgvypjMM0C6+aCcdWOgMfSk6c7VzgoraLMNVg1vw9kWDNWtlgVIMcbWoGtzuQ5pFCQfEjH82my1k43tDEcKRrCsA/7ZIici7gYZ5bJjPrmVOBZv5KkRse5w5yQjKXpza0ZRdmxChSkDx4ncfHSei8lGMWzRGsjx21ymwIadXGw8vp87FJ8vSoDV8Ncgaso0VB5DidDq4hmamSq5ZzRvgxEoUjjyWE8p9ZKGSaLVoyhlTUVno/0pV4XQNSV7TAJqrJ5Di5Shwi7JjDaXtg9kNIC8UYHDmziqlkvryygnDa3CXdFru1k6y/jmqk/QCVVFh4cqKsnSa6fBabJpHC0eTQFnzJhe+IjkaDbVfXkvbObp8iIsa2bTWrr0+rfAJszUEwtrjYFnNzjVlDlXyACaDw8mFtmLADED+pJckDg9E7GHjOtN5Ky14xMQydNaWrnpmFc2v055CbkH2CHod6Hh/v6frnpVDBESeRNSWmp3ZJSWBFwUYAVuG69O633FjufT989WkdAu8INYb6P1Fof/EB4KfuibFCVUAEvpZqvX4Urt0GlZiHegzY2gq1rtoR37G84KRCvRXmVrkYQbrlen7Wausw9KagXC9WT4z2ZQA91It/eFx6TFep6kwNR+G9T4upli9Ixy4gg7l41M5IWziTS+jWIuMAETkJX9yKQeBZRbJwxeGPfw9I5axoxo3d7v6y0qOzCpTNzo8aamNstibezpBB2GKwmQihM0giTbX9zvIFeSfXmjMDFaWIT54wQTadvwCaeYBHj9hAdwuOgwhjL7RyNCYYyKckHA+yhfFyI68TBVCEny1IJ2OqHzyM3wOIbJ8HGSnKpBByfBe5dWQ655LELCZsvzBv4m18KE5tOTTuuNaSGSxIPz2CWG2JmiJZo814wUKxPB+E/HtBHMl9za0YV6mssQ0RwlWBXJ3BmtOxc+IFNCi1vvgy9Gb5eaREDGr69cI3bYrm7gFI4v3aQeNrzoJh64/Bp9Ixb616YAcL/ckI0ALdQl4exFpIOP3ldjXy7SUBbv9IqBsqMsPuQbjR0D8+wVCBEf/lRbo4COMu9fzjXiCAfdv8rMdBA25zkVAmLMVBFNkBkG7ixh+oB6fK0jyuZULX02ctnBFSnMa+DXCFfc+8a3KYPYTu+Mag4U2ClRRssEg4ZOYRS14BTf+xh7jWWVZ5EgwOOxe4Sqnq/9nZNgIg7b82KD5EPNT6fVALHsQEruRdWNVUt2eOCfchw0+0toRrG9b5I1OzO2/g971rwySyAin16NtZ3PWpsabizAWs9lKgY4azVXmtGOvVjgSPz6g8Ji2CrU4YwdkwAFvB4S5dCCU241LWvY/MgqDhGcb18EwRCAQHEmcIJF5Qin2sI5138iatZzXUSEbrMujWLOgqTJ77wjzkmHIlATS5mRrTWPk96JSMV1fI+96FaBRVfy2uxLW4ZZORl7bX0bjY9WTEViOVUvbxubCs4Lu6iG6cOfs8Ip7Y0mjb1xI+FiFWgnLT3CDyI1dVVO9sZ/SFry/hmgeqe9rH9d61mN7zxn9V4YOF0B+jG2M4eqTZOxiYWJrnzISkrFaRpbvItc2U8A1ZNFhNB+zIZYFeVEMvgfsEnA2PEEdpZQi58MjmKNINqRCD5cLbVlGJwV/qTQ1LrrknRpyxdG+JYzIw0eDPCVbSzWrZAo4HPFoqO694GjKsWUc0DW69blhTbt29RCHteQytggBx00NeUUkCNhhNIq6Oae/IMiW5BoQB6gVzhgy2+QDt5EXHrJVr3tsokh01ndN5jNvMhrys5FCcgl5GFMN4ttE0LkQXtfotXRNeaS1ex/VbDmlmViuySQe+0Ey6f/wMekDXx4+mRYeiYQe2Usba8SKaAgcf16p1t3evam1sg0wiE9mbSpgcTqeMud/CaECQI6BjBrVglZA/aW/otJpWb0OtT7XM2EUmzY+4bLYP9WjC7rbIDtNi4xYWPoBvtnpiaylNxbOn99p1ToDSYhznRAyLHIO/gghpbw5W6tjZb/u2WsBnwyjZiaNIW8eVqJJCr4XEh6Bv2lI2qousw4MWUwNprL7uOurjesext4qumkkRt4q6Z/73yhdp+jLObqnL/KQobOsD4MnmwWjCU9aDVxtCmFYwoPMKmzD/UO7nvIaL1Qawslc4VQgjHYfG3Y8it+4ZSwH90/pR4rJr0J0vBa6bRcc8Tva8/PwdGzn4HvveU2xZcHCWOOgkxeP/mbWNCWi+bZPr5ixGkJzBxxQYQfwFPb4qU2bgMXzupxtqxAlLDOKXCMZta2Tz99eVA1KdIRWTkVdlDgyYbXLAR1uZ5VLUoHME4W2rspPic59Tq9JWscxUyZsQRhJuE+jEP2k8wxCykCxeMG7RLp4rYFnoN1JOjFuhf0mET4nRpX8cm3mfWRR8u5fm/j+sO1YuyRoY04aB1Vvxbq6q9Gl2+H5r5ePD7ssnRl6pGZurwd2ZtT9NW+fs83N1ep74P2Yuq9JM23794Ojg/0xbO/LIngk9eqoMry2di7fx6un+eX6xcPRxcXqBep67Pqynm3GOtTde/PterXB/55/QOT7tcmT+eL4aGRlTdr/6ZzgW3m1vgzvRpj1fx531fb97r//7Y1blbspv7eT7TKrmPDOsxtvR93R1W3QJGA38+9m0o1w0p+32+tOj+PFVa/l66ZHyvurm86Pt95p5/Xa7n6WnXH4/ZEhB2jU0RFMS3jVyHPTat0k887Oq16IddvRR96qM3tfHLo0+st0lMOb4s6YsXXbrhz5Waw6vRCZmb7+bu6+fkhfj5qVVHYVwSjTYKfVGt2ES7YBu7/CJc2kQ/s41OfrCHWpwybnjg11j0xr7QiXmhF61rfVxa9A3/b7DtwxeRuj7eXE1KqZxdyWQwvbAOTx7W2PX1Prf9Tv/WstReqe5yRlo+cf7tJtla/p5FA97nLs593tY/yfvxL2HzjbJ74/QWeNyHxun3AbbJ36u5Cz4egEr9nmpA8b9GrA3OG+ce0JIi2REkpE+Ap7YrhHfw+ujuOXV9bih+JT+cmxrOgNvcWGrs/VS+Mia8DonopY59GhLN8C9vTC++7Sj+s/Upmj6sUcDRzEtgaQO92ZXX590eu2v8Pm0TBop2NC757SlC6LDsm5yYISC/P5nKfpJ/ZfxQ/37E8OHWGGbSfDIeWjVtxDgq/jlkOs+7Me6ensAfO3N6wHB6WDstfqcijxvKZvFLTxob8Mrk//+zxOFskiGqt0N4+Q8ons+/CUx1fsyCz2/96/s3adCPSGh8wQUHtvYTx7DztwhHd+zpA4Pe6WmM8Ye5+5rJ9XIK4z7r5NL2m+zkXDYadPSpSunjlPGBZ2fqd32pY+eZ8ORMWAaSi8cnFu101Zz/e1jaMxUdxMMhNTQ+SUiOsLgei5TKkRhFDXgFMWgkkiMYnfUs3GnsfW/d++4fn/vK4EHTcNBd+izBt3f8j5XTClRLByKjDKddlKFGWb0twgoCS1C8eeApQiPfJvQVu7l1YBnACpiqkrmogGvTXb0c6WaOkcTN+hzvUdLMOYimw8uEcG7uU2IZn4g87zHeIgwfnZk+YRWC0bo+pQkq/xm7z4+dLgRnaP6kVOcj0u1sJYKryjxjcDdEJdDF00UthButHj5beFm+IQ38PQfYU4kqnh2qx6lNA7ThOwF6Dt7ZyiXz2WJYcJi8xwFGrvFSk1lIT15dFnZWzRgnXKR03afjyv+KRx+EbXRXEZFRaQYayhynCF+vz/N56WxTsgO7JzO5TqwuoHdo7vXtHdrXt38u7u0dkt9vJM5hGVn7Pyx+nvW46Ibc5qqEhhGxbjTD6QbE3Yg3vYbfwin4zq/yKfnOL9U0ZxZc2fvdH/v+6BTVzJX1AdK0Uvt/LPsuwogSwM3gcP0ua08z42qCVeY/k8dBBS7cmRsbFCV2EkRcOI3c2qta8g28Z2zzOEOd40SQKvVSABMMWHiSaIOdhFfy1tI3ggwYPWSG0tPwTgIbgNog0bA8gYJHbMUrrSkybrJp0r4Xiakoi8cPbr1u572hCL6LsOsxbQB4M4eV0CxL9vpYVjB38Zn87wP0IUysuPHxERcVE2Oajqy3wM2qC0mV0ccPR5gcDbY7ifFRs87nhR7qaqn4wBXgMf7DYZPcReBEWJVsQEwGa7MIzptkRFT0JdXKH0mYlQTybmipdiXmEEdpo4/lOCcuqad4ABWLMZFMpwnxO7BXY/a8BaunVkBrjJPOI6ngguOo102a45Q4KRBFpp4tNpWdJ4cgjKkUVwPctcb/eoJtRa+1THwW1/x8+M2xaZn8CsebR7hYnyj/a/MEpjTapei2Q7D5vlEzohXsPzh4wLl9Sxaf+Ic4cJlSLsnUZwbrfREqKgqlZgHBay3A0NKVjikY09v1rsr0SUHFAoX+I4sX3ndEfKEnM+thM9iC2wFSoFtpFSaN/sCp24ir19gtdR6nP/NcuNgy9j5hSGL/K8oFDFHsCFAirhN4rsQZuP0WNJwEH8eScWSy22Up1wblywju/BnoanTaO07MAxoea0HfHulMUVlJl/uhR0ylLoyD0K5ciThAVsuUD7Pi8x8QfiB3scDBXiJG6v7ticSq0hd6sAuDSynQ+TJ9pTBe1GV8Fzq80U4o8jUMeplQUImQERA4pvLQQxmJCtfDVC2UQJ4FwdMNFy1vDZkvgv2THq6ExbBO0OSSYFOoKDsLBaSHItsMZMx6cK520DcNoL5gNw+suHRG1TMXUcH+QLgt/xl/Phl7VJi1dfW4mDAtwN8NzP+8xRtLXayuZELBa5hhjxLvbg+YaxgmYzHiByP598jDJpzw4cipnxW8t3O9T+KBWBw6fzdE64NUX427k49i4E992yf/dHThmcCz5Q0DWGAgclbPqmTjncgHwtmccDcX8ov3EYb08kE4rNlBrkpvjE+iGKZC6Pw4zLhy12sHUAjnAU9qlEpXsqv6ihGZFiWuxJCzd1KZHBm2l52ksu5mJ3UyGqCdLOZ1dl29oXCRFhQfD1cRH8KlGyJ4XOXv+va0N0LQJ6fj6B6QqbO7NYPeBA5/nvkl6i0BP1hLXF47e8ABaYSwQCEibVst7JqnBN0ISBBTEx/M1zG0/tbRb+L7avH8JZbc22jtnZ/GEFQ0RKBOosrH9uEt4X79aXqq7Iz+RYpoBXPV692wq9x0WMGrYOz0jbIqlFmFmNY5s39yPT5al9K6wJh4jDSKigPWdaRMAGX5CX9uuCUpEWjKpTtgdhbcVuM2cXuaLBZCkZZTq+ZRSgzTTzuj2wQvIsW8rYt/QMuXeOEb8JQgaZLcaCawTj5j68fptPUODmW8N8T96f+D+ulqoPIo2s8eQ95zu30HezAvKUQi57M1n51tBRwJm0syN4e7wkhPEXGJcMPr796Y3iOJd6tSrrKbwUVDxJw8jIAh231NuYbuHKiZHmJS2RlBgQbAhwyuHOoAIpWBOlYTa6MPIoNkqtFIODnMRuu6X+VPvjxB3hBFbkVAKnVaHbTUYCsiCWIhsCQhSbJ9PuAcTxCDvwUniRXtjRPKQtVns/wYuLyD9thN1oaKwl5ZbdcVkO3dDS07EWR0Ces87pfvlWuKUbqifP1iqflET6ga1p7v6tNA1S+uSC6v5IHY4YL8EeCYEQ24To6LOWCCAcR2OlS0WNUkqE3230fYiqZM
*/