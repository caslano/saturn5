//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_ISET_INDEX_HPP
#define BOOST_INTERPROCESS_ISET_INDEX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/intrusive/detail/minimal_pair_header.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/intrusive/detail/minimal_pair_header.hpp>         //std::pair
#include <boost/intrusive/detail/minimal_less_equal_header.hpp>   //std::less
#include <boost/container/detail/minimal_char_traits_header.hpp>  //std::char_traits
#include <boost/intrusive/set.hpp>

//!\file
//!Describes index adaptor of boost::intrusive::set container, to use it
//!as name/shared memory index

namespace boost {
namespace interprocess {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

//!Helper class to define typedefs from IndexTraits
template <class MapConfig>
struct iset_index_aux
{
   typedef typename
      MapConfig::segment_manager_base                          segment_manager_base;

   typedef typename
      segment_manager_base::void_pointer                       void_pointer;
   typedef typename bi::make_set_base_hook
      < bi::void_pointer<void_pointer>
      , bi::optimize_size<true>
      >::type                                                  derivation_hook;

   typedef typename MapConfig::template
      intrusive_value_type<derivation_hook>::type              value_type;
   typedef std::less<value_type>                               value_compare;
   typedef typename bi::make_set
      < value_type
      , bi::base_hook<derivation_hook>
      >::type                                                  index_t;
};
#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!Index type based in boost::intrusive::set.
//!Just derives from boost::intrusive::set
//!and defines the interface needed by managed memory segments*/
template <class MapConfig>
class iset_index
   //Derive class from map specialization
   :  public iset_index_aux<MapConfig>::index_t
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   typedef iset_index_aux<MapConfig>                     index_aux;
   typedef typename index_aux::index_t                   index_type;
   typedef typename MapConfig::
      intrusive_compare_key_type                         intrusive_compare_key_type;
   typedef typename MapConfig::char_type                 char_type;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   typedef typename index_type::iterator                 iterator;
   typedef typename index_type::const_iterator           const_iterator;
   typedef typename index_type::insert_commit_data       insert_commit_data;
   typedef typename index_type::value_type               value_type;

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:

   struct intrusive_key_value_less
   {
      bool operator()(const intrusive_compare_key_type &i, const value_type &b) const
      {
         std::size_t blen = b.name_length();
         return (i.m_len < blen) ||
                  (i.m_len == blen &&
                  std::char_traits<char_type>::compare
                     (i.mp_str, b.name(), i.m_len) < 0);
      }

      bool operator()(const value_type &b, const intrusive_compare_key_type &i) const
      {
         std::size_t blen = b.name_length();
         return (blen < i.m_len) ||
                  (blen == i.m_len &&
                  std::char_traits<char_type>::compare
                     (b.name(), i.mp_str, i.m_len) < 0);
      }
   };

   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:

   //!Constructor. Takes a pointer to the
   //!segment manager. Can throw
   iset_index(typename MapConfig::segment_manager_base *)
      : index_type(/*typename index_aux::value_compare()*/)
   {}

   //!This reserves memory to optimize the insertion of n
   //!elements in the index
   void reserve(typename MapConfig::segment_manager_base::size_type)
   {  /*Does nothing, map has not reserve or rehash*/  }

   //!This frees all unnecessary memory
   void shrink_to_fit()
   {  /*Does nothing, this intrusive index does not allocate memory;*/   }

   iterator find(const intrusive_compare_key_type &key)
   {  return index_type::find(key, intrusive_key_value_less());  }

   const_iterator find(const intrusive_compare_key_type &key) const
   {  return index_type::find(key, intrusive_key_value_less());  }

   std::pair<iterator, bool>insert_check
      (const intrusive_compare_key_type &key, insert_commit_data &commit_data)
   {  return index_type::insert_check(key, intrusive_key_value_less(), commit_data); }
};

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

//!Trait class to detect if an index is an intrusive
//!index.
template<class MapConfig>
struct is_intrusive_index
   <boost::interprocess::iset_index<MapConfig> >
{
   static const bool value = true;
};
#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess {
}  //namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_ISET_INDEX_HPP

/* iset_index.hpp
8qHeoiFauTSTNrVVZXYnaVQG8VrdZQL4fgoz/x2O6xYZHh9iJTafvpRnF+tIkoe+gR6lU4akbH8xiiS8uKn+Islsp5G5phHpvOov+eKN2QQSQpo3M/gsk2JWvAcifWR5C9LZpZ0hu+KCqJ5WX1L6OdacuXytg0AQSCSQMXhwixAPrAS72Q367ljZuSKi2BYrEvEDOFtsqAyDcAng2vEAsvLEvI83dM/2Z3Uu9YVfkyw6TUrbBgsZsnH66/REiB5XLlX0VrypGpCxnWAk5pe0gQGPMC2JXEfeiNCeyZfFIqqea/az+XQWSS6ZQ30ciUNDp0aG496rccx1qJoPtLed4zQ8yKngRKIQcZSpc0oS/eefk4elYFfpY5uC1pQTWf7V2ldSMqeumk4P5guvOzr8irSjC1wQTwi/322m5J6b3pNi/ojiPpfW4uuAEDKbIZmn+OxCg3LCzdfdICMS3dDV7FbU6bwKQyNJTbg63Sm7R+fkJe71vpAYbYMBRDsPsxAXbdmksDnLsJd4atj6Y+eG/bvtLreXyxhwK5grQ+1oOaEvkHIvuRB9ZR0Y2WhCFyA0D+px2Q99dPs3ce1ajM8CAmOJr3MGchSBkmmdP5Pw5q0+S6pKV6iYf0c840T3dG+hFyL8KEAkUFcwzh8As0IkEiIZPQYRwqdrBrqTamqeZwgR8rt/PZ7DbEZ/4RPAWuzSPa8jT8eePwVW99L4IDViXX/CJ0evdmtfx+I/MsJmN6QGD/JbCLYbzuGJhCBjWxKMtHWV8m8WVx4gbXcPRgaHtXxDxdPVbt2l8F29yhepSEhBexcevMrjECbs3LM0UE24ZOrZoaE7F2UnDM+KBkx21TJUy8T9dr4Z3RJNt6lnEvXqOyh60mNd8sqtdKr1+as9KGMH54saG96kpuP++VtzGmqC0s6JxGOjaqmAgTbHj/KuRyJRrfN9FgmeowG9esPzSw2B2mrxf9QXzsJXXFDF4D8yiLNa2VZFapEHWPs4sM1u6hJRXQJpFbvdjw5RUeE1WfJchrxCJc9PZLGGGrKe8YEk+FrhCPHOWzv9Cdgu5ADFDF5RqEUnWAzJZNX1p94XlTxA4Q2DGYnCWDTOzYKghyWo55KKOeitNQq8yCM3pY8uaSiw1Q/g+hxHXM4y3/g3bLgDOmJXeDvPvPdZULOrzmjnTaI1E1CwRFEiVswhcdfSceJE/edpNUb7s9NPnIv+nhVR0F36zNMy+3t0R5vqbVIYUM7lp+mmGucCmtxh4T5zIVXRT78avTC1aYedcdj7eZNMSP6vMFJfRPEco/AZCHWLbI6emsyhazg9bYQkgYyNx7WzW+6McqV8SIK3Cgo2ZJnkJH5wF9SIetNJlj/w3BU+6EGe6w4rmxAD9OJ0UTY19wdzyTD/vZ5IdoWRfYMTJBn0XcAEYakADPE++PFKdHSkcv6tVZWUzrwI0+Rt4Hpod/4HVA0ofb33kIt0WO8K0PQMU0iADbzAX4ezGVvunFHTqOLXxrf2TXJlz2pHWszJcayxUWvqhHKENGpK6Eq1u+she8bt2QC6vpzdtfIepfd7GBF1Np1YRbiNb4K+KrM0H8UdHm7bmC7RBMCzvkH3W5WnNM/xf5HEFgNkMnwGkQ1HeLJulIR/O6Yoba2nLT6ueb35vYbXZ19hwfv0VTPcxvFGD0bv5P74AmLaTfFwmM1tsXE+bK/SM7UQAOLLj7hDh+g8bD5k8pb5V3Auj7hXmkftz9RKTNOnRbx+a0aN5bsJCtIkv36EURY5NLMLiP7xdAla0jiUdZiWOGQfAjRpNZVQ2II6Ivy3/kmqli546ifrrAF+VLGWxaBTBViF3pWVCNEP99MaDk4VtNU80my0C7zAUcKTOAHGTrSMgiKZ5KzZSJdYy6mFFhnkgzoCEuzWeFhwiVzNeKKnr62vEnwXOXj2hEf3retn4/zPCYcfwNxUXoVD7cOtKXpsLM6e+BCiECNt8mzS23HpZ2W/X0y3PmXN4l9vl0/2WZbH2bA7NmhzRlPKqlyhcONH9/xLX/jK45Kn5j9PiGytWteG9OmWdH4Uzob8CNNIQz/dou2ckFLAr3KIGJ8ghcxUflaepHbVYqTExRW2GDpi4LUrZ0N0WVCqDQKma7JjUDMM/O0WdYbMAKbALxlnPd8oRqGynhC4En1zHzuZqYMNOHFj3+ZIjajbhsz0i6YoaOKxQZhkR+V/EBbC5jdTUharmW+GaaPuMgFOoSsc//I2HWDrekL5NfwgKo5i9XyyICm7YdTnUq5aHJr9oQEBAn4F/gr6Ffwr5Ffor7Bf4b8ifkX+ivoV/SvmV+yvuF/xvxJ+Jf5K+pX8K+VX6q+0X+m/Mn5l/sr6lf0r51fur7xf+b8KfhX+KvpV/KvkV+mvsl/lvyp+Vf6q+lX9q+ZX7a+6X/W/Gn41/mr61fyr5Vfrr7Zf7b86fnX+6vrV/avnV++vvl/9vwZ+Df4a+vXv1/CvkV+jv8Z+jf+a+DX5a+rX9K+ZX7O/5n7N/1r4tfhr6dfyr5Vfq7/Wfq3/2vi1+Wvr1/avnV+7v/Z+7f86+HX46+jX8a+TX6e/zn6d/7r4dfnr6tf1r5tft7/uft3/evj1+Ovp1/Ovl1+vv95+vf/6+PX56+vX96+fX4AwgAC0D3/3CD+qC3ePa9Xm3UNLO0Mcd3Ad2nAxhEOYYUi8odaDEbgUdN3S7EZy55PiXtGoPua6F6Tf9GAHF+IWwv88kObPhtxqUV6cAy6ntlyi5RXJuPiauvv+dJcADEyiiHnCBTl12GxlqcV+XJrl/hHUCjLdWGu+83Phl0nGf5ZIyj1tNxUEeJ36xwVVCXh5OAyXcHojmiR+e0p5Q72SrBSCc1zaG92VchTyub/VHM+cdjTTcjg9Prgx0vt+OryHIlRCaXXpZ7NOo8YWRgsabsmkM3kDmnKfO2zqzev1xr1RPX81/S9xomOdP49QbLda4NCWnAwCkkbw5V3/lCWg4OAqwjattazReWscQKsI6W28qtgUW5iRyNcj3PSnWUlvb7u3ajjRMS5HyzN2MLnkSrLr1PXl6tZSPFmbHl2kvvJz7yWUbxrcomigVm7ua3a2XGDkfXQHaj/LIBZCcshUa7RjmA0GfndPnjbhUGYExuY23F165w4oXdOjNZTbKmq2WeOH8gs+YoT2U8cLGJ9rB7MHFq88t4ILqlUhPYv6VZleLUKhuoR8MBH88Sw8ap0Kcb5kl/tmOekUnlrk40b9YTCgLbt5mHUnE18Lvv+4xbHvnNqkTLfeLk6N7J5v2SRJPnlf9OK8wXMbjpy2PIQnu9/K3yYJS7dTX9QSpZ0cmVrS4l9duOZCspw7GaQc0EbIH/Ei1sVLNaMKr7ngZUFkbqy4ZzF084CWO5MazeTo5m/EoC7ZHtLyuti7jxjA9ZS+kRmafct9GkUQQdRu57lpS44fZZ16DrRkB/I7muGPMjAMKoJ6l7PK9ZFKiSbCEtEX3aqdeCrtqXjWOOmwrlqCnYZaJGORCEkLWt31JXxdXsK7JOKd3MpbSdLJAxXKet+GyzJm3XnICVGunnCA9x/FyvKtHw+CVX25PFvJWKXHlwACLP3TIZakUHU1hvDXJNJSS3p5lhE/sCUuGR0zLVsIt3I6BdxCix0jhlx9tfU/fv8ooGoVi7WUES0TBkLXW0LOXYq29SQx1/hcMTW2eVv6j2c+AVstFYgBHi9MRyeoAW1Lvq+xe9hdc8AT18h1pzXope1IZDFTVW8fKQGwUUfsfZyJil1ZEqSanDGqlKRlaem6hu8Ig0R6hCfWFoYPjiC5yr3XI2hFNEhuXamDbWgM5cca5BFgUi/ttj5QnzDSpsligYukQay30CtKZkdxP/2ivpid7KWvTY0xa5tJTQoy1RHGOq9JQwbBnV81A/5ibEuclRAFmFne3fkJNt+bnFFwHE3EtCjqtWro63ylKcinnuzvMKqvT7GtKOHf4x3tgHOorPHrMsKAgroFyYJw9QpDS1vvIX1MvwOPu2MbKfBWgprTE5WrdOsLRJblkhGVxk8o4QolZ+lCEXYrIAOISZCuY4jeJxdnIK1Xn3D6Tiezs3dE55AF9Dd1LHfKQj5qPk1j/mC4HY+BNMW6+NkKFAQIqOXj82H4DAPz9umTbYrXex5x+RUeiKSD5N6eXHrE+DU7y6AOyYFOwt+ajYXqZVBferZvAFERnulxOWFdEYY7jwPQ+E8ioxWT/ZmU3Mp32vzwKUPfyKwB9B9iKujUcehiDs/u/bFUKYni0SxFagJmZeZ27O7UmQtVh38ye6tH5I502ptrlc9zqOkrrLSobOAGE7KSoJRrDEat17TqMM3mHmbHt+lEJv4CPqPHMt9QLkycy+TIrsgIoht87C2o2/pZQlRHA8nGD4cC1AXrU9ppTMSAdAXbL/DnBHOmzbcFOfv04bXDo9VzfX5BRxeP28sgofEIsc2ZTU6yTNA44XlcUX3u6Bzg9+zBl/48QJmlakreE+afM4o4G/OudJCJUhCgRmx/PvZaAkVrWGwutszr67XQodfMumnJud6tnZGu8I5e82WEYfs6YDs+QxhxCOZOuZogFMYVKOCK3PVOiMRp5mDg99n1edkP96j2MhPqmWYczsO1V+fum4D6ShN1brGusv7BTNDQqN5UDQQgvb9KDt0PNvKX6zUOL0089zPl4cs0rVRaV8HSuw9Faz8+0p5RJAs7gmQfafq+4bXa84r9xIfKuBeggbmi+j7QRJleDp0Xo4RA6Y7uL+msQk8NHjWthA5fsc459CALFVIfe5m3OaacGhBBqWxLkajNSmtneel6oDrASkusztLdE20l+AfMZyTbkfF5UkbmfgCLvutP7cxfMTHgX5FgrvRSZvMlzt0URs2cvpZ7H32yyiFZy8PakNYOIldCyEZD4h0GKCMdp4GclTZErFeN5uBuJpduTTc6lj4+A9/zaS+gX3eI1E4JVdOu+3ZsYtyq2LLsIJK/tvzsKzdaiSpf7YI/i23MMEfmuZayMdLu8OPSlhk5v1MmHIJpZHxuE39g2nuikoF58fMWlAKIpZvtktFEgk3KBU4Lk65sbW06gRJpprt4PtRVMo1Cyng8HpOgMwWwSQAP2fNdFI/4zNENpQbNeIlKb5KnaMhuJVGIMtM+h5SKY/CP2Z6HFqCImQDondPWBOBiYxevefmsR3eiOrwlz1ssfi9FfETOznPOIelojSdqjQpUvZ9tiRTcP/gJElPUNnqly9lrOBdSyQK31sAr364A5EgxBUy6l/m9lHfWDDHKMIpFup4LNfZeE9wS+KnJY04fnK1AMVUL7jV4GFookNvvvoB7muNtz1De37PKaN1UW9fLT+tdKV9mKwe2Zjau62wnFuQdl08RQsqSGc0SE/7y0ebtmO2i5ZrbDKW769TE7mpXIHjPgCcxlVF4BiHfJqE4zAMr5Ck4amweAZ3BGBJ9bHKBDH8NbSvqoUbs9HjJzJGa9yAaLNCnIodgm437nZgk4ILGiA2a8S7KqKxxDuZQqgvTpf+bpBhWsl+uDMnpB1uBUW8cpFvSRMSrasNR4YQPNM1CYXryLTZ3JUXwuSjpNhllCVOs5GKKWReBv+yWHbhO1lS07Du6aGqyYmfQ+Z5D6/vILPDtH9lXliCwOZsnOm0cNJ6Kh7gWiBLA3JtsHwvMoTbz3DiGpU4XrIb4GMlwbpCodcqQHwSHAsuy67a+6jDl5bLXRdJ91dDiuRk8coqcQ73lYII+Iz8HKsEWWX2otCoad9dfU1l52z7/JqhySpqWBJPvVKsc4EDvR30k3nayUDrcBrF7irmWZNwByDfrbmFsCmm4cEB7gjno1DxDU+svDvlxr1YYDnS7+JMmcGkviE0PdHkf4MynCMQLoDqx5L0+mXATOMkHOjgAohnk+c+/gTidgLp3tcCXfn5XrwkL5axQ+PT9XJx1cyG92iablslJAZpBSnPod3XC9917C5EnJQMHfsmnD5jg8ugWjWSYdg34n4KNHzJD1zcjtuYRUogcTT70QFN9G+9XxoiTqNUmXczCWUgxDGGDTFBnjapKCG18VLOhUfKzNNlwCGWS4wrdzWyNV2VD/b9rNg6zJCHsxqlppwbHNYzFLIj/ygUifnQio6U5gGce8nU46Qey6+73EoDiiExS12h5AXmTCu3joTNV0qUXFU3kRm0Ql44AiKTcZsLECUa0WHsx2r07N36/qjRoy2m1Rk4im0r/Kp1l/bRsdGXqV33od2O9tvBp6OL3U/TEGVkb1Vpxe4rR0qHiHAnESV5fHnQ4zjKfFmIdJlhH4SxqYzSfbX5dnahZ2iYqLijmiXnmPsZYehR7570d6JxhNDnyw1evsDF0jtoAZ4gh5QTszqrg/FtVC5SGCEfBLdiR9xM/62oRWMmfE5rxIvbOFtJTxK0J4ywcm3/lkT8uQc2f70/InK1lqqv06aJM3OMujLdAPHBXAS+j8/7WI0m5tpzk1I5jfO7FE+kf9NAvFJbyryFS8WGeOKn0am3vM/WBiIDzlmW6FQAr5Z3YZwEn70lzF5PbOjo82N06WoR/Vjon97/v26YAnmE48tcQF79r/KShd5zWH46PhQRxN44uxBGddj9vc0/iqtuuYTQKKbYKtlBJEiwi08BdHxpEpe65vneZE5FtUM468cnkcwTrmAMM3syf+zOQuaK8qou94tRQah6jENqkxEcENMGSqd8o6PgcJogMqSqS4UniI2ZGb64sBv5gXZRc5HsdHDlplRHND4jB7W1yyAkT9SyuM9pEIjxTcauBQxP6K1BqL/axFU7li4dS/hXgB5m/z7HjUAVgWdHJhFKnHv0nQCsKayiDtI7HnZQIsPiC49nReS4Np/apAPYIwGEOMVpCuhgneWXwPhfLGTMIHp1pqCafna4J/flFcT8eeWoI7eCD4Du8X9Fgb97dwJGm0tPblXrU1a8ECVZ5NBmyhh1PEgcXsbCvm+ZNqwe6mHXXBdeH4AoYefj5gMGvYvQ+TAwH3TEyeUdnC1PZUkQj3XjnW4mDZ1zQrIdBdNCSNAlJFSqmMd12zozxwXZY7QKBwx83ZLxKRhTMr47du1yRgitziYtcTdmiw1PKCWUztWTTU1zZf2F/yVj3Dv5XcgJn6HyCooTbL9UXQP+Ydi8Y5O4HwpOqDE5R3+TBvT93Y5f+ZBQv5JCwvPYow7fDKLdtUs9hsPypN9wtdbkZ1SRKfTfIawOAqlWMyfjtkr2ZwCttGJ+6uS/8bFg8d7BYuIVROkPAl06QzwU9geGS6XnLztpl0TduLIqiz1r8Hjh1uk7DVWToexiGyr2rg5VUt5J+5mG4CikFa6ZcxeBiwgaYzu5VrNWDFweq72jEOQ0ddXEqHG/cXGzIIB8APfmx+k97RGTVqjQvJlNsLm9JBahtKxE/zVmomctJ7u1nkDzwhBQNA7u/2TbsX061gB9Ti8dHZA0NYHUuWeKcP6fOtWKjloVMpMFiqzGmBKGopK6H3Yx7VbzWAUld0h1zZdCNYyZ0iVE4g/qmKCbdi419aJvFR1rfEAKGGzltEdg9eIJjeTNB1A9/PZZMznhySsQbz9IwLtty84TyGaK+3QrVuuSgwUFJWuAtGDaW34WZdVV70DNZjmYTRxVDatoS0+MUnwQbmtUYfSKv8jnUzlg1
*/