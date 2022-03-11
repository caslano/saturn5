// (C) Copyright 2005 Matthias Troyer
// (C) Copyright 2006 Douglas Gregor <doug.gregor -at- gmail.com>

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Matthias Troyer
//           Douglas Gregor

/** @file packed_iarchive.hpp
 *
 *  This header provides the facilities for packing Serializable data
 *  types into a buffer using @c MPI_Pack. The buffers can then be
 *  transmitted via MPI and then be unpacked either via the facilities
 *  in @c packed_oarchive.hpp or @c MPI_Unpack.
 */
#ifndef BOOST_MPI_PACKED_IARCHIVE_HPP
#define BOOST_MPI_PACKED_IARCHIVE_HPP

#include <boost/mpi/datatype.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/common_iarchive.hpp>
#include <boost/archive/basic_archive.hpp>
#include <boost/mpi/detail/packed_iprimitive.hpp>
#include <boost/mpi/detail/binary_buffer_iprimitive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/item_version_type.hpp>
#include <boost/assert.hpp>

namespace boost { namespace mpi {

#ifdef BOOST_MPI_HOMOGENEOUS
  typedef binary_buffer_iprimitive iprimitive;
#else
  typedef packed_iprimitive iprimitive;
#endif


/** @brief An archive that unpacks binary data from an MPI buffer.
 *
 *  The @c packed_oarchive class is an Archiver (as in the
 *  Boost.Serialization library) that unpacks binary data from a
 *  buffer received via MPI. It can operate on any Serializable data
 *  type and will use the @c MPI_Unpack function of the underlying MPI
 *  implementation to perform deserialization.
 */

class BOOST_MPI_DECL packed_iarchive
  : public iprimitive
  , public archive::detail::common_iarchive<packed_iarchive>
{
public:
  /**
   *  Construct a @c packed_iarchive to receive data over the given
   *  MPI communicator and with an initial buffer.
   *
   *  @param comm The communicator over which this archive will be
   *  received.
   *
   *  @param b A user-defined buffer that contains the binary
   *  representation of serialized objects.
   *
   *  @param flags Control the serialization of the data types. Refer
   *  to the Boost.Serialization documentation before changing the
   *  default flags.
   */

  packed_iarchive(MPI_Comm const & comm, buffer_type & b, unsigned int flags = boost::archive::no_header, int position = 0)
        : iprimitive(b,comm,position),
          archive::detail::common_iarchive<packed_iarchive>(flags)
        {}

  /**
   *  Construct a @c packed_iarchive to receive data over the given
   *  MPI communicator.
   *
   *  @param comm The communicator over which this archive will be
   *  received.
   *
   *  @param flags Control the serialization of the data types. Refer
   *  to the Boost.Serialization documentation before changing the
   *  default flags.
   */

  packed_iarchive
          ( MPI_Comm const & comm , std::size_t s=0,
           unsigned int flags = boost::archive::no_header)
         : iprimitive(internal_buffer_,comm)
         , archive::detail::common_iarchive<packed_iarchive>(flags)
         , internal_buffer_(s)
        {}

  // Load everything else in the usual way, forwarding on to the Base class
  template<class T>
  void load_override(T& x, mpl::false_)
  {
    archive::detail::common_iarchive<packed_iarchive>::load_override(x);
  }

  // Load it directly using the primnivites
  template<class T>
  void load_override(T& x, mpl::true_)
  {
    iprimitive::load(x);
  }

  // Load all supported datatypes directly
  template<class T>
  void load_override(T& x)
  {
    typedef typename mpl::apply1<use_array_optimization
      , BOOST_DEDUCED_TYPENAME remove_const<T>::type
    >::type use_optimized;
    load_override(x, use_optimized());
  }

  // input archives need to ignore  the optional information
  void load_override(archive::class_id_optional_type & /*t*/){}

  void load_override(archive::class_id_type & t){
    int_least16_t x=0;
    * this->This() >> x;
    t = boost::archive::class_id_type(x);
  }

  void load_override(archive::version_type & t){
    int_least8_t x=0;
    * this->This() >> x;
    t = boost::archive::version_type(x);
  }

  void load_override(archive::class_id_reference_type & t){
    load_override(static_cast<archive::class_id_type &>(t));
  }

  void load_override(archive::class_name_type & t)
  {
    std::string cn;
    cn.reserve(BOOST_SERIALIZATION_MAX_KEY_SIZE);
    * this->This() >> cn;
    std::memcpy(t, cn.data(), cn.size());
    // borland tweak
    t.t[cn.size()] = '\0';
  }

private:
  /// An internal buffer to be used when the user does not supply his
  /// own buffer.
  buffer_type internal_buffer_;
};

} } // end namespace boost::mpi

BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::mpi::packed_iarchive)
BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(boost::mpi::packed_iarchive)

#endif // BOOST_MPI_PACKED_IARCHIVE_HPP

/* packed_iarchive.hpp
1Bx0e2W4csHkWNc2XN5jtyboX0Xg4h1w+Pe8onqrvFVOBFZsA1thJv6TyR/05+z+eX5CZVv41wl6FzNpq6JXHVdVNb1KmB51S/5vx4BSlcaWiz/iHZCq1tdq9oycmfT5fvJIlr4OzslOJTM5X79QB1gmNlQVujk5WVWdrZmOBgYrUxgH6J89mlSZQzJWUrazkxxUYi4tC4pYWxxEuRf+0Enq6ck3Ted9Vk8xBr2mBow9LrViCp+zCfLaXjzbljA8DTux+owumDsu7g66zLG/AKJ7PaDhJyZVKzf0JWs+nuLQCNGjR3JyswxPXaq7+Slmbkm+S0oz3zYpxbkc2ZICbxuD+wSUzEY+Czn1iP+rIU+2pJ+3h6vD3OnA7RYsjov/GEtNOj3TdB6UIVazrpE23OrbdPEXhXViBivfUOtuOdQiRGrOQpe9zl5s1edtZLGS0/6pplekzH0kQglxxvF6i89kMLyEDN/ODOPuYj6vjUgeM6EmNQbm88k1wEczm6eqQfjY8o/Pyuz3O6F9lSMnv6v6ONQCxksjCua1nF6L9c4PxiKB1U3nDYye4PE2asvBkflLr8WrBbcg90r0lfYY3wd3/i0D3bcDiMNETm9uD5OP7cDVg1uEQoWncKkKObE8LzCPRVdZkgPq+qMzTZfXUM/fqvNelEdW6ujj2JR7YsgV96w4cufoJzDJCRXiVkmRH5877O5MoZuVBYLL4tfBT3DTM9HLYmLKJrM2qbSmb+jT9x7XpWti2yleJu5PI7VCAK4x+Ydtn3TxNVgeeAO4QQ/wwxYFlRRnHqvtN0TG1a3ohI6c/047P+c2KnxYRbwFO3Mavva4X28uAICIX+EBUCYoSAq27HV4AlWDJSiBWoCFYAmh7XunALAiNV3+VifaR6C6WAK2D0UeQiKQPqg6ihbEYjq4/6X7ngs3Vlxj6IdV7C9PujMWxSdTjF3gtMxmD48WLpNpf1eMD32Ttwo/6kcP0Df8xBtmgEv5EZUESHym9FFeJdDq/bERRMLX7MCeKb/rj+J+FfWo22HIl43h03nLy4Gws42FMp+I0BvziA460+nfvCPzzWZ5AsfGtwWZroWXLxd3mNrvRZfMjg/IJdwulpLteHvR9QWevDdbi1k7ZQKwR9OEOSPqqG6+/c23adNoqvbT7+V5mUwqC33btrAbsLj8ufhZjZyqZ/bpOVIZ7O81AcjuGIfo102+dL41fZY4aw3YaymseIHVDJZvgnJ6hG55U89vNugICjhPgcsBFfpvIhPFFJhUAlCvHTDTAOSujxbxOc/uzG/H+NmcQDT3ctRc1NWN97mzTvbO1TV2nbXqFO10q0uQpu6bD42XgeN2qUFK/uDyZksbc8dFXGRNgizLcbLRZMkVeeUWfb8bjBUk/BOVW4VLPi68GtcMLf8ZtiQcSWr0DBvrHoY1+1vkmzYRYx/eyR6Lv8W95t99yHf7mH/HUPr4Nqol+uo6Grm4ecMguT2XxHn1lDwh+mZ+lAcnDbJG66GUO2GnLBK8DzNCp7uPC5lFpy/ifXMa55TFe3OVnVwRfAU8vabDYNDXM+A4bOUBBj1nSTwPCnurgj2zwoyhAOMVmMqDJIwdamwnpq/+g+3//JQnirfmcKsR5IPwO1TNbHcc3GQ8JOmwsXe7P53hK9Gj5v1SXeOjkmiigj/2IMvhIGnE8CFJMeKIRBHYkL2TxmBAQ6ORHtN1qslag+Raf4Jug6+8gNDV8bWmiit+uyPYSnbATNYdXO9E0aP727nb8FEczCGgT7ISVpAPkwuCie+DvZ5TRndgflDY440HlAOm9rrrcgwuW3JRy1ZVrJsNe0tE7YG8CHBzwGJDDkcCGG4hKxUwHdwTEBm+keefWeOpKDy1Hx2viECCt+fBgVsQXT/6exRtBSmByLfBcE2i1xIanWuUscEitvQK3gPi56W6+eBfkomJrN8jKy5mlYkZvLCLYOffI9EYxX5EMkoOcDBVAwOCaLtKggFWx1S8gO9BQQQCiV8ujmE7d9s/J7tVdo7v1iTHjnx6WcmFG/2o4QK1YXXdXtf1L9hdsALo12kgc8FW05Ok3zaY6xlm+3xxlskFGLwERKc92tAj8j7jt2loBZ3TYzrtUy5WHlaOIsE35K43/AyiVsjseA7meVZilpjZt+j+aeO9klYFr/LbEPkp2yvw0/uIWxYtnAl4mJb2sp/BiHn36WYZ8pL3T9dnL52OXkdZYE7d0xWRsyTOnWjARhye1z6zWGLlhxvDpe+iTyjpNhgOJwYYZH/WVaTtshdI3ZdiviMWMubpz1fBL3K9VMJx4uHhnONLX2a8xn8JlMBzKUD/k9F4njrk0I6fuCe8JKjP+8rusq37s063mGlJ0+4hh7ZVsdsKuaJVAyJ24sumFjCbEqZOugyipCefDB0TFUoTdLUWJ1Y9dPBp3Q0Uk1r/xnhpLrReKWOx8ZES6fc8G+6kus6wHvMlnyqZqaiZXeRoVNmPLHd9NoBZmqnC7eizKUDMb2pkD0UIU3vPSCx+JS2i/cu7+3I8p4GqP699hcR8WtqvG/5R4kUCD9n7g4W4qy8XysIqA6r1kKXPUNf3poK+Lti6dY5LgIihH5VjN7QExz3E7pjiTI22fajuZTrE/LJ60o28FRdvkJw3N712XtHu/YGSIjtzyWPJfub2OMsx7m45XgE7EKxsfbfXDYBrHO759ftb+N/1QohTIkxSDkUsZ71fnQALqQa+K1PmG7EBy5fTaMig2UVesu+Vh7oFy88c73w7TyTxF9ITmcgrv+wStKsekP+i+ErN2ZqO8hLnyf22l0RgGMYN+V8U8PZXCTCMfQlYTXaC1glqkUoMED2rzDD5eBoC0V88raPyu2LnjdGWxAyxkoJz5uwSDmBDMHxPRIokhn3R8PH9o/1sIzcCS/DXYsvKl3JgG6VhRFWABh/WBDnBug/HA1awF/KTj6tv/v09uPpu82axf/sJ18Skb+AvZYUM9makohxyqW+l89ctYaTAwlVOGkwinh2aYfyTFrLa2WeRXGT9EvCO36q8zQrN16UeDG3mR8rX95VfRdV3BOWFP9Vp1sudHpp1JoTNOcsOBxavyq8W24IijU24SkkxGaSsJvRRKzS2HdoVGwjr1+QeeDa/n0J28DZLKaTqEnc+GPCCa7BOWYJw2IL9v4767WI+fS9L+Ik/+1fqnkoI6+H3G6OvzCCxOweijXM43zDeduFTm7PaUhdcKrMAzgzrGv5pJ9lBmZuN0PFYAJFRRZrZde2fBvJs9YvPq9aWi4lcBXsFg3AioJ/EO1bdR1OAEi68P99fcD+WrcMiakUHlJdmxLxR9vLmjJDddgqcdQ4PQj5rOOKxeVV/412VYobu2olEShFq2op2l//F5MKV/8vdWNGmCWpVy+owH8fdP2mheiE1ZA/HVc38vjxnh+D+zvCFNCYAOeD0lblnOwI7LZc3pOGBqLrsu0Hbu2o18ASmsdqMvbXtixFKhmo34lSxm8XTO6xUAt/mmEFTTXri+xAd+gFvawRejbO72XzbbpWTpbKCiFOWPBeKPx9IMMimew0kpuTuhBTVT4VNWMr63u2nEfGn8v+kUo3+Cx47FpMyMAFErduuUMQ/eQ556r0J0obtbY3XulSz34jqwzvAj8x60Hx5du7KqQc9iKwHO0B+0ZNAO5Us4b4GIc16tiPvSq7FxU8HGWGMaQMk+vfHz/wIr/mu2e43H/hoD+rUtfpbQ1Ar+8ckEeM8hhT/ds10YPepimUlAX7LiqGuKM3Y6GDGPdaccaygPkyhcs/kgve2ie9iFS9Zcb7diNZ/P3z7Yi1LUU1CW3BWFQ9VHMb6lrZASkS2mFi+aqFj8jWQerdgUP0at7u61hGeHsZIC3u/nuuG9kddT4Trxen39zirIaT6FbkhsR0Z/iZ4U4z2nXsrnouiNF8u1UNqpm5eXnuelirmBLkPwEzZUwrD4/Am90DKhAG1W00HpT6MLuYWYX/UOL+h+LCAvP1hyZK3qMEKTVpsE2qXD/4l6xLVJME3PfiMwq1mwnwlaZSzxukmaQB1VCz6iFkyb5QMeLNfannkJNAozSj4x5RIS7AL4g3c3pdfVS/t8U9DxDAPNNi5xgzFL7g4/xzEZRasj1LH/PcvMauf2kaFrIy89Zde4EguW4eMpqxk/Nh2obWhnpYpx5oFlh+/jn87fryWuGCqdMiTcPD/deqejxx3VVmO9LV1pTXy5zSaSBtet+yNKdfIUOQCOjJ3TPtPM6O60Yxf4hIOzy3UQl/C7aGfFTG24sHGaofu9ABGfP4zuzkDRa2xFSM4M2P9oI1bt7FAY6UFLUQziF3w1wDaW+Qrofw6B4jDK++jA2hqBXL3ELT6tnLtf5wVKYn/eMmtgoSdzihaN/H2aZlaTTpivuNru8NoUCjz11a5xsW4FeNxhfpjG6t2pSez+63SuTmB7/0+Vux/N4vEkSwJHslqUyhX/FPfryyKt+LFOv/6VN0wMVWDOEH+9K0skXER5MYG/ti4BUxWMjb98Ft5Uy1CvmIAG93FwA93uK0/kJpKV84o9GrY0vT9UCoX6i9qomDxgt4wJ+bDYhM4h90WFVUVXd+vQXze2vw5qJBjCrGgWj5BvFUtarqMWQffNRpWDHvVt98Bx89YKM5xl/5U6gUOwmadWRPP2WxBv/arussv2lqX3dBKWom/r+/WloxEClWbm5HPoHJYrFsuf4rTflWV4R5EPjw92XSIkX1DO1/Kgwx834MLACZck9Y/GCuMraxb3jeFH2/2cuWYKu2qq2eLhzIUOgSi/H7P3ewpsd8kkCvTvkLBRUX3o7xyKWzZoieanodA1jpw9jEowuRn9SOM3TRqVNPG8mfldYo8pez7wpug6Q5jzh+vd5pmJMqtEuq69g41z21udqFfz7kOhfl4WCX8ekapPqmNUpsXBOvS+GHNRlkRzbKvA5D53h7IkoL67t77tuTnYe/YwXrYfkiSz54XRK7BiMWoU5b6XjOTglSeH7kLXZzM/NG9k53MjCBbOYo50j7bFzZurDYTTr3wmdHPOHdZLWGPH7Gy10bj+sdW3l+Lf/jIufOH12stdDY/9JFc6+cj8RUZdcgK1rcRQaHDJ2TUcBdUH2HZgJfJ/J9GuOZCv6Y+2yFR7msOGP2Q3NHnVSYO6fhBkKeSRP0DAkfRGmw7hOTZhWhTE+ydLzRgiXiJdrLphn0NBQi7+kCDEtaoPmmqw6LMoLzpD6B7lElJ7OYgAPfjtbDYl9+YvOxD+PrXL/3nD3YKfTnLgePlhK3P63t2DvWJqtrpMHRXKRf+7HOp/QJ12Vnb0EGdH9R6Zs6ULvKMtn0/ajraLgnvNY1gFTuGPoJIlu96EMbOsE+yY6Ox+YitqXYIkUoCyX35R59WHo3NgkSsgW8my30pJcKP1/wvAT0e0KHP+tXFlh6S7y8I+1WtFn3ydh4Q7puwjMDnBkY3dnXGYC0I3PpVkMpjZoHhtkv+O+63lgfAy5exwFv1samxi/zA1XPJ+CDoBSvry+Wx8XFAvu9NPm238pSdP8k2ru7kaYWOAOo9/juFLe5Zsa4lj7vKBwcq9Qgw/266RuGpMIh9IOBGsPrANX/tFndTG+SkvhCGqbQ6Gub5Zo5PxWXyFigSx2/iHEQ5srYLh4/Ft1tYfTmMuQR5P9xTBibemwWEvTG653DNhnUo/hpt2xT1DaLB2mKcMvn7Cf+Iz8QR/4i7KMWseQ3IxKMXkMKjevnhe5Slqc3eC8sBdIm+oIP++cM+GpooDdKEXp1Ogc4uR9D1W8e08lJH7jqDzQXrQi7qv0dnsi+Wcdw6RvnzQrJzK5wnbtdK09FL877Aw918LrO0F/b0VypH7jh7az89xC9qrPrR7Bi6SjW/7Q9cRG+d/dhUGFrIXaJecqu081vDitbSPBH/6IDMk0cdDnYhxNpAPWhJoPTHHv57unxjuI3KePllONaZPycTypId/mdaH3Sl0fwcKh1vgKdWfPU9aC1EugyGug/45uYmW2dbtN6jJsa6eni1kalB7blsn9HTmvX0Ums+a3HYjmJu930qyL/RSde8XfywJVDKrxZFr4J62okx3pRrb05oy5xJn7iFnkgEmjfU7YnN6BH7HB0pSXv5QQq3Kos/+oD5+ZMP+p+t/BYxWj4w2dxr5Q69CkajvPo43TYNdOphLhF0sWvYUvWac7/PCrhne7lJj/S64XiSy5dMH/0aMvIE15jZEDb14eNXV8UWvGoc7d9VCaxTmonrN1tmU6yyDH8o5YkqSXfHDl9vIC3dOfdw0qffTOt3l3XPUzy25Jm6zykfexw0uDxizvn/WOhyZE4CAABgQVBdrvEL8PAYayf+zvXpkNF0Jjn0Im7jkphELkOBUurq52JZIU0Kp5WyV29h7k65hmDZcYm7PJyXqnJb1w5wg+EQdJV4G+STOwldOOl2NjsHYkhJfKTQ7/Nty/k1iBYpaFT/RHXk9rdFYXQL7uNBmLGYodcfSYJUBa1STeywFOXfk5nJtOKSnArbkczGUloKZxTHP2NuG6Je/XhvbIQt9ls6DignKMv02OtpdHp7zNx+o4Qe1gQLm4vYjQmSY4vbSLF3tL+MRMAVNS4mkYYbqMoKgJxZYrQ4eTge1+Cwl1PRkCKoQ36/lBshkro7qYvH2X9kWsxLX4mx/QCv5RT2O9N8KEF8i+ZPZSXQQCLZ1QL3Sw+b7BL1A/In1qz7XQgibXdL2O9DBdXW5DlATXtCcV61h4sHe5SfDFV2kyNfWFvmsCOlMi1Mg/FIXOzdnlEq2KAto8jbcNtXsgwlzCujLDKuLybZ8EBH5RPhybzmRBMS+8m8khYJH1QGFcTR4us71lCiDQ228J0o3VxCh7tPkfIwWo218h2n7Wo7+Nm+7Wpn33OGsyR7xbntSh3Te9QbYHE3avxMaPYy3vAQOPFlzpjDaIsBzSIoq7kvNLgR8eCGmrPU9Biex0LaFOeLz2dRqOqc8iE88lg06dajmWKQsK1i1Q+hDYCNZFH/zCj8ywRW4rh53Ck77VWWrWprZty1sQ5+533S5B+C3uBi8tPBIOKJma91lBY6bZhOJfZ2VytTpEy8fWH52A/DI0yMS3DW7HFvX2bbeAvCGreGqzcgbWaK1A32w8HOUWQfmrcjYo68IMchdW8MZE7P12JH5LQRBka++Np9rCK5oFxq6ZIvgKkWwetK8Je73GO233zK74Vv2ISP94f35FgFmwtoNkuWrX4cfMCde5wXf7VslMuC/EHqC2CTzqfIRDStiCksWuLhDsxebQNcYn9bGN4rtrsyvcoqvsvBHzfJZSjGcASHZjQNF43k4PoBcM28CF8wZWcIhzncOyOpp/CltJ06f/z1x3XZUQj2KpGBCttBi0YR5u7u8ylwOlXjbOcPJSzZCBxGABNDFrFhkEdUDLKRqOgcyd5Ynq8fWwiiCAfAXZamNTouYn9aUHKGYrBaFtitcVnvhUZj/LpedFSzJ8JltwdLuBnFR+6dknVy6dngLDkIvjFkvOvfwPjyt5wVfJNlPcf7HA5p981PNkv4Xf1DdMM/0btc7r3uPXmgsFK1G0BxNFOSCL9Echo7kjFqqIZp4ebWr3j6wuBUxzIMFfJhEXvikUig9t6flA7j0ehqgMLMfOIWsc3l+ktHtImhafYiOI8BX9sDvLPz7HoYFchhTU2Pzypxic0vmZy3wjk9BJJMb0NHsTAd4tH1XWbE1oJKa80kp4XYsJqvlnnC6WtP7tAZ68+axyvquWYTpdtZmM5yDzWeW6yGYVDldksJwFy5+vPqLKTnVsRWbUri3hxo9jKUXCd6lZsP1tlCRakeftSx8xS7MhNXvyorkzqz43M6pkfXZQ6N9QuR9lTTfZmOSSUMDEShpwYybinS87aO6x9+5ppf5yAnPsOcNeuqDrrmjdtsN0Q+zo1LbjcEtnl2UxDOwt08eOvaWxjHURDVLdDvMTTbxiX37FtEMfXH2OJw0iMvFZURhIuptNpnmlSPaLeeQ/LXGZmWrWNXf+Rc9FlL9F8I1YxaM69A9dZDmXoXwMI9uuc2h4xZ34/x2EX7km23OY05CeMpjegf/HWYS4yFEZMaNbKf6R5e81lEm7NouRvT405u9Fi0Cui09Aq2RkkbTOXLQuH8JIjxKy7frdZ/rda3072+XClGGOQPaFK9rInBn0xYividfCM9Z3VsKL2wa8RdZadSnIhI97FR/GvgfehHKdaz9tpIGZ3LcBJSZw2DnDuJGH7JmGZb6pITF4N7FfHI5DLlmGhFYrSKLwVxx7Rij1ahTQumavdSaYA83GmD4xvFA92il43z3F8iF+gZNskfWTIxEH97GFHAGKganpC4M09ROaMYfc6l7fdkiqwZ3lKE+MsRhoaNiFLxZkyzkr/RjTa/i7PxkMll1iLcy29nyUY+Cr1urip+t3BRbrcnsbA3di4953xp3vBHm/ZjTm41hDKPboabvefXn/M8BULxbdTgJg+nKAvZiYEisGMUmb2A5zaOZszWoIZ29rjKwiWmMn7d8hiSOnFZ9Iwoh8mDuI0p/+C+bzbO++PN02K/FTyuFulOOSxO1H/FCSeb+XraCWOfH85Jje1f0zrdAx5YiolQUSYmyI6W7M/dnDxhC11YYXVXyGk2jcp5tGiPu1kCUo4XjRgpJKz+WimRVP+1glV02YUkVAkB3D4OjHhSDK/u4Uq3DZHsdsawGbWainZVCWZUy7CO//WoNz+d0GOry1iSD7xOsr+rb1Cmy/0EF1n/SY7C1EyKS3OCHmGKPiL4Ly3BT2y1U0Tls+8MtA7oafc5sJkLqGcLwu79PV86ACQK7oJBjwuCjmY28549tQIH1amJs/bDj7xDhPOdEo6z9juOdKwTMKbnWtp0Xlnw7eQDiafEjX4kHOfs+xx51woTZe9LC3MIQPAMrB/NhIEXea61a32uRWtdn0D7rtFrmTKg8eKgyabtiwVSAT8lI/tHgd/cfjJnwMdqHvKIVaBSDRekOy0Lanjv5EaUA8VFNFWAoesLu58vkt3p+x3OGiBixofbUGO/LQDNPgoN17k27oQmX4c9vEiVGiv1WCR2ujp9Z++sNh5Wjohf4Mj0u3chrccbk0nCKYVvJGvUOj960RRNUJNDaESaR+nAmsdew+xAunUY86IBS1t+RqbFlqIKEYP3IbpFOLAY46QpSQqKoAg=
*/