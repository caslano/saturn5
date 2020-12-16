/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_POP_FRONT_10022005_1800)
#define FUSION_POP_FRONT_10022005_1800

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/pop_front.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct pop_front_impl;

    template <>
    struct pop_front_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply
        {
            typedef typename
                fusion::result_of::pop_front<Sequence>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* pop_front.hpp
B7Eu/a/cuJrQVpOQ0fBRS6JtN2/xX/lTjo+2PRfm+9o6h5jfw4K8uLZyzOv9MVw+V2OOB9vqXj49f2Mh1p/3Vr+7Jx9OYcz4HNKODWqsecQ964bTXk9zJj4PTmRYIxnB6aU5SIbthYmfJpxBe2WDVnfnYkMR8jKetouQRvNn4ATtnvzPgRu7J/8LYCG75xzGLeYpuwe+ROAY7tk/oTCkzXfQfV7gGz1YvPJO/N6ab9N4uGxgf2tH/h4fiahOL5YWG+RhIp8OUaYwbu4iH/f0VRFrtF8mv5M3gOeqEsoGnITrt0/kxD1t212fPw/TA/jRT2ssIN0UxpHjmiuGxgb6heHoYRFnjXcuSbz69GKjUjZ7Od4rMdyjW4M+fkTi8e131AM4zvTRGPfJnsH8iN9j2/wsRRwG8Rp9DWl/THFWuyej++bWYUtqnEOMlAbqQHKiJMjB1D/n4w5iz4niIaloGyrk+bjidDf6K221n0jhLnpMrpm1Hp99UbivKipz+q61nuLhvgX42CY/4fGUf3/ryeL3OPRHN5i13UOqy3iv7H2e45sSfQppDtLtsYx14ifBCbZH/lPA0+2xjLlNcg6G89n5tOJwPljrSlzng7r+HDj7tvse82y7Y7wBJ9juvS8AV+2ONaDC0Z4cV/mix7n7dG8MPwmwtL4k7x5Nod6udw3HLZVmpGMPdU/GFfD4/VNQcg0+93l1z8EMBV9s7gb4Xjr3evj2Y/jWvNfX42+7mXn/I/keTrn1yybtFH/vdvgNsD6/YfIbXHHoI7mbAyM3nIhl4nfpfuMy7ALHO2FriOM+yGPxe61D+MMfzL97SdZQJoHFkjC2+xDGktzQTx/qsfj9V6z5cw/j35NSI71HMebz4hjRoxnjknO5Jx/DeFqW7R97jN6blbJs/YR/N7Iw5svNWOFnwEy5txKM3q+VefV+zr+n88r9jrF0uXt7jIXKvS1xLwv0/dR5Dpsru3t2+qsn4uuyxH179wcen7B287XA80++hMbdwUqBj+k8nsT9gb0evx3D6Q/jO5qnUa4BMO/kd5lz2k2fN3CXuZTtVVfVuM8cbTtzTYcv0J0my6srjaLbzYW2KCnskMOwfj6ssJVV2hvk/esNjAV3VRx3LVq77zmwQSuKsyF9Yj2NnVV7xhcT7OihIu4/51h5YUnh/p7Pc40NkkKeL5u4p+GBhvlQc/zWf77nZ+J+Clf75yarwLytF/ki5tW+lDTnEHPgh6l5TuK7XXf3F56cj61+Ls+o4Xn+oEZsEnZcofvwYbcyOI1D87JuJu/uecr3edJx5qHb9084rsroYeyWvpup98YDDr/nfAlv2ZyA3r9eYq5OGdtW31GNEgabkjG3YnaXGVPIuHS4tMBybb7FcNzph8OwYbYNvrHajdYW85h3mIN7rPD9W4G52gnKsKM5Robm2wwOGWADch2pvUb5t+P3OCYMu8/9vlipN2ZL4uL6kxgvDO6+ZrzwLNeeFH8vTk8vLRSnj8VhI+CbBk/t3TzvWhqPXbKdlX53IM/+1TJ4q6sdxesFebQm7q63BsRDXRu5qFzyTgiTziAoV/P8hheUa/IChqfkQr7v83K5YTtREe9/kOf4e6/wPLx2ORws40VMMb+Dh5crV+SdhzuvDOIDeTdo4dWG4wblAcbE1wg83m22Qj6I5ZVznEbzdSmOz2YKfdvgq113BsVtJHV2sdtd1hmqOs29QX+TXLVJQ090nybGL8OjscmF9DskIf2H30XSPIxhCBHxWJd7s+Ji99sA+1hdgmlOezDAlfR0+WhH+PANt9tvtZ0dz3nupDlxGTrtAXM235bmYAsk6+LbFQc7G/15xlPw6bwjzPNF5T057ww=
*/