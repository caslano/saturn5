#ifndef BOOST_ARCHIVE_BASIC_TEXT_IARCHIVE_HPP
#define BOOST_ARCHIVE_BASIC_TEXT_IARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_text_iarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// archives stored as text - note these ar templated on the basic
// stream templates to accommodate wide (and other?) kind of characters
//
// note the fact that on libraries without wide characters, ostream is
// is not a specialization of basic_ostream which in fact is not defined
// in such cases.   So we can't use basic_istream<IStream::char_type> but rather
// use two template parameters

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#include <boost/archive/detail/common_iarchive.hpp>

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

namespace detail {
    template<class Archive> class interface_iarchive;
} // namespace detail

/////////////////////////////////////////////////////////////////////////
// class basic_text_iarchive - read serialized objects from a input text stream
template<class Archive>
class BOOST_SYMBOL_VISIBLE basic_text_iarchive :
    public detail::common_iarchive<Archive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
protected:
    #if BOOST_WORKAROUND(BOOST_MSVC, < 1500)
        // for some inexplicable reason insertion of "class" generates compile error
        // on msvc 7.1
        friend detail::interface_iarchive<Archive>;
    #else
        friend class detail::interface_iarchive<Archive>;
    #endif
#endif
    // intermediate level to support override of operators
    // fot templates in the absence of partial function
    // template ordering
    typedef detail::common_iarchive<Archive> detail_common_iarchive;
    template<class T>
    void load_override(T & t){
        this->detail_common_iarchive::load_override(t);
    }
    // text file don't include the optional information
    void load_override(class_id_optional_type & /*t*/){}

    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    load_override(class_name_type & t);

    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    init();

    basic_text_iarchive(unsigned int flags) :
        detail::common_iarchive<Archive>(flags)
    {}
    ~basic_text_iarchive() BOOST_OVERRIDE {}
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_BASIC_TEXT_IARCHIVE_HPP

/* basic_text_iarchive.hpp
0ZggYSE/KK7HPtmnyNg5vMKm17hSVtNugLeqRU5bDNf/DdimMD//UF94yiN1GUqiC/pMIb8jjjPy7NRk28pHzQK+/wJPqaTxsCHdw9eO3kLd2Bw+04hTOUSC73LBWKXpwyjK3VO1FRPTt/hG+dy4mzVFLzMh74NYAJnCGX0i1wrEIe4IqnZdQrNCeyN0RWC97RmQ6wuj2+1SJTrtTEm3GlvYxDtIBmDI9u9nejN7aVlhcdG1bDhRXa9vbpEHjdtPN/HpuFPRseanhfj06PybbGyhJML4ZnpSi9Q9P3UlyEfSzyQp8qlZ3h7nkgdcCRyL5b9Ea4fn/qc7K47JdHmP8/IPCOwVGphP6FdTmdTv5hkaCkdNrZVA0PpmjE3o3FR086gWFakjpuYxGrYC+sUmLoxUzlsgYSnJdM1RFCRDzfL+XLQlvfN/wemfyP3AJhKksvDuFVxd0cNoLZ0SfWTgKY1OwwQt7nj9fWG4ObcDllzOaeiRxlWWSb7B+F6g5mDOMaTWmrhuEJhhnYwUrxrYdF2M2KxV0YPK6WiZZ/ySeFO0eOgH/O4pI+0kQDRFdN9XrHDWN1dO3CdFrX36tu4xBIV7gaRs+sBsn0GpuBE83USWnbbbGSj/DjGE9TDKXAXF5/xiKONCFQ2zVuRiz7D64mg7sQJDKPTJDOcUIYVj7pEV65I19KVNy6COs7YLZkGUUoz/fG6ZZ3l2ClJ0Az7yBDRLoh2UAMPXAb3T479tmbYVdJNFImoMrsCSctjZhngmYBNviPGi65a9FVMU4WDS4R0MbmKVUgzwJmfyssQ2Cl0MVhNPb30qqdTnw9ezWYtJahFXRxbSKZvMOk9MQVaz6YllEhQ5K7M5icXFohPjNP9rj4Sy4d3/fAmpDLcdFINNzzHw8C7Yiq+GrM+TjaTAMtyaZx95mbREmicxiZTAKdyQ5xjJSpktqY85wtLcJCgdM03QwucQ48WAoAvKSEHFs8KurfAz4ODlKWmLeJQzJWEOrbm07PrDXagaxYPRSkfcDu2aCBQP9Q8dRtHaLvth28stUZkiLGCd4BhVQfoz1Y+DOJxlbgS1P47QZqz9tgo/YzveGr8Kf2Q53gV/gSqjN34ParIF/tnCvhHWj1tjJt4B/4A9YyfeDv+LfWQl/lCcbG97HneZnnGVXrZf3hYfmq3Dh6D3CPvLxXizX5tZb03mbhQ0vwPXjSAOesy5yLW/AFrSmcktvwB6zmXItR8CpeyfmabpGzCyfVkvZAc1p063v4IW7ZlDixYrvaBL7y0nXUGQGDX80U6JluirgslwUxMx3LOohjy9UPyI0jMljVan7hsS/VBCX5PHZkq7duCn2jv/GNJGCkFPS7ypL+EzKXVSly3vzmMQxQPjP/EX065YXp0nYgpotpG750OtVb4yFLaoA3aP5h9vG3E8cwtHIfzt6sEvjh1kQIRpyDGuBw/LHRugfjU39o7zlxuvBRDBhvuRf87P8NRDN3OeChtCMPcUJJY0Wjd6XkjrQyrQ0sMx1E/XkF4Nvvz+bp0dUC+lE/vXCZ8p/15schD9EP2DwA4iPf6mLL+ITtRjv1UgkXgAvcjK2M3oe4NiH4B5PKdcv9jKQM7ssyTIpgx+6pNLAjP+i6sE1LMvvK4sY7Q3bk0o43kdl60SyWScM0Fck/I2x58cXEmwX55OxFeDo1HUSeHDhmEt+mejQuE5as+0shBoCvs98vOR4c94ZcJfPekv/H7krcarmx6vm16gn85l9m73ivQ4sAyREvRs7j1QGlTMEH8sykePmGWy/4pqJMosMxWHamRIPzMUR2YTyi1zPZzCLS+r5AkxhZBEl6vLyRZTym2oXaCEmqbIYROQyS3JMTISV6QMrIBarYzpaFq+bVUkJGuOQGdyCVazUKSrrMrFFuNAehJcxsBo3q1wxHnjdnoAlrfw0oSqh7P9R8kkto+zTdx5+3J27E8xk7bM5rRsgfIV/EpUN5O6zeR0bMM/r+nxKKWSjenSOmO761P4tahyJv23k7q4J85T2V6p2Y0cHwCX6BL8hWV4G+3H2dP3KX24PLX3zrG8A6ZGl86quOnO8bwjpvwXle9vSehh8kq3NYEGC9cbIlkdgadLzu28T6ZiF/bSjrxlr+2P2Ze/+/jPo7Eu2vNgFncnTkqTnEt540zTAyw7uFfFYEtJD5nMkXA6Xh8bVDjHsrDENXO48jntvsbYSxUPgiHhK6oRBqNKOrA7Y+zOc6qeDrChs1u6c6Z/9Wtsv/ev+Jrj6x3E14QNdlK8/daE9XYqHPrmhG12elz9NoWZm6ty1mY8jhviz7thF4Rd5lfc+VaFneYvvPBnh0dbiXVPiELtxSPth5EdxL3mf2wB70aJ4SPq8adXWtaS+Y/ulO8+Q2Yw8/NiG5xwTfP5xhogcQXz974bGHBHKwHLG6Y4FPzwhqzKFSZE6PDUl0uHyup5+1eD1TZYunFR0Ta5YZIs0Fq43wNUSxrfeeqmkTjjyFu0NugxWAiuTT23of4ZPZFdq2bWb5u9zUIUmzjFWN1kam32ve6iR9Jbz22Ff8g6FqI70lmT5PzZ0eMcB6BjnydnMZaputGsQFcHVga/ZBG/8X7HcwKpgl2zYda+3TbmpAdg4+Anb7GZxrXOwcHPDrv6WkvpXAe+bJGd5r8e9UTk1ekiBI2T0CiNtMRMAPFo8I7KUt9k43HnFngfcnpE/yznXGpteO57mDh9rWs38ll2HbkYuEjZnOtpF3AMtw/ZzN5dOfBuvgy4j99fIW7NcmJ2Dnki/Yi8iz9e8XKw9jn5Pt3CeZg/ayF2TXYaeS29i3yJv7s/MJq4uTxDwGP1tU8mBZGaQPa9TUPnzkbH58TkpsLEd/2D8mKlCO8tvdp6TiLOTHnF8sh3TrDMJndwnlN6Xuv6+YV4yun/ao+oj6FFq7HdG2p6WBhzcRWv2f3iDg2FCE836nYiUGkfDsDHj42u+gT71BGqKw2OlHvlwYtmF614qjGCJVXGgkxgyv1GpIUbVWtjNAZ00F4adZ5KVHtGMPcBPws80D66whVpnjqoYNqDMJFH0anCS8Gr+0eRmVw3vkgYFyr9pp+l/FWU3v8bGr8Mml6kGAIJKRvKT6vwk3AJmV9Q1wZNCm29/Zx9o32Cfb998x28QD8ELMQ0BCpEMsQ5xJecTQpM67zeBcb0/FYVYswmfi9h5x+haeec74prhZ/sX1NsU2xHeFf4QLRQtEQc1q2nBmgXbActryyDLStsNy29LL0t66zZ0s28efyJvIPFH0aPzFYYLzBAGtpyicaKjojKCHutsdJnxqPGM8Zbxhpxz+jkGP+Y7JjImOiY8Ji6qNao9qjOKwFMM0wrzKI/7dzL4x1JLxSmFKkUpX8gSG5JbGTgQ7fh+x7AjB3FnOnQmZTFts23w7fKt8e3zrfDN8l3xjfNd8Qn595m32TfaHHygXcAd4DnfFN5FfHA4LFDnz6v374Y1pmANHdTqBERoRpbbduqbgb3dsZCuhOSPUs2f6T3lwj1LPspzQTG/eJwnhvQFlSb2c2kN4IvaTwiqQe4ospS/8DytOYRPCqiOyi3TIfhzGsWuIm8PjdinlzmT8jQ9j8bGhQ4YUYIBfM8cdoATLdiNbQVcuemoV949wqywEq4waHhrz98LOimtwremuXPERFKupeztGJttAb2yFHkDunKCZU+Itt0bulyIHEQuljuIX756iFobwzIV31EeSM7kWAZBMzUaSUE72mZzdxsITGlGzLsVQ/n/iPbgksrhCkNRw8/DVc1uBnejskjDtEQvAy8DrwJvBLUDYJ9sbQBserNiWM/9lD0CHRD9ih0Z/QAcTv0IHJbZBlrFGssayFrPGuBbCFrEruYr/Es5W0SaRqpFWkZYXdzuf8GuQJ5AHFi/vz3+e/yHxAxMjGWWcAIwiJRpyAVL/Utn+8ibBREAAPBP8p//HSKdJolJZ4CRgb2AU4FzgNuB/rAeoT6As4GrgHWBY4D7gEHk08wZ5Lfkd+Tz5G9dU/N+8wPzV/Mu8wlYo5hYKLekcc4e1tICxWrBascywzLE6sDqxprCmsWO8Drppu2O61r8KwBHAmcBewNrAPsC6wHnA48AmwKnAaOl7fw+wX/BBX4IijO8U1cMWWosH/8/mUv02cDkmjPh2d+VSjgFNWL250nVqOIeeU3O7pxh9RL2w0nfnPXWeQjCRkRJFl8un2X0ivXzXJXWfBHUPpoF9Mb2B0kHnJjB0f26u4X1MN3wkBOgd915pMNeQkXrp6CqKbRuBUyJna9DTMSicnPJytZ6rc2ikL21Ru62emaT7AzQ2q2lwZyqz120tK+ZYcY/clw/WsFVufpz5/P7+lHaZFdbwSYQWnVL/vNib5Tz590aNJPs0ZEa1gnOaYiiUGu5nx0z+N8cfjkb9Zr6lHuYelB7RHqYe+BSxmh9VczX4tck15rXQvo/LAR47F0wgBjf8mo1jChKN4ovijBiKmQ0ZCxkMlQ4qHyodLnxmpqZGJgQmYmA+wH5OBa77rsxu6y7Qr/huyS7nLtCkE9uUOx3bDNUfNdx1gGIYVkcnT/SMhPqG9Ll572KDve6Mpo3GjBaNdIO+sViIoHlIeLB4MHmweFhzAUXfAPAbgXQJy/KV9iM+T7GEWdz0ZbO+JLzpVWUttKd4pq7kPRQ9G9Eac4wDAQkt9db00vqy4iLWDqJ9ZH5iuWDxV0yguoJL+AXzY70UtFMGt+sGdrcGNj8H1u8KCHRP/Y4Y6Vo5Q6Fue6sHP84XIrzr1j/j4z6/cuTkit0t7g2mY7kbukA9IN12XH0nWiQyoezwxES1IU7s4VESrXY+OTJ2zrwf3kcYJ+KIvdvNFr+DXyMxWCtaojxUnmWEOYTGDsv3/a9quGFe+ZEw1RMqwJ6nTc/9LMVY0qXj+v2DayVrHbTKBzSAXih2SvUCUarP99qW5Oww+z5Zh0UP8xsDxLTjKJlomiXruMrUAqlRL/EUAlM8jUj9f3179XvVTdV/W8jx26ne6dnp3enaZd7r1dfnabZfvELjPplmmSSZWpkymXaZCJlemWiZfxypDsEOxw7+Dv8O6w7ZDvaOT+Og8ZZ/1g/SD6APk4TFhNGEx4TaghsWsQYBFgCWAZIAUmFRA94czOZd5DMeez74PzL3y+ExTLHKALoBsIBw4XYNc4OiE/STipPGk6mT5BO4E4QTipPxk4cTwpOlk+wXKpdhF1uXd5dGl2AcmuikGJSYu5igGMYbPKp2D0PiS5ux7Y1qDbCNcI3zDQMNiI1IjcSNJI2njWyH0Ydnh5yHDw42jlGOMo54jgqOSI4pjmeOFI5BjiEJ6BxcUHNM93RXEtyq9+QbHpjyjsnygdkOAOUtENkVA/rivjIJYfLz0s8XeicjhXbDIbT2A1dLxn6H33WKMul0ZPuguiHj8RK6BXfeP3IKYmp3L8DEujj3yL0h3rmn9pBOoqj6HntzETIx0fRIzoDfdICsUtUNI16yGKl0d+JMJQOCSSl8hQqgvdS8QrB1mIIx7+I5exVCe6myhc/jiXRxL8J87GI3WpNrQk2XMiWUFOVkmWOtdASpGZQjeuSA5DPB23n6VCdhpD7k0ohREkjUahMlpMQmiEWqFak1UILW6VQ5AhsLmqfar5qj6qlarlq69ytayPbL2sn2yhbIssV1i6gr+l9JIwoJ796qc9j9XO/fQE/pr5uPmdeaR5g/m+uZ95oHmLOU+tTaFIIVlhpO3HjZm1Q9IoGJaGzlzUsdQj1DLUXmOs8pnzqPOM85azRtizO5AmpyaTJqUmsSa2pp6qo6qUqqaq8spDQ0zDLyq8e3h8BGUJ5QjlCaUIrB1pHSkdiZ3AnEB9ezASfwwfrGH47xjH1ApTtTuJS4kHiX2JJ4lDiRcJnc65wrnCqYJbKdAnhCIoOfCSnzgvUy6U7MHbQcN5wz0TtuZ+Cj5iuGdjIWKbz/ZcxgETsZ5RP7XZR5YAVdfrCWNxkqXXvH+zlXXAuv7dHGN9ElHHsFJYCQpKR59cWgZiv2IQionXhf+p3F1TvUvZjWKH0nR3+Kcj8aUic7V9S5Kq4tjC4gP3bvgEU4ZIuPbaoHiKNvYWOaUUSrXi40+nUouiUbnrzxX3RtIqSpsFdAxpV7qQ2BWyRJe18FvpvDTkMHeORYcz3cDIPBnFClbN36vNNEQVCtmIRG21YxcwYiEmIRShqLoYg3KD8TFi1CIOIQ7i394sUhUaUNj44Pu4VSmsftNe0tbTHtIu057S5tN+0xbTfqKix4OMZRcFLIRDBCPzK3waVxknT7xMuly6VLpkkubOLs0mzSnNIZ1K3kzcRN5JzEfOS8S7emj1Vw9MiQC5BxkH6d4gQyqzSx5GHkkkRyVLPpVMuqm4lLluuF655rjRuSS8FLmcuIa7WbhKuda4cdBs08bXGtOZ01nTRmht3lbZNNlu2QHfPGkMpUYDfohO2pLoKtEvRilBLhkpHi7GKEEvoSghL7kq4f2I+rj+YPkAUrFViVdRVEFVUVX5q5Kpcq1CqhKuElmNrc3/KRQ4Tt6KJORliWKzEF64MG46L065QG47T1T1sGqSeU7apDSuYOJY5XBe0kg1ccHW6DTOYPwIV69VkrlK0YPa7j9zIdJUNx4EK65JolH5dkHfhDGBaUIEJ05XCeItzWUOja8aN5sStoIyRYqjSBAlItOv7lVGWERzWsVSPCP2TmSlMYQfrOLPiGEppYzWwmulMYLvp/KXac0kShutmdf7UE9jAD9bOz6OiqeMtgiAuta4SqGZaje2KAOrPEent6VKduaN7W2C3QywXrPYEWwhfDxdq0Ozy3adPb/axc8Y8Er0KfRq9AjiTvT6NMCqTiNAo1EjSKNYo0ODNyBTOkhb7o0VWHULaoL9TaFeqd6ovmmY5A/FH4k/F/PsF+wX7wHtAe6d7J3vj+1nQTnQrSKpIuciWCLWIqMiUCIwIs4igc1H1knWatbYK98rawxrRwkMy65OctD50FvQhtCJIuLNTStkK1Irfituf/YjiD/fPo8+2z6LPoM+k3ItZRFI4RTB3mHJAVFWpc9nqiNrJKt8VYyV//2tlKmUppSpDONGULtbNqIUpaZdZWYW5TblDuUq5R7lOuUO5STlGeU05RGlTH5Pfkd9V8aRAhrxU+CltQVjBcwEkwYyyRnJKcnuW1m2ddJBFT19mGN4PnJWrydUvw/W6E5pRsZqPHTVEXdNu5VY9znJlN75cAt6+0DCV268csAsQXuJro7tInpjsn7m6ip9/SM9vkkCT03RycpXRZFPMsSiewO8M+Fck3kg9nYk3jphyW/bkqI6+b1w9MC1GzbBosEbjmC5XzTBGnCNkswG6oLnnuYwc7hBhMeviAWczEnbVtl9cm+FBD9NLg8yMimPXaqJutPTZeKB6EHwYoUAb5TZvFrTZQh4ZpwUI3V5abD58NZ8gcYQnaKt/nYMYPHoYPKi1cV7JQ9mpLaDQYJcgkKCYjIyrKPCzeq2s69r4mLiY2JzAmDh8mr/wX2K8x22yIKr+gcGGBVYwW+qF0/3+8JN3KtDMkQwxD2EP8Q7xDZEPqSR781c7SjwK/Cr8avw63LsdWxRp/ngZgsr9zL/knDr4dV/PUgl4jfbToD0bASEFbPB6T/rwyK7oLw4
*/