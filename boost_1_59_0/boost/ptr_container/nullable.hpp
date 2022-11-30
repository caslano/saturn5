//
// Boost.Pointer Container
//
//  Copyright Thorsten Ottosen 2003-2005. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/ptr_container/
//


#ifndef BOOST_INDIRECT_CONTAINER_NULLABLE_HPP
#define BOOST_INDIRECT_CONTAINER_NULLABLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/type_traits/detail/yes_no_type.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/config.hpp>

namespace boost
{
    
    template< class T >
    struct nullable
    {
        typedef T type;
    };   

    namespace ptr_container_detail
    {
        template< class T >
        type_traits::yes_type is_nullable( const nullable<T>* );

        type_traits::no_type is_nullable( ... );        
    }

    template< class T >
    struct is_nullable
    {
    private:
            BOOST_STATIC_CONSTANT( T*, var );
    public:

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)  
#pragma warning(push)  
#pragma warning(disable:6334)  
#endif  

            BOOST_STATIC_CONSTANT(bool, value = sizeof( ptr_container_detail::is_nullable( var ) ) 
                                                == sizeof( type_traits::yes_type ) );
#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)  
#pragma warning(pop)  
#endif  
            
    };
    
    template< class T >
    struct remove_nullable
    {
        typedef BOOST_DEDUCED_TYPENAME mpl::eval_if< is_nullable<T>,
                                                      T,
                                            mpl::identity<T> >::type
            type;
    };

    namespace ptr_container_detail
    {
        template< class T >
        struct void_ptr
        {
            typedef BOOST_DEDUCED_TYPENAME 
                mpl::if_c< boost::is_const< 
                              BOOST_DEDUCED_TYPENAME boost::remove_nullable<T>::type >::value,
                           const void*, void* >::type type;                                                       
        };
    }
}

#endif

/* nullable.hpp
bc6j1TgTEvk6G8gC83WoRpgTWZ87jwqp+c1OK44W7omgkoIP2L/c74JyUPkbg6jvuRq61WvbsBMnuBWgi+T3Fcw/jby5zJtAXlXYSSNaUAr5KgKizno6DilB3zPkVkgYAvonP6OgqW3DHsxO/Qbm8gTygKIhSOSvETxnMC7dJVq6qs80sLUJ0zWydNfq6UCBIGgST+HCkVjnyW9YBjNoBm++WVqWr+L29ZRAdfp1uMu9v7X/fbHVIEGYxDa9Z0LcOIhKH47KhCjcRT9JvjE7HZPTXfTLIfVX8uH8Yzfdv0IpBTUZI9lhtfajytE2unG+XTgNRE39t2dnPoa757Vd844tNrgC4X223OXZ6ZNuyc6Eqx2ujpvuT9R2za9brW+WXzliebA1oOtAi66iywOcoEtj6wPyLC736PqgXRhDbohRc0CtpMspbIFQPYZcoUdBHniQkBzcVfZqzbSHE0Futmw8VtN1f8T8uj/dV4SfQlBVdzZtm5bbdC1cMnObDhh8Hxrx3nptbpMSU6uDkid916uoEPerr6LkA6V6YwCVanMTPUPI+qquRR+7tuA6S3WK3HptweRfbzsDlb5B8oAO/WuaHNVoM4hwb+I670KxKguBSZTowVfpVOjJhId1oDtvDKDubG6C2tMAqis3SWm6nuwhVyxlqKnAkYWvDmPra0Pi9uUGgfNmk5VbKHC6HOa3Drlo+Vpdvcb963Hq9T3R86nX0DHpvr7tqfDWwjvyd1znIho02RfYnuJWhUxyDQ3DMz8g//EY5Bne4Z1Rw09zKOPlt3ObBKvXVA4vYsDXzO0K+JcbjDENvsSmJF5fg05ECn3NwjfXg+KdGyweddoLs5ldlUkPSnK+u30aTGfy69cvyORthc43hD6xWZUPQzLn4WojTLuZIJkKKrNRtcHd3LCMdGXL8wvx6JdAQWVOKShAmdzjATzN3vIaw/2EbPU9hB17nYP0JJ6bIXj7Mm9X/rHy/n4xYtp0tX/5Etsi3GCxZRxJ+yuMxCOgR0xuNLz5psGgjHGTj16KokLLJzUaOjsRbLbB/K+YpcrTBZWn+efLYNHDNrLjLvhsBKa4OjzTQ57v2DzNUVrKCCjz3sMzkUD/RBznIBbpK3Hwl8quLAx8niKSEe5nf2AVnxyfMEzduFZHnIPbr42r/FVYeWdwy3hyy1+g5kPOQX5DYyLWXGy0KRPdZOY5lZcjiilfBcIlILKhiN64UqCzLyktLajMEiylpUqCvks/UlaKLctYSPG/SBl5JvipWgHpyO/gBpbFFf47uvFM4ZKh/LfI3idjJuDQzdRjRi/J+zUMRCHH7+odtfufFe0mH7OZqAYP/EqUSyIIgzQPI0No5FxCSPhXFBjyLzMuQmxoCye7iFyjgz+KcF4gZ+uzo4CcyM7KgQbXGUMFHkqyszLS4BqIoTfpCOCA/rESjxjyY5ibXPMLVCWzQAFxLHCdjgFJME+l48nH0132EejNaPBmLP1+s3UXO0YZqBl8Q49FnqSdox0aPj+cSXQhc4TobtWE97vKUurwZFhun+vwJJM6PEmPOTxB0Z1IRbdxRf4xuWEtSuk4vEjssYndvZ2Ts09x2y3ZBH2BNIequLHLsy1V3GsBc9UMdUfVnLy8qkWvObifXItQKjc2Ne/O6Y6vuYomuM9YQO/nHP2aK38dnqe46fMauM/JKGR0bVVcenPtYcN9kw1fc44u8cMlEDknCyL91l5YBwY/tJoPV3EVkMeaENCnlrM8PoL8ttogcQCSdUDAh0BEqrg1QJwz38AyH4LwDhZeAXRr3oc4TPwGJC7PhFq9Cw9ngPA4EPTCFYlbkLiKK5/jYJlkwf38Xu90B2YEhUEtysttEPEOPEAJ5VCV8m8gxw0QuEbBIiGwGMm/hhtIUv4B/L0Ff2/A39tVXEYfXuElgMvJKm7c7dmWTmAqrEpCO66H4KogsVQtOmsXxkMp1nvvxKLHLR8mQlauZ5VrheLgr2LKhnOowlvtqvqo3p81D6RZhTFV8hN4BHLNO6aaT6N/XaJYqv6+ZFyV9MRaCGx7AX///jxk1Pax9Phd8LC78xDuLWmgB0QZdtf7vw/XlpMtAy3B+mA29y/ulUDtSQuaFb1vbhVDDnX6f6CYtmZWTtvHWjgEvEAL/rjlbMtr9a9BwfVdcbVo6W7pTj5ybl0IitO25s7WEEF/w0pfZ2tna9sXIXohofZDaF/W/gL+9vk2quj0y8bqkBhiV2OH9Y9Qz1Bb8/mIkzRiJVGjPhE8b6ZZ3z05Vq19zqNQZs0hyowdemRycyi5mTe1dWkSoS3QNtRxsq25rautt42cCLad7WwLwctvqf3QgLaJr++oAl0voe2u7ITQcwaDDebbA+iPLdRhDUD2B3AWDMnXWmYYDL07FuEPb+40YYjYk5xqMKg7QF1MgEc5mftjU0rwZAo8WyR7dvvsbPFIMn5ZMEBsCJ0rxeVhpAGhqtqF2TtMvLltdvatoSrZkl21CB6nVoldWXzG7g+66I39AIoU0gY/t4YoJUiczvRsmQ5glquSfm4Yv4iVtS6W8WWYn3CxnnEmzVg8M4VPJA/S3EnlcCGd1h4ce83IMeDiyY4pHfAMaZ88gC7YNzd2pA5BgPJqp7V7FOFxnRB9v9/3ZEfqaST8lS4vj3RJri4ZtBEXKk2oDSTFgjsrI/h12oXn0UsuIpX0+F0wA3a5V95MZAs9nrjTFamqrbZRvt1ta47pS75mfhKb279yuuybObJ037DqVxni/lxi98hfgVJoLMoPiNGuLeM8Xpt+SvDpTdS64kpxUQBPCuYne8jcnWzVfIy5DUqIWWikyiUOKCyh0YgBMS+9cSeOP4Wr7suu+Dcnjr8659tOHE8hz102fOJ45+X/9sTxFHri+BvvGC504viuy//dieMpXgcJXxY7cfzAHgRInw5kwVrXm74WeJFInfQpCc6G6kS54Q8Y47W4SfFdFD98ypGDTJzqtXik+RhHrhgRYfVOLF8byj92EPNVrE9jsGQ3icEs8bCldiDn97Mc2z7zRtcCxYHfoYnP4WDEKlvYkb5nxE+nBT9NkC2JeDKvzdnAWyBLkzQXkl9bO5D5BCR+ex0q+aRsCgjVRTbUHngr+YXZaIAugbKI8nxUt4DBxRVtn7N30yW1URuUvWUi6uTBAasYdKwkxztUtXaFHT1bgqIjNmR5zrGHESPp1ePFgMNNnu3Apby9tpjR4948uxjIcrMkwyloy53BTdMW0QIza9fb0RVtbhAaSjO6ux0YVhliaevi0pbYMMuB9OpxWhpaycXnknsdGwgumn/+CYLT1LzAayQJHQyPzu+ThC4n7RzOj9u3aCf4LXsLMvnVuCaw7xGF4uewFcJSf9FZMeLYMtZfBDUztWtGJL/UU6nz9npIL/2GRp9ly96+QrvI290egp9RKyqKlMdw8dCt3OZdQE5sRIunVNrplv8BpXoFNW3Sk7I2MCsnGiaMgwLIgv+GLmMjZfJeZVKMEPnKki7cixYU6+ygk4+v/SHtAGmdRVpnk6ZJ6yaLNznUeOMhuZEc+hgBS8qWaJsaPyDKPCQ/CUEGGGHup+nx2VGjkNRXg/vbjEKKGDUJk/sKlxv58V4TsSXhiQtyhKg2avbbiFLjFN5D/QICFSjJzOCFrRo85CYbrt+HR7X4ybTgJwkVDcvzLAb8JlJG/rI3Sg+CZF/imXXVe9CdoW6quouDUWESeQCIxCwDWbcXJRxiH2gRgpX0tW+1Oekx2psmklKNbEGMjAzNUFXlmByCKvgXshfrFKuEnMi9AtUQu4x8Qyl53KZjLYl9EGrk7aXkn1F6EG23wpFP/hwruKQ7xl+7BsKs6UYGV9pKyee2EfyVi2B48VP32PiJ6n02sua5qFpbZe8fRAPoCikB1vawmo9bZSP8kUHu/3PsW9OiGbi1G4vBnLg6/P6/p5DzfYpXE58iNmVJRfZwK+WIEW6fQ/MlIclDnnsZ32OrDEUkqPdlQvEeMiMF+4r8ELepHbFD0Ti8ZXryj8rVoQFSX5H9IWGlhwwma6Miz0O+ZPdRPhuGy4fwALz0aMwkx+BZ7JpWEexKMCdWrFOsBzJ/O8tRX2jJfmjhQ0IiCpQsg6F2eybKUSEDm2Hj057DxSweCJuJ/lnlNHWFhXvJuFRKU9LpMeNdDhAOSUV2scqCPb02BgNMllc5kE/eaLnk6pFWdTt7YXisfpH1e+GL8cOj2mowlOa3O09tsznpgeKbppG5QCFlkotihKR9OtseuwK3EuBILYPhoQ+VRBgn9TfmWfBw6XRy+gWa+P0X9MTKhtoz6P9vywpY3Tvf5eoSIJO+oInznbXgtxA7P79+eV62KdAS2emKgiZa7LVU8BOKhTT5cH/LHnirxA+j0ip0DClV9ioPsFBhAqlnJd37QmwgzINqKlfJh4+CioAC1Sy5HIjG3H8HPZYVkvvahalk8QsxA5ciemvTmPEj3Kto9BqYIcAUUHxlTlqeloM+SG9Jmy1z5rf7llqK5RD/QP311pqBZH4T/SB5l1riqKmOGnamyBwsoxtdp1FDbFieZk3m3TJXf2PaDCR2UeIlO20yV8hSIKmJkc5IFmZQ0plIOpGSpuukQGZmZDOTvQZYtK/Eo2rlRHVegppRyLODVreaqfGGr5nbeTciuyWwsLwdwxKNJaf9yxMsfYYarg5Nt6BkE1eXbsIdTHxyjTNZsNbYLIq5JmtQrgT167Q5JFU6QAdztnLiUXqYsqPeuHAiV/dnPOk9lbfvNC9bCjymJ78DfbGzaXOmf6mxZkEyyMOgCaIazMmKAPxX7lZdDqgztTDxu9SRtdZFIdwBdwhwB0VLgqWYT6+pVpP5gw3mVDmxvkTdeWOCVZnhrOwVEmjEU9BPqlfFfhL2UY2IBluAfhlUqMDl4B5CayglQ05kbS/ERpoUa70RKi+Hcl292AHQSM6HqCdyEDGP79Wn1DVvTVhGba/yA4XcS80KJ0YsO8ZB4ZvSvse9lFJYcxC1EgNP6sdxL73OvSLho69ZSCUf/Uk3YVEeWAr6nMXcqhTKXN/yudCkGct23jLXCmrdtqT6cTK385a0GctQv9OfZi7LbVXG9rfu8hpvpgdF7P4bbRlIz9zK3qMEd/OXqkKv17AhfBZWGRmFFDs6Dcybx9joJjv/hDNFSQ8oHr3oHTLRTVL+CEGyqwekE+eTjbTDwiK7yhflNztD3ONBcwAykm4cn6c0wJhIqRK/fVBQDxnA4/02cQCGRRs91SaVH1MlpYghkxgwQc+H99GRc1oMRp3BzVP9xaYqsSBZSMVtxDAkkin8hoMIpyjR5TBpo8SEKNGFRslqOkpW6aMkp0qsjiTzf/GmlqP1P4yUCI4UvBmAmxlyYsPyhJnJymU4chIZsY8OnSgy+Jq/Ugaz8CSWCdRfH0ATcQBNgHeaT7P0JeAASjMpSVWygZFBp4BIC/8cpzlaP691rbNBuIh07olJzo/hVsoLe+mppXdzvlvx5o4eQ3hNFOe3dQhOo+UwzubfdMTN5s/vYeL6sT3x4vql0bO5TyPzDhd5+dTvMpsfQJnsdDkmBQphNl2sZTN9jy5Mlf2l5BnDqPleQxZLyc+Zvzac9y8iXzwbK7vvWZrPeef/jtj8b4jN/we6J0KqhY9F1fgzf+1U7QIt1TfvY9y1toD+5sFvQbWDIs4vJqA1uDCN+KBAaQG589nYJHDFFDZXyQnaXCVHS/2TGR/MbLlQf+OCbFNzy4D0RDbkudO/BH5rBkw8iHSjMAuEXf9RnMymkFmsOcQ+nH3LZFA2pkDefcsXWLJ4zmvy0h2DX+6lQ8lDnvyLtmFnFzrQMvctT7SA2H0EHsjMS3Hv/F35zQXF6X5fFpTK/TLols3qvET5KzXjODWQdga5uvVA7fyKty+gVePq3CZ83VvxyPUnKEto4vyA5JuNTIGx+vB0K+6VL/wYD9vGRHUBzoeul+pT5H3ZlBjmFe6XkGQyPMkJ5kZx6wIDn1Hvnrdz1emdJd+I6xfgUd6u027le9wrQTd5C3qlgp5h4Mcyc98wlzjoEdbcw89QO3a/b/nHdKPcTUGqK1EF6ecwhy5TaUWUSV5jKSNyk9w4Gpxn8Yux1+ovOb0SpgU/0qxEX25w1VIzaJyZuS/Cidngp611e7COsg8bJRuAdUCozYDJdJMeJpb9OFrMQcmHY6dgHybkHumj+1ex/Xh6giEuT5yahjNtcJ1OHZHx/9CESGnkHtlLN+5h/irNPYyOjRYaectCk3Axtz8/v1mMAqeDKAhpZUzSPmyf5MeSNcKbVRpGnv2GukOhTOJ812M5NFOTVk/+UpBKbonGkwdGEE+m9VhA64G1AXlcQMvjHhrALVk2nPvT6scxmp23cPPkNGk5tyD8pQnNbnBoLsCh+bSJ7kbD0iQ/y3oPPRwSe70AtIiHz+JIfiO/L5cOBL+vGH5Bvdg8s34cqAFPYKfVnIGZn9WjwZBaWLTTUVhUG1XHGQyb/in3siS5vcjvHNaHNOT83biMHk6HdEZadWcD94iTeqPLpQLBibIZsc/wjFjVQZ18a2Sli9Hl/zPID6g7qzkOWSx2LVZ+Gbd/nPmE+W1WfxHqP9G4D+vvTV1dJWXKNNjcYNyHWbDfKslhbqg9hLdRbNmB/23LNhrPbdn3jaNahqvk8PcoJXvXZ+tNEqhfAnzUGhbXrAGtWU75cTrY94810lFvfhublsYadcHm7AGBtimQ3+fxbFiViqey9CrwQvr9mG1ucFfu4aMwJQfdHk3xoG9mq/MEV/dr7S2ibYdmNLj9dfMx8fkYwNvN+5DQeWLHG4pd2/VBRzOErJFpQ3O1Ri/Q2ZGCk/ASqAumRL1X3YcU6rwFsWwzGE/FZ5bTQUzTjsxfpHOIQbhLPERp+DkwVxfQVxDWLHOejk1g85/G+VpZor2eBU+jJf1cvS0ozAt5jnVMzYKJ1MIwm3z+FKafTPdQPMUmQFir22VakVz6UqzWd8B98hB+yYMpvxinfNM/46b8gywtefKp+Cn/l6On/J9rZFtiZMQ5/rst4I9HoheY0H8UiZvQpwznPOOpC07o8nF9Qp88EEPQRnyELkWfTbBaLizjfFfRs1ya8GzBv+PqF9fNl3vIfgzAdfMlHvLfcB+/bN4Nz8PLZsUkh+oLs7N3LDSx7cYe8gBLTDP6UVxGPxiV0c0XyMjI1f2eZjQ3LqMZcRlNGJVR0jkZ9RVaavhK/CDrOu21uv2uXtDBP9at5BLpDkulMh8Ul97tebCC3zpWBvVj0WlY2aVpq/k06KFFpz1ucmU53b8J1Wi6zlndu60F91ooWWKRJbo1VU7DjReSUUwwKanoiAsSfP0lYsWxkyHkGjq07Bs24NB69lgUJn3oAJhAHw/gJkHiejKmxiSlqyqr3BWSYPeQs59pqp4H9eK5FL9DzzDDxjTJ9ERO6PdfQMYhGDRkoRLT4yrDPrSRoJA39rqN9jrtaM63iXb9WwPDPA4ODPN438BIHj8zcC6Ps3fwNyHzkmNMS/SQns8Z/CIk04aEcas6EO102UbSHdHo+NadriRkKcWKsIKc71+0+6+Mq9rMuKpNHFW15IHzdT9Xh6vgfPW6c2p4g1YyV4f+9na6hriXAm4i7GR61bxz6CfqLRrHveIagg7+
*/