///////////////////////////////////////////////////////////////////////////////
/// \file integral_c.hpp
/// Contains definition of the integral_c transform and friends.
//
//  Copyright 2011 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_TRANSFORM_INTEGRAL_C_HPP_EAN_04_28_2011
#define BOOST_PROTO_TRANSFORM_INTEGRAL_C_HPP_EAN_04_28_2011

#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/transform/impl.hpp>

namespace boost { namespace proto
{

    /// \brief A PrimitiveTransform that returns a specified
    /// integral constant
    ///
    template<typename T, T I>
    struct integral_c : transform<integral_c<T, I> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef T result_type;

            /// \return \c I
            /// \throw nothrow
            T operator()(
                typename impl::expr_param
              , typename impl::state_param
              , typename impl::data_param
            ) const
            {
                return I;
            }
        };
    };

    /// \brief A PrimitiveTransform that returns a specified
    /// char
    ///
    template<char I>
    struct char_
      : integral_c<char, I>
    {};

    /// \brief A PrimitiveTransform that returns a specified
    /// int
    ///
    template<int I>
    struct int_
      : integral_c<int, I>
    {};

    /// \brief A PrimitiveTransform that returns a specified
    /// long
    ///
    template<long I>
    struct long_
      : integral_c<long, I>
    {};

    /// \brief A PrimitiveTransform that returns a specified
    /// std::size_t
    ///
    template<std::size_t I>
    struct size_t
      : integral_c<std::size_t, I>
    {};

    /// INTERNAL ONLY
    ///
    template<typename T, T I>
    struct is_callable<integral_c<T, I> >
      : mpl::true_
    {};

    /// INTERNAL ONLY
    ///
    template<char I>
    struct is_callable<char_<I> >
      : mpl::true_
    {};

    /// INTERNAL ONLY
    ///
    template<int I>
    struct is_callable<int_<I> >
      : mpl::true_
    {};

    /// INTERNAL ONLY
    ///
    template<long I>
    struct is_callable<long_<I> >
      : mpl::true_
    {};

    /// INTERNAL ONLY
    ///
    template<std::size_t I>
    struct is_callable<size_t<I> >
      : mpl::true_
    {};

}}

#endif

/* integral_c.hpp
gtnTuxg8UyYcC8i4JzoWYlFIdwBF1z/lX6v1Xw38a5X+a+siKdNVn5EHVDN1bt4Jlmf55Pv/AU+p0qo7AIBDS5Q9e1yU1bbQjPip2EwdjnLMCjv8Uu/BsoCTBJWGAyghM6A8VB4qKOAj0UHMAC3InEZQq1+/bq9zup1zb50893Zv/Ypfdrv4SDLNV1YeQUObbI2MNpmixuh391p77+/7hsHH+WP4MfPttfbaa629Xnt/e1M+i1Fo+RWZjaIEMSaHSr8uwa8L+9GEeoOIPyjsTxMwqIZRBjzN/TbDGBpuO6M3m99vMwyX4dxpvdkj/VEVfl5vcEd/DfCyG9ngckE/Dcou6A06+2sw56LeYEtIA3RrWAYZjoF9uuJKU6QvqwprXe5lut+lmtAVxLc1XrJann0Gd9rGNr+4cZi1yg4pBXI/KG2832VpmocxwhuMO95Z7D/W5HcFhi2j4WLH/EPYaspPrFUi+68C7wAFf34/W+ujsOFvmGX0Rt4kN3e3GxuaRMNueoINvw+XDd/ID9m2bmnahk/cbCp5P8YTFqbDyvyQveKWJpxGsAuHgXlkBZ4PA9n5IXu2LU3L8clPiG5hOI13bH7IbmtLE14sAvcyc+e18Vam/JDNx5am0djqacR1J291NM/QapBohZV28DHF8l7Cfa4V8JGx1WDRqgOnsRsH8BXueMbaALTkhez2tTThfQ0QhaL4GzbE0jqU54Vs87U0YagPTdgQr9OtmgyPGFsN5ZuBF0AVo797LnscY3x8M3+cAY34OLVqPIQbH1v447EwvJs9jq2YTfufZxhaWHmLgYBHzOFOWYi5YsLawcahLcOs49knj31Ws8/b7HOAfS6wT8yGYdY09lnEPs+zTyv7HGefwUx9x7JPBvssQFXG9aHyHlofwguD4jvYPGcuKqnY7BzLQqSkYqVhOMUY0Wioftvk5S9ONYjYax6SWlI8a/s1lqpM62ipatw6uVR13rAIWHYseBEQLZ9ho6lpRj8TG/N42eDE9H4aLP5Vb7B1er9uGI3UcAOeV4zNtrZPNP8WHUOYD53ervaJCt/HG+nKiHZlRLkyrO0T8T1kiv/fRGPxfq9JOkqEQb5ixV2U7U2U0ink2F6gOiSF4nlsFiOGo4ihWsOQZh5GVdyJmLmNpPQmQHU2BcMgFtCmRbkaouGNHzHyT6FCD70DiWdGNNNhXZQKeAEznVZmPii1+/QTyms+p7876G8bJd+49kT7kT/dT7920t/D9PcQ/e3iKfh/9HJyU09h/edXbcABKuFhI6Y+3JQk73ZG0At9Vn5wkv6d6RR/c9WW3GtZ30EJEV8920cpNb3Bui9p5DrM0PmDD3mGnrw9KC+iJbUtiI5eYJ2E6OiKaiLa0ryG0O3X0A3nD+oXhqKiN1L/r7llj8zIlxxETrbKHGvkwSDG/qAxnp9Di0fqTBu5rigAk05qsl3F+LMdRq7E1DWsdSOybMMlEx6O1wi38LfVMvhxMBnO+gxnQYYzKcM5FMuNdUwtvXgnTgUu9MEBRz9WH+/Zgm1o9TH9qIqBd7EVvinh5q9/Tbgs7FUFVh9gvSPEGTnL4G3m87tLquJgsSP0PScbvMtsXvfECjz6ADIdIU7K+XvYxqxx9x3MqMU5gv0hs1d7fcJeLb1kErXOHcgF10WhOGxeRUSm3IV3dE1qjAlrLDWHNbYpU574BReiTgZESbEFe4Nyj6pWWQurYkow+jK7v21fe/EmHrO5pimY9jVYXVT9dbW8yAvOly7SVcwUmIWZRGCG/UH2aqwORBV7x1/Wwyk410VvYeHBOywri4Ckv7OgzIazzm2LYhOvuEi/9PhnMAd021Fs78cGHTI0eKi/BnMMZm6k/WrhyfubvbiHJSTVls9f0J73CWIiW39Cbt92wYSHrCRurB5txaNTRi3Cc3oUfoRQPvuF7tiy4oEdLNhu3Op32QDuaSCkauKLBKW4bD6AhafEmR3sh/gORyq/+Ncey8/vcfvhYr1XfabHydJHcNt8rnSWtwEsv8CFr7Te1c3IWd9jJMcHzy/kh8rCL9nibJdtLEUgApG2fOyPjtoIp5eE8VQR92FoqffSYSCcYljNvmq0wiNEaFWYWmvGm07de4XCqvaJGqlZgtT4jlT3dtjXI2nMQhrhvCksvgfmSIrGuxD9ymWjraNqAkj00SrWAxZFkESicB+n0KodBRMGp+pQffy48nw7Hf03/zgeBenH2jXe6auIA0vlWTAf19FZKamClsjWNUjLbEaLWm2Gz/bgtdjORYwggCLWPyeInwPlg0z2C9mizdME0U9iSpGluMObZ/hzmmdADt7eSUfFaXz0Q1qdVxyqAsl12lE044kSutkQPjgv5+5bSM6X53DuqokTlnFt+gorANgLrd3sjMvD3vCdfXH+y5N0rCUsEVjCWncilmcRyyW63SxKpXGNlygVWIMoSTtRhHFchKo9QRwT9YJAeZtG2M+IMuFcsJo/WHkdNYepT6JU14teB/Ne2835ms6Ek87EiH5vE/2+dU7qSqyP9fvJL8H6vK1C6PPvs4Qgzq69jj5D26ogbf7vVUbCqiuups0pgrKnVnHKBgnKolprkbK7BGVrSE18Yag4sRUGrvCpDMQYBUW/m6Y/82L3rvLSlRSWplexp8Q6QqGE0ZnKC1DiPtQrhemUJ0fjVKQ7yyMQnHmClI+5ATuqhp89xS2Mf6TrT/14Qgy++jzcDq4AiX9oc/ZIt0Ox58CQL1WuUKrNz4CSbP5lX3BMMpygi9rFFzUxQyji1AVknbKjHFzWGpeEKiJVBU8gYx8TjI0WENEOja8mCaEIiLsJoo1k64GT8zmE1YG3fxCEWeqIHPm5lQixUZiiDwSEovcxgCCseh/bCOIvBNEFT8/nehjJNKWLQ0RIiC7S/5VC/89yaUe3HkFpJ/ysTamtvchTS9PdmLAKUgDGzheK+dxUcQhTYZM8hIkTCEbFJJsweiW3CZpiDAui9ZvyU7IcBAkcqwdMAquHYY108EHw053iOJfgQC1i7RIot9fqLAZoLMfh56q1Vk6PxuIUbpsQYhNBcMF3gaNczo8o9lUwWFoM2UlxrS55D9yhgURrguRMTtAF+Yda5HNSeqyl5QhNgjW8Q36xHBwp497Q79DkNJBQmPVeYQVD0ZNU47c0NWMyYfPRFona2AancU51QjMiy/LLOdWZI1JjwtYpsL2yAielEuYc90zPSltybWz9RHd6jDvyPdyXwGdUjWkUbbDCM375BOk249RPY63r1rMeDNPI5utWoGHxKVKmvT9J+3wZlenHM0KZKJbDnbUzFvOdtUP5zlr3PriPJRcLeyJNzCzZIjGpG/wXES6ZKVxSxGlg39d4VViC+OUFwNxZME8RyGGkx/ekMdrxVl7nCLUmwKBgEu49zQq4jeTulNe1Oph6MK+Nb/XXRDQ2mMOc93KEAh8eT4zIfofI9kKTwHXYgGv7rF2YxYw5zYYaOM0d2mbhN26aR66dENr8efTSPnNRhe7DhYx/FzpGdEgzPZgN7AqeFj0wj46q6L5fTXxPzPtP5rLJtpNFSc02JS+VIUEBXmF5X2GhMNp7nF682GzGGelNcpGaJX2occ4l9yqoscOvYnmgUHiOtU7U6/eE70njrZttPta3XaaeO7FbMaHznNx4HDstu/1P7PaCj7sK2e3lOeQmqNt0xS6Og35Y0O/X7UEE9f+yGPXOObp9DPKhBmt3aDlCvCY6enHOVay2Vbfa/0YQfxZ9zJ1zFatt6GPpct1KsWhGQIzU+zBrfbDmyJeHCeJt0ceVUg4Rcw2rHUkQH4g+9giIWL2PiL7e58gyhGgVsnqllNv5MSIi0OxHtBDVu8u4qOJ9XFTW1vvOMFE91m3Cfa4s9od/nOd2/gGy85sF8ZNKuZ1nmte8XEH9/SxACqA07iWx1QQge5kuNh9YSk/J7VuweLKIWlIwA+DxbaZVj3H16BEGL5OxI6IMVOtyBfik5JRcHYYRHKUC3nqOkvmazCjubxClmVDSpPioWsagiPKdal3wfqjkKFEQ0J4qXNhL9bQXIQLRMjeWGc35v093YWXV8jBCRJlXrWsGwDCOEvkOzlRBZaqBypE6lYpO5S1BVJqqddXxw/ZiQokVSxglqfTXcZRIYYygkKEcrFP56VIjle8t1XVLgaUMJR0FsjwWqRIFTDoETKgjA6lfqiuXBx7SQMaQg9snipmag4OspVy7vvbKmLEOtesMhMaM/qIbihl7H796zPj3ohuIGT9+/AZjxhlnZcyYwmPGb7f9czHjDiGsYUV81sb1tT4x+qyNfRwZ+7mQhWc2hxjf1/rE6Jbh7BKE2CNE8T8CIqFvzBitj7yNID4RUdUaATFBjywGSAgZWbQwCOZ1IPlXVYVbQMpwH8rwX35EH0IWol1Egni8hhy2D+7EDgZSwrZbzVVXxPHZTTGWT3Qwbok+bIDTsxCCNR3P54MmPkNU1rtYH7YPthAE3rmQwLFrvE3QO/mcgaAHr4mXowd4epZQ3RUTtL5MElD2tYEBwrZHaHp1wSYWpFPdERmbVDzZ0nLMELCBq8jnKvLDWELMAzYxpwdQfAU8YTdDEsOaVMSCtefC+M4NHq4VT254nKszk6CrSIHvZgZFax7MqiMIlUeiOrMIUSnOccm9ddm49XUqboWNbDWGaowu3Au/2zlEhGr4C22J3cSwG+qnPO5/dRGGV77u38AuDFH4j2sX8Wl880mTdrZGkfeegKhqFXl/vKz9G63/euAybeM7i+rS6+Ehx34xKcJnitqG2J6nWVRj7nwz6xdPF96B+/U2/SAz8dt/Ygj/5tEykcrLNFPtOva3CkUWYn5Y2Nuvanm+oDga2+0iUdeyELK3by7UzpN9aSEf7x0/yCJJBXb5gIebrUOil4cKjSYrW4xhr5jYMv9fiArbKWb24EI+66Y7+sv/BchwAukSvXxbQCAlBbn9pZwCxFPFdDw5zDlfTfSIrv7E4bJn92tEBNzmKuwKxHRaJEBKHVq0oGWeWt3giSq9CgaQJEDKHFompQUxIEHSqrgdCVxictz1vYw0tiBTT5zQ5PimsCMzyY4cEuP4Nh97iO9g2Zqdj4TqgSmGUZys1Hnsh3/PF8nddI1hmhnRGPZ+pc5jBZZLkII+xY8EQy9rGEhSSYFzoeSxH5IJbgvur2bAs7X+TCH9pVYaGW2S/ZX2YXSKgdHWSp3RHtifpwcm9ySTVgNcdnKtBqbVZfnc9HMzESeKbLsr6Ahjqv9UcK3OOCFT+pv9TABzjnOtXq85Yw/Mywtxxh7pjD26M15SIZ3xF2QK12nOuItWJw3OuCvIGUsHM65COuPVRmdcbnDGLhtelZYKDz4oxjwIx5zViYghRxPUGNbI2pztdE9S8Hc7zP3hrKqb8h0LvH1996vX8t0+od4zZ3D1rtDVW6veSNwVC1BOfqFKYwTEIn3amfvWe/5IEOeEJ+6ZziGWXsMTmxfoutAJOzjEBtzN7sBL2YMLODKV3zefT7sUNJ85XVLqlSj1hd9p7ntZgE87P007n1Dt0unSfaOXrJDmOSEoMVs8Xx+6D8YhyHCmYnZ1xSJ83YyOM1dzDL44Zb4+cj8EcqX7XsrxG+edDI0GzTfam125esg/eoKIfHuqtci3RfAkKOqn4HdrudegEO+XU90lrc7Scp50lxdC/fSuHMv/ck/J8FwSNkBWSiRhSxGFmlSv8GPD2m1d/NUUhtKtTQe6U5LTTDsaVMs6XDBMbqirf9KdtpLenDZtrRiTcpeVJcCddlg3BA9Hx42VA7FRnjtPNDqA+jvIntNs87iyAE++dNuAhofyhhNlcqJT/su+MSdfZ1lfo6pqsKbburoV6J7FSzLJx6SLew3VYvpR7qYvCpHOzDG66Zb1nLk8jjM6hTLWn+VDWhhTEwNyNccPI3L0cEgxhnRGJzSaAT+HB8+HMYatIyQMF57biHEVw3LIERxUGSNozckcn0dYWLywjmDhNlT7WUdlCWIfjs/ZqXmbs0Lt/0o0XxTTt9KhLQsMVD9aTzTwlQGjw6mZhzoZEGqcyGAsH27YGMZvInFcw+2kEGDYMs7dgJ0AN3HAMN3r3qQ7AwY0cB433Bs6jeHXf53VAi3cayz+/Vf91xz2K5PriJ/ZuOs6aNzpcWpinFR0H9TZQ8y8IYDRZvmzcykm1FyyKz0OJtlDUpTwvilK9lwcrPSVFoQY1pyeIAo9cpg5hjTo9rm6l1TgaDaHmMAgFLtufHMMfXTPQYjxojz/bjaPlVLYl1yHML19I7LWObjqmOAeQttRP3fnT0j+on4wfl0d4d7afZN7m5qYIIJ6ExRwlNkT+wY40QbdK5/DLe2tp5nKwRGpcuXI+vAjmsrhti1UuUSytHFihaBnWr8rURMN+jaARinjzs8IoKpMrR1/DVU7UKpzX4FN02QxOqG/9R0B83qpzn8/FGn9TLhGZFNZqktAgbEMhvXhjlBrU/o4QGNHCQSUIObBuSxJ3ERtCgwwpnFgLuVTYP0/JG/fQ97+9XBwRP5uVlBEHncVhf6wBHs/LFizIuv6qtxUYlTlyVnXV+WcEqMq35p1fVWOKTGqctdjQpVz+9QTjap8uvj6qryUM5mpcvNjuir7+qiyZslfKeaqnM7kCLcfluzuRXb/8VtNlb/qNqqyjNX/8JimymUGVTZK/sFinfd++DWTJD/s2qocUWxU5Z2ZN6LKB4uMqvx85o2o8htFRlUuzrwhVa4kIMFlGJt5PVVOKuKqvPUbGZA9fJbx9sjXXJVfY4jiO3hBATqmnpKLurIgRsmPYrA93tlYBPBZml4hR/ayXkF4feo162EC/p3ZFBon73Zmu8NdRf7QeljydqyH2b5T8drKoc3Z0bweZvqw33qYsaTg07/oZf8IRpZe75cre+knxZqDXHS4Zbax6H9gSkjR31CQF0M5NgtBosUKWlEnvMqhWISshdbaJKLKxuZZ6No6XelRKJJ7vpYicaFI0g+RuhcpuXDoGFf3P4frRXAfpEyRRXBfcy1dJtP2g1gF0YrgU2fpw/DA4Cl6EbxinMhoHsDkxITi1RZ9d2tFcMriBszSgjuG8sJMwzDhoww2RpNcmWSgRtXuEiA7ZvJlxhi5zPiaUBO+zLiccPAAy8NRmGW4K3t9ClF0UOXKuMxYEoPLjC8blhnvzghdZhwQtMzIsMXP1JYZO1bakkticJlxpDvy5esvM6ay1v0uMw538Jh2wVeyUvQBinHNweDVrrXpIWtvX3wfrHzuw/B8oVd9psN5r5q4SNiDaemUEe1U8vrEsiKzg5JCPrN/PCj7/w77D+vTf0RQ/9j9c98Hr7cNK0QBy36/SZNZktKnY7lZ5WSB2P9yUJZWbv0F978c0HK8qE6uv1dI+JOFsarTMI9EAxPfQSuIwlSJOfUcw51UbLW0tBnSJMBS58NpIVF5uBSzZp0yC0S18ymqdjJMDYuZZdOSI7RT5219Kp2aQTcb7FR4AS92xib31j2a3GCtf8g9DS+/MrGBbLqiqkGmp9Hmi2T5j7XupaAiJzJpygFiEnin8bf9EpFVs/fTVOfn27tLlEZfZGOb31Xud5+zwwNl8mU0W2QhLTxbcxmn0hS4/zj1i+TNzaeV1m6GSB63df0l6KPHr7kE
*/