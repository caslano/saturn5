/*!
@file
Defines `boost::hana::minimum`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_MINIMUM_HPP
#define BOOST_HANA_MINIMUM_HPP

#include <boost/hana/fwd/minimum.hpp>

#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/nested_by.hpp> // required by fwd decl
#include <boost/hana/fold_left.hpp>
#include <boost/hana/if.hpp>
#include <boost/hana/less.hpp>


namespace boost { namespace hana {
    //! @cond
    template <typename Xs>
    constexpr decltype(auto) minimum_t::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using Minimum = BOOST_HANA_DISPATCH_IF(minimum_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Foldable<S>::value,
        "hana::minimum(xs) requires 'xs' to be Foldable");
    #endif

        return Minimum::apply(static_cast<Xs&&>(xs));
    }

    template <typename Xs, typename Predicate>
    constexpr decltype(auto) minimum_t::operator()(Xs&& xs, Predicate&& pred) const {
        using S = typename hana::tag_of<Xs>::type;
        using Minimum = BOOST_HANA_DISPATCH_IF(minimum_pred_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Foldable<S>::value,
        "hana::minimum(xs, predicate) requires 'xs' to be Foldable");
    #endif

        return Minimum::apply(static_cast<Xs&&>(xs),
                              static_cast<Predicate&&>(pred));
    }
    //! @endcond

    //////////////////////////////////////////////////////////////////////////
    // minimum (with a custom predicate)
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <typename Pred>
        struct min_by {
            Pred pred;

            template <typename X, typename Y>
            constexpr decltype(auto) operator()(X&& x, Y&& y) const {
                auto result = (*pred)(x, y);
                return hana::if_(result, static_cast<X&&>(x),
                                         static_cast<Y&&>(y));
            }
        };
    }

    template <typename T, bool condition>
    struct minimum_pred_impl<T, when<condition>> : default_ {
        template <typename Xs, typename Pred>
        static constexpr decltype(auto) apply(Xs&& xs, Pred const& pred) {
            // We use a pointer instead of a reference to avoid a Clang ICE.
            return hana::fold_left(static_cast<Xs&&>(xs),
                detail::min_by<decltype(&pred)>{&pred}
            );
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // minimum (without a custom predicate)
    //////////////////////////////////////////////////////////////////////////
    template <typename T, bool condition>
    struct minimum_impl<T, when<condition>> : default_ {
        template <typename Xs>
        static constexpr decltype(auto) apply(Xs&& xs)
        { return hana::minimum(static_cast<Xs&&>(xs), hana::less); }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_MINIMUM_HPP

/* minimum.hpp
Eocn9bZjkSBakmi4EDtJTnMXWE4D53fGhSeVMi5TOP91xvl2r+Wg4GoRXK3kyTuAWh38I6LrNO5cgHlqpZ2BPrSQ27sYaA+eRy/L8lraFoA9A6tYCynPVqu4LLW5Fd6bhy/OC3+T4j1Jb248XO5qpIzcIPP5TaAevfPVQZoEPtNlXDcOH4GlipCsPAd8j7u2NLhp8feRYCIiXB5UMliuASq1MTxPvjmk/c4oMGmwEeuwETxtRHtZpuhqMrmauRtAOEqfsiGcH7rTyH/t12Agi1d3R/n6oIobruZb5827mTeCEcf/nCJHIVv4VtCxIO40aCU0fWoQG2youJsGzzbQmWAxaui7mDurezMOWNAQpH5E5qtKZ76q4aQwNoyjnFaZo4oqUxGq6WxP6bSRr7vdUgYpzXpiLBXOMeiJugGFM7EydW0saddT2XwB86Yz31KoaIbEnrEcBNxU7KbNjlpXz8YxI4h8fGunBEiwaiUPaqsVl4cfmNtojjS2qf7HVXRwKCQgr86xBofsQMg3NAzoZ8h2kFMKiY5z36aWfHUIJDpmqRU9uIKziW82oHsnA/kxjdyuD+fihUsULsbHTPXcaa+lAoEen6SeT7C6y/nZzA/q1Kw01ZUa3AHt2nR3QM8NcgcGccPI5zHyWs2/mxyPkXE8/K+RfTF01/W3orlicjnNdju8eoy5okCI9porreTZ4LWgkAsryyet5Of0O5Boi5X8DL6DMneqMYpkm5CbQPZsQ37YnnFKWyPkGgcfQ6xmwZZUghjH7rpkG/lprGS23cMlMoCHXIuEEVIuepEalOEdKxEqGP0H+yjlsinl5odSrppSDj1iBUA6pKD7QBCUFj+KXIlGLLdQ6iUsZpXU+o4z/M8OPoYcg8f8J72WcqTi4wwu8/oUfDFaoeBOsjlaoeDvyGPRlILPQzdCKFiOBKwATdYlEfBxWNJ2SQTcbCVzukIIuBUJ6H4BCbgthICvhxNwsl45Es3oF71IitgXvUgSpmFHOJB+exT6fRvOey8qnPOOLFI478x35LwfRYVw3oqoEM5bEnVdzpuq6WLEehKokEBG0Z9GZD4gChmk6Qrjv2TBlkLmPB/CgmkyC6ZLFBxvI/7oSBasXdgLC35yz/8OC67TRbKgcKfMgp92s6BV921ZMFUXwoIDdSEsqNNdjwUvqCRKPk4peUIlUXIzpeReVVcYI1JKdmwN4cU0mRdDKPliVAQvPrygF1586u4QXhRbcGZAd0kXsNpSbbiRupoNhNO+nMIVoJHnvjps7QgyPuLBbOVB/z1Oo81OTjG9AkbYkPLaHLA0Kx0JdebErDrzgBV1ZoPK7s3TWb15CVZ3vd5uAxUtubxl4GFSB7xkF1uJG1ksugjMRA3NT+ioDY59HVFyuHQwud6gqlxs2dRyl6abEaj1hLsysgg9pAkXIe8CRYQaJREq8Hpfh8kMx30rtgDdIry5x9BPwKFPxqFPI2M0IVgSFMiYGDUKA/iJVkMZ4JzowZK7eYD+BDbwIOCIlRy8zJSRZzf9+f5lpo881fTnH+jPBGBrfAk4xNOI16VBhyl4H6V0cvege/IkxlbMlReWS/ZdL2SiuJBAKX40KVBHysjqfIVOIXp6Ijznb+ym15b+yEm7SpGTN4hPpZDpJXJaRcn07DeQ6eVAGJmeCYSR6bHAN5Dpt/oIMq3MlWVDotJDdkolUC3ju1C1LA8hlacBF/meJjXVzujMk1krVRXOWrfm9WUXbO2vdj4A07iinT+gPyTt/Eec7PvWzj/r6LYL1nZ02wXOjki74PUt32AXrImJVMq3mLuVMlKD0sxsQ13SqJZ0SS/8RXdHFTXcChNsOItpcmU1/GU3h+2Dx0ANfzsO29ylkO2P5LEuhWzbycNdlGy/+QYOm9cexmHT28M4bGx7NxHf3Eu5LIHc+yugoxd5rpuUjPPCqDk2OkIxfzYvhPmoVr5613fhvm3XroVRc+f8vmyDfnOf5VoI9+VcC+G+jGvX5b6kK9dCbYMo+lOxDdovX+tpG4x95htsgxZdJBv+bm4vbPhBwbdjwx91RrLhI/NkNrzSzYZzO78DGyZ2hrChqjOEDS9d7RcbHpQ1227GRwnknQAjJeNEpOaOQA9mpARt2BzOj2kh/BhC1qe1Efy4dE4kP/54GfIjntWBNROfThbQxpMp8Cd04p/HhsN5w/KVtR3z0xMuY4jhUbbO2jmHslw3LHMyvFxEWoAxEEV8h5Efs0PNjWyH1zQADCzz01wy+dsVpBWeXyP76NdEJNsRTIEgr90IQvUWdTQWDa+molJCbcDkUBtwM7UBt1Fo/4ogBZ2yefnHBUc5P45UIE8mEyf8CfVvl81RpOZPaHjDUL8neS891J36uLUkiuaA2o24sYFNQaRk2QTvKjVm7F0E6oWhY3F2T7DeXI5uI26RrUB+nq67Z1VFZ6/gdNlT+KisXDU3vs5cOZMGKNXdrFYVVZoFG0pRnbkKbCRRJUMncTGCo8JvyDgl07AB5Kgo01G+iouxkRo1onCZK0QvdpuO25+tKApbFDP5J5RESaEkehKJs7pChU6BmdhCr6NSrJW6eEJs3dRFuzfDmwvds4LGIE6QfAz/LyriDWTSZZmnM9r9gz3t9eYK2mGMdy3H9zOCnnbuxvJH1Fl8CnVDO87hgbEi9xc5/njyj4D8uttVoeJiCshVFfbC+yRNTcK47x9LsBebVVJqmr2ItNmJo+TSqzdEw/8jyyaQt2hJBhzBLQGZYVhi2gLy6mwFUszqjCFfnLwm4Y6izVOdU2lurjOfz6p0XMCoUHm8uSjB0eQfKNO6BEot6i2HwVtzGEhmDYhWUYiQpAeokMQFwoUkdXY3fn64aBjkqq7BFF3kP4OyUM5FuZu60KGhttINzyHVrHHHUBTkXC+Ms+2GChqblWyoOMli+8Xb9sDT/D1AA2vwOMUtlKp4FqrIqPa9T0GqjabAOo0YcAeDaweRuzuuKZvGvufx7IfaTtcCDHmtk59O7uhQFNkpfPvqumFkTEe4GN0xiwW7vIMAZ+ZOhFkM8p12Cpdoqi8djtFdsQjsFRdEPdDcfk3e962Edt4Itw0eenwYHvkbyFSRbw7zOPoT6T6XnqxRIx7tKsXBrkdvfEZ1jqNWByOqxy32OnMsCFAcLDLiQYj2SsOKYQQnMqodUtQpHgTUc3fQHB9Btos6jdzXrrDTgnalZ8hTxDFTPoV/EX9u7wwGMXhGb6egX9xk9AEe2DiSDGwPp8hY5b03aUJXfeVIRAPF4wGDsMUYEgGt7bql0hH0x9SZO+HLNRsbQiSfXXK94kByq6GmJJNZv2E5eeVrmXRQ4N0ms7EMI6zpdiD5tVoGb+OTSfnX8rCRSvqVbiKPl8o2KmXHQhkuDAlSGPInX6PAVNOgOGdCCUEJfHgWxbp96fg1OUkHbj06VeQ/u+QUTZFwso/PYpLyq4+vMTBgfQEUNI0VdHd3QXIc2Yo+S5orlWShJQXHTgcasb3D4JCDbPWoZ43HlSIMeryV/K7tGs0DUJtRXcsWjEf6eNIV8qThrfnpOsysk1Beps6yi4d4rXexpmpg+ZUVXFT5lSl8dPlDahWXCBNYbMXRv+A5Sz7qLzk5CO0T037EeYttbLkqGEzEPcL4AHl3gVolTQ95JcZ7h663kUcnSbjnGSV6eoGXL4wuUdEL98oXBpYEfogXCqQLeMw2R6yvIVp304z4AH6LdjfFxIPipPo+mVqPJaHWIxqM6BBpVdMkV5fs4vttFD+hElTWg5folGi/FM65P85igaS/wmNyV7nGkhTarOdvkZp1AxkLb4AJBOruFixiqu8neNwNCMYPoxFpUTNWariThg+qreTW0TDDucn3/FHkR5cR07Pca95GE9zIRulWg+cNqLYkGWsRHFvJbXJFv/Kat7JlnNeDUC02K0nFo/3SCZViG0lrg6YGtEVcLKmIwpgKbqmNST5C25szHVs50DpbyWaY9YucQZpx3akueS8GEzRsM6JgOt4THNWVjoPkwFh00Ve696QIefAvWchL82H+WSjEUBFLddNWcicW5LsKhM507EQw6t18lLAqxW9Hx47XvBOmk+1SIry5amY+4J3gkG3SVcxUa9hl3uIMWuHPM/jfZvzvF/jfz/G/x60kZyw9GwHtyHS8jrW8wUeJeSn+u1gtr4fUclrVWy11qn7U8kk6rSXTsR16i7XsYLUsYrVsV2rhHo6sgSv5xtI3sNLRhZWXFhyyGd6zgfVPngUFWizkRYvmaiEPbfn8IiFGyDMWFdfn6dWqYmGVDj4J8InLqPYPlXVSY+s1PAW4lZWEDn8v8jYzGd7JQ5OBqBW3FnHD4+JUsgH+4L5WmpyE+O0AOx4UIN+HW54gFy1MBdWX7p4xmsI+DicL4DrdKRamgnYTArhKSUK1pKZHVL6DmMW1UjFr/SJczHR3MDF7I1zM7pioiNkHX8hiVv8FFTNPn2J2IFURM017/8Ts0IS+xWxXV/dBMBCzt1sVMRuhuY6YTe74ZjG7d3S3mKUDawh5432LI8UM7YOeYpbem5jd06uYmfsjZidHSWKWHipm6b2J2de9itmn/RGzNaO6xSxNEbN0vzVSzAwVT/RSC+f6xhoGjuoWtfEhojblMsbVwDIFrPP3UOaYiJFXH0Wmrs5oh2ViXjKI4ODj+VQGBXtKX/K3/B/Xkb+s+d3yZyPiReSWqKLSHynLnlVVuWrp611VuRr4asmewi3w5mqr9LcezdrPzSq/vIJLKL88hR2T2s9/McPI3ZwD/6XjT25Yb/ejZljVmPgyB2fu7yKZD7RQybS1hEumM4NJ5plwyXxunCKZ6S2yZE5uoZL5pz4lc9pwRTJLvupLMt8Nk8zp4/qWzBFXuyXzQRsZ+Q9FMt0M53hFiGRaFcn85aVvlsxDaVQyxf1UJsYL9kkonktASKcKS6b7HpCFtKuLCelsLNPXKglpIgqpXlg1Xlg1yX93Tzl9uFc5vbc/cnpbmiSn2CYU1cEoqgNE+J2XJuZBM9PlGkNlVt9rjV/1R2ZrR0o1pgl2UA7bscYdUo1TaY3T5RpD5feZXrVEeX9qXCrXOFWwT1fkjIpxyde9i/HnP/v2YvyU7zpivCYnZBr9DuI0ykfFKcYXLk54Bp6e0AwXp8Xpijh9TGRxOkuoOD3dpzidu1ERp6Ff9E+czo/pW5wOdYSJ0xGfIk7Tr15HnOa3frM4bRwRKk7ISGhULqFsvGSSryRSnNA+6ClOaTjt9SJOjl6ZO68/4nQhJYy5u8UpDdkIJ+WU3sTJ3ytzf9wf5ubkGpOBNUPFCWd/WuMk/7IeVqerx1T442+sKS4lRFWEi9Gor76T4bnqwnUkZs7Mbolhi8yGPhaZyRe6F5m+jxDHXPEc/f089RwdOR/uOWqe1Ld7tTHSvfr2eXSreM/37l6tPK+4V53n++FeRTd6Wo/dQm8zGNOyW/VNgp7n55rQvh5Hxp2nkp94PlzyR00KPy4FI9kkOVd/jdzkIXSjjvlXT4f6Vyejf1VTQFqI4l8t8QTrPVgf9TjejS7W090u1kV4EnXmChoJP0XFRxebcjXc5OJ6c9tM4M9oK3nlEPSvWDC303gruBHIgjF3XAkOWcEcRXHCc9jBUIfrD5vR4Uo7SX2uFpjsi0RPMz06zw7xzzaF+8pHNNPB1DaHD+aNEyPdgI2RbsD2z6/jBmy+nhvwPB46yUxmi0HqByToB1zZ0w/4i8+pH7A61A8oHWAbRJZ8HukK1NhJLmilblfgpM97ugKTPw8f9EkT+ukKDP4defbkuV5cgYskV+BpfMQ3K8IVmBvmCozI9CaFsqN7jssAje5nPr4pxH1O8fGtPicLAXMYP3Qzm6GQfuRDglMCsFQKPb66MZHcfk7Z1jksmFvx8KlWcGCiqaHuupxigW8DdmoHdgKmuoUylT8OOY9+b2ejgQd/gAatNNgP3W7FUMNQk7mVut5KyNHPZDJg8TbFr6dBv14NGN+KX2/HZ4pf743PFL9eulSBUakgCsrY8JI88ls+oz49ZY/nsRnIt86EkvHolNs6gTrl/vphpHdva58+uT9MYD65t2sk714+FlTACtrwYQ/v3rI+S7pXKuk/WEmSX6+lD0V6uCnSr9fax5MvN0Wo3O4wwLY+XintUXigjyfzm3pzGha7yzSy11Bn2DWw2H1lBWgk95UpfEyx+yGNihsAujmu2PPNrsPlF+S8K1xeyXxqMb3frLgOZ9ALrzcrrsNJ9MJvmhXXYRq9UNXcP9ehrhNNvQ26EFMvoGWmnk6nmHp6nWzq3f4pVfgpn4bL/tSbmCBtlU295bQVp4hi6v39rGzqXTpLTT0E5aRk40egCgfGjS7OXKnjPraS7TAnGXZVS+behPOh5t7WEHPvj2juWWVz76dyZb8MMffQXgVzb2SI+/A+GznbrJh7Vcx9uAyK7pTMvVzF3Cu8cH1zD8T8IBEHXsd/qJMcG/FYkq/9n+w/VA38V/gPnzX+M/2H2cbe/YdPfDf/4ZbTPcw4ZHCmDB/OQDOuU9vtP5x3mvoPs09H+A/LFf/hqNO9+w9jT4f6D629+A+/raztP0Vl7Y1T4bK2ZzSTtTfDZe0/ziuyVnZKlrXHTlFZq+pb1mb8KFTWPvisf7KmOd+3rP05xIcIslb6mSJrqZrryJrvXD9kbeSA6zgRZVl74VxvsvZ/2om4OfFf4US8JfGf7UQ8mNC7E3FkH07E1aXf3vsw+OR1hPDrKd1CaCPzPmVORMPPHqf0CTXuoTO5mpDf98NvHf39Q/zNOby50YZd+oyjxab9nLXYfXkFnke+PIWLy8mB63CV/3txppG7zV2twb+T2UVuVN+PgpxYNWG+xm8rxbpGKsV/PxEuxV2pTIrPhUvxK58pUrz7hCzFNSeoFO/qW4pLV4dKceBMX1L8XpgUZ3/WtxT/40q3FJeCxXFGkeLlzN/oCJHipYoUj/m0H1LsSOifw/Gy5CE5dBYF2v/Pdzjuif9XOxyXxf+rHY5NcX06HCf14XAs/em3F/m0j68j8ppJIfPud5CpNxqoTD3TEC5Trw5nMvXXcJkqPKvI1L0Nskzd33At+L8A4DTBOGtJAIBDS719C3hU1bXwTGaSTGDIGSBAgKBBgoKAPIKaOEETYEJAAxMCEyIkoQo6jqIo50BaSUh6MspwjLYVb21rrVatj1qr1lpfxTwgD0DkJSJECRJ1D4MaJIZJmHD+tdY+Z2YStffe//v+X78h5+zH2muvvfZ67LP32jCnfv/Tc+qSW6Ln1LPH/mdzin3603Pqd+f7zakVx8JzynzhP8ypD4//D+ZUQsL/bNVRn1O/OP5jc+r/warjesv/71XHi/H/v1Ydt8f/5Kpj+9n/K3PVf+A/TJs9kyLTJuLTGub+uKf65IGIp6rUy6vNBnm1xdBsEIFVGwuVVWkWV5HS0xyP74oJ6lzuZC0H0fnMdbHgsT5iY98CszhMTQfmzTh0UbuD9XazgfrAt+6tbDAblHoMgMNBKwnYjC/P3GAx8FaUs81xlDPP4su1eOuUeeYicSY0eIWTFWGDwQVF7EG9wVyzmKxuMBc5WdNB3mKCfJvZEDBBDgZGxPbC2MMsz0GwCzhYHapR78bMqG4gVOjH+jDU2wnqArPeC/nn
*/