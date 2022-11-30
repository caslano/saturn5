// Copyright Sebastian Ramacher, 2007.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PTR_CONTAINER_DETAIL_SERIALIZE_REVERSIBLE_PTR_CONTAINER_HPP
#define BOOST_PTR_CONTAINER_DETAIL_SERIALIZE_REVERSIBLE_PTR_CONTAINER_HPP

#include <boost/ptr_container/detail/reversible_ptr_container.hpp>
#include <boost/ptr_container/detail/serialize_xml_names.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/nvp.hpp>

namespace boost 
{

namespace ptr_container_detail
{

template<class Archive, class Config, class CloneAllocator>
void save_helper(Archive& ar, const ptr_container_detail::reversible_ptr_container<Config, CloneAllocator>& c)
{
    typedef ptr_container_detail::reversible_ptr_container<Config, CloneAllocator> container_type;
    typedef BOOST_DEDUCED_TYPENAME container_type::const_iterator const_iterator;
    typedef BOOST_DEDUCED_TYPENAME container_type::value_type value_type;

    const_iterator i = c.begin(), e = c.end();
    for(; i != e; ++i)
        ar << boost::serialization::make_nvp( ptr_container_detail::item(), 
                ptr_container_detail::serialize_as_const(static_cast<value_type>(*i.base()))); 
    }

template<class Archive, class Config, class CloneAllocator>
void load_helper(Archive& ar, ptr_container_detail::reversible_ptr_container<Config, CloneAllocator>& c,
                 BOOST_DEDUCED_TYPENAME ptr_container_detail::reversible_ptr_container<Config, CloneAllocator>::size_type n)
{
    typedef ptr_container_detail::reversible_ptr_container<Config, CloneAllocator> container_type;
    typedef BOOST_DEDUCED_TYPENAME container_type::size_type size_type;
    typedef BOOST_DEDUCED_TYPENAME container_type::value_type value_type;

    //
    // Called after an appropriate reserve on c.
    //

    c.clear();            
    for(size_type i = 0u; i != n; ++i)
    {
        //
        // Remark: pointers are not tracked,
        // so we need not call ar.reset_object_address(v, u)
        //
        value_type ptr;
        ar >> boost::serialization::make_nvp( ptr_container_detail::item(), ptr ); 
        c.insert(c.end(), ptr);
    }
}

} // namespace ptr_container_detail

namespace serialization 
{

template<class Archive, class Config, class CloneAllocator>
void save(Archive& ar, const ptr_container_detail::reversible_ptr_container<Config, CloneAllocator>& c, unsigned int /*version*/)
{   
    ar << boost::serialization::make_nvp( ptr_container_detail::count(), 
                                          ptr_container_detail::serialize_as_const(c.size()) );
    ptr_container_detail::save_helper(ar, c);
}

template<class Archive, class Config, class CloneAllocator>
void load(Archive& ar, ptr_container_detail::reversible_ptr_container<Config, CloneAllocator>& c, unsigned int /*version*/)
{
    typedef ptr_container_detail::reversible_ptr_container<Config, CloneAllocator> container_type;
    typedef BOOST_DEDUCED_TYPENAME container_type::size_type size_type;
    
    size_type n;
    ar >> boost::serialization::make_nvp( ptr_container_detail::count(), n );
    ptr_container_detail::load_helper(ar, c, n);
    
}

} // namespace serialization
} // namespace boost

#endif

/* serialize_reversible_cont.hpp
+Vz1Q18br47DRvrnOK0BBZiDtV91nSSND+tF5OWXNVvAqXWj602H8IQ6jqCU7Dvc35Ed4s1bLEDjW8Fqla1hPypkm1VI+als1PGjU5KxPFhX4NmXwMGlZf/6DoAAtcmh6/04fJCp75dv6MDUPsELtEXWat6GwDloLSmpciLBOugUcFatqGdbapLxNec4OYZuGejkJ/vwcNJ6VlFFC+ttg8jPj5qmyFHq5qFC3n8/rjqj5MHVbv8ElqrR8TO0AwOWX1uuRLkPi0VW1aEfrMSHrt5ZD7S0q3yXNpMTCxg0as0zPy+9b23gGz0BZaw1ePXGUExMWLkAy2ZvR0TzyNobAY/FP82I7ORcfUAZX11MIDyA9gY2ynAVD24iSGvIqfB+iQnf6Zeaw0WC2jXNv4TquE3ilQ0SWvPOVO1tq4jfPSsV+Xku80O6PyuHE9LjyNy25fzPYTRRjD6n9VveNV4GV3dcnLE6R37QaXrnBokHMrTWaPuRu2vrGKx1PR2rbMRKl49Dfm4rOr1FZrLWwIYeWL0uE06JShggXlEhmHdYE5L6/fruw/pQitZvPDecogHqthyKPT8vYpcm6aCDAzsgbkz3dzsiO7U4QiSIOU+O3aeBA3wV+LbSZTVvp0mzk3rC69Avz92sZFwW3Rf/ImopivchbrfpgwAyn15YR2niZhxbZhP1Ou9Qk8SA6qReLVhnxDGnzmNwWG4ovg6cKaRY67gsYYj/I4TrrV9XYPCVi0LzdU9TBmi9c1OXyyWn4Y/Vmg/qDj9u4Y/6S2HG+SVyqtMBn42j3Ciw2+86zcxfW3WBisCRcaCogeb67XDdh0oeZCmP/g58K0Pazfxm461y/3xujuP1G1uHCMfcU+64xevTI2xZ8qtOnKuka/XMvY+1jj0VW9RxSXOeoj7Yuc27Awn5ef6uiW29K0WHZUNCN+JHqPWbs0o+epwmKzHj73TaY8Qkv3Fyj45fUo0GzgyYSg9sEQ7pH7jrm+x4dKqUmlxWGaY6EwJAts0cl7prmjIIfh6DH1FSa3I2Z+Yfu7OdEFsZs2d+n0GVLXVHA5YTmjJYacydRxO3+gvqaJ1VOcuJfSCa/6jmpbtDsOdH25EZIgSuQW4Rf/3XEZ9EcI4+0ufMfFgmnM+PUaj/hnYX8Zk5l6IGaY1gNTzMJEgZ/HO1CtROzh4hpSpbOQKb5wfbfahNLevGtb67MR7MrWmd9z2Vd027LBPu0aeXwD9pfoB2xv++swycW1Gdns8lt9P1vGCtYx/NcKQee63X+LLLu+G3HixvU0GCT7gHpZnbwcwEof20IPLq6nYSja4u+OzTtC/geKRVLOjcyjbkYSmqyuK4QqcxErZKkZauZvoQp54bwa+hl8g/iMOf+OhEVrTw7S5924hYL8fzF7NrEAjP4id9fWNz46E56UUZi8rJgVWxbpnFBZ5+mzS3L+vBGTtmIWbwanreOx4ThjvbeY2JYM7j55pJ1V3KuC7D+jYp6InO/xou3WmdOdG7TJDz7TSGcHBuD3Wc+/Qbu+iRXFrxWjxOxmAivFJG74xfvHmhM1/cY7tL/RNHpv6rZOPmsdr4Zn2mzwhffabxbA9Py5ARa4hos+XXr/p6Ug2uPUct2q68xJQEd9HwaupNC+zfzno9H5dscTQEeoefgLQepfVh8z1LsxFy/yPYjwoXINt8Ea5BnjYn6M5KqkECP3hnA4dmOD9aC82gJE7bZhKko2Ia0i6ptnNkaXTJjmCTvhil2Gr94flwyiAZTqUQG6nLshyJ6Hc46LE21d1fydB6t1Yd/JW2Z/KG6sex6Q+akdyPOnaqVForVf8ZVUYbkZwUO0lJpIsPdsPecvehMyM59/DoOE7SCiwlWcaentmwjWlPXr8ee4pjK9p79B/0eW8qj54NDzVw/MjCgph17CORT1NBpqSZawEyVmWX6KSQ3s6T4Vz/TXcGPzc5/b1xvgHxntG74284LFzp3RJ1n/+EI9gdWsTDqzSCtPK8vaC2/icQptgUxcx79lnA3y9Uby7o+UHq4CR/BjfRvtaOJxLoFP8+QU9oNEsi9plI6kdEBaM3EB8A2gxpk3V603K8MSOuKaMc/8YLogMAAiz908M/KZZS/lPb75QoKbUl3UhiLV+qMMLMD1KERvnnXjDcy1bIaR736QklBXeFwUN+hOiVcRsXeve7jXwEyvWShyXpfLCRCPVlq/1KyOvJgIrFNhfqHfkvT9FqQKjmO6meLNxItcx6Hivw2eambJugk5I/0cYMb/GF2pvLkV8dODhMEunwOWm4KFuH/+Q+XnVGaDPt5vD4J7sFtg69SRmb2dpugHdH4NdSkq6yndnayScuT4bf6yYG7Q0+TiIfKwEVy+/MStC939LapewvZbuGfeHn4xznibyfITV7DW97pidnP0zANuT6GqucwPLTF030Y08UFt/zWm4ag7/iD3OPu/4QzDp9FNpTezf3DUcg/oropKQdZ/McSWi9HPgoC/3apIkDYEzJ8wvxS0s+gQ3s/aVH6WGiQIZH+f5tVCGTJ4MH4Ik5d+/IkzxNqwihGm1SPV74Ms8vwGTcYdzspehJ8SHY92sGkWxenG4+l/2jF+A4tg5nHCYm49HJm8W4WYCGYmbqIemrD6RAxj3b7+C8f0uer7zja8HR04YVPLZPGKlekG/JcCX+vh1jjR88gaeDFyhMJJwduh//SrgnQ+f9GuzppE8aG++qYjNEAq+cLhiJF/cJewH8m1RPBKuc2VIkPElHKY9co0CGlOmkOIf8r8GWLHZwGZ4AuTdp76HlRgmr9HsXH1/c3kMsPkP1nU1ZSTPc3pynskhH7iSs5bJsSSodWn/MRXSPu+y/ZjyVJN/cFz4rImUiCR7Hq8byZu7dFjzLJl1/Dp/l16o2vC9Qf2sD9207ZJCI3EsKOHCW+1pP693wixCqMXSuKM5wRmladGLOt7erOnuJfVK8Amb9CiOUHaY7qC34z6jV9q9kXNBeIjbGqkl4so96PbGOcbn0dLuyQiOGSgSv5G2JGqGx76RHskm26L/dr8jfzsZfqcoqIonwqh8F6wiwHTJPKmeoGBD9o6FHwpyWHYGAzhDvY2/eH2pkJLdTCbRM5cWK5voi04M4X9/fSVl271HelUR2lRKlqKTJUH4n/fHxncS3g7M6HkVZaeXYk6xn7tq0y4e6qmv6mmRAf+Q3SI3ccOOfe+aYYmP97Lj5NB/Wny8CiRUzAS1dQr0V1vYETGImoBfqgL4deygxuK1g7HjkD/JlCJruiSS5tsiPMv1N5KddVHWky9OFyC2PdN61eoUzrsPf9TZ780B95UG6pOM74OzoHOMBPfaV4fonR5CnvJT807YPCX32W1s++0mX8PLZbem8fvpErYIYLrK5AeVbZgdrkj1UOdu2Wf+ksrSr/+oS2np12HrsJxfC0zSq7aFKawXzAo5EpkXyCmX+ihfl39Wg2NI2t41x2xinNxqrq7FbQCcSuBOTuZpglHZFcRX09cHeUqoTec0Tnz93zA3mjPttr0GbD+ZRV9Tw6WTRv1+qqhCBnWt9NST7eDraJIlaPwCLPp+aVn2mJd8ldQE68QjAejasC4SP+p9W6cBq6O0L/718sdNhQfgoSbDDQtnxGI7pW8dSZkWpmWd6r+GSVWyHcpPfxX4dsqyqtKMU/R02ZsChq+gwqlUayxLBhgSGKLBnN3VA+HLT50nadyueNMtUMWe/exa+nC3L37Iel9tuiDyXfsg2TsidkTpDosMlBxkmpbUMcftoUqyjA35WT6w/4DYyb8uXIuWz4+6vkC20lvvh1cSWjV9Ontde0Rr44Kn+JxsR6Mj8O3S+uvTCndmU+bt1jN3rjcu3/oUFxaT530JhMWdWPfpfzxzlxdg6DHDMSHtHcUB/1T8jCYzuOPZD8gtP/3j0az8NDsuZbWoNJW5772LMp7jyBK+aMZgWT4DZW6TXyW7D5nlHyNk1q/RROncOIG7k0G4D02kKlVy5orpm4Pvv+H1ff6c3zN5TWlCzJyP2lbB8xvSra9rMMrwZ/GBTvHrmhtXj6iwNwjH+r7RPZVNWZp1ekTTAXAL5T0rbcVJo++2s4Ci2VbVJSsJVbxxX7t5KbHOIy8EiydYYzoHJEMDbGhp+JnmGdCu44SJpMO5buOwML9QcPn/S9zEvb/WNizXO3gMON8ZJGgVpN7nCqxk3r7faktsgI4Qdvl+HHoE02K5X3Z5m83D3Nc/kIYYF+2EaG3H2b2XRj/KW392bLHzbvGT+mobVZfR1jrAtr3/E0mKOtULyrDZHeeQMoWgzyfEtl6VEDNCJ6rPeOyHx0MhgQa4SuhRNnO65nbFTT0LypjkOVsuto0uPmGsCc75dQxnFcU6+3dg96ruvxs9Cbwi3Kh7zMNmz/LB/5+PX5UrApLigLx5l8xaqT+v3C5CGJur6SQow91ktvPnErCi9I6xgoe6inA/8IurIAQD1RG/eqQjX5WODnlkqfUnkqH2gMVD4SknQxfr1E0FbaH+sjQUlS4XamaVfGaAPp9L39rBr+POesefDWTCf0u4H7C60X9k2zSPJrMKqp5Gtz98eOGKbX5seMDj/t3ZJJMqkKIZbTuorJ4u6/eUy/2Q89K/vqZOrnGKOR2SRIADq0qVyjPDHEb2LqMewRJJx5OCE5dB8kvH2HUiOVrgCSJpOAKc4SUp9v40ZZXjn+q2O5XoV3Zbgv/qy7fqVP1vCPiL4EnCwOIBOkpzGdFpuZH1ys8E9L21oCPQIfHgpjPe2uSDvQm2WFY79HtlnUE0La0eGcA6R3p5txKkY7BfUv69gwtGT7p02+DXhKn9TSnBlMbqACA/avy/GttyC6V0EpJ7JV+xjYei8fNmzcJ0pNKuYyLlLCtdmfo5xTUqSPRB4I2T5mrk34T9zCJYjmjjMVuZFpQTV9K0bCSbRg6YUD9piCZbvWNKiEHvzn/4aPHwi6TL4moEjSb85J3xmRWqGsQ1eNYG3XC+G9Y3PpRuVDpwTVGY9RB+PB11d+2+YtXlwDJFDVHqa70g9H8InInUJYubuReiTCmWSvpi3RIcwNcgVTZSsu50V0y5XzX9Y80Pq3fuPAAhrTIzKfBChia4l5kE/hBtAY8+rEjZ4HEtujPn2bvR2kb8t9ppZv649lr2xdsxJk6eX+Snn1/CqIWvs+S4t/GtS8jXJ3t7Qj9aWaEtkeM2ZjxWOJ5P2q9BDqLUjqOHLSdDYKqc/oSloluV6P1zzGP/aYBp3PCAsWNZJAcibbB0Fy6SbPoWvuqgkkjy0NrBejKXh+vxlcynDWfuvDDb8xwvApGh8tohHfh9i26g1pFKbMPJDGgs7UoseU4EcE3I1uLzgSChk9HeWUZT6nuz7+bnaRTkJzZzLn3sSNz/6y+uiJMvVYYatgHErA3SjzoJ8dkHAMXR328P78LlQXKbAxsqqRmdGIm4e9z+fXFN1Uxaf2Ch3UTkByjc3JzXg306uo1krtM9qQdqGIwUioO/zmv/yYm2VwWOY3NcdXMmw/l4Zb17qf37g/PXT07b0f35gw1Yhe3bNwjts99v5RniawdIC09kpqUEFKMuYP31DwKIkhwh03Qhpu2SfeGX0AXg87K/cefNXuIYLgvgydxHflmRagMhPCHb773bymE0iEb5KGuwIKeMFTP6EqBwk2lkkb0fDXm0QKBgkF2yz2MSNeNEY+JusTVfLxXHsnnsdeMwStn3SFWUIB7BFGhiHa1aFB2rkPDWqD1+WXVXx02AbIoMKi0TcQeVdMpj3Pv7bH1SZ8uOpYAVnMc5KfHzSVhVuy+f2QS5KiJSDOhjJ+OcWbParjtLs27zRT0IoWsFAfmO7oyA/PO8NrnwsUB5IEjE0mRfuoVHHhRT8jgwLzE0LCdfM8uo+9JeXSbrdRNxrp1VicW2xy2AlFUslbVfgRN5cmmkjenaAs1OjNdVlAskIkNurlwu8wj6+WNORvpPh0Ogh672biDGWKpWNmaMfdepvpBSfHv+wOxSu8UhMoUV2cfpp38ps0wePSD8xkyFbedqWxCIaXRgiFO7/04UYBub/+4C73OD01yQ2yB4CNNVN54SHPdN7sQevSvYNEKr514ZzP9OT2aMi4/ke+im0ZrpnKDCiAv2mvJN1DfSqBhNjbqV7YFexgR0BYYmRqY/KCL7b3i5shw5NMbqJly/khjB96iiaGLpHa+GuhIWMsbeXXSoX5mQV2soDE3d8dSBTE2tX56kwzu7YI+UQNK6kum6kW2m78r99mhD8oC0ZBiyQalM5GJBpgKCf6QnAKcx0DB0LfMxSJoz/V3clDWjZtbNUPJ/MeY8pSoc8FQ04NkYD1I/Ln042FgkFS5ma7zxnYIHfm+nAEj4ncRvTfsf/8e5f8R30DjTutQdjnni/MwnhgjEd5JKFhJuPW8JRGiQXSOZIOD9x3ylz4Deo3GR/HS9tCPoM5w7ZR+/IsGNGSWPSf0q4fEm0X08bGfjHo+9Y6+3IGZLtlKA2BNscW9sOYy7tPA1CH73nDx/Pate1Yems9jb/2OPqmoxRjBv+xC35FBh6EyQ1/VM3UhT/mR7jv2pn5ws/GWY/2cDFuJlp1HOP66DDXIV+IZPTiEm2nL1kYZowzYPc19jHV7AFmMSqqljp8Hm/sPaZEvq9izn3HqE2QohmmTqh5l+1UoOpVr4ZzBFW4Hyde9pV1vkHY8eEwPcgdsEaVHXyJbYGT1yv//S3ry8aLt8qKSnZptOycnNLSlFGx06krpWglxifsGJ+j0PfvNV9zsr6jJQU7+2Tf13d58/w/k091tIiTW748e1v8pHf+vcAGMOEi5iwfnDS6UPLaVeQwO2a3KZHz/qNPr6bTm3sJPsga5IEusSAC04XOxd5Iqg30uP4Uo+pK8tr+KKAGVTv8T18YDtM9D6ol+eXD1jIagFiI5cZtS4vKQ6qEv7bfK9txdBVd6hzaDI/lB/OdxP2RUTbY8qt5dRtxsNl6DZxFnm7qQpMGWPwXre4YVRjQkP7NPw/DVQoNhNxBIzfYQ2YRLgVZCafggOSuugvKYl33wimnJV0lZ+TXKX3qElmSstm1odVF2VGTfKFZ/m84ok1/HKqJmiH40/NoCZMQLybZZW+GSTxbYzw6mcPrxRGfNENF9plNV8gRz+WHd5anekC16Ccibrhj5c8tcjntmXuoqZ2RJJL+vUcBI7UogIKJ2h7mssNKPforO+I56usZBBsm4w88/p7j6yTh3LR2hUcwefMBw/k3p6eCbLNIVEBajV6j6HzJI1oxkAYrrGmx18H1VpWIEfHTyufgiSaOOndO5WB2D5q2t+XSZNOffvC9n9FIHLEn4D/mfu+HMrPmRwolB76IOu0mv2pgze4sTAbHeFKYsi80QLNtnLpE/sYEBc/iRv/wm0luTl0a+pUWxVJpbuPUnF8IEE6fK5WSoYGR9GUNcrBD9gMifn2TqIrryVGCqsMasFk+XLfT+VrVaVvVW/X8WNr18ODB34imYLdcJGVbL6H2nPAvbxRd6YIaVskWDcYnh07Fyrb9tmLmVhPpxZTwJlELKT/QilyJtfpg/ObC+C/5jieSfXaxc2j5G4AFMb3ICj7zaOSc5QX+6EH9f3XrlvueBbQpySuG6XlcyZg5Tq6ml1njHHTsHmufh1HLKhy
*/