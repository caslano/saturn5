
// Copyright Aleksey Gurtovoy 2001-2004
// Copyright David Abrahams 2001-2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/iter_fold_if_impl.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< typename Iterator, typename State >
struct iter_fold_if_null_step
{
    typedef State state;
    typedef Iterator iterator;
};

template< bool >
struct iter_fold_if_step_impl
{
    template<
          typename Iterator
        , typename State
        , typename StateOp
        , typename IteratorOp
        >
    struct result_
    {
        typedef typename apply2< StateOp,State,Iterator >::type state;
        typedef typename IteratorOp::type iterator;
    };
};

template<>
struct iter_fold_if_step_impl<false>
{
    template<
          typename Iterator
        , typename State
        , typename StateOp
        , typename IteratorOp
        >
    struct result_
    {
        typedef State state;
        typedef Iterator iterator;
    };
};

template<
      typename Iterator
    , typename State
    , typename ForwardOp
    , typename Predicate
    >
struct iter_fold_if_forward_step
{
    typedef typename apply2< Predicate,State,Iterator >::type not_last;
    typedef typename iter_fold_if_step_impl<
          BOOST_MPL_AUX_MSVC_VALUE_WKND(not_last)::value
        >::template result_< Iterator,State,ForwardOp, mpl::next<Iterator> > impl_;

    typedef typename impl_::state state;
    typedef typename impl_::iterator iterator;
};

template<
      typename Iterator
    , typename State
    , typename BackwardOp
    , typename Predicate
    >
struct iter_fold_if_backward_step
{
    typedef typename apply2< Predicate,State,Iterator >::type not_last;
    typedef typename iter_fold_if_step_impl<
          BOOST_MPL_AUX_MSVC_VALUE_WKND(not_last)::value
        >::template result_< Iterator,State,BackwardOp, identity<Iterator> > impl_;

    typedef typename impl_::state state;
    typedef typename impl_::iterator iterator;
};

template<
      typename Iterator
    , typename State
    , typename ForwardOp
    , typename ForwardPredicate
    , typename BackwardOp
    , typename BackwardPredicate
    >
struct iter_fold_if_impl
{
 private:
    typedef iter_fold_if_null_step< Iterator,State > forward_step0;
    typedef iter_fold_if_forward_step< typename forward_step0::iterator, typename forward_step0::state, ForwardOp, ForwardPredicate > forward_step1;
    typedef iter_fold_if_forward_step< typename forward_step1::iterator, typename forward_step1::state, ForwardOp, ForwardPredicate > forward_step2;
    typedef iter_fold_if_forward_step< typename forward_step2::iterator, typename forward_step2::state, ForwardOp, ForwardPredicate > forward_step3;
    typedef iter_fold_if_forward_step< typename forward_step3::iterator, typename forward_step3::state, ForwardOp, ForwardPredicate > forward_step4;
    

    typedef typename if_<
          typename forward_step4::not_last
        , iter_fold_if_impl<
              typename forward_step4::iterator
            , typename forward_step4::state
            , ForwardOp
            , ForwardPredicate
            , BackwardOp
            , BackwardPredicate
            >
        , iter_fold_if_null_step<
              typename forward_step4::iterator
            , typename forward_step4::state
            >
        >::type backward_step4;

    typedef iter_fold_if_backward_step< typename forward_step3::iterator, typename backward_step4::state, BackwardOp, BackwardPredicate > backward_step3;
    typedef iter_fold_if_backward_step< typename forward_step2::iterator, typename backward_step3::state, BackwardOp, BackwardPredicate > backward_step2;
    typedef iter_fold_if_backward_step< typename forward_step1::iterator, typename backward_step2::state, BackwardOp, BackwardPredicate > backward_step1;
    typedef iter_fold_if_backward_step< typename forward_step0::iterator, typename backward_step1::state, BackwardOp, BackwardPredicate > backward_step0;
    

 public:
    typedef typename backward_step0::state state;
    typedef typename backward_step4::iterator iterator;
};

}}}

/* iter_fold_if_impl.hpp
sRU6R5DmlQEmoIOYy2CfLt5ZZBgO5/CCHJXBpNVf7cHf9UNAfZFXd4CgcVf4e7FkX7I7EKw5D7kmQPIh+y/yP7c+x+XJrS3c/s6Wn8A37vmcNQUbRKnj8vml/W3EPV6BmBkF6oA9U9uQWixyk57pbarJhfu4Bq7vg9HkAa6i8+nZfL0kqC4Jq7/Ele82ot1HQhttUUNyR+jd1bPaBhNaMkjwFPAxsxJ/DgTDk84fynM9F/zyajwABHfO6ZRbB5LSJjmylI3lfzg4l8yFq1xfq1L1EPT2LdSTB/8OoVSFfuE2XVtOsCS4R+DgHV+y0ZvCHv2JqiWcewnoCwR9phn8gNTWwZ850Ne6Oh2K+oyG1SPmIKDvp3dC4SaAvw6M9n32zZc6xjVJCqBUOSNbEXb5gfToR+7KIuQ8g5/AfH8q3qGOsFTJfXIJwjEwtqmlYFK13C7jU6OZHvgz+WoDkf2BTHXxDpjMeDNCdPz8IVO7SfKpLdnM+LZUh4+cmYG4y1XDXNRD8vzia5+RptPrZM2hVSPe78Sk16gb2CH1asvL+JMMgUtz79VnejxEZElzkWEjvoo6aw1sZ2HHnBkDsmavtJYOpTQ3yFb5nDuK8twLbrpMBFSCf+U8eQI1+Kd06p4kR3FA2bt2bnx/PUsqhR3fYQBeWFDV1ldaFXh1+w/Lbfkqo+IVG76DucJBjtXPZBdRdFzgJVNAD36r5uuMgb+rc9ZSPB+CJxbQfligX1ynA5uk40Xln7A4y5YhEXem5oScduoz7dInzVIa4/f9AhzdSXEZjjtCbR56pFmVeTC8smUYI/KWAQa8ryGUr3xNHiC7eOTUmfUzo0kQWK7NRNVwuzgRMCIFSQ41uDdeZof5iwoj2YWGo/Kfyfrah5I51clazIWrUXEcIpmNf4lsQ1CsifnKAVG7evtdhoz1E7mb1GPxkL0tSsgYfQL0Tp3yDDqTZNX0xagVZkNdp5DsOIc98Z8POdQ747yYssWvopUfwZ4uSzB3bfvakbYBmXdhGVtYQLWRFjiJM2Hh7eV/T4bzAY+UCFs6BQpitqGyHL4M4GMGq2xVQ3Tvvhw1WYXjgGbKk8C8Kf7hLvLw5TAvp4gK2hWdaprLDlpE5Ul1v7MFxgZTDwE9tUaBZAE+ULVjwGwk9m0GIwW0oWgvxxmotSSNH27Qln4GvLEkHzzl9TWb0tGAjCFqjqofIeiYCg4pYuIfRtAoKUbdJCBeyyXLMAii0wQYJwl/KO95K5d2Wp7pYTf/85IrueM89BAURV1n02hiqNjeONSszvyO+yjDDXFRi26xwhIPegq6QAX8C41Ozmc2D+YiuL/uzNz7lxWlS7dmzOl1cwdOrT6rbVYbEw1dSPXcMmrLBHmPKSh5tlTsy8DiFYh+TeZ2a9T/UzhgkInzNx6jgEGT8xht+U+B89ltfnHnK17X+fM0qoKsroPkhHKb763F/bAuN85xvUNyEEPBGUb+pWXNkyd4xtg7uvPahlkJp4VPfP7D892k3fcMXwH06shi67M8fYdbWez6Ds+pNGuZIyLotI7f4XrgjUMUmc1i844fByg/3bbCdWVh5HpfZXZfhQF8xv91T4ATabHG8Ar0gqwl/8chdra9HEWkfl0JCpzsiB/SOjfvSS3JR0NB5QhEciaK7JsXsHP9PgogR08c2PUH1S85GdOweN6oy7xecu/aychpvfosReeq7GewGpxXaRA6hKZvrNtXRDWZYTn8UG1ihm5Z9cAtuRxgKs6Jlnv4HalL5qzR3Sp5CK3Anqg8eDWg2tvu0KUXPFAZL0flVSQQ00wkgvAOaiWcTEKVYmjvBTS7eIi8ILipTnGwfEBdFHV3tcrftqoaFhoNRdqR4wI1w9GxQ5DHiwP2S3ls4ZEQD/UbAilny5LqMXeVbmeahMNl5HMCcZUAGCw+Za0ncwnwkwEw8KnEA4ifx4PD6tylMzaV4/zcbcVYqcwOo3uIbaDFgWkEVBGiJuRKYnjC2LNcGizHhCt9BtEtFBq281TxAdSlUKb3eQrR7Kc9Bdzz1Wn9j45n98gfhArnFo2av5KXVHkXPV64//wwYvSKEr7ySDYmELZIK5vfrNsfK7cfTIZFC0VLmG8GvMruqUxvEIwP1//IH5v7XqtpsXojS6e3pL4orRKDAY4496s9/3O2T4yIG0ZGqdG+w7f4Fwjo6oYLcK0JCgoZA3e3uYIes0Kwl1bJlVbSsLLbzu8OJ2AM2UVhun5/Xg1hGDUQxLlnBiKaJLB5aqy9TrY2GV1sIE2sLfPEd1i1rAN1+heGIiegjI9tqxjpb5ZxHToM+/Ef7iS9lBxjJIwIrL9Jo+mBws+JJdunkBvlSK7bjiT7+axFASAeoUkwMbWdA4tcld/GWhY46yezpjnOR+RFgupVR+dgVE0WIVwA6w1Mxx7seAGECMHhSls/9upJlYXndeMp+kdZ6DEZ6ipt1vnrumXrj7c27hus0uokNzXHL7PlSO//7lhnZfVD2MiLTZGZsl13SnUtXpfRu0+ibVraMTA+NOBC5zZQ2jEHX8A9tfbIUkRN9yg0X5R1+oVGIjDjvgjZ2g1WA04MVR7YHWmy93DxTQaoQILA+tP6W1QmA/07a9hSsnURniyGICf3sP5qFzkew18tulmnYWkAG9m+qbqdyWCOIIE54XWKkm+cnLnGsZa5xhmuJ8W9+ywMBynTWIZEE1uF0cQSmpLT7r0sghGutpKdgSahv1RZ4NJAnlZxsTgAjGR76niZR3xkF3j7OIKKbxY9KrcTVSMRE7v1/2SWalmwqXU+koFda1vZ2834cjb/W5VWuvPrfzgsYEwa4q8+f2uGUI9ASAtAUWYrm2Vy31lLExVziUp2JPdodtxbnpbBSbqtomdwBQgYnB/g0MECdown/NuDjKpbZ5q6Hjl9reiRqyhrpW1vnnCfWqsMeOp5cVsLTwNZ5JxeuKdLqor7Fi5oJX0zeWCxZ47tc57KjN5zDfRNLep8b1LA2bWOlVCBH7zs76aJp99wxRpyv4LIlUgSkRyvcXI4V1BtD2kUJ05+nEF6n1gaw8MBlCQf5KgMWCvtmueJVjsGutG0QB91KomcSBtMqza4MUytuaintmn6MYolZfzSRyWBPonbI4Mp1Y0hpSiixc9ztYG60PP13orx+ve99AvHTVIOhLohZ/dLfmzZjOOYoN6DhGWQWtdlB64Gd6ULCFVvi6IQsWosa+QBAT/PTVHofGWuyhXZI6sSmVcfDMogd9mNF1qb2tmV14nZc7bos2WaOqWpwU4D1QGzOFdwhEtXCCyEIsglR9/F69v4ZeuIY9vB5QvpS3FliO3m1JOEg7Z4Grj+C8XRWrBKJtN0q41jPmI18MGR1zaYKdwFb6/obZLiSrrc4yXFbevPDnyi1MwAX/ADnzW5yE3G5Ke2yJdIgTdi5fw5pvHwgx59h0H3DzBakXi/JdN/3x3I9PLiU1J+/zkSFsJKsxvMRNBsLkJZgBqgvi0aHdxEwObr3crfVHEhdZyyH7ZETBKZvXOXVxVyqFr8tF6tP6Lp0kvPV9PrFhptTixcVNBBUZWfk5t7yzphP9n0MLmma+rhTWx7yT7xnJ544Ppd+etmlRvEdHD1/d/R6b1W7YKiXF4Qlf9qilqK8sop+7/852SpgOnWGwUgbV7Hp5XhqYDzO9XO7Wek/sgChzu6b8Ed7aCBV3kmehwKkZ1n+6YqZUw5X9sFStsIfH6KfsQ1RKtCjnuS21eoWoKvjOk/Pcj3xFlSYZZ3m/5WtfBUnGSuYjbiGsBgmuK0k+d/MK+vbOy+GhKSdtjDkVgLEsZg0C1jOyyq82//auNsjHVsIq7xILEa2TLuGYudLeCj0hjcmQvSvQORQytBLpOuZxp9KhTLqMrGlzUwLJV5w/ioHmwfoJKKC1YOe42Y36OgQM1eT65GXv0RwNJDpXwx8Edy3bjkeQ6yzrB6houT3RAj3KP2xnnZ2IaUcj3w52OD70faCClIIJIq3ErLjRjWWkz6lOWrT+u2nn1yQlGqwa7saIwqMwJAS2h2iyPlAxmneVTyA+nEEiethdgQ1+dywxzBYknhQpPADMiqh9Xy2TFHwmagDZD+I6ECYiSSTidiCJhuacb4olzzoAI3DNdKPsGDtb6b5gP8w/cNJ+YENXXn4ufw+eH2o4MnzYL7ybnOsFZ3o64XFhhinjyG58qC4wD6Upt3L2iXfTRh+xSAjbQzueVJb1IhlX33jKVwqPXyfWZOOw9spfOYuWlpinVkRZK5Go2PNOPqLH5+/YCHzHmJ9oM0LhmJc32Ugc/axy//VDNI4nc0IsZFlAnC9UmyOswGQlzkq/+3NWImR4w9tLEGfz1mEWPYrwK9sr3B57LMuqv8HkBlTeE4GiyZ35k8MzwksLK8JbeqmyRg6X62eNuovT0tEnZG7xBsOGhjqgKmN1SxlhiA8fnsNAx9Y3qOlmVYmhQlRq+68myD0d58QY9Zzt0LiKmE+KNcdXo7eyzwjSntkefc/K/v84kDd16Xq8xJeiHiH5vJvaEZePDcc64bbFmdJFKbGNIaDel1sS2zxEaX29E2+ZyTq8fDs3csLXy5r+McoC7N7L7GmdqIVFm2UgPGsYWM7qzUuC8NSWdxod3kLnDGhYWoeCYZiCvCNFUrCPDSKJisqzIRzulwe7nw/E5sIXTZAY8yqC3nKlL9aV7JkFa4/HtuoTsXeEhkGsA4sDk+kMWkrwdFvNSabOlZ4HRvanlga0LTDMB7/X5H2FMw+Eh6wnqx+iODTH/RIDYQQrHrqwdyMIs1aCbb2pZuLwjoWD4E/nh58zfeGnd+IvfJ91cffXw9aFi/2CUcEGKXWnuBS5EnmPg/BFMyKmO5u9F7DauNV4FtLTHilMw17yPQXmpF/rEaKK6mzma6XqbN43PP3TtfrUbdKt3HYF8euxyKTYdl3Z7Hapj0J4vNvtZCsqGcgfZ7x3TiAI43/qZhUsFctwEhnY/eCUraCwMvhLy3XYxKr9M3BZsIIjX5iXeqUbpeGcuffFxFcHn25gxlTrL4Sak++vRIwY0zWqEZiHbBmtlRm/eOLkFU0UcttXvzQiSB98oPo0rn4O2SAT6f9x24Dx41W7G49MSGdL1sWrrOUl2EYA1hiatj3F0+/z42lqZ5+WQcxGTQHjmMhSEvU5OuU17A7l/C359nuFtigKN3S5tK3syheINUry4h84uu8TRUO4e7T/QAAiz905TevycrMX8btnSHmA/GRVxGVR5Zp9xMUwMa+1oiVmqpjYyerBaDFazSj86fUweITtAwMR+Vj5lDBrHEMpwRoZh30vGn5ZNx4lgiwa0wcYTvhN7kuYMx2jsapMgaihyXG2EU44k14kxp0kABa2j2QRVv3iuOy6e1pWtKOjyf7eEVZEv7HhJb/dqRo/40CufD9vWn2GxoCeDsRCDgxwoYhj//dhQE6QkYvK5nDF07lWLGz8RbYWDGVR3XkLOVpI+Hat9tdpRhQnxMjg7EC7sv7fratxG0fDtdB5ltcp8qRpv635Wlep968ZF33ez81w3uPQ2STk475LBdSfI1gtZPEup6q1lK1+8f7PB0JTqsNy3N7l3ORNsEu7LdsVAsbkZi0S9r/Tr18WF/Cr2FexJqnJhSETfZPqQSC3EWebDmeFZ/pKiSvCnF2PmRWsbkW/Hl+5z7Ng9U9sRzDKf93vDP+9ItdET/gVcfiGS3HVvJTqYstoxJtuq+fQCSOuUUo4xebjxbvGeWCGvbzojTCtGcderPzg6/WvLcge56J21ivYVjiByr2mI6TiZ4uXUeR+qsx4WTo7gZSKHU4c13HHqD9aUEDCOIXSjx8kBXbb4xjf/8a868csNdd5kUZuAxACZiLoRSF/w2SVvBlZufNjqe6Zc7OJcXIKkJbgyEDHnfzL10g9bhfS7smJ4Yb+DNTClphtuH1ud7xp8Nnw2kc+HMZTWY8qnWn82mQWkbfDjHukR7SgarLbF+Ott3ckfV7dpZTRiiTTimqTZNvY9v1RofIb7mh4MAzJdGnCodDsLUSiwf/7ly0PXU7Fg54TlspocVjeAoHZ9vn2Lz5ml6BhuRfeLzv35VAVoOaWfsm7C2D64gWqwC/8w+KRokk8N8T/fA0rH4dvFEUYk17u7eogKfvYF+qpcsrNOzgVqSgpxvpYV9evYMeVwm7H4O5LA0aFTagNwWUF3cNbYZkvQIgStiCTeS9YYjJkOV9FrFfN2zkpM4hqeU9WqCFuijjtovK9jN0Mrk8O3yxRWz2l8keTf4xyszH2NCmiburLiR248C+cYO6DP8RMqreGuan/SJ5ef6RB+J5s1nfZRA9A7kHbv5TNPFLrQOvSINXyDjLw7y1orhHbs4kbKtR7sLxh3EBmFicgjCdJy1k1bUv55VuITrdKUqcckKv5kxytm26o07EITrq5kzCRkvpbsq+oBUsAeiJfGjthE9YTJW86OL+lRHrEe39shYm3Nb5qJ3Emo1z8DFjjJaQ3kW+Plv3jifo1HzQnPpPkklX7YdOwH8wnBx+sxyQlf8orYAF1Ycqbk/vI7fTWmm3z+a1iMAEXez4ljsiRA6SdsUgjcaEjLOfvYixMhWr80G1D6wg7I8twWhm6lyHZFfp+AnsxswBWQ0ei/VroIjD24/k90n/HDDxthsKmAMNv6nelAV37Oa3C4DNrA4T3PJJVkNePsD5/TzrXWswlk8bnBS69PXIzPhM1nrpX1kagDXpc3FaTdZmwvrLe5K5gWMzdBxuJc6SvNC5TpeK6Bl/VAbwUksfIyIBH+TO/mfKqKLqOQ3K9m5awSYAx0l2MVArxa8mxXsFiRrkPAxErb9NiQiJJtMb/VLN/AjFc5iYUibNYEAtjf3H6/7TWrW0cmKko1Bdh/p+85P4A+fTvm/MW1S96iAkB0ZKM/87NTwMGamIxtunwOPf1rzOTzYhHikWnqZ59fo11kxvSOCJoyuipsn6MK6PMG2/HUXBFRvfmBtdAMu8G371UCpVIO7Qzzqqz32gIg+U21aKnymgDYm4isKK+wT3B9fVtoUgg1zjKeoxNCoAooEe/5QgOITE8v/dO+2s1JK+k148SjLeqfg/alXXknwjJpkyvQlGl+zI7pxTa8RnpbxbY05G9gTU2gGIeApHjHbsXylTvYkxLXfDW5R7phSyI2M+hSoAR5A3DuOh1wVXiU8zre508fx8rVg2vzgKGXd0o8s1tdRAb6it4vWlvZZBCqJkv03vAYjxfOsLxUdckOaHo9x2N5fo39J3Qn0kyEJu0kjnhf/Ka4wwPbKr9MKuS9wBCzDWDntpzulQxe3AYZgfSXtIyJvDaV4HHS441sQj8LZgeIQEJXL3okWPWycZ5VA1mGwS2GfAk2D4DJEUYEPv/nOvZ18VHUScuM3QYXup8kUwkQ+WavKg0xd97i5E8+MZ/kJanTYlRhnxcWAOLqgm0/MrWSXDU7yKI2wI0kgPubQ8I0FfjeNGtwoms/bVQKw0HK6s2fLhKx+Xylb288FsrWPek/h30nwuMu9dcVUhJSa+fUSZBDQb3NeczNsKKZz4vqic+IFJ25QqNVsgDhGwKhO7ocLES3sjGa//88XNIRIOUHensOtKlk3EBBRoVF09rEek1AnalBnLElX68/Vxik6tSGc3gzuwNHWxK1ooSmXlMJRWLPUJbIgFPKxrBmpQ+8OETy0SnDAvisP2fKEMRtZ9EkAgZvf/5d593x8Qj+ksLbfITtlGbrzZUjdk57I/zk7jH3k03WSQwxQ5tNV8hcBXcSdWodkmEVkVwfHaXkvBd7x5zWPZx+6G6iMDk2crvtp1Qt0WCMA6WWpfYZ+botgFJMo0/gtQczOSThLFrszXBNthx+dx4KNpbFYTnuG1bHZn6PPOMZ6qXnl2UFLdVedEt7kElRTdac4XGpnGh6oZ2UGHEmoxH+fK658FFSsHiLmCmqDoz0WgFVBXoFrWA8yMyYhZxA1vxwYeP7xOToYs2BIqTwnZHqL5xFI4F0RNbtXP+TvetNjQ6m8l1S6Fn7myTVGGSN2JVZHZ3HQaNKKnMr0jpXCrr/Y5ekDm3F227t8dsb4o8gzLFCIkP2vv2jxPR9x2o8O5beqcr0QOBR3uuwaNxTi/lTPj0i6UpnWi4u/95kYWa3jRNJuZXzq4QvqKoDEq5B8j7S2spYUKvObc4GAlVU8hvqxdrwkG3aCRHjcyLgz6hLOdMWd8IjbJnb4t7DiR7X9zczZ+pDrV7c/Yq6NyBq79sqyNRpkRrL2kVRJDvizN8R7b49Lr7slxFP6MQNIXOiX8H1/bm4AvVLctL9u337e2JdnSiZPKeK2Yxvo+WxUcVWwCeJBVKKsoyO6UCAgqbhhiN9F2a89C1XhVAE7X7OIouzGpKuTJyBeEXCPsXor53piVneLdwUIyZvlKTdQdxsLCnGDMQR4my5ymsDx1McTpXNFgZKirAMNMozs2BaAVLa1T2NGPDxgjzGg48w8frbkaoUTXmRdgSXUVymoefR33ASxS/qs3gFCKxywjN7OW2weH690GlbanM+OI1XY8sItLvuMhLqF49M2cEI9IUuKSu/63l3r7+Z7vnY3C+Kz99lpvEoRfbXHHRQBC6zgJzwXvySOyMC+7BpBJ6A9/rZHW6KOSATqQr8XG5wYHEFzocsZ6gLV0MHbEp5Lz2WwMrQZCzOGt/UpBcFOMq3S6E+FVd7sRdS9dFBT1i1jVfb2yYW4TfBGh+ahobiObLZEkB5plAXEFayqkehVQJwOj3C3IVUYf2EfMQaXnS4tFugSC0jNBoWoh1vHYfhwXeRfhvW/D3EgBc/Ct5aHj1nCIVpwoEeosahpi0xwwIZffoWIhTIXFom8wW0W/es28TWePua1K17v6R0s/unoK4ln8GpQ/e1efX/zDE1wW1JsexHx5FZGYywdAy2TjVbg2Wumz2JjoAnfi03UNJritffEd8hLWBOCK+V2zBgC9s4wyAR9mx8hWrfktpYjabNeRteWHDMDeXj3z2RXexPgr9+UC0/UDXiY+A061sXq8bjel0rNyr5kWpuqeU07tdpy0+0l67VsZxvosEQC3UYptkFD4wk72g/9ZdhrBt4IyHf125zV1tF1ulGodG26PJ8qPanNySh3hNg1hfEMrrL1hR8/KTYf/H+3d3CEJ9tgked0TFfYHdVBcqiWo/Hl6TRjCBdvM3I=
*/