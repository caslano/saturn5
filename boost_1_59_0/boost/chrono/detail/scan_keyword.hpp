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
8H0G/nUl6myTNjnqdyqDfZuoIHfPOEktCLm0fVKevEy8pIGy2JSYFUNg4ITf1IeE8Lgt6wNgoDYIImRXSEjY0lCslV/ExxjCeGRs95oq9mtqJStr5ka7pvGX+wF7A8JAdESdWmhTnZ1Gj4djy5K9QrJG/a72qRunotT7h982+h0CxIKy16D03L5z9EKOdLRtTHI1CwqC3Xl2Oz35mjYFGWJBQQGkqEneEByLqpmfVitpEUcyU/2xgkHV0X8m8kJewyGtlB0SjC1hBnaFA+sgQu4AQW6ykHWfYY8s3lTkm9dx1pV45pYGv2AwYcGbQ7FilgNF/NzZK2+lEiFgNs7vpKTAspjSbD1znWrO+C9EEv2Zxlpc8+s6Y7QGIQK1wPRBygY0tblNu8IN8HrZvGaSZ6b0t9aN2s8Ca5vfIiGvr73za/94Xv4ozdRMHBGOS9D58p4b/AT82fLbh4cdaHM4cByNIdjAwxo5CShYFwsOWmvFRL9G2+4YvtR/SljT7xgP6l03NXs7yCMztYqFDeybhw4ZksmCCM4iJgcGgxoCFwxEACHkf3KZSAHMal3FMZBaQd1qi0junph765CCu9AicPb4g5YI4C9IZsE7z4qGuk20v70akZ1gC7eDQM9XjBV41g7lcy0c5fkRKE0fjm27GphjTip7MpRhofLzRHHIPlBxjieqjT0zVLEP2p4aildKlv36/AOtEMfuNt4eskHF6Pb+PGB+ogpNQgF6urq6mmhUSg7/Xqww1XAoaaIjP7HXGn/eHs/ImZxZOu1Wc8pNlczM2suFmoLQ4/gFm0JDEDaQXiFH9FQRD7C2Qwd+yHSBXwnQ+yUzXy8VcQWAB+sZwYAMKmFfSviLnc7aEMJnINpEQHbVLfohlbwR16W/iFhPNzXKPtOoRAtSvbYEYwb6kAIXswJCgKfZFSLaB9reEw2Eu4sk11+VOZ1fSLZ65UELejJXJiJ810m3t1s/AtvM7heDkaL9OdKREi9UYcfG4skaKeWz0mIjiW3QlqjBg67QS6TVCk/vLv5ecqhd7KBoVhiGLN18YvYB0Gf6654Bd+Dht/ZmhmI+BaAleBkF+ZL3u3m3Rkpc2OZBocDV6EVCReb598PBx2rwAhC0hmIkPNsG+Sx6A+McIOEspdnyuLCRz6/+3Y5/9oZshjzvzQHzfXls6MIOtbETstp0em1csYn4w1K8RCikVSZgnmjlwFwTcvtXhDPfdyAIpns2bgYEXW6SUaTAr2ymaqNCafPXks33uKrdy5iq70c8jN3H4qJ3CNOzozV4gMjJINXCkNICcBqEMkNBRMSadgLGPK89CDECMkphVtZSyI2eHLVmGzziLe2xMPSX6+McZRBWEotErHio6H6ncRM8DCi48F4eTLEBUJYYHfEF4TJ/wOvgfVZu5ueXm6gVH2j1nWbA5UZXOVQceQWiTeIv88ROQESTHCwcXCC2/4wRGeEdi62IUJkadCgPuxw66lMil3GktOV369Kiz5e+yvsRh0qrUWe5qFdIRonrA5arvhCY12TInKl/EMmlMukbKJo/N78BFxT69gvxbX+/ZMZun/BIrgaxUBGBR9LLl163Nr12Aww6dHCggH8eGfK5+Q+UBAJeV9XuQKSVXYo2nhLxTVrrTjAtI42GUWubDiELy+jHy8uhA56t5aEIjXgZRvdbWQAzHkC2qA4Jl42azefjZVuzACwqKKiuTELJpqAOuPMMTqHHjSPph3vrYc4Y/xsDNL6qTRB5yJmPo0ZGSzrcQgHAtqMpiAkP2s8Fmm+PDO0CKAg5RgfAeCF/ghnwuR7de9iNHG9tX/D7NeVL8DdaYQb5QruNjoqzxgp+vehpIoIE+1HTw4a/bf617xs4cH5GhQumOoXpLysrg37wwnfXx29k6at4fBeEYKMzFRTsFZ0sd3c59GVvdojLyspyX5M4UF4mNseWZLWSIXZ8zp/51UyRu/rbwBUiXw5T6MUMEIBqO0rtfewwSpAaKanOUiatmll2Jq4ILValriS1GMuv7qYbCxUcICyXvy4iR7OE7S1mPBiC8N5iu1Vh4O3PVuykvmm/s1cTSSikXOXglwCnuLrBjhawk7qGgA0k/v14OtcOBoU46bjxr9PIN/8g1UxTcAOT8DdYw3ElMNztsJJgrlIEwss5AIxw3u9orRke+gQ2oCEny99np+O4RoimiyfAAvQKk84LDT3f2WnRMMDz0AEhuSB+fwAGbAsDh7BRuOy0ZmNxJGvIQX6VaujoAwUxQkNOnps1kLKk//i4hH5Oh37+YKHdtafx+ocqdzd9AOyUAhkoMOTawkoIgl0evWhx1Dz3t9r26UBbLiaolCWjarSmyPqXC5bQJprvr2UwDaFTM9AANGwFQ0NeCCOaNWz7SdWFyLgyFalTNPAnI39DH0Zq27QNHsvwYP9RJWgdffZgUOFc4BCPAGaDw8EImHaLdfl8V9yzbpF2OMcIK4ELYfVUK1Tc8rIm3fz32cdwKSAkkviSVTXu7tSf6ID6pzsSRWNZGbWYEDq2SL/L23kb0eDjATem5MNywXCNlXdDDxzY3zkXLHDOLHp0YHbFXA0XdLTS8B/Urq4JwLCX/YwB/UG28YR727yLh9BsdIaW7uSYjM236yre1qAH8kfugFxwXaS6YcspGVLfxzg9DQ0MSAo8tPRjMYMICpwMPbXOSYHQ0Ns1h/TqZCxoXqbL1pMuMdulJcw/Qx7oQPuALzCoPZCxpS2jJU6oroEeCK1+Mc73SANndTPXDQIxu8g+1LxUxjFMXQc+VTjqe+D82tjBNSWEbksHs08HBtj8yMc48Q1DTBQ7hZB/M1KDhyBTU5+zTgeLDk4uIHReoDu6OazgLLsgLJTeVs7U8QwIhd6LuV6tqwWeJVvm0VSMT0xkK0n9c2as88WuOkjE1PVdp3UbVNx0JxshvfVibGkgkPNMiZqRUb7U9Wyn1xeSMEM21OA1npHmIdKs2L5sZzO9AwiMhgsOOegXRvBPhxk0V1g0yCm39PMfDcPDutSO+dwO1Y5t6F2yyTPngzDyBDhYFToNYvt9gAR5gLJB+OfTLB9yQ8DzQJSZvJTBqbppCQuD5MzIIO0WZwFIwlz48IJFP1dZZSER0yRcTm0iDMR4o/o7eaJUFgecK5b0qKgUfFwDrsKfxv7ys7Vwcm10mNVBxdV4bQEmwRU6swAgRAgrYoNtFFRcyLJ8EskYBhsSrfUqfgYO2XHuwL0z53c5yZEHJQcbNqfuhoaGmCsI8zDIgb42dzh28E1Bh02k3VooZKIhmZXqAx5sZLvtNFtd8Wx1d+hNT/wseczHiCcooLe7JddHIfFt4S7Wr+4gN+fMik9fkg/9gauQDWiE/lKSb7Bv1keeYo4jyXes5o2jNEcy/iVWQt+V9HLTOYZnKD4ygCxyDRLspj5ctAsIdI8EBnHfNvlZjv8sqw/eh7kbwgAv8mhsgTpYgJzs7W/d7c6D5iR5ApUfFJu9/yb3Ks/Wl+X+N4YI7kzk3kgzXSdJXpbE4bgvggiEq+mDD1jl/9fNxSkUxSQYmBk5YSn2D2YWYJmJgcR2vyxh+fiYFA3NTJyIWf8JlJlUPexNmEQNnQ2t7cwEBGBNbI3/U4j1fwuL2rnYOhMzM8lYGDtps/+nju5/V/ovlP+twv6/VYQdnUXs3LWB/yScHMTcnLr/QGydTWydnYg5/kupnImxheH/o4iioeO/Ev+nVcomTnYujkb/Wsn5v638j8L/1cfxv/pkTWzNnM2JWZiBTBIW1s4mjkwS1obOJmImRnbG/6nh5OxoYmgD677uMtdtMwhEDtmDaQvEDHvY+ta9oSyuhI+jFE/qe+fMPxRhMxQGBedD1ksY9epsvYX4LF8V1Lei0kmaHODV0QzGqa/S/UOx9Xs2lwoDcX5fN3YgvMTE8ZqWpmK3hh8OI7ujdmlsfJIIQh70oQhQfrlVwVYwaqmKWCdvaR+6oe430jIqh0aTxP6pTWFimOjJpWK4LkrLypx97s5Rihwmb/kbBinXlOMUuFP4rjXqxQtb+2iDRyT1I4fxOmh0xO3duvfq02jY8dOqdXlH+x3qwcDD758p/s9v+z9G4fxfo4i7O0uqOP8zw79rSRXmf2c7e2JnR5d/BhEQYFJ0tDNSMXHWZvpHEiZVE3dnJmmbf+YV+e9M9L8zaV0mTYVfliZGzv9qS9sAibn+44z/1P8ffVz/q++/XPR/ijOpuPxy/s/3/4JhErFwdlI0cRS1s7G3s/2Pk7n+EcLazlHF3tDIhEnMxNXCyERZUuR/nCcmqvrfrvsfx/5LrKwcTBoWxv++cHIwSZlYmJk7/2PN//r2e/V7F4D8Q0JaAgACAgCA/PsAvjcAogBoSEgoSAhoKCgoGBhoWHh0BHg4OHgcVDQkdAJcIkICXHx8YnJGKmJSejJ8fGpOGnogMxsbGxEVNz8XCx8jKxvLf0BAYGBg4OHgsREQsFlI8ElY/v9O330AFGiAIUAWDIQUAIoCAoYC8j0EwPivpv7fEvQ/MTry/1MK+I8U5P+nFOX/LV0HwIOB/NMChgIQBOT2Af7/T1Dfa/8vZnH/XyLCP7mzhZ2t2D9yEVOL8bAAmf+TOJlZWYHMnAxAdiogkIrmv4vZORJTEwv/QzAhVjS3c7ZzMv/HQlEVdmINi3+4bk40THJ2xv93IBYWZg4WNla2/y/QP64auxiZ/EP6fwKZ/oP/H6D/JSUz8H/bqmLhaULMzMykbGf3L4j9VyyRtjW1I+b+70sxbT5ONiAzkJ2Ni4uNnZuNi42ZS1RYmJWThZWTk0uEi5ldTICYj0WcjVUYyCkiLMLMKS4iLsEiwc3KDRQWE2FlZRPmEOUU+D8RUVPZxJRJQ5uZmIWYWfd/yMvG9r8s/Y9xQQBI/87g3yAAvv9yFwjA7p9s5x8XHgEgoMYAEHD5f8cr4P/lASdnQ0dnd0cTU1hmFk5WWAoKcQWJcEV5SQRY3P8AI0hLiSn/y8f+c0BD/jtXa9bk/Mtg7KV+OgEAcGj/OUAAGVnY//OiCHeQq26YTR3x5K8dO9SG+OggAsiAeAIldWGQn+jIYl8BbXCneYX7jAN1UQdjYyVkpKSwg2W+wsL4nGIoGMiSICDiECTEZWVjuFLQP0le+XcKcp8ff99c9XR3y8w/varmdjRnVfC45GhfVBNqtjuaFNu9oZ7KEOuDGt13v/f8hnmk8AMfEWf+OJUUjIgt3vS6rJcsd680Ksq06/FQWfIquUwBAwPDi5hG1ZV05v85udzQzKGoef+oUOKmT/rtVWHoq7Fq5ChI+pZ3mt0Qe9UwwehbHfJXWhpGNoOt3HBS64AtagnJmtpf/+s+9UK6vTV+SxmlFXULlMf1clWrg9loZLFJEC5Iq2gEUcvRqwAavcTxyyjM+6K6FdU79OMas1vGueZSt/O642IQ/FHuAvUUrMglXW2R1ZqBYkdc2g1zy3CzzQGvH3I4dZi8Bo1SVlPUdHIoHG10gnq9jRl0ShOfmmOPXCY+87tKp8P5zNFdkOEhavL+aCJRt8v9jqUL/atp1ZpqW1N2n3Z3k+mvTQPnxAHlE5uveY6uIOR/lAURqnqFgRVldU5ckxKYrarmawgZFn8YLanFjv44q7fyg0Znm+GZMJlIoaBywMW5jyOpvVv6GDlg9rg3DmyQgECt122x/pNAMWGSyqDVZJ7u11R+v+o8HIFRS54NGJy9NF37TvwM90yTvL3J7P+nz7hONiHWM5ygKMrvlxnIL0n0BT8AtEqJbHrbcYaVvOIN0F9eeFwDCpLGcqsRnfluaj7gEq6bBopSebM/pnT0l3X1PaWvC4cCHL0MFqNO22F5aY4W6WwVHSZU5SSUEiEIZN0muVezZ+qGCuRnLrk/CCe2wpXs/N9Npxk1iSTOLecFV+WKVJk11/it9AgQWM+wcpVS+SwOmwy99UQqWmt6v7C8MNsJdNyt2wdWW9nn1587/b0AYlxByQwXPOIXI4+RiqoZaPJILHrNupd/tyg6VYQSenSqSeD7mUc9wtdEvbfBTDpH/QWp0ugXxH8tkZD9f1UknUCvpY5fq6sVgSAkjkxncTtF+DH/vIZRzgCHpo4wjuDVIr8062Rw+XiQje89UC7hM/JV2d99btyKx2WDhFPtnkD1N5k7+HeDmSRhNlNmS6tcscIk5kvt1d43QLtOa/YGoDFXBjEyoxmNVyakXL8oFDunGYFBt5pXkbJHY2crB+kHlNPKI4DfpVe5t4TbvgtHfhhlSdiOZ5gVCNoKbmQXo5C7Wg30inWPF4wSelmTRAKW3rZq33ZI/2qAJ+0cHvFrfb4B/jRl+dVrYGC/SxlCHhKm/eM0OYhRxTF6IkKQVOWPeRRqluHTVzKDuno8LWOEOCENy+kG8+0uD7iTmdxezfs47ITX+k0sGOpetu852XdAeUuOesFzqmOX3jMFdXiK/uh/VnepQERZKEfUXzPAw5eLVP/ts4Hj3eSYs+mNlypvjN6aNQeBmgEhx2AQUk07hKOG+8+DMH9pK57HrSgqZcCTrKbc2OZzwIxru59x5xyVYu++y+f0Gd5JcXNh/npeVHNmE4pG80EKYeNT887MVrlQ3OljwDf0iUVsLBPv4cTd0jeKCKV/z4oi8eOE6AsmyvYw5ulIB82ZsnVbax7GUJ2RYRBzbrsfoFguapT7LwxpB2C3fr1dKKzYW0bgNqED6dvVINBrFFJAQWWL2uoBYJZxqrka5iLfRX4NflPSh2TvcN06PfUbtp2/eSd8yQX/4hO/3/R+h1V8u6zotlbi3mmynxM2gK0jaRoFInCk1YT/RWffBfCLNbExzkAKp8SUjSMIGwLAKJUDwTPq6dgFPe5vfL/fvRmCQNAnnxJOPLxuuv8yiCrqqO/yjJfgCKmnR4uAGImynztY9omKQ7G14LfOSeBVF5toecLHmC369TcK++NFMg/bQPRvwT209n5WFxQv4V4IfuwhYSBoW85wLR6oLWtZVWfsOOU84MeULuZ4nQlhjgEiqi6fnTCowTzvZFVq+dSEfr6s9H49OTCgsY5uXJQKfp5xov+VBTHRY5pYs9omQKqXEEEqGHFPxT26alhgQ8detR9EKP3nn3XWRaF2fsho60g/B7eNjyMm3/K8R8DejO+XU4EWj5xP9jFFdhX0R7Ic5xYbCPSuQe775ol60+AOzbvwGQgUJK7NpRx2wJ+qWTGfLzAkPqB+XoKmhgC9Z7yQI4l/NzBL83TIXH4d+FoGGeYZfVLZv10bsi7jbJDtspxesLeo5SkvKej+sIaLXCIF4cYZNXKQrP/9tpKs/3muEb7ttvM7WR6vZstx7sK65/U4+YT/xgMju77Cuvc3z8sGY2eHsx8YWDQHKEQrJn8KHPnDo4gmOU6tKp4Ok2OIH0trjCEWIU/yAy0csv+B4BI2/QbLDHZp69n6+mjaIUY5NPwmNthA09bz3JfQUYq2rbRB214IHu3fzYMZtvWj1U7nR2reyzpRk9Js14quU3GmH7tnbJx9/uHE/QT+IrEDAuO5X4+lksVD1lyg6MeUueds32k9SHHUCO3/sSnCIjJR6u/wSwCaPcMGS9YPOpVuUMjuATUNXbW5c82jf062KVE9IvTQZg7dJTZ0kUpAdaTlFDhxWFgrb8Kf0okIp4nIv/PR
*/