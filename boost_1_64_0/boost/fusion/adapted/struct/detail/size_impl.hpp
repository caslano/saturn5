/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_SIZE_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_SIZE_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct size_impl;

    template <>
    struct size_impl<struct_tag>
    {
        template <typename Seq>
        struct apply
          : struct_size<typename remove_const<Seq>::type>
        {};
    };

    template <>
    struct size_impl<assoc_struct_tag>
      : size_impl<struct_tag>
    {};
}}}

#endif

/* size_impl.hpp
C6/JMIIEdLwpd+z73W463dmBuQRJuftScvdNF26TTXPRq1vYY5wz4bVGZ3+oJauvojy/sLLSyKvdZ9XZdE2Yo9nG8zUzeSZZ+79Xe0N9J9Y2C96XlU9Efhu/jVWfeWXjqlFTt3+fw+9jW1nlzKsqoq4V/xbn9/KS4vwTLF8pjv862SHzBv7T+Gcz+0CzKW8ec4+DjkKmIL33VEt3ADt53oK8qjz7935WvUpOL3krHaMClt2YwsIdRzjpjI5Ip5Op68A9s7hnJ8LZI617wvasy6y/cx1fdgGfdddlWH9Xj3X8xFk+Elso71229Vh/Tx4Z+veiUc7fwe1zhuaW2cn2/DsT3kAeviOs+BWdip32if+V9e7tX3aknm1ZgfX3sCND9/rnRGm/t7jYHZsX6mcy4LOru8vz9+n3wPPX70WyLRbcjsJ1A1qGtJPxsl0W+T5ND9Y9qLSfvbElOZ36O4rnudaqr3D7ZfllY9VOtiXe6QTjR+e+QcHtxPFDlm+/XvIpGvCRV5ivNaMwv4AUzl1HJSV/4+uo9FKetVH8Ambm/z1+AdtE8Qs4NX/T6Mwk/MUl/MX9k/zFTbPWilKbt71x5RavfXHHmp9/PaHPl4c2TFck26NxksZPOUmhOhuvI97W8A24A3xTdsXeglnwbTgQvqM1lKkejXvAnvIHtqXeKXP11vmTPrCXdCkGSJfiWOlQlMH+8muWDWdLh+Ie2S97UvbLPjFZwR2lO9EWDvbL0VhjGo11jBylRg6Nf4bJ791w2a0bIR2PXPlrGykdj2Pgu3CU/JAdB1vJnllX+bE7E44x8WE+nAkLjLzya7cQjpV/sSJzH7IUwwzZMRsuO2YnyH7Zc7Acvgx9cAWcCH+AFfAPWGXkoCzVpj7hJNgBHg+Hwhp4AzwBzoWT4b3wJPgmPBn+CqfB5GTbP95weBo8Gp4Jr4DT4U3wbPgwPAeugTNg8ya2f7d28HyYBi+A/eHFsAheAifDS+EMeBmcB2fBpKaMfWBTeCXcHc6GA+A1sBTOgdXwWng5vA5+Bq+HX8GbYMfNbL9u3eAtMB3eBk+Ed8Az4Z3wZniXKQecB5+Hd5t04L0wk352PjwM3gcHwwdhPnwIXgIfNvUIH4HL4AL4BnwUfggfN/LBhbAl790T0AsXwQL4JCyGi2EtfAreDp+Ga+ASuA4+C1s0552GI+FSeDx8Ac6CL8Kr4KvwMbgMvgyXww/gCtgUR2+vwRHwdTgKvgmPg2/BU+E78FX4LnwdroQr4fswmffmAzgcfmjSgR+b++FqWAg/hdXwM3g6XGPqG36h93B1ksaZGn+a9zA9aM70tXSuvpHO1XfqX76X7tUPsl/4k5ED/gynwl/gpfBX+Dj8zdQ//AO2M2kn0R5hI5gFk+ERsCmcCDeDU2AzOAduDo2szeEXsAXcyfRdsD9MgQNgK3gc3BoWwm3geLgtLIHbwbNha/gy3B6ugDvCt+Au8EO4K9yM9y8VtoC7wx3hHvAguCc8Gu4NvXA/WAz3N/LDdvASeAC8DHaAt8A0eDfsCJ+EneBS2Bm+AbvAD2BXuAoeDL+E3eA62B0mJfOM4BawB9wWZsBdYU+4DzwE9oCZMBP2DrZnmR+b38TM/Nj8JmqcF9Vv4hLpvC15o369t3jW6ze2rltCz+2v0XNb91jC72AUv4PaT0jotzV0T+Kv0G9b+QZ5EVLeJB1CNqGIUPtmYp8icSWuxJW4ElfiSlyJK3FtmmsTnf8v25jn/08w/v8yzX5Z/6xBWUN6D/QOHd5n2JCsLOcYQMBOQE5vE29Q7yOyXKwEyAdg1yAfgFUu+v9vbMv6w8FmLSI8Q2sHLGad3Ne2jbQTuCaKjQCfa34=
*/