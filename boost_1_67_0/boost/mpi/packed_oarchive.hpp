// (C) Copyright 2005 Matthias Troyer
// (C) Copyright 2006 Douglas Gregor <doug.gregor -at- gmail.com>

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Matthias Troyer
//           Douglas Gregor

/** @file packed_oarchive.hpp
 *
 *  This header provides the facilities for unpacking Serializable
 *  data types from a buffer using @c MPI_Unpack. The buffers are
 *  typically received via MPI and have been packed either by via the
 *  facilities in @c packed_iarchive.hpp or @c MPI_Pack.
 */
#ifndef BOOST_MPI_PACKED_OARCHIVE_HPP
#define BOOST_MPI_PACKED_OARCHIVE_HPP

#include <boost/mpi/datatype.hpp>
#include <boost/archive/basic_archive.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/common_oarchive.hpp>
#include <boost/mpi/detail/packed_oprimitive.hpp>
#include <boost/mpi/detail/binary_buffer_oprimitive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/item_version_type.hpp>

namespace boost { namespace mpi {

#ifdef BOOST_MPI_HOMOGENEOUS
  typedef binary_buffer_oprimitive oprimitive;
#else
  typedef packed_oprimitive oprimitive;
#endif

/** @brief An archive that packs binary data into an MPI buffer.
 *
 *  The @c packed_iarchive class is an Archiver (as in the
 *  Boost.Serialization library) that packs binary data into a buffer
 *  for transmission via MPI. It can operate on any Serializable data
 *  type and will use the @c MPI_Pack function of the underlying MPI
 *  implementation to perform serialization.
 */

class BOOST_MPI_DECL packed_oarchive
  : public oprimitive
  , public archive::detail::common_oarchive<packed_oarchive>
{
public:
  /**
   *  Construct a @c packed_oarchive for transmission over the given
   *  MPI communicator and with an initial buffer.
   *
   *  @param comm The communicator over which this archive will be
   *  sent.
   *
   *  @param b A user-defined buffer that will be filled with the
   *  binary representation of serialized objects.
   *
   *  @param flags Control the serialization of the data types. Refer
   *  to the Boost.Serialization documentation before changing the
   *  default flags.
   *
   *  @param position Set the offset into buffer @p b at which
   *  deserialization will begin.
   */
  packed_oarchive( MPI_Comm const & comm, buffer_type & b, unsigned int flags = boost::archive::no_header)
         : oprimitive(b,comm),
           archive::detail::common_oarchive<packed_oarchive>(flags)
        {}

  /**
   *  Construct a @c packed_oarchive for transmission over the given
   *  MPI communicator.
   *
   *  @param comm The communicator over which this archive will be
   *  sent.
   *
   *  @param s The size of the buffer to be received.
   *
   *  @param flags Control the serialization of the data types. Refer
   *  to the Boost.Serialization documentation before changing the
   *  default flags.
   */
  packed_oarchive ( MPI_Comm const & comm, unsigned int flags =  boost::archive::no_header)
         : oprimitive(internal_buffer_,comm),
           archive::detail::common_oarchive<packed_oarchive>(flags)
        {}

  // Save everything else in the usual way, forwarding on to the Base class
  template<class T>
  void save_override(T const& x, mpl::false_)
  {
    archive::detail::common_oarchive<packed_oarchive>::save_override(x);
  }

  // Save it directly using the primitives
  template<class T>
  void save_override(T const& x, mpl::true_)
  {
    oprimitive::save(x);
  }

  // Save all supported datatypes directly
  template<class T>
  void save_override(T const& x)
  {
    typedef typename mpl::apply1<use_array_optimization,T>::type use_optimized;
    save_override(x, use_optimized());
  }

  // output archives need to ignore  the optional information
  void save_override(const archive::class_id_optional_type & ){}

  // explicitly convert to char * to avoid compile ambiguities
  void save_override(const archive::class_name_type & t){
      const std::string s(t);
      * this->This() << s;
  }

  void save_override(const archive::class_id_type & t){
    const boost::int_least16_t x = t;
    * this->This() << x;
  }

  void save_override(const archive::version_type & t){
    const boost::int_least8_t x = t;
    * this->This() << x;
  }
private:
  /// An internal buffer to be used when the user does not supply his
  /// own buffer.
  buffer_type internal_buffer_;
};

} } // end namespace boost::mpi

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::mpi::packed_oarchive)
BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(boost::mpi::packed_oarchive)



#endif // BOOST_MPI_PACKED_OARCHIVE_HPP

/* packed_oarchive.hpp
f0W+9RuLTNpfAVfZJFHIcRy4j2UliclJHIjJ4Q5hM4dqSNnSxicp0NYkTdJwy2EfyI8JjGGNadMCgzfLL0s2hSte0n9+cHkzHJMYQ0yijcJ2CXw/+jlpMAl3jDWJPkmQ1unzdkg3hg92scjLEloSaZIuJbQcKqOh0VJc07xb8PbQ+s5WqLYz/QiaUan83CMo+7yo2+hl69LOsL02p6ahcfXBdn29M/cL13ae84TI/q3b7ISoGyH9nMcze8Nq6R3ab5K3YZde5vSKlIBYvH68P6SVWA1lpHEKMoMVywi6aDbhX/3QPW7erXtUvKYY/qxt/hOfYsVa/ZRUEtrMaZHFbk+EzbRc/CtNprhm7ect2l6u0RvVOHeRQOEmmoHTaJayjLOhbMXnx3To2Ctig063W6rOpjXdWSjTVn1lCQ5u0Pzk6VnzJ6aEoIQvM1auno2H5Mpf8Ngv08mzV4Qx5zM1ioNQiwBocsaacaJm7W361advlqk6MXSChnhgcGDJz2EG5fMPlnqcdGUtUa3pjjWoMJZgd4sdnzMK704CmH+UI1xvWFkBK4djAkPnvrKamoxb5rdYQ0Fmh6UFNNFotFu2TDL7JIHjwve5QPT7Mc35fddA7x9kdDW+QQXudi9sLB51+q1mev6dyvyu1umrZfsmNmuOk3NQX4IV99g/nx1G3lWN+EQO1X+tbV/xsN+fZ9y7dW9v1R1sSprOdLQZkB8hjX/o7w19LBP/mK6VjrPhaxBTWHbqu8S/Ged5lN6AUIlq22oo9v3+3bnLlFTlJhNf8KteWdnJjWLbJo9NPHlpD4tIk4PGaLHC1UJgmMm3zJbPnpKTbCrh96yGnzbpR9nYWorFv40FDuCmWknfLkCQW0rXWGSntSd0Xmya7ALpqzW/qczx94rzaSnQ+4A/fcc0OtE2U3i1pZ4X9XxQkddjqqx6ZNK0vtRaehct9UKDmPTBHIfnPWlInHTClcIfbgrNSa10xBspdJpAOdT5/5HUSXvBjX4WimCB/kFLWVxxZgt+Tyf+PxHILRLX3KWarBefe5HY0KYi77FK3e575JiSHmkvZTvRbGAIfWll6KcSqRKBxo+32FAa0e177bf79l93JPejir4tHV4CCUrPbxc3Qy0mbg4nRpx1IBrD6+F7vwR/ycqvRC+aqIfeRDZ9Cfjz2HSUn0Ui3KnN4VLC3p/R12LuCyGcwt4OzlatXkaVRPpir2fqN0G3m9OgKANRfWb2ly2O+68e6EAs+66BHPmfzK++P1bI/d27JMOB6BdaocTvxKA/DXKPO71n+PMDJer9QyFtvt6i9Z6hiUjiol3Blzze1M8LcNUDO0Wkk+reuxTd1ADulw0xSPgsO98L9wTY4McxWXfhapMk9ap/KLZ6b2wwe+OLBdWbxcGzRapTyl49XCdGXC/LwzVwD0kndgRlvMBnNs/qPvWgD/sXYCd0oedWix5gm8M5TIvd6fM1KOyiTtawRvCBX/oxU8ora4kJEvgjUJ9TY5umvjD+mE9FEoHN1OUPOH7MrWR8RfZm87190wDko4R+sAP3E9eaMJaF+EyaV/CteLAY9qpv0aMPkr2BycWH8bfU/nw+b6zhYy57aoHHzwQFjiee+jBmic+iaZ0lwGarGBjuCRX3C6J5EGI95jLW8AL8EYnY12cjrAtXiFhKnmBwj8lD5ZYn/HnjYZkQBZLn4k5gzHFdMHTiEfEAQFLPHZqoFtCDeEFpV/D6zGwKU9+YGYd1zObZPYwDfPqP1oRUew7gJ5selB+PEXOcrqVYVhB+YFRLHOZgswFbWVlWlJ/aFx4lc1pLr2v6W9ffwq6NfvS0UtNDNkIcBNsTXzuIVlseheleceo/C0ho1FYEi1tAaSEqiH7rL589Zz5tiA02q8g8tJOsmoYSJ0ExQgytrxkbJfFXFUMTcSXIV+1DRz8CdfstdSGMxlCrUVxxY+4f631vTfs/R3KmnuiAvAL7sSOySpLMwD7+fz2UNp/HS6Him4YaKsdR3PjjNG/Pi3+3OpWRGy5fLlJhnhS4kqH5vZSyfEafDhv3ow66tprMRnEHvgET6MnAaj6XQnSPld2eFMm6paf5ecUG2nxXTKKe/nNPXM9Oo8Rz//WTn9T97ftqbnCG1xJE8dps8ilFr+R61Cku2uk9P854bs55U6+17SecEPu9rbrIniW//rtZJF5rgzalVU39S0Z8k3qxeiPzWuR/KcTgUnK77vJl79OLpxge5CCRMpFPQvrB4j/NXr1dK+tPdb/6/bRFzn/J8zhtAv46SNY9pP6TyX6YWVT+l/Ay/mwugT6Fc9fzFU9S5f62ZT+v2e0WmKCOp9JoNko5VyH0z0K+1/w/C0MF/xkRk9Uwbi1IO05e77iElW2fCrdA+4YiL1bfjM8yJywgQeOZFxtvxhfqrw4wzsuM//p7ipcTj7A97H9zqlwtelq90dj79rzuonpfSbnuonXPbCyaHwMzByb03Yp93/zPUsXmv0lSNqg8tLi1shareF54fwBgDI/+q5VVo9Mo84DCT/wZ+qDApXjJk96mD84LjefEgkodoDbJLJeF8oWYGAWvXLW70Cx9AQNSYBPsQkUb1u6+M9rVd68ymuc2iEIp2htoO2kz4NQn4bQFOa7rO3ceBCWwrcJuY86NRTpolwOGyQE9oLqemov5xlDslcpZB/KquwfeEJXX43ExKbkEtCzAvBtlPA92ndXFujlWifLRioWTVRZUh4mXnt+2pnNqiqUUILM4/r4AsVrzyMJdmZJn4cC8YfCO7IpCN3rOgdstbC6xRQeph4iX+HjMX1bjSO8iTj86C76hyfn0ZYnHqwzqYt7KtCUJ7sZvkPsd/6mFumo3mZ43y+QJL3ktf6myi8Wld726/rdLw6lAkzxuFhLWvrJ4BalSjjZzfG3sl7ziYjym2ZSoez6m3MXNfL9vlk8jAMEzUlWnt+qv7IJNXRgHMfEK3LUaVk+HMxdfcRIfF+O4RrCySGNLXTtYYhPT5+To5jdx1/bGhmimv1re1WlYhm7pXgRX7lLxAst6NguX+wFhUt/dFkh9OmU5BRisy9L/wC/bmbSQqC1bwa8xVaBqnQevTE6dmr/e0o3xWiVEm3liNw0zLOehilIqK/y1UZqGCKiLgqOhYd5NM1Mjfhl3B755zMNkmiEaoaUsS+iLsdstI0x935OMAkF/8llrfxLEhqewJf+yp/D2BP/aU92kcJD6qMd030JSph8CM0zkDcjrL/9RU1BPYZQDO3H1btqT+QMXsK+bhPSdaSvqS+xUoWeR9mxTtXFEQo/T3m24czWKSK8/9aUkwFqll5HHTGshT64K9bHpq3+uopJi+VaYhaV4xpmD0FEqWHBzi9CtuKbyLQyKOUjeI6COrqLAYwoZh9akd15k6N6M+4puA/UqqvxC9z2CLpxqLlY0E43a7ul78vxFd95edNaldD+Qndq2UaZ2Ke/KGV+MdWal6uneFMWPWkw9xOt/3stXqGNqiPTRfWF0tLK4dT/hb42pvmRbAMUcUcnm+0EDo+amDDtmbSBHxfNfd8xOnRb8Nnme9Flz4TcWLF8IYkTFca32R7sBq2L36g3z1YVn3H0kZNPzse12VVcvjlXe3LrkpxZGuQ2O6Wv5Mdb8vpt3Rx82zYV2e51Kl5qdDGLvlO43fbFrMDqUlK5AOAqswwVhuuIPWZpl/q+gjC8VlxtMEoI9m9WP2x2ymNiMmlLpxgzOFDWPOQ/u4LxZB0wxvS5QvJSBg9q5CW9+jGPgOnoeWVs5ob2jbh/H9hqlw6FXziIk02utO5Syi/qUNVIdpPKnoQP+sIBaVfjOOYzv8h7D64O+eK2SDF+1wKRtPr1dDEfG23YblTWbGcVcYMu3t/zaVrzRu7VcU5rS0ZFLUTzlTXLld3XnbDbKfJH4eSfPPJoOv0yxC7cd5Yy1s9Ht7TON+S9vqnDHSL7UZZ73fsyIyVfpjs4BmxcM9TOZNZ07tX3pXOjuKmCogvm4usseui3yqafYr2wGFqM6XdCOm+XpRj6Uma6F2y3dRksZg3gKkPxvIwpHMbdGnw7QWli7JXY1Dz9rfa4igZ1HefbbkldXZ+A173TryxfVtRYtkiNxDgW8/Nb28SpUeg+80i4BLP7hHjvp1fPukBZS8ZCkABpFBF21Eusb0zJtL5MCC88nP/TcMKsPLy/oXssr9as7r4ybHamrGrz4gy7/yOkg5uHlkDULU54qImuh4QSGGtJ3R8jf1Q4EsL0s67gZdBldfVAcLQAALP/TcGF+eBfoKrmGKI5lh20XXJPsUqnWPX4UK0RH7T5Bl5O7rGdlWMqbjX5GfSz7kjOQjv/yK9CiLDd9Z2Iisf17HKr2BOT71mgaa4kc7Dg/Mfze/wkrIQjZ9Rbx9r37bEuDNDibxb1ubQsjArOmEqEgTWGJ4TvKw1GAQ3glPqXLFuNE+LnJg/w1DF0Y+SA+pC78wHDUz88ZWN50vjxZ0aw3+OX+mmXTkC2ugN+0hGTF3SHD8sTixe6y7NwaS12nNqyMfWnHOG+OmWikNIcjWQtU/jmtVnCUxcRkHXLGbMhqM9k2d8dq1zSV0w6yzhzT16psIMzw2vP1UajGL08fQXBtWXfW3PTPDpcdbGVR3zfNiatP2P3tMaaI4Ra0KVyi7HPslvVj+KjHKS8r3mVK53iasAN8RlWjNbKs7CPaCrLlMGaGyoc2P1z4h5PUNPEYFwUvh2bVcUkL3RG6yjfdESK3WhyzEiRJ3BG+WFMmPKMrpXHeEUbYUKY9o3sG8qbW4RT7Z9UVTvxT+g+gPaEzrD2jx+yN+yMdhXMZhzxTT2n/eEP5FztGfcRKoAiY0f7Ri3pH+Ivz7z9F7H8Kuqn/B4H+v8jGH6lx8P8WvKH/E8j+J9D/DzH8Q4Fo/1Bk8oj2x/F/gxqh/q/A7Z/A58M/Qf5/MccD/zkpvSH8bfAPSbz7h4j//l/mSMoex/3DKW5Tn9GnOE16Ee6kf9X1i2EfsXL1hf1Dsv8huX/o9T9k/B/C+A9J/i9yCv2HQv9DMr/quLrZRY1prXw9e/+i1mhzG5u084kaS835apIZh9xn1e3QBxyxvsfPH9GmCfz8D/mgDWmTFD6I/YOzL9R3hNlyBc/oAQT/CvVkE5D3jB5q/u/+2/9bCB/aqf9nnsYpI9q/kvP+GcX7ZyHxP1f0/2v0f9D/GAX8+N/p/IdA/yHi/1QK/5B/Jt+/nk3Uv17yv95wyP87xPwTOoHV//+oKf9Uz/+tavL/lvd/nLT9V16r/2pJ+t+SIP9DBf8/iAr5/1b5cP23CJj/u9jg/1R8/4sk/61l4Yvpv4wf/stI/s9E0M9n9OxI7jlgs3EQNCOF0M7O0Wmj1QMQ87eDmHOzqW1vfa1MVKVA87JaJAhSVfSoDmUAfpTwHqXMue19eUmPRFc5fdkcLGDeAHf4eCn5dAunaf/q80gXwdmEzQhip4F7OyznQvg/n1UeI6yIv50c6VNB/QFLohwBAcC+N6sb+kTovgNr37zzefjG21UE1Gr6IyjI7gJ6Wled5fuyVkXlU+QfNLysPToDG7xfBWW+HZR1rh8bG7zVqAcJgv8QUtf62oEjbf2mFw+9AkCAxdSgoNcZvytSiadHJQfWiJfMXgG7EWyMyAivggzq2mr/H2splQM/AyRZfU+uwFd+lsu3A32Oz14edyNZK8dG/irDbxPZG+egAldb9WGMqsnPFc0F7nsyghJeI1mZeQHNDaeZOZxdRycj2UVOD2ISh7sHSys1QTd3sirbes89nGwB4Ljln9oSq9x6kPU0L9Yr6LoCNudbYNAocYIodFqFcrPHPwgq6CWpRiR2qjDpazXTa66100tJfKC89er4cIctAPafdZUdD2gLtNwfw8S+Etl9dnsB5VFjb79xSgaBRNuuep5Lk5diQZ1dvELuN9N+oQEYb7fZA3mCnJ0fOdv9YAP1TrvUb7ud6uBDKo48qpMgem+VUQ9jn5buj0ED0QPdO16ZFF7bjZo9b7bPBBczd1vOjxONACSjl4vHjUXnabuKV0Uzp8SLb5fpDyxlBZQuYMXF0yJcr6Avedux93FxQOqXj6KiY1iwllRl+rLnOlME/2K/u6R8KNp9hXIh7DFWI4O4p1GllJcvZIa9tMkMIc9z3saf26/alfry7a4n6ObFykkC31DO7Sr73ulrR1DBRLssbHt5dQVhP7BEYUNZglyVycrctXwkCF81luc6q1MymHJDpZt/gfBUUkSs+/iDtjmF38bgIFMHHRRnV1/ZU+ZF7a9V/kXM/WgfhnkQ51vip2UwEOHvM1Twy1OWm0FyoGNBJCBnPybODEXMn2uF8LQCdHeN4maYfBN53TftITPRAhwMSjuPOVB4STzspDv0XR6k/odfaV+vhGvlekOp3pz+jXIrsbsLOWqne6S+vvY7bqd7uE2KxJ52kbmAYabbJbDe9nId7Lr94/uARIRKgOCyyrO/f19FH9MK4VzQ6qATwEPmLPla1NUw2RU30KqWdX4btU90hfDmzgRAnVM3pSK2vytg/Jwr2z6tLSGI73iXDvAJ2/A/dNvlzZfsy9+PeXpOq3ByyYJ5i9AA/ThfOLca2hs12gqYEG31RpDDXyCPZpEI+AkAJBDS4omCn0boVHorWW8OD++Lg+VIs/zROX4jB2Xyw0ShriQoLUsdRD5m+9cPg8nD69EPIB7htwVK+3pgUCev4g9Ef3a0etmC35x74QafOn3iUHtwJUrWRK/pmwoIqvCA6WQfcgwWnONS7ZBlaTpO6lB2TkAVSS5trqKaXwT4RntXDz9kLLLfyeApdwvPkWqPV9VpxqtcqDUYlwcFcXR8KJSOz9Gkcn4O7Fkz+7EJPk34oHn7qY4s7M0cTHtNfSVeHoCKJQNZ2rV+kXhHP6fSij3AOgfLC0CNKLhKD0BN+NITgLr95SVxLZKmAV6k/gbrwHDMD2cJjXLs/RjbGHMSL40b7R0tUhIGjQKNlByivcbOr6bfGocXsj3iyD7d2vHiC+czVt35GhWDVzpmvgH5pHntEpoOP74/CEe5PKh4GEfvtiHsP6Z7d5q5PmQRK9UB/HMLUEh7xAojXIzCmqnnw9xJEzRxKL3YM+nEiT14IrzyV81+p/7W56SlkDWD51+NvlvpsXJ3t6F5uJgIpO1zPm9ykneef6iE3MJAkLChbVhBHSDEYQDtvIloHnXuoRKWUseQ3ler+JyJxLTllFDLkqPRc/8Afhtfnuzf+/HoG03l1+eD+yLG36MSjuybTt1wQ5/wpjCxyDVjJlgME21QwQSdaSK1Pf75UJuodKqO2PbZSaVuopJTXYnpvrJ3hKdMS1rVqcRLq3KgLLWu7UBck9rYCYZpj0Ug4U72f/6xA00Hf2V9NHHn50+Sxc7WFestGaU6DNuad397PzCrysRmo+IWw5fjEGxGxdipffdC8th0SUzv/I7m2LJUVakw6WFjtvVbT8kQ92EbJMkLv0eS9mgE8b9Eyge6HXUf53rNTGV1ux1VB90CU38DcpgFn30dA3ACcLUBXNAI4CRMWnxwHgBR0QVwBangb124F19X+/qkKGmyAiSboKngIN4++oHGe1eIVdGN6N8ezqagzs174osCMaaezTeZhvPc4Xpe64/+Pvc/ZLFH0upw8ctj0tX+hP3Q1PuSwkOrO64oQzo0zvCNpUxrGCNkU7ZMref7Vc5EPCNGWy3uYM3DEKV6dpqOx08N0jq6D8xF53ItX5cIj+eGqkwXJ26vo/jQdye4A1GPkB/jTZDzw+1w+fO5ov01xvU8fn6vUlb8AUWr/iqtgTYXzX0WpvPNVKxMrexPy++vNnijeF+D5MWajhXZRH8LCitnDcW9V5RTjNHe0/owysRoi5sSh82u6WpAx+soYpQVU3Wj8POs/52/8y5rXHK4Xfq3dQKWd4JMtNmVZT3egYeo8Sym9sUGWVP+uzK/W8gY+1llyCMB/Fci0vhmJFk8DF8NPSkKUqoTLNcH8ZYu9PQsXjZNj54EN51nHHozfnmivO1Ad0uRV4YCr4Omnh+w25YlyO7Yfmwt3LF7ij8EcFmt5kY/ZLLfbfmxCfsd5m1erRsyuAkq5VxCD5cjqD06d0E/xnVJbktXxF1GyjqdfFSvxJ2Epnmn9INYrId/OEyBj31nOk0DN3fd94TbZAQL+x4vwuqzc9peTfcTbd3XV5yaP59cbUiWBWYUzBdXr3EfXnnhh0mYhd5teMtc+fPY/cjd1wzQUDOus9ljPuchP6IkP220xBwXeFLMahaGBQwuoQws/g4HRH3lATk9T4yFfy5/h+3t2d167xoVeOQ+vcIt/rZklX6S7OoraROy/3c3FnKJk+v9lroTq/VMC4kse0/R5lb28hzhdR9A7YM8I8D+q83hc5vW8YJXnHCfbTyIuFYqr+v+Zdlm65eIWVviGk7z7mv0lvlAEiL7CB9AX/jB5aQZ704dTC9Tky243TjsfgR809eamQqscAGO635XAQR4nKEoAQ2zy6lB3DsD3KmTDzNXtB3kGRzyoOXr7Z2spiasWvG9ilQ+UeqbVTU95+eJBE96iTRFL+oO87U8AR+lu7NcG0931ZMRH2LGladqi9l7R94C6u6P93pBYN+bURSl0Dr3VU+m11xaPq/++IROqvsr1h5IoPk+k1gQZj4w5Njr4DnvV0D0L/Ho3OpLXI5lAR3LAOly9jZS7xybKtP1rho7Np5zrpgau48sv4BUC8jDiw41+1TTyxHG3LPwZmuWJPyTevHv9pgHazvqxDb19FRTuLxV7qRKvubpbsrdAIik3DNBiPu+/pS9P1wE1hAUC1HHsC1TJQrZrf2TbAaXMXEkr7iZbhe/tW0emuPP2Yubsrzcyv21edJ2DjSB/JKld3gdGY7kDTLwmFdqexcIQ/xMSvm+OItVJ8CoYYz3GhlvB9E/hPoaBb6Q9+RdJ5zXLKE74lYIajfKn+Jjj5Vj55Z+n6VokrVXgXjPYStUBAzbrHUZ2Ln5WLknE7Gnj9XbARTTVsa+i5jt7f65lLVNPfQvh4FzYhnFo3zFtiOluEC13XmdHEi5y3ExYxqkQbDcMao9DBRzymqw1+jlC/p+V+hBXOfpv/Wsr9T1sJvfl3fnb9h9dv1/XkDy2oKWSqP1MrY6GX698PaA19U7dcBSSJfkBoXQ8azBWr+V6AjaTODKQUmqSVFXxBu9RJs=
*/