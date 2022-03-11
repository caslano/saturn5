// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/detail/comparison_adaptor.hpp
/// \brief Comparison adaptor.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_COMPARISON_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_COMPARISON_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/call_traits.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {
namespace detail {

/// \brief Comparison adaptor
/**

A simple comparison adaptor.
                                                                                    **/

template < class Compare, class NewType, class Converter >
struct comparison_adaptor
{
    typedef NewType first_argument_type;
    typedef NewType second_argument_type;
    typedef bool result_type;

    comparison_adaptor( const Compare & comp, const Converter & conv)
        : compare(comp), converter(conv) {}

    bool operator()( BOOST_DEDUCED_TYPENAME call_traits<NewType>::param_type x,
                     BOOST_DEDUCED_TYPENAME call_traits<NewType>::param_type y) const
    {
        return compare( converter(x), converter(y) );
    }

    private:
    Compare     compare;
    Converter   converter;
};

template < class Compare, class NewType, class Converter >
struct compatible_comparison_adaptor
{
    typedef NewType first_argument_type;
    typedef NewType second_argument_type;
    typedef bool result_type;

    compatible_comparison_adaptor( const Compare & comp, const Converter & conv)
        : compare(comp), converter(conv) {}

    template< class CompatibleTypeLeft, class CompatibleTypeRight >
    bool operator()( const CompatibleTypeLeft  & x,
                     const CompatibleTypeRight & y) const
    {
        return compare( converter(x), converter(y) );
    }

    private:
    Compare     compare;
    Converter   converter;
};


/// \brief Unary Check adaptor
/**

A simple unary check adaptor.
                                                                                    **/

template < class Compare, class NewType, class Converter >
struct unary_check_adaptor
{
    typedef BOOST_DEDUCED_TYPENAME call_traits<NewType>::param_type argument_type;
    typedef bool result_type;

    unary_check_adaptor( const Compare & comp, const Converter & conv ) :
        compare(comp), converter(conv) {}

    bool operator()( BOOST_DEDUCED_TYPENAME call_traits<NewType>::param_type x) const
    {
        return compare( converter(x) );
    }

    private:
    Compare   compare;
    Converter converter;
};

} // namespace detail
} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_COMPARISON_ADAPTOR_HPP



/* comparison_adaptor.hpp
7RFnQ/EDmhibg4geF9dzGzQEOZCzGTySr+TJtyUqcVPlIG/IZ7SRoVueUwknJtIuIm2ffJl9lNJYBFdf3kagAT9DLE9JAWOn7cDa8fEiv6yleYU1rVBeR52rBw0TtXx2Gg7T1uv2rDR3GRj3aJXXYes+c9pDbaKXo13J+Z3QW1hBQP/VluJVn4TqWgLRWkBUVBQY/Nq9UzGsC5PVkxavl1p/HTg8c3YaYWLKNnfLgs36bZOEfK+APUpr1c4rUg78gQUI88nO6QBN+FZb7NYm9wQPbMyN0w/OBuOyc426+iIeMi0NQVmSxrL91aJGZ+LiS3Z8RkScQ9O3w27cORBbd7wU+pxZptU6pkCZeFAqZ3bxrfFavB9BOzR2aVHwPumIVg/HoPsr2YAMLjJ4jqocZzm2VCO1Agp+008pcOlWMefc753N74AAo0elln39BesqFobOUu5G1aAuvjk583z2EkDJcS3Nzkd7wa7Xyo4QGc4HRkgHfjssk8vL43k4Gn8GjRwfO9cRj7naK0gYJjCFHh/8ugqWR6PbPVLZF32ZtlvP729O2ovYewNGhcBxRwKMjfXsMgQDCQB9OUPLBU3zCwbte+Dul1faGpS6D2RQoIwVUd/204uLvAul4fp8uUxrlt0dHoOIEE97OuK6jwYFB8ovQPk3Y4NVl6fPc9dvBxxYsAinlm1Bl+sewv2MqMKLJM4FyJg/q8XP1ygFBWclM4yp0uv5opg/CMywqqV+9oT5Znkwb7Qwb3WWk1OyCp1EwSc0iyHYNu2rpt5+tE0D706JjsnEUSqVTk8IHI8hl0clsVYHCwcWnmJD4fcTKl46bjvynCLQfQdt0HVOE9hzzj/Eb7aHAobBHp3MyfSC4QdgA4UGDD1lAGMC8/sHOAkOotSLJfKFzN2VnRblyeepM1Cs+J0thS/C+fPnsVw/77MPSXmGlABdZVWTMogavU83qcEOYB6wILokAWwUmuVf0TCh4RvViG206bcazORYz4EPojF8es4q4XNP1L8nH8z/0jNsQiHE7SkAgkg77O8g1IBIEPICIOQPMxiNROGrOS4PTsjoxMXlJZX9m1B21QP9/7WzI+z758ZOcV2nApHYA6PnKKkFqFUTxV64dRW+KOAa1UAtOCTHuQkIotgh0kivbBiT6k2xrFrfOhzfwjBB3sGkhPJiPswm1Y+ho8BA+0i98vSnnimsglH8rA2wjJ8Fh26YTEwf41DxArgR04FTJ2HmWTFBV1992zoCrANcJ7B8cPamSettCZLfnlQDn8bHclhqoVyx8+hj9iHhrnYVsbN2u84gNptNWmL26LIW3SYXIuErIz9j5CCD/f5g1O3BiFm+wb52nvjM6WMONCIrcens/HOhHPXU33Ne5po/L5tedxqkw1RPyP+E027T1pfqIASI1AqRMUEh28Lb3XvNfTx6z+OHCAzC0NcHqPqCewUBfQ5l6L0UFK1aAEJEvtILaNB2qS7+yYpANxHZPqkWqYibt5vFhcmk/S9E+t9ns7zF7qVjDn9VYwT0CS+HpzLZCY6KYAYUivpZrkBg2GHfC7zLm+A/S2Ud4pSgCTV52JMuvsgB+/gsbrguwOSy2ZxNBC1lrYT5p0sq/Abt77zVqHmdXydCx4HeI7OjuzSYtSg04YgN/EdTebWDBTxUfYK+nhFzyEmPjn1AGFCFJqiJu7t8iC0jnGFQ1xvtiVJho6T4oJC/gx+JT3ZtX6s5gBQQ7EiIZkSCf5uuv4JMBQNEPDQfAm3YbZtx0TehoTNAQwJAcPv1XSqgjaIH3EzQZxSGVwYuzXaxYzvsnYe3NeADLmWREvnKOcK0EjLpV5nhNw/xAQbY4foPp3MWieRyV6GicXXhAcGEROqYIS5EbMJFJThmjU/1xE2m9ylM92/HQqbn72KT8XeafqA8xKxAIL+S3l1ogWf/asITCZPyG0oGgX4BcUXAurFSz3dQTVHL1HnmXLXAL75+CPBwSIDwK0Bw9YjBTjAMnRxlQAV/Ss+pa58fHIkd2MaeQYD3oKFC/2yhRV8QjK+bh3rcqMCdbz+rD+O58wHXFvKu5v4n4KJobGD2VzZsI/gwPpSFoFtSUtJ0zNFSEFTaQbojCpKKauAI08sGEBXT85jC461LsclphNg9HX5PYexsSvBrVB5IfGqX+HuK+L4ChaDNDB19IsIHLQEBM7swjxhiY20DAX5Cll7aGj1oeIpio7zscBBJjePNhoZanzmfOYlElUT3Za9EJQoGc3JCVFyGTA6hYMeDo7QS24BvjF3s+z7WnPnW9vkLMHHUpvC6MX27RDEAKlbm4fExmQEYb2agW+tEOxSQYLWgXdkyvrqHSVGhKapEM9bhwadeBs93aOkcbw1TLl4lG4H3W/HviGfgZ+9+mEKVzfq5WiGElb9KNIomIuSbqCABfEZ22LplkqwabgS3k0TeU3EfLMy4ZBjCHZKUP3+LBQrSEliQVYQywPj761OFg97n8GZv4BEWpmXp5p23dTi/ejyRL8e5p2P0erH6uttbqEUC/LPWCNhcXnrrNAR8NfbQtufsA4EeiNCGlpo6s9NwKEJIKAT2TElbOwuMFCbKWj4gSF8hRrBWvm3X7nJ/zZ+PRPefXQRgfw2q4i7C4/43/6Ea6FSYQT449x/+ijHx2E1jnXhXMPD7wry8sTclO0TECqAw7AglgHgVxhUc4KDcbIdG/Zx+YewJr61Zrn4+T0BXJEXvcbD6r11MG6AdOzayBB0NzUSQlFoclQI0LCB4SAX4PlNHB+018IO6NT4Xa+EBbfZtS6UkoJ8VKkS8t3fjoMkrNtB50ovwg83P9NURR2xYOAua6m+zUpyeWquzR1yMv33pHePl02P2m3crgdCFJDB7G8KgL1YYVe5eLXQup8vFKqy1hgQRPyoJCxpFpd26RXtGT6yzEUP0Qbk2w2x1Rq98lSGqzBHm5q96k4kUh03pwt4XxC+r2tB/cwfpviWPI2BKXMnGHh4egzu5iriDtJSD1Zxe35D8r2h+/WvVE67X2zyAdmiEdxIMdHTT3fhclhiF1ZfDXxWf+gad0PCsOuzrcuDFfvq6S1cBAS7LYH0CiZo/6Z9DhHSZKWaPguY8ZY834B07TCnW41HmREnSGZuQri8rjDUw5ODgFgGEogcc8wuIMC3gPAQ6X4rIAQ+L2VTaQ0BAQE9agKxVO1ifyFLC0AQAANn6rxdAXnuqvj3jyHniel0uqF0ekYEeGrSnPEtQBiw4Y/NPh/f7U8TztieCJzS1yWxQra8/3wjWvUKPy3J+JjTuOec1C397ue56Ng12QukiBTC3h/dttRb/S+oBW7JEmvPvCKBjhRil2pR5DJiYcioPSrHbwOBowd1ZpybT8T8sK9VfdQyf+vrYPgw3mfzyC2BgQHuWNjBADFTPV1taxfZ937SnaJhG3ASRTFlh9k+Yfq3JCBruSN0YBr4rIoABVsKnCTsrPTTWZvzBe0qrrEi5qYmJcyE7Cn3ICPO+gl4ixjeB/W+Xe/TobPt2yR4L8DNzAaC58gx23X1pNzRbZAPssGsAfx3Um3ulSedZyQbKRTa4uBlOBxc1Flw3/FnNwIMdG+S3x+kZxz+ucM+QMkaxHMAtNSsfXw9CbwLwr3Dyn/1hicxRgYbJciZa7HzIrsMHhXkcC8zf9bjBavFsdYRo+eubdhgD4ENcrVVxTMxygZtnHRKP2N8dvFNFysDAJc74GKSsWVo3rl0KhPw3Cm/GTQAgFof/DMEDXxsFvDcTwkvA9FxUpdWiKs/MB5BA5pAiCDOgPKQjFHeH0fUXVPLfy2i0Emp3GS6/alQ6Yw/fUrliv3yrcskQyAqw+YlGgA2309n8DBAI+EU/JWWDrrIhA+egT+b+qlDdaM61g5IdpcsuwG0TN6QRRFaZ756/CfRpRRp21x90FjO7IjE8bjc7praJPIFAxVoLJiwzmH2kajD2vZaf1yy9MkBAph2MEgP2wVUg/4nQLk5od9SBdhiFtdWsAru3zPlgxHYCEvo0GjDUrivf2mT0M46FDvkUHbx6TgExOiG5X5pULyVkmoT67+OnCNOCgSwP4DbYlnb9EBpGcnKIRKMxKIBsAAx8E7MsWGiGk6MKy66feVAksRV2XYFO5FCHR6XSItIo5/nh4IgZOUfOapgbu0Ft19DteRP4Ij89PzAVaRYK5L+am8KUy3WANNRvmD5gYPpBWhqNWbh2v+NhoV0/hoPaLk5/I5zHgyKA/5BtwCCIUmL3mbirDdqKAHNPvCjPCMwuogwoyFYA6m/QB9WiDqxj0UO+4xkw0KMDY5dzMHFyTQTQFiS+UvRgjToBwASFVxacIwekD+yktteJZ0E63OqQr8AHgZAvUBce7r6QcA/Isay0IO7FfpGHtlM2OGQz63OrJIyaPuLhyU2h7gkCyE0UsH5C3vuAbdzbgRYAVCnbQX/PGpkc3onhCylMr5uH3Wb6sLBsSdyRfcuj4h/N555keZjKiiG96mBcV04X6yyIFf90w2OvwzN6Wwt4QYX/N4ReApMsW8MLBODnIyEiK1wtqB8QLi8rBgeNDf3zE5yEuLDiz3P0P5DgP99V6tU5Pw8oO3ENRwAABuU/QICMLMz/tw25AV14Q+hrLyU/YUV7pHpes6UZ9q6WgEZRkvELQgdZIwt6bMgQj5G9X5sm1mZOJcS1r8WJJsiwASmOlsQJtsiwNp/pb3LZ1FfqihJPfey4bnPJuYraijLXk8LsU2/9bkl1nHHd6LjuFmdKTzr4xwER40iYBQK2Nz2iE+u4ywEx6i+YCvdzFNVYTY15bbufHKFe2TLOrjdZlRZuF+bJhQn/SuQXC4wBw0OQYSXgNAd5KS/8LIq+0rHbuXi/DNQDmXzMexfQC7JR73S7xd/55hiLBzExMdEQAo9OZF20n6nEVW8wnXKDfJaYJSfcDc+7Fy+cM0esycsjjPtyIgT1r8dZTYDBBM1jgDbaQX0NJ8/Je4ax2wBtB3IifgghlUrBLRqxT+aDiAEh8c2BEg15RbwbCmuHfIjq7+8fkw4JQJApLk9JSkIVQEtKSUEXIlI3AOJHKfYPkPEVXegF+SYxqlPPsnjmfxQcOrBfys7O3nIK8EVI+A1moaRkUQGYpkvLDdGFCR1hnLfG4ug4IBr1PwCMCcB/IO0vIU475mEIDf/+gxwDjaoO6Ysq5MzIGpTTHhaW5xdiMVHf0aEVDZsow4hAcaxycaImHXp35wBiwg+ETLKxtbW0hBZ6dXV6egoeV0IcexYuvO8cBdFrZ9mM/mZw+s7Yv7jw2fpv5mewsxkU5z4Ke/Cg+Dx1UH6aIn1sQsig8fHx+YiICOQoeFJcVEIvSn2/vJJVorAMG86pOG9Rs5TA8WIWrvY0YvSTZYqadqPaMyB1wz9//uhcXl7qAKY4SG6xk16hUyD8iNTxQ7shCifuM/puCY74B7Gjmvto5mf4vj/UYKkJfD9ulQiVU4VW0YXoDYcgoWMQVVRUipeWlk4bJ6T2MEgJteVbTQ8oy61MPUxL06m2rtqevkkB2iYuqSWZcIROpSXZ2CaXYOKcWpqanFpaWlyM/b2U/gUUYSv9H5iTz9nOyxo1brV5zPZr6zMf7AiIfgXQ/Y5wD6SzZu8BqH0slJyWi2WSgELcY2TIaOCApADjJFO1xAFT9gb77CsDqsSOYJP0/qQ2HBPMjCkb01Rsc1iaIkyddkBKzPDwsMvktIcCO6rE+SPF6dZsD5B6a+RThNIIUEK+BFCUCGKMK79b62wOP1G/uAKkvLJdEeBAkpEVyk8fcAtGDvC3MlNtzHSYOhbNGNuCS5yarA+hXMk2bcj8nd1OyMiM/qGDqcKJjY293gq1u2KL8a8H/jgXhGIm6OjTwZkLPq4xBYQh5a23FREYxf+34s/EwfWVDWQUbPjtyulJxEAjGg1h25L1GUxM56XXAfuzJMs0eKEIBDZWNjZXoHy94CrPfR9GAJPo4m+HkhGg/RZ8lwK6YLtOtDdgaKhmvcKD4ei/wAwVRKgKOLSwmIjB+g95ayyJhWtJVmwt8eIaZkqmZM6sfQIdIMh94EF28Qh5jYsrKxtlAZbkan5qLcAU1DRbqcR4Dn40Ou1OwvdgxMM4s6e2Abyp0TNgzy+3B1YchnnxMJCQIBDB2S7zTn+Si96pBeIxlOmK1xr9g1wCglzKQP3mvXZ7/VXN3h4R3e6sAEczsDcOSuq6prR3SPTzYlT8qjW63nDYj9Hm+jpugUjBKGTSZX1OFchwGSgMUY41qPLq3vOUAvxHihnlULCKIOG2cvoCO9B5jTd7JK8gnxScqVzTvO8XO6WlfAmXQvBxL+d0eAqPNa1WR8gs+6FzZScCYjfceeb7g+Gs6m5qBUDEuETaU8PFW/xxsmLKRyH5DKAgyVJwJEUWnOGPEufd3u8ZdUiiefI8kD7bmz5r9c4D8tptrWejbCvgwKPUxwJEfoxQ0W+x5r0rgaIMLTRZ3O4OeM0Wvw1v3EQBsOtwqCxKSljFa6BBx/nyWx2uEnKOSnFOK8NwCVGecstTdebzxpS4rOuVipxmObubkvoEkiDuAvhxCWqmbB0ISZCcOZZR4yoAyY0cHk/sOplJ1u358Q61Lf9aPSB5eAST36Gcl2qg/LOY336irwAn1hLgeIlEsqUoLOYSdDjUukcwnN94qNbWagqQMSkRl5tE2Ti6SVc8HSTNf/4OQoa9eZxtjga2/OIOWnJNUigCFZGYyYb464E7gnlBY9/YrCpZIp2YoNFQbPdgDiZ7tumu6NIfjlxVIRpWWBOldqafz9UrmKec7TQvgaY+yn691dGCRdoK7oORd/DGyO8wMUcfn7o/Z91Qy4R/i32oLlvX+7HQm3c+xy8lQGw0ElM16FQB78LzZpA3Cgpr9cAwfHiw7NgqsL5cHd88QpDY7BwrtXIso7i6VCwoR2iHJa4JeTbdTTJJu6ILGinkCsINiuQvxEyOE4zpPC6bRY9mRpNQ4ahHigbzyA/witFOZ0hoXyeQCTjD4Czm4HfAnFHk7D0gefkmHE0FSooW041YRKWzML2EqKm1SGS9Y4QY/fv9iaIBkzZ2v0da843AAtvyp22aIovX+w2Te4QCBocREpEKJGhO2gLhcHtj/VfVXx6GxkpNoi1MynGij6MwcUlEDrxv/jE8FV9g8pBJLoENgQ7GAmU63V8qZtnUSxjaZbu/52Gh4KkwSFg6+PcKcmYUfkoVe0gYd147EnkbXtspgm77oteOW0++L5OVjJZXNIi4UPQem1/Y+1KzGPxirYCRZtpSpXZmEQZ5FFAxFMxsTDTs64+uRu5GSc4cbXI0ALDebNmkkbJ4CqpUfaU6cnIYFBCTiGd97YzNFR2t+XmSOMIwfGUx9HoHyfwabbz6v4whOFtTFzi8uBP4WbZZXekZyJT1ieq49aMa3gJKDTp+gTRQ0UTRK7dXwr3A4ZmcnqfY0MooMcFQbEL6v6yQotErwjDQvDAlsSdXixdrDSMGGIIzEmujAvppsmadrObtnmRcK3BwPZ9NuN33CAmrnQoVQCGMvAxMQwItVOEZ0BLKSZL1BdIWBRWCCb/9CI0y0rk5vm1tUgOa4c0BkO15wS4xBDn7CzABrchOuObXe2Rnref0DpgeECUYrBN0CXO2rdD6bRdhbIBRRyWbkaD4IkAmaaF7kNlG8x+Iuo0hZlvyfFq+2Dnj4CEsmqkWmfupExPmIY/DSvZNSNNOLE4mj4dTB+nyl3+WPQoDYKEb5m1MZP5NQgc6vilvettU2bHcJKzmrsDEB+tAfqd4OsThc0uSFmTiMcURg4zjLM2SjXUi0NiaJOt+rA3EvapsESxiyeizMe2cgCNLLM9LriJcq7Q+ChRVxQW2y/0kmN6zrTbHEyJu68amsUvAWA88GX1kYusXtSku6lB4ROWt6AdkAOWSMcNr5FdShf5wFNZplKhKQ6pDEwzs3zrWtLWGuavPd+NvhB7yx55unXEcnGJ0f3KlAEHlgmpJj5FFwRUKChLO+qtucXQMyesXziXNj+0g4XOc4pteg/ArLlzpKcgDqsU66MZnu8LGj5lY43s5XxKRUvokqOv3vKj2Ozhk+5IAosrRU+PsxGgy2DC2qOkMVivu5u1Ml+vtrbAnd2rO7lvIAcqVMC9aN+FYwixF/3J2v/hCjuIMZjNZhmImO0yGKFPrOlh8PJzliW4CLzV4AypWcMcPTkjpVUtCBRW6LqURiZnF2wSaqe77eKK/SAeVhTC9iq2OPcLtbzVGrboWoB6GSiWjgwgfgVHe5xukmgrxrq9/UBkjmmHR7zhYcTfanalLtb2wTOjXryMxZa7G2BPz8QVEafgBMTh98tmKBu/NAR3K+rpAK9igIED7AQHHXsojkecmzyvdNJe+n4kBAb3iahKdTNtcYHl+sosO6N/jSrgaBR0Iknu82gn9MgAxJE5QSZgSvUQ+hy5pt5n3e91SRFxlA0KBTNLaCZVra4gTniNJn30yGd9avlZ8QqtFJAhE6XLJ3slMQMyKgz+74/GkgrojqBIVCITVETCJFS3ezHRVpsmKDLvkOcEXPTGDB3l0fI4FSpFrQLfH1aAPGA5QTD8PYHw5tSgv2Ug8d3/51mDU/TyNkelRKTceaqVL6pfIa3QBOGLqelh/aCRg3MDJYxP6C2X9USnN4RZpxs+yDIipgGwGMMLBcAkBChFbeDB2EeRkh4ha7YCVM7W5sU61wfuO5W55tob8+fk9RnPhWxKFvWp6mc4qwUmv86uOlPzzj38grMmnmXRSdSSGxMWFUpErjZpBzj6TC/cqb9NXHMvXvdmhxM0Ng+i29Yfsc0NjpRLxEY0fNnMQdjPrRtYfhE+eUcHsod8pToMAUNh08OEPxCgegmtvjFyPf+WJL1/sWObSrKLxr8pn0YimYjCjX7mf6su0GoRbfG/5WZjXyQrwwwkiwch89px+9ilO9GnEY3d7v8+NnbHCk4jNLlRgis77g08p3qYD7Mltgd3YbTbY1u6rWyYcbb2i7eAwhp8Z2JeTr0oqddaGvUY9xylLpfc1UQzoCmj4ycg0V6VZaHK9NpmKra6IgQl5OXxAS7IimHmKyXO97kgeyEQMdmsDTvpB2bYXUnVI4HK/iqStzBdPAOi5PKZeV8pnwAz792aQKzjmXQfrewIFzZKGJ1m/dCYAqGbCe0LzlLMmsdw0cjpOORcv8z+3+N4=
*/