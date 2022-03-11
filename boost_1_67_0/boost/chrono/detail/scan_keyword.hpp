//  scan_keyword.hpp  --------------------------------------------------------------//
//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//  Adaptation to Boost of the libcxx

//  Copyright 2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_CHRONO_DETAIL_SCAN_KEYWORD_HPP
#define BOOST_CHRONO_DETAIL_SCAN_KEYWORD_HPP

#include <boost/chrono/config.hpp>

#include <boost/move/unique_ptr.hpp>
#include <ios>
#include <exception>
#include <stdlib.h>
#include <boost/throw_exception.hpp>

namespace boost {
    using movelib::unique_ptr;

namespace chrono {
namespace chrono_detail {

inline void free_aux(void* ptr) { free(ptr); }

// scan_keyword
// Scans [b, e) until a match is found in the basic_strings range
//  [kb, ke) or until it can be shown that there is no match in [kb, ke).
//  b will be incremented (visibly), consuming CharT until a match is found
//  or proved to not exist.  A keyword may be "", in which will match anything.
//  If one keyword is a prefix of another, and the next CharT in the input
//  might match another keyword, the algorithm will attempt to find the longest
//  matching keyword.  If the longer matching keyword ends up not matching, then
//  no keyword match is found.  If no keyword match is found, ke is returned
//  and failbit is set in err.
//  Else an iterator pointing to the matching keyword is found.  If more than
//  one keyword matches, an iterator to the first matching keyword is returned.
//  If on exit b == e, eofbit is set in err.
//  Examples:
//  Keywords:  "a", "abb"
//  If the input is "a", the first keyword matches and eofbit is set.
//  If the input is "abc", no match is found and "ab" are consumed.

template <class InputIterator, class ForwardIterator>
ForwardIterator
scan_keyword(InputIterator& b, InputIterator e,
               ForwardIterator kb, ForwardIterator ke,
               std::ios_base::iostate& err
               )
{
    typedef typename std::iterator_traits<InputIterator>::value_type CharT;
    size_t nkw = std::distance(kb, ke);
    const unsigned char doesnt_match = '\0';
    const unsigned char might_match = '\1';
    const unsigned char does_match = '\2';
    unsigned char statbuf[100];
    unsigned char* status = statbuf;
    //  Change free by free_aux to avoid
    // Error: Could not find a match for boost::interprocess::unique_ptr<unsigned char, void(*)(void*)>::unique_ptr(int, extern "C" void(void*))
    unique_ptr<unsigned char, void(*)(void*)> stat_hold(0, free_aux);
    if (nkw > sizeof(statbuf))
    {
        status = (unsigned char*)malloc(nkw);
        if (status == 0)
          throw_exception(std::bad_alloc());
        stat_hold.reset(status);
    }
    size_t n_might_match = nkw;  // At this point, any keyword might match
    size_t n_does_match = 0;       // but none of them definitely do
    // Initialize all statuses to might_match, except for "" keywords are does_match
    unsigned char* st = status;
    for (ForwardIterator ky = kb; ky != ke; ++ky, ++st)
    {
        if (!ky->empty())
            *st = might_match;
        else
        {
            *st = does_match;
            --n_might_match;
            ++n_does_match;
        }
    }
    // While there might be a match, test keywords against the next CharT
    for (size_t indx = 0; b != e && n_might_match > 0; ++indx)
    {
        // Peek at the next CharT but don't consume it
        CharT c = *b;
        bool consume = false;
        // For each keyword which might match, see if the indx character is c
        // If a match if found, consume c
        // If a match is found, and that is the last character in the keyword,
        //    then that keyword matches.
        // If the keyword doesn't match this character, then change the keyword
        //    to doesn't match
        st = status;
        for (ForwardIterator ky = kb; ky != ke; ++ky, ++st)
        {
            if (*st == might_match)
            {
                CharT kc = (*ky)[indx];
                if (c == kc)
                {
                    consume = true;
                    if (ky->size() == indx+1)
                    {
                        *st = does_match;
                        --n_might_match;
                        ++n_does_match;
                    }
                }
                else
                {
                    *st = doesnt_match;
                    --n_might_match;
                }
            }
        }
        // consume if we matched a character
        if (consume)
        {
            ++b;
            // If we consumed a character and there might be a matched keyword that
            //   was marked matched on a previous iteration, then such keywords
            //   which are now marked as not matching.
            if (n_might_match + n_does_match > 1)
            {
                st = status;
                for (ForwardIterator ky = kb; ky != ke; ++ky, ++st)
                {
                    if (*st == does_match && ky->size() != indx+1)
                    {
                        *st = doesnt_match;
                        --n_does_match;
                    }
                }
            }
        }
    }
    // We've exited the loop because we hit eof and/or we have no more "might matches".
    if (b == e)
        err |= std::ios_base::eofbit;
    // Return the first matching result
    for (st = status; kb != ke; ++kb, ++st)
        if (*st == does_match)
            break;
    if (kb == ke)
        err |= std::ios_base::failbit;
    return kb;
}
}
}
}
#endif // BOOST_CHRONO_DETAIL_SCAN_KEYWORD_HPP

/* scan_keyword.hpp
BA+wM2jbQgS4pa1v5b8ksrK/K/YAAkV8Y+up+iWZ9QC8rlraxhTiWODO2Fh+cZKp13Sg9V64pSjI/xZjfVpsuha3B+2srEzdU8jFzypKO/BUm8F2M0ZETnhIkP+HoUvxMD8iThQ47HukTE0RBAF+Ide3W0/C+YclPki5jGZmaKExQHQskEaBke6xiTLRWvI4iR3bS/w0ZZX/ViIfIJkKXC/L91QW8PQDkCp5GjK5G7I+oOQvda4Mf7OLiP98GAMGBQCBgH/5KOLZF+gKAgYODvI76AqGhEzLS/8AXcNQCAjp3NOkNMt+99pkUPQABCz70+u/gQfkOmEqupm+XmEhL4DG0AA12yiURd1mc4C49aI0qaHDQUY2ybHjeuyH9cQX5FrDJx5YzVj/2EqnrMhCro5CJdJ4u3EAk62EXnCwoH+CbhlR+HmvtlYqJ8eAFjU+8tuX2YJsIKM/T0B25MeB1rnwwE0WbQoSy7wn7jsGmDaZ8dGSZ/NSq4eCWO84eOtWa2r6Wg2aGqLHT/v544+y1uXqGumSPPV5ub5e4gtlssjn83LTCif9j+oaef5Uxvp6bKCi8Q+bcJY3Qli2D8Gs0e0zdXcZwezTmnJlfRp7KvfD3di7ZRQKa6XnWYQz7NVQDVAJuQSRIfr7UyS7JKap/lKcGQ2vE0rj6j2eas+A9uDDna8a2c2c0pkAa4d631gwNpo4oDO50wnzO9dhzDM1qXfQ18bJ2xWmwmwK/UkHROuYb/gxShYRefALnqnb0MrnXg9Hx/APTNxEVIj4SlJ8uatVmxo2Xke0xaa647+oxrJH2rixdlkZg8gqS0O62eHFtERNKAmPBtsjFEYQvJxP1XJuM3GhbzabXl0Jc6FcDDukHJc7EWKJS5+HP9s1UeRCDCYluxFBO2cqTIHsRoq8+3xwxZTkQtsOoy2f0qkrPbkd/sPO2Et8/Uzwda4tLtTcWL6Hw6nziBOVJI1Xeihm7E3mpVLSdKwIJqKPblNn7I10Az0UoSbN7mRtBa6hra4GkbEgdvwFqtaeKsc3E2v/zcSefDWx4i+haeXkoHsdAkYsXkv6l5fKSY+pRUQAB8pGeZQnp58S6nVZHijQGlmgVuUKDgVuzJdqTqxSGUkEpaAPNb3uLHqvNJH3juaDaCB3/c71L6tWivPiJ64oqLjxicAthks+R5IaVz8M2sDSCdmASIu/8xbebzU0mKLpwZ6CE0M9HDaDQz2c+IpirxnffkWxQRpfUWyGCPcTnwqq9exwF1oEXeUBMaJbTZz+mvj4zBWscx2nnnxx2iFd+f7v3YcA1nIm3UOsvK84thGC3OariQXqjZ3H0LIzCFoq+WtN7N8o7+dPk1hpvyWxgoL+MomVVxIJjdb8IYj1q4n9rwSx5lHIS2+70LafoZ7X7zesTTgig3PD44OaLg0yReQZcGUWqb7Ku+xGGFOe2ak/iFHclXhyy/IWscGHZUY8K/M6/Kt87fPFjnFt5y8jF1DIx8qJecRO/Qng7aMp418mw/qKGs9G9RMA7ufEVd/s8UInCCZCe24KSnZEsQKFS3hjwWMXuR8yV89LdyXHjXAR+3znEfY0pjLyJ7gIYxAbcWfay+CoNHLNcYx5dhsCGNgffTGy6x3wfbUV/D9PocUkoYAsQzj/ukLZwdJVanKudMm1vI+mmGDpr3K40b+T2LijlC80jzM8Ox++Thu6VvhKYYl1K2nTir56WL5B5wnL/YoUa0ZpWUaFN/AG8OgepYtYI1j0YBqtrJksutATX/SreIAigwuyVxPb10TW080/SGENSJdNS1LpgNiA/ARAJTrajeguf4XTq50tqp2taiFNXUcWoxK5FWPNpvNRPM6WT7l71fbwbU3I+4MlKDPcsIU2xwLx3pKFgX2NG8pX1gbTsjdXTf3cOn77RezkLa7MdT67Zd/yWD83KLWMcovjyp6yMIzjfAPWEhWqsi+sOKO+LaGoG5a0STz9D1GsWmzucTzKSf1d1iB0iTsUfeR75+vXPvznCn/ciaEcKf/QqmTx5gzqezorgsRvg5BpuFZfY1n50SW6ZGgjGbMFefrnrTe/hLCC656U8D4Es4bSMyc5wO+IfJGx39JYm0RHhE8I+z5uyxvmnbY/WYYOcFSLUe3fEfC3xPV5msx0pIPJ+6EWV+I/m5aKeDrOH/SuvxYHcptK4kD0ZYYsPDME3aIdYW4VfxMZXZAMyxxWn/ticPr4D5mrBwY+DkxsylJP6GxwVi4q25swH8wsOjuC+c2MxnzFA4ZFZ4Y/vFH6s467M0auBbvfBcycY4IM+4dnn/csZM615Bhiafj7qFbZY7VUJ66DPB+HkvDvaaxOMbm4CA3bGvMtf20aK8v/hjRW2q9prL/7hsGDi31MC4GGLyk7wqthHlFBYFGGREhCKtX25yj2/dCIRtXUiF2Ys+j/39TiAWr+ds60z0wte2d+fd65xnkx/JFhcb5zrHNeo1JBfoourqHZt00Svm2R/V/eoHl3MDPh1crLBPrO2GUYjVhbLWWj9WY3C+ibin9GsfHXQO8p9vu3RSrvGXoqOBSD8arRfWwYq5uNNiHwKu7SE+QruBVcMeVcK6UNz/V2EFYMh84fUOzdg0yV55oAkcovdi4Ez5JVuVGAE4V8q85Ya8H7KGC9Bl6YANFpYqkH5mMJ+HWaY9Xigswzm0bM7bj3ExPrSKwYM3NteoTKyrFKyV1iR0gh1QhrO9JTPc0E5ufvbpsMHdGZO8S5prhj8qNHXp305GItfd4dVWbKRoQE6wNTVRbhHiJJtfQ5qpLF2HlEN7OdO6ngHj0pK1jfAVtd78Me0FgowzqnuqaZNrh8QIE8YBkL2/r2h7UX2ISBqVe322pq/QDVh9pDrEg0xax6NByQ8AkmSjPfxLtS12dKXZ1BR0gpD49MYaqsmcDy4ZHJ2ES6lpIklz4A2ZGQc9DRiQe3OyN53xrv8PDABBakZYUbtg3z0JzFJF7tK7d7eLhazGMhI91EHy56tdMO5HigwXYzJUOq0GPN2OHhVS1svAMCK/4E4IKEpLK9OlTq6ghaETcrFuY+rwryw+xKXFAJdd0zwnzMHMTaXIf3CTCzIf+zgu0Pw1DW0mXAfkUjz9aYkU+WZUDb9VpHMmMpHVXbd2QWkzZ1296jbvx34Jboq6qV7kdRZucqEPMN1wRrnJ4r0NMbNyh7/JKnJoE9ynj3uoiJQMQX9UTPImh+3PsiXBPudnYuw7ZKo2k11tOV6eLpxz0FM3sSvIWBpp6G7YZ0TYQ8MwvT6+LNWM9t5bmE5oJ6Erzr6AuSg/zRwgjELRvbX1VUhNqnp/MCOIZb2cAkyILG+AisuLIV6nz2XpnGyckJ7zMGVBlan7f5DrzF3yDcrjbafEVTGRQxOmqPbF+QHQsZK4le+pZj1VluwBlqHTW+cjw7/Y+/Ff8/qGb/Ri84/ySQlepbIOsv2CzaQyArEiqt7Dtius9vw9P+4zhWLplfxrEe/zqONYpFezmrR6puZox8klskMXkDhZota3DiIZv15eoFS575OLVNFXTV0IgeaV3I4wnS6AyZljjVOxyiwldUgnmudA3XHCIKyUpBUvc6tqdUPTJ5MYYoRsFQ9BFzbXNRonE2aXK1ixGsnP0/TbWMUo9TUg9adKgPu2ar5iuoJq75tqR/ArxskCltYO1DdBUcNaj0nUdlHM77OBNlghq/ZZAdhY15s/6QqtqjmgwqeFhW7Cy+P1agXzn5Qowhd3NhvuwhqVW0bvG5GQzGxtj+nmh1gJhV5ahocNDdDhJZud9qQTIEgi1aSOaXMNaPnStbD1Gq5szmdtcP2atwc2pc4Q+hrN82kfi+BVpFQB/M4UNwK01TohqL+tt/xLLePsSyhvCN0g6P8HWTYE0wonBdcsK87BZ6AYMTa6kwJnOzeEpFj41NSemgMaAlKX3g+ddmsf6NgPmfZbESPXyM9qBoQQA/foyGD/r52fEYmZYXjID+34hi9Szqtafs4dVhYZv7PjAIvqbirzD1hhTEoliA0pgFyb1OniCaCQsKqq9ucgzbJ1FYXHWwOXWXY5nPYt/6DEJj43H1bYCn267jpujsMTU8SNlBGoXZ+1oW+O7mt9obihqtZe6bWqRsffBggQj86KwTCm8oXzugZ30Bsz3z6zFfCC2pY7yKrl4qPVbSPlZaMrvW+o9rrSa5pJbuuOAzJZtPABxd9nGD2Vv74KiaGnzBV8Jbyo4WyNqn37oiKATUzi+894lkfOvOqDFrw6QINsZqTZfJSpg8pe5O/Y0GUsdanAniT/QZny2IlHU9SUWg1wqk5cHR7X6i6cbRVaubgbEUH2jkbUgf3NGL3q2pA7tSRueNhxNfdi5OALRVgKu9/LWDl2htUn3Dy7I9a3LuYT5ePbuHN0Zhgg13GWqIUh3sfSvMCD0rxO9C4oXbqftt0WLpDSX8thAjSJe27bzvT9u2eaJqj/4QzApTQkgHBitRsGvzJPSpppe6VmmHOz8y+Q22N8GNI0Q7yKrA+TmCN8T7gL1dXFiEMKAuTVfLsA+wkPD0SDeJwW6vecxjU+ZWrUCArfHa3PSkYJ+CPxR/X1tLz8z4L5NYp+M9aGAFlaM93k8AIaOgoD1HR9Nf+PTRGxzZh7c27oUFEP4C/l1CpoB+5TBXHC+Z9do1P8zyaeXZ2FCtFenbqbA3PcSWKEu585wduHZmclwkRmE3aYxLiyS2y+QxhmrrLVLxC6oUsbAW0FzVPMkV0HB4k+IBWQ2BZsQyJ7FQer387cEHfAHhVXbFTUTRjfF8sHzrQLeoQxjyh37v7fOk4U5qny7UzlSQTISXmHDyGiTfzpnRkWFf6PZ2bKSrU9RklFntcV/llxPVYzkvKSSdPR+Ebbru3CNpfkXM0HqDUOBn5m/AHVISqgofXAYiipqg5gIfLO2E6CzZ6pR8xoVDnreaquQjte2D02xoxlOgn12JceozybtXPr8aZsV4mTT52pwiXznE59KQY1i3hMBYxmtvPMRG1xpPKro7FTyJxLmxTRkiFOf6xqj0AveNHU48blv6hnuMMdNBM55Vl9e7XU2KpRqi+Rz75siuAPtK13JcnxfY938n1vsvs3qjoqDCO/AgBQ5cn08fEWW8o8oQ0S3cFh/hgnRqFTdQ5uknaHsbyoVWbsjbp0lme2oIbEWaqnBSAUa28q7TE+zQHkT48LTig5a4D9VyTb/wIrddFNz+Zc1gjUwLhecL+FMfPpK2j8iiquaIFkU0p+yxZnQAX2FexhmI95eDA9UE9eF56tVvhas9aEAOx+xbNvINwts5vYd6a+Bb5wmKSqiRM9y2Rzqp7FUaBt00w8SMeZ16bzTIBGfPJzhOuODmR7qYU9ypnWau7GBJ+mdczHEaJ6Ey3+1ExWoM3/pXDg0vLsUrbDvJy2WcJCTnCVnuBOTGPKMnvp7wQHtVfdjI1epnBhChwDpJfeWkHSwIwBKYnE9wg+Aqh4NbAR5h97XhIjI7ZprUCIyNlsTieMYZvax/yKXVF8Zkp0g6pysvoxzOec9T6+Adml8XOksE11zTEl/lSR5eqy07b3e45wSTl4+L0cS9A2bTrqicRIjCdRoi9lH044xdt3UjoH9n+11DnrBIWkMETtY1bnBNB3o3a9sCyyoZh871qklUK53LYvzkMPAnO8+7GYi+Z6yJc+Y2doFrlV7JZ9q8zU9PKN5/9OC8yUAlDtg9WUCHTlwwssQHIy9Qq1iyxRfJCAlEOEQIws8X+FvYYHqG/zkbzEorwMJIx8rPy8rMx8BI87lhoWcSYGF5ziTI8nmAkQuPg5aGj5ZGkOE5DSOrgCATMyMtnyCtAC8vHwsDP/9zel7B/6YUVikAEAQIAAh6HACEkAMAQq4DAGFAA4BwyQFABLIAIOJSABDpCACIXA0ARIHwL1JY6f7PBv/7NpiO4V/ZYDn2cCxmWM53c7xlIOiubnVIPv5ObmJYgbsWy+QL83hQTA42cgX5a80kR852q9whrjiPF/Bctye7h7pLWj69NWu5S0pZZM8o5XO5hKfrUrl7GTnG40m6rVkqB7rr6EUDXkifu+SIm9/BcReWg8hquPGkzNbDJ/2qMuPtmiTruYHgI171HHePk4Xn2E6LHCC5jfJtUs2YL4zarW+a09YlXKgDunyjJtdmBb0jCqyv/UfWns9Pgya+Zz94JJTb2MBHm+tkSwzB2udfaMQVuZioi7aA49MQ3tbL1Gsrp9JvU/34na1xspxPWoqNksN0QbU+v46e3cWeA8HBUxDx1SQxOYhFqoMnSs0NfJ5h5/kUrDIQjeNOz6NXpG27Hp2jmNkeeX+8/qhPn0HF5DlzkWSErVNRXmFwbjNvm2zr5fD5gM3JqnpCr3ViZQshrG2b0wDpW94wd8c1xfGxfzNpILX6kmsBN4Tbxf6WUQCQA3mrQPeGUNb4+iX6G0yfcHNhxmXkObFX5it9EypPy2S1ZjXp1jh5t0FFFsmHpqGsvBuomM4JQNBmJKs7B9c5D0K6U+TdN9XwcPT4aLITZPGq2+v4NkSdE6yyJcHqacBqs4slRaPNdkxoqyADUGIOPIuAieXVhlUEDD+QBgR9dGb+/v84ul968SpEgapZpYCVR/phbPGNpkXsbUN4jX+gyqeUW0qMH3BHjsMoRU54qii1nmRM4kv/RQYHeWLKSXpB1gjxl8Utt7zIHLdd1pRBlB6U6OHRdTRellhIFo4MIaIZixtz10KaNo6svLEWkYqSWHwcCTNKdIbYKpgkjvJU+MV5cX2T/OU89JZcLXpOadEbWX5jS1k8qWuSbb5quWBt4zIrMaHAunI8jD58aGjhvKg1+Tl21io9JebOXXex/tZwAaSMMFgcZuOkQfBW0TJbw3Lx11eSQ9clyO20fnVOCOe81jVktNQJfHm6ZftemSKLHSxkorU02f60IRHdcqJJx+7Mp6ySMEzR406M4dbJrCXguevr+1EIOkVr3kVOfAI9ajbrWFlOJayiSqRZzc7jftPlmT2xNacuqkSw9WwdeYqlmm1XmrSqb/nSo8x1Ndq74qV1/WRDGk29n2+9480p5LnsreB0DsL5NIQZVZkXKVjEwLGx/dI6Q5EtwZI1SPO+zP6eMT6j2PKYRDQzC4Yko4NC0efsjTkrml2w3ZZd+F6uIzRrFDjytRPvq8KhZ/R2xagKUtscwheqtPQJc9SYDpysltU15x8gyU0k07GNBttYHLJIsuQhnKnH0s/ZduQgrCnsk9EUZakarTxIG8gnsSLKVrTL6nuOISejnr1kb5BpHSn1pEoPtrdu3u9HpNhCE2472CbpPt+yWu6uWXmUh2F8WmdcjyLa/srMcqfL4j25KIs6QvUxL9u14x7ysKRCYj1DtrsNgSGDkcO+87xzkjFkIal8cEjTawpcbj0HvcxVtZeF88zZebWTlgd8rALNlzEYYIe9Mba6e2lDECnyJbBLHPjHitdQYi+bTHESDkaK7tGiQRw5X5s99TmAJwoZxFofeHxWOZhwOcdhfmlYhnt0kTQQXG3X7jFpWLGSyrovd6SGyp5w0TjZVFXVVT2x+gk35BNQZ8eM8/8x33+b+dKx/H2Z7z+FgHy7WDvZt/MTwOAgQD+lWiLR8j6co3iIiyOgZzj6xUmK5e8Sk+S75kXY1zHJEn7+riwEcL/+2yDfXK8x6jYDYM2F7ovwlUyFoDgKraFLAKsPArCqB5o4wi5R4IBYaBlN6UEpHGJGYKq1s4h2u83FEXQLwhi61wDFVDs3PxYIDkQdBzEFeWZ840QUgP2EKh98Dlxt+vxSTLdC8YVscowsi2Ym1D8XUULZ20lAavO8SOQhYuNswE2NHiSyOAn5VmCO9qCi3NddjsZ1N0zcdCH3Zcmz1C4DIf0ZnwCFetV9KRVaJ5R3hNu4JcU0DAvVHHc6KZnO/GdnXeAJ590phRWnIbkuzbWtoy5TJ2eh+bgjMxls2lvHnwDlKPzXyjJ6L5O41M/5cl1fGAZuReT03Q/6zzqMN7XSp1fPV5m9gd0sqilSngOhoqKiq7jZukoZ6x06yFl3labgbk6Ju3tpQk5ZSRcNl9q6kmxOW5lb/qFXgckTJNi+o2skvY+f7PUMLDzrxmO2iZLDyvQbTAjXmj+s3xXiRHfZUKqExj05aF1WYPQcmRrsDAhHIsS+xHoBXuqgjD5VZsGnrdUC4jcSkE5+AyseqYooP6Vplb7p39z+WLsnblaZnZAQTIdLUPe7/Q2L+25/V3VlDUjzxl/fuMGDs4sWEZ2xFeK+AWrtNpDNTM6R9dwHsDzZw1BppMpv79oZWuyKeQZjWHpUf3JJm9XXNlPIYdp4DxuVu4/T/dHHlAZiRHTMFkFrv73mCcgWsSG7T9mFxmwg0Gn8gG7Zt1gLRKS/kv2y0v/vYb+fn9Og/8iF/JKYBvYz+6VF+qJ+H3JrNd3DyugYpKSPfuV+x90WpEeqXjOPnRYpwP2J+30wv/r6H/bSCieMGLo8breCwK5GMWBO8t5fhhZorm4irOcQLvMVBUSkcscnhvhBV1OLu90bEfBldUQfuply/qoymJdDK8e7qmI4oICZfuQ0E28b5bXry2UiBjStQOkGs/nEhMdGDgYP+BocUwI7yuM9oNnde1y1Ozd/n1NA3nyb4rHHMF3x6qPft+Tml0+egZKovENhuYVF80Cifu2f6AIO8w4qhkZA5xPA4ln1C9eyql9VTEtHCQHB7VjVNWwm7SvMaNjerCamVrM+XabU7LAWM3ObsnCgbi4BiZwtMyj8vHi46RsIZudeEh+EITbr2mfvCgi1/T/yMGobhynnghcGhVNYAya0jMuxxqZ+bkZc2Z5ZXmbeW6ltHIncbjYNLefgA63CZrl3KDgbWjzC4elVwBLwmfht0MAc24kOWc2bt2VWVOX/ASqjamx3TwCAQ0vtvQVYXEmb/t0EC+7u7ta4OwS34BLc3T24S3AP7hKcEBIS3AnuTnAL7uSDJJPJzDsz7+7+99uZva6l6VNP3XVOdbVQnK76nbvEn8EGYmS/sDkbSUKabCMS3TTEua0twOoycTYmraqe0xxSgl2taWJGVpu2ptukCrKbnk8JpbVsQD9BE+fhGBe7oizhXO4sYR8WVfgIz6rQHEZt3+CSLO1Z//l9obBSQtPbVoO1hsBbLuz0BxqYgO4tw9bQuLZUgpHu4zEtnZJtrVIagFjOyqmq4po=
*/