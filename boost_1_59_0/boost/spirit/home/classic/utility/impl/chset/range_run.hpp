/*=============================================================================
    Copyright (c) 2001-2003 Joel de Guzman
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_RANGE_RUN_HPP
#define BOOST_SPIRIT_RANGE_RUN_HPP

///////////////////////////////////////////////////////////////////////////////
#include <vector>

#include <boost/spirit/home/classic/namespace.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { 

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

namespace utility { namespace impl {

    ///////////////////////////////////////////////////////////////////////////
    //
    //  range class
    //
    //      Implements a closed range of values. This class is used in
    //      the implementation of the range_run class.
    //
    //      { Low level implementation detail }
    //      { Not to be confused with BOOST_SPIRIT_CLASSIC_NS::range }
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharT>
    struct range {

                        range(CharT first, CharT last);

        bool            is_valid() const;
        bool            includes(CharT v) const;
        bool            includes(range const& r) const;
        bool            overlaps(range const& r) const;
        void            merge(range const& r);

        CharT first;
        CharT last;
    };

    //////////////////////////////////
    template <typename CharT>
    struct range_char_compare {

        bool operator()(range<CharT> const& x, const CharT y) const
        { return x.first < y; }
        
        bool operator()(const CharT x, range<CharT> const& y) const
        { return x < y.first; }
        
        // This additional operator is required for the checked STL shipped
        // with VC8 testing the ordering of the iterators passed to the
        // std::lower_bound algo this range_char_compare<> predicate is passed
        // to.
        bool operator()(range<CharT> const& x, range<CharT> const& y) const
        { return x.first < y.first; }
    };

    //////////////////////////////////
    template <typename CharT>
    struct range_compare {

        bool operator()(range<CharT> const& x, range<CharT> const& y) const
        { return x.first < y.first; }
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  range_run
    //
    //      An implementation of a sparse bit (boolean) set. The set uses
    //      a sorted vector of disjoint ranges. This class implements the
    //      bare minimum essentials from which the full range of set
    //      operators can be implemented. The set is constructed from
    //      ranges. Internally, adjacent or overlapping ranges are
    //      coalesced.
    //
    //      range_runs are very space-economical in situations where there
    //      are lots of ranges and a few individual disjoint values.
    //      Searching is O(log n) where n is the number of ranges.
    //
    //      { Low level implementation detail }
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharT>
    class range_run {

    public:

        typedef range<CharT> range_t;
        typedef std::vector<range_t> run_t;
        typedef typename run_t::iterator iterator;
        typedef typename run_t::const_iterator const_iterator;

        void            swap(range_run& rr);
        bool            test(CharT v) const;
        void            set(range_t const& r);
        void            clear(range_t const& r);
        void            clear();

        const_iterator  begin() const;
        const_iterator  end() const;

    private:

        void            merge(iterator iter, range_t const& r);

        run_t run;
    };

}}

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS::utility::impl

#endif

#include <boost/spirit/home/classic/utility/impl/chset/range_run.ipp>

/* range_run.hpp
4xzZin3tbpnZwZYFX1kTBTsH6k+Jek1soWu+euWrBCpsd1UV9VIv0sciFjGxE+9xCONob3nTK9pH3nx/4uXZKBpSYEgJVMaTlok4aG4vWmeZld8hc0qhxwdPnCsffG8lxpv5WPbxDzOf2t98y+KPVef8mkmvdgS96RKJbY9v2nh55uybNkp9KMyBCafkElVRuVNxrs9T7vLxmlB70jL6x1947MOEXOaM14Iu33J2mtDrueY/8dG7Nhg34jwo8N3s1Rfn6N5IsWwamgDpUGw7+9PTCvOgcOd6Hh/E7hpvmzs7bcdoKyhLoq9eRytoAMLFhgbp3fwzXUpW1R61RVrbidPhDmOfvhTFUZt6WkvSCcf+7Bn8IKHuEqCFghMJh84HuTSDBXv8bZ6VdXNSDrfTos9zMKEv7k8LRHHz44Rb22k4DRNq88qSpHpeitP8uQxcDA1bwpmj6FZEhvNg3Rwrb3AAkzL2i7KuFDETo6WzVI5LcsRQLXfB0jpho2nNAcFatqHugjsBrGIgZUvRaUtFmlLuHV1UQFWXuCi9D/pKHMpTHw5L71CxCieBV8Zn07x6ySDdEbtzlS2iV+Q6DmjB9nhwTTE8wEE7aGaroyQnHmwtMIqnIAr9ca18jbECqBXiK0T2iZWvcRA2L18j/nGfPHGaODXWnrHITYikol+s9rS/fkEv8YSZFlyjFU2NB9aGCoxoBnUextRqa5rVfcovVX1g7Q94n62RRnem91m2fYtYA4rmqAPhFGPmUXgMa9QKB0FPcVquVpKTX5e4Mt2jimWkogzRA/s4I2XPlSqaWmGOaZ9X6E3p/5cnQ1LRQqm7N22QL3rM3HVQLIryeucgNtU2HixlCCsX58p1Er3GRKFRm/h8SaeROD8Jj72s7Nddr6Od+ygLEPkLcazCJF2eF8S1JINW6lDaOBW1lcRvniH++CCD/PIQHkL0ADYuahhbYLkEumQJ2Cp52ou2NVmnyZBH0sY4hKOCYo55uhBi2N7+OnSnuJhVnyCV4I9D88xwdSGn/lve3EkBp3Srnm7rEGM4zSFEQhzLQ/aHyHn+0AjdLTeTU+INrXCi3jtkOshaLvNEWdllorFiNL80a7QZofnGArfMJFYKWxqGi7W6OTZkwWFwQ8eJiMyqZ7L0OehlQSLKeC6l8uGpxNmRpaP10iQCYD2RVW8DJjQV70L+b5RxemEeFXdliEviEsZL7egB/EZfkMciyz0Ecory/Mdghdbyrd2sORxO03NLfErlnY8PvlH6cnJJenn1Zgus6AEbQT3KUhCes8txvP8bldH0I3jJWmllK36W4xW/W2G6rfpYbxBfyOie77dEIfRmOMYF5Mj6XreOhW8yoCUzAQhdK0WouhL9AZd+Hbx3Qb5LlKTYNlEiYcIJcy5io4R8UJPLhlrROtYykFR76fsni/GUw9+06N8JAoKQjSMkUmm78oI+FvoS0d67AwbRZ69LvYl6xUnPLolV6WFJ0DCRrnxwEn6ir9XxnldKDV09TiuD8Utsrz0cEZErcZDuqWJIzQslhPG72w6PURExjpPVu+g7vbrTZp7TX5Ue+ubCJeWGSx0aMwj7yz3pe9qbDV1F0e9N2hIDxK+DHQZl8qq9oUr0lxM8qIz9vehWNxZaKxlarhlYz0S2sdbRZ9kOygCPBSciWqDJcpoEbCbVCj2V2LSiEBZEbBenD4ZmnRZo9O9W/MZGKdQ00U8+W8QFGuXrrhZxhtrEKOZgyHiHOj8TAJCXURdbnfl5nFMvPxhhpRtkvbS4GFrwu7RxWpHzrNXYIN60OyF2tOiepMLEkIVpzv3lstaPYYdhTXTZco9hlrjY2KusMBSRfqRhiIrzjrLutO/gZ+H9VOXmVpxpbdWsazulVksBbUxKGPX9jXmJtTGZFrA2JrFUmZzAejL8wfuAXomxcmlQWZekL4xBIKZeMclj2TLLBZ5J9rnSfACqw2KsAmpTzrMAoFeXIC+l52nVc356PT3lqiPE8NoH0tcf+4iP4WWkAFqa1/sW5ikT2GgO34CJUT16zNrPeBwq85vRm3q/GlKJLKuFbl77yQ8HGoTKxWfPSZ6ZqO1usQkzVLQVJy0jxa3PpTw33X/DunVxHSok64qNTZKQWyd9GqW04Frnn0V+wFPdIa10hf+kmimm/5iq1RmH9V3IhHotoqbLN3b5ZonNUwU2k5cx94QIgyRVkHK0FjjiII6/vPXp/B16gx5odgTEW6foIT5z5fRoxlvtoeKkSnN9YOW5yIcp+mBpJ7teUgDvxANPSXvQd9g18DZ95sH8mfv0YGN+sFYvXeFo5CCoTflEGgTbHHUggQLtTHW0pqgOOcD5x2ivzmxfT3Rq7IsMje6cijMWaMvQg8fXZ9DLlgyN7ux42ZqBM9sgkRleRNoguiNHm+bSStxy5miar8A0X2pO4TBZw3f/YI2tHOn1PTrMeD86nCgW430QL9YGfEZJM1IMp5tH1xfRVPCqi91JPORgc8ndwaTJHAzzO7yWkrgBj4XmF9wQm3INt6Q+4AYkF3dzg5Rh+lhu0AXGe5dMceOPPTuahwdGS59i3ZiEkKdyOUqjGiWH/wO13i3z60/dwOI5cc2zjHFGp+Gt46Yxp8wZvaB+CfKiWaYb1ynuRE+ZGFuDJLMNfi6TSKwGABSQWMSX29T+VMtbq7mWHlGnVYTTJL9uUa3wpucht6dqBJDofvEsf+Gp6scahWaE7yT7V2D4Kkapd4rs1dBIQSj4JDMETAhnjkVyeL8fgo3BgFjYCEzGt1e+T19MOE7Un9rXN6ENwb16aPxXzIh9Z1iRHEviLyG7nlUFrfO0IgfrV8e2y0nsw+5MAfmSKr5zUrRTF6MJ6sRh35xRnipIsuFY8HKzwTuVEemlDzBbWX/AanBYdLxrMUxpOaVqekR8s+p7YwLgrk9AayDYKxVUx4+TtU1Mr61AvvY9xbvjwrIqaawEIC4rLLOn3pg6q+bs71R6w/LJbQVEQQ5fqVBHYf5X8fxfUDYJX7NLCy7tbLeP78/1lR614GrZ33lTOiw0yJsw994u3jTSrCZNml3u4Av0Q7SH87RAM+1hRF5uhn5rEpZbtFkfE1y+fZ+1CruziJd1Pr6vMptWAINN/hgJ4s6DHWy2FWj+fiXdaNW/TxCVECQLTY9Kw1ywpUjRg62O4FG44uilEyQMCgfYKiebZx/VCt0EvvQ/cJn3J8tUehEseN9e6CRg8P4lhfAgO1ffzQN08pemp8m8mqwTvb3i7ZXdbfohcfMfpLc0ROCMbYVvGNprzEjJEWi8F6o9bbL1UXNdsUXiiuWSEvBUfoRGLHDqE6B9CRtGT+V+zP8CZwk7mLBGs/JeHk2XTc0oOIEPQXFFJ4rVPo7+0soyLECDvkTuPLssk+PF4RwsJFGi+Lh7p3Ey0AagoxTQh3eaH5pSMf72fPr29nN8+4L1bYb89pLUtxnWtwPp24vP8W20O4wvD8KqYhX0ydbDnaEXaitHi7GP+GiMplhtyt8dLzrjC4pFDloosDoMHqHZIoz5VvuDsNrN0Bv12Aoq0/Fe4nIavVqlSC8/qtscpwgB6+XCcZqwsF7hitWPRsCLmU1x9SDso6kQWjH7eZ+E0tcbNq/492PdbTvFrOshoJHrf/zZWu4PJ8nvO9P39S36Ft7Xq3lf/9i3+jh1Rbl+OzYa7c/v/sLo5ir9dVTo7yB6zqDlujjPsyXg9mwJuuqavT3qQmF28wfy/Pf0QYsLy+eAOP6UXFqIksGxnB9OtprNYAabKOwdvY12JNHE72iBXWmZ0rYJZXGo7XaiCCnHFoyfPeAiInQS4qWZuly3QL6lX81x093x4D7EIHFAqyhEtG27oR5P2VXdXnVC/aesnymgA+KfCHGMYFtHugTbui6uHpGRvaLOdcY7Dpip7kI+ZxHlo6rklkVuqXUcq81IuMWBibTrJw/qQqY/cHcamd7VDIHIzaCrao9yo24vicRntkIdNv7QDUSJ6ebGo/pt9L+sCvcSGYMSJXZDOvpIrQdpL8Fm07OF4+4uQLGr4bJJ44IfUjcTjzMNFO4EpnBhhpxG4eJxtK7zQnlJkke6HWaZ5ZslPpdwufHFDkbNl0GU4aD0FGg8m/WRYDLVapAWWmCjT93sqboAq2eveOUJiej7JGERNVNM+kWn8Sro16o6dZjv/hHKYN/9I9XcaF6xzFOCaCQPjRdByqfdP953fx7cpSIlUqIRnERlY9bDp+tGT+USdEjdrDyEMhZEx8QDNSUh8WYFjhlbzTqhZ9UGtarA8dgutxao1QPtJfGZNViqdpqoMhO2rb8bBo01ILaHN/gb1BRJg293EaHLDglq8wM1BOq3GWpNScvXWLbSbxUXEu0/0XQsEjtgTAxFIiXiR/fA2yXHHOtv+bSKRBI7UyNyxd3JEVG6jEiJOSTmiPjv5hERrSth2M+uT2Yez5/Zqo8rnm5xGsaTEBlrk/NoeJSfYmhKUdgt0ZHxwC4amn+Um4dBuwAKf4lgLjPhQhfSvOBaR7BRm7lGC27IDzY5dmiB9XF1DTZPNKd4Xf4O6nXTuum0iM0Bm0czRIX84pSRsrIL/1zKWHFeYjFrF6eDq/O70sY9QFLOMdbAtDMVOLDEP8mpZuterdiZyNZDTn20dpV/kotIn5BTK3YlEF59vlO7zxkSi97OSpNiUbX1Wfuu7usVX/7zu6RSw48KUkoN0iZZjCtNE0Q+U2FJrJXC2PZGGxp2yQ+IrXtL2iu+HKGOxZ2wMMxm7ww42pyLqJ1NAt6WLEYvzbedHvCCONQCTXIMwGYUHIZf4/KDBNUL04fJJykpZDunA20WUbRGTMglqceQeG2vzba03GWn7av+yjxF7hPt09XMRpknJVWJGXo9tCEvx/acb4qrsHUhrup5OZN1V+qBg1qA+MYmLbAvHmhId6iyDz7OGyALXeEAkeiJt9gYw6zXSvdZkrH+jjQJYjcHAwt9AsZSUhknGO8elNIK3ptNHAOlNiRe+AfC6TmJlqHPxHy29EETUYupocZFHLJJSk2++75XBTlULM2xfLVXrkuWIYZflnRZ//giyP5Y4rggT2/XVqfU4CwH8y2NaMxLP+qAV3rxRo/vaOHweVloHMrNAIsjH/2BHE/V19BZUvfF6mfQUEVS9X8ABaAtgX2EgBssBIxZSwpIwAPeCYkHD0x85hFoqFrKMwBbHFdGb8cEDqC7iAz/+s5DUJ/mScNQIv41DyafK8tp28UYsjaFIX/i/8YymSpisxlleEp4ZPrK750ui22ZBduVchdoJqUn3WRmgOS8kd5yNt9T0ET0VI6jFy17oPD0jbIgvQK1TD6Nd5o9lpo+v8hPzkQP7sesWfTleO7NcV4Y7YhkTOOub5RGN3dT4RUD2X3rXgAVRNK5BZpX7ZmeypuhM3VWRzxVwL+ptwfB0JxsCg88IQVb6F4h+1Rn7GxKzA5eyjEQh3CwXCIwb/4V01S9oEGyjEHhY2Wd6GU+rTV4IO93lOnrVZeiQxOHEoj50a9MsXImcVKqg3YIjRtWoacKBrq62ijhjX+nOr6gNuE3F6FlOmbVk0/1tDR/Z3Dco0zquFqTPjOJAwSrfFh4F6HQ/aLgt5KAwxKBaPKgvksjlqIJ0sn94tFvUVCGkguT1r6xdpfSK9beTekWa6cScFIl2xSWgIm7VPrrTnMbcjywQiem4VUAH2m5hcr+jJQJndTwcNnoNmYsjPfDZXnHzFt0Z0kXwoEGs1vUwZkTg7smmySkm5JTBZQ3SiIzpeqcR6xKOBSW48+S/hKj3zL6loZ8cNgkXMtAiSRpr/oAthBBn31J7PX4T0FtmW5ints1CIJY1ZUYiGi+OGly6DfmEeEpnfeU5PnfUDzUto9KXq3Fot12oyMNFfHn1LGxOB8uQQltqTIMs4wIysiiMj5M9DBLaW83jDlzTVRFWLQQhQwNiZyPWWzeT5/m1ablwGBmIgy9bOIXNItzkmSplKHSh56qlZg7fU5SF/75bwwJtT6ijdFOyO682GKvTelLxPO4X2XatEJv/RQQ/raEM3aX1+ab41XywBG4v4XZIC2Xj7gF7tg8F2sDHT8OAY6vMEfN9zcpPX2FXnWY9DaSOJ8eqKmMKtNc4OgXdxp8bI3Wsg1+YQ7x9bvkEhgSEldQFbG7cmx6E8H2w1TV7U42gdCoKjkSeajZxdm8admkpcRPj7OjQ6hI/wQc8sYqU7kvNs1pxKa5DMSkqs86QgSCVuHWKug3R6vI1SoGaRV5WsUIrWLURK1wtFY4RqsYp1WM1yomxufcEO0enzZD82sPObWHXNpDbvFEaYYNL+dr5Z1Ckw9sQMraoQvpBauz9r6Gld/5UOKNDawfWCLpBlZ7ZiG3JoUlfMQvsn5NA8060tsZ8W/HOq6vRjhwQB6TU2DpWlnNSIIqu9UOQyscqe8Wq6vYKbPV8S2VSd1wdJY4ZARoKzic6EddEX843QF41k2Hv5IGY7rTN2ee+hnS5ovF309bRGm5soNi3veSV0PioDanOiZ6LqXJ4m5DX3vJ36H2nxydX9+WYaN6YIHwAN2yBQI16b/oXhyiVmPuVniJIz4e624TvwunkWknFPO8eBQrgcaDbcS6i5blDpsxGoIHceuvCR0H22J1bXqbcFG9+m4wcGIpyi0bRINZ8xhGJwOjM/ap1wbAUScL3quOAE2dVErL1kDR8MBIVv1uPoO4T53+euX8SHRi1G4R2SJwq8OmVR2l5ESW9hr+6tVOt417o70mpJbxUD2OFP8BJZtPe0NO4a6UwWm4ZHgvgTsGor1OFI6w6y59Tp4WR4qn6lp6Xzb/EubgP7pfMmWIbhmvaqL0UPjVO8YRqLjmYonTIOwpW3kh597EuZURJfxC7LifnbAUzadmeCNhUWWHvhrVcASLCA4I6JvF8htfifRIsJy/8bGSsTJCn6gU7KEh6MtAsOBt36w8z8od+htUYIv/gKeKj6Sm5dFjZuyUoTqirbOBFuqVTH3BOAJxC8aEiuVIiNt/7LCFSiLheLwVjxkfZsNjwssYL/nK0mi/mlLkez2OmYlXITUkFsZkhOW+8nXIej8vJrWtzYJX/5s+r8LnvtfkeP6GfltALYgToy0RC/QR+i5jMrdvrGKQTe1pefgTL51ml0Cm51jxn4clFmUX8ZTTU7XCBvK9Iidm9FVc8SmfETp+oAKwlkZzGC1Z/4fqPQW1sURf5aZYIlsZdhOE1l1wGoQNF2J/Z+YB611iCs2Hz2Fe0GYfXpdfx3m8REVlAvUlMmvmtUGCZ0pYU9gMPtVnz03iACgfEIfDjVZGsflfO5v/dbJ7xFQ7YAQIxyXU53bx2il2aZhSdBJ/T9MLP3lhioWK2mq2/YR26PQl3eFNQcxaauKTh8SQqwDy6N0HfzptYE9u/9X1hIrFm6MlxVTCicEXT0P8myl+fgWRedJsrtRF6XCkFi8aJUZP7MA8K8MINXUsQQxakADxm9rEVX/hXd230LexhohMJYGXg//CJnO/XyJh4Jiandjlg9C8gAsaWzgE9Dxeh+AxgYP+A1TzV5d3GPFCBDmDcSRRFeLX7yPa1xHauAERubJDKq/3pW7oha78QifBgYnQgim7/zoO5VBBoEY9Qqw0QYYS0eeXVNy0NvHYn1kjlsUC
*/