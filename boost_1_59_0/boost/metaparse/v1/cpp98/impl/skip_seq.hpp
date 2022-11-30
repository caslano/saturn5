#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_SKIP_SEQ_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_SKIP_SEQ_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/get_result.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        struct skip_seq
        {
        private:
          template <class ParsingResult, class NewResultValue>
          struct change_result :
            accept<
              NewResultValue,
              typename get_remaining<ParsingResult>::type,
              typename get_position<ParsingResult>::type
            >
          {};
        
          template <class Result, class P>
          struct apply_unchecked :
            boost::mpl::eval_if<
              typename is_error<
                typename P::template apply<
                  typename get_remaining<Result>::type,
                  typename get_position<Result>::type
                >
              >::type,
              typename P::template apply<
                typename get_remaining<Result>::type,
                typename get_position<Result>::type
              >,
              change_result<
                typename P::template apply<
                  typename get_remaining<Result>::type,
                  typename get_position<Result>::type
                >,
                typename get_result<Result>::type
              >
            >
          {};
          
        public:
          template <class Result, class P>
          struct apply :
            boost::mpl::eval_if<
              is_error<Result>,
              Result,
              apply_unchecked<Result, P>
            >
          {};
        };
      }
    }
  }
}

#endif


/* skip_seq.hpp
EdPmCwbk/OWuecZOvILlPK/5HjO1H+Bv/y11w+4r0oEHAAQISwMCBPz4PxI/XOvwoAVb13HsMgcqyPcivlG5T6szZoPeHvmdZu68+9fBMKv7ejPNSGKnaXzeD7dTrqC5wnZmUMEEc7787SNalLE0hPNik2qoVfVElCcaeoxRVZsV6mtpT7Ml/gCyKUvDzT3g1cwxH2mHT8eZNBJ8+BDr1EyCdMjWgGeGkBBXKSp33a4ohIxoIHyde2NS5U8Aes9/y3rdbt0nBuWUR/NG1r1zXd2YA9zjV055+pQxJBXN5j3a4gFvZM115Hbfm0y1hqZwGry2ACPcqRI1QDWxv8c3zOP3BghcspU+gLoSqR7G8lPFnCaPIqaD6BAWf5I0dFOFODBUv7CMN0QRes9Iob4YbkqLt64K7JW2AyJqUQb5J/otwPXZ8kZl9DNCzJBZzOPClOEyZlKvXA14RVPZYaHqp2TKzrsBvWS1w7ZrWlpho2xQCahQN0E8vmXSNNc1QIVEyTN55IsJ/lROOmty25YKG5PRxRfo4K40HHXdMxykkQ7rKcvD6SjMCiaTqgPjWj/foSc+kKdBQJvoJS0awJfc/9w1tHzzFgiHJ9DgoAFdgoUiiHh7dVkq6SVKsibZzgGMXUn7KTir5eRH65GKaY/hGenFD3qBHFb/gg16+l4HHhOyH+g3R44iZqXL9xenwhwyw2eXKETOLW2iXlkt0IzouxkHM+GMcty7qm9eSoEHRJbK6AERY/RGoj7nvqRMyEg7lmCm2CCrILoSBoGQiCuBo0NMF20ZsIMoVes+H6upK0z4OGe6r/ZOJElQRlTZYi76UwaQ0ORfC69MJtAxd1DbWAvjXfCGqFQeE273Iq7B2B0cLP36DpkN/yo7xoI62/G4EMygF3fWCS/c0QNxVE/6RKCs0TNRyskQUSof8LT91TRjK6PcUOiGB4P9VBNaGgCzqV4eE1CSyB8chQrR87Za2hmuxDUPQY/FWs7XSQsli37iYIRBAtRcFodyzCEq1iOtE9YpZQhoiltAnbM0vA3vMuYks5+AEVGeSzJ7WtB47ySuQEstzKE+u3ql665606U31eP1acRE2k8gjAPp6IT9EPdogSJsUYqFJrRCfRvgQX9tFnyQOXLIfcbtrBfG0R3WeSOz+S2WWAO/kr8i6vdQsYfsrQazkGQaUh7aHwjAimB7cLtiwAJaX1dHa1pm/+7fliWNWs7kwntKci7524j9WM/zDdVzdiHXjCNANW/VQL0e/ceqoA42tiiiScHzvLrKY7irChki4XCdG6NJ+muMbBsCVL9PFmthcAKpUlg6TEHKNnMqikWtZObMQVHCFqAUD6cvSKLoCKpWDRWwwXnNQ7+lGJmdmKFRoRu0luzEUembB1CGWzNmmif/cA3r6RDIqnEFfLfA5PMjOWXOFaglCFXWQay93hfmN6isdihBuGEkIptwhePvqEWA2SU7aKD2xG8g/52Uj1cAT7e7UK1UEry3ADQ98Y1CEq0SsFMxfW0SGciWcniJCSQCBw38oDzP308XI5B2eRrzcCTUVCNb46PQx/qgCAMiRBii9LQ1y4YZAAkhCjkhAI/FAU27WR9+eBu7TFXPORxhRge2ZLsZZ1EVDVAMZtE8cfRKZcfpV8BiqlibQAON4RHyYast6UYZjGFQP1RmAeNgAbhRqR3wjvjXgBeM6imqeJ0UeaWV4S0U8/HvyEEhSYG/xxA5U1mjy8fdU1MVuxiB6uG8r4oa3YvaUUGuU+4fsaTfEpyY8gE1bhb3Up0UoifKciIs/hjG09UGlGyODBUqTS8hRTxHTinKx/hERAoko6bkh9m22xXWPbvd7iopwXTM4yL43kF4WQrhN73untA0nmEpg1HfYslzRVg7jsUsER765HcqbfFO94D+oN36nCiBJqVhLnayR45fHklFmZjg9LnDbF0CnDqEuJQFrcv29W3YEG+zWIUmsj6e47uezsrmIC0dwcLfQ+2sP7mQR+mBinPDeYwUYRahqtw62KGHsTo1PbLvXz2kBnzVuaJwxytRDGEIUMuuCxuyPZmMxWYOKC66e96XWHxVX+eYjbwE2BstqoJXUG7TkenSELE/EbTn/G2F649DTkyuVIzPSTKO4ILjZTghKUGORB48Nf/Ugmexa9yl0dH2hAn24AgoCl75fDwFDgzTDaniTZJtodVLZDmG4owXd51mgky/c0UBy1gpEqL6SvkNG5NQ9OD50AB0jJUPCJq2r4bZ/a8oR+hlhfmplyX36j6/YhHkqcX0wIw4s066gb2R+6UPveHGCZw1xTYfqG41YrhfnEod2kcYdUevFiQGSdV2QFB9jq252L97/jh+RhrWCrUpFPtez2ZAO5qcMXqXKa0scFFsZwUyBzZnLj1IuCd2Jcse6LZLxNwIHc7aRqsHkaoDVNIoBYATQVxJp1N0o7Fbh1IMy9434Ba+UZ8QKiV9Icram3ZKYCfnri9iH6aiRFSiFoA9AvYBR8k3lUS5ICJNCpmW1Y1MnjFZ40IxvTZAPEDdqdQ36x62JccPin5UwRcmDgFFhY59/fz8BMkDAgT/CvkV+ivsV/iviF+Rv6J+Rf+K+RX7K+5X/K8/vxJ+Jf5K+pX8K+VX6q+0X+m/Mn5l/sr6lf0r51fur7xf+b8KfhX+KvpV/KvkV+mvsl/lvyp+Vf6q+vX3V/Wvml+1v+p+1f9q+NX4q+lX86+WX62/2n61/+r41fmr61f3r55fvb/6fvX/Gvg1+Gvo1/CvkV+jv8Z+jf/692vi1+SvqV/Tv2Z+zf6a+zX/a+HX4q+lX8u/Vn6t/lr7tf5r49fmr61f2792fu3+2vu1/+vg1+Gvo1/Hv05+nf46+3X+6+LX5a+rX9e/bn7d/rr7df/r4dfjr6dfz79efr3+evv1/uvj1+evr1/fvwAUfvvf2YMt1788AUcyGWUytrjACjHpvM3Nmxy+N1MkHYQS8uorNeFMOVGN/Hn8yPSI0oGXzLfR0JjZ0zYBJDfEvGMwD7dffsAxhEeVvpPsTJswH8juOVQE0z2mDX5OqObgMjRzFk7HtX5y2/+z0mQrR5RiBx4PRSjIKTrv/wo6u+WTW6qegCcIJGNuyxJ31XBwSBHSLiJ8fJyYtl9mhRN9nC4ns+xye4p2v4kZ1Zt8E/6HLMpk2+cPsSOQWiJYIjmoIPEg5g5XOYXY3RRiHBKuuhFWWNcI5dLO4SjAvQw7EQfS7oAkZfnTU1SnJ4I+wdUrakIA5GuOTnQWAoIncXqfWBxP1cNfsTcNGerm91mF5ydxOVViq8cicq2W+6GT+ykfs/HH0Mc3nxzDg/ziBQHP/D8Q8DA1OtW9rE4UE0mRR2g30m9A5so66CZPEF1MNjJ81ZhJav9YKTrsLxW0lofwFybFettXFNeSpqv8ziYoBcuR263sLoWRqBCPEr5ToD1TVP49StlJDL9ufwrmK++dfoRwxPJNOD9EIXMmPHmDFnpQ6aKHcvrgaaOf/ekfBWavwyzBx+i06LXbiL7wODw6jZhsfcO9Q7LIdMoPEkxUfk1c0sWHTTIYYWRftKGktWnzisVfvrzYhXdlwCgAusFvo72q8cZWGG6iqrUgeSt+L2T13oZp3XqPUZpD+PCs1Age7ruUCr07RXImTmvQ4jV93yQnmul0zsObIz2OLKH8kcd5FNK88fKc8b0Kcgk+nUGM1eschDoFi9eXZiNi3A0+i8JXf+sGfTnrrWqTVSe8pCKlBTI6Y5UN76xtBSKZ4PFl79nAt2NY63pr48bHoRf7awKfwE6zbD9izjk0xwSdwnYOChrr7X1bBLhToPUaG78lyr9IqjXgdbUPeCBMqjVXoXc5ox1r4+uy4w9lCz/+TxQ6lE3XTKtYrqnrrcTHX6N1zuksOF8hY3gXNFkvfAdxkIb8ymBfDGxdsYYYbDUoG/WUJNNb+8evbOvNV655iprWd/cvLHuQLwfpzJpbmFRTyINYUn6TP8v7pYpkSK0jIwOXbPnmJCS8J+XPEpgQ1RYUv8U9o0J83pyoF/GiTT9uKioduq1xVipKBurr5Ip8Qoj8AK48WuVVD+8s4VJC7guIVxrMlAGHDO8VyxewdFVUEXDzWZE7kZ8w8EMGt/NtjHQLeRchYkHhArqta1UBoz9ILsJf9cPXIChfhXf/oi1yhyqywiY+WiSa6b+noR8EaVP7jDiRIo0j45xMpZBsGGXdz+ceuTDBnn3sR+7eD4yuB9wqzkOrCdninEHM6hOITREy57zmVix/oF5HC2v+KBDopvajqeP3VsOp+bLKSLhnqlHSFFHHB3a0YhapamssLAVu6gjsWqpW4DIzijc9wIpiaOVrZw13IBK4gpMJGeKOtadDEYtKZ3KM2UJI1zrpuEK38zeruz9HjKox2KOM+lV7kdWmWK/vfblHp/F3oYh3wNDyajmA+J81JwmLrFZiO40t5l+zM54C5TFaIry6XV7a/3FAm4diUyjyikczGMR7PtXkgqGF6Av7CXeiHw3l2JoROw8Onyhjs9lQv1yc355maUZw0bOCxrhypnwIEeDUvU9wZYVuQNo8NeysrLIivDNSxKEeCwJUX1uQ3BZUgjtS1kQP5Ih4+RwEviCMi1NiIYlb0xrEUYDJGCQLaJ/gqiFKQuFBrrrwGm1Q8ihJ7Tw+uSZT1U8OAEQguSVBLUT4IjwcCAV1GZjZ+rsBXStqKLQ+WYq2ck0fsGx3o7QbF759aKsrChV+D0LiQiuNO4r2uVLtPLPd2cX/el1IsYVwB68cSCoV5lfmecJWw3W8YGedhij9w7fQMkVyI1czQgl4tMs/in9N8f5iu0o9nEsm/+mQLuD9WivIORyHH4PpZvnCALQswfKDrvRcpyS9PkoMIQUWvhSVWk9sJj4YEVxHKiTJWm4hkbB2U/IocneTGqb/gcJ51Xs7HU1gYFzQfseRXZ5zPuams9xZLyOGskz38FoROqDalC13p6xs84BMHJ5rM8GwYP5odKMrjmlxC/j1R8m/cMS95fatlqcZcjBPrsuIfPc9R5oE5pzsuMbCmZVHpCkqzOV0BgxuXGCxfxtsSZXA7Gnf7P2aoy7Dt+q8C67PXg0sI2bum9xHOdrdRHPo7Hq+9LSEuBipNCoLJu+b6Dep7g7/fbZHPwE+kp+aojFb9cWFGU1Jbhw8CDvjkzVOJxr3PLkvMohtxmQ9/mPQdvqQmphYa18c8CfJOyjVmbvBGGgtQe+Jzug8TfAECcMnaPRf2RvG0TqDzn3TvPQO3AcjD3KJTJfnptLRUi6s7YFUUsShY+eYm7RS55u9szkMaGlZbZ1T4tKeMtcxVRQ/44S8BcYgu7EvR7e+ZdSliB/7jzrAler3pXvvMPSKGAt08DyDl2s81whYFCmsAKBh5UqER+52bZR5QmqAqWj3GVm0qDp8+DH1P91cK1AjpmoSgrNAvnLnBBQlPztGfvHumJw0Ubt/GNrE4rSdN27isLWRGOvkXcHZd2dh//hQZeb1QAHNGHIYStPrMg5K0YDnaYTqA7js73l4iTfkdAwhSbsB6phskl6RJxg8H3mf/JAk51KnlVZKpttlOXglYZfnVUa26wVmA5LdafiuWRvRbDjw3WsYyEi7faro59In3KDB6Ldiw3tR285PkYriN9ApkYJHAoMJeZKETQ3DvGWUZK0BsRqt3s7kuT5pMymrZ09veZu5LXkUyw5XSstBxudGoivCfNc/yxPo4Vgr9SnDuqIc1bse/ppOkWurZQGCnZ+N3PHzmEYxScctt+Ws6qUJPx3np87n1gDoh0tr4iKVWh3mENvGO5aqLa3XXwqkc6iyJXkcfZy9p6b+RFJIvCM/acNe3TO5xmxRSfAWNA5QRCsBLhYrjMAQFWRDP05l86jTbeIUIpKmerN8jj7WMRz9mS27gYoKjFUbRFV/5qXziCocOxFlgGFIgtlS0PKpSTG+DSUrU5ZKbTcgPQP7tL9rz28wURCUUzZ2AmpjTFXXBmUWeshtUyRkhzATI4sGmAo26t1OC8UqE4i/SjTHflwI+/Bd6xVEgRnxBI6ghmri9I2MOWcAcQmDGc1VliCzUI0qpq6keq0MgCuCv4Oy9zgucZWJGoYgGxjUTHTHUxObVF57FfMRmoOGfQchHWyMRM5mAKS0WWgve2xf7IQCq5A8KKSAIaBsDd2iZD2sxHMIuDDzx50Lk9mE2NwfejzqprhdhDKeGEt+XdJniW7zQ2teCkh5bQnj7AFb6wN+5Pwz7A1IjkTXXli8wovC+gpPgIDTCVJXOzT3FO8jJRNjpJnYAwT5CXpAL9v1AXd19NLFlVnsK/YSMwcDssX5UCW6kGCFYR1NrrbsCgWN2HrpLVFdSSHZvUavd+y4IOnI1+29474nMgceH3uGSsaodn/ef9g/c/9CpWjv6DVUIiPeSXO7nDJKRhSO0Ox7y+F4Fu1P2wmN7qbW3N3sCpWO8igotSIs9AmMv1k7UsvIQzD8B6+g3tKycZ0GYst5k9mPxwqYxFvTTDVXKiulMQOU9sovBBbm2bkwkImm1/jrU4BVJAV1aYWM+atDQpKltArCzQfa5k4Um0uoPFekNl0x/Eb9ks5H0B865nzW7c22QpXfzVe2trrLgh9b2reTPkWz7tQkCJsxmtftNig/+TtyyCvFwvUq7oEdwtruYa5WlORx/t7LPvK1LICCYTLPGxbqmzJOxfsUhx6hJdlmBFKLtqY5w0VRFCyLcqTt5COV9EaqsMfeY9X6onuyG6UX0N3MrqVnq0yfiBXE6qj9AeG8CcRjgsZ/0WpTk9g7szKswv9+ytuRjRk37QLqZHGoCwCLbsUFTmnUHQPtoYMmnbH5JpfshTG5ovhjCCsLqwlmqpVLTKp1LRasJ2dm3FS9yZt8oOvCVf531/CqrSiyVWYRF6pfa9XPCdFX1aPK+ua3qNy5pXqxFIpyAjl0mZ9yjLQwnD0rcsyX8IGS8CSKBBBB+TRC3X57KooCHVcsPssaLLn4fnmJGYcthR3E7M5B5I0QsrDPKvuK+h1SOLJSJ2sSrTIJg78zeph6Idt3qCUvlbYFdqSHLgOJ2b7d4a3pGh+bmoldlHCPQb0/w7dmhl2NIdSPKLf4AYmjOoDSdFgda7mMqGEEMHg5OONYxiOZQDWErliu7udwjDm3llLqlL9GBNAVRQc1IBs+y34qBDeyBhhtvxqHhDRGvS/1GbI1cRTYFLexq5Lc7sfqAoCc4sf2fB/VUVRuyOeFyYBwswvgOUnM0EkHCvQ6137PMoFjTuDBbEwoxYoCsVXGfgxRd403yJhz8Cf9qYYPa6n0ll+l2yekh4kNu/hHifS0C2k2upkW37p57/Jmn5+tbnFbk/1EeiGKIBSUA4WMKi4Bq9raplhWhS22t9Jeekc0bcYJxyBzWL90g7jpoEvqmiQuuVQkv5C02eFM+2BwI0KtAXBfSq/2uP9imaszGfDB/K8UUeBWXUvIseq8kix7ZprbqF7kxiyVumH2kTNLGlNObKE/AfPCh/+xcGUsE2dmYnrznFO/4Hdcn6zMs/eFHeDtXNYo4Tx74+O31fZQqjHMT+hj4HfSoF+B1m/TgfWgC7p7vrGlmD1VC27+yc655X8GCdA+7ENCajiJ7FFUm3vUyD5L10UR2ceFoX1mWo0v
*/