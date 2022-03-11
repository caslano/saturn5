// Boost token_iterator.hpp  -------------------------------------------------//

// Copyright John R. Bandela 2001
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/libs/tokenizer for documentation.

// Revision History:
// 16 Jul 2003   John Bandela
//      Allowed conversions from convertible base iterators
// 03 Jul 2003   John Bandela
//      Converted to new iterator adapter



#ifndef BOOST_TOKENIZER_POLICY_JRB070303_HPP_
#define BOOST_TOKENIZER_POLICY_JRB070303_HPP_

#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/minimum_category.hpp>
#include <boost/token_functions.hpp>
#include <utility>

namespace boost
{
  template <class TokenizerFunc, class Iterator, class Type>
  class token_iterator
      : public iterator_facade<
            token_iterator<TokenizerFunc, Iterator, Type>
          , Type
          , typename iterators::minimum_category<
                forward_traversal_tag
              , typename iterator_traversal<Iterator>::type
            >::type
          , const Type&
        >
  {

#ifdef __DCC__ 
      friend class boost::iterator_core_access; 
#else 
      friend class iterator_core_access; 
#endif  
      TokenizerFunc f_;
      Iterator begin_;
      Iterator end_;
      bool valid_;
      Type tok_;

      void increment(){
          BOOST_ASSERT(valid_);
          valid_ = f_(begin_,end_,tok_);
      }

      const Type&  dereference() const {
          BOOST_ASSERT(valid_);
          return tok_;
      }
      template<class Other>
      bool equal(const Other& a) const{
          return (a.valid_ && valid_)
              ?( (a.begin_==begin_) && (a.end_ == end_) )
              :(a.valid_==valid_);

      }

      void initialize(){
          if(valid_) return;
          f_.reset();
          valid_ = (begin_ != end_)?
              f_(begin_,end_,tok_):false;
      }
  public:
      token_iterator():begin_(),end_(),valid_(false),tok_() { }

      token_iterator(TokenizerFunc f, Iterator begin, Iterator e = Iterator())
          : f_(f),begin_(begin),end_(e),valid_(false),tok_(){ initialize(); }

      token_iterator(Iterator begin, Iterator e = Iterator())
            : f_(),begin_(begin),end_(e),valid_(false),tok_() {initialize();}

      template<class OtherIter>
      token_iterator(
            token_iterator<TokenizerFunc, OtherIter,Type> const& t
            , typename enable_if_convertible<OtherIter, Iterator>::type* = 0)
            : f_(t.tokenizer_function()),begin_(t.base())
            ,end_(t.end()),valid_(!t.at_end()),tok_(t.current_token()) {}

      Iterator base()const{return begin_;}

      Iterator end()const{return end_;}

      TokenizerFunc tokenizer_function()const{return f_;}

      Type current_token()const{return tok_;}

      bool at_end()const{return !valid_;}




  };
    template <
        class TokenizerFunc = char_delimiters_separator<char>,
        class Iterator = std::string::const_iterator,
        class Type = std::string
    >
    class token_iterator_generator {

    private:
    public:
        typedef token_iterator<TokenizerFunc,Iterator,Type> type;
    };


    // Type has to be first because it needs to be explicitly specified
    // because there is no way the function can deduce it.
    template<class Type, class Iterator, class TokenizerFunc>
        typename token_iterator_generator<TokenizerFunc,Iterator,Type>::type
    make_token_iterator(Iterator begin, Iterator end,const TokenizerFunc& fun){
        typedef typename
            token_iterator_generator<TokenizerFunc,Iterator,Type>::type ret_type;
        return ret_type(fun,begin,end);
    }

} // namespace boost

#endif

/* token_iterator.hpp
lB1JHVAmXG6opk22W6dl43yH599GBmxh20bKpC/4n0HszLjWbjk2CUe8KcspklQWTpJAJKDLUeV68Ne7m1BCnTGGrwFHM4UYlDj3e+sy7sfbpP5wQT0/fumaZTvzziyrZU6ab3jKsWOAKDbje0HCxiidjiAQsMkJz0ZQdYE3l8HrnvqwnhSjy0WRH4+AjNecRPCDLGnwW8rCBt7HprpwKpRwo2XNcGawqhaLRzp0bMZikwuxRk348+NqFSYPE+a89Ry0j8iv7M50n9dXVBupVHjKsnNyIwfvoOf9QXFkebOXN7oxd2yF0q0ucThK5VRJrYr5qZvyRanU5m3EdmuHP0ud/OXFSV3BBxq/bmNC4jM/zvrYBj1Q7NYfpWplUe2fZi2GGqxKAwGtQIORda4f/XaKhA2NRunKP2Ko6z/ZlMFyu6U6NevsqOIucE9GkDebPXQS1FjgsDFk8t8lxl4NiZ2hJcZdDHsMOFN+wtF5dNAwTthyY2mlqLZrZPCh8roQKZ84QJvD4fbvF8LLByOQe3qB9WhDa0yobmW4LHpANH483UEHakpMsdWxR+6TmzXDr+4MqLrasSjgo/nPPAD9vSC9Vrb8TQjGDrebliLmRm/S8pfwjL9VqZqUA+5l4naA03s+enY/sr4EgaNHTSFPqGoZoZtFWmrD6AJEU8zftY9RXBF6Ruyd4C377bcVDWUUbj9EODXjP8cTb95JAiO9JzkClmVvKfJMSQ6OmH05NFZ7Eca8qJV5sLXxZZilUJ3LYbdNxDL8nRaydvwtK1/8iKBHSRMJfD3DvqH5qrttXxqNicG+EKzePS9FvByKa1+dY0pdvWDF4NgZt1RISaRT7D0n5sbJCFK5C5uJz7cmC0EE1ZOSJ+q/emVFFjn2+aD/8DnB1OS3j5JfA7qGWWGJQRfJVoYlkE5UVc1uHZqk20XnfvINJOr/gT/V+t97XsSS47ovU+sWmD7clv1LXjx72YqErxgWUyPt/zPN2l2Q9HPvQTeKwPUrgengZGaKDfHso7biGEajTt5ezRHSAr5kXW/yfaGJxumVL+tgIQfMVy8LxvLHPHHkzeN8GLSO7g4mCKToeOpLKXbKnDG3lT1CiSD9YXBNyGwRiOSAVBArnQakfFQC7ZWnsATopQH856ba87X9ctoGulIhMqNV+ZmRa8Uirm5NrCSvmCXxiiztg4/upQGwG5LbGN5ZzUdTGQrxrpjPmIUz2OtemnptJWhSayCU8QbgEUfKrH6WQdWpC+1xJkIG7JPt99m7sgq/ZORsfYai5Qp5CU6kgvIdjspBWaOPhHaEd3q3tCfvm8gEUqpOvJb5xyycq0shzXLiVLMDyIv1vPSFq+O4vSCH8HwAjGCiMT1g45vcR9Ridy457im6IRIirKYhu3AQL+LBlxZTJgm4P7rFc2wylJlmZ+eBZuH++NGPpPjBad1CdhbdTdjjTdkNnSJKR/HRdksug7xAdCtRdWV/Pyskf/grzbbT7AGKfmcV2FsLIcuaGwIY6pWzi3C+HWbbWwAwDdsulz2AcrTfDxn/AGX8hqzm+cPybziwbbd7LfHJKwsKtrhCeWABXYNs+ZVHhK5wJiWAhpdos8teropI58F7deUJs26R61rO2fYt4ivFmnZIYy7ZniUlgxyWw9hhf0eIB0UipNQwHgn4EVSPUXBUzv3h1hpytLMEoUN1nvapHbqaQBxVY+gvBf9dliXArLEhREKipkN8XrolIBxPNxGxPq5zgUf/3Y763D/aY5zOb2kJMr1eWcV5nCNXci0eULNC01M0ZnPBC4d0RKRQrLRlLWlwWQTOEFl9wryt/se+GndLHcYwV35i89V50P5brOy4d98tUt+QeeHkDy2jVFBz3XZl/tRatsE3TNlZyBr5hocR0OpKETfuBW5eYI9XbEdut5+quyfPeSqqfYUIt0jlk/SRNxMl7f4GFUqUVQj492daAnVmbpzuhej5TNINdyG8TmZdWevLrqLpfjGz2Dd1ohLo2fgjLz1DzFW1WyuBvczOSMfsfnqE/5BVvhgxv87Oku4Jsrsf1Nod9rjmj7K4BR5mojlQCuKaCm4m8DSQDSB3IcWqCi/IQuUhZlkp+8Oc0EHWZOKFusMx4o8syR3s+7DJLP0bYH0xcMs1XG+qOHzcYQFUHKzPBS5Fe90jOC26vaY95l2W0cElh59ut32G6GkpOJh+RkEm/g1M3hndytmMbJYVTK3STwRMBK9/d6fMaVEwIjYl73mcMQF8z+PrXv5ktj8gz6tQV69aBn0YwyzK27AoBDQuXm+GqI5nyWa/KPsGr5MCaSI/b7LPkyGdN69vx7G0e3R3LbGTgmPluhdwtqu97InKpvPSlodcBIZDAeiNJZiUxx+K6F5NIaDdG94cW33dmqHaJznf9FNflVir2vUcml5VPyBaMtUTZgrRIGC4ZBs1eL19xT8vykxBDg5nbsg1n3LjA+W7uolgJEYKkNrZCYJ4DypdUjGty/YwnXjQ7naAz+clEqi194kwvIjUe8XbbTx62lLj5EZGIKhuF0QQaDMZ6rJ9TP38UGKdybaxwigu69rjL76Ft1lQegMGjuVku+WxK2Khpq1CTrYAKfp3LrpGTznEbTnqGKDSjzQLVNMLPODCLPyC1HEvN3DWpwLFzzu04jy4n5ss0qlvuipT21MQ6rE/JaNEYHe9BUsVe6pB6qksEMRpkxnFPFDw4Se/D2Y59xPGBEYySfSwxuswh+H2EJVol/NTWJ3dfSZOBq1m/LDrfG3WLLIl/YsgJ1sCKuZvpNeCafbc35LuAr8Xq1zX4SDcTGbteQZZNuDlxbVs/oJaznaILNTlxhj2jO4uIdmEXJapKcqEnbus4ohOvmQyVnMdhufH3+JQKuUjcLKAlciPkOuY93gb+xo0bmn1n448iG0o/me+Zdfd5wx4+8ehVsfTSxpS6K4ABlYPjgMkRJx+J8cwANVn7S0VzLCyrxQ7uFvCOOPE4M7sMT15FAMbwXImJXMPvX4Qg80keCwgMO8bqd+TsPyEgrGi0Qg8D5T4hNVADKwPbgXMsXASayrHs3rL5HR/Ql8btEtob4bbM8NTGeIdGsiQrVOhOZ2+iF0/woTBgWLXOMSxpVnTefq8dfmMu3HSERk/90q81k9vdUkgr4sk4mMM0K1LFnBN8PTOaiIjKOkZuFNh3NFy5OYcbRF2aZzmhGOkqHRjWyEQgf9aanPfD0rkNvM2uCo9V93s5Otk8LjtYJSm+3RFYs7QWznG3t2VW90+a6MmbD40ucpm38w3i6ecIoKlohanq5YWEtg/ydVR8ezCQbIArE0AOIO5ouljeZmv2lZVxnjWMautKlgyTXpTBKkCcfIBX9vSdMwrSuCQM0k7//fWqpboVkFDXqnTlrjOT5TnLXxyYf3O9d7f7Vej+PBkyLvT9+10rRjDmvsklxWEy3hXYY7qPRGv1C/hBsLgf0FToAuXIjrf6xdc//7wFrBEWrkhpnMaHwdJ6BjlPQAhediAPIEAPUnhCPJjjHwf8u2haMlbk4QIsyHJzgd7/Q3AoHEEHDJOiBKwOgC/YiG8QjSrzk5Ngf8irnOxw035RtVwVSTRrcYH+4Pa+6jG3Pvq4tu7YPg1O34D6CIo4Y6ntGZp2IdLnXFmCCCpl+MLT6m7WhbQt5FaF+XdouyzrfHN7lLOA9lKZypYitTeqmJokr3vajo5C8ghzmsJIwjl5Md8+I+dBdu8//H/uS0xYWUEQnshgzGPBLSeY0FdsB64I7lV86FxuBVrzGR02iwtTNiPKnAWZQHq6OwXM4qpnl5s2cXJzOfdzCkGtAAebggiUnnFAYBqBHLEyt8uISzd10xsrOauZlmt3Wu99Nvt0s03PhWlXKVhvwxQ+3r1i+MWEx4Fgm8ONDyB3LW0NP44iNITSX4MFzyYGv8YTmx5tlQM+qG9FpAq+iiC3aYIFJnhPPjQNk/+dMIFayYX6qqodjKeP1nMWjaSCCP5DfR+sm4MOTZc6TRR1bFa48u5ZYtkeAklkWdz99E8eOcUOeHLTGSAsUciuPBv1DpqD7XYoo6CDdhYUyrPtkWuQyJGKME1Vl1uLyQ3kG4+uV5f1Kc9aAOrtUQTqtE0urpNgk2rlq/WHNwOuDxtfPPwAtccYD8VC8sV6zcq8ev5TR7bmp2UHwkO9TU0TLd1Wn1FV0D7TwdWLCfYme25XAd+LnO2QLA1vXfvfHcU4xDk9ecnLBqdvICtFSNRsTCkhF7oAQPNJgv9adhzY9MpRSVD2YI/dB9DpZ6IzI9Nvv2HCxSFBIhkFwUXFOLwa20QNcV3DFRVg443Kkw4Ih1P15CmTc/mWOq2jqJX0eVHy0MaAuNInW3IWbTx950+flUzM/bBc+OaF3PVq7BYeNeQsmIRDZVa6XZ6MiMq+O3S0CSMa4pmG6YW6+V5K66C4oosKBAObCH58PUlKcdYcbzzRrDRLadKLraZxzJ6FpbcEZdbsqGDh9MtZMwy1YmmP6E71ehEsExLrnx+EjUm/bWKzXRkQleIf8DGaebmouRP5K6y3xljj/sjYi24j8MquGvt2TWgUqN+2F4+7XL0O2+63Jik37i/LnfxeHgnHCQ/ADYTQKfEgPfTyh+kLw4voZRtDYHKWK3XBYCFJDAF5T0P55KH77EZbqhazVbpqzP9e+Mg2d4LQvinCbqaPM+GUu64l/V2tdf/BJBQXNyKbC/BrT9QM6gEEc8dopxwNPRKhY7e/cP+SY2pRdcgcb7tK1WjadRIpMZSbWK0DfBBJnVjWgR+R3KtmEKIhfCWP5yaNAhBu9vgzR6fKW5woGonbNL4TQeB3YIPmZ7IVstFuI/PHipGsoYQdM59KJBuEIYMF4BezY/bByguHUU7413Zo6e9aMLaFeb3AIfvwX47uKMiC//eNkUWjjSFWxGV+Y3UcBcKBFXhucxZtZcQ/DtuyU69TuZ0difgAvFyUOf5m9/FhGYEKaADTdSTfd45qnx5D1KPNs9IdQNRYZWU7jgwgMfqNAO5fLjUm5K5csWFAuYsmrR7fkW+kljpi5UdiERw79jMOFwwqyTxrrZHRSQBzMyL2Bkj+nqlKIjMCsvN4OLmSTCZJik0+cNBXKqKqAHc/yMlSemvQ6b5UHnnpnAAUP3h0QH0+XFFFfYdyhxx2+++w8yC05qEkjwIqq65sx4ivhIZZOELzz/Ld59soFGg+ItovQGNrNHLeK0BoZTkDcLUILbUuaYtM0OsQNV7IymFv16DUeA2KWULNoLFFyYqfGEpvN1mV+WCDu3fkKCQQbvEwShYngOZA1c7YcmwGh72EsTag/vHb7OyDm+OYP9JDGnThM6dPg6xI9wRMD20L+zG5SjN+jMfpWdqJZG9QAI3wdZy+VZc7+I2fl+5zwU/6PbxpQVgUu8vc7pOrY4gJKlNoEi41/W2CcxUTHz7sz4JTw2k/NxcUkQ3BfUU1cH+Y0hW9FzPMmLFLsozVQuXpVIK6ORZozsMeCEM+2KZsxZ1F7DBghYVOXwB11OGVMhWc4J7GYdaj4SMSSnBh9ZDWhTCfL/QSR2fSoGkCZOOZFC9Jpu9YtlXatJP4mKRsrZ1nFKTR7YGirStSlsDRfIUOCpKUfcvra3jZqMFjOVBQRG1X3Ru2NHjFQ6Lf6dsqsNoyors7UNKA5cuMPLhm1/2M/X7HYCLks3BDz4TeKT5TbEY7NC2TtyXEWhRohXEOCFTWkUrWKzLQtsVI/Ex+gau+Be/CuLVQp8GVqgEPyrc0Zwqa91wgpZi3uND+ptGLSN4aPsw34f25+jHiV2HIcQKFt99t3smMOHEF3dxzmMxfkGEGmOs9h0n7E4qpZhhC+9wVP6cJcei9q7OlmQGTrDz3/+qxiyA61iWNH3EzMzMdMQMFjMzWMzMbDEzM4OFFku22JIli5mZmS3Gle+j+968idmI3Z2J7Y5zojOru7q6KvOrv2rWui7hiCt2Yx9aKRCt7ZHiw6fy06r97IdeioloUuYB584RhQpUOipjJQ1Yxcl+AkSWlG44F0eEy1h5ZeWI0Esoetj0kwwmVnzMXliGDfwFPCagURXP2GFToqRwCub+GQYzxCvHHRXRrS+KrJoFTkWw1i3nrCg/Jx+uGRxR/StydWQMkSi10Bp/ZpaDn9HHIm+Rhv5SIDgkVkvsUcUQO3a//8VrLtpSmb6Ji4Zc+cw1n6HazLCA8qge2dCTPeR9LaypP3KDUxtY/rMNlXALEO48z/4ihkyROOriWZx76DOjb1AQHjmeB0PsCnv56nBxwtY2QGKnrJCZZWnwWTcwsfx6nUN4rrf3rBhZAK3ZRBp3KfXr8hh+CYGXfQ/B8p4XLM7beGdXKpGTgcHnuCNkYFbYyuw8bo3FYpnOwEr3F7SbQPPAYLZFE+TPQ2Hl3eotPgN1yXmHqoVH6D8C08GemhUccBN9JoaTTZ/5ydBZCEUVWxRDyn8IzsiHVOwUCllTouPlPMbFz0fotFUiur1J7D/nBiwSJy1cfHdtkMeeM0itH/Nt/3b1Rh1qzZ5FVB9h44/1yJlVpt42OOmeF4m89wW3Zvg6fOgGyT2yEbu/qma9gmxhMuemZZkpbYApYib7vgPZWaN9+ks2VolB8QsN68rM7sij8rlFq0IvDg6xDzPmEpmMo+H2SlbZM+8PlZdGgy1+hJ4OPAZFPHC9qBInjP0HvrTMCn9+Di3e0lf+El97bRT14bY3X9vDzpGdS12niKp3vSqXnifRAfGTEdqfobed+lfSLgK6Bf4WeE2mKT3lj1xiU0itLTh+6w6UKh2r+dE22Z/jfp+iq9ed3FgIodui6+IR8aZOKZE/I4h0GH+16asvZZjlgJeg27WP7lKfvrrQhpT6lDmqVCrXJoilPK25FH5IZBuuoIFRfikmivF6osTDAJ08rhSGSqYNQqEw0WT/ys82Q6OVeh3jvriTIXPGp39eO0Ty4gJM0tbU3Uu+6T126iRKWlS70rSxu9K+ri7b2F/u7h4uC78wH0FZMabU2M1VMWvU3C6K8cahwihN4M0otn5bRPe0sZAlTaJsyWdzgUGwg50LrOZxVD9LvQfvLxzTu1fkn/AzxVeP/qlJlZIiiAyK/ObZLjbi5cgxiaZVq19ly+eq/Un2CetLLHGD9+oXVonbgUzfrxbUEeJlD1gknBTTplybVICZQ8h8rm0+dyDQNxg9KEVixCQkCq7aHhbff34xm2d7SpouFQoAal84PAJGdf/9vNfaEiTR6cdyTZFjWn+Zz1RtEYTH3RGdLzU0WQQdd+yA6d2DI3PIMEYU/lWsAwc3DHxdRi1iEPjuIuGWDKaYh5Go7bpEbnnkJ6ptjytOxD0qVKKVZ2nv2/gqzytRlgDlkW6FJkCNLcEUW8/2jLExVEWYDTeVI3b4aODMJI3iLVPMkQ6FBZvLFogetKrScCpBst7rflkbj10YkUNcLw3I6KW/8rqDFCSe0lR4OMlPgTm/mSE9ddxMfYs0hjmX9l0N6LW5lK6S+5/6WromSLzlpjeA12Rmb7O6gWdpnGBhSSypYWcF+Ltdr2zuT2pyUBBluavSIzhDLU8h7d9HQu6aMFE3yq2Hi3foXlVge5AmlecOfuQd7Pkpo+5wmE5KVB6SnvUsn1DNhUc+hMTY7x8tIaOqJBiPfwoZE5RVNkrm61lkJ5lTX4KePaGiu0q++IaRJXtchekBFo2qrR+2lJKxuTeh9PbzyO85qnSRtXHCnU+CILDUfH5nl+vXjF+ph1HDdra51DU9SDthtYKnSoIXuErddzSBHiGA83BRqbKB16eppWlOIkrNm8gdC0mAtKjZtYjVcwAyuWBRldDuV/HKL+jIRBHx9bqowbRabP6EZ2PopfbCF2SG3QOJ6EmQ0Gc3be7bOl7h7DMdEs+BEd2gvFbKM4L087XjKRTPPEJgN100z4NSOXyaCs8r20T9yApBeSAxNMp0XsmAyFEtgjhVhNlUA/qvyiarLfRs5OSkUzrCmmhesoQGtxptZ231oTtSnroGqZmpel9kJjVFY+iIKSpeULGZ+WL7a2iauZDSspcvRL6YTybPbB+t9dPykIHNpspKrWw3fEcJSLFlr9G4sxbz50PqHU4y+dnehJUXKMhCQ93XuhgqbkZbAD9Qox+qioDcL4hRmCb0C9OnU0uOuzo0U0j9ig+FlWUlHgwBijufEIn1cIpnplUSt8sIl4sLrWtXcSMYP5JYqFsG05OYKI3JV8muKydVDUKZOjOZ+zTrGy9LA46MgDY2SVTma9pBdI3wL/6uQkN489sPZlouJ/cTlWdWSK9q3t6DJ+j4MPRQONtbaSmZKIWJcMzf2TdWOMF1DB9aVDYMQ4X6SVGdS/aSniPKNlrerKd0iVMN3qrUKF/OjvFnIL+EWGSsA8r0XFvlsJqZsrBgsaxtaFtLdVcbTYL4hWoKNfG/lVFPi+Wj5+FOExslbUoF6ncEQEUUQJEWSph8nXOdogdw96dkfZIEUiVCapmRu1OQRXhqTuvRMuVblBXQRUJlFUjQdcV9OmFnY5Hyu+4W7V7a6YuyXdLrO3XRJZ3H753YKIOpsGTYdAg7kWqzW+Gv00rlFiPkwdKYNkGvX17G7S9wGs/G8iJgEaVVkmoSCHuYql1A4tc7O/+Q/yLXwP1MBptvcSpFzHOqFfdzW5TnBT55w9kX2m2AIiu0yaoOR94SE/NGvPhnWhSV5jWLBJT1DsA0jiKBB1oS5nQ554Yf7ifJChn98tboE7V/gmDQjE5vODnzFGij7A7yNwEfKSyJDNlXZjRzfqN7kRZGJ371ewXw9YoBiwIubwqU41OZ5ZzDUP8AbPVblSRjaNgvMde8AcxE8XJNa+vnTMOfuZz5KY5999IsUQLDilvCoaebVzdPPSyRzC1lJyqucp9IkRCoKD7GD6jmddaSfhOJvnB+adTFrjsuWC8b6sXmj+V7lWgu9/ZfzifjCzCozqChtofVzapR/RhbBrWDI/TTgpi94msy2IP01AvtvreyUNNonzskfukF/c7qKqu5bUCE0o2NrM52M3xhHKEq1WBYTV97T+/LTJ4FRk7Y95CMXRFPKn6mzjDtD8Yod0HXPLFonpttzvdngezW9pSE7DEON27Lwg1VsEKDoyyYGNhoo2ie6dhi1wI9Nda4a8hc2ZsdXZ6WfQ+UKee2MTTys9ZoVagVRMOOEI/J92YrDL0+0/0=
*/