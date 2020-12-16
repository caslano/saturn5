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
7hYxzrtPuyrpgOqZ8oxxf/QDWF2X/3OqXfxBO6ZNVOMsfxRXWEdomyK7m76JfgFnsp+SM2Pnm+onbJcHEwdoV6Qs1jr5/Y63J/mmDeziO5w9GK5uNk2KUNEzTMvcU5Q5rrHqhzPCwxI/1DJS3pD0nLHcFhq/9qtO1b+psAC1RQObOCz/Jl+yvhHxnPluZ3v1pitD1fe0UKO9A0zrk25Qg1N2SBoXWO49Gp83Cnre+fegjMq6q34bvXwef39DtBTU9V7rBuuD2pV2i5oa9bwt0/uZ1j7JrmWnPK28fmP4s1Za6zg/wKyfbMZj6TEqZyDaPF0NVAvle9pQ7TLrq1pLe5zMcbyuLnY+qn3jflC73atMDyddp5JTImgdlsljbkuaf62qbxfT5I3ysLrd1FS9arnM2y3lap+NiG9ZDJ2zcNJvCI+tDUl2TwqNtzxe3k60tPp8psKk2ySfdDyB8YfGJbLJe/qzhrGK+Sz6WNWJZH3jlFSjao4X2vgQ49SkmnyW0hBj1/SaslpliPFscU2aXB5i7FobYuxa70fDGQ3yN7hWVJ/RyPU7oyF4LGpAtrg8Xaf9zOeS4onWN13f09wnz75njd9PY89aD+ou8ju3YVOhz23EqJrnNvYBV4Y4t1HBsfd3AJzs97gOfDsv8t/vDDy3URR0NuIj4p3B+58+2aRan9soCnFuYzHH4j/DfpgtgDngq8wI1Ms4txFGt18T/xLWzSffkHhnBZ7bQF7guY2VlE6hcxvTYadW0Kk++WG8djvObUSaHddG+c5tME9v8DTQeUyVa3X6+e1bV5/bmBXi3EYCx/hHcAE2bqvStgE2CT63EWqPmmUizhkX7zuDUBTi3Mbaeoav0Dh7cL3eRm2NcxudOoQ/t8F8pnPqcK5zG2NTatplAfRY3tY4t6HrQXbIJjtMM3wVtxOPmXXyyWghz20sP0+bZdc797mNhPqhz22sbVu7cxvgC3duA3n/3HMb79YPan8+t7HZT3cYPpzuzGcKcW7DyLsguv83n9/YT/TBSUuLbt3fc+vb5Vk78pxj1ted3/gl5zd6CP5t5nMa7YLOciTw36MB8XxOowOgPv/djc9sVAqf755+Nykvin3jgs9m0HuX8DA0BFbAzZneiumXAZuBr+IzGcOZbzSnxwNHAE/k9HXADuC5wNF8hmO8YL8633s9j4XDSAtg+ulHfYDrA4/g2PIc1mMMx5iPBR7F9GuAc4FzgfOMsxvsUwb+OMTZjTf57MYfgbvzmYzLdV7gTD6bMZLPZkwA/gS4AvgvwNOAPwOeDfw58DzgQ3xW4xvge/jMxhrgY3xW4zh/K/Yk8IvAp1jPncY8jfy4pGccYCvrOZnveyPwEf5WqhvMtwAnAa8Abg58F/DlwE8AZ2OQ2wbc0Ao/NfAeGHgH8P0OhHoDb8Xk6SngdW74jIGfxA2fAd6QgPk98COYFzwHvAUN8DzwlQ2hJ/DjMNhu4K+BXwPW/c2vG2c4eC7FNg4+w9GVz3B047MX3YFvoTYyznDwnAa6hDjD0dvvDEd9TjfkdAbwIL8zHGuBBwNv8TvjAB6eR6C/hTjDAdlKHXcAtgF39JOrZDlTiDMVzVmuHbBG9aqWW27cr6ZcJfPP5/td75Oj38LzP8Ohy20+i55DWW403ze3lmc0PnsyEp3lHz+j8Z9wPgPvYf+nnNGozfmMek9F/sNnNDpANgtQCFgK2ATYAzgEiHk6UjQD9ACMerrujEbdVXfVXXVX3VV31V3/X5cJcO0/Mf5/MqAc75jBFuUF+fbfTfFY71N8f1FBxaSS/KqiSym+P8Ivvv8M77dPACTw2fY/JWPO/2NV/Hq/K7OLC6aRcEEF710CI28=
*/