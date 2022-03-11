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
XZRP7nLQSg6RppPacciZlI8FlA/kBvRxHi2PfWQI96ozaPtTGierOA2r2HlSiriUXRD+RofXymDXXIBd82Ud3aaPpYl+lfROHLO0p+WBF/HoOezJ71kHcmhH8PuK4Bfci42zGyeDG7AdG63uDFh+lY8mTXJ+YYMlv7B+RJms0Wz4u9SnZsnpQ3nPUduQQn64GQt09KwiSpuybmtiH7chLJRDFYINdTO+AQvPirMO7uTfxjONq1bCDpQH8K5yjl0Wi61E5gvYvZP1x/UfqPwLwP807W7k35O8xi1mSBSsb9LuRhLqr1u06JvqD2BwBGu27/9tze7RXlizn2jPqxle/h6+hWKqY/3KWJV4emATo9GKjanWULRaNulZ2tn3TtLSXq//AKuWolbqR6uzExTahoB1wOWqWp2M3wrqk2FA+v1INie4LefQETDJQYcr6njQkdlhO856/y06imjdoRpNDr93Pmb+IQFwZv1uRLQdr31PNqs2U+3aAFkr0YrmRCu9ICYO3MQtLwZeMCf6vcpuxFDmLYiTTVNlKuxYSjsxzTuevkBtiIa/TzhAcbi5YKvz6BCEOUu+MhIzYEUQFHPlxdHhuQKi5fI1sbqgMs/nWLVh6hZMwwso5GyiofkzMT8DQTSAMFc3S5SRHDoo1sSOBlzRN6JQk9+NJn+zcYzJf3+E5iV/GhkZY/KfOd/k74iiNcbRyKu3/c8m8A8u/zGDHj3dqxr03FHKC9TCfsiga4wxg75/+diLw8dc3o2XWcBsOb+U9V2H12ORPYj5F5z94rz5KhfZsTw6b77URbYtHz9tFpePnTbLOinUmJ+dXbtQp57DcpGq5dEJOBBaO4aQ4zxC+T9CSMt6f0MJXTyG0OQxhBLOIzRYdD6hgXxDHVeBtyLa+z1Gh9/eB4YzM3YLVAI9eiJXWMFx6avJhRn8lkkSuB+L+mFmlxKdzadACy3qdznIX7bSgy3ARssyW3Xf1jb89oWcJRQaRrYk09ecblErmHRyMl5LAhn+NJNeDxy7WvvDr0dip05K6N3DVPRU2qxvA5X/dUWjFb2iaLSiM4rGVzTlByqaXcvdhjVIjHOe4CJ3n1IJ8om0qmE8SAdIDXZmPN7iKB7X0WCfgPWiCzbIIOv7lLbB88tGWXty2ShrwrLxrG1c9kNtoN76blWWXcDhO1+rdFnv7dB7G+zD7J6Ag1xyqerczLsA/9koPj+ZPWgfBim3zwIpqw1ZhNdNnltXipdF4ZtS8hEb92p8s3FwfH9mJDoBDMvo6mPbmYH8Xi1Oi2kBD2Cr0TunQAtoXgQt8KA2rgUmkzfOjB39L48f/ZPIM/Fk8votMOo/+9FRb6Kj/gMnedg+ZtSbYNRf4yQjS9UVyY/VCVZSVFnC8DcId/VohOoeDTeV3ACFScU9IkOmj3L1A6rge01MFbxuj109RK6HxEfD8qXkKtyC0ypP7TzRSRrD18J8Oro1rRO38+Pf6cRWztApHz8R3agFwAD8J8cxkRwPHr9gf5mWN177deeZUFn4vz7EzVxH536G5xhwAxmX1NXRKUcp4XkICA7SYLiO4jb+TdaQVrSyEsSFWa++BJP56PLwasZV6mvnEuh909Aas4ZGohdv4iWJUpNspYeueEODTv5c+i6nr5FpMJvyva2c/jb+NGSZ2KTTkG8ikOvScpGRvpWb1CXb8y5Q/bMBP6KBr0D6G1eneldpp/Mz6JrPJKm4TxKjV6AumWm34Jqvj750yP+h21Q9Brpa5dGQf6fv8CwVofh+HLwZ3RoQWpXvXheC2sFO4Rtto918DmLN2gUJHBovndQ8vG7s9a5m5C4V35PZ+2KXR09GteYx4Iz5hv9SXwtZ1GtapWIG2CwSug0/eNNr9GpnukUiuSNX/RAMIMcud/Yp6uXO5xX/rH5c8elYfBW+YcQ8+36ncjBpHAezMPlf8ZA6jgeKHuOiZjwXc8YbMKYUbCR0B3/xMTKsA/fXfsxhPYoXOZbi3ZNU4791Jd462Ath0BdJl6JOmDNg79XzObhhceKCCoK3zPbgQUGPvky+Wojo+MxxUINMIIOWPwm/Ov6DsWnWQFzDf/3VyOhdvP+Cz1U/wueksXy+Ofv/Nz7to3xKxalOqZzO6K0BWx+fTtq/jw2prwvpXbY4f8qzmzd9Ia22NJhsbTU66VA+ADankN9+PzqQ2kr9NdomU67U7GuvmYbLdJyJPdhaIOs9ueUNTP7NvvbaMBTXBBqzfcukOtv8rcn4IZbcoroFedzgiKbuxmt4o7LEIE8qJR/o8A7PUhfxFdJRg4M0tnmkRCo2s3uXmJxSR1A2zMI3Ua638G3nzM9KRRiySwzSBHbv2YPY42bha1iRH/Yp3GTbGY6pD2kWgqGY8zZuA5ezre22Q/wk27s8td5AV3QYRIt8U31IuxDPbwwDHTwjmRbsTkpqS1o9THdFJcmTJUbqDMoX69uTPtK31jfTK48YyOz7hOsBMkkfrqt0i0XM6DdTcscuoIDIKywu0X6sFK0UXttJLqWdHPcVeDSeiUKv2c+3ScM7drh3kI5c+oEMsYABi/e5qGfftneLBQa8fRWvDief070f2aD1UrGFxY3mSimEzVz5BTZz7G7Dv4FJGXNeq9S12qpYv1ZvUa9OW2bHTeOjF8uliup9cZmx++gyRtMyIS0jevV6BhKI37RsiV+9nhG9ej2DXr3eQTFXqVfUnXcDHd68nElvXs6I37ycGr163aJevZ5x0arsTHr1Or2EvTh+D93o7eu38TFYReW6QxbN+3VD+RvT6oayNprYP7R9dDKE1+HVnbj4IwICsbaHPDpiGBiJucX0GJQZOsugMrMFx8JgsHu4b5jL9g1wybiARB7CA/Dloom88V1seHxQQC3ONFz3BbwJZHUe3TRlJCsosjWAdmUJvr417nMsBPMX2/SiKZWGuLkuVG5fwITEv17rIrecGsFr85bh9ysmQgpogAnqKl7TMkZbuQ6/6CYpLunbuhpGw01QNhnIa5gFXy81FTKayvjLV8BBYLOpCMrEJCWXPIJ71psqVSKxF6fSkG2Em05+i5tOkagZiEofEtzfLpukQgMwIzWvo5matUgs/DCSUfN/q9IneNBnwM5o8WsOx3Z+gx9jGFMMVOR8bsjD5/EClhNlwutwk8XY/dJOV+lqFH5VxmMWNMxk9s1gFfDm8y8qLvx+3rX0035Fw9YWctfnI/j9PIvkmLNScmSvJKnqDtsLPp+HN7pCp1rt8IxUZT12/rcAHf6l2YY78X54/BbgHPwWIH4FUOFuELZmX6lwJhuXfeWmuf55myTzG+KKbDN+BnDrGwYNP0X9DuDSNxiyXBMNrKOrtsj2nWKyRhP/EKA1cKdE4/UPGZAHsBIlZmmlOa+EgX5DN6E7S/6iuR5vjY0GJCzrFgaUgHiveXWJo6y8onwNiFNpi6mb7LHqhnHSY4BmF6jHHvJeobrELSxa8RuwvKKd8NVVVZMmWZS01+i6AX65Bz8oIy06DPGqv0K7OfEKYdZLX+LOvw98UofySdVrmPAKElE+xfhzNO6Ix7fS+KpY/JW1v8HdEZyl6k6VIsLKAPYy/kjFRP1arS3ILctLRlxuMWAo8zEoRZRPgDGFu9J3lJtD7zOeCoa0xIP+SIlH61A+wpP2A3YwkxPqiy0aTZZGtr6MvNjshLvcoV62r7SBdcW8L6+KprBqCqPwvTRRmU/rgzALnXv3KHw3TaSfQY8ZUEP3yLgLBLbMEIZ0NWZhSM+nvtzzy3Tw8uhDTFYjpPrUSGyF+t8Wj/s+X0l0PZ3uNbOUunCLmSYPUD5Uym3N/ERy06mYay81S5/KN+PnFoqHSxQ+AvODjj/TbwQA4uTYOxhugoPMQ80gf3jhrgX/0lxDXdY5CQpbDXWhX3rKwjmOv39EEd5T6AXU3XTPxwifSTq/VtcyDn4d5yEkfaTOegIw6zFG1zz+FMX7dRyP7LoRtMgRCfeZ+Bf66eynLzr7YdmDK64xCCe0XJODVC84b80jc9ym0E/pPieo4zFxdbc8lcwbLWGhWqjK8vgAEyzs0ynPMWl1N1FOjyghpLF/QXz9QzEaoH2r8I09kZbgi7diRlyCH61Jxv3HzUvoy3x5Iu5A9i9JhSQA4StgaQkj/MSgEbVjt8WM8Cx5pTfGEKqvMVKZRBriSeQ/FoE0jkstMDMGgUhmKhCYIsM8UAvzwHzoLzhghRattTXPeAfwyD4TlIKjX3vDpRrcB8Cl5VVYOMuCGdRrt4U4o7XVjTe744SVdo0+8v3gCPrneWWp/AwVycTuSQGssR90w11o76HXye4xOchDk6L3hlbjZ+AaXqMvDLU1s/KKLVuzrO15FQz77KGVIMwSl2cC3pNPX276AoAN+qrYYqNZNmQtqNRyF0l1GIHCWK8bdb3q8Idxfk84OTYBH8sMTqVtCt3vhSXhNbEMkPZox5fG+vCCF/mt+B7iWC/5+0h0bhVrG/qFk7yKVN5iC/GWvAozPynqQuJV8eCG285unky+Ohmz5bqF1JZ3YRZDQ4bcDr6u7SMa7BSqUxWphZ8s9eV815jYYE6/6Yb3uEthOilPpzPM1JSGiUtu+IhjbuOMSnEqfwqJ6Bqm2s7yEublWfAtPI6GtYxSFt6CixwZ5P6To47zI1FFMGa+gNzTj69kjv34Subox1ey8OMrqfTjK5bRj69k4sdXoFicOdbWLKzHS4FqN88b+8mVWbMu/ORKG/iJ5321BIwA95bfsBi8USf5CeqGw2b8LAmOTPzwSiZVkRPxkzP0FAv9XCgoIicxXRX7Rklv/Bslf/9s5MJvlNwGcweFz6bfKDnv6yR0aeZw5g/NF9UNRqz3Z/h2BXygncA7bkt6iT7N5Dn6tJCn6DOVNNBnBqnD53XkIRrNIg/SZza5hz7nkJ/Q55WknD5zSQl9ziPL6TOTLKHPBSSPPheSa75AkeQrm/LJbApaSmbQZxFJp88VJIU+HcREn6vISA8+y8gAfa4lp+jzDvIlfd5JjtNnFfmEPu8jH9DnetJEnxw5SJ9byB763Epe71FZoLe6kJcQugdf1ZNnaRA/u0caaRDvDCW1NIhb4AlHg7hwTe6hQbz5llTSIB66J04afIkuuNPgqxhcRIP47olcS4P0U2aX0WAAg5n/D3nfAt5Ulf2bJmkbaCFBC5ThVQWUEdBiASkpQ3kEKhIsQgsoBWaEgkUdhBweSqE1rTQ9RFHRQUXFKzgoVTuKUpCBlmIfwJTyEItUDVDxHMNAeNgGqM1dv73PSU+D//v97/3u993/vZeP5uyzz2+tvfZr7bXfzIk17FIn5sQAgBTBnLgMS7p5ThEZKzqkf5/DB2ywk84yJ1aASd8yJ84CkA4zpwfOMuZsgPNL5sQIs7SdOS+w+DMnu+bsNeb0sfgz5zUWf+b0s/gzZzOLP3PieGppNnMa4ZzKnLijUUpRRcaaNGkE+wDjSLqPOWPg7MucONZA6sacPeDsyJxxcBqYE2Ovkv8snP3h/DdzDoTzLHPGw/ktcw6B8zBzDoezjDmT4PySOZPh3M6c4+DczJwpcL52VhF5Et7Wsg+pcK5izmlwPsOcOMReymTOWXA+xpxz4UxlTGLbrutzzBQjrOHskrzIVGkQQWZSN8EaPlDx6c59qAWMV3zacZ94a/gMxafpDHyWDbEOnfUAvwPuJ/i0Dcich+sdxfHR1vAhCt0+RjfeYg0frvh8zH1irOFJis9b3CfWGp6s+Li4Tw9r+DjFZzn3ibOGpyg+87lPX2v4JMVnKvcZbg2fq/iM5j5J1vB5is993CfZGr5Q8enJfcZZw59UfKK4T4o1fLHic93DYj/JOtShxP5nD4+9FEcmAvVkRz9pDcfNdQ6L2JldfTdlsRAunVuPpQlGzdkrSCula0//xLRo3LOmb0/mn3N/mHm7sa/3MiWlsxr7yZxlYYUR7FNFmPl9Y9+lF8Uy54G42dX/0/zEAGMUrTK67B4f4Jx4m9yeD9kV3MfG3dUxu5Ee3FmZLg7VvdLFwlqnx6fnNwrdE4eayMMxVXouHgalMJEjqKCxHqFjBLthzock83vvTpVK4LRWLusmRuQkDR8pdMKp7qlSn3gWGi5GcVYYxQjidFwZ1SWDd3iY99rvzH2JGfws930YuxErM611ZK2E8UWqYYIlr9Tswp2m2/Tm/IexQZY6yNjn8eWvZCjxeZEoNmXjvFc7ZZaQLi25V5kcuTtdyry37eRI+r1scoTPjcxkQbfOkJSweZaEe5V5FmJ1t4ZV9xBWUf8Rq75rHJ3ENFOWfgYWjgi/umw+b++2M2DNYcoMmLAc5l6aSZxsMlQldlzawbmaeq9/sY6PXZPh6uhOCVDXxhLo+GDhrA6/ihEFsSuvEj5svJESyem5xFfrZor7vfdTalK9d5bqEyOWdmRMejpXx+qXdHVFOCNakF5ihKN7ZmKsoxtWn0VQV0btS5Ucg3GAKX1iOt6o1zAu954KMYBxAYv1qtDJenNZB27a6l3YS/EcfzE4TYHcAJZOLbtdandGte763s+su3SyMmB5fHNBtY/N+WgQM0VbzC6cVJ1pLVs2jGxsM7GPmj41XVrgZZaPtNejWq3S5+QUFeOVWyZsroio7iKbMk561QPLDqF+MjgQAC5fMXJlXDRfEKFY5PxOBGYkJ8FIVjDsRl979JSp09Ozwtz2mClTXRnRzATGpD4RxpAxa87PYna1yXrI8U9XmHcX7/s5/c+a83EvKE75XIrnTfMLi+iJqGz6hUVFfkwdwkFN1XS0XmU2V0zG7wxYsrRnkxWnXdl1rgyf9aYjmrohbKkX1nhQjnSW3vwx2MXdQbGQ27FNT9Qh8UjzKBlJlry/oX5lexLnxAhjxXLisOxunu6JHc1rcShPYUcxra4gWs+PQczEYXnJVptlyanhGRfMebvD+H2b6Ex8giK8j01ACI+iA3JoWS+xAgUsggrYg8KvlDQd6FUwDag46k922Swo+VNZfOvoN31qYHkwUc15NtzZkuEz5yexMOqGzyIjt9DbX0OUFdDQ8JuFzIykHZGksN4Ne8UgiSY/cNo5xdT8gkuHfWNgt7OIOa+lUv+mlaVY60qrxQLsXTpFFnYL7XHzOphczhvh5rXv8s6tO1rPVg//jDWK1S77Cevx1XcWTupwjSfeiEPmvMO42sF+YnQyfYWs9tpVP1CKshUbywMolxfQ+ZLY2Yi2eu9fRJsH/cW+5p0dE0rFk95Oe3mFqFk+KNm5X2/e2T7Tekj4RcaFrRhzmTp1KkuQ1pJpzr9I36RXv2/t4LWGob1iurKm7Ty4Uq1dGc1UiSZQ1ZtAT31Br2D9Fm2xpPT1YuVItlC9P/UXqLMTky5NYTtGoXiFuziNFPM9qqd3MhXRXVLk96oGuPNepgEeSGb1tHJZL2d2bMBhLuhl9S9vJ/1YjzrrPSlWVtqaU0n0glnxSvXSu8JEW/Oc4NE6qDVtt60msHm92P/B5rsCXZt7RMZiXW66uDRajEiZ7nKjR+h4JMUxNsUxJMXRL8UxPiXFcXuKOX+rDsdCr6LPOFfRm1iJI7N0bFku974N3ndydye4u3A3jkXwtudurJ2f4l4dOz3wBV6lzQfU/X4PimNNTj/ZGU5/F0eU09+Tas780hbvbaK99PvxFueZc99nFDurDS576XT3ZBOW/4GDOx8C812B8YxZLN+P+AX8pa+qccmvaeZMR4y6QzAqXXq9YyM7EtNEXTB9BRt24cttvqKC2nbHHzbYNfNTg6o1fnyD2y/9MbC+bb0wKej1NdtTidOFZvLjhQbjU32H0pudLFM4H8DeYTB/KwybATE5koyf6uDmvvQSbCE8dSbhWELjLmwdTLTFCCMS0yzCs6ekuqN8P68Zp5Pwvbwy+iTwx27A0VRSzfnf6HBWyqmLMvo8ifYYIRnk1lbyKH4OILt3/odTbFcgEQpRCsfXQB8eT86ExvHyWsYt0RYt9McexuxTF+vTLIyPWURNVt7AwTEb5wp6ZyTao4U0gFO/t1l4Kn2O878uziTwTLGKS9FJjYLzephwxymPt6fKSjDDqyO+p2AHmxFssU09FsP2WBaRjCHDR6mlw02BDVlhkvkJfjVglmGOK9tjHYldcdnTxCa29y2xR7HDJhqLG5OjnQ5zqnSun2LiGAK2BmcgZlV/BiME3+A1ifQJ8wkMKZYqvyGbj2+h61E8wfte6KVK3UiKcpJgx4LgIN8U58gDVPJayG5Ov5uqHl6gI/hyn+pybNFoxrpWO0p15/58ldpZLHtRixzUUrr09764xymaDJOZ254Xukk764KrLCZHx/EVNSNhJCY7Okhvso/Yvew9sy3M0RWzHtss5jx2QPJkk9PT4uqIiyaVHUHzm3VTs2DsPBZVHtzzNFBaXIkbTuKsPke0NI+5k60+oQPpGinPy8+VJSs0Hs6m8dHook7nB+SR+SX+yZ2id3UUJ8cO8A845JpszA+s7jkd01PSgFPK+rFm72Rlv9VIZkJEO68HHN2d11scXahP4OktHi27EQ6j0vgazExlLxQZqHGOzlMxGTNFqpYDgT77ud51DEK4GSYy37w9sTy5GcGJN5lXRrP0eZ0abmJ2M2kZNdm8kWJ5PzjmBK/GDG4dm/Jt0JBY1J8MiYiw4NYx3LqHrWNXdW22jqEOhmwd6/gLpVDI1rG6O9nWsYG1XCa+dQwrJHF1TN6LOmUPGc5QVveQbb2zdQ/ZG3dq9pCtu7OtOb7qzv8de8iwHim4FqnLLdvIWNKpPWVulTmPBGBdC39Nl67fQfLtRrDWSspSP7K0ynmmt1hXdjO87EyEIfptlqV68WDj6L5rhH4E6wZYjDouzfLdrYD2U1cix9FV2v9NMDvq78J1CnwmPsNk/dFxhfeWTHmlK3/ephfOqb2k9RJ0fIR1vElox3oD1cmUDR2VfkC74bGOSPLwfl4Aoz8w3hi0+VEqUIPewvVqUDK/nm7BqLAt2vxaKbvfNKFVHPtdbCbFOxAlvOPX6sXvvFmuawm59F1VGNJpNi0QLT38tWZZ5PA2E2ZYCWA/bN6Z0n6qeCr3DJYYuOxVYkqEy+4TU8ga0uWewwqCXG9gFLakW6a77NdcNn/uzbDSQEC4O+E0yTwrnypustNvWHWN7OSNbFG9O9u3fXuWfvsMuYDenfPrdeluwefObti6das4chMpqofdE8LecJ4=
*/