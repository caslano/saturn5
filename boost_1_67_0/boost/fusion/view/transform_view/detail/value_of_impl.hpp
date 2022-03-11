/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_IMPL_07162005_1030)
#define FUSION_VALUE_OF_IMPL_07162005_1030

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/utility/result_of.hpp>

namespace boost { namespace fusion
{
    struct transform_view_iterator_tag;
    struct transform_view_iterator2_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        // Unary Version
        template <>
        struct value_of_impl<transform_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::value_of<typename Iterator::first_type>::type
                value_type;

                typedef typename Iterator::transform_type F;
                typedef typename boost::result_of<F(value_type)>::type type;
            };
        };

        // Binary Version
        template <>
        struct value_of_impl<transform_view_iterator2_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::value_of<typename Iterator::first1_type>::type
                value1_type;
                typedef typename
                    result_of::value_of<typename Iterator::first2_type>::type
                value2_type;

                typedef typename Iterator::transform_type F;
                typedef typename boost::result_of<F(value1_type, value2_type)>::type type;
            };
        };
    }
}}

#endif



/* value_of_impl.hpp
TZ/NMQOMDI2CzGyOyGyMu+G4Z4LA9iGUAVEjKRwmgu/+RT3MZdFdCU9HDfebVK65vbpKFo8Z8HqOiB6smmeiQVIzMjPzIS49HZmfw+v/zRuJZ+pE6XzR27OFLxgJf+zCCStLm2EYRUht3Nib02UtJ/oTmUY7WcfKVS4zeccZycg780KyCZY7QD/uJ9YzkFPDNma9iJ6U+3wwvLzVTziaslhRbI7eQHVc5ZZK2mKvSmREGoeGjs+zkk/DEIcV0Wulq0uNeNVq2vO2KtCrkhohyv8j7/XA/9QT/F3BnlDLhvvT8r4j/zOXYca9hZWeVGhkscM7PrGBr3kgBtcj1s8MJig4gPizWwCX8PJxfsQzvlkv+IwTLggWsK2M+5xxjEXAdH4UMDAE4SbKHEcSdZA6Xe3urtU5pu6msu4nIzlYy2Tv3n156uWuTeNOgwzYvKkvQ1zowc9rz5fk5Kslls/6tp564uV/rWb/5P4iXm4v8OwJyOhE2Qbv34yEm9QLszz6OCnwsw6QwPsaKQRgCSwUptOqZ+tFiBDoUepb+d5YCwD/felqUPqW8VW9FHVbxyBhKAC86+jvHto1F2z6pWf0os/XPgDLBajZQwZvuaasC0l8XP0M5gkY+8mSWgwz6rcaR1Qh1snx3gGcx0rg7/1ooaBkw1cgNJbqiJlh92D4qfPaxgyI4cfiN41KM+Qo44bwGjTpn176YbO7R+o3f6EKMDsn0ZlvQFf9DdEB4zfrh3B/se1gimDW4A1wYojE2eHzncCLps9r2mvm9WNp4p/iT6XKRVzOo/FG77ZLdV8qE8xRy4tbwfIzWrwhIJnAO2237TwLCL9aSbzmwi+tP73l5+Sa2xpn7xny11J18cOGgPMRQtFN3cEHsPaw9bTm0wUhFJI9Tif5FlC1M5NkFNCfMZWijN92b9bF2BKpbavJW2ADED8phriPypdAzsAznbZHy6QrEZyaXOzjNACNETq60UQpc5gxOLQuDVx9rjN/0+7lzQOdTstbD4ZpuLh4UcmgN8GTiViqESKu+oZrasWlh1/clhgTiaf+gO8y30QSQCoz99BQZDSyuX8gBFJKAhWVsbZvVNrTP/C5XtfXr/rbbd46FAJ37I3Hyhs/A3Te+imImPjdY/KPGXzAY9t5q3A0FEIQ3Nc+yQi0cKAFa0Rc3u2XHyXIk5dEKPcKHBI4XZ0yMGAY/w0ulQFTgH9OZhnwh0zrsCUzeQaS5EeeGxrAqZ9u5RRJeggUUMdiZOUfvnhsqYxpmEPj3iIsg9H9EED9J4knwymC6fz896OQuTLqU+5cLRSJyxBRoDFhV8IoA7sfrFRBdbO/q+BOyW4LCsht/6Bh8so73nw/YLXhyToDHKXbWIqJ6Zy1LMzDTIOTFz2potur4LqiB+QjLLtoqCQ6w3wpYjdH7c3qVhRHOPLxucC7QECoepU02FjPIguCgfFDVnnwjsb9g3D+QsDe6Bf2eGCM+62rMevWMiJCyBFAfp5E6DC9YSSBaXmOr83nzHXae6+Qu2ivEEV1EpnQHaTiKoEuWvct61lI5+2FDR5eW6H+ycMexL68VpoO5q8IYzmhQjFw92RJwlk2JthaMcBn3zOHNIGstEGgG8vZSMHLsoCQyTiP2BGz3IMfBNvUlsNAbiE02KtJBPj2Pox6M+6hnbmvjFM+FPA65JqkUwZbFYP2kErHkgBZ54Pc6pwGL6zYpdtDb1oh8lfbYdL1dQ1Gv6Yco2cigALmR/kYiUJqqLa6Vt1rtmQiIH0V33WiDXZGkf3zBwbmMV6ETNwSKjLja3smZFaW/BnPHMRbvbWDW/m7g8OCaUn/Uwl8E3OTEbgKWUmDRdf8X09XM2VM76cLf46QcgMpuHcPOxVvzLj8JV6QcoJEcXgnFRwQr/2ouMsOm1YWHBabHHQy9/AkVw1Brh6twnHSbJAMmHLrzedQKgYmmsDrnNYkU+lIydkV98tfmsliwgxpYrZYibBZaAhXgy4v94UH2zvA9T8mcQbgwAxPr37VRb472J9TEE+312KsuKRsXQ2Kr0HB1HA2ICpTCLQ2joUUV6aZiKwZkdr8gyCyfog473HxxlxCoBuGYLH+WYuUf3aXUj1rvlC/TkeVSFT+TrK+iwzWJrcRThwzpPVtcqKlqqAEzVsGaMLgOJUw72mDmNeA+mW6vjg+izw7vjhQQF36SaNH1TFns9SSGsMN+NEmG38PrXWU9xPmPrAnY94Y73MiimftpfVxD4YUySKfJnfAsJn31l+2XCw5qKo4VfN8F/PpwPqOeXNuKKZAAnw/DYsSyx4xljZnCoFKfoKjV+0u3+zZcDKW4zoWJIMpmmiPhbTDhbgmd9pRHFVQZLJgAluIy/pdovbEoKeeGYyb+rCm3TERnRNxtfpJVt54VJXNnI6fpzHZYUghewz9xLS7lfHvrF3VnTwvfrl4ohWaCf0QQLiz8pIOmteFBX094GjPu3StQNVCtepVKOqebtOWmzwfANGBUUFh/EXyoheCYl7b9uzCwreomKabKpJ8erNSEwW+rXYKRcxLZsGlx6P1iS2SX3kmgONqmSCCJEqayaMTpHLkmSnAH5aqd+iOdP8ajDSpP3KKXrUv71OXN7EdSJ6eVZBYu7/X0+74u0NZbtR0VSVcWQouTsWxq6p4ukovPu0YqqoEHkkFFaeHyh1dlAQqmtvM3b9ghKMuzyfoHsLgZCzaqcmTsChWzw+9YKJczJXZp3dfGxBUqqBf/iXrfBjJQgc92INz3SLu3MsOsLOHLtV1QiCZXJJUuGwQyr8/rZv2D0H2aaeEqHUyR1xsqSUrIXQZJJ1sWFGbzOdbF/kvRr+81L9GfHTRIXq/H+MZ5AmoYQYiiqMyiJ6tsfgrMuAT2p2wGGTZwzkVqLf7ghI+cnllkh/GWHsNYI4rKyl0SbU8zMppqnbNR4ElGV6suxG92YhdAckeIZlQ5JQBRC+y2ceGXMJ8jki4aLAlug5+e2IJg0AkPi/9VDF5KWyFjwV1PEDH8SizRFyCCSAXQvwk3SFYHMA2o1wZZ1rwEEZYSqEtMVetXftZNEE37ctYvS/mvLKjnygXqtQ+nOw4MTZxoChqbvh04Q5iX5TmuYizE92UPYhzWK244Zs/MP2Du5NbOX+S11SukfRuRCquJzWqiapLYLgyzdLjBYqpiI7tm/PAVGIv1RifqNxZ397Vh/1w5pH3p+3PJsvSjNcvzi5TXIs9JBoZCs7EkPuNDpdfXMysathpdr+dmFjVrVpGtB/yjU18fDpX/Uu2EIPcSWgYEYvGtJwt+KwtPOOX9sZxkSTEOXuIou7S7MGwL2mbhfHi+lOiSwrIEAJrR8uQco0ZUDoZOxhvKqNxdARRVMDHNrOE4aoqbff/uKfvREAmYqFGYLukcEPnh1PFLzwHhP/j0cs1YslvHfF1PPQRtQ7qGpBgy9fgHcZfDzWgC5pt8jR9ceqKFk+QBolKnB5gX4zbeKIUWOC5KtE4UXjJFaLpe+TACetkF0doJyGG6WY3ffzGO1dvP4lJObJoFcfzTxjdZVroaRNSkkoY7/EqDRfNcuhgTsUAXVWi0uyUKJR8z7wXEZgdYLvkmumH4yeRMvkavz+JNFycm74kuvrYtKGrzHVSfq7eaPbECh8ulr9bUrg0bcsnqGna5qHZfmottUtCUL0uJvbK8w0hl2Qrd4YnpjwMJ0lbvK7LobLI+9Gq6Zzzu/H8HHtJ3JaJuQbw9IO8wXDVSCUFXyjiD7/CcV2Nzkq7LdhO2NilnBuJ5i7TZi1R1zyhXEs+XHgMB9G8ps8ZcothlbcmUQW9Ab/AEOVp9tpX3wJcb/DXDJYN3p36M+sU7mtEKbgg3QfKSnZzE2TaOqytQ0PQTDWTQjrwFORwdg7D6qcpvARs/BpXpS/ANnvW2jcBYpVySxMTtHrCw0ED17LDUylUB+u/QMAuVZoyXunubuS843er/TXkiuSo+3NiUCSpipg1qZW/2D5vEF4iQgU1MMp8LbcHynzMUZ5ls/C5kvI5oaVZsBCy8uEdnGTwgSUvlaI8tDfn/G8Ta+aBdOPfRfMefCqjSehz6P3D+Y8pL8Ix/urnSky3NF/Gl/6noUHWT8N3bOaw6sdMDNz10jJfHf7QbEoQPiUWNLg0B9M94GGCVOR7IIC0b37APWDu4Cy40etS2KdAYHBQGP+Q5bM4I+3ZYqrBll2Gfbs0N+0ZMNW0tYd8cXHMYIV1tWs6bTKsPVUmPbi265yavicfmFFJxPPFC4+vb4O5f+YAZcvZC8sgXgSunVNMjxd/Q79QyLEAPqoOGkbsTTfiEgCFbQzxO4i/aoGgu6BSodn8vPWe5vdz2VvTzgwhBD0OZBkl3HEYNCKpAqeWA1nJ5zNRGJnYeVO/y7X0RTSdkUj8a/4cON25mHjxYdjNJWh/MhTqVHAvHvcud/MUTzjyNTDD74Izkekwi5cGDeHERy0WCuYOh0B67Ra4kFHXZVUEp/nAaR5eUbSafWaSY1blqH27S1CRZI0AEUlVwZG+OQpvCcrz1A7+Elo7LXAEjpgyvlWVSqb/C1xIZPsO+pOfdklBJ7hLtBdx5Pfq/VKYhLnyzNzNDZzudWL14WkPqzD19z7HgesR4GdD88Pz9fjZkaCkI6Xv5I1h/MT0EAX6x5nsuM+xpW3jCE8tGTZ/l6GgVR3XO9piYiP7GzF2D3hIcJ8qI5Pq0LSXaKs0L339CDyUJtLRHuFN6yFSCewPRD8rfiIDRDu5sSpYjfs5078QzFb8dN2MNUZ9k4hxfrXa7X+i4C2F0SHc3c//1kMS/cY/Cc0cVxTqSUDT8KHiPC9S4SZKWdItcBePAOGornTMJu8w5nxpdiYbT6S4PHg4ikfKqI3oLrZDa6FcUWn+hsAwJxb4EfZFhLQ3Hdr/caD3Lx3nRaJGwWgZPguwI3Xs+vYCOkt1S0RjqJBFKepOzA3hiqA0YXKK8LyA1sDGJlYUY6OD9+VUmAP8V8+bqI3DKLmLXuVDOTvGm2F23lVyRwVnUZYKMnopxEVS0Rlpf/U9RUkFaMJUGBIshCK3IHuD8LQWqknf07AcOTfRDrgZg83hojuTYjQRd7LennKzAcd32gPo1JmTxGPbTbi989Vm4jp2VVkrE8zilUqe1drFL9/AwqkKtbuwZ7uZzuzUYxvkx23Y04BVjEVNuz44eOa8wtTeJH0zV2z5tLIruBzdxpiNQSxUkMaqbgsu51HHIoaBv1Cy7WPNF4WSMTqzENBoRrpL8R0WQCiTkrKcRtTeRHyav2XW4Prvx6hJj9VE4hTcZ21sa3+QvqPRGZQ0Vl2zCuJ5Q0Z13cbkYPIi4TElLbi3y5zkw3amkl7OrTc4rSuN0JVDXu3P7aKW099rxGhIo9eVmYHrvgVCzMD4CyFWIdckbzhZXTAcsAeFfq8SUqmByVxI8smE7H0dHQgrlRwUKLnrxsgNjqHOsuc8iB/flQNpfxJ4+XQvnn7vpRX/dFdUpqvtb5y01O83llVJjmU6XH73EbHMB7686M49b61GFF/Lqou2vpfPAAAs/9No/P2eNatIJi374Pq6NWen+0NEWaXZcHi3tPYr2CbguaBiAkoawmfqZ3dLpcmbDBGsAuniZN7oTBYfhtCUR3aZjk3egJTGKrOoi6kYtgbrpJTQ0L+XjEArBlx26DChb5dWvC5AwAmAhd2i0HrLf9tZE/sOz1hBqpBqsyF5CKP1nZkr0vqOiYmPkLNzOSbvvLtcxT8nGE5j6BpcGRzg/2Zm4vA1s4OBDYePNXCxo6ecAJ50jwxJuZ4H7uuydaMpp9Bd3O9z1r1A+w5OMbPSoVNPgXgdRsutAzvmBJ/K/Dte81tcaN/dciMqq+tWhNIa2Zk+jDpgLZY+w13+Zw05B52LXiFypIs3LPWVJTLcYp2EKLafvHH1b4cR5zKJF/9ErUE0m/sc3b9ZMCdnlKsyLoJc8RCeCzz6uFj2+ZupwPjq3qOhBAJPWPbZpZ4/I0eKGVUOAHPLnhyvC6WD4ogCz0VNWbyGNVGL5hHXLf7nPqTOEEWmM29gycT/6nvMvuD0bvOv+rcEattp59vn2dutaLQVFkp1b/Zrz5C4wk/ww08MuI657sPPRDtU8faPjYDWcnIZia7r8rfCut9ZmL4UxInTnvjfH1jQEFkQy0QCRjHHGfh7wZvDgZ0UYDrjaAkiEz+ID+5M8hgGGjmiialxBkg0VWNbCM9RsVHXeIUjI+9grts8z+bNu08D86fXqh+LovkFtzahjXn2FUWkWvSwHdoG142K8gXZ61tkK292Y68Gd1rVjork0N0HmJkPX5YIyr24llPoe3QAyN5Twg8y1ts8redPJl9N0wqv3Y8lJwenba7XLckdXOaI22j11sjDjFB1s+PqXQB95AgwZFMAYWXLrHp1v2WpTojAfngUEAgWKrlS5DgNd3OrmoVkpcjur0PSikglUo57dHQgJVgJs7565NKAigqmyAvvniBR8NoOaQqYTsu6yOAYt6X6C7kMvRtF+PXa9KNA5oVSz8UjRwSjluN9OJkQ5ow3amR8RS3vZVWc4F7a3rN8+HIpO6J/pCAXoEEH02PBFoGzQbOEVKLmgU+ozfL/Psk4EzZd6lPOYoXARynIXrRdQhArzQOCM0hDGAQTnJJeMLXvZ1JHnrI0lBm/Y3bjHTA/Ev3UAoMfNOaAC+5srkyX1CgBSjSTTWDD7K5o9/yZUp/iZ2VW36E3El2qlhj4iTvgiQdzJZRlIN2vEMbqwWUi/5hTnvN3F29PwqylY6fegC9YapoD512E0xhVSkVHy1YsAsQsJZRAFbKF6ZADMP0UscP9dW1v0plvq1IwNynF/ctAYiMATQunKNZQrOHacblrJFj2fG5eZ7qnlrlMf0ajuty8gns8PZ2tkQDfSVJ0b23x9x2gKWJIhpdDdKyVoaG9B9BCFrhQ7V+CrHbpYM7wjQSpfNUXdDUdh/JbL9mdDWAtUXaUnqrlQaSC6VCuFLSp5+wWCOe+SFrJaPb6pR7y0gpYTLcmX4oJqyQlj3GcbFooS/OwDtQeSAPYMgcOkkCEKlgoCNAIzLc2BQyZtd46K0luWqkWaS4MXVIkyrgLWOToY18vQqJ64TRVA1mYU0wvhhZqn/4leFsY84Drki1O+YSWiK5wftuJ5ePCgWey+ZVTcFj2p2Gos07JNNIaVxfQJ6u1dwhXmXz1erHrj9hB67V6ErR7OrdKUWOPs5Dk/bfVfUmhDR4/LzowQbx2Olq1lAPn1mC7QLCnfOxiiEYVjoXZ3NysS1awUtMN0rjBUceoUv4ERV3nPlDhmwixoXSJyjeUMOTVCvDMqx/knc3n36u3ysUIx8dZCWHJ5K0bV9fy8xxV13wzk3Dfs4vLj+mPnHfLamZK2IJeMuIfVTvAwfLvpASRtY3rkiTIbcm3ylUTvcp29B15vAB6mxx+IiIfxFE/vUUyJ+iypdPowUzORUmcx5s+SwnGR4Qb39oS+L0vnkF+w+2C3E08BF/vLz73hPaoKYAwRl5QmwW0sMGOqKJ5Rn46ZOmko8wyOfRQLalxVcbP7MjVGyvtmoq45cTsm7MMhhpom61g7B1fjMlMeRxNbB5HJTBbfI/uFmZOPA69HfLeJuFYYk0IFKw7KRBDp2GNkY9VcqMDMdl12EXhSJucBeQAepx3zwBKAwX/MN35IC55zxMcC3BnQyEkqXUb4IEfj8TV7TXOtvaeOtQRsQxc8UV8tjwsWSUi9za1hii1CC/cSvrOqmCKUN4mf3B6H2RgPGCjzjWKbsM837X793l0Vg+LM/bCHA1/pvzcPMqgyi8+ikFIdu6MKnKte+8mvlNvNsyLXDTSST4XfFKfbkDxUZwnuk4jrypClUEUhSqJ1CJW4iaYisLrxYsw5MQhzuRhZbOLmLF3rFiYe8UUh0KoLoYrLNIyx1fSOEYsFBh5csu6PzmI14s2IMyyjiSmBOk0C50Kr4SW2JxP61yte4IrDDe9afP5OTkk9jCsKSqFIFPSYLgVRcSnY7W0qWmcgO4CiCByZHRoD1FSlWpuVa4or+/WW7dGgSMI4W98SjmY3kVMdHV9hsm0DLoLVVb4uglTqqy8pMQIZu6oY1Ai/TW+oQbg67e2krlo0y2VLmCA1q3F/JhTWuKAfM9DX2abAhgaikOCx2ZgFiynkBNouk+7ZpcKrPffq3EyBg5WDjquG05/vJwPqk/j0kOGGYUd7qhF9itNif6IqUoy+qnkGi1e+J5PAEiaNCDmN1908hm0wvDKLraHJNOw4BS3w3Q7DnNxOKpNB8BV49Ir53mWvj76S5EwaUuy/2n05VzAg+ev1vI7Z5GDpanLtBrtzmjx+1xS9SArlFwAKf6BFy/CI66i2UYRjd9qsvEuAHPOR7vzHV46DCs/zH8gVSd4kCHFGrRVV+F7TbWwsUprw+N2o4eslsCxfQf0QIxOVHCAtRLRZIYuZEJ6z7AO92d+rO1wNO9z4qdeVtLyKvDBcglq8OqJfmzWllWGej0hPLA+HNFjhPC49pOcV3uXFiX5Sn23nbAkXZ/VUeI+Djn+TnmllLo9iclDkOALQo/q++vbihJZ3leN+fl02DnLYJzbEGrQOCxVN9JEtxwdHlvbXpjfYVCIyRs38VCLxv5XMRcRrJHsKivELZqL1LTr/uDtX2mjmV5/kQlGl4X3xF7xgIBG3MaWEHYgJThr61aJf4bJmoL6jRGR1THQ2XsECKtFl03r6aCUAQcFctldZZ6zopJye6xqUk2EhWMmppEa8baK74gLkGvouMCAUOUxJqzKo0GwCAaUVXOlJ1mW1fRmQdBJnAzvWY5rJ1Uvyd+nYtS5Rl8uxl3nuRftLnGEsLRC9bkoBTABMNlnPunheG6bnPRElJh2sHT9qHK6czenduz3FXYT/0PtDQPYCzYsh468D0mo2QGQIZi4fyIX1j2gaMNrwOgRftESZ5OYS8B9Ci5J0JuGZLD3grSwdXydUPKRY2VPX63XrK8+5hekeCbjvh1MBVd+2Htv2yMvUPo0IgYm7ry7KRWvW67SjQ/KH8ihILNnfkBvPvhqRwBZhAfh9i21Q/unZokRyFU5Yw5gRolrHVzBrSdLbVP33XI7Lh12O6JciJ0Kywpoh7tli8maejXF9MidVZsqNyUFDXPu3sexIJmYgUemUyul/NWnLhYoZ/h8eMUAxdWqUI+KJJk=
*/