//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_STRING_GENERATE_FEB_23_2007_1232PM)
#define BOOST_SPIRIT_KARMA_STRING_GENERATE_FEB_23_2007_1232PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/char_class.hpp>
#include <boost/spirit/home/karma/detail/generate_to.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace spirit { namespace karma { namespace detail
{
    ///////////////////////////////////////////////////////////////////////////
    // pass through character transformation
    struct pass_through_filter
    {
        template <typename Char>
        Char operator()(Char ch) const
        {
            return ch;
        }
    };

    template <typename CharEncoding, typename Tag>
    struct encoding_filter
    {
        template <typename Char>
        Char operator()(Char ch) const
        {
            return spirit::char_class::convert<CharEncoding>::to(Tag(), ch);
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    //  generate a string given by a std::string, applying the given filter
    template <typename OutputIterator, typename Char, typename Filter>
    inline bool string_generate(OutputIterator& sink, Char const* str
      , Filter filter)
    {
        for (Char ch = *str; ch != 0; ch = *++str)
        {
            *sink = filter(ch);
            ++sink;
        }
        return detail::sink_is_good(sink);
    }

    template <typename OutputIterator, typename Container, typename Filter>
    inline bool string_generate(OutputIterator& sink
      , Container const& c, Filter filter)
    {
        typedef typename traits::container_iterator<Container const>::type 
            iterator;

        const iterator end = boost::end(c);
        for (iterator it = boost::begin(c); it != end; ++it)
        {
            *sink = filter(*it);
            ++sink;
        }
        return detail::sink_is_good(sink);
    }

    ///////////////////////////////////////////////////////////////////////////
    //  generate a string without any transformation
    template <typename OutputIterator, typename Char>
    inline bool string_generate(OutputIterator& sink, Char const* str)
    {
        return string_generate(sink, str, pass_through_filter());
    }

    template <typename OutputIterator, typename Container>
    inline bool string_generate(OutputIterator& sink
      , Container const& c)
    {
        return string_generate(sink, c, pass_through_filter());
    }

    ///////////////////////////////////////////////////////////////////////////
    //  generate a string given by a pointer, converting according using a 
    //  given character class and case tag
    template <typename OutputIterator, typename Char, typename CharEncoding
      , typename Tag>
    inline bool string_generate(OutputIterator& sink
      , Char const* str
      , CharEncoding, Tag)
    {
        return string_generate(sink, str, encoding_filter<CharEncoding, Tag>());
    }

    template <typename OutputIterator, typename Container
      , typename CharEncoding, typename Tag>
    inline bool 
    string_generate(OutputIterator& sink
      , Container const& c
      , CharEncoding, Tag)
    {
        return string_generate(sink, c, encoding_filter<CharEncoding, Tag>());
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename OutputIterator, typename Char>
    inline bool string_generate(OutputIterator& sink
      , Char const* str
      , unused_type, unused_type)
    {
        return string_generate(sink, str);
    }

    template <typename OutputIterator, typename Container>
    inline bool string_generate(OutputIterator& sink
      , Container const& c
      , unused_type, unused_type)
    {
        return string_generate(sink, c);
    }

}}}}

#endif

/* string_generate.hpp
LA0oCAxVLjkxaQSGB3yWw2pfGeH6GQwUwW6uuGUdWBsj1lFpdA2hq561vGAe0kyzc/Kzk0kRx0s/ATjOsVfWBZwpGJ9oW3kf0MISnurfo6Oyc2ag0wzGqcWiZJ3dmY1yYL9nTILSHoerZ1fc+qQRfBhy4JYH7j/FfFZlkBiKQLB1S1G+0mvZ3dS1pQ7Ri4uLOK2B7pADLXigl3NP26g80bpWrlKI0VRWTzuTmpIlU3Y/tyyW7CEbs3rmRXBXQJB/Nul8zCoASfGUl1LwfAlyxJz3TibAf+ukJPh/GeAB5vDGGHa1/1FI/OZOae7LFspXcgIOwhQSy+hLOCPDCqZl+92XIGZu+6vfPWZFPu7hpp6lqwyzSj01jbRktO0MgzzVW7Gw5j7Kuzeb0EQErfx46DGEtqPdplX0paG9JM+covNtabTgPonCwjg3BhdCsCzm3TzSAnN33EhN4FsAO/EneoxliHz6k1fffi+qY9g2HhtRHcJdKyoyx6x/VnZxEAJUxQ77VjJw43JCnpobqYZlOx1ZNOTDY8fZDAZxlY18qIxxXLCG9i6wTzaLRDa4rnhmcjow+TZ4GhtivXaC1hDmKutTLEhddo2gLj8kQNLU1Ff55Uq7ehj1ZBUK9M9o+/GQZafQZMWr1aFptOIm6vzRhLWt8AdaKxrZ2wu2G68y7qcyxhqXl686BmsTf+PjAyfYZ8ZuGunj+SOcqjWB3LZVhemJLjilG3v7qdRcdRiPB0Xjt4hq6dC380mwHXssMS/t/4Wv3YepbKM8lLevxoRItzBksHxdD7bqK/lA4TKniN7ULsLTrNEpFTdZbVIy4QuqENOdZ9rUU/p4UE+jh6I/Kywa8xKj0egW0Rdgd6N21ZiKG+KQrxbHrWVwbidoX9u9SGNkAZxAu+3+s0puxEX5f79YSr4RH7iH8FuKXIiQ/FcjYkQmkcP+i0ASRsJ19UCkSn+TBi+8rOSazbgU4dvqWj2wXg8+r89Y43uJT7n+ERcRgHqmPs1l7G0voWb5XuLl3G96UaiE2vGjj0+asTZjyigjP+7frS4Syj3MHtwoRu/6BpFEjXk5xeKauxlbChTzl9d2M2PwNtqiffD8zU84VqRyTX4IzHu82r4Npdw7irHGj+phfbQBOJHxV9xutPGtCnrMOxIbVxzpTYnF76yCRsly6M2BNbKchgDMax3CsIqy8o+j/L5hFS9BXf+EA50Dyig9PBlTcsaDM/rjvuM7j0Jh/yN6aVWUTxX5d1ck63kwWQ/HvbqqZz2H93xjivvvtkbm4p308d5HKS20gf371Wzx2Az6Fh5xxUCvCP8MCyd20csc5Rr2YuMQNBhOEgojzuJoYCMmXRy8EftcHRqShxi4/CH725/5m3KJbOy171J1gY3mwjg9hcTMt3oMoY+ahumbGYeOEItQ3ESkrSGgqTZGAys8b3SFxCO0/43AiugtBaLhxdSz9ZH6dFNdE52T+R1TfT4aWG2q641DITHrb3QMLnQZbm1vmraDqVQ9+ILaX+g9cqd3GoG1+hB9oUtM/RUhyF5HXc53CbPNq29wTqabV5tpR/iWOa5wIObloKY/DvbqE+e3HxtzxpTOp8SzdNuQibQvIy0biQ4sLk6N0zGMP9Tn67W3XM7Y4kVQQEGZy190XYF7N/9mXcHIriVrRuFqCjf/3vHns/u17SjFoQ4UnykJy3nttXoPoA1T2KNfPJGIgnqpndxD6/5By0GHeM3yAJTAP1Pj4ZWAXoW05XxCV25zRINt1stapPcnY2Xb5XBhGhMbbmZbyBoneCD8VoQuk6++diReTbBSHeH2EhZDSFJz0lnUwIZajAwQxL2BmNkOObqPh0npzS/2MSBvJuQqD05+d1Zm5jYaJ2N9/IF4VUYuoVfdRqCFqGfry/v40o0v3UaTXtnqP7UkXZ/RanAtRiNCBWmfj9J2XgwJ9NXQFtLqRyEWYKC1qj/P6SLr/Murjz3oC7ZW3n0k0PZJWdsngba/P9TarFr3Lf1yiE4TtU+nOZYHYrFr0Far3ZdeoJuZcup/Fozl1Y9diRWh9FrOf5Ow828LGXZa+M2fnyX8xksJhHn7+fjNd0H0PfxcAr9hJoxoOQSP+G6nOsNaBkq/FB8tsTvllNTsI7TtvzexvWlWQy3aheGPwTVKi1SUGOTZXIvGRdJCljupe163opTU3fcgiMPGB7MtmZVtbxOtBTsjFH4pn3AUcbyWjo7aw+l4c5TftPEb+DYNhb/hNx/wmw5+s5zf1PMb8KZC4af4zZ/4zXwu57/85gV+s4rTVPCbn/GbQhfefM1vyvmNi0t+kt8s4DfbkGbrf+hNcako5lejM5DoJ5zI+RTe3JKRLGgqvxmLN5RjHD+N4++yU5HquLlsb34GzMdkp7q0hMMXa7P1cEVw1KgtzLBsIabpwQ6aVT0Y14lo4ECJNmMy0PFq01gIlTtfPYy/K5EpES5HlmFuXE9Q5p2xrxMi8Ns8xDxiJbyVP5RcWZoXtovbO4qg4TC2qjJLS8MFjKHFEXv0Q2Ml+lLYkDH6d4O9X6YzYZ2p98OTUTs5g30X3avXgQDwbb8P7jGvMVZO5pYAR9qIQjbjmRthbkYSMQBNqQ3J3P2t9P1LSwkRHO1CQWi7ckPPLpWWRq6QQX0Oir+CIcU9tGMhfWjUYojnGQfnvvpCzmDv7HZXYdyMZNV9DSxj+TNgG0VXYpFQF2lQRd5jcdM3HqDcU30xwBP3X98+MyPRgKFU0+weNen8geujcZrC4xR2YZwQnfzQ/4e0t4GPorr6xzfZTVhhYRdIIGrAKFHRYKUGlHVBg7AhCMENgSyovNT6kq7aou5grEmEboJMh0V8x5YiVLBYbaWKEAtiApQEQYhIJUqq0ab1pptqSGJIJDL/8z13ZncD+jzP//NDZzNz59479+Xcc88597xY4P6MCi3NovFkIAmvRn1ER+JDPjH0yx6EFhtIQ5NavZlIQMiqIF8fvQWaOW1wQKZSUvE+Fw3TFdcZq1ogbNOR4CB9O+osEhnNp6Kq2So3jr2+nM7p0OEWo02teo2mXR/PcCEBYTzDShoaR+MiR9anP20EXxpEvWmm5SquXN6hR/oTJg0kiMFLOnVx2VNxDJIxEByF6iaP105Y5nH6priWUIIxZpdSTbOi42KMF2+Afjn84q+/gOs2DIvhjNhW9cQMmqPmNTGbm7sQ2QdLKtQCX87n0ZCItF1EIKweJxNFf34aazz17mzXw6uxdEXo7R66xUonms0ugvwIJMM29Hfx42L5mCy+2YFHoBd2A/BvfiyRjzZxnB9t8tEqHuJHYBX2pXAnP6bLxwQxlx+B31j1LJcejeOyCaOoWZ+uiT9Qssft6GXj+xj3rXHRWDQ8wUYKJ9wjJIA6Elg0sB6jaVrvD7yRRn71ZMNbws072nUJHmFvW/HJG2h24SOiffU3OMmGZmQg0y9mPMZ6yXAo2F/U/rVdb3kD2xu1U7xNT98Ls4uae2BOTd/sb4Jt5LG+S1OqmLdpDZpHgjLkFc+Ps4GJnJnE8v4L9e0MCttRtz5+g8lGskXZYVEISaxRJxgP+Js46xsJBh8N9kM88QSOSe1Vf7qcHv64GqNFEHvmcqhAuncDnxDnmWiu6uhabeS1qnpbEQ6oYgwUL2bmGCNo344RBNDFRrCsV2wNE8u5z+EPZFIPRf9yOFaCWwI5hqG3aQyhAsljqNATApupZW3FvrgPQifFWcGngxsWUAVPsIAjx0HEympgQcLwzh23zIGbL586t1VPrcdxm0V9nPMZ6BEhwRg9+sXPjnfr0ZEdpd0yJ2Ah1nytMaZwyjbIRMKSp4tHwTtQqXjiqi6iA1ppmOCDQuMvqYySGSQkbteqmomVV8ta0fzfotjntyN+Fr9TGxzcCW78EUix0WrjZTczwRMAAeZuYIHDsDVj44EiC2DT+j+2XOZVS0rjuuAXH4yh1u++PQn0S7K6G83WVnOlB4AlfUYF0NEg6Cde9xK/njpBKl4miQ89hCflpvhyVhfNWKoFshnuch8wk0n8COdm4vywVP0pnkkP41YZ+CowIftEYXHyjTQ8F1xqMc7LWWsdeExsHtmpv+t4AMHU8CIOZWgjgQnxGIdWlnIie7OJoZ6fcCIe49DTTFRc+iAqLuE3UTx2DWdv5cQorhvBiXiMw4d2rkNBHcf4TRRxfjUC2fEoESslnic+5kTjsb9wTeLwbsDC4sAb7XBBM0CcnsiJwCRim0x0iH/LRKwu8eIb4AOhnj9Q5dkl5p9D3/plVeqKxcgmqmgxGfU0ynsuXk/3G0F/qExmbcRur/Lmr66fyr+8pNbP4d88/r2df4F6tP2iUIsd9xQYFNA+uFFlwKPN7Yiz4vaEKD2T8T9RMnlXdumF34tkwG5dwwpTxgCloQ/+4iWcJxOL8kPoHd88CkOKythy3++LwxxwEMXII5iv9Qsky4qgTOe7U5s2B45LC+bTJjCTfpw78ntpMWIZwoULvUOwyWLLY9jmzSSNgwxFpr8buQFoJO16loYM9ptz+OwbEIjQCvnLBKr2Li+/dmo5GYF2qmSqUYmBGrD8qWUfxi1wi7HAsax7+/SUo4JyL8X8Szr12xYtNLQC2Gcm+0XNrvb5doL01E4WGt339urHK6vLx8j64jDqcRAfI3VvLz5q5NaPu729pceyq9mTpF3qGirJ6mp81aBVa4IObdkx4DRGdQWoVlIrsgaaj399p7Pu1tsmlzVzJXFZd6LlL1x1NpfVz+cTMCES+kpghglVrwIzXLASmEG8qROVK7t2YvluwCroZ2VkYWE8hX08r5CGhkFZ3HBxp75x67OIMN/qZmB2VqxPiLZ+r7PiqBVbTZOubgXFbQz98liPfgBW8Uqsu7xLFxl+2H7ZtJzbcYS0fjF/gx1TUO12fIv189ECpHRhL8hvgGJq62zdl6LVFa+zpLhoCMSVJQAPZ8V7yOJtc68FbDkrdjLya1YXiGg/zdkRZddAcN93IvcGh2g5c2hPrfViH7V4Js8JWqkC3SvcC5qDf6UfJSBenmA4wrrjz+wXiPqZGJ7bOJvQLC0G4qYLi6fE1QoaGL6mCuLn1tumLUMbPTxSSjJkv94mOA4yRFDb/9Kuuxe0OisRy1Bkm5/8+k/tevF/buAwk2ihaLq2QydyaB6x/3docpxuBZtgJ75Cy7EbcahVb6PnYPBHtHuIDZfzMUEqtbO4hNCVcDwM2ZrK0yonOri9ZRjEwdcRNcgf40/bXm/Xo2Gtg1+c08/C+C7ShOrHQ2VN0Lr1NtSuANJDe9FJ7jINfpO6AsuhD9CL6dcZJFASevrRTcZO1DOeuwnDykGcynke+HNck5wVM9gwoC2gF98cB9PFxym7qIqv4LhZwdi+FfT//goaUMHD8RU0mBVgPuIqOHDmeyv4GBVcG1/Bx2YFf+5bwcrvr+ATVPDNuLgKPjEruL9vBdO+twIoJN9P+yX9ebJHN6hGMft1wG8U5KbQY+TWQoN3efGOTr2wuC3HAqH7L2BOWic0Sit+HBp3P4u1ZTCnmGj709f6NKfqO/iROiza0ol/u3+8AcVXvEpz2yqhmEXDF8R3rdWEuKf61nXfd+haFOqKJdQVxrF4tLBi3Qn+GXJsybO8BW64fzh/l7jxA0KEzE0gjKQhbhZfNfQQGUCItDUy3lw6IUEMx2evtOvzQ9UuX/xXGbgJE+Erg4ADsO6U2iiOkU3JPhDqTnC+WFMgCSox6yc0oD+YBcSNyPqJ9L+Ahu6jhkYmFhqFj9AEFBq59sp70Gpih7wHeSVelffM2L64WPrxNs5gHhuFM5i1vx3qEiMeYh/bhCfSic8JV+VRNV39EhRYLoJ0E3dS0a5+NiWt0FAiLJT1giYT0xazNrH47a+gBVZ/N6RqBbaiyqPBy7XJcGWQkbUnJ/sobZTDK4+WjPEUpJVdrj2QEpr4nCV43k2e+tKW7OqFe5Hs0vbX2tA3izbZZt2zcK+oGxs1ZJtsg6clT9uDHs8D9oevzWoruc7zQFrZNdrklEJ/9gntTM2XidlH3XMdzmf3hm+/UE9In4D3Q+i9tXbRbW5XWaIqI1eLB1Grycs6lssTnmQtr5PI88Aj/Yv9ln7LhJ1m8e7QhARlHjy22mGG7HupQ9fHiqM/TbTMl87mtG6RQRDJUpWfPN7BpyqjcTzThvwZlB9KMrh3/yHqMO4rAnWtFgIScc9ytuo027JsWaJF3HqNge6GbWlHICL9WqnzDw0zLyJoFt+TQvP39E1s+Wt86pOXo9U/QdWLQcuZiETFD1DFly/Dlq/l2rNybdkncjgoAC+j1SDqPAdLUz2zMP5FKWr6ryd76kpbW97HPOddzY4RxL9xDNcNta/tlMyBWzOlSAiCpd8j60s/NrwDLvqDoRrEXjxp5OCG79Vf4hyORzGEvWiWzVPz4HBPrv3hIVk1Jc97ctPKntJmpYRty0MZtBHgA+lb4PlMV34kH5lvFwuoIdkH6KPP1lQecFbABKGSw97ZUPVAHObSxBjLvfKP7foUz4I256qF2DG/fUwOtr3qMMigofTItFL2CRoPU2xR9CPZ484S1hftcFY0ocdLoz3GfroaSprvon+F/MZoqrPyaZDIMs1FaVsygneJX481Bib3ZTkwfjkoh8VzGFWvHTF+S4sBa8EsmkOxu5c7tZjKFNCzT/yDsZy90Ki5m8Wr3MtwXpt4kfCRfCGH6PoS3s0H6EtsqA1jQoPQ6lzlo7tIqoTuKwGD0sPnIiovPi03x6YFY3NlOfTHHHnBkXlKBtSZctIZkMW/pkrTgYFVs54a6NorOi/Cs3ixXOptRfWQ2OeBNTBhkV8cepSWi7oCp1tMvO8a04EzZ594+T76CKfDVn9C1MkA0abn54MMnEjduFRbDb0WWpkXaq4C0H5p+nakiH4PJVpCL+PWMt+ICIqiO2H75RJF8quc8+BMnlOqUBaVNGSK/F6CVIGlTu2l+w3LcH/UzZqqQbvUWI0kzxY3DeOO7w0kiOuGmT7ZUIIN29lJoKnSahe/PI0wrVEBekFRmPiSk1q+wye+uoxnJ0nz9kbYAMmMvL5mdKduhDxlFTJHnow3OaPILzy5NBy0PNu0fp7cdMWhTbN5cjN4b7wy7HX4ArbAEL+emvbSEFdXvxwtNx3xlOBEsOldtZ+Wm6FOsxleJhyW0Nt1GLLayYsT0cWhxKIkFT+AvQeObXBstLflnXSoxhaBezH9EwXmM6nwEr1ZaAwbPAhFGVV4kAOCLiyCj8Nt18teAlTy/c4dZypPBG+q+cp1d2WXcj1X+7gFi4fla6+4MqghowJthdIvfKjJGXQaKtB2qEAPADHcq5YsjjJP8ptwpgvT3ySx4UrIvRw0zD6x6tIfGOEfXW6McFXvPTgASiuO875ZWV2S6lkO1aGygZoKTUzNtpzhdeqVMl4JNztoDlQnb6LX03BAwZC59GxdpKfwt3Pi9tnh6dhn8S3x1r0dUvN9hLsKkxBMPZVTQn1PCDoQN81UW0GsEXglMZtGLCj2lVv51HYOf11WvevCaNW33isjgXg6gldLHV03BzQpvxiIZjjw4jKk0pp35zmCqdYbp3g4Q+ln9AXztGeaI9IpT8S0BYikUSZj99D0l7qla0Ka0BY+Lc3NcPfjCDBoiruf
*/