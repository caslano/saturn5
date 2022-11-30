/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_07202005_0851)
#define FUSION_DEREF_IMPL_07202005_0851

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/prior.hpp>

namespace boost { namespace fusion
{
    struct reverse_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        template <>
        struct deref_impl<reverse_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::deref<
                        typename result_of::prior<
                            typename Iterator::first_type
                        >::type
                    >::type
                type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return *fusion::prior(i.first);
                }
            };
        };
    }
}}

#endif



/* deref_impl.hpp
QZnvxgBzaUJojaPGsw6+XY4C2Kpv8YELbUtfxN/ddwn2WMenbNM8f07xLLROvcLSy+z033Squvca6L/fQl5Pyl5PXD8XDDwlRP4UdYnZrlFtt/gWMPmg1xEdZDd/YEBIdXMO6hB/Yx8Fof1IIdw+qeXdqC1pSRbEv1nDJwJp3qAwZ3G5HhxDl8pqBF9b8GEOU2kAozbvZ8rri3yYv0y9Tt8YwoFbz/3FZY6y+GEsw/prcbd+iG4HPay0RPKWUoe3WVYV2cnqSDh8KtUEdTwtreBmRD/seJ+610xWRnSvGEn4Wj71VWqVUTguxiYUTWPoiKOIV8bpyc+JVuqf7S9GirHwQCfaX0+ggCeCJLHEHLY/TpwWYof8lx4BecMnimlJfFNl9TDl386o0ooRMnCh6Okp/G4Y7+af4MLwURiDaNZ0vMEoIK0ZYdpvHDgd8hAu6eb7UY8QGBKOS/5ONjjt3Aou2Arww1ICMCoxFodMb2ymD5x9MyUi69HzBaEgA9YQN2EloWYDo5l2kMGowFY6QDttrg92A1S7XWE4NdlADcH8ZfaBCRU8RkX5MquMhHGRXaf7D2vp5vHRMUEwJBNwV0Fx4wdbvSyc7JbJmVD98LAWKXjEPLECYzyS6hmS3GryxT9jpRUHb9ilE/vGBxO0z5Y8PgWclZd8r0rhs37YLk4SI1tq3XCZIpD6y2syIQHMkpW1wbKcSfdWj6v8jHdeKcz0Q8+5lTDzeUHqZ1xBHiRZdJvSZ1qiPZxz9cDLY9oUr5eMKBTNjSjp4ni1c9L56jWRuiFgpNF8ozn9JtYDcrLdoaZ/ZXnhAX8aS172rdlSB6hwof855AYcv06xOu/a6VrK/MydHhgyNiEo5f2D+VG0uMpFXsO+N2+I35/Q09+8jJP1Igkh6Xwb+gbh1mHPY1YDHtkvO8m7kLeAT8Jela+S71zTPGynvGRqeGDTTt75E+ElGvjQOkGS00zR5EYsSXAAa3K3RlGmTxr0pxfOQK8syUlOenldecS4XqwsSQ396gt1LVrkUBHNWYd/JVzFOcfxk+mCF+8ovnjzpJd6GGpswy3CB4sgehIA9kRWFKnBL79+kfB6bFd6vhRk7A+T3fZosn+9D0NGO2NMaRMbFXyBKq+dbJpR7m4uiht4DQJuOCUuOxYF7sa/wjM+NLMwpht0VySO/38aa48lrwQoApelVccOygNLgtvkdoKnzLrZJzMnT+t71HtbI1Yz6sxrv+J/RCl+vExPzkTjSSpX0WRKyt6GhLTaCKLpd/UW8F+3yfuwwfUg1NdPW3lR9mYfiah05aeRJ0i6p+HGe1DqLFqP0wNHUgofb3oSDRLkHNna9T1HzrFOGpUV64klalyPOQhORW6CoriaqcVbXyQ7osGZu0EcjI6cNM5q1Y+KZhDrsId+l1CJU8fjJOvZ330ap67c9cXI1efn5Q6+jM4BE543CkjijoZpjZsKS6g2xBN3/eNcSIXIP6H51zu9okliOaBjQ5o1EEcnCmiW32Ot0K3VLhcBGS75oFrpUiyBNg7jolf76qAkKKAdMw92L9i6kVLvria7t7yw7u+LRCWr+AD13ethOY3YwNRpJYjTzwyZKrgK+7E8kzBeWuoISlNc2QrYuuD9O4GzyHj1KOSahIw8qq8rw1hx/IW+b7LuGFmc3mbt/p4UxtlXm2frHozKfR2W7Rm3MFqCgvXhVB0G7sKuSerqyp2T/ElxpuW1BI8S8XRaD2FpAev9DSS7+EteKyfQm3dNWXHztCp3eyHPRMqw0SbVYy6WYs5GcEcwPfkV+rdfPtIztF3JbZ1jpNQqpVKoxMEfKTLp1m2nBRdtvp1zByYR0Ql6ReRPGMkIsmhijkv5ReQXHGrjqxzKxtgjbbIEectNZI2h579zs/FXjvHWtwWLe1S4tSiIOdw0hRMv9AxvVlLFBTkoZB5vGI7gkACcKD2lASqla3XEhpKZxUqbnBlBNooYOzyxq0gpsXhq8ZTNC2SzzScavpPJRPcfKFY5AR/39pzCEpVfbVlcMbSt7MpWVtC0sl0qzaQS+AgB0IJtPtX7TS86A9pfJmRrljwSJ6uvk5fXGzNQov5FDyPIB/ME4zy6kimuUPzq8QwNRqUUMf9AgvHEGsbn3mhnYHxw2WjAh55FR0fAcEUYMDngedwJYAvGDes3RUjjXBSY/XZhL0XNME9r73o7BlunxgVbaQkDk+xpEVdGJdqyxjqYDyuWR4hT2F9HeeutByNaOxQWmYqB+F3pTugR+peFvkWsMvnvkRLH8MjOkTxSS1M01waEcDEUQttX6CY6/VxRu0RqsnB4i5aSMP4HRoC5f7RLSZU3N1gqmZNiboGY5Aq+DWKEpJiVEGNNilkDMdOSYr4NMSlJMQ9ATGpijPIQ7jGUSrakyH/jkWlJkc/yyOlJkft5ZHpS5Os80q4F6SSC0iFyhhb518TIDC0ylhBpEdmjCTPxqFkM/BV7ikwKrtzBlkjQuXBsWwIjG2OlNGSgqY+gdzbQ/ZUM1SvTleIdiYMNw0NTAXJusiHgGwl9ctyOfZKwFkM2LsgjAJm1LzNTp2wnSVmeGtw6ZzCNYrbCnxdxiWHeqqVWpga3zcHjM4jBVLb1OTSHYHX5isPM6gqVarMV4vDEidVQXA3FibtXpjLZR3WQZxN3l0B74WFVsHg+hOpExiitet50cfcKkcnNHBJCy65jj/o4pF3cXXMdY80cEkIr5xo0M4DmXIMmhOq+aNCUgOYXDZoQWnaLQfMaoHmLQRNCK79m0HQAza8ZNCFUd5tBczbQvI3TBBHNm605sQm8JrY/wVUD1SFrJx1wkCqvIibuZlh5QTZE0QTy6FZe77EgpfH6ZkGsY9ZFNHgN51ENL6AaZr2TKp3xOieoGg5Vk89YCIcBoxmGHyX9y4zG1FjwGUrjILU822oA0Fkp1QEHQM4DQ6BFiEXQIsSecAi5mYnMVFjl+104aBD3CLCXA5TkK8gH7doClFlGLswyz6ouFVSKjasUXscOEIyaVK1pHElSYjNDkqi3GobqrjPSLIlSgqG6uUaaAGlzjTQhUUpsIKM1XzTSIFR3i5E2LVFKMFT3NSMtBdK+ZqSlxKVkDQRTIfE2nthwF4a5Y6qoRQyQmbysnXiyKt7vjwhVdqwB6vc4y9N7NrptFQ5/qn4vTez3KWlT9/sl8X6/5WrdfsukXl/XrHV8EsCWpF7fTOJGcerK63IuowkSDdPqilS8mDtipQu7JHPqunHhDTQuFHdbxaB1vrjbzGUNd4WENyCGvK8QLK6RhSPouwk6aRQHcA6JTxxr0bfbKJpL8woT2gplqc0W4c0kaA1W0qI1aJvabJ0ICMvMLXc6hTfxzDScFcycjwtPmAeIWxcmuBmL93nGexP1eXZQ69agCnif5wphKwAbLOTT9fwhTSHw/nXFPr+e6teX2OebE6pc6/MEVcOhapoT+jxBDQ+ZqMfezdq1fl+uq2Lq/RCeq/X7duJui1dXzqSQthTNDcpDNM9BBtnKZpiEAAMwR5CJ1xUYUYMRI+Vc4W25PZWrNV4LvOgoYlzvEVm9iInlQeb3JjFPKiFRU7DXaGP7+GmYRH/vOhApLmAkWMZ9Fep+KEIgM5nCYTSUEnc7bgkCWfjk3VGPvs6I9SXE1kaD1eYpoOts8fhE+NkQbZkCXIrHJ5FHMsIU8E49Xg5Z5YNZ8iBeDZfw3HfrFxI92+Ga7BZcdT/apk3Yp5o4SEkTB5qlT61AMicoEClZgRywTq1AfIkKRJygQKREBSJOPW3YTrNOaIDtOO0UDsGwwLbTxLPCxrbTxLPCrmkWGEECBG5m3ef4EMICBLvYxro1WHXlLUkaR7yaxln492ics1NrHGmSxvFcUeNkJWsc6UoaJ0/TOJ6raRx8TOu/oXGkqTXO9lN6g/D1CXTK7RH+BQ1yhn/ZebtBg5BOMtqPg0cN8Etam9o1RdWtE+82iHdHNBhowjNac5P++lStPYwPxqAjUO77SVdv4ieoN/Fq6u0hbZm1XV8IPaQvs7Zryyym0rEpKT8A7NYBVR2wWwMkj5m6RhSn0ojiFBoxuU/E65TXktEp2KfuE7RSu6IOvQU6SYIOJfuz/wH9efYK+lP6+/Rn1hX0p3QF/ZmXpD898qBnSv050X+NjbbgHfImr4n2a0povyYQ3695gfZrkuy7XqD9mn3J+zUv0H5NomWXEtD2a7gp1SoXW1F/010u+W2rLws6Alb0C7TptQ93mciRNr68gW3xNRagnZtQKdua3WIhwzlt12Zbtkvg1t2QlMU/HeSX/iN2wbAfZCsy2RFQ7XQBGZV6jRWnmDVACM116dEe2kHj22zyK46xEk3l48G1ZgMJKn+FSygxBVaAyn+MFhA/NNHW9fI5eFbRqGy9iywbt/0Q7RjldkrNUguLNg/iaTfNbuiSrCSHF6nFN7heQmOOuP94cc+GU+wFNItsVFpSLol7FuqhwjxIy4qnWSHoiQdtckiSh9uW+/cN4+Fo4Fe+enGPZmWJPLB9yBDnkWwwxT3Lx+WAFdnTzDE3D+IxvhASojqbePqybwElIfdGAkxutqkmIlI5p1HpjhtzQsQiiMAMaGW0DzMYSWMqXVgqXIwkk6pCDlANsV9pmyhqtSlFtaMxkSSHFunvYBrzGXFPs1E/hfPEPflGDWRYIC1eP7PHIWjUT+F8OWzDk5xIG7lA7KVREF/l6J6wBdFtNYwyyx2sBNqbZhIlOJMgC2vcSxBC2nYrKCL0zl0k1eLWrKpPJkDWAmhsLRS78gBvBt+mxrVIhVRHm+zZhnS9aY9bgXLpspN0NZPnoR/aqJYrMhqVbXeVcsmSphtTCi25kpLR3BaiMJnVrsdKbP9h/nS+z1brow222mb4AyGYUNrsQhgA0CIVPlaux5msD3U3TGq9fFZrF/eUZfCbIY1K6SpJ3LMsg5u1NirF34Bg7RzQ9BSsvtMh7lk5h18WQWAILr2ZG8cisFPcU3czUy9pwBAsWxSnnAmUF8UpQ7C2LE45CyiXxSlDcGlDnLILKDfEKUOw7L445WygfF+cMgRrW+OUc4FyK6e8pgHBc7VJxa/E9j+QtHVTnas2OonqLuONAaKl2Tbz5G6J2zRXat1KM33mbaTasVlUB7XKWmyVgNEod/NGWccb5V5sFGg5aI5A4RXaDTdG7SyArcbq1iJEHSdSt47vmdbdSwDFV2vWYXrobJsaFx6tHNE0o0uXkaypUhyknEAuxUEq9U5ORcROjgVT7YuhDMpMZL2COK8ggauwy5toLyTg0KCxEKp1MS7tJLbSh/u4sASCMqxswe1sqr0A8mgOSAZ7oCj41gjKZqNiL4ImNIQSQ2VzdNkoLbKQTGqJFCy7OZ4KGnTlzfFUK8mkkZoCqYviqRAsK4un2kgmjVQIljXEU6dDakM8dTrJpJEK3WrlffFU7GWt8dQMksluLpN3UUx8o+Q/yZ+Avs6ZSjtJ/5faSZpaOy20Ta2dlvy3tBMZ2yUrqJ5z2ra/lZu8oRz06LNMQ0198oxULbtZXZah1t/gyhnDB59o9Ii/dyjuKUzR67rl2ks4gGgNQaENZ/XEwmth/JD0RAwtjONZaagxEHEoluKpIAzNefFUmzwAg71HDqG79kwxsCFx9QKKxk7n3Srvgbb4lQnUJKCAyuO3J5jKFU13paaHtF45WdH0nNIq2NA1PcYhSw9fxIA66eGLGFA61CCJeqfnnAEeNcAvaU2kK6Dt+inOdoP49vjpzXb95EZXRp/ceMOzaBHj+x5r15RTuTH+kIqCiEW6cmrntcG8RvfnSpkVAUigkq4+2OlEXcu3R8+3U8/XEDCukxqZluvtGYZOT7i8Ag2SkXy5JS7IVM9Qbimey2QxDnxqKZ6s/Iz5UcPNOWMwLc7UJkog7HjbkMQ8hcXwlbFGtiCF7eO1tmAhzZEuGROm+8+yF6IJMyZJT6RggZE4f5xPpy7Fg/dLemrhfBJxnaw+uRrQhNwhBnwTd2jOCp80rwIdlKy5MmEqfkXN5UrQXGS7MFFzPSBMrbmuT9JccyZqrqwkzTVnoubaSwqLjiFhnpw8qd/LtVRU/WViLEwy1bIGtWgO6aT/0nWSMZ+9uj46laSPsq6ijzzJ+igrWR+tnaCPhtv4VHgKffRL0wR9xPbl/11aia8jeE0mKCWsMH0aAfWn18++Qr4ucUyszn16bYYSI1GX8Ao2ViPDeGuf44Lu+Ke47pjDdQfbZ59+dQ0yZ5IGIdKaGqFGzGT7HMZCaKTK0BRzuKZIqqO4vpgjhJI1RuLaKpMXUV9bGZXSm0UQyd0fN790FXB/Q87v8Y061cdVQNEcQwXgA6Ywfc4U9ObPnCnucerFw8AaQ6TqZ0KPX2XIFAXnGom4gFplCBUF1xhClTkbEg2ZypyNCmDQJv9Vk6oJCiDZPy6ZoC7g9mPyi8VYYh/6dZ8NrOcHTm7A7+nyRXfrtJfdOGZvRnM8esGG/CZt9hjBenp92rHwSbzMKrb/A06OlubWsPtKyVMot2mjRPdQHetF83R1yblASHwsfPtNh5hDPbvIKSk9drp45ZvpHtKSwswRyB50AAVMYmWe8KkUpUciw7NzXMrSvxX6KXljs41YjkaVjujU0Zc0u+eUr+OVjNZpvYfIFgzvfU4BbZ0qmv36+Gmlw2bYu3FG5F5ecfaDHXkW/qoELMrJwpEV/8ClW0ZiGktDyzwY49EESN6YZ/ZLgSH/TdwkSN6Qb2q9DoSot7ampmZsWHMWrmHSr2rHdxSzVatTGFI6cyHm8RdTIL+x8+F3rErHb6aRGU0261hPhsN2tjRL6TyBsR1/wG35Z/HCLDscfnuaak0TIsov3qXYdfCLoTMYWprF2r8fnEb7zA7V+hjUMwa+j9dqhSEYVzsiFL53Go2yHWcxtPXZHdPo2lG2mvm48mQUA5q7GCeaci62s7IspSMzhYAKlc4scluGd3LDp6HjXCP8Tnkym+LWI10I5WGoLIttfagLoU4B1GalMx+ditmvYdvx5q5wVOnJRbDtPi20IIWYQbs91bpZ6SjEMBkZyy9pl8C7yMaNKqjcy7zodn6B+5ja0Z5C21X4hmn2yz/k3ticrHhbHoxwhdATQtATotATeqkn2APB9x3kAVcttgmP76NWuKw5EEYnKC7VOvPxscvof0MpOYG+1NAbDM/XY1dK/oBtU3IKX8oOn54W/vM0dyj8NhrpS1i8avKoj684Zhn7LerWInxVV7U/RO8mpQmQqOYKSukvopDUYCTlxpPsv8DDgkDIN4Meb9m6/D7UmNOhWuGbLgLYH1LtP+FUbOT7j17+wIYeVu2Ccm8nPTLBvkSvf9+7wsQjMz8tWQ/QdZEDlkVoswc1WlwkD8zEOt58ET0GiFsfx8d27mpYPckDNOomG+ug67FeSd5gN/m+Xhv58Z+gnDTXq4z89OtmqFK8tEIuXex03QYtmQ924CyOXiem6zr4r2HgYMe7xvfU9Avr1D4k3WSui+wD4nWRPbdhFkgtBzpGj8SvSsmhueHotDVKD12q6TiXgSTVTnRUg+5ZfvRDcrhwkBKM/PDxMLVwufxXS6N8m8k3xnYF8aL/B+Ke6e6TjYEhsXugUcmQ+y3yoEUYKXjzX/+yRiGQBnYALfnkM/n0TFkX
*/