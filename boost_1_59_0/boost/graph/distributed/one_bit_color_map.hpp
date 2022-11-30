// Copyright (C) 2006-2010 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Jeremiah Willcock
//           Andrew Lumsdaine

// Distributed version of the one-bit color map
#ifndef BOOST_DISTRIBUTED_ONE_BIT_COLOR_MAP_HPP
#define BOOST_DISTRIBUTED_ONE_BIT_COLOR_MAP_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/graph/one_bit_color_map.hpp>
#include <boost/property_map/parallel/distributed_property_map.hpp>
#include <boost/property_map/parallel/local_property_map.hpp>

namespace boost {

template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
class one_bit_color_map<local_property_map<ProcessGroup,GlobalMap,StorageMap> >
  : public parallel::distributed_property_map<ProcessGroup, GlobalMap,
                                              one_bit_color_map<StorageMap> >
{
  typedef one_bit_color_map<StorageMap> local_map;

  typedef parallel::distributed_property_map<ProcessGroup, GlobalMap, 
                                             local_map >
    inherited;

  typedef local_property_map<ProcessGroup, GlobalMap, StorageMap>
    index_map_type;

public:
  one_bit_color_map(std::size_t inital_size, 
                    const index_map_type& index = index_map_type())
    : inherited(index.process_group(),  index.global(),
                local_map(inital_size, index.base())) { }

  inherited&       base()       { return *this; }
  const inherited& base() const { return *this; }
};

template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
inline one_bit_color_type
get(one_bit_color_map<local_property_map<ProcessGroup,GlobalMap,StorageMap> >
      const& pm,
    typename property_traits<GlobalMap>::key_type key)
{
  return get(pm.base(), key);
}

template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
inline void
put(one_bit_color_map<local_property_map<ProcessGroup,GlobalMap,StorageMap> >
      const& pm, 
    typename property_traits<GlobalMap>::key_type key,
    one_bit_color_type value)
{
  put(pm.base(), key, value);
}

template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
class one_bit_color_map<parallel::distributed_property_map<
                          ProcessGroup, GlobalMap, StorageMap> > 
  : public parallel::distributed_property_map<
             ProcessGroup, GlobalMap, one_bit_color_map<StorageMap> >
{
  typedef one_bit_color_map<StorageMap> local_map;

  typedef parallel::distributed_property_map<ProcessGroup,GlobalMap,local_map>
    inherited;

  typedef parallel::distributed_property_map<ProcessGroup, GlobalMap,  
                                             StorageMap>
    index_map_type;

public:
  one_bit_color_map(std::size_t inital_size, 
                    const index_map_type& index = index_map_type())
    : inherited(index.process_group(),  index.global(),
                local_map(inital_size, index.base())) { }

  inherited&       base()       { return *this; }
  const inherited& base() const { return *this; }
};

template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
inline one_bit_color_type
get(one_bit_color_map<
      parallel::distributed_property_map<
        ProcessGroup, GlobalMap, one_bit_color_map<StorageMap> > > const& pm,
    typename property_traits<GlobalMap>::key_type key)
{
  return get(pm.base(), key);
}

template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
inline void
put(one_bit_color_map<
      parallel::distributed_property_map<
        ProcessGroup, GlobalMap, one_bit_color_map<StorageMap> > > const& pm, 
    typename property_traits<GlobalMap>::key_type key,
    one_bit_color_type value)
{
  put(pm.base(), key, value);
}

} // end namespace boost

#endif // BOOST_DISTRIBUTED_ONE_BIT_COLOR_MAP_HPP

/* one_bit_color_map.hpp
bYU98W8zaNZ/2R/goEoD7nXcuVyU6T8BpsOSkpeOUKCBF2C2wZVVo02Xl5dvjuX11WSMm1aP74P7MlRl2HR1jek0U14b1XtzQqwH5S0Nhau2eUWaQatOhzRLc+UR72spxOWlZGadJv4PYsF88W4/r/HQGcmt87lm2LYLKoZz4pMw5Ylm2LIJxnZPcuZIPtcIi2zpZpOUlmPKhlhdvWFzIeqo2Rv/Zf3k1nDpoFChUoU3m6R4XQJx2wdM++xm0Z8e5FVxzQfMe/PLOhpCMQuF6ATV0dNxQhaLrz3xIiduhQ3yzZVefNkyZ0Q6ZDmZm2dCKJKT7y+AQbjZ+KQvbKgrebEGIE/zsCDxQ+ateFPUerDq9rTu4g7jnnOMKSGVoIgwj+4NWpHZ0TOztgCI1GSRu0LY3woRC7H4NQLoV6y+RzRDBij0+HjxYK3kepoxouC0EDdiCtj7sX1PBg8v98+HTuDmXRttH098jnQGvlviaXHKOxcjnTQXENMD+LXAlCm3n9OaxY5XkS3dD+zj4DHcjrdLQaps3axwmG/qtqGQVHubiJ4U065jbLdwHozNAAkKy5fHZIjlyCPBayjDTjQZenLiBXfMG+cMoNC1yJAlL88qf34T0U/SNw1j3BbFxSgtAntODV80nO8HEqvKU2odqrk5MfIOhERUcBvy6zFUmo2VHG7FVf3IFX5L42rGEc3WrOw1aPShkG9IVnwrLdl0U1Ev0YJm+Z54YBhMBLlARHCbflGQGdMw8URlMzeRHonrCHN9/QlIF3q8dcC7APUrHJ8yhpx2bDnDPUhuOYaHlFBwYt0DGQP09O1RIAxqWHSwJpsatJETjJeAsdWs6SR0bsf7DQQnZrHJg5biOTloEygVtssOewKOgvimRS2e/OyVZZLLEpf8TAusioS0e7O2f0eNOCo1VgIO++2nhRocbLo9Tcj9rUDIXbzwvrgorBuYGNGy60tbFAkSZckk+HZK76+re7IkuGZkyuT5Hp7u7//OTqZ9XZvHjeqEtWAX7DVgkeOY+hPGwkve3zYhgq1tDQKjP4zBkuYSzTg8huexN/0SpKgJOhHPmLdviyrtaMJWnbjnGdNhw5LEW2u8tq5Qwe3ywob3PX8OTUFEiKYU/UUTgzYDyVgyx0odyCpiquBB8g137y8R3To80JuozuvNPMyTUcQN3VLuXd9QAFffrSLitBPpwchmi1Qlwgisr9YMkapHVTB+KhYOOzQXcPuqAVVJy5e1nsSReBqcbwMydGeZiFrmB+WLDgHAbP239V7deb5eOfJqqAYFx3lO0Dec7BPQnwb4WIxQ/dJo2jTzWY6bM7rGAHKn8ukplgO6NSO7AxmVXX0sJb+hlrMFxXuxht8oGzZs/m02Fr6fAV+1RF5WcGl69Udaj7gGXVacZHCJbYfzuXfCvrr0MIqZHuLeCqlFr4xYcwkldJw9d6HO3aPuxx0BBZwHkVlzbVO0ZLMsTAk0UTE9uahPZbLD8yaBPDjW981dzW6Y6Jmh8QigZ4wAHcrZ4nGlDH7TdG9PCJSHEnztp+ZJPvQhu5llDRkfqPOccMdmssq4K2xuZNIvHajC/N5nCm9q+Be7IdqhW80G/o69ND1EJBumRC0P5p6xVyv9qzM+G7uUGX0CNAC30zoB3GPwNSrUSBtDaBzEBwUaN6nRo5enpwp9jUgRV9kAQudV0TJOXNI0pBooPHmRNuIu1Da3ugnhXo6SgYv1Uaof9DKDOY/0hZqOWtmX2ASyL17C7sCweVxMd1syBVcRrZ4woW9mSfOMCrZHyyaacJdN5YkJS6peUDlb4Nfw0lcZQh9sJlAdaa6SdsFebGitSypLdh6WDFTMQwGhX0CifEmvknzRe1ifIqLHEPWNXvRR9J0Xyrssivdu+kxLGIlYUlcIX18u/+Cm+NAw0JGqFaoUSKdlJfvHW3k5kvx0d3wLXTfdhtM3tgzegUu5jJvPvwOZdgHovbDSwEvuhcD8wYdU1oOMMoFI3u1+f8+LEJdKfo7vWw1U94oYhIPA9O/UkOhvNPaBSbpY1ilVPHyfUWrP9qPBQgIPPPJ0W0KBO0m0zbF+7A1Hx1RNHrXhmTDhg1i45lU9J0jd2pnDSQvuWJj5vaPY0IsBnqkFOi6WSWDMbb/fewSrPWl5XOUlaXFX//L7zhgaN+2xR8uAA+F+pnOrO6RwvbnFFlxNkJQzB42TeNo9SKdPfsyzJwxA2F7oeaUbiP3+gcomllDXfwI6ib/xhTD++vCeAHnrR0NzuVUiXSz6KY7JrV1MrwGtUuZeL3UiD56HrBIVtGRI1YZffDNW4m5NWp0lw+sf43MgESOViBgRZg0jGpTCgggECcqDnpjy0/+lCnhBZUL055l4qfmEufAU8kTyXYy6VmQX7dBGashvHZz0NL/dNw8gCLxR8DkofEZ/Y0lqmk4KTNi+hN+ighqJpv6voMblFbwGMXVPE3f/U/jk5PRH5ep2892ORNLZXvedzuvQ9I5Hrl20khH6oAAG1E57/eZsmfWwpN5OW0+JB0WxjC4LJ5unks2jsA1jNyxgM+nSe9/Kmkmu44eJcDB8u/sVn6IGOKRhmzsm+E7zQkQH9F4H3/Urk2lvmmpvWtKNyQNRGoEFDOsayqj54v5eEA8/B5SEpFJ3gCWXx+8Ys9L4w88R345iwVyx4Gq3E5FQvArQi/8di+uBaguaUXU1THTzfLEXxRNxgj6SPUQReeCiKu6/pXdR3lFrWlPdPlXFY8Ugi7pyjVhZQnKwRlGqDNnIizfw8MRIUHtKRGagpgZwMlPsai8HGw1EUGWFIyC4p1kQZhrj7wjNGB28ENebIu2OC/093Q9ZBYB61wUE8nYQRha9gOTgNCkiO0TaoMjO0Dw1p6Jno882HF0TXWc8+R/Cmd8DcKDbeoGlvh+7/bmn/j5Qq2KQi2z6mOFOx3WuujTeSDysuUOx6FHHNcnKE96Mp7bsnBP76a+bNpMerV2JCE8oscJWgg7xSpoTKryYTBE30ezBCD3MxQFXlHS/WNNyYyNM43KHooa0pZEJJCEumbCLoLzH+wLyJ7qukrGir6DiQMlOsVY2GlGbs1EIHYoj6m6KpFNQnCAJnrbNQQdu7hc27EQf9ESi5JlMTj71qQX6//5xp2me5K6b2UL13nxj2cBej7BhrvnVY2meggNKYsbNN7j3hdkO8H8dOd9CzVKMzN+9Az9q2gIxZAdrGkgnbV9UjDLJvP9AuSPnmKiq6V8L+SpJAzs+MhWvSs2Ae9xOzX5CfgWemgxeNoTu9oJIgDpvfdKNvxkNDK+q1viyPrpmv9J9qVY2n4q5ee37QCVLR032S5RPg9LAfRyzq2pQb3YoxDS13P1HdoDhBCyKSsVwKgY4ZP7v3+SGBVdkmexP6eTcS2l37d21lIzFO2MPBp13ccqkZSVQQkWUME3aPsjrtubbg5v51rzlUbTrDfzUEOOkcfNWRcomItp0UfXMfi12UDpdatpUEqIzoSON0mTjvHbgQ6EyfKUM0uMp5FGzAdfjaUW7i6m1T6lyycqJkGmakegdQTrdpMg0Jfa4KFrizOzveRqhSRmHG+Eh9LY/OPtyYZVbYgV2sR6kK88x/hls8rkkjHNCIF6iVWeCe0pdS7HV61SFcYUpxqdeSamItaW/O4MhTMj6TFIhk2smWcGlf2dPE+HKe8iYql8oa2yjmMKtMdd9XEzSuzYT24LCduEbX+fyxE76O0DORjnXva8j1Ji348oUb6PIUTU4rNejHOQ4/YjFrcdtVGPhYkk49oSAKoYd7nkW92PYvpRi4pFUQ/ZySx6RhDNMB8S3ZhCl7660tAGURoozKbnGshgDn40M6xLkQa8Gq1xGO3SFM1HXvfGRnu2/EsQbwRaHHJ/uE9d3N3FBkhfX3H3G9uQumrLkOcvNV4SmqK9FzeIcErOVrl9haV1ffPrrdCEnvQSxGdTomPwcoXvgLDRubyQTPGXOTpEWgH+dpIN2elGmE+1RsqUaHrLWqGLKNuODcjqWDLBWcdRFqPnlDecMX/21bxLSt7qfYNsQauWkhiQfOqMTXgPiYM7LPR4Bu2QwuyU/9Y+1kty/AQPfX5Fy+aky4caa//6bmWVzv+cfjSVM/bzsO/DG+fb46vpmeJPNI5/Hmlfhs8PNJGsUu5tabfdcXp6xaC/0W+98Ba26QqukTNyNllqwqQ+hY2EACc6pCriI8TSWrN2PTFQNbUACSZ2MuAK4xte6UGO5XNwk3o6RN3H77lvf6Fq19yP8xIw9uLFN5Kv/7vRTWcG60MYod+X4OgoFS06MpdyUlrnRtAYEpD2SNx+ej2ky45TkTj7IzoOR3+XczYM9PM1QH54nLh5ByJaFjxpNZGfV8dks7JjpDRZgy9wtGthMjbRYI3LClBUQmXFN1qg7qvz+8uyjeS/XeEKbDGRD5D/9GgvRGRSIJ2KNciPJKOmRHZ6jKzwOBExHpATE3A2xXbdsTgOTdqddd92axavEyezJjs0TFPHTbp0opvB/FBCZx3WPBnHRjYAeOXWMyuSwkp7Obh5vr1lmngqCHEGo7SPMRerWeYEIAGhrEuvVgVrrDYHfKjyTK5hRZDvQLWxWlx87eFO95XOimOBL/YeIK1RO8K/hX/w11mF3RM0YvmnidvkvVm3B9urXbXfEBbH8LJOASWVT9V4Cf7AueXle26pEBc7PoC7F26GJBNvrJUbe4ufcjIHLCml55V07qXxyQxY0yRzYi4jSmrtFtlEW6W4A4MBtdIMmlN+wejbb7M0Qc6mU38sNjb0oZ2m9yjD1ncfU5Mvsl5u93cJUWGVEsxQghtrhgIHql/Zck03ysmb1xpWMfJwhHqYMYQncGubKhgcpN/7q4HHVtYl0fRjFnLEkrAsIte8owiwbiTX56vJ5hMogvbZ6ZUw5KkMOJf6/kA9N09ejvN/xxd+Yg1aW3FVJt5AgCN3qdxqXiaYDEeldbIR2r0IfJGeAqcJtXNlUNc7HoYHuhIyZCoP9RIdP6ZbIXv4xv4a1X56x3fQIrF5wHjYb2JYvwsU1959znFLnn7bgLbDaIFfB8duuWV/x267dkFuYBa5bMdfKldvOwm18X7vf2ATS1hJ5JHdpPdhJejsCxVvl07OLx6YLAd426VVNuPnJQIXpUYY5MIvMApXeEc37HPK35kHXwsyvRv5iLe8Ibg4n4zS+J1O9mrZIhzUifNnEVgM6z4wWA1tpq+GD3tOex2eeQzradVYb+Nc7JSc0u8PVl8zZexuBnTdXX4lbm/eNTvdTN1f1g+0VL7dmJtBklDQ5FpnelUHX7BGJJjJbokGrzzuvRJz52tPZBW9L7vjN5q7PPYpugnjl/56TFNq/KXmNZDOaCr9q19ESGQaPuiMPB3V1fTRMMaQ1Ur3wDdOkxQY6tuqpq0pBMgY7OOywRvYNMx6dgbo8SCPvUA8r32xYF/5SpoP9Yj8yH4pPfgjpqKuOf2FpC1eSR2bPGYibcMBxNFWZUFJS3thJLMGXMYfPT/klkU7o1d/vaGvXp/kR3r8yh8L/OU9VDbbX+Of4yLHptNq4dD5xkmODd96dMO5nysqNrANLhw/PR9bFp2sjpFbn2TqQu7DT26v97B6k6x4urODMV5DugkFbV/5kbBEZH9057z41Lfnx/SOUfBdVSukIwt1EhKav/h1+TnDcwNnhrQhuQyE7yHdxnnk8ooTjtUZWv3OJsT2fzyu2iApjpvvaSSAAuhDjOmUlyoPU+T9DVvM4WI8feMlSW+gAFdZdDnQa+Fz2+XRM3vgdDjKvATRyyFx2JLsqLn0gKToPEm6iWi7/wWUfibcg3GxKH6e1Qhd5jJ6oCfy3hT2CPeXvULpNtKkgB7L+UgDe/7ByiexwbrWZtvF1uA2wRflopp5APYZUmJMkEts+uPPa+hkiBt33oG34ZIZoH98Pmp9M0fZhhJFQwvZ45S32zSW51iJivN1FbegxrAQ2RgNvoC/oJGXFYSd0SmL/mRYkrL+QKfZqyPBA0wsaHwoFyYEZwVqlcN8tSVYe+qmmn4YX8bkuruRtUJdPuzRzbI5Na+uLEJ+cIDVzlPE+g3DMIjpB9beVycUfeVuAf+8+soDz2JcM7awL13hk5niE7sUb6eAtOh9FXIhGPew/3pWC+h6sMAKCNJccyHG2pIXzzR8bEhVfTAznMv54RS00DcxWHH4yHE93sOEWYr/IL4oKuyuWXCgBEWZP0fGfbejcot7WaTDuLE3I5rwjCEYZEK3lGeaysknx+QTxdATbBVZdAJc5AbCYhKeUwecl4PLIZXKpuF5xyYbXKStuYWzbXxkCj8aWobqcek6IXAAfdf30kXpA4C2fTLxlGMR+jFRoSM1buJR1r7I0zrZYpxrvVUB1tiia4q21bFv8Y1OkYKa9AE5Ss7ytgNzQesQgP1djdjyhLVwiSoGqE62mBJw1vJXMIcyrnNSQNEIvlpofHlyPpSdV7d2ZH/ddo4jxXppAivJ1xyaOQPSauqiKDv19IR451qM14uPqX+WO/gxDP276JZ6Tf0crIoio6o4PrtoXl3rLJDUOWbEChczCtgP9x/TlVYbEdFRcCGmRtV7nxJ2aJy70AiFLaVOpdaleJkcSZ9k8IiL22bfx3svDauIeEQwG3dynph4P9W4+5eaRc40NiDFvoqZnsk3USEnRtWRskMj9IWguPoQ8Lar00wM+lpqsovHcwrpfGWhmwEdqAfG7XlBUj9jC54F406uDxOsW0ryezkXHje8PlSHKlf1aH+vmRhF1BLsfWLoOUSwt1grOJWTUGHAHMEAvnXcGvRUuETr6X//hQb5VGZbqBWxx/lUfS3Wj+2q5UtgZWYPpK5jeER9Qtb5FYxp5w94rMHxaFGhc9cgqLycru46kkGfkt2x3HKgk9NoPFzyKRk+BESqGh0yPD1/70soRBVufUArPx3ebw7N7u6UQ0x7kD4cZOPANBmGnCKvgvykaCgjXkyNC/ONvnoBWNtJj7zZzJoYE0koX3R7da0nJz71DPk4h+cq+JUavr4jT81A+H0b6gVDccE9Ij++525vE0jkOmKuKR4hgjGW+nV1y+SJs8DfjaXSZ+V52jCgOLZ6KyLNffaW2jzKbKwC5oJe75kxInXTyOGospU+Dk0YuuKQd0tZOSdvEjeyrnYA7tukJGNVM2/LpYl45R9XYmoy8rFmEUJKStaULhYAn9HCDg76BB7uiOffMJos5AMpNlTNiQ4vlR3SoMpjPN2kgYqGPBYoYETIQ8FvBKBLEukwdvE+kV9gK415JAkoj/DJl2YT0u8PJuWG6Tfu++U35D+Idq9b9cLiTMkRnXER+x0xMshRmDeB02QgjazmcsjSzGoNYhNE16S6Df6FWm6xlqnjRG/5KW4WbLdct1pFqHxDeH2UK3y9uzxaHPvMBUvmgsDH5SHr+qKFW8P/W7MgqP4Sa7ZuS/K6tjvjF88gLCyRa7sjULMdszg+KpxuiaQvYUJ8X0UiDMkf0YSjLk2DWmiaApIbpzSAthgWKG62sU2HdbkInYA+S+Ullj6V2F51Nh8scwmuGvnh5xcdnyAICmnzzBkzgxgyKCtnqIwJF6+YSNYXXzEa4k2mFpx+nn9vzsGWEujgQ+1MD98eXQ58i4t8rnvIeKCp/4hoe
*/