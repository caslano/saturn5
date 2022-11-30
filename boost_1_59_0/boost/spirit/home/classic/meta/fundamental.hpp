/*=============================================================================
    Copyright (c) 2002-2003 Hartmut Kaiser
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_FUNDAMENTAL_HPP)
#define BOOST_SPIRIT_FUNDAMENTAL_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/meta/impl/fundamental.ipp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    //  Helper template for counting the number of nodes contained in a
    //  given parser type.
    //  All parser_category type parsers are counted as nodes.
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename ParserT>
    struct node_count {

        typedef typename ParserT::parser_category_t parser_category_t;
        typedef typename impl::nodes<parser_category_t>
            ::template count<ParserT, mpl::int_<0> > count_t;

        BOOST_STATIC_CONSTANT(int, value = count_t::value);
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  Helper template for counting the number of leaf nodes contained in a
    //  given parser type.
    //  Only plain_parser_category type parsers are counted as leaf nodes.
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename ParserT>
    struct leaf_count {

        typedef typename ParserT::parser_category_t parser_category_t;
        typedef typename impl::leafs<parser_category_t>
            ::template count<ParserT, mpl::int_<0> > count_t;

        BOOST_STATIC_CONSTANT(int, value = count_t::value);
    };

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif // !defined(BOOST_SPIRIT_FUNDAMENTAL_HPP)

/* fundamental.hpp
Hxyh3Hug7VKk3kc4jRjzaSGRvcP6eFYp0nvepLdv66Sjr22xrbW8PYtaWfKsMmLXdipC/OVWsD/CmKT6/A33FhhQrBEctHxbKYJISD+w+sAdLP5N6Ga/XP5gbfCXCgyI3khEXNvmfk8ZTyNMBFhJeAFfU/7cmbsM5T9eRkYDJwO4n2agR7MH1sFB5A9S90z9r4zWsLx/nmBJeO5IOa1eGqKt/ko2F4VARSOrEnPiq/5G7xUCyNmZlbnMEmeldG7Ir97GNKJnb3lvw/0n5Iy9AksjDiWVRlh9r35lzZv6knzb+TELYYUTtKyuGkh5QlVoGy5+8qrX1aSte1YXp/vjq+u/0OM8gXAwQVfQiQv+3FwwvgMWXje+6kVMxC49nNwZ8yAYY/EvxohdFGIAU0JaAkRjWwWR5nQr4QfqlmisIaNuf12/LqFTdZNEP5jKe0vMY0e//Vug4slJiQJf3b85RFnqBvKicMJxt7fWkLhNNK6Ex++bJdbMsUVwzZ/E9jF8g9UtRa6Il98ZXiztTeIvI6xG2/Z6sB/I4ZiBbyowYH/rZZa/6JaupdStgTverWAzaSDmMqY0nvBXCFpT6Hhw3NrFGqE7SzNeIMoyQSe2cDBPMKgrvdvu9MQS7xZ3HrcT9xjDAu0m2GUt6NQHThOIJvlPJ47vV6xu+TUTS5ZbYX+KQKxD1ISvSt1+3a6nUqcUt9LzaEH/0GLJoIO6E7qkT9H9Xz9SSGIEoV6HFv8lO4vX/rldgNT4Sbtr6znRyeCVVyjWfqeMYT5A5FVRpjXx1ph5ECjrvOYUBJMGc5Cwo2Be/+BUVYm6Y+FAVrFRsTXNmcz2RzcNl5sYrT8l6hh7qrvo6rUaT8JAJngLNzcjmSs5lNec3tMPQa1NuhawAOjFSKYAwN5uLDNTCk0aM1JW4BZPFF8aRekvRIofiJu9JuD+JvsfrjVGUQyNUP1TsVsOUbSxEJ6u9DWOCcxOzNWvbt1+a25rJ2ugNdSdLsCa0gThWChhV1U3//N1jQOa3d/v1LreRwuNvev1xHHryLw3zSJ3mq7sm2+YaMFJ5zKty/5kgsHv6quByuOgn6vr8+XBo183f5IOq3dNPz/CYlhsefpwlEGu38cEdJOZGTXqmQpxgqzf3Xmnynx4aiNEzHHM3MaOx2we7bL3OervaHboM9mPXIl0ZvzIUUnuZQPpBK1ibQVBoRmrD+ZloK2olgvPc4eq/ENUyMl0aWBNFl4tvwMt04/44SV6U8rxefa/uCe+XgiZO+4bLJYulVO2W/w3GP1fBToflvbrYaoWjj22g5XwYfDpne9ctdatKb8QS/5biWFQ97lfziUynzvFfOFKhjBZ5vNawG4JlxJUkT1dZvNgmblDWvCNheFbxNkeYrzk9EJCSbV1w1WX/MbqDiz6ocjypVAKMD+ufztUnUHqO7cqwObj97QNEjH2a3gxK90ae7EKhrmQq8YH9+GcprY6oAROFQYQFzMuVOxL1JQZgsAVH1fLETcrKbcmsciHf+5UHo2ic6vKsoRQAvUA63pB099LcO47NCXlfuANk9fIush5Xl1ABeisGTWyeaOQKjcyY6dSxX+zqo71jNNn6I6q86JUp+GhAue7RPs161dkAtO7NKHt0ZIR7XXnQIjWVkdE+2znU5z6uReMLnGnpf9M/PxH0o2ZhXTV3bCAohusnputS4q19xdNasLcZ88+tJYLh3+JvHjc3DP9awotoTcPlGcuc/W1tBx4BxJR2SZn5dFa2iGvd8SrJQPyfFn0DOTuvE/DPzk5urF4qJ00rI/p9/99ZLZife7zPOMiIMHjNrQMenKBvXTSi1xIT7qtt28GDNYNX7xGOJPa3N2QucisXWQ5Tnkk8fuoqg7dhkU1qWdm91k8H56/WYy7IFcn3YdUVUjUn8zF8XCO5OzcQGsEabSriou7p7d0Z2U6nBddLnZjyig4Ks7tBJw99PAreZKfd7Ct9WtL1VS3BYmfxSY+jNzVnYhMnl+nlHk7Tz9oyfF31xY8OFzGk0jJdKaorALT++roY2XSRQZq0zlBwwHprOcly2q2KicMOi2KC4pPXe6UtYC0I0Tq1VmttNys7pZP0dC1nhGSK13GDOkLdYYBRr6ORV1ml3w9a50KSkTknImnD3pmZiNMx3jSh42GHfSB99JYcyIC5jCqANCSzcNB7JwbLBuiPJaAvV5z+ruC1w9Ft6jnAU/P69l2Son+2XGQ9aPkKudHlJin3oLYlkyjBURWejLoBBxwQc45gkDkwh0m0XqZYui27jY3WeaZkWmJGd4PBVsSzJoqLV5fvizWtx1rwKQZ3FsQBZcnSMytSzw33Ls4IkWzRKRWKPFttm1MOkHakYnMtufFhWmai2djcj13g1ot2bObtN+tWF2jrFiqj7tj6nb5yiUdz/DcGgKiNpym7OupdpAGCnueLcwqLJTw6G65OIW8Ea5biDyRCpS3f0Eb7c/eoaBuSKlWGc/dpfKYCOlkd0AnsAS4fwXCiZ2xhHJx9UI8tVCjZaUH0MTe4o2gCMiJK6OxvaVkROWgIFD8+rn2RXYCEIaKadqUp0mQvYbtgBmXS+iM1XH52KpWinmPCaf9awBHJwnmTMR0fouJj/6zS6gKUUNQj8rigKmeiyIqSzOP8kVOqASVNBd762tmLQQXHjzZhR+bK0W4/R8NqAtTi6j/QQwKtNitf0bzkdne2RentNW5DtdJs3pJW3czjb+daMUS9X4TgHxQrrsRwQzQT9T9zRhb+NVHGNIpp1O8nFhGJqlNGbzxrz3Q048gdRkhbYmGm+s9GaGAeGKmIT6C0czMo5wQRT6PomyHh+e0o7v2isbqFi4mIfUGpKY6WyOsKejwJ7Y1zny9cLuJ/2wdvla6/IPot0nydop8DgiO/49JvwEPAqtLDN1YNPgmnyV/RvVFpRfe5maK1SnJPA7hVzcKsNv3zlRZi5YuCkVpI/8xykUvJb+jvMBKZCqC9WXu8iK5KoakQKXb87zCraWnruCjSyGUCQgrdrSDbKYmYtHviWiC3pYaicgqJt18f+4bfmtCjyUv/ndZ92qguOZIQ5kKMSc7FTwZG9jKM4GuctSK6kvVny7/g7KDMzoIdwtTmQqtOrI9uxELQhVj8F5ETjx3OqOF8Pux0OHXgho/LsYjfaGtV+xYnqw2pIxPx3ZSW+7sWOfsi8jXQZ3nR01qnSEQpgPkr4XjJMWsJqmlvX4LaKP6U0hp83Gyxo11vQtyeRMnWVPerAT1D8zJr20PiXFUTdocetc3pIW3KEL1kEUJXo+8MerA0MMy2mZCL4l0u8MK9Vtopf/Tln3um+EXMO+3DrV90P30JDX8r3sz5s6K1Q6/rs18x7+PJ+4Bs93HsnZmufFs5nH1z/NZjr1XpXrdGECG8u6WZDpze/YBJn65FSYtpW92MaV40LIy08gz1GOQzvVAd3DcnNB47MfyIbXdp6v11Mx+e+e6A8dNUlui83n9ochMym7m5m6M6exKiU7G93iBbpwTvD6Gk6Up5Z53luVUxcPTNkTm0r6BMRfTR3xyeNfta7fU7YaQuVg4Aki3QKx8N0FOD87gmkXvjZYl7tHOd97aCwwxtPNZ/krAwOFGlr7YJ5cVDosCZM3RVoXHyQhVm+dmK+WxkcmScBaN47gBMvus+y5VQF8YALvabdH8V8dpwcFSuZ+bY4bPn863AScnMGEZMkGfMeh6jMPcqlsgIqmYjusm4QC82xJ432+bmSR0Pc1WDjV/1fnoltYEiB0QptFEbFwBOhsFwwm4NCkS4U85LhbGFSYWw6Og0v4X5OMA5XDc5v4mneTd5P0KHayx3ef5sTP2vLM37mXFqkX6Djp+PF/n9JRcfG08e6RC0zZwHYQwG2+3ERM+ibuyZn72mBh+mDOJIADf+D9RWyvZVgROfOdzuc9Ss9Awe/1cvJAmb2GOKNup8gFYPOeP8o+cP+5YQxH31YUNc8a0i50thdJOgy7qSsUrP+5gUtSRRaQ8ftVc1E3XkSYfAXaEMN6hGinX03y639xq/q3xOTKC18ofWj93DVey0C5QSV6vnEed0Vc/zeVlyVAGDMfdAB7dd1lEAjPr7foyKjl8xY6lHx9rK03MO9b9xzjATeorNlnPrR6/TwvSDlyppJiuesE3BBZSZhabotez8jKNnRIOm3vRlH7VcUs5tYHKv7dUFrzGeSyedMavAFcuLcfzRWA64d0EV5fjUWj3mfAvmz+Q/QNN0H31UKc8siegJXPfsWfmbmons/fiG4+pniBo/cSOfOIGLnnnrVcOTWXkGRnJgVVnMpmbxdcHL2RC/UKe7kc0BswTzdZKXe3tU92+S/a3dhltD0OI3rGnuchyzn2VsmRxSL1iGD/1Six2UloN5cztn/7X7ojTSH5fbMt6K7WVlWLWDrdwcWw7uECMicd6sv0whOhf7csjhxjhC0Yp1sNm7qt5d72UGAsMI4MfjBhGN5OTR3WTX7+e1hnVZSnSyAbOKSwpPzdxlPU1vzKUw9/FonBYCKt5V4LVYCk1gCUg9+4bGkOXrCU6fr3L71uiv8MHOIre14q4ZREC/vg0OZlcrCr7mpO1tbrlYo00oUQnWaIMtNe2D26CEOLt5a1FROWN0cI46KLiQoTVoe0xhufycOniM/VZk7h4AK8w0AtiLUiBHSsLMP32YCQboDEQmovyJ5QmF1MvWNUSa99e8qJOAUF5LgKDP450TAcVFrLbp7wKHN9sDMfIvCxn6B0hft6Mv/IgmVJaLClx/BAgGBe+6s+OfICliTpueDtOxd9KPI2dyK1SD7KOHF/m4MZp8su8K3A8kzS5MdDwe6wHrVdna0incL8HXSpq+VRNx87UW4vtZWEEnTuMaUmDCxG+yW2WgZ0wt9SCqf4EKbEXcxWepyW1fbqi/JcPO1rkjD4jo+J2xc8eXIxSbl9CCp7dNV7V6SJ+YOS/4BDhqYB/pViuBrK1L7uXLmdbmnPjpg5VhhQ80nS3P0ZYmncSf4d2tLwthTn+EZCQGo6OKDiIJP1+X7gHNE8IVN6fM9gNAJfRl0Isineu/noHBXAwXh0YAVyeQhbU5/jJUEC3VrE+9A9yzL7neNaCVRnyd4lMiYKEhmhsVxf0pbCT3e7NCXyVnANhZapiCiC/RNxfGFvQ9Vt4gcdHXMY4Cc+3jo8hb+dHEz8lCgYtTNZ5gd0+gKkt5z53HYcdou3tb80ZACMc8dc9YiPehMqEkdZiQr55K9OgpgIo0Y1QKPGNCBbIawn539TinPMP6A8EkRiiXePxo/K/5sf0/Mfm3ZbsgFiiwfs0WXNAS99EizlfCYTrUERe/K3PNz8BG8iA8AAH2fTyzDeGAsopdEo8SpxMVLF/+LE83zJSRT6pDrAPyF3GiQ2wDmAq3/8rm9iTtwDPE7ugRqQOEB57XFlpABDGvarpocXLJBTD5Kc7JxvAHfBInMmZnVY5ahtLyFkEJdNJrAi4fVre0Vk0Q21bf71QUqOEfTiJCqrogrLCi/EOxVBBUV3m9HADnMMGVFBOF/ItXATvsBK1Tc1SJGxIMU7qvWUC2bw1xrVCsJSZ5TjRvBr6NW5wh6plNen8Afo1ZnCHkaUb6fx/zHX+L/PLpDgqUFgXLRe8H/cwChXU2gVlgKdjH5KiglK7zDngcziHBKigui4kO7wN3Vc+w/nPPAP6tUOwlL6lJsn8NMb1m+AOBcvqV/Pl6NfGwR0alm6v5rNKT3S+WF22NZBBuzHTMgt2SGk7Sj/mVFtUzVoPzwCRv7503BM1BLmHG4tIls1u0uoe3HHMANULjd3MC2flDcp9DqgazOv1K+eqdA+UoFoHfSzqzlgXe4S7PrgdW2zEdWyPBzDhGodwpM5fOYyv5o0tOMjtexUL8nbuR8nLzszNIa9Kf5ZIZ9vM3RPVxz+rVzMQuqGT9WkXrPW/lC5MCmtld3ruJt6GtINk6YR80PNSukPy3ff7HfMOTy3Gct3dxvWkqTZ/WjDWpX64uc8nRurKCeqfqyQb01cMDAuYH4KELttIWvHu34RDg8AFl4QwP8hPi/IJAr6kClOi1SHtpMMUK0i0a7SNkZx0h5jwdxr9XYl+xdp+km2jzXcLvuFBZPd84UhR7u8z7MMJCTaT0efC8+8WsMMhaJeivatKEFDB5WFfvpLDJdFEJOsliXpQmiLP5G4qVYdx/smfXQKqp2+KbtO79yo/7p0uiahWyianBYGElxTh5oWDq1WTNBN0Wrs1g/v+o2HmP29B9R/jbepIga+eYyIEBZ4lIxMMCzAQKnfKShlWlDAHXroRFI21rl3CjMPYD0RHXT+DD90L+XjiQh0rOFfCJhnHQRzH8YljnH5eIfBlgd8rKNdXOB4nKPFy3a5KKWNHEwvB+X9+ehm/aRUm/MVvTRaZmSp+nrm0PtWy6gzwRcTlIdEeOqh92tgUSQTKsjLvrOxudA1aOjnRM4HkYywEsUfqNocAivTqUFPCFSiGtE3FIdWuNQWIovfT2luLOvSjVJWf1lU6r96vhr53MLBcksUqCJZcEfxJjeoJd3CmDOHvSWOA3noZLXtH5q2Gv0ioJZvNO4obE3INazr7HBMyx3keOTjoZ8NHS95ICc3cYqhGJz5oHnV92vdtMhKtX+benphlWuacP2rM5xLtWXa112NByA4O4JNL20EL6jYBth84R77h9EZYKdTkZeyVwMeC0LmS1RNbF1nc9lk/4HN++0Bi9b7mJ4V2BatdbP4Vg0Omc8ifrKsWUb5k8/mmiycAP9pvZ26rRo1x745QRgejWm3olvX2gffkbJhE/sc/5otqd89NSii/ndGsyKgOjycO/qtJmsPR4p7aJuew01mqGe5nzV2wGUmdHxCvrxl9Y8ycpX1Nb2HMIkudT+KfsMXYkKNzR4GhscaqQD3cRWsoVv9RuPhw8/sczkQfa3jtaQyxgKr3OmWEhqNkVf3ZL7hzaOUb23wwBooU724h9cQUn5PjTRUVK8Yyva04AfJ59ohbAsUdA0hNXj/tYELzzxxjE149ij2vjF2Ua0EQuYAdST3Fb3Zx2jNUebgkhXAdjWFwpgXayHnA8fv+2JBGuhpgNf4ZqpvVAkpWPomhLAkCU3TrwlTEmmyIu8WfL58iY9tX4ShqkbSB54v9H2TJivZDvq/yEV9P05fcPzPSAckshH/iS6S02/KuPxzFLlI3SHyB/CEslYJeV1KxmvUBLdoztNl9zqTDSY8Gv2DqW+7IFEUr9U9HxH96t5GO+q+JQ1a+ivK/RqWvr1gYJ6CH2l2oqijnQxN/Z8E9R+bBt5WYWfCKfal7TcXLicfeEe6q6rdKSVYTdjrAfIaFmL1YTFDipOXMTSUvdQ9xXF/QJGZI2qBiwJZ855R4vSt5aTnY80Qpy+ipYYlm9l/H2E4cLgCnuub7LaWG8L4wMYK+V/8jVyGpc22qw5vEYqA7L/QpsF7oGn59OaMn4U5/b0krY6wknibvb2QsIxZuVpEx2TJCNOI9+xaUKDRQRocYcf6WIELlIo//98bFnQ9EBoJ3EHivBHqmjo/h9emNJotcVSbpCg29veFi1lgRr/6e+dDfTa5yXlD7D+2b6l4iCxZRtO/3H8b6HWCBMRyCzNG52xr9jJXTcZc8xHWy/SWzSku+rQEf
*/