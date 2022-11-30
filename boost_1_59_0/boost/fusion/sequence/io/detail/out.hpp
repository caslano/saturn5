/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 1999-2003 Jeremiah Willcock
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_OUT_05052005_0121)
#define FUSION_OUT_05052005_0121

#include <boost/fusion/support/config.hpp>
#include <ostream>
#include <boost/fusion/sequence/io/detail/manip.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Tag>
    struct delimiter_out
    {
        // print a delimiter
        template <typename OS>
        static void
        print(OS& os, char const* delim, mpl::false_ = mpl::false_())
        {
            detail::string_ios_manip<Tag, OS> manip(os);
            manip.print(delim);
        }

        template <typename OS>
        static void
        print(OS&, char const*, mpl::true_)
        {
        }
    };

    struct print_sequence_loop
    {
        template <typename OS, typename First, typename Last>
        static void
        call(OS&, First const&, Last const&, mpl::true_)
        {
        }

        template <typename OS, typename First, typename Last>
        static void
        call(OS& os, First const& first, Last const& last, mpl::false_)
        {
            result_of::equal_to<
                typename result_of::next<First>::type
              , Last
            >
            is_last;

            os << *first;
            delimiter_out<tuple_delimiter_tag>::print(os, " ", is_last);
            call(os, fusion::next(first), last, is_last);
        }

        template <typename OS, typename First, typename Last>
        static void
        call(OS& os, First const& first, Last const& last)
        {
            result_of::equal_to<First, Last> eq;
            call(os, first, last, eq);
        }
    };

    template <typename OS, typename Sequence>
    inline void
    print_sequence(OS& os, Sequence const& seq)
    {
        delimiter_out<tuple_open_tag>::print(os, "(");
        print_sequence_loop::call(os, fusion::begin(seq), fusion::end(seq));
        delimiter_out<tuple_close_tag>::print(os, ")");
    }
}}}

#endif

/* out.hpp
7tFnbv0TUl3dnI1LOu38c/J6+lYY2SECrsvR95bqzz3yBsH6mrrriQVS7QrL8j3bUl13j+24a2DV5EFjC87WDfEIY4hAb7X4xHYrt5HH9ezgYhnlNC1jn7nyshqz0P/3YnVb33K1x2015b3tAf7Rd+fcZBvfeZkZdwboJKTZKrKDuFlv2957hrdn/K2IdePEZ9qGyJaFtVvotIWtWxy8GxNrh2+X/GYv+yevZcvgiOP0f4fmoPfJzpMkN2fvNZrj9jdo0Cvl4MmSS2PvaQDnuYC1g2WLuaz+Rp53o25xlOHwX2vtLEa+R+6e+Hj67uQyr36DcycxeD00vc7GVU5eh7k0/Pc7AQqRW+3pe68CvVaqI02479VOyt2xAp2VVc7d+Vcnr++5ObuviiXPDp4BvVoaJloLC7MmURaN29a4rcN3sz4SqcfdKzQ3vdka41w/fPCJ6XbykVcOhLS4PCeEQzMfo4c+76OzG9zyLTp4ORyEsT2Bn8iHJ7FLNFCGJIekh6CjMIeohe9Efp6A9ABpvpS849NQhaDxfpG82/6L8HwhnwD3HKIPbH6Z/pK8qHg53DSxhLESsTsC2e0A0qMyeC14TGqvwZ0wbZBrXnJ4M3zEeDf8zDpIouCHE7GIo1iFrqp4TbE0fNrBgSK7Bop4O8GdsG639bxw/NJ82kGeMGvuoCt4wLGQo0CFl+TrwJA6KJY/V7HPJ88M/j/fKCXLC9zcbyT5Vxz84TCW8X3aD71wdKugaJXPkXqHg9WtKjkJG3LNWxSo317h2B7vHmkJYN5zxdcaO7dvZdwDrzGbFzgUbnODcO66LQyrYvCX+GAdp35cY7oT34vYHG/5dsf0lo03w5yW1vSfGPCWbxL+yyHw3Yb3JlyW/jRpnw44q95gFMltBiPol87wltF93Ed+TzlMdcA4q+xgHNd+UvSrmeDOoX3JlS4j05lLI58nJlN0ZU+1ZLjzVjiCYjVLMGfNjiyhbqvEIZOrwpy1AsE5FME5KRg8DTjNLBg83zKulV0O7TlZJ5Pcq0d6CzarMLTMYvAZdQ7Gkmr/VTftqvt18uTktOPGkLyBw8w3cAwdOfX8wfmMNHAMOiz8XJvGZjNJM8CsQ42B9egSX8LF2qwza+X816hBjtut77B1r2/Op+9y5h4W58CRL8Zt35/7RrtLd7qDGX4jIzIHEN7SbXkVvsHYJ9pjFWuc/oUH/lJ2WZUHxudM2CSDXfjnuoiAp+IGi/r+5CbkrT60Y+d4hKBermdH+8jz6AHlLfKBcAneujGb7KwJVbNAk5FmrioKx+Enf3v4g/rc4MksMfEHP3GdYVqoK+aDhv7gRyzmzqTWCmc1c89nL39tBAMe84doq/gy3sxhaaB4utZMz9Ieh1lsgHhgNdF73GBak35je98vS6+2HDwZJmMVH/7SGYzjyo+L0dJThbkyxsd9VbOipXOdvXImimLA+AdkPMuKNPhb/UewbSSTVt99I9TsJ1Q7XFjNOtEiyr5FzlpA7MGMS//0BtPOjK2H2a3RaPD1e6r26zq0G04bY26lj1G8nXlHUGxlCUg8/eHCa6CEtfxER5Xjd0eKu/RAYykg5nPQbZH43YMayBkdfwzJwVr+sjUmt3UDXTD5+RLKxGIefaP0O4eMjj9P/GDpVe+8Yz76jA6+vdLaftxWIzGYkSOjLvUSGCxRqS8O7q+NHLyzn2upevSbTZ6/eSx3rj8qZR4SdiyautwaSqOUbsfvf3bwcSWGjL/cfm9hb9lVT2jIE3lTOF+DujKuug4wzvoPuMvDUntHVpks66c955vD+1BdURLMVoZvBSLJDyzKp59O1J+IATyKdZk8P1uwP5pu5PknIJ8cBZl+VEfjeZPKqTMV+JgbWCYa9UItW7VD5hXrq97E5w8+lqcLwmkr4B+O3CXvPl8UFl+UKj/DKZsXPQ8r109h3i/vwz12MTcjPhZVOXvnHt3H2j1fbBZfWCo/fTscIytvTjk8904vrxHdZ9o9J7iZGy+fbDk/Rw7XzxfTHS00Dttb3ie12jw5Iw5P4xTXX7iveR5fvTOVTwmaXlsZ13cuX+NZPwMtk5wZNV1G0w7ZJwU7rS8DwT/NyzJ2Tz2uI48Nd9gmPDseMiNP+Z/3HsTRWSoyPTFuwHovee/wnhPTm5fZ+VkxzeFBHnNRVe/fDa1L3j9jH9gn+xddRSMvFq8eJ8AM3M08cF6HDxO4bDUR8HIvPMJfXhLubseAX2y6h4AONPk7Hfcec1M7HTUtTdx5CAvExwwxGSiT7Zm6MR42Qbs/tkG7pzVmRbs2WmZVJx8XCUX+Fp085MiaJ0p37i/vKixQ1Q8fGRmbVys2djU7Hyb+F+8WPr1b3V4hu+3cOTUOLTWbV9o53pttPjWXiJ81l3YvOaYOJz+Cs1vfFDLsHz1/UD9/gNgUzIhVtPLDlEcue6B/DjrGfmx2pL4jc41EfCpVlPjDpksrGQUL/7SZCH0bkMqVkpR4daAkEZf/eBJU0/awjUD6HbeIjYrPunKd24gqZC55cR+wnEmV/Znyqa0qZfubgqkf1sjfvOsgmdeYJyhio67UfmqSmZt2wUgmSVkTzxLeu5wa/kzKmCfBVba8ml5Q1ihOJ5Xmzu9t3ucYDxBzNtg2sZIvKsb1tepjmtOkaHQYuppnWur5aii/WiJq3/DMveIlGKHhA4hKhvxSVvd1Z4BHUiOXA7tVloikIqBOnKaM0aDTkX567s+nwRjt2kN1mZBvNigrmrcs8TFi6enVPrtMRcGuIKc0pznxVzwJdqUw8fwKso2jeOkmqX1WlgCqyozQiJdgqXKWk188tvuQqzpejK6wsD3fTkwJau2QOK30Ac2H/Drm4mYmGVquP2gZDc3shlVlwKPAvvUjzSRRcfuC6jyvjQMVWtw8UDjsTm2xGt/cGIdrOcNm7YFfVi5avhQrkhjl3hpHCjwBJhbsaqvukZ/rzYT4e9hUXIJqPsL7FfumKcE4jIGKQyxhZrRalmaCrIpmfBJnScBv6p2A+W27x+xB0AT/cIepKs74SPQxfkd/uQD+L62u3OQKHFFlzDUhfwbBE+lENYmpzLn3X6StU9J7CR0L/CR48JqYCWyxd21gKJgLBj7xsi2xdb+sQxJVP0Y7iJvDikVwBpNuQufBP0Ri2sgCQZMePPk50BhvxaXKo0svAuVmE/s9CJjq4BEF4Zt/4UsaGxlaO2ThJ9e9M4b0NEYPlqlyqlLB5RGJbMJfBBXCWEGdTd2057MOpdi9nVEMVV3rNcSewJISmZ329bo+aD+kzzgUX0vncnhUuVvq/imsL+FdsSLl5Vxg+gdySlrlmJqX5Nz0U3Lz7swt8rLQnWEEcZI3Ev2r3BkgE8vQ+imtOXdl9+sLGFIStlnR5t3k+ygio+axE9xhwXlJa+M8rexjKJhdnqUmegr2YyiPIV96lIpwRGUaaV9AFL9Nfb42npxjaWRrkZkDr+HfwYWZyTJUrrjKrZEhoc8baypMlL+15Y0pmy0BL1RMNB4sI/FIf76yMq+oXie2ONNL/vL6cX3SvorERWh6oJmykHkIWubH9Z3kN8ZZ2pn3qAeb8YQ/mIQoq1i6gufiD/2ZketBPlEYzdNiJeH9zCEqxI0PWPSS9umwcQO2/qnVaBL4h4kPz2+O74HnA/hGcGgR2xBLEXsj4A2TFvAJdY94GP03ztL/0reR75qA8ZpjTL0eyG7B5jQ8LAbi0LoeyuTYY/TvPklF2JFJfSOJLPM89Co+eyOaNFr1KUtNZ3EVgjLk+c3BtE5+AuXqeqLcGsXbVUxXsYfZcvPg0QrVadc43TPDyV1YIVILaRYoVSiZkuwzmVYYTpCFJrizjrBc04exCD2q0pnXbGWeBuSJi488M7PqO/9j/5H0mWm3zPfry8/njdMldolPcc5aC5e6T24TF7ppomJYdFd8+QJO2Zp79/pYN91Puouu5eXa+QrKN4/+gBhJMiKCxopumYeW3gWcxP3CY9DdXnsjuYPdH/v19UWU5qASzMmi1djQocaH4G1TbjCv7pWluq/0S6WYxBTwnCuxf+2KYtfytsgSwjHFR6YuLYXjCEUVJLGX7qSbhKDm5QRLTEpntksNWkpjJh37937v6aIxncDysGL83aIThjGaOMKQYTe8kG6lItGKfOX4gBDUQuZ48ALm+DG8/yBsMXbpe418JwBSAKmBNcFaYf6LCMHPnRlFALUP1BbJXC2ZD4kRY7XAUVgyCHNUcroUzQWTR4lRVhopOBopVFRhxaj4llQtl3a2Ovgo5ZpDVoLCNsKm2OAuecO2OkYPKL1JLoAE3ucKXo+wuRqpEQibWB+MLE6I/xv9x7h4yrNA76zwWTMv8Q93u0wflWafW5G2lCOVjsifEMw28j0yfCPey8/Dqrd2YrZy9iUzmyuj6XVp1nVtzNX77jjT9elYZ9fakVm/IVh4r9Rmq4h8cTirRUns80Zvx/oCK8bz5KkYTpsIgi8azDhl302m/3uvEFJVeWibhxIxjaiOtJgY6tqR66M7l6Y6j4CmDZMALx+CVFY8Hc80mUM3v+UP6FxkhsZ14WFyMke6Z3GxvzC10P4U0dgNzwkWiJ/Ke/a1V/aHEwcnz3GnyfHkp8kxz4/adOYDtI9mu9NALmRAVf3cgvWut1YwWH/q5phTY14eewWK1Vb7hd5GTchSj7dbZJ7wl3eA3rK8jtoLsdr4XzREVCZi8kqPy0P3oxvjMhrRKtov/78wwGZzsIVB64F6/JVyohRflX6AzQOKb8vUBd2GOZC08z7mW09EfYcjxNLlSKdmVoU0a7rbjkHu6phlc8F/Z8vwv4As3/E7EBBQcm4bmXU0MC5sbpR2pqumnb72Zj8HmqnTmwmX6ZnphpU1lr/AIjGQceN0N8CkwiAZ9t3TubJkh2osqOm43ASyuDnIJXUU681wJ4UgNIzMPGPr3jEHZJqIYqC/wv5dBFfJ2Dpwyj24Dfqsy3Hgij73yUEaxHUvbficpeMgWldMSnLXjKB2S2/1dk78RTNXCHHyCEdi+dIgWuuwBOHUI8lH2n+y3sSaUsaISNcDe6pVzohHeFUy4dwoQNMiDPzuUEY3XDYH4eO5KAygfobLMYyKhoooxShv1mKQHFiw0rkhaVDg4FkODYuNj/rEc4DvnmWcVddP+qfYdaQfWHeKVSSbw6Q/eJ6MKAg1QGNKD5inkC2vLBMMGwkXFeZq3pZPH5EKUQTNoKJxZBwscL8Ma6qw7CqKm7+ssp2NsBd2O1cXJ6eHj2jKNpkptngfExomif5h6Jv+XRcGiV9nwE8cNCwovHgSw+2A5d/9aPTX/3vl09nKsnuEhw56YL/h+2eGB/MdJ9+raqCP07w7Zz7d3vaNq7Q+R8riqkiQ2p3fv9V29pu6UQT66obfoy2bKadh+TBV0Jpw4ebtr7fUlEfcxmDkylBn8KuLplTuhdXkReRbR8bbhv43HOMNJH2NhpRLLcaPLMOV6QO7fuod/0cpXYCBPZLyVEhYP0kGfUnqNcwCz9KjDMOBWiDGZtLE1A6FlJv91ONy6kpL2j02w9dM+nf2zF8jOSXjNbthBovD9aXLzvO1KsMd3h9lJRMfbB/snpfZlx2m95VIi1l3+SunApFjORRti69D74R1D5n4Axhsmp+1VhxT2G+BN+jHH4MXEg1sLaiqJQ9tTwlsTfXkvx8KiCdo+8nYwc90gMkAzblcgKY0xOY/sYhYs7i0fdOjFO0ijFfI76Vf4KbwELkQtphMHhArKLPwCF82uJPtq5wwPjQZIzkCH1Y+f1Y2iYweCqp8cKBvd6qBfeCUROGC7wK6ChyoYVaFp1LpC6LcuG44BrTa1m0VlDXdS28CPEnUXFb4X2nsp49WyycTd2BWZhxbPqdvtyRdKAJ5ussdlyZWl5SMKoI3on+ykt7XeNF14ThfhtloKA83Wx0Mt26FhtBotkZo97EPpBttoKIgabxudu1xZGFYYVkBWYFYQUhBLMEtAQ6B6gGgAc18DXsVew15gfDgEGDRoSHAI4EiAWAAQYCBALwBcHwz9jiAOgGyfYcBRHq7LOCoWQCNfOV56XR5dDl22UbO7TbBXrtQY2FHgShBJsH+Ae8DFAD4AWDMIu5C2oJwdp7v2oPbIstCscL/Vg20Ck8K4Ak2Cn4IRA845gvSq8rwCcGL1wu/C20KaSt8x//j/F9SQFXoUcqqbNxPjujNvKZuq3twn40lwotVlvIBzXeM8T200pyOWJ7WFaNWwMVocYrsyQotrhuYz+yL5s+fmj2rtx8SrKa3/TntUGQiOOqqWdbSwV2JLR392yIccrpXOZIUzM9yuyMwnnNVWx2QltxB158TBtu5T9qWwV0TbCXrThXGws1dtSwt/dvG4iR0zooxouEPAdxk9BtkI/8Lv2Hv36wXm0gBPU0ubX0P5yrWt+33u/lt2HDWDLYc/huoXTVA1SzjmK2nGidUfUKewte7BNSEJ/flL4zlrzQ3aQWbOcUr6Z1EKm3U3zEXNBgDUQ+Tz6nTE+G0UI4LPM16kiwxthA7HMvMsdWE2D3yet0/SkU8o8+cno+hdCcFpkuHcQH4plCHvQuZKfn2WdoN+g1XFS0xuO7F759+DwcOPfCYPNzwmyuHd20z2CvlD4fw9enKWR4ol9bWmRzXbJv63FHTKtvs9pVD2/nf3tpHEy2DTmofMcC4Qm9Z6Gpr1+cTD+CMPXHnLHcBDRFUNNwMNQvvR94vL4YfO+J2WrH0BiE7OG+S23ciXuoy2xqHaB6385u48fAv62l1zRp9k3c1LgjHW1EdjE0efUFvaDc+jxdRLsuwjZWdz8ZjcRtZ7cVFjS83p/OWW10yWuJwlz67PgZTZ+EdLNQvUuqenSKDcTRoXakvZs4P8ZnZNIKMFpmp9BR3UwNdH7Bn2u3EArGpVxnWah9VbezybLTy6Q2cXqsFcW5HFF1QASozR/wyytMYzCWtW6Mv1z6YbdZ3XeFwHsrYf93w2Yh3b3dSXLtscBnNfTgED0KxuewfQ+0+y6UU/2ZNhQn8XJsN9BfdgE1qIB2kv8tY6cTZCD5QCKRbcbw1OOeHuajXoHbdw1e+yT1MbPxF6fpOm2lTY2EUJzvNdnySPM626V55VlbGgZbyOKsizEk01wIO1rlu8XE53rcIaXr8Uiab+yn9uDa6aIqI42AIwvlxNTq4k5wa+dhN8s9CQmQnEYP28jpFu7FslHbaQsnP+qq74CzZOmPg8n5a8Wxc4oGo4NDM6W5uYKbyMTLje13MJqHurA7uunIc5HitWhSJkE8Ugh88FtO7ohTU69487kr4jNSWaDZIMil6aAhhbVlVVaanmOFjT10u+GjQSCG23/mWKiRu5jz6onozyAkaCOx0cUGD425xF94upzpMqsvQVkdu7Pc5ZUbbcfYS1zE6A1yWiYmyadEtNbDeG+pa8KbieB2/vzGBx+wU3UZOXV9u+LFALKBQQKt0Gc98lj+rQFPB4nAavePXtivYMZ+i+gGtsHOfeK60XompudhxLz1hP79AVOkvDYpW9cphHHPJ3fvBmwwP6vUZ5DQaej/VhMbffR5x72/rPpm8K9mJRP3EUo4mjiiuyFN8MrZSMbkqqQNuHwgnOt3MC5XoKJmu/QtIN3J6uYmubBzTv4te
*/