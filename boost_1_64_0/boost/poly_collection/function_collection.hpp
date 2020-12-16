/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_FUNCTION_COLLECTION_HPP
#define BOOST_POLY_COLLECTION_FUNCTION_COLLECTION_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/poly_collection/function_collection_fwd.hpp>
#include <boost/poly_collection/detail/function_model.hpp>
#include <boost/poly_collection/detail/poly_collection.hpp>
#include <utility>

namespace boost{

namespace poly_collection{

template<typename Signature,typename Allocator>
class function_collection:
 public common_impl::poly_collection<
   detail::function_model<Signature>,Allocator>
{
  using base_type=common_impl::poly_collection<
    detail::function_model<Signature>,Allocator>;

  base_type&       base()noexcept{return *this;}
  const base_type& base()const noexcept{return *this;}

public:
  using base_type::base_type;

  function_collection()=default;
  function_collection(const function_collection& x)=default;
  function_collection(function_collection&& x)=default;
  function_collection& operator=(const function_collection& x)=default;
  function_collection& operator=(function_collection&& x)=default;

  template<typename S,typename A> 
  friend bool operator==(
    const function_collection<S,A>&,const function_collection<S,A>&);
};

template<typename Signature,typename Allocator>
bool operator==(
  const function_collection<Signature,Allocator>& x,
  const function_collection<Signature,Allocator>& y)
{
  return x.base()==y.base();
}

template<typename Signature,typename Allocator>
bool operator!=(
  const function_collection<Signature,Allocator>& x,
  const function_collection<Signature,Allocator>& y)
{
 return !(x==y);
}

template<typename Signature,typename Allocator>
void swap(
  function_collection<Signature,Allocator>& x,
  function_collection<Signature,Allocator>& y)
{
  x.swap(y);
}

} /* namespace  */

using poly_collection::function_collection;

} /* namespace boost */

#endif

/* function_collection.hpp
2ja29dNIA9jgRxIl1B/G57ChhmN9bOMoos5IHYMVHkSRR8100heD8CCGPGoP53hY4UcapiP47DLihRZe98GFCHKoMTF+bWNcgDYT4WdrZetBDAXUzaDcYOgdfAazmbYKXiRgmEk5RD88SMB8FPGCGykYj2YcjUH4kERHNWFE51nk9SyugT64MPAKfSjbMdQewzGwI4wc6t5JGYATUZTQVMN58CGD2tmcBwfiKMJyLO/JZxvxbFpMniPE+zHU/pE0wBCCKKA+z/gXbkSQQ81+jsMgPIijBMvLHIthhJBF9Z8Yt8GJOEwFxnywwosMqg8w7sQAvEiiifLfBzdiKKHxFcatcCKCHGqLhAVDCCAN80E+wxACyKD6VcaKsCEIx1+4Hv9HSIpt8nL2f41rw48imq+g3COIHOps7IcLURjWEmZYEUQRjV8nzPAijZpvkL7wIA7DMNeFDX6Mof5KrosRpFH9TdIQI0ij5lvsxwiSqLVzTfiQheUq9sOHJEzfJu5wIgrD1dwTdoRRgMVBWsOLHCzX8B4BFNDwHeKFEIpouZYwI4wiGp2kLYLIjzuaz9ZxDkaRR8N3KR8YRRkt36NcIIIyWl1cA6Moo/06wowYDN9nPg0nEqj+AXGEEymY3JQpuJFEzXrmTHAjieofkoYYQRrVP+J4uBCFYYQ0gg2jyKPxetIAfoyh7sekM/zIoP4GwgAv0qj1cE+MII3aGzkeXmRRfxPlBwHkYfkJ14cPY6j3sh8eJGDeQJzhQgLVNxMHuBGD6RbSDHZEYPQRBwwjCsOtnA8Xkqi+jfPhQgRltN9OuccoCmjyk2fwYQyWjeQZ/Mii7g7iDBeSqL6Ta447hnCxTaMmwDEYQQaWTcQLPmRRexfpAh/GUHs3x8ODDBqC3BNhlNCymXxBEEU0/pRyggjKaLmHOGMUeVhCXB8eJGC+l3jCjlEUYbmPegkvMqj9GWGABymYw8QJLiRRfT/v4UQcRbT+nGsiDvMDlCe4kUD1KNeDFxnUbyENMIIMzA9yPYwgg/pfUBbgQx6WCGmAAApo3Eq+IIwyWn7JvRGG4SHCAieSqIsSFowgjuptxB8uxGB6mP0YQRr1j1Bu4UECNTH2w4MUarazH15kUfcr4oYRpFDzKPvhQwb1cdIWQeTRtIOwI4IS2h6jzCEO8+OkA5xIwpzgPeyIo4z2nRyPBMy/Zj88yKL6N4QFXoyhPsm94UYK1bvYDw+ysDxBuiKEAhqfJGwIoYzWFPdCAtVPkQ4YQRLVTxNP+DCGxmc4F6Mooz3NuYjCuJt4woFRlNHyLOUYERieYz8ciKKMlgz7EUIRjXu4PsIoo+W3pAtGUULz84SnirrANgJjlmvCiRhMLxAm2BGD8Xfshx0RlNH+e94jihLaxniPCMpo3UsYMIoSWl4kjIjC8BLHYxgRlNGSoxzDjzya9pHeyJ1FHWsjHy4jX1FGsYnt+DMg9hkWUz7R+1HyCcEF7EPfB8lLRFFA/H1cp4EyN4fzMFRifIgcml5jHokIjH/lOxeMIAPL33jWgjDKaC/zHAMp1L7OcxD4kUfzG3TLiMH8Js9a4EMOTQbijyjMVaQ1wsjCPI34ox9uRJBDzWGkEwbhQQwF1BlJf1jhRRxF1E+n3MEGP5Ioo+Fw8ht2BJGG4QjKCXrgQAgZGE18jm4Mw48EiqibwX0xiBFEMAbzkZQp9MKBIFIow/IOwoQheBFDHjVmygj64UIYGRhncn/0wYMkqo/iGnAggjJajuaaCKGhmuMxgjjKaJpFOOHHGOqOIc0Rh+mdxANupFBTQ3wL5CMysPA8wIocmv7Ma3gxBssrlA1EYSpSVuDBGBoP8hwLcdS/yvM5uJE=
*/