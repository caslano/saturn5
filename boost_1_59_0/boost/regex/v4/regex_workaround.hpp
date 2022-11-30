/*
 *
 * Copyright (c) 1998-2005
 * John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         regex_workarounds.cpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Declares Misc workarounds.
  */

#ifndef BOOST_REGEX_WORKAROUND_HPP
#define BOOST_REGEX_WORKAROUND_HPP

#include <boost/config.hpp>
#include <new>
#include <cstring>
#include <cstdlib>
#include <cstddef>
#include <cassert>
#include <cstdio>
#include <climits>
#include <string>
#include <stdexcept>
#include <iterator>
#include <algorithm>
#include <iosfwd>
#include <vector>
#include <set>
#include <map>
#include <boost/limits.hpp>
#include <boost/assert.hpp>
#include <boost/cstdint.hpp>
#include <boost/throw_exception.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/scoped_array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/mpl/bool_fwd.hpp>
#include <boost/regex/config.hpp>
#ifndef BOOST_NO_STD_LOCALE
#   include <locale>
#endif

#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
   using ::sprintf; using ::strcpy; using ::strcat; using ::strlen;
}
#endif

namespace boost{ namespace BOOST_REGEX_DETAIL_NS{
#ifdef BOOST_NO_STD_DISTANCE
template <class T>
std::ptrdiff_t distance(const T& x, const T& y)
{ return y - x; }
#else
using std::distance;
#endif
}}


#ifdef BOOST_REGEX_NO_BOOL
#  define BOOST_REGEX_MAKE_BOOL(x) static_cast<bool>((x) ? true : false)
#else
#  define BOOST_REGEX_MAKE_BOOL(x) static_cast<bool>(x)
#endif

/*****************************************************************************
 *
 *  Fix broken namespace support:
 *
 ****************************************************************************/

#if defined(BOOST_NO_STDC_NAMESPACE) && defined(__cplusplus)

namespace std{
   using ::ptrdiff_t;
   using ::size_t;
   using ::abs;
   using ::memset;
   using ::memcpy;
}

#endif

/*****************************************************************************
 *
 *  helper functions pointer_construct/pointer_destroy:
 *
 ****************************************************************************/

#ifdef __cplusplus
namespace boost{ namespace BOOST_REGEX_DETAIL_NS{

#ifdef BOOST_MSVC
#pragma warning (push)
#pragma warning (disable : 4100)
#endif

template <class T>
inline void pointer_destroy(T* p)
{ p->~T(); (void)p; }

#ifdef BOOST_MSVC
#pragma warning (pop)
#endif

template <class T>
inline void pointer_construct(T* p, const T& t)
{ new (p) T(t); }

}} // namespaces
#endif

/*****************************************************************************
 *
 *  helper function copy:
 *
 ****************************************************************************/

#ifdef __cplusplus
namespace boost{ namespace BOOST_REGEX_DETAIL_NS{
#if BOOST_WORKAROUND(BOOST_MSVC,>=1400) && BOOST_WORKAROUND(BOOST_MSVC, <1600) && defined(_CPPLIB_VER) && defined(BOOST_DINKUMWARE_STDLIB) && !(defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION))
   //
   // MSVC 8 will either emit warnings or else refuse to compile
   // code that makes perfectly legitimate use of std::copy, when
   // the OutputIterator type is a user-defined class (apparently all user 
   // defined iterators are "unsafe").  This code works around that:
   //
   template<class InputIterator, class OutputIterator>
   inline OutputIterator copy(
      InputIterator first, 
      InputIterator last, 
      OutputIterator dest
   )
   {
      return stdext::unchecked_copy(first, last, dest);
   }
   template<class InputIterator1, class InputIterator2>
   inline bool equal(
      InputIterator1 first, 
      InputIterator1 last, 
      InputIterator2 with
   )
   {
      return stdext::unchecked_equal(first, last, with);
   }
#elif BOOST_WORKAROUND(BOOST_MSVC, > 1500)
   //
   // MSVC 10 will either emit warnings or else refuse to compile
   // code that makes perfectly legitimate use of std::copy, when
   // the OutputIterator type is a user-defined class (apparently all user 
   // defined iterators are "unsafe").  What's more Microsoft have removed their
   // non-standard "unchecked" versions, even though their still in the MS
   // documentation!! Work around this as best we can: 
   //
   template<class InputIterator, class OutputIterator>
   inline OutputIterator copy(
      InputIterator first, 
      InputIterator last, 
      OutputIterator dest
   )
   {
      while(first != last)
         *dest++ = *first++;
      return dest;
   }
   template<class InputIterator1, class InputIterator2>
   inline bool equal(
      InputIterator1 first, 
      InputIterator1 last, 
      InputIterator2 with
   )
   {
      while(first != last)
         if(*first++ != *with++) return false;
      return true;
   }
#else 
   using std::copy; 
   using std::equal; 
#endif 
#if BOOST_WORKAROUND(BOOST_MSVC,>=1400) && defined(__STDC_WANT_SECURE_LIB__) && __STDC_WANT_SECURE_LIB__ 

   // use safe versions of strcpy etc:
   using ::strcpy_s;
   using ::strcat_s;
#else
   inline std::size_t strcpy_s(
      char *strDestination,
      std::size_t sizeInBytes,
      const char *strSource 
   )
   {
	  std::size_t lenSourceWithNull = std::strlen(strSource) + 1;
	  if (lenSourceWithNull > sizeInBytes)
         return 1;
	  std::memcpy(strDestination, strSource, lenSourceWithNull);
      return 0;
   }
   inline std::size_t strcat_s(
      char *strDestination,
      std::size_t sizeInBytes,
      const char *strSource 
   )
   {
	  std::size_t lenSourceWithNull = std::strlen(strSource) + 1;
	  std::size_t lenDestination = std::strlen(strDestination);
	  if (lenSourceWithNull + lenDestination > sizeInBytes)
         return 1;
	  std::memcpy(strDestination + lenDestination, strSource, lenSourceWithNull);
      return 0;
   }

#endif

   inline void overflow_error_if_not_zero(std::size_t i)
   {
      if(i)
      {
         std::overflow_error e("String buffer too small");
         boost::throw_exception(e);
      }
   }

}} // namespaces

#endif // __cplusplus

#endif // include guard


/* regex_workaround.hpp
fDreQhdX0KlMOlapofuh2N/h1yoo1GwExcywhBWVIYc9rkY1AGFc4UPvUknnm9wilk/CAfOI2E4hs7D4o4LnwoERVyOju4huSmLSmVPUI+zEg9BRY5eAQXdwBGVUVKEts1BCAfqKhBgaetZ0MSqtNzCQ4UUQHUwvC6Dr4J+8QlQ7BLdTRIbi50ExGZIAqJlgIRED8OvmXbNRApAanwwKGQEh6vcHWQ5Y1pEE/YL0hnN4zjMCb1LFKdXzy4xccGSAhU3cAn/N4FdJf5NsppHDMnOZFh4DfXw2YWQTGpyApstF/rugGe0IC3BhCQhpkPooOQ4aAz4Xk3QwEX79PCIiLE5KikoVReWa4kptcYUWZZ3AKjUoFg1WoUFefxAP3kcQnl7YZ/AL/pQLb/6nxYOp6RFtfHw/qLDasXMJD784CHpGjGIIYCBsAjixbsBNZ7TjL8H5a3hZuII+PIQ/JiJLpNfFhbMD4rHtD2178L3N956584lzh45+9NjLF5999fLRs588f/bqM6cvP/PKhaOvXjj56sfPv3z++Zfeff7kO48/c/bBh0/cf/jonnue3nLTQ6s33bts/d2TK3f1jWxq6V0YS1W/efypqalf/efVc7+7/A48/uGTd//06ftTX3049burCMhTf5ia+svU1J+m/vTVLy++/frJpw8fuHPj2pU9Pd2hSEIoVf/ieu4P/h/xvZ/NnqX4+fcs1/+Hk31dgGJEUOMPN4GwzEtrUJgrq0OW0fGAo9NqOOCX6rhZHTOpJsBnNKKJrAi2M90uAnCsmIRTzEtqCxNZO322Lr+9O2DvBQuCWboDhjYPsLO0VM8Ny1EUC+4HerA/nYtUEgVtDC+l5RAWIdsn5UeUvKiC4RcRNrxNI0CbruBCXW/X1CSgRYCmYFp+000WdC4JBY4I1GWA/SagXdTagMWzE+/vgOJdyN1GLfl+Kd8n4XooNiDRzisEqegDfBsX5D3d0oVpl4F6kSgW6Hy3iOmi2G4R1ysWBGRUBONXIMDhWcyJaizVaB8ZdfViICOvgRYezEJZIyhPNCUPV6t66Cwzj767mEExKyhi0Hsl0MIbIOwF11LISki4KRkvJecm5OywhAl/6xbgJmtUEobn80jIuJyd0QjKTcJKCz9nZEYUqJIfvvCZlA2NXzVaRdGoHD1t9LqKxY/o77sb/qmR9JBe/GQ5LiEDvJgZcLaEh1cUFhWVKIsr9YxGG6fDw+/287u9rFYn8k9r8M6IzUayDUe04MesEgXePVhL062d8OXj2AiKN9JDpGn88qfLVEQYv0i/4W0yHdN7wfh4yCWHrwtUgR4rZ3oeFH2SsCyjAVN8HIFES+J/6H+oTAc2H3xz/T1ndj742oFnzx869vFjr1x65tWrz5395Ohrnzx/5sqzr1w8dvrCi6c/PPry+Rdffv+5428/8dxrhx976b77kX7efOPhVRvvXbx23+SKW0YmNmequ9auXD71h0/+8+o7v79y7o9X3/3TJ+8DeP/8+fk/f/HBX7744K9fFmzqqw+mfnMJSHlq6tupqT8iOE/9fuo3n1x5/+yJZx/be/uti0cnq6prTXFnsVEwi/rZLPb3Zwn+5V+0vyhGQVEpIyTHm3SoGDFUJwyrNDzCbxBzgY/gxRNZgTrpaYc0BfPQRFbCRrFjGkmFVd3oMrSiKazWTo+t02vt9Fk6vaZ2j6HFqam3KSqMopQGwELQiz89eJ/uFCgkc1nFJj7bI5XENYqsQZrVc2MKwocLtoFSTXy0I7KURIsGXVzEx0SsxHWGuBOZYeUxaMQV2HO6BBptIIKro70ylFW0CgryGOMXjR0ISLl+CdcnYnuEDDfdroWTuageg04VfVcWzsAlppyAhItMirjbC/QtAfzyA5h/y62If4lCC16hcsCG8evmF5rC6JelJwwUegrwzQaU6uUjsWek81YccOdZAQk7KGGgHaM5WHuTyAsGLAcErLhEkFGIc2pZmU6W10myGkFKxY3JmTjfjXqQo3J2SsXPgbtkEdXYAMUgodGYAiWjwL+F73+6mVSFb3I1rvGge6DE0xHv/2E4D83LdF2HgI51F4GDAKqgKCguKlExqi2CNq98MKpfkLEtLrMvKTdPZBVDUXabg2gwkI0Gst1E9tqRdVrJBiPaohi0tBcPYbBgOeRA6YlCDb8N4xc4lDcdYxfiW4gu6gP8wmJow+xPG/gaJgLhl9bPtIRDLgaj4HnBQgrKX1v8L+SsWGvn3qOfbbnv1M0Pv3HPM+dBPD915srzZz4B/L4ABsenLr9w6sKzJ88/d/L950+89/yLbz/x9KuHHjpx773P33r749tveXjTjYcWrtk3snD7wOjaULr20YN7p/742beX3/4DAu97f/r0PID3L1+c/+t34P3wr199CAd/++rDP31+/vefvvefX3z4hy8u/OnzD6Z+e3lq6muMZfjvr1N//uYPVy68f/qlxx6494Yb1rX1tyv9plnkrP8n+xEL3eESIoh2HyfgwC1CW5BO/6YwkRWWOHpDHLqkB66UjCTMAjKoFGSNsmqbutGha3YaW5ymVheYscWlb3Jo662qGrO8wiAGio/I0YVQ4R3oCy+Cv0wFo9jAZbnFkoRWW2Ex1to1lRYqqyVjSnQCASXaS9UhRduZy3AVAbeosOoqpvFr5dJdBtO6l4vqog04Om0T4upoMTK0ufJ0dbQdy0u/mAHOckAMxkD0h9O4QbxvBXidAfo3QnQQFDPCEnZExkNdgUpBTAneLj8s5wVlXL+MF5DCMZVQ6aocFCUoSBQ+XvC19DpPl2nRW67MHOCFArgVNF4Ix2x9XOThGhH9ESYOKHNuSAbfGysgJgDy8HttMTIjSTjYjKCQn5RJ8xp1tVFXa9HVWFQVRmmpFlDMAdqNof3jBSUacblJVmuT1TmoSgsb766C1j06/kNLaLpAmvZT6PACnaeTTse6Of9ldscMculOf9qlomajIfbgj9s4AEMsvNPFAVFxGjU4iDv9hpG0e3FlZE1D6oa2zNaO5OZW/6pqw1iS1+UqBvA26cgOEznoIIfd5JAbpYabzKjOKiotlN5ZcGATja+UofQBrMlqfP6c6Xg7Fy9EgEcz5l9UV8PGyIW1DmQAQZpADxSjDi/19EdTFhfiqCZc2qcoIqjr/u3ns9oXb7376Gdb7zt144Nv3vXUeRDPz7965YVXPzmKwHv16JmrJ85eOf7qxRde+RD089GT7z537K3Hnn71wMFje/c9e/NtT23f9dimGx+Yv3xPz7xN7QNL2zv63zj+5N++uYTIF2TzZ+//CYH3g2vB+zfavvoQcP37q+/+7VcXpr79dOp3n//lm0/+8Bl65t+++ghs6tcXpn57FTT21NTvEJbRf3/+7adX9u3fR6g5szj/wqJrXej0Cp1PQUE/ceE3oDl1uAH/u1l2CL+kgUd4pKy4WpAzSCrNilqrus6qa7DpG+36Bpum1qKsMsrK9JJSrTCthpsfxYdBD89MTeSgeAsBv3FQorhaV2m1NrvtrR5Dg0NSgbdtKtGRJQY0xyyqIz1y0ihAbSlCPD5ChFddHZqPAczLKnQZ0L0JfGwC3OZPIdjS1dF0YpemZkeh6III4JKtIAYs3bURlxTq0xISbFIiKSfSCnZGxc+i0SKirE6U0VJptTChooEsiCpR2jqrM9R7KKmgwAs8vDrR0o7OUDuwhHZykQHnAnJR/TlFRigyKkRJliAPBXysKLhH2PjgTVAxFZVU8/H+34SZhUhEgXfJMRCEk8MOiSQZpabKaKizGuttumqzskwvyqj5SQU3ruCn1KJSvbzKoqp3KhqcYsBvXI3GbiumnZGZ0mjaZo5najyoafzSU6avrf6iaZeJlZhoNjorPYEqK4KiYuDcGgvV6dePpr3LqpMbWst39NTeMli/a6jm1oHc9o7A6mrtvBi7w17cqCObtGSXmRxykaM+cp6fnOtF7fkNJhTHg+sCazKg0imElZxI6IiYFk1cAegJZhcWE3r1KFAwHqhoxxLagSFsIQv4NWII0yxcmL6CB7QWhrIWX0f+x2x20eJbj+x89ION+0/vevit+499+PipS8+evnr01U9OvnH12NkrR89cOfXmlVfevPTimY+OvvLB8yffPfLMG488+eo99714277n99z9zNabH16+4d6xpbt6522s7xwbnzf/i/NnwNX9z2n8/uXz72QzRu5HU18CPAG/HyFo//Kjv3zx4bdXzv3pC5DTV//69ZU/ffHh1FcfT/3ywtSvLiL75YW//fLCX7/6+K/wV7/8eOoPnwOMz7/+2vVy5g8kP2GgvSbxPlx2QSEcBN6iBydJga3ovDmd/UcXugjTH06l+aUgvDklGiqnk1YYlFUmdbVZXWVWlBskpRphSslFtU84R4AWTyb6tunFnIP2HAHy5QblqjKztcXj7gm6egKmNre01sqsMBLlJrLCQlZY0UZmcRrCQlLOLKgghF8mwq+dD94rCxxYJ25ksIvwUCzJtOEKDTvuWbDxCx4uStrSUy9Q6QXAlohJiASuncCNG2Qpzm7kFEReRZRrWVUGQY1JXGORVVuklaiJA6ABKEbzgtIaOJDm4INbrO0hSiH4ruqYXmTopZ5uqQDnlxZ4oJNpCNP4jWGLCFD+xc0jnHyGVwQrAyplyejFSQ0QMeHgEzoS9xgiFBNGAp7Jj0kVOa220gT8q6k0yXKwsKh4CQUvichXUmZS1tg0jS5lg0tcYWGDpIErK8eDO+ii6Jntk+j255n2Q3oLQgqvQrTP8g/Vm4zC8ou4zMRAGa6IqDirImpNnA63fE7ctrg8vL45t6Onbtdwy+2jbXeONu+ZW3Nrf2pLi31ZXjQcINrMRIOWbNaT3VZyjoecHyDHQ+SCIDnHR3Y40CawcM+4hGjMoF9GpAyMCjejwlucNBM2EfLfmdehIZlMrMco1DyFUFnI7nEKWyuiKD2JNmgzFhcMHHMdRjqdWUY5cQ4Ikh/+bJbSZtv+0NvbH3hj+wOv733qvcMnPn78lcvPnrl6/K1PT771yck3r558/crpty6fefPiiTMfHXv5/HMn3n3oiTcefOTUwUPH7twP/u9TG7cfXrJu/8iinXMnt8Xz7ZlsBShnwO8fPnnnT5+8++dP3//LZ98pZxq/mF4Rfv/4+Yd/+eojoOA/fnb+Pz99/08A7W+u/uXLC38D/AJyf31p6leXpn5No/ji374C+/gvX33858/eBwjffMv2WcWzij08VHLmwT2GM6UvHux0OAVoZdMxCp6REvueOO+A7ky7AG2TF0YVWbyUSpTVSkv19GBzflzBCqE6ScKFsWNAm4IVyg/YSMIVq1kMJyVOaw31DmdP0DcU9QyEzZ1eWZODXWMprrEQtTay1k5W2QoQdsvQ8A05jmjR0JhuiGO4cFbXhedieeVIdYN5ZOg3DtxzRO+eiduFEPEFKCJIESExEcGEm5KTGQzbvJpABfkaslJDVGuJOgO70UK1OGRtLmWrS9noVNTapBUmUc4gzOqEpTpRTg8/qmps2iaXqy9OKQV41My0dyDHFEznMc10IolZMAAy3Pao4FmI6g+jFHoMCgk0e0HMDcvFSbU8q1fkDLKsXpRQsf1iAq6CCi+eaEpwEWFhMv1CYUIuzahlpVpJBhYTBF5OXMFNqgQZLWoQq7UDeOWgn8tMOH7F+45/afzSRk/5pruWZkBNx3hntnigvWC6XZGPlxFwHj18VJMMX1qdkdHuFAwG1eNp28qqyA2t+Z199bfPad07r33vGOC3fvdg6Y0dvnU1qskkc8Bd3GZC4G03o6LoER85HiQXRsjJCDkWJPvdZIOZRLOz5ERMycoYBXU+SUdK0pPjNceL09YiG0UgNYjyv4Vt+3T0ngU4Ne/iFcL1sE6a8QaLBsy/JhxVM033vNM1LeCnaBjf+/GsWH3rnS98sf2+s7sefevu5z54+KWLz5y5euyNT1965/NX3vn8pbeuvvzGlVNvXDz92sevvPrR8y+df/Louceefv2Bwyfvf+CFPfueueX2x7fuPLx03b7hhTcOLtpmDVUN9A1OfXv5T+DSXj33x6vnMITf+8tn7yNVTIvnrwr6eeqrj/7w+Yd//PyD3yOafg9Q/KcvPpr6+vJfv7ow9RUm319fxvjF9stLGMIA7Qt/Bpj/5etP339rtoj/A7hMNgkRwjvD0mXA9O7PXtw2a8Wevp7OpODEq55dMCMOMuAyBtA87IicF1PyY0puRM6EWw5+T2f0AGtA2aLpafBColiJpugIIgplhcnS5nEPRvxz457hiLXHr2pzCRvtjHorUW8j6u0EgrCVzJpQGggksZqF8CvD0EBCiINOmO4idIEjoChM1AmqUOSKLtigi748uN0pUMjOoOxqXMpMylglSk6pmpPXsCt0rCodo1qHBkfU6hkNJl6LTdzpUvTgbbU7vKrCttpoNC6qTS3VissMimorgNfQ4XMPpxF++de0/FzbbWGg24fhFiKRAYTteONdH0oGIRSHMH5DIjaa6aGUpDXyrA7wCyYt0YJWRyrawEB3LFK5ReALEzY2wydkRyTcqIyD5gGiqYDMmJyNBtRrheUmSY1VWucQVdu4WT2KbwB+wX+cmRdEg/fajTZmRnnQ4L0WtjPMy8OTlwAsYQmRUxfXGYExOf1+8byYdlHGtroquLk5c1NP1W1DjXeOtO4dbbljbv2ugfyOjtDGeuOyUsH8cPGAk+gwI/D22MghDyhnxkSYsSjCWBQlxyOIgjudRL2ZrDJxa+ySFr+mL2WcV2Vc2KSZaKR6s8xKd3FUXewTF/uEBfMLCdobAj8IDFQN6CsAMkAYvuoCfklcQkMn5XG5HSq04xAa4t+J73Ut27bv+c+2HXz19iPnUM3z6csvvPbpibc/PfXe56+e/+LMu5+9/OaV42cuvHTmw5dPf/DCS+efefHcY0+9evD+o/sPPH33gadv2v3I2q33L15z19DCHR1jG5zRuo1r1kz9/vLU7z+Z+uuvpv729dSffzn17ScAVWDhvyAtff5vGMg0hAGwv//kfdDYAN4/fPo+yGOg17+C54vwewnhF1EwRvGvEH6nEH4/Rvj9zdWvPnrDZvKjSnS+g6lVow/upsWzBBWt+aYnslroED3mZSdWpGY8kEdL59kLuVECt9wyUHkzRdjx8A26+09WXAAvXH2KIFQchlUkCClkWZ223m7t8nuGo/6RhHduzD4Q0nd55QDhZgen0cFscJD1DqLGTpZZ0DRC4FMtB+FXhGkI1XTh9cTEQ31noJw9aB8HNL0wpET+uxvrB7rKGu2pKsVbRSjYSSUXzSVQ8rPgv2uoch1VZRDWmPh1Jm6dkV1v5DSaBajE1K3q8+v6g/puP95W2yos1XNSalYcTQfilqipvAEcf12rx9gdcM9JF/iXZrFCjgaHTVRkIeWNpskRKJIMXGDFQhrIwos7j/wCIF9GSAxgFCaU4pSa3qWF3itNnNZww9MqWjYbf3bwOkk0TscFiyfeMTYoQenjmJyRVLEyWm7ewKs08yvNnLyRmdKgigUr9vjoxDotkmkU03HmmZYlWjPT7RL/ELNi4lQvoABot1JHtNpYfR7B3LBsPKFbmgXw+jc2Jnd0lt06UHv7nIY7RupvH66+ua90S1to
*/