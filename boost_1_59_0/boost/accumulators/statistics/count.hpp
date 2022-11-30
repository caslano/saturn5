///////////////////////////////////////////////////////////////////////////////
// count.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_COUNT_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_COUNT_HPP_EAN_28_10_2005

#include <boost/mpl/always.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>

namespace boost { namespace accumulators
{

namespace impl
{

    ///////////////////////////////////////////////////////////////////////////////
    // count_impl
    struct count_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef std::size_t result_type;

        count_impl(dont_care)
          : cnt(0)
        {
        }

        void operator ()(dont_care)
        {
            ++this->cnt;
        }

        result_type result(dont_care) const
        {
            return this->cnt;
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & cnt;
        }

    private:
        std::size_t cnt;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::count
//
namespace tag
{
    struct count
      : depends_on<>
    {
        /// INTERNAL ONLY
        ///
        typedef mpl::always<accumulators::impl::count_impl> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::count
//
namespace extract
{
    extractor<tag::count> const count = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(count)
}

using extract::count;

}} // namespace boost::accumulators

#endif

/* count.hpp
zelmLFTjdklmFZ3NYoQdMa4V3zJ3f+kvpqqUtLahz3ImZYz195LT/BYj6aQURYD3n6miXzWiJa/W/q/9HHwjW6V5DZqxSvV/m/0a/Sh8YXVnVnGbEJnTFYU19pPvL/1oe3knKXdT2ZKQvSmxMpyg+3ncvJSxHJMfjEmnl9W5FSbuzX6UxPBZRGV7pqTwMZ0umCH4pj865M6hOFsooYnBhBwlcOPe/ri7fXYQ6wpaejHt2CSsm+/Em/wL/mwhTSr8wiN0pBCBKTB6ZE7VUiEz92sU3pIB2aXbDl0xObAXJ7UAQ+Xx7G3VNTsChQDx7V+KOWs8Pgs9zqK+G/Qz9TyW22Gtre/5T20Y5dWgudKXAxAcXDCztUDwTno3E30Wo780JmVuF7wBVl7FPXr5Mlf1Uka//w5NVtVn5T9GQJ3fPhDKakYCvYraOxJtcWms2Ylv6Jrq9uN0f0Fo+06JsVChfB58RQTpXCUn+7sQUun7uoCnange79/Xs76fGK3BvfuMeL2PevXvsxdcPoXQ2bIWqiBRgBa3Oc+Jo27Dypujgnnd2C0ksls7n96oA/TPmn3guDtTytKqJ0ULWp/GncZCYEKLzeTmEeMvLPtc67owrSFw8OC9tF7+tZgzrGjtHNtwACBbN6JKWkiFDfvjk10ZwCCsu1wSW901Y8yDKXg3/yj685eSO2IVnpEVNePslbr3xHvwRLW30dHyfBPDgbXr7hNU4OEEIw4kHRiGFQwZQlrO4wTXF4CKVua9SNuhC51Z2L3bLkVSuIrr/dCwn6dXyXpe7OTTrCgxXwc47/wp4TDYeCTjFlKlzAHlYuTkXlo22wwadhZ80SmU8r8aFWL5d0wzPByhCYsnycK4jVxm1Wwe+bwB/7mqT0KKOkjH7M8OQB1zDVziyGUMjaMHyYAIuMrv1wfFIYMJK3YXhtXfRQBRTp0SiwCb14WzxL6RtVofjHUQ5xzIuq6rvZDg1v9ex6b/+j0hnjBw/zNF6HvF2EXMwt34HXe3zKjclrGevXo449xsSKQlF8rKeMNrljXUfsN9apt1tJHtWmY0ZepSkBmYkyrtPB/OXKlZ0JqhD4pqY2rRKT3InnZY5aNVeOWPaAHiFIlcSB+qBbM1v5QCzlBdm7ZxcvBqosTVww86BFZ0YnMuaVUP+ccQZRwZDE0cPzSNV4lLVyTONBJt5B/Pd+/igrrjbe1eJqmwHUubC8k3n8CwcgEPTOLf+nn5Q+hIdqbqL/FDbN7N8JUUZBy/osWYhx3C+r4tzPq5uTK9t4ORUWcef4Z9kF8mCxoHLXQB98VszCTiYYZmksCQg/QNpKYyEXQpBzgYPebtkE966h+tb/A7alNPdvdVa37UK+K58mdcJa3oUHiJz6dUquCv60eg4fJB4Q4HynPeoAselbBzej5mHmblBOq/+3k3S8euFD8Iwdr2+jCXuvv+gzOOrjGKQJ9Mkv3uNeGQbE3Kc805w2CVXu23CvJatUnWa5sPKMnUqjTrJqX1ShTHSIRQGmnSExZ8pB1DQv/SLd0UOybJq5l5R8K7v+oqFIKbQj9UabzOSlKDR+P3W3D25PvP6pjPHf6+1Ph2AVY2ga3/CntIUbfy48Ojl/4dzmN+p6BAQOg7ylDF0qzSe5g0L+4PzdAou7H4AH8XpkZ9pDlBNSvFo8n+zejqagnqoyWKKP71hj3u395BwxiH97Sp3y2FX5bO5I5LaVfvQB2YHBCw4BkhKi4Tq/Or8cdMJQ6a2i7Uhj7srViT/RSXyzW0BNcRTMLYKcdPzOkf3c+2vZimJRveSTfAMJJ5Rdwx+mNZvI2BsWZSj6BCxxN5L1hC65MCAXkfCDLiufXoslG8vztoHxJG3z1ADxn6R9GZrcA86i3Gr0snA+DkbMe+E7BbiO7iDpj1M2kzx4afAOp7xqUPu6R4SUGoYygaoCAdyJLFOMG9gS196rT3XAEzv+fuHeLso5PkTNIsWA84Zt7etYHjipGUARMKVMBJeAAIcM2PbhBVyVKxPaQWyxRLOYxIne4Kk4D6MhzVgbPRLk6EmRNdw7TqSn7z2IwrSP/Y2FFHEkuD1pZHoBcvHEajas3MWgO1G6Tlaz4c0Md0Wk+3Wyy+kfQcdT94W/za3R9s5isShsLrCqB21/9oDWl3s3lTULJKI/egfK5ZEEkaN+SoxM++lApxK3FRMmv1Wszruo+W+uEhHFcS8s3Xx5W0GJdVtHmumW1d48aaoULD7kyWAavbKGsn/nyVUZuZbhRj44+iNfhCnZcGdiplAAlh/gffbcpmXAiHT/Ji1ichbLR8zvtnT0FU2Rc6OIE7SvSAh361OGkKQypg5O8zhQtakO/ZaAIGeCkyvGKZfUU76198hZw4JXk/iYphpXNDFEvmcBCuOQluzkfIHe9fEaV9PQmVo0fS6reGm+NkV4uGGAo+yESeblMWsOqLMp3FQaQMzBA8rnu5V5Hq2bV9EjO7DDLYXs96OxkEr6OPlFHxw+BAaE83a4nY0QEFCvFRaFJF28JLIJyaG17o7NMAtjTdpjXDuKoHN4R5PtgAzyIuAhSZviIfRPBmXtos6mmlsTRlMtnV+Ish8FRCOBI7zxcLyGd9P0kmVU42nizJ05LNTldD8551lxiONtkDt1NMY2aypKBxrtmDMY7pZjLEU5yRcEeeARxXSf3tAD/5azCWxvfyMvtj1oPiKVu4sfHTNLO3PBtxIu2RGY5LbCItGFL1r1Xg91J/idtew1FMNNsEb9BYybtD1ywTeAN4ZygdqmFDqokPax6U286AnVVDd0m04zFaX7xtynWP6FK5RE//X2dV1Y8kijDN3WbzzmcNt2xMExmewV7uYipZ1uvrAil7cwj1DvQ7qhRlzVJKNYkYkU8JZb8jKW43YaeBIX6PIm+eTghamNNsd8SpJqqtm7iVQxFDepYtlpGbsWTVS/o4j3JtfTSEByOJyr/U1fppfODfTtdTNyy+NoroS2OLOAiLE3e601dVMGTZB6cSo7R39+Czq3+wBzVf0T9dqj+RuUbMmt1sPurUBmkus5bKzzF6q4i4Vz88DtGdh3mSGJA4gxDXd5aRblbaiL4N2OkzhoELn7Cv6liNLCw89EvNM5QYeWGzl2ivPZMgW5LwYaibQdAZJFef9pZ1b8zVoBATnV9MNpBLL91H9g9JbNb+fG7aJ1BgVOtBjxhavA+eKcc+mpSUjZiWl13wOI48Fc465K1IcfCw16UioEvNxkEtF8rYtFUWb1Vl31K3SPWyl8Hieqe1HlfxLVOoJHiSVYQ+roZLhT3Kv7a2KlC9FAzcalhwJpWqa64GdZ/CEtd1h4FzKdPowQ/DQAANUmGARDgRQIaZd9cbl/rJNYThBxgrXHvSFqPLfDuCTVgdmwVXEhjgEuNIN7PHWXNHf5iJSGuop7Imo1xIZi08145J59+A7Kn6ai1QiHb6p0Wz2wMtKCzbJSQ8kEAJKjJIKirIWiLjLMCTuUhs/vSn8BcZeYlWSvc8MyR5NQYgD0x+ysgF6AX07z/pyUH8HSi9eG+rmpnckL1XXXQale7sufKdpX8R3rAsRDyeTPhWS8/5/CtD/xCvsVyic1j5X+EJERBIcDT1PeQbI32r64S8E3uCP6CiXpTIE0bIJSLjQKg8EZ78d4cUI0vRjc3KQXkIkQ3eizf6DtrMwXXoTYc7rEPCrCwIM/DUwSNBYEj3nA+eKrLe00IjdQrNSGx7R93acpCpiHCVbSfoUvVB8Rh8lGqhZWYNSwUWeT7Hjz77CfL4Z+TcR75k82f5OfrPxHG0od59cSqb5dpxdEqqCuqiO6JJ7+/NCHVX572oXgvYrS1sQ4O8r6o+ntc/ur7iKrRDJ43ZrbbJwE9uNbGca5xBPRBuW04vPSKXNgbu5yfS6pfBJUL6bFAluwsgA+qdUA+UoyQQ7yG9/M3J6A0YO/JX7+gdWc6oi+p5o85gzCdoa9kuhrwdS/9b/zWnfKQthIjut2XcZzoSFzUmnUkogx6xbZaMJZ1pIBe1Q1KhwnFoAzZRlBnQ2MnIg8JE2YBxAOlhCBtd1lPXeDhdRG2EnT6v1Utm+6DjgIG5081v3+4dI41Zu8BkNMgbypQdCA74Gsidlz8EgBMoA2gLwAZ8BJgCaYPug6XPKj2eAcoCd8fUt8tJWejB73EDugPQ+jP6c/tfAkiBzoDAUyzbXwG64G/YfXZAvvD26H2i/i6AEEA5QA1kCBgDEOpESNsXBiADeAK5AnED3zn5q/pb+iP5C/pL+2sAHACiAPjDzaatTECv6kSnC9jSH31Ufto+F0AiABZAFKJ5A+MfCxQDcgXmjrSHd9eJ0DMNaAaY/Gc/HfAIOAAaAbIH4KPx8/yvbdh7VyAcUHdkfcBjX9cVIgQBJgFEHmzenzy4PSB/PmAcADsUPWSeHtQ5iDZYHLQ9SB+nv6Y/F9ANkDuGPkIflL8TgAgQX9m0heLv7u/xn/2Q/+ax/W9ADvgbgv83QAywA/6Gog/adwXoABIHHQOyB1YGuQO4AXGD1mHvYfRxAITiUyLB3SHv8nTgnsEeNwEIwLTwA25sfbX/zeHFxA/CD7FmBbQCxA5E2T8NFYdQB6rP27cMmAcMvsu7QSZC27MAdM7AbOsB94BHIEcgVaAqIHsQa9A2iP/cFwP8QNZB7In4swHNHDN1YAT0EG73TYnGWIEZ4KgEaQls2Yi0ssSpHTqe9EKcnb8CEABbYHV/9HH9cfWh+Bn7VACe/v04eT7+QQAvQA7wG0ufHECWdsUxc/8SWB3sP0fQ+HH62P33rfsI+zD9U4FeQL7+7An4ywLw9kz9VQAcgHCAEmCD4GZVKg8XaAeEHXgO7I64LwiQDZgGwAGSAbL/bQfn/5ZTCQCLwQfzAM4O+V9KJPzDADdAa7B74OTAY0DiYGlAiHB9QN4ZUG9g7LB16HsU/0V1A9GGnYeqT8RPwg/Fj9fn/d+mOgD8BQoF8CH5E2bu+zA1yUH0KQHogL/CFnTD52gdABySn+z9PuEHrRBbvnB3GH2TEb+MMacVbXDGMycXHAGVIOgxVCc4W5418ZX7WCifjPb1QMZOlX3WpxHksqrZImWdzTW+StnFFfX1PfOKvb7dc2vqKhwQD7oH6rvqi31a1meDDjEflr5KIkYqGg4ySsnDCnpUdyzPLjImwxpglZkVWEE/YCyX2JeZfeCEl5SXbCzJJkYZLl2NFfVQBUkc2ohVjGR8veEX8qtDaksrqvqWKVWZl9jvFRNU49m1llWVZSqPehm9Q/nBJieCYvNZwe7wvRrv71Zq6ziVj/maYOuTEZeUjdiVlG8V1OKlfftTNLIZbBAPhxN9vGYzOPDNFEgpxiZ0ejazGi2UAVLqvYjdbcEbkrYWqLlKi85WtkYqyYX5hj7JNk5orVstFXMptcSBFmgbETgtBYJaEgoKKxXFLX+H4X7Qa9Wbt1TbOvypwGHejM3WcSs8mgdbIgb5nKxJWKVL2+oiwr4Q/TSSanxQTeLj2GsfPvrwpQSPBb8WchV8x1PfDARDULHvrjVndtR760sYzfVUmvNzahvU7mj1b1W+Sj5GtCaRVpy0lYnnZFUNWuAsU+rwGPzdERHJoNb4TfwxYfgFREySSUpLHPJJ8qEO1R2tLCup15/htJTRYyaBsvT0lBvzLfNJWntaWnyVZLZpUixh1dRmtVZW2ZYAFgLyUqAwvc7LEcv+eDM9lsMLgVWCNVcdHG97878AmnVWtqUVNlUWYAWV5RXDGnmTAqqyX5poVOyxLJ1eAxB5tb5xYFut+H8JiqfTFJR1ShgEAVeoYPCdNNg9Ie2TKTMUQ64qUzGK5GQq66oag42UdOXqfpVz9lDwSEiJiCFbONRCqgp47dV65gEAyp15WeawZbAsJUxC0O6XJkOOvS2N+X8eNJWVNXRUllVlVobfIIMC7Y95x2yVx+AfFGW1KJaV9MCsrEjUX9YuA+Bldx8VJaQnu8wTcNVZRlI68duqpxlKzenmwWDSGWrqzekIzacrzKz5QUhsiAT6asB1umrKenow1fNxzLMKavNzRxWlTScox3T9tSasc9aCwKdHKdoDxQA5mT+FEnwDwO5K41yB/xbrGfUMQDiiWbAD7u13XajKyirbwLpUj6jHSXnzn7Sa/oPwbwxslvxxRpCz7435c2UWSmuI7YbLyworW6CDGvslmOjLyjg5dVuSL5Z7FWzqyooMd4KBEDQtneHpZpVkYciXipH1NXyaSUfgofqOmlASOwr1lEnt/DJBl2FPXcBfU1r/JUmDbkFD6Gwt6BA4tkogHJVolj50oWzE2ung8vUJfH24KcIxvLmADja3bZdVDepCjNqgWv4RmHAN6j1sVA3lwVVVineF4vkoB7t+V8oG1DXkCST/2r+eq3+za8FKOqooKh2FZHDVuqYMjHw6jCVWKK3VVhr3pcLpd/rdB0JDNyh7KlwjwTrcdGx47DFxfNhjciHo0c1b7Js5RfkJPfKh5MN+WGSwLSvyKagMuDFUUDFY82BR1TMjMi8vsNn8Z1M4tG3BjqCac2OvSavEOo7R/DFRrxKA7jQYxhKCqPO/QrSBg2WOzLf2bUPiyypYobrzY4afM0/IqIpiv3k8mA68mMK4X1Kw8iAxtlWZdxQV1Jw6F6yEttiW99Xb/7aWsVslX3d+0ewrwo9q+MOQKM8o/PqZWWMsD62xAo8OFLajwcLm4cnaZgq2QckL4IA4CW4s3Iw10ME0EU+gyduCYkfVVkbk1Qq+ZYxUPHuPC+p7ABcFw5UhPlGL+IvnjSgNcFS45xNeInGVwA2vic41wb3TNjQV/P3UNrRgZ1bMte5AGw2x1hpvKLhC5WDW1U2ec0b1dcJ9fwSUUmFVXKSo2dTbwDsEcWehNguiclDacqiIGx55h2MPwYdPrqUmFByEUiuFc0xcL3g3Wl1mknMM9yiWWW4VpBiz3IPB6NkJALeWDWYOayyOwaA2Q2erN9gGuLYurWxtqc+3mcQMKx5VWDQwM1BU1V+wAtWtGe/rqPz+DcjglPIhgg1Kw6d/eQbWA4tW3FaGoaDCBd8kgGqnfwJLGKHu+5PPBE3urGFpG2CrpNIep5Wgom6u1ZwiXDXQnGU5O64HrcwwYauXDOeqguZ0hMLR6D9oWjtR2pPROFXvTQMpIsX/M66joB7cpJyipTd6mIZCn/qd6HuPi5kgLhFPbBUnZ2Tir/AY/dyM5gXmvMooEig8pUwQu1e+I/OO6tIKSc+tn/VVNVCMSAdhTJScQOGdWNwDr65YCCirIkoiKkRC5NBfN1wH9VlvyBkrRhIkmK5sOCcRBBpto/0m8awPdjWNeWP9+nx9Y5vHbpgJJpXEZhJoRaU/sbGs2q+XnVwRCk9lXYGBizJKxD0GHpkaz+jOT+Du12ybaihAs8bJoLchwVjDUbkgD24xoV8As+Ffn/D397GAkiIymNka8giXIVdiXFV5fo4TnNNtKs6nXJqJQG2qLGfEfiIliQ2WxGCbWFu7D3pEbIrBWzR3ptVSWZZXWBSPVwDfUUeVdtfIBgs1Z9aCDkg1SfSH9phSCG5bdkmjTIxBUkWvOIqWTnAv+itEWt6AMQVFfZYeP2csI56nj1JTHtG61xpQZJfmVk2rCeRN6zWTQJ3xTwMozbhmAoWymwoF
*/