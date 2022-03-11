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
7+Oa9vlWl1535hYPER64PPvznKzwNTMuXH63Z2WN9Zln8fccbi/fk3LSute8Nya9S2beNZZmBca1ibJNETfTXnYuosWNZurqP9e9NCl+k7xhTBv+88ua0pXFjxzopCPmjePvbhvd4dvyllTuyFNzhj4OMO7Z2eH5/cF6xhXT8of4Gp6NHp/Yc4Z64jLLgcdSy1u6NqtO6Hbrqd93l3G8nuUHG0/ry/8amhtVd69nee8jTZ9tSX2mvmLl8cMjb0bfmtNl3uH9jmO8hu780T+h357EumXzlmoXh91v/yPp1IfHd7/ZXTio1c1W6j5w0M2Bu+5McXJ7Gtny+JGmRYMLnH7Nniy/F9prf8KNEfkHLDwMHHq1765vaqjuHuPYXPfScK8VVoNfv3LXKHnrcXbi3FcH9r5sHbs8WOdVdcCZw8u6f3/Uni4uu+yw/n7q591DT5pSG6gJTZcmN7aZXulX2HGnVkX49w5jPZqOaxRb8SX+/P0Wo+cZHZnX/H7n1ymDbYa+3jElfUX8j8J7k21C1+Vvjl/2S5IQHzvs8aH4/Asjq7ZGZcjzPCZ3y9gX5hIsttH1rTaPGJzyZOrBp03SFx/ffv7eK6p01rWQddYPtbJHvJCvatr5wJtdXQIGKtK7b98dP+jminYyi5VTTkT+KLkw6+TqSL70a01cq+hx7od7Km69X7K+Z83ksdvCLJcV9T2Y9EhgvcX/Yp8smdlgq8l7cmuO//i5o0ObgzU5G53va+4Le3J8XjPdebI7p4Z+leat8Xx34v6X6J79DkXcub23W4V75ly/1O0rDG4vSKx8PXqhZ2OzAzLRlftJOyOfaVmfC62oOb3Sa2azj3ZDA7f+bLlT/jym+2T13Mi4xRljdt67FRgzfdMvf6stPda823e405TcL8Vzj47qNb1jz31L37odO+5TWpGU1Cp+uvaIm5Tm+l1H9URfwyu9zmZOsfPNnVn3YqhOkE+YePC2gNujJvQpHH5M09bLIKr1xpOrHl9ps3CNuf8c6y891lONTWOXFC/csvV95uoxT6e6rPXfkj9vxouV+nFt6ejEZf2G1CRPYy71u9w4a3VRYDurw9/SbdueLXft8ejYkjbnNz/YsiKquuXKls7ptsOtclq9Suu4rEOLVolnLsV681a+vOlTUedSa7T8+rqLXa7kPNWo025+22RHSe9oi0DDjDOdQ7/YPt42fK71r6h+gvGt+WOG+VFHm4zoLB+T1Z05eCtLcP3Lrq/71hsyyb8shXfWO1zynze82L1HSmXRqCsjnYOPfFQ7tKFZqGGKZ+brXTc7DWx25o2zrE/1cfkyyyTxreyvY7K1Mk8emju68y49+tKznzusQoxWTLuuVdN2g//hAdq5Fu2f1/LjEkevetDbIiywBf9Qet8hMwPuxV91T9X9YGeRf/Nhu+3PLd3XjJnlfqHsedv4n5eXl2616ZnikpjbLdv26vdm4seLUlNSNW8f9jIrsCxP7Tj5At3o5NRvRQ/er2810d+77NGYNgre6wsTc4oW3Kv9ufpO2vbiZJ8eibtjG99PfdtBcHRU/sWprfdeXHLy0UvpsD1nRY+mtmkjj/vW5la3ySuax6/ZvftGj/JRSfMmX81z2bN6q59f1LR1e+QjatQefrl/1XWw07bGtVmHzw06lO/fevLVmPazDKte5g5/feB4+uWPg5a2OvH4yYLnjm8jw/Sdnz90z8uldKscZ6xT7zZs1YlGwfIbk6y7drIUtpHtWHVA5xnvVJqP2YGznYLPfF42yK6y9efgr3byN83zVokrf1WYTM547Xyw691Lip7nx5ybcvDu5Is3Uzu9D7ps2W9zuw/XD84yMpzh+3Su+ZZux7Yb9+wteLqi36R2w5fOr/Y8v+3Rz3npERkrLyQNOzpYf9y53imt72WOqPtyJnlV3yfFh63zWvONbIwuaFx/ONS358M650V3bpg0fWiftefnk/iRwgkLU2YtODX79KwXWyd3nKSV4LViS/h1y0B5u5lDzj+62M4vIKtOy6ddzOr92gl3nk2bGvWizGTUxFsZvaQDPu1qkhMba7nc+vXopr4ludo9dWc/+Kj41GT/momX0g8fWrvrU9U2Q/lq7wsLvow4r93tpXuL2YlDvgSmJg93tzsUnPJhxdOftR4HFp1Jb9a/T/HizanUoUHrthffVffpO3r9kSkLHbb1mlu3u6ms9OGTmxHXTN78GOk7rXijY5djF7csPx06fdqgOxe3Lhth1u3U04cvb609ue9Zn5v35p9xnJU8s2XUlkVLDbN9d/ezHTjg8Wqfk6EbXq7Q6mM/X93a/3tW+Ey7jCLHz82iWnUYenZjixXpR9v7PTt69JhT/+ct187tusLY80ZmoaG+xrz2ZT93H3j/SrbTvE3zrZFznE59+NrVRVTVvk1uv7Xj+rRv0njNm0k7yzNP3X7XZ5Dmaf9tJfv3PJrar3mq09yLA3qcXKHm2lWte9OXe5qtHTQ47HL/vbrMBssBA0+OetYzWLrz6dm3T4edfagzf+SLqtVDnkx3S84KPnnlYe6aMfNM6Rt3Hj7t/9DOaJZTSP8XFzbufV9Z+eTT7Z66mamt7L6V+OW5rZs08dKeuM+HvlGzI+aOtF+U23TKBZ/sON3bL3VmL008fvpu1Ti/pR9umz49Pv9hlx3d7QoOTciM6DB7bM2dANn50tMG39p/NjLIdfj+5PTLrzVLO9kETXrl1V+3+S+1rRZmQ8NOD3lwbHHLeL3g2nk/+83/NGJKeTNbvZiNrzx3l7pnXTzw3fhMyRYjwckIw+42B5ms8Ulror+1zWoeP7Xv6we75pQ2Nz1TuXL/j/AlszYIbnyY5q8tDVw/QW9m87annvrdWrK+6t4YRZFZ1JAvH9b3ilr641XrhRk9d5bFnskOnr5S7nYka9Glubo298Ofdfm1WG/LsYIOMsu8caOmzXf7ZXJ//e2YlMsFH91PjTzaJI3KP/4+bnJwt25B1sn57XT6nzZJ+li529Rp6Zl9z0Lvn3CMGK5t0Lp1kmnLZo/nzPz1eN8sgY/hheFzO/dUW5r16esEP2FE57NaK1H/9c/yKECgTj/Ay+pH8Hqns6M6NHPvKdR4N+jO4t7M94M3Zz+NinNqphUbMlyvecXkia9Pjk9vR4WdC/r9BOL/7/wpeO/5H/h/9d2HT6kroS3QEQgF+gLl9RfvF6+O10ZAqbcDdABYALoCBOrT+FYCK7hjPzx1mfEy43vGm1QfWz5F+fPb8wL4y/h5/Nv8TH4OwW3+ff5dfjq/j6CvwI77UNQg/lt+X749vz/fAb4HAPrxHfnOfBe+K8Qzgj+KP5rvwU/Uaqo1jj+eP5HfjT+ZP5UfBJ8Q/gx+CiCCP4svAb9x4EtR0fyF/Di+lnoi+CyHkEv5GG4lfzV/LXw28Dfxt/J3wGc3fPbB5wB8KOooP41/gn+Kf4Z/jn+Bfwm40oE3Az7Z8MngPg/4D/mP+U/4Rfxn/Bf8l/zX/Dd8hi+H/HzifybfX8n3d/L9i3yrCez5GgA+YAFfV6AnaCaYT65GgpbwaSUwA5/2gI6AzoBugDU8LF0vgbWgt8BGYCvoJ0gx7iXQUi81fmv8xvid8Wvjf9fu//n7z9//F/7uUM94z3kveCW8l7xXvNe8Ut4b3lveOx7DK+O958l55bwPvI+8T7wK3mfeF14lr4r3lVfN+8ar4X3n/eD95NUSSabgUepqIKvuGqtR/3s//+5vM28rbztvJ283by9vP+8A7xDvCO8Y7zjvJO807yz5XORd5l3lXeNl8G7wsnk3ebd5d3j3ePd5D3gPeY95T3hFvNvGd4y38LbxdvB28fbw9vFSeQd5h3lHeWm8E7xTvDO8c7zzvAu8S7wrvHTedV4mL4uXw7vFy+Xd5eXx1AbxKB5AHaAB0ARoAfgAAaARQBvQGKAD0AU0AQgBeoCmAH1AM4ABwBDQHNACYAQwBrQEmABMAa0ArQFtAGaAtoB2gPYAc0AHQEdAJ4AFoDOgC6AroBugO8AS0ANgBegJ6AWwBvQG2ABsAX0AfQF2gH4Ae0B/gANgAGAgwBEwCDAY4ARwBogALoAhAFfAUMAwwHDACIAbYCRgFMAdMBowBuAB8ASMBXgBvAHjAD6A8YAJgIkAX8AkwGTAFIAfYCrAHxAACAQEAaYBaEAwIAQwHRAKmAEIA4QDIgAzAZGAWQAxQAKIAswGzAHMBcwDzAdEA2IACwALAXiAXhxgESAekABIBCwGLAEkAaSApQAZIBmQAlgGWA5YAVgJWAVYDVgDWAtYB1gP2ADYCNgE2AzYAtgK2AbYDtgB2AnYBdgN2APYC9gH2A9IBRwAHAQcAhwGHAEcBRwDpAGOA04ATgJOAU4DzgDOAs4BzgMuAC4CLgEuA64ArgLSAdcA1wEZgEzADUAWIBuQA7gJuAW4DcgF3AHcBdwD5AHuA/IBDwAFgIeAR4DHgELAE8BTQBGgGPAM8BzwAlACeAl4BXgNKAW8AbwFvAMwgDLAe4AcUA74APgI+ASoAHwGfAFUAqoAXwHVgG+AGsB3wA/AT0At4BegDqAAUIN5lBqAB1AHaAA0AVoAPkAAaATQBjQG6AB0AU0AQoAeoClAH9AMYAAwBDQHtAAYAYwBLQEmAFNAK0BrQBuAGaBOoVBYwbU9wBzQAdAR0AlgAegM6ALoCugG6A6wBPTgwvaEay+ANaA3wAZgC+gD6AuwA/TjePvD1QEwADAQ4AgYBBgMcAI4A0QAF8AQLsz/1//cxq8ANZ2i8GV5hYKiznHzkuPfT1mqvwpAkzYXmlCnGt1pe05txJ22nnTwLLOIyPBpkX4zzPz9wsLCxWZTA80iJWFmwWFmzqM8zGaEBwRa6upqm3NxKGaWtb+otyRCib2D1SM2kKt+xEFy1YgohusJWiPiHLkaEPpFvcURHnAtCOpG+AuCTCMukGsr7tqSXMcE+9MYrzLP7iJYNahpUDkt+7gpaSUUr21jNW2K6g1jYipLG3IMvvQwAI8id3gPt5rcnK68Uuk8UnkxzdTB21GNBEJe1ZW9lAwAOQAVXdUD5BQSV8D41mD9f/vbAXLTgKLMmlGU6V94K/9KbP7QRpAIw6t3/vHPUhw4RwzXC714bIZ6s/lu+GdGUVMsA/zEfujoT7FlR96+v0fsCKW2jJwV6Q/3pAxQFkoLrq5/4nO0jAwMDQfG/NYUKRsmQo38E9/g3wj/+fsf+1thDfMu4BIgD1ABEEDfMAP0B4gBhwGXAAWAcoCGDch2gCXAEbCoD+gmgIkAV0C/Pmz7RkGf5wHKHSBuwBVAKmADYDHQl8I1GhAGmAIYBugPMAM0AdT2h7kOUAC4DjgK2AJYDIgATAW4AwYAugA2QJypgHMAR1uQ/wALQEtAE8APyGs54CngLuA64AxgD2AdYDEgChAE2ABlOApIBxQAKgBNYBy0A9gCnAHugEkAGg8KB2wA7AGcAGQCCgCvAFUAHTsIC+gP8ASEARIA2wCHARcAOYBXgC8AQT/gB1gC+gKcAV6AMMBiwCrALkAaIB3AAKoAGvZQXkAXQH/ASMAUQChgEWAFYA8gDXAdkA94BagC6EAdGgHuDmDbD38HAc8px99QwLN3kaYN9dCaa98CqNNzgFTAK1uW1g/CWgDcuTjw3Go8gxfPrsZz6fFMejwbGs/vxfOF8dxiPLce48dz6HdQ7JnFeBY9nmuMZ8Li2cR4fvcuiv3dBvzNhnYUe+6vGcWeP+9Isb/ngGnSkJdowDJAcy4fDf8an6D02uVTejUfKD2/E2qclKaod1fU9PRP1ruVf8q5AmPCg2EsbAFdWD8PSkSNADhRniDaplDeVDA1B1yhVDg1iwqkBlER8AkFqj/lR4nhGk6FAV83wu0JtEhqGvCJVTRncM0C7kjgjfhTCCfiCgDqH30GAUVMQk2lJHCHsSj93IEeDrEFwlUMbTIFqC7UGGoU5fZfyrUZhBgDORTBtxkIbR8S2gNCzIQ0A4HHH76n/EW9YL5nQJwYD/KJqckNShwM+QqEsGLwj4T81fuNhPRnkDj/vsb+uuR/VcKhJGWshTASgwdFkxTFkLaExIh/TYVPqmdtedD0pCWVPmpj41O9lvO/jr7xoKn0PEXVtHnVNu6qdWfb+flNTzQB/w0Dpqz9g/vv+8UYkjcxKYOYc4VDypFcvVn+Y0625P+MF2P9V/X/z2P57+fjn7fVv4vtr8cf9sVIKor03EDS3mwcofBhc1Dfo35P9V+HNINcuZJ+L/oH3Jb/lsOBGviX+cdyToMws0gtzeXi+jOVrfe/4w6HT/34+Guu4UD9syT4M+8fS/5Pc8iW8K/ax5+0YiCkOZUKodhxP4uL5+/8lWX5d+FRPkyFGq7vm/8uhDMZGX6Q93pZ+u/CjCVSMvIf87sT7hmkfmb9QW7/u7D/auT+2e+fj7J/lW63v4n7r0bBfz3vDv8i539Fx79ISCWM88XWwjmQpTeUEqx7Ktf/8S+Mi0n596/lxR9nm39V9yOBMvsP4ZV+LmRGw3y5kJ4VytXRIFI7bPt7wiiJaBCGrUt2dv/noTxhBsO0/ithWFmK8x/bL5ErgEgoZ4hjLtcD6jmVtft7WVFPCSX8GLJh7v+od0yDb6zX31tvBBlxv+dK2XJuJN1ZwDmN+neSmtWIgsA1jesrf9XO4yDd0D/wWv4Nnc3P34XAtm0oX/6OT0S4sDeFkZpGPYr+t6G8uBYJgnr9p2H+2Gv/Pm6cfST/gNOFtOy0Bi35d5z/p6TTX7fLP5NK/7W8/lel0V/rwH/sFX+lE/99v6wPXd8n/7qf/c75T3j+ST/8PcRf96ffef6uL/0xf3/dj37n+j/bhxrW0X+l//yTPP7P9Z3Gamz/SWcvLt8N2HWt0u1o/+VnxWsTvYQk6iA1wKtmh+7FW95P7zXdKKbMjj1eP1XtD/z4NW4yTy8NIArzDw8IdA8PDhMHRgJ9OMnfSNJTraleUBpnuBtBAjoH/s7rEjrLJTIwEK8egWIvv1AJuR/S4H5QKLEAUpRTeKRoTrDYPTLcP3DWLApqZxaZM3C+CoRUAijUjdk/TchqY+6+FdwrTZXrGtynwL2Au1/W4H55g/sVDe5XNrhf1eB+dYN7NZ66hqYWX9BIu7GObhOhXlP9ZgaGzVsYGbc0MW3Vuo1Z23btzTt07GTRuUvXbt0te1j17GXd28a2T1+7fvb9HQYMdBw02MlZ5DLEdeiw4SPcRo5yHz3Gw3Osl/c4n/ETJvpOmjzFb6p/QGDQNDo4ZHrojLDwiJmRs8SSqNlz5s6bHx2zYCEVKQkTB88INAuMjAyPNKMoXW2K8hwxysODpaCT8hg6ckgDJ+U8ym3Q0JENKRQ1xtbKureu9qAwM7+IiNBgfz9xcHiYGe03y2yGX0CgmR/QxeLAGRFiM3G4WWi4X4CZmA40czJTph8aPDXSL3KuWTD0jcjIQH9x6FxLbffQQL9ZgWb+4WFiP38xCdEg9k6zzGZJIiLCI8En0G+GWRAUYEZ4ZCDEAbczCI9lw/xZ62p3NxtUnw0JxO3mMXSEGXYxs6DI8BmQRPAsM79ZswJnTA2daxYgiQwOm2YWBlFFBbJcwWHB4mC/0OB5JHpt8gAiOCwAsxQIIc2mSqbho4e54ZLIhnm1NBsqNgPWGeGzxFDW6YEQOxYnMnCWJFRsFh5k5u8XGoqJQU1hnrr7h8+ICA4NDDCz6OEfGtnZLEgS5k/qlOTTrz5TYbPEkRJ/MRQe/omnc2iom18wW3Ysdy8sNz4aCQwLl0yjzWZF+PkHkuqCgeIX+luFNayvnn+oL1XZA9nGG+PJ1reYhkyHh/kHWv7z+lDmzQrTwJgwf/UJBHD+vfqivyTMbypk8/cs0IF+EWxuka/Pvyjj7OAGARuUEsPZ/m24WeKAfxHOBsNFSKD0UcGRYolfaH0DYUsSRuTr/bfxTw4PCwTp1AMqCi5mYiyiKv6edr+XOzwiMIy0dTi4AwKjgv0b8HJ1FDgnAsYN9BismYajE3n6/IFnBnS7YDEdGQgjEXrB9D/y/329cIHwuQ2w67JN/sdBHxk4UxI4CxPCnjKGG+RQEJDiM4Kh70Knw/bG7i4Jk8zCCpzt979xyEMZrOz+tgyBYdBq4WEzAsPEwI28ff+W1y9ymgQZZ6niJeMpCISYGAdsBM5NqmxhFCje2B5MUW7B/pHhs8KDxGZewaSUTl27qupjBCv0kE8buC0tLan+yqeZYX7AIAmbHhY+O2wApMsFEWEztdXWdmfZ+pmxw/X/939mf/pYqD5/9vvzx5U8cv37T8JffH7niGvw+Xe7tJSfhuEb/mw57x9+lGHN/l31/P/g789tSv9P9wC1+s8//futB6jVf3j/8FPfA/67n39XfvwYwKehq6Hfvyvp739/5P935fxzuf9IUVPDXhAbtyg+IXHxkiTpUllyyrLlK1auWr1m7br1GzZu2rxl67btO3bu2r1n7779qQcOHjp85OixtOMnTp46febsufMXLl66fOVq+rXrGZk3srJzbt66nXvn7r28+/kPCh4+elz45GlR8bPnL0pevnpd+ubtO6bsvbz8w8dPFZ+/VFZ9rf5W8/3Hz9pfdYr/tkL/9wr7P1Lo/2+X//92+v/t+v93C6q/9/9/Rf27uvabMaMfrnYpKgD+upm5wZ8Z3syFP8rNrUdAQI+5ROdwd6OoQW5kjQ3rHbK8pkaGR6nuR8GqAm89AiPESuIgyTTJLDFFDZOEkjiGgU6J10ERkcG4lnbzi/Sn4eoSODVSwuk2w/zCyC2kg/FjvBgnxoXxYBwQbi7GgeExLIahPPzEksgAPxKHS2QwufOkJZGzOJp3YEBYIOfwlLB3buFhhOAh4a5+YgyL4ZAf+ZAH/akhgUrbgDcsWcJne4iJAon0sbMCI0dNDQFdeWi9ZjkI0gG/EX6zxIP8cfXlHh4hiSA01s1GQ7lBjH7TAgeHzxlEjfUQjbHuZek8YgTJEyQNOYCMQH4gW5g7Uj9QZCg5VADUA1QH1ApUDtQRVBXUGFYc99eW6kB1ghmtM9WF6kp1o7pTllQPyorqSfWirKnelA1lS/Wh+lJ2VD/KnhpIOVKDqMGUE7EBuVBDQMoPpYZRw6kRlBs1khpFuVOjqTGUB+VJjaW8KG9qHOVDjacmUL7UJGoyebblTwVQgVQQNY1Y/kOo6VQoNYM=
*/