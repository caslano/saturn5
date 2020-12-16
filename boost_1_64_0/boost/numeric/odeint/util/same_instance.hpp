/*
 [auto_generated]
 boost/numeric/odeint/util/same_instance.hpp

 [begin_description]
 Basic check if two variables are the same instance
 [end_description]

 Copyright 2012 Karsten Ahnert
 Copyright 2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_UTIL_SAME_INSTANCE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_UTIL_SAME_INSTANCE_HPP_INCLUDED

namespace boost {
namespace numeric {
namespace odeint {

template< class T1 , class T2 , class Enabler=void >
struct same_instance_impl
{ 
    static bool same_instance( const T1& /* x1 */ , const T2& /* x2 */ )
    {
        return false;
    }
};

template< class T >
struct same_instance_impl< T , T >
{ 
    static bool same_instance( const T &x1 , const T &x2 )
    {
        // check pointers
        return (&x1 == &x2);
    }
};


template< class T1 , class T2 >
bool same_instance( const T1 &x1 , const T2 &x2 )
{
    return same_instance_impl< T1 , T2 >::same_instance( x1 , x2 );
}


} // namespace odeint
} // namespace numeric
} // namespace boost

#endif

/* same_instance.hpp
Q56AbNtsD9jX2AMft23OgiEr0NpVzRoS4kE7Ncb7oCppIztL+RyzvJRdcj2HAzUnQeQ0ta3REfgGYMJgD0wHTBiyApPbGq2B85WWxaH6r1a4R/c1qsRrHV2GKkF9oFaSq2RoW6Mt8BWlb89V4Y32zyXnRJ0hhFomdyg6aF415hnmbDru1T5OzIVPwvlLDkr9REzmi+XeS/I1KvQXKiLfMq/rQAGG/uqKvOb5U9vSrIETvFAjNjlRaKioLc0W6A91S/CIfi3avzDmcxaiWtNNteCM/VH16OFB99hqyD71nBk+0fCh9nB0uGM62GU8MrOyEHr6oGLHGmcglzI9lHDNYdvoacda3QPkvDuq2B5UV2JGRyYW4Y/kcCnlhX7xNaU05ZgW9C7y64B8Lir6ErmcMO+e0EdW/eXqP1hd42cMzqz5s8UFtn1GTdRixb83/jYLGOS6Lxezqy+H5ePpgx62Wbi29sCu0/DvNhNKf/L3a5X8spOCH8w1FrFUeY+dSh5SVgNWpEBAsCfJlAzQCnlCZWMvHzeJiULtDrYm40dppfO1hP6fhdYdZEXNFwNOcKjeR288yqg/SdZ56wmjFtmDff3lnWo60J9SNhPQv/O00nn3QziL+ZTTkqp+shgF5dzMFkCQ49W63P0TvWAIiNPixKtN4tfJGh28ohdctN2zU0GbFdFv2LpbC0IFGTipAFWYoQIPDZBq+SVx3lUvYrUu1nxyBW9KpR9ji0dnxzAUFpG9Wd9OU6gZZK4fIyFVK9dr1fdYoaWOMuLOrydc5GABJCi63g7dQW4L1KlB9av3LoS0w1388aqEkG6GPLvmXYpSh17CkVMtKxZwXWJAJ1yC9uPRQtb9I07Hhqsp1WGU94gqE7ZO/k0y8YRAyRGaUIzEAOJxVAbumEFFiZ9J4+k0PimNJ9J4jzQ6abxdGq003iGNbfiK70pjK40rpXEvjd+Xxt/QeKs0vkDjAmncRONSaXyGxunS+AiNmjTeS+O3aJRwxDekcblst0IxQ9puoodfGr9D42QaZUhxqTROo7FUGi+jcRyN8iv6zKZxDIwaVaRo1moLTOhiogoNKW7BB5J2DPneLBo9DDk7FlJjyMkIpAVgUm7VdBsju0GpGCsBvEVYBdL4axpzpbGZxmxp/CWNzsUdUfHrm/H5CDKl2ip0U7H/SsJBPz98HRvrn3TX6Rd5xJ7PcP6XgwSpm+OTwzJUwLyhw9HO3EFjdzlKESpgX8TRgSyU4cgcax/1QmUd5mgeq21T4hBihjmGj0xfe6IdxFCqz/aYr+hQtdOdPgmHZJN96sIhRkeYWy2iLkVzo3vl9WTL6z+vOs3z9UV6tdKoKOUms/VCOGKXFEg1Mq9t5KS0RuV/SCz/oA28w8xRo+7cWNgnE8Ienq7CHgPpEU98P3tg16AauUeU38ZO/sCJa3iUDEhxYxf1YYeUKBd1nGGZERgQar8qANOcgMTULaxQzMj1CyW6KpcJkoaE8xblIPGDSPH+UPt1rmUrpWKm5U/cSw1DkRz89CXPyBlO/blvCa8wXCjJtGSDWdkM8qj5jwU1XMZ6pPViD83yk6UcsmjGJzrPLQ7PkksKXXL4yecnl59Cfkr5Gc/PVH5m8DORHy8/U5guWXu9xgMuTSqLbtSrtJluTDdSY+ngCZgxUIxUFl7B9TxvBZf9G9LC/LNEZvy8JfRecA76zJnhJYmeBFQEtRsDF/QOr3DGPaRm0hVP0IwdRS95957bcFE5mjmoyE03RQxoTVO0AK9ukyNghFheY+wtaFeuPr2wdDK30u6ZjavWrba6035kdffDm4H3VLyn4z0L7zC85+EdiTcPbyHeCXgvxnsf4v0U7z68+/E=
*/