//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_PNG_DETAIL_BASE_HPP
#define BOOST_GIL_EXTENSION_IO_PNG_DETAIL_BASE_HPP

#include <boost/gil/extension/io/png/tags.hpp>

#include <boost/assert.hpp>

#include <memory>

namespace boost { namespace gil { namespace detail {

struct png_ptr_wrapper
{
    png_ptr_wrapper()
    : _struct( nullptr )
    , _info  ( nullptr )
    {}

    png_structp _struct;
    png_infop   _info;
};

///
/// Wrapper for libpng's png_struct and png_info object. Implements value semantics.
///
struct png_struct_info_wrapper
{
protected:

    using png_ptr_t = std::shared_ptr<png_ptr_wrapper>;

protected:

    ///
    /// Default Constructor
    ///
    png_struct_info_wrapper( bool read = true )
    : _png_ptr( new png_ptr_wrapper()
              , ( ( read ) ? png_ptr_read_deleter : png_ptr_write_deleter )
              )
    {}

    png_ptr_wrapper*       get()       { return _png_ptr.get(); }
    png_ptr_wrapper const* get() const { return _png_ptr.get(); }

    png_struct*       get_struct()       { return get()->_struct; }
    png_struct const* get_struct() const { return get()->_struct; }

    png_info*       get_info()       { return get()->_info; }
    png_info const* get_info() const { return get()->_info; }

private:

    static void png_ptr_read_deleter( png_ptr_wrapper* png_ptr )
    {
        if( png_ptr )
        {
            if( png_ptr->_struct && png_ptr->_info )
            {
                png_destroy_read_struct( &png_ptr->_struct
                                       , &png_ptr->_info
                                       , nullptr
                                       );
            }

            delete png_ptr;
            png_ptr = nullptr;
        }
    }

    static void png_ptr_write_deleter( png_ptr_wrapper* png_ptr )
    {
        if( png_ptr )
        {
            if( png_ptr->_struct && png_ptr->_info )
            {
                png_destroy_write_struct( &png_ptr->_struct
                                        , &png_ptr->_info
                                        );
            }

            delete png_ptr;
            png_ptr = nullptr;
        }
    }


private:

    png_ptr_t _png_ptr;
};

} // namespace detail
} // namespace gil
} // namespace boost

#endif

/* base.hpp
dRMuvjM7zhm3ouI0yyHpdp4IOqW4rtdnW4xg2i4u0FfFNuFE/UQGPI5ZupeauzZSBnVcJe6e2Dqfrs0Bfd17aTV9TmW35EI/9tHNCAtymb3Q79WmjkxcJsML9aoDoor583Wv83W4e8riE3j0BjGBAPH2xcxsYm50WdLMs/4hqdAb0KaOKonPjF2/eisQZQJh+DXvDIembkH56RyzA/CRrSJGe7Z23eZm+2tTMZ0uALj9CbOEzsSBgjldteH+rlPQ/ElofkGuXwd8z19uwWlmYsNzBjzeLR49fIubGA0KjhWM1iFRNb3Eru0I3LeE/FvOovqzBxGu8jYnDhMypbM6cghBBozAVqm/2J1J8e5cE908CUXjKajxIJ94mtCRTYyWO+k13AdWqn/7pG/723n53RYaTy+osrFDvylpP3+LHpVLmDkuc9TSDp3/WpP5Tz9dnjjfflpbCAKnwxAM0XAnXiHX6rxwzdH+duUm1wk84pTrqgmPZGNoSftCvbzoLkajhJ8BFCwudwSJ/kmwAs9l+ki6bwbhHxsF4n3aLmPdpde6ZTOuqEdp8DVhm3MN2QH4gUJU6GKSl6FO6qYeIoZBYqFH4pcG0E0zC3JDn4OJ6oVG4rwyItmao8tFdqL2tVXcjb3i9g68HM9RNQ7Pxa2uUpehOubbf+hmyiwSBgFMzXQh2BWPEYeRLNF1sdzCprcxT2tePQX7tudVU3Bvvepp9ApNW+vmuegUmH6MLz5ulmLnO3di1He4ry+AVdKLlrViSIbduRM7pFyPmDV8tXMnYgblMuTrg3iXwTqvblmUPGaWxE07q6oQOOzED7HFRkbMMhqyUDW9gVeUqaKu8K0szYelwrh0diIUCl+P368Bxvv+0fgive56nXutAWDfa34gzuoTCErSIbr4ofIdPCqG1RMVsWrd4BpiskizjCNTz47ssjOFBtddn501GvngOl2U20DUnDpywb5BB9XlE1F3l1rR16+bW1pqisRK5IAwuXb92KkBAsNwe2P0eqQZjSn5kGKkJVMPQHC+jcAKJBHDv7jbPk9M9GAWwRTSVYL3n7i/U3PVKL3YFsJiSkesb1BqJg3w+dsYz9fBWl2nbOUrgXTBxjGZQHD+z2uJPtnBzeL9U/EuI72ktFga/bUg3Zbs6ITOoC5VvM4xd87MtisTo1tQg0ZLxea10mreQreigw5nGKrDpreYn8LtcjwQHFkDDyG7wL95u73+qUH7aBC2n73TaTiVfuJY9AMFTjq34H6MMrU2YmxoObcQq90Q4KebcFzcuSUM/VBu0uVOdRsNYgSSPYIpIl3zjgRSrAVJVqJSnca9Q69co8MCD3cdDHuCc/Iz7bx+JImnm3A2deENFSSPGLJvxEXjbg1lehlBFkQsgFfAUExDNjsZexpanNaEhrqrM7wUXtwVnfqCxe1TV42tIoibx6QQbOWz0TW0MBzccxP04N6RxMl7w4OYHa8xehJ1glORwxmQZnPOmwOGYf4cIci97FByqBr/vBx4Ya+tvB/ufoN6Twos6dJhdsjr9/v5DJjc5m86dS9FN0RBrt3TfMWvKaTLcdSLIrdLUBcKEz+hP92t38Q8UHsjgjtPC1Pa86Yfy1NaAWVbXD+AxKeb68UCMLDBpVcnRZb52BE/UBp168nw/aTd7wnsQt0M8vWje2hiegJuBlUOmnwEZUjXL6OmGOrRQOkB5XGZcIkjfpXNJcDK+64mp0N/qGy5qMxKlaH+BlIm30OJLlzD/r88st1KxsNAmN8j3xGPnSe+ApMsrW5DNHliBUhJ9GIW3df1Rpz87iBtNEYS7Ocf/RsVLDpwmBm3ZglnxnrosdGOk2hX9mQPgSkDOkj1VA1qBzuhdI/rkK38KHKl0MTAELXuOlocm0nqm8HiwIs7cFfzlBsjIgYqbtIEANC7BDWKUBr6YEiSCdi1Om7NAebRjQaxxEv3QIeMFi/T4cekyk5tO3oLKqrDWaFcf6GA10ur6WsYvjqVOlvFFSm6CbNKxEvNghUR4O2xbgrsGv41JrGR8JrHhiOPvD0Cn6kjMOMBDG17sg11RwTVT6wfwAsc1ZaEMmJjRhoBQtRbVQFb6JiqNIFFpFsznxjWjHIAd7OUw6rSIBJhUnwXiDCccxKLNmoOsFKwZhqZuxWsmain0YRnY9ow+KGdlliDit85f/Mrcfj1Kgqh4Xlg/ZQ2wvIL0IZWY7ON1jSQp4+pC1FPbY0TVQGi6jT160S9eJtuDgla2irwnmVXp61cRdS44Z9daWor343xLFtoJkl0gUjYyAdQ18KXxif/HJww5h7ihJQBJEb4t1/SYdvBfCw2obQDfIB1nTe9hY3yT8V5eTYxL46TUYYt8r+JQiNAYeE8RnBOUQBFaFojmMerbcFUjbqINlzttqSIzl5XCNnw03mOrTWOhwnn0WC0N+Kxn9Plkzdn58ISBnlAqIgOq53nXE4rpM9UXe+/yGHJDnCuJGADzFSIyGZlEjMd5Kvuji9mlAiGz7WH4dG7iuCdztiX8EHN3Zjapjf11XGKs5DxmMBorLMmjmRRWR3Xs116EjASwVXHUYwdqQn3oPvqEaQKLPFMC+7Tys6ijvCAZACb2gXA8jecAv7XhHOT4H9NMvxHWfXGcdytk+OoVZxdsONOiu6NRljWq5cF7yUtD+oxnkY+K+246F3fdZpGiLXOCuqu0bgk/Qndbkym29U89m03ul2EBtgWAuBLJAW0YKk1ZNGy8Bpq0wRLCV4E8KsujXTtNV/ak7r8wa+6dblLJqsY16v/MdMbFsr0aNdMdJVESFJXCnDm1x31+mtI0la1mIx3P99dD8Oj51Aq970BU7MMX2qXlBubFkKZbB1J4nMS7QJY6TLYb/6tJWkTtHsiu0aSMrqMNmQG0fEMnZDnYd8fJ3QIkwMLpAkhdjqou7q5nfHz6MBzAERPE0SE0vw80O8YwxMexcblYsCN1xACo36FR5TAxrsaFOgVpG0vNQDkn/JIgfZnn8cyQqnUi+VUyIyFGowgW7Sy1cVxhfxEno6fx4BwmbeF5NA1wvehL+YswaFzSNPHndnk87LH3W/xW0IV2VHlN65kUQusdCaBZHXy2UnhTUGnPl7C8yhQL8DbHo53quNyNPuhW1r4HtpkNwOqdO1VivEmqu8aSYj1wrP78Ol4pqYJZ0HBLzVxO9T1mG2vyJZBR/yNyOBUeCNHyCO5rI834NcKvV2u9izRT9nitPJfJjp0z+Vx2HIVSw/hT0iswrMQNP4wRkfgwzQc5kGgkyXUI5YCnHX6dZzkeEjau7f3lkKL+E1tZ38Sj/YvWG+8dFb8mAleMEue15pFnfFws2upYJe7d0Fv73go3s09l+Fksnaa/Glk4pJbtS8RcecDZimvIEy3I5UkrnWFSgBSeQN8fqKihy/DPQwZw7iwvvDl8IJhYyCuJuMGA7GAsBGD/UxJR5IIcLX8UvC2IQpCdCf2cT7/WzzD9sUg48eWerA+qqym4S3KietQ6IcIomAhHcfIIx76m9j6Bm4K2fma7yjeLJMtQKdBrYSbDXjTwDya1eJ9dGCu1oR7x2Er//pLPEdDgVS0qdyc+aWOq0UrMMnBYeh+9HTwqZpgHuV8BuZaDz+7jr8HHYUZV04Ai9YBi/pCw2b5QiA9nrlcxBV5MoHNHVX5c2nD1a5exIqseLqrWIaUPnhRdrv8SJa4pqxgGIY8zL6cxh67KHLarJwfslLQ1LCQ1cufhca8POfZDjwQhWEz0SlyodcP3V+TK0RJvF/XJPoVu4Yubq04anuuih3K9/J7v8ToxBxT2LJ3woWmeBHtkniR/Fl49Xp2fMt3xIzeUnAHQpmXj/+ULwciX349I4kv+bvfJgIgXzyexJF461mafrt6/JDpzjXoqFGy4qY4Gm+jMLagVZejodzKwC+gIy8HcBsC0HbkBEyFQAlHQUNeEl1O3uHJX+reYfoEWjjhHRbSG/IugiR+0y9Iit0rUpPM8h/vQFNM8eiOmZrwOOcaVCmKS+gCH5+IBwZ3ks7A32ZZhYGpKGSefA/1xU9Uwqa0FH2/xc8/PgtIYacdehq7hNW6zoRvwztwbwpWfd7fzvOGkgFZA7aREKauM8qnte7DmcuAf4uOqUVNalGjWtSgFvFad0tPiSSLWtQBwgV6Hsvh5+cCzFyYG/Uc5utOpkogv0IpAUPAX3IHmbVnlM9YaUPscjYB2vWq7lbj1gS8y7hVEMFVkKv0oLdFgEqgyIfsoNg34oMeMuun3g7rPePu36RI/Fs/xtiGK924V5Tipx/oUAAOuU7YyhE3ohes/FIEtJ4l/JrPNc0HD7jPpZTzzz7HyE3PG3xzX4StDbR79FFPdHFWiii7SSIyrIG32el+KTaGIi2URu0TpjTSsoWR8K2NmnZDDWiLk80rEEG78epMpRwsLQvGiRTJfNBf+0h0t8cBtageKC0X8p6QFHsfr7Xxq0V2Xt18FpBaC6zUUDqQh/MU+A45zZRoZRMtbB6e/cmX847783Z7C6eKwDbOv/wK+8YBtNbYVlfDGriy+SxdhrXpL31g/K1hmbwN0GdjjC/bcbxv4G+n9KChL+F34LFKcR/i6um9JdAzQQyRqFyNdM2AFDyRW40w8w21dLNzRthWfgTWi+uMbeUHKUhmq20l/r4Smxg2WAbjg1Aat5touwDj9oBtlB2GdQTG/7FTDd5TRwpFTJ84GoCmD+i8lQ+n0CmzPHcTvt1HZz0xiJLf10ghY/AhZIJ1lusVZcRXL/4C1rYfNc0fjc7A3B/ZcHzradg/ypDyJvpOuszuen4eZHI+j1EF4UztzXniyIsec+M+EDOrRQeinspCvAykqJJiLQK60/kYGUnrC5lnx0ZtFfqwnEUHwlYMYjRqcBZVKrNZRRjdN0VLSvsyun5pou019xIzpTIPmCCcHc9TmtiPeaVAvAO2105VnCwbHqky75V+8j1SZdHcmMWpHFj8RSxNfEfXiadJnV531A3/26x6djQcP+recdRtbTje8OEXx07uGatYPmuIpXz26ZH3Gvbx34zrLX2+j7XzufAA0xMdjKeAiurVUljnYOQ2cstRjKNHEp/63B8QGejHtgKncSj28FDmfgPmGw8vHJsq6IZ3d2tvDkMKrmojx5USxgjTR9KTSG+Jk76K/743kh4LhDP0ghi+mUtxx8COJ310V5H4ubZ6L3zU2eCvxzTNdSLc0x/PLyIZzXxfb/zhJ+wtX/qp8chaeVl7ghU2Uh7kEFwElj74RtXObI+vg/VTky7BpmsZw5KSzl+d1anF7vPZtlFosZV2uqr/BZxhje93FQQPJPa7VLon28GmAKF8fh3pA35WbHhIAc+G8icwyrSBTcgNST6vNr3DJ2ABiPaboLGulx/m/MT9XwZr8R1EALziJEYGhqNFTT6xrcr6eoWNxBpcXyhB+Mbz7o/jKEcuATLATA3JTn9jzcb9gYa9j9u3PZFfW/EEz/SWvGrVw5mnLZD3nrcQJPX0Jl6LYqQhaffPVRvOCTYlqIEOd7YgN4AXGwE16vWh6v50QEncfWGShw9V+t6TCZVe33w2+U6mPSidrF5UzfyNr8jC+CVo7yfF4wx9389LpsitAofvDGiaYx/ACMjQl8nR6a1Tg5a3sX99WTx2jO53XpALllqh/sOloHogPY2B1e+V+f1e43dc7zsIPXhsCuod+hGhu1olvmY4OiVkL3/7cIem/3wrO6QfoOe3KXRFEL8iXscsPFBSMIV+SUZYkYuP4CYO9DCXoPsIoShxe/e7DWTlSiYl1aFNwK1sftlw/V7oSdAcyD/Q7r3wCiHI/UWYbuiApzFoo5wJ38rP5Om/k3sR5CYr5SCtiDdEVrpf+u8d4jo1X7BCSrrHWlydiwvmhw86NLaVcMqJMB7DJm9T/tXoG6fLpz+ADPy2KYmT1YUiToVoxAEVrIfWZ0Yn0r1HMh0dz3wbT6gMrvwe5/SFyQLEHlfdh/mnx8Q29VfIlOvI3Xs03FPcHXcQ0rZLEVi/Y3uC1gRlGRy2E9m1QcUTkU3kDUav99bN2MU/z9LEr9u2XU5kaOT9/96hiftAiAx/mQ+zk0GR4ShzcDtoCcZg79eUBtx3lrWpM7AvOE0YiTZdbAHbyjMw4SA/cF98eR3O0Y1X3PWF9S52g2/LZf29hQFt6vCKqgf70J0TI5o1rfl7pE7pYUm5MO7+uNDYuP022yIBIcjGdR9ORQqghPrZqkdWVC3aGPdH9wtJfM5dZKKi/XP1l/i7cm/h7fH1tBtpSK0bgvadiZBo3NceRlXjPcTjckOWqKe+MNTTq30C1Mede/wlsXpvKB2v+L52NsZBH+RBPC8K5EoEIx6sXfaGHubDf/yc1iX24u4vNP23avnGQ8BMngZ8/B088mEeYpvKOe8gQ9grJ90BDHHpJPwpYH7oc8EKV1D8C/+T/nqReJ1yb5z4gQsMm9hWLomp+dsLCERP1UpLcAvlM9IqHFfJrLM6U3wxTF9JKR90iMXQQkwR+aaDIEOwLpphhwry8Yo/8RuvTV6+8UuEpbyQfq2HNNDf6+h6CVR1saH0C6OYr5TytcTzpfJX4vnSqFl2rEP/pWm+6iA+Nhm/5bsUX5VWf5Th5PP5OBT6XVj+q4Pid3pLqAD9euw0eIz1oQ0pyu2G3HznbTpVd4qDYKVI1Q9uNWLCXr6DAp2jK1ejY9bdUZsACiz101YOGdVleGZXXYbnEnnGCbMUXbnGCLN64YwJA7fm3maYXxQYulp3Av7YZpb0GHP4g05ZvcniWxPxXLhQqULjhwwuO2uSRBcodOt3J+LHuC+B/vEfb42berobFLPCbJHtlV6ZImlazJ68RRz8qosfTtwrA2BGFJx0lgpeCKzeJ7JrRx86OI3RKL30necm2m+Nm/8vYCwYhtKnR4ZQWNjSauw9v2U/BokmrhLwV3M7AIa5kXaTcp1tG97nWzqbvFIXRB+nlq/+hFqmxq5kvccXYygzgBn+StiCftFvI2P2FGBQrE2/0lLmqe93aoYXKKEd6YJXMWk7cQ+HXwY0S7qlLcDnfyf8HXbhlYnsxDPsUi3NrInOdPLPqNFwOpi3hS/RWhm3yCLpOZV0kB83QHLkJSwSDysvtUpKKr+oH6oNfeL5dyfNiXDgRHLeR0ayPz5pxzhYpAeLm1MOdRq3AumxxWv0CIAlu7rEFq+hUOIhVaauCXd0T2g/aOoW9Lvm/w76XdMl6JfVdAn6XdM16De6FBPUpROpOfau0X8T7e6t0b0Ig4uSXOQyP6J7cMKDgLrDnocy51XznJB0qj5yzIR3Hx7UnswVYbjdf5QvoAcLIOmI3eq/NiWFC6z61AgX+JkQAbwWVQbZ+UgJzOnb4pqXhSQdRF8TG+Zi5/sAjgjvkQKOnCg2uWNZJLhviLyN9/5L4athCW1ZRTvcFHbjkTcyd0eeu402jHHnGJB6G5idwDqD1yH/RV6kho1wF7wlJ2RJBEPrI/vDNyZJ24p2e3DSFGj3iSxUocWkM+r4gw91i4MWIRQGxb34E4UiZgJ/xkGE3SbmIBPd9MYMN75PXhhaf/3hm6gl8f1Pp02ScW8iOaJedveWgstRml70xU8dUa/+iD/HW5DsiLImXRE44IuzXY/qFhaKgK8CCzuyHUkfcFUv
*/