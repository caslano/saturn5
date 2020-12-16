
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/template_arity.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< bool >
struct template_arity_impl
{
    template< typename F > struct result_
        : mpl::int_< -1 >
    {
    };
};

template<>
struct template_arity_impl<true>
{
    template< typename F > struct result_
        : F::arity
    {
    };
};

template< typename F >
struct template_arity
    : template_arity_impl< ::boost::mpl::aux::has_rebind<F>::value >
        ::template result_<F>
{
};

template<>
struct template_arity<int>
    : mpl::int_< -1 >
{
};

}}}


/* template_arity.hpp
rMjsLus3y39hdl10l9Cs5n16fZ3dnZn33swu8455owUtaOHaDlel/z+z6vr/D6v6/89L//97WBeP4ONKH0Zv0z7GzGvg+f+NeM1dXkuIT89Oo7cgO7F0282VbfE6z7kyrOtxmXZ89VwiKUSlDd8nzLTf50Gz5eZ9LPcDxdrLPRXVKUPMw0LKsKRPxWWonqvJ8Rovx7nkJTE7TVn34rkKVeUqWTL0tyn3h3W3L+3Lf7Iv5WDWdyLPIivrc/u1r+mcTM/2K19WP1vlrJR1hPQrDSY+xWccBxjKWgo5OS3ehmdEKeVgKAa+HxXOOanqI+wqadkp4xZWS1rukLTMNU9LTFxKclJagk7S5FKJNJ2VNOgucy7HyzbOy7xlujh9nOGYS3/eNrN5QdRl2/86y2UbMtCYny6dlOzY8vwtW8v2v9JvNtrQb/bRgpx+W1t8Xz1A/232/E+zjleu32xYNfk9lt/pIvQkhslvd7i0Hw9BJxyG7jgC2+FIDMRROB5HYyJGYS6OwRkYi3MxDlfiRLwX4/EZ1OEhTMT3MQk/w0n4FSbjOZyM53EK/oopWIe0pqILpmF7TMcBmIHDcSpGYhZGox4nYDYm4nRMwxmox5m4EPNwJc7Gx3EOPotz+W8/zsPXcT4ewQWSzv7V5DdafruLsA2xu5TrOinX9dgQ78EWeC8OwI04HAtQh5ukXO/HZ3Ez7sEH8AA+im/iY/gObsOPcTt+gU/jt/gM/og70JG0PI+xuFPKYRdm4os4E3fjAizCpbgH1+BLuB5fxgdwLz6Nr+Ab+Cq+i69hG/K/D31wPwbhARyMr2MyHsRMfAP1eAjz8LD6WRoD5NkgxCKzZwE0lPJshG7oih7YGP3RDXuiO/bDJjgYm8r25ypRtr9atq9+1k9L2b4nOqE3+qAPBmF77Iq+GIIdZT9+OAQDcDQGYi52xiUYhHdgF/UzDwZWnM9Fko7bJZ/5ks+lks9lks/lsv8Vks87kHPT6vtvpF/mb/XJKPfd7EinP4ZYM8PBzoPYP0Pri9GCFrSgBWvC1aj/J1bh8/+Pqur/h6pJJrCejP9/Whlf201ddy3dfUxHY+1V6v9WzPVaUb21vqreytSAWWBV3dU4blEvdVRjnVVPJHGW6/4yv/czXlJ/slAP+VPel3pIefnIPD4j5VojQsontruF8imr3Vs/56c15UO9Pkk/6cqWj7o+qc7/WcnE2/bkH99EJf+HLOSf3Fsz9tqq/FemXaOyea9onuoUactQ5m+rwTYjWT7Vs8K56Ms+68tn2/FaYvDF8zPqzT4bzWc78dpnqs9eqGC7i2qUzs0XEHLpZxRM62HabvWt2fLUnqbLQ4NNl18zW+4bUr6sbv9oK2Pzl/GmM87FHUrbYajh3OCkyDQd1ms+/+ffHPds/I7oiWnKj4itvyGq86K5+rxQzTv+nBf7Uq13SOZeNZ5fR43L8v5BWWaOVUPZfRn63xwXvNjQvrG84K3p508Nmhm15szz8x29VlSyfcNO/t7I36Ei9TP0ZPxsPXwa2+MzOA2fxbtwB/6Az+Ov+ALKHCn8Tkv5W5gjZY/U0/aiJ76CESjjZWkTkN85+f0rwsFEvfxNcJb1XdEJ3dAdm2AbbIb+2AKDsSXmYiuchx64ClvjavTG9eiDW7E9vogd8BT64pfYUdLnh7+hP9YgkQFYGwOxLnbCBtgZW2MQdsUumIRdMQO7YSb2wBnYE+dgMN6GvXE5huFq7IMPYT88iv3xIxyA3+JA/A4H4S8YjhdwCNam7IahMw7HPjgCh2EkjsGROAVHYSpGYxaOx1txAq7BGNyEsbgd43A3TsQ9GI8HUIdHMAGPYyKewCT8HCfhV5iMf+A=
*/