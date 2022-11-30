// Copyright Kevlin Henney, 2000-2005.
// Copyright Alexander Nasonov, 2006-2010.
// Copyright Antony Polukhin, 2011-2022.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// what:  lexical_cast custom keyword cast
// who:   contributed by Kevlin Henney,
//        enhanced with contributions from Terje Slettebo,
//        with additional fixes and suggestions from Gennaro Prota,
//        Beman Dawes, Dave Abrahams, Daryle Walker, Peter Dimov,
//        Alexander Nasonov, Antony Polukhin, Justin Viiret, Michael Hofmann,
//        Cheng Yang, Matthew Bradbury, David W. Birdsall, Pavel Korzh and other Boosters
// when:  November 2000, March 2003, June 2005, June 2006, March 2011 - 2014

#ifndef BOOST_LEXICAL_CAST_INCLUDED
#define BOOST_LEXICAL_CAST_INCLUDED

#include <boost/config.hpp>
#ifdef BOOST_HAS_PRAGMA_ONCE
#   pragma once
#endif

#if defined(BOOST_NO_STRINGSTREAM) || defined(BOOST_NO_STD_WSTRING)
#define BOOST_LCAST_NO_WCHAR_T
#endif

#include <boost/range/iterator_range_core.hpp>
#include <boost/lexical_cast/bad_lexical_cast.hpp>
#include <boost/lexical_cast/try_lexical_convert.hpp>

namespace boost
{
    template <typename Target, typename Source>
    inline Target lexical_cast(const Source &arg)
    {
        Target result = Target();

        if (!boost::conversion::detail::try_lexical_convert(arg, result)) {
            boost::conversion::detail::throw_bad_cast<Source, Target>();
        }

        return result;
    }

    template <typename Target>
    inline Target lexical_cast(const char* chars, std::size_t count)
    {
        return ::boost::lexical_cast<Target>(
            ::boost::iterator_range<const char*>(chars, chars + count)
        );
    }

    template <typename Target>
    inline Target lexical_cast(const unsigned char* chars, std::size_t count)
    {
        return ::boost::lexical_cast<Target>(
            ::boost::iterator_range<const unsigned char*>(chars, chars + count)
        );
    }

    template <typename Target>
    inline Target lexical_cast(const signed char* chars, std::size_t count)
    {
        return ::boost::lexical_cast<Target>(
            ::boost::iterator_range<const signed char*>(chars, chars + count)
        );
    }

#ifndef BOOST_LCAST_NO_WCHAR_T
    template <typename Target>
    inline Target lexical_cast(const wchar_t* chars, std::size_t count)
    {
        return ::boost::lexical_cast<Target>(
            ::boost::iterator_range<const wchar_t*>(chars, chars + count)
        );
    }
#endif
#ifndef BOOST_NO_CXX11_CHAR16_T
    template <typename Target>
    inline Target lexical_cast(const char16_t* chars, std::size_t count)
    {
        return ::boost::lexical_cast<Target>(
            ::boost::iterator_range<const char16_t*>(chars, chars + count)
        );
    }
#endif
#ifndef BOOST_NO_CXX11_CHAR32_T
    template <typename Target>
    inline Target lexical_cast(const char32_t* chars, std::size_t count)
    {
        return ::boost::lexical_cast<Target>(
            ::boost::iterator_range<const char32_t*>(chars, chars + count)
        );
    }
#endif

} // namespace boost

#undef BOOST_LCAST_NO_WCHAR_T

#endif // BOOST_LEXICAL_CAST_INCLUDED


/* lexical_cast.hpp
UPcZAgQPfvwp8FQi0MEBFrG94v86OW+BPZz8i1t+R2jeGC4tjA0bU2aycAEFX7MBVyqo4DU+cqTdQtqnlQm7Wpu34EuOKxhHmQJcCPf9/JLszjYA7D5k21tFc1yfLZvzE71db17VFi1wnl0Rhl5DvDmStnT9LqxQ/LLFDy1nQLLvncqZpcH2EH4ve2SxDZ78nibCvIEj3DNrN66VByjOnYOr9BEsWXRk8Cbzu0zITKGbFCkgl+KYvsd0MoIYlhyGOaIm6sq1jCQ12FB6fvy+ONK6feo1xikR58uyD689M3LrYhQDUowAzOL7kXx6k7nPZ8LJso2LvPSUjUmz807FbSZIegqiBuKzWoYdo5NzqJ4yQOhZeneeYWvM+adfBfhwvMh7ACaVTr1P18q7k3XNW5kaXmpXmvrTG3aTEhK3ouhfSJUOS+GN6csE1LTNLnqUIP/vNYCSYUF3o5rdCebSb3VnXeZskSJTUSJa82WGhMOFjnHxzb9YPnuL1tuSiFHfpdJg65ZHOIryCxOMedfCTIVlIe02ftbp9enmW88FZiJSqr/gOWe5tSa58XsrpQRFQTCseQD6jxKuu89rI4DB7EIfrbbmnrztZXh2GAebaC49ylmyoY5ggzRJRnsR0F8MRC3baG3BrITOJgitvBjTCBOhT7l8MlGQeQ7Qc+eGW4+b6gQb+Czu/B9SUPq95Qk53Y+3OB4yaT1iENcDpbU25aihyYck8BlvzZNvibbJWMJzGcaEr0qgK+9OmaR7COxFG5zDsr6414sBGQpg2IF/VD2jdBo4mS9tYmoPAK486JGEC2gzPPXSOQGxIiOt33ToeOQt+m0+8TSlFazv1ggPU7L4MMQ2i+OUeaZZLLcgpz+Owv81xa0XUI6NgL14+Vgf4BxmzuHu0rIJRX36x4ONhmlvFYEeFEI7xGGUrt00agAQkEz5QV0wm6M1pzgp4KYgjkxG9rvvijLSP8LWj1YOGESTsCW5oEojrwY4TZnespJEZwSkSLmx/hbhL0ijpJ9W/P3YlDpmuHYV7lis09RMkXJaLjwVoVUeJrYmLtrbNIxJC9sN9UO1I7xeaFakdgmsfkfisNfadzR79+zFH1+i/+17A1emkU/85l/ExKLcG1QmZEPxwzHVR+BajXR7C+jbVwF2m0QwqXYiu8b7qAdeOgvbkipy1XIEroc0D0ZMQg+78Y4VMpX9+QYs1RZvDdWHngl/PI1NBp7PTUfQUiKTvfkhcIq47H2OSl3kJrPKk1ICB7S+yVZift8A4HyOilDiyTAnr7nmVBC3uhkaUoJ/+U9mrdrAkNXZ25yy0eSZXrFMO2fWJIKkOkInf00i5vmCYu2we0HP5pjlcbu7W2cbmL5DforG5Owou9buAQfKcNv00D+BrTo1mmWrSQ3UjkJ085eUVqHSfOMjBN5nqCkqfHlOws/5OeP2kPXghzWaFjk6ACz3jxrdj3h81r9/kXtBsuhDT33HAH3F4U6A+HIdK1fQsY2dBLh+oI/jX0q1vNlX02oIz/FBfEZMvgnwf9FjfcrxrxwaId8Mdu68i8gtK2ZW0YHkoAXAtox9gKLbRC5f00eLafLJfySykUIyrvGHm2LFPrzDhedDMBAQmguEfryL25N2V15kFlT4BkZ1pa/LU8jT+NLOdFq8iN+AQScEP4NGZlQhoL1HlsEp0Q/n1JxJ8kCN3QPjIuuZlXlFFJEdygy7GulxPbmzLxe95CZBGPoyMtaHnA23eP487BAq8VIPT8j8NI/8zHD8kojHX68rbEN2m0khpOKpCTBa5o4BUKcvj4Qa4SaGNtpfCf71VfIQZ1TuCSeRkdhKMFHZoKc4FD5HhqsSM96VFgvZfC3Q3tDF42wuBjxEDj5C/tUAdiGdAUjsONlpp3jDmsz5pr884Thqr7YtcskILiLICRJ/A76pOaVa+JN9Fy2L0EWFfB47oaWb60KTRhbQ6dyWZMuiBUQpuJeyN/n8CV2Qvap3M+ZVNB8Z2PfVWIG73C91g8338+UzjRyPJs4Npuvwk6HqOBicOR9rNAi6qHmta72xL4QnyI+vqKGdOVitQ1uFcfys/Yui8nXRMAORaK3vf+Wdt1+mGoi+JDShJDPnkAWYg038905eczxmefnbCwAKgPV/EtmwyE0l2RDK7EFnA/buJ5VlrZkP6J741aV9Ny2sKUk1YpjKJNyxCSzItVby6Tubn3JQE5AS1N0xBOem2467QhAQvxzY2mg3TC9vuloPLeJoH5uHCgfp1MOOTqNAKrIb/iBbrdDQdMWjukvMwXbf1YJoDbzB4UyBUv58T/MfCZGpybbrCW74JvTPMjna4nQm6J2rwUs8P0CWixDANUXM0HT69O6rXwE+7EF8kHTjfqvCPWejobCiQ4inzQEB5Z3VzUioyxwqdv2DqljLkHZptkqcl3tu1/9yJt0Yzbws76fDpakxOrYsRasT8WPR4gpbwE4fC8ouCaK/yLqIYY6q8Lv00bq0HhOVyNo6gpgetCyEbKnFagu75PicF4c/kVCzS0lfzhPQBo+mtVB1NKtrneijitl/rcRGnoQeZgkq46ju14kDvrcv3h5D/Olvtfwz5Qt1RJAg7X9ukULqsH1+8C6vSZX0/AXEEBwTAK4gZjATZNdO2hogzFKWs/hPdRM1Aqy8a8shR0tYIgaCPqE6rfoH6/f2oJ8zYm/m/ZI2rmsgTS2WgcWvafnjAj3k9DE321c/dsuAJTGO2Nm60dBpeiHT8cDR2e1trqV6/iUt3fcKtn5cRPMBV3Samf1Odn/4WbEoPi/IJQd/b/FJoftn2X5KP+7YSF4D1vhE8yJwTPmi7ji+/Wc1C3NCTGzKsr83KC6U12lAO3sKEgUgfOtS7RL5EZm+KODXxGAywm8QFJzvpcPJjBT6M72UJS7igXepxZwjgBdGAF7GHXMBY/kb7TSwSRaW1PLOPkNk+/rM/NtjlEJrb8OLxUq3Tk9X3L3X5qggPi+wDiUznKHZsTWQm/6K/pIb+Nj29Wh78cw9zRB/ITHZBgnCS0ijGA+Ale3In50ZS5/kEv4mB2sI9Uf6MV1H0fRoIHjSgD6in/TGqFCGlZXH+OcZSN46d2thdfg35rLON8jWeTDifYLDCb7ojJL2ospt/Epss1HSUbel+vU0qPL+2+t0qz+XDquJcfq/kp163PnDEmUaq2y9CbHZbCtTgWBEOXKq/uxJ7N/pbM03eBiwP86EXcYpRRQoUF6n//9CDgx1Dq0ewCKSlD7xlB4K5Vip9Gxf82w20LYvsq0iCNCnZdsYir/3MlaYY2RcSJTyVbSqXiHLkxJIFo6BaPu8zkJ2nvlACh0uNfCITxHIijbdpUqApIrDKEsvsnFxi7OB3vBni/QkT43ZBsJezGiRtuGLJSRQt1kNc+3ItWYfH8bmUo2MTBZ7hRDCeVL0LhvzJBKmwb1QIZQ0KSCw7Ec0ueQcrF9lYLtRGCtsgSVW5Lx4GLNr4oTVBwlG4hvJyLihzldNkLYgVaak6v1FN7JMxcEgrobPluhc9pCofVdOYel725RQnzD3PP1ctASR+LICm/urOdSI5NyxWnBYacQtQ+DIzISn5TYkIp1J5QYfdTYCJFrSAvW4sdc6Q43Pz0bRz+ayhgr1Dclz1s3p+RZc/xRfBHI/GgbKDcat6QKOqSatjL7KfuKtvYHTMtV7wHtmgycL+qef2YUAsMPGXoHmkXhXf3pT/ZaP4P82vMXyLgVPHW/wzXjFmRNJWAV+sM75gTwCzmeWKDfZWnfVguS4au6mvuEPW6tndw+427ClbchHH4JG9z6UL3LsjrM/9NYfQOM+8RghYsDaYjvN2scOOlZ3xzd6XzMKMTOMenV/rmAB/vmYn1cVFyfNEh5QoryYbDRsd8r2DSlcWRqZ5tjn9NJg9IJUaHsonLqUR8R3lpbr5XwDHweDOaksjv9LZGq+dOokfqDWLhdIsKjqGCdaIcDh8AfEFZagHxtli6wM3I/2dfaP/w41c8dQ1DIgQjYxrm8oYfUgyaOYRyyAoriLIOGEaeU+H6YsfhPGspNAItn+WC7ykCzi66cNIkdxhK1WqpL/g/w1j9pXvTTcM4jL3xqBVg4OhH/Ok3vM0hL8iKn91/OX+LwgQijWcbCryqubDXQPJ3LOwa+rGwhcLleLdH75uQTkK8tF1yVhrdYKHWswO4+Bm/UNRAuVMbOvjSpklaKpXEzgIxAjL05bXhoJXA3bblMp3mtpgce91giJZn5wOQfKm7n4BZyNlzkMpa57X9yZzynCejEW+7+q3Glg9NeTeFNn/VwBQPEB0p/Ge3uSr/D/gpqZqbXqbZ8P5tRz693tatcYZDUJw41CjVEfy+Ntx5TiWtCBribH/8Tl9W6aJcxWt7eupDlJ6JdT4EwGTyDAseSB4/O3I3FWcH3P+y7e/gs4JO0kExCSrzklf4UiigGndkZW353ZYxzBW8Hz7VJOKJ7HPExik4Dc2m0E8j0G1NvmsHQzQhEXeyT8xC3FY4Zzk3yd5gvSr++4mldDnp2aRyvvjTXySsuDU8TQGwBq1KezM6Sf8Po5tV6li6aTcQ9K8BprrlDA9B9CFfcloeS6KZ0tbGreLb3TlSqtzZo7/SjWRvENi4gFK7zuZ5xRyC1hmwbYwwjRoZABuQwt+JZygP+KkE2rGqQIbcBsIthA8EVM7CVOhAT7cpGJ66nQzerP+GRWk8kCTYelJElGCEXZBVcbOyAHyCysFoR2WbZZ/SiTfFX6HN2L0CbJTvaHPIq5PT7+WL5dW3INOXWs6iWWU93XdZ6qNvLS2JPaaUUL62cg1Y5VqmUKWqSE6NK2r49r/y7iwcI/VRYdOHYnOyxopNFLZlepGz1KoI4VRokSOThoY76A46a2ddzoLpxn0MM3yml7JnU1BQI0wCqywlvgIIfxPo+eViIvKFL5bj4Ovzfa1xuwoi+4GFaRRO2v+T6qgYgnlUR8/iYcDwXJbtd0GUMOnwfAJarW0NRphU9yhblFLpZt2W0FX3j9Mjabda2RXEHAYqxxf/FpHziqu4jeRkaep8Twjcpa4o4CCgFahU6qRCeQR9nDwSZ874HtAC/hp3icrqAX5SoezqPpxSVAvquZYV7oVUUNm/Flv5EtRJZBPqPYx0V6Q79ifK2GH0PABsT3vry5UQxy1cZisHahzDbJZpeuchMRAyKA26+fqLa8nim8Uh0p+cixAAAs/9N09LiJGx4gBO1pGxY5MVI3CvbqVoS0tQGmcSVSmgayV1OuEYM5Ei+kjrHSDqIiS/g+ZtEaJ7z8tjqyVIKzGbAZr/KpWNzvIsfbYo6Q7Itkz94FsagSgzIYp0k5xGpyBp8jOnX7ttI6BzFyS5Ww0eqPaYaHzKxuIxQ8kt1+Td9pe00jN35SsGXJteT7eNg2H8pWpWUWK7Og2NFMkFiHNxLtD9bdg8S53mOCCXyLMwd7y5qw08GDF1+D5K9F2Xlu1JJfK2nU0hTlmRpWnK36FA53XXs4uj9Awcbp7XnoHKGolAEngCr8GJGlQ3aGiIP8bWLurk2dNuuBHKmn/g8i6ml6V3P8B0Bo/OF42IHwhYYV+aMtG4l0eCpDUVYpoDxlzGyqzTf16lVN5Mj/lNZX9eu8z7WxiCXHn3lotDsgqC/v3ncvp4+qSOeQurH7PVlVvlsdrQCOIanSVWEeyBFNc6BbxrV0h9sVHFX2OGmavZyu8ibgK0BidYr+iq2a03N/kxFKwRrdAIKXukWyTujruLNoqMik4UpNjluG+PEWpepud46VrnfjQybGOUEu5TfIlI5xlfUTFQQnyk4o0kapvCd4Cr4+ik48FCjfebuyD7ucd6hu+TDJSrZWme5RdkJUrtBRS9xCdqGpInp5e0C1uyP+jGi5mc9ggNhv8PTX41IbG+CZdbeFrZnbCt9QnqBnJUeHoIO1XKtg2jPsPMFVADb1ca4z27ZYk/B8GoxHBy5r5/W+zXCWieXco15i+DpnzgRPAAan/N4LhRuxaPk+Z46x55pIoKxV0AGPGQxWBTZgqo1XXnAmqBMhuFT4ZfActR1eT9/ccqzLvIbEfsX40o2qTHm6CTNxOxpoEyPeH6MsGPYyRqF+qOppHb7rK2qcfK1YT0uydnAMQaU/aPg4I6l+1mKBXOglpqnW37AvWUlJDdJeBIaW7f15R77lvvrSvb2ReJfoh3ODHlBPy+vy0H13FgLIeOtwfMvXTP2bl6mBFXZ5ya1QpbRIG6P8jCRIxuV2q6tufyvbqyNzdPG8ilSsZf1XRo/duZBjwdzGaIXfwd2kzNg/6Ehq1zTtYLb0h5LrL5ecle/hP7wloPL850CPR6WRX814vJ2EMIZDqWs/h5tl5+dqLymXlgbm/ML3Ko2ARW28v7nnJfUUze4wKmrU7+FyDoSAWHfrDh+S98bO8+eY7qEAzMZxwBJaAJJwvo58I1qyBL7BdBiYQQjUs7iDrfoyTSifjP+QW4AVhrp4HpfvYaOFwuQyWqQ0bGE/a4PW7H9cr8mUXo1qQtjulTgR1hx11aJtbivYjhOmLEc+L35hpPzo3H2E7rG4VV8vQdvddkZ86zfFyW1FacqhAFL/caXan0myXuZoDYqT7f5DpcYD1fuTBddmZJsPOBXZGxBYKMmUrJD4jj0fztbCrLOp5hQnNfs5KqWLezR+wi1E9MDPE7mZPuFQtTzgCATZ6w/Bn8eiOmatWj8DqoDUeWBgNZm+0eRhnz3C9O4bzakS6E/bd1Ckzh0ObrWTkWXkhnSzDrvSIB9jGlQoHnNtpIhALqYLAR4l34q4CqoKSmcL0Tp7/+0FSnxinLt5Jar6FdSSOC3+sopR5h2SJYDgjKE6xQoCjka4irxBXFM/Be3H1sfKXlGoc3KfuybtcRxNKVzsmkqZT2o8u9BH1rAyILUkGJvx6wVMd+Wk/AK9Idv7w+IxwlWhjNCR7GDKEfonPZJEEbnJZVlMUtb7HJKxGHtvtqb+nBbVkpuPobpvnYMNOuJ+PwNwDvlZ91nl+fwzfQ51PmXK9v0cM3KC5Ffxvx6Lo1m2Inf1XpJScHu0GFmcp6e2EmI2RV787ig5WoY4WRbq1Elr7wavZfPiH4yRtL2sDYQP6cgUz49Pxtqu49raUjXuackmhIPWYUiYTj97gOj+u5GYcxiz1sb2m5fuEMm/WcOy+VHy8Q+1YXa8Z/iOcuReri/oLl88zZEh8fwDe+yI/ouToWmUBVyiKSFIOtjin4ZjtdSxKkrkbOTUj+U8BgA9C+E/Lo5EFdE7bseKQU+Zc9HMcCowKSEA8QxvYJvjXamUfjKwwvEGAbgmaiOZ7EbCX6fZEuZd2p2QLIqb2Wm3yDVvYCVBxDViv6LfYs7727bj0M88bWjptjmPhiCJQ7XcSGUqhzja37B8pXeE9zVyWlFQ7/Jn9DeQo5QvFRydx/RkJLatT2WnxkqTDzAUnlf42WQ7aKu9cTQ2AfNKQF2y3mHef6Brw9oHgCyaPhI1RqYB/IGJ2U8nFqck50WiIru2W7Wt9aXImsrn5YVISHfV3wQAogYtn0U1cov+Hv8EJ4eZkd/yCbXrCwmnrZCifEQIDeCnZFyKkf3CCvnRcXfPvjcQE2j5yua34BZrcCnV47hZTWekN5lLcXcqmHBiYDmjdausQacD
*/