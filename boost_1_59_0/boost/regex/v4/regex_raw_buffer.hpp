/*
 *
 * Copyright (c) 1998-2002
 * John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         regex_raw_buffer.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Raw character buffer for regex code.
  *                Note this is an internal header file included
  *                by regex.hpp, do not include on its own.
  */

#ifndef BOOST_REGEX_RAW_BUFFER_HPP
#define BOOST_REGEX_RAW_BUFFER_HPP

#ifndef BOOST_REGEX_CONFIG_HPP
#include <boost/regex/config.hpp>
#endif

#include <algorithm>
#include <cstddef>

namespace boost{
   namespace BOOST_REGEX_DETAIL_NS{

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4103)
#endif
#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

struct empty_padding{};

union padding
{
   void* p;
   unsigned int i;
};

template <int N>
struct padding3
{
   enum{
      padding_size = 8,
      padding_mask = 7
   };
};

template<>
struct padding3<2>
{
   enum{
      padding_size = 2,
      padding_mask = 1
   };
};

template<>
struct padding3<4>
{
   enum{
      padding_size = 4,
      padding_mask = 3
   };
};

template<>
struct padding3<8>
{
   enum{
      padding_size = 8,
      padding_mask = 7
   };
};

template<>
struct padding3<16>
{
   enum{
      padding_size = 16,
      padding_mask = 15
   };
};

enum{
   padding_size = padding3<sizeof(padding)>::padding_size,
   padding_mask = padding3<sizeof(padding)>::padding_mask
};

//
// class raw_storage
// basically this is a simplified vector<unsigned char>
// this is used by basic_regex for expression storage
//

class raw_storage
{
public:
   typedef std::size_t           size_type;
   typedef unsigned char*        pointer;
private:
   pointer last, start, end;
public:

   raw_storage();
   raw_storage(size_type n);

   ~raw_storage()
   {
      ::operator delete(start);
   }

   void BOOST_REGEX_CALL resize(size_type n)
   {
      size_type newsize = start ? last - start : 1024;
      while (newsize < n)
         newsize *= 2;
      size_type datasize = end - start;
      // extend newsize to WORD/DWORD boundary:
      newsize = (newsize + padding_mask) & ~(padding_mask);

      // allocate and copy data:
      pointer ptr = static_cast<pointer>(::operator new(newsize));
      BOOST_REGEX_NOEH_ASSERT(ptr)
         if (start)
            std::memcpy(ptr, start, datasize);

      // get rid of old buffer:
      ::operator delete(start);

      // and set up pointers:
      start = ptr;
      end = ptr + datasize;
      last = ptr + newsize;
   }

   void* BOOST_REGEX_CALL extend(size_type n)
   {
      if(size_type(last - end) < n)
         resize(n + (end - start));
      pointer result = end;
      end += n;
      return result;
   }

   void* BOOST_REGEX_CALL insert(size_type pos, size_type n)
   {
      BOOST_REGEX_ASSERT(pos <= size_type(end - start));
      if (size_type(last - end) < n)
         resize(n + (end - start));
      void* result = start + pos;
      std::memmove(start + pos + n, start + pos, (end - start) - pos);
      end += n;
      return result;
   }

   size_type BOOST_REGEX_CALL size()
   {
      return size_type(end - start);
   }

   size_type BOOST_REGEX_CALL capacity()
   {
      return size_type(last - start);
   }

   void* BOOST_REGEX_CALL data()const
   {
      return start;
   }

   size_type BOOST_REGEX_CALL index(void* ptr)
   {
      return size_type(static_cast<pointer>(ptr) - static_cast<pointer>(data()));
   }

   void BOOST_REGEX_CALL clear()
   {
      end = start;
   }

   void BOOST_REGEX_CALL align()
   {
      // move end up to a boundary:
      end = start + (((end - start) + padding_mask) & ~padding_mask);
   }
   void swap(raw_storage& that)
   {
      std::swap(start, that.start);
      std::swap(end, that.end);
      std::swap(last, that.last);
  }
};

inline raw_storage::raw_storage()
{
   last = start = end = 0;
}

inline raw_storage::raw_storage(size_type n)
{
   start = end = static_cast<pointer>(::operator new(n));
   BOOST_REGEX_NOEH_ASSERT(start)
   last = start + n;
}


#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4103)
#endif
#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

} // namespace BOOST_REGEX_DETAIL_NS
} // namespace boost

#endif







/* regex_raw_buffer.hpp
WOr+46ceR5dBt/v+9tkTq1VBF5XCrqyOsl0Ta4+sZcQrd8EbbM/DtYRvOaTupKTvrsr5nlZ6uvMVaZCRGnR/l+e1tREu6vxf0qJJlv3yCSGxs7uK37yZmp7sm57onRpnQb0DwPe0JOUE6BAqdj8hsSPF7qRGuqzseQuKPXCAHkWvuNXw/AQC7VlfU9PMK1J2FkQb54cbPI80yA/ZnuWvm/xAJ9JJy++qhssZ9V/3fep80bCutorV219aWqyrq2Zjcy4sNMDypx12p/UdrIyOf69nYqJtaKilqblx9+6dlpaWNjY2Pj4+QO9xcXFkMrmioqKtrW1wcPC9oDsuqEtDOy6fY7A6IWJHe/oFndhfv1XM6vO4jk7p2Ht1PD4XalogPEqXA3VpVsdBdBRQn+dzdEqXYnUiiM5DhA/n0nwugegYlC4B5zKShfPRaSw4R6F0wnDO4yDCRfF5DQsk82gKUSBXyOc4HI4J57LsvVAUh9JGxMERd7i/r4vZwWTw+NsYFotVVlYWFBTk7u4OxS54PEZQ6YILoL2Vzhjo73Sx2WZ9ePnFvSutTJecNVpkbbro5q6P7+xbfO/gEtfDn5KOLPP+eYUvcpy6MujiKmTlfp2/cue/wZbqvjnTWyXbTz0vUAN5yyFKpyxhe0XKjor0Lysy9zcV/cysdBjqSM2IsLp/SQlZuXtslVu565B9VfOCDIZ6yv54+3pmenhmij09OQD1/np2jNWalosQO/qvZ0El9hg35PwUiN3rli6tMnigLbaNat9U9Ftd/uFXOfvyIz4viNxJTTUrijPNCzcujDTKDzHM9NdPIOmFOmzzvqJ99fiGiz+urCzNbG1rB/zmcEYcHW9u367u7//I0e6SlcU2RyujC8e2m+/QUFffoKz82RrlVfv3779z546dnR2gO9R7cnJyYWFhXV1dd3f38PDw30d3XFbn5x99vSxIApQu/QxMr5DS5ROH0tH26r09XVDp4lS4UUendJmce8MncEHiUPp0T1f7fHa2z80iKc3n6GQuTNFGXZSMNzOT3Qvhc6ycncZkcumkz07x5nOS18kQJhaTS+WETNJmJsY6UGkchcxH29tasFKCxpunxkeQFNE4djZN8TgyiU3jCHtjJp+6RamIvaVydIjRAskmmNLsLaRuwjnQ1lyHmvSmOihnhdlPb3qlOIf6uqhlxeJtDPRSSkqKo6MjhUKpra0VV7rggpKvqakZGeNF+VndPbc8+K5aDEkj3kMjyknt8ZX1pJNKToeW2e9f4vjtUudDn7oDup9cwT9OFazclfkr93WJzhtS3PhrGV/RWiZSuyRWj5JkXIF8+cTe+gILOsUGsLmqgHTv0tpAR/7K/aEmeX4tA8QOxa4/xCp/+9cclPnszMgsUu9Dc3NT/cyc3CcLJXaNECd10pW1Xr/r0SpDBhnxjMo7zcVW9QVHa3O/K4rfnfrIhBxoQk01L034PDfc9FmEaW6ISZqvYayrfoCdnstFrTMHPkmPvM3sZNFoLXX19R2dnc3NzWZm+seOHQwM9P/16JeWP2gd+0ZNT1NJWXmlqqqKrq7uF198cerUKah3EokkWLxnZmaWl5fT6XTB22x45Y1zEWL1BeD6nBSxi56EwcB14qAuZHUcYscDdSlcx4dzKUTHA3U5PkdZp0++UcDnUoguy+dooD6OCI/M+eIJNYmIEJaj8fmMYiCXIvNRVMkB+f+Sdt9BTafrHsD/Pufce8+5d3bO2bWuCgoqvUqVKspid10La1fsBVgVUBCkSAsQQ0JvgYTeEqp0BKkppIcOASzAWbvunpn7prdfCbvvfOcZdseZ3RHmmw9P3iRIDlfPS2l0BrnM4bK80YxO/NZ0+Bxk4PktEgeN31oan1UGjdzyzKBnQZxFrbwSTfJZdNHsrLQNANrb2tpiY2PLy8tByWsUe19fH+h24eh4I5V00PXvN0+si7quR3hgSIrdXoU1pRLMqHizqiRjYsTW1Dt6sWfXRRz7LvzotzEnv0s6tyr1yprMW+tyFTchH0vWMhgD8ZvGEbY3ZZmI31iIZNtd5txZ5tlH3c9qvzBOwwiGcmMDTZLu6uVGqr7fM/ivGFLxQOydv/3+BRS7NKDev3z9IBpvBZ2vo9grk0xKEkwKoo0yHm2Pvb0xMciG05c5xy/ivwgbafOjNZ0Yqj/UWuRFTXeqwdpVYGy7il07ya7UbOe6TGdKmlMJxi473Dbprs21n77FhnrzeDw2m8MC5T4yAn7lefnqdWpqsomJnr//jbOnj5tv/ZeV0Soz4y1mZmZWVlag2y0tLX18fAICAoKDg0G3A72TyeSGhgbwkCp9NdOfpDui2HXxOZTVVfbqMFbX8Q6MUumK+Set/uXj+0l0patY/YNS6Z+hbqFDKF3N53ypzxUT4S46qtLRZA6ldBWff4DYnOvqc8WEudOCJHPFFPsc3eTqMl98yWcrJ7rM32hrXFPmsD6XaXyFJpfdSNFF4Iqp5XDG0DKKwGeRBL4ww6HrNBcXpjn0ATDZ9IHXc5P9z9tHBTxFG/D5/Orq6sTERFDsoMmlfa56entfjI6ORwWf9LD9688/rL5+eG2w7/dPrurhgwwKosQfb1uDM61PM2tIMwc9X55onP/IgOC/Kfny+sTza1MurcFfX5cduIGo+uYTKfI3n8g16yi07ipx6Cx1ey5ey/jyX4TOcsnp0bujb6zLCNtaJHlP0OoU06okAyreWlzsv31WFDsI6Pn5iY46go30w1jgi92sFrAfa1aZYlaaaFr4xDQz3DjOXx8TvIPTnz3HJ/P7wlntV+jNvkMNR9qK99RlujZkOFGwdiUxti35rl3F7vU5rjXpLtV456I4x/RHDiF+hiEX9If7Wrg8IUty2Gw2nS7+4Czwtaens77+ekdHe3c355Mnju/Z4w1K3UJyzM3NHR0djx8/DugeHx9PJBLz8/MrKyvBwyswv/Q+JEJ1ox5YrqMTHWa1rmJ1GLTrCHVEq+tw9eWPWl1C9A+aWbnSZVCHsDr8LRcIqK/kiouqz2GUjo5zFKJDLcxhla7DnlxN5ovKrIDlUDL/FZXlaltxaJNrshzmFgpiZsV5qQwawhUUVwH5AlIW1Uw+jZ55WUQTQg6Tpvq0HeBienp6U1MToKNGq8tOfz+TORJ1x8PN6i8/en17af8q/6NrH/qujzy/IfbKxqTb+oT7BrnhW0vixK8krcOb1aeZN6SDnjetwBgXPt6aE6yfHrgxPWBjtvhjuPRLQb0nSt7vmWD0LEu8lukk23WW7Owo8xpuPMLuvDXLzavOu/Lw0mpskEFOxFZSnBE5dnMV1mpuokNV7IpiB5ivSjashS52MwoOxJySalGLs6jCWpZhLIpizbMiTOMDtiQ/cOD058wJQLFHsNqvMZ6dGm482l7i05jj0ZTt0kBwpKTYkyNtqYSdXSWejbkeFXi3sqcuBbE7E+/ZBvj+s7kySSCcYktaXXo4HE5PTw+FQj179rSBgX5ERERGRkZQUNCxY8cdHBxAq0vrHZxdu3Zdu3YtNDQUFDugO4lEolKp4G9aKBRKt+7IryBGOFp79RVt19XvwCCJHUrp0GKHsLrmdl0Xn4un8Mun99I5MY6wV1ffpatv1OV7dcRduszqaj5HsjqazyVzeUzAlU4UmUNO5S5dS+YQVleTOYTPxfO1gDcinig+Z75bfiVQbM6Xdd2WK6dc6Sh7ctmc57Fp4inXOIrM38zJJpLGRbyRYcXkjgwvK6YuAoebEplzGYPLL2e4aDtwlTmw9FIs7aUFlMmWa1w+p9j0ftg5P8UcesFjDs3OTKtKb2ZmhkAgdHd3K7q9X+sMDtGba3KvHFrvbv2Xg27fXNi7yv/Imgcn1kWeXR93aUPitU1JN/Wwd/Txd7dkh24titlegTGhpJo2Zpg1ZVk0ZZnXp5lWY41L47YVPTYkhm8pitxSGmdYnSL5qJYc8/Yi245ix9Zi9z7KXkbruQk65kVDVNCF9TG39Z4GG6Q93FgYay4agyt26+okQ5Wti7TMzaip4j6nplqKg7eqTbWufmpdnmxVFGeVHWmR+IthykNH3kDunKBY0P+Y1XGD0XJmuPFYR+m+prxdz3LdGzN21uEcazD25Ajb0jjHDvLuxrxdpTgPUpJ7VpTr/XOrCpJ9BcJxUOaKYgeHy+U+f/4caPzMmTOPHj0qLS0FpR0TE3P16lUfHx8rKytpvYNpa2t75MiR4ODg6Oho8Gfy8vLKyspaWloYDMbU1NSf+bRMKLR/+f2rOCuwOrzYJfn0m06rdaXStaMidnSlS/Jelo/ioChdNVpi/wypdDWuy3wOFwnXkXAuz7Iyb5WBXp5rRMXqkixKAw/1N8iRQx2W5fK80sySLJALc4jIoL4gn7JA4FxG9HndMgc6XDoRWC6JSDOv1KImcOQofT6DEJiV+DSocfFcQaYUWVRkHj2vRRMTfNaYkK/xWzxoEkDHjo4O7UpXnIH+fhqd1d1KSQk7ecp7tY/DX495fHNl/+rAI2senlwXdW59/OUNyTc2YW/r4fz1UwM3E+6Dkjcsit5WjjGWlnxzjnlLrsWzXFD1ZlSCSRXWqByzvSLZqCbVpCHLsoVo11y4s7tiN63pJ17PfW4vJsRvq7/vP8P8VuEemk0J2n//j2axi8Y7AObLEwyqsaaSdxWT+Zwi7nMr0Oeg9usINiAUvG0NzrYixZYUb5MTZYW5ux0buhMU+7ygRNAfye68yWw5N9x0oqNsf3PBnpZ8z+Zs1wa8CyXFuSrBgRy+I/+hQ3PB7vo8LzJ2V36CV8yd7Ql3zVmMfi5PoOC66jl9+vSBAwcCAwOTk5NBvQO6h4SEnDp1ysXFRUF38IWbm9uFCxcePnwI/oD0xaq1tbWA/dKXMv1huqtu16ViR7M61HYd6j4M0l4dYruOZvWVih1pl66ldK29OorV1TbqEFaH2qgjKF3m8xUrXX2XPspjf4CVOez+HOrGC/rmXOFz2YTdnCPJHBQ4n02XTsR7LBAmh/K5LiaHkDmPOQwKnKfz7RTlfKmp8WV0hys25DppXL4b75dPub1pYnsjzkk2rQ9ysoZfiMb5PZ0tkJeoQQX19vYCt6v1udYZpjGYI5zuNgoh+sLFA+v3O/ztuMc3l/etCgANDwx/Zn2834aUm5tS/fXS7+pn3N+cGbwl++GWvHDDophtZRij2lSTxkzzljyLtgKLdqJlG9HiWZ5FY7ZFfZZFfbYNJdu+qdB1iLqP0XKO1xPWWXWXiD2R9MCJOVD5+3++fv786+dPy58+LoJiBz0/PdpRFGdBjN5ckmBShjGtSDavSrGowVnW4qwoqdZUcaXb1qftqEuzoxLsavF2FVi74sQdudE2yfeNcY9ceYP5kmKPYnfeZraepzX5dpYdekb8oZW4uyXXszHNrQ7nUpPkXBHjSAqzzwi0r8Z7UXO8SSneT0Odwq+sed6SLxBOAbOrVjooeemToWFhYc7OzmfPng0NDc3JySkpKUlISLh169bBgwdtbGwUdLe2tt63b9/du3eB8AHdwcMr+C40NzcrXsqE1uKaZ/HNGyGfq7S6nOuIaNeyOrTYPyFZXSl2JKivxOpyoqtbHYrrWkpXg/pb1cArHRXq//4oDZLPYZX+EQHnmkSX4Vwjcp+jyFyS17Isi6MTy9VxLg+qyZEiN/m8LPAUh8hrWVAoDgHyWY0gghzJ4SqZBllSjc7wVsu8WuTenlxZ5hSZUM3L6VEeY3BuTqRd7EuSp1MpFAqPx5M+kard6uAMio94DtOZI2xeb2dDVsL1K4f1Djj+7Zj7//ntXeV/eHXI8bWPQcNf2pB8fSPef1PmPf3ckM3EsC3ECAPiY8PCqK2k2G1lSVKrm4GS7yi07CJZd5FtOsk72kn2rSTnvupdg3UHGS0XhP3h0yNpUyP5E6ySSU7N3ETv4ivB+7cvv379wGM24B4Y44L0siKM86JMiE/MSPEWJRjL8mTryhSbapxtLX4HhQBa3Z5CcKhNdah86lCMcch7YpccZJYa4QGKfU4Iij2a3XVnpPUivennroofW4v2thf+0Jrv1ZTpWY93pyS7VsftLI10LnzghLvhkB/tWZO1Nz9xz4NLaytzbwrHQLFzNbgOuv3du3f19fVA3YcOHQJNfuPGjfj4+OLiYtDboPDPnz/v6empWLmDendycvL19QV0f/r0aUFBAZFIrK6u7urq4kjuQ4JHYbQ6Fx8gfNHM1ISQOynkLMyOK7br4rlSq0Nv18d/Q7c6hNIhxI7u81HFRl1q9ckxSLFDbdQ1rf52YpT/GUXpsBt1lb26rj4XTz4XNPmYLkrX8jmi0qFlrjJH3kv35yuRuYCjnEibc+XNFpnJFRN6W45ocvmUmPy1fEJoXMXhUCaXyxxN41oOh5x/YB8umVMcer/qRLQ3tLqh5gtQ4JI5IZ0s2os3MPPV7Fhv57PxUQFksUsPaHUgxqmpKTqdDr4Gbh9EPDT6CIvD7+9pIz795fpRA9DwP7r870Wf7+4cWh1ybG3EqfVxF8UNT/DflH1fryB0c1GEQXG0YckTw5K4bcXx20sSjcqTjavxpgDtrQVW4heoltr1ljv2Vrj2VXsNUA8AS4+0XeX1hAgHYsdouAlG5sRIoeTTEVvJ+J9jA4yib22OvaOffM+QEGqSFWmRF2NVGGdNTrQpTdpRkWJXhXOowjmClGMdyRjH/CcO2BAL/GNP/hBRXOwDoNj9mW1+9ObTXZVHW8kHOkh724jez7K9Ggie1KceNYluFTEu5Ec7c+87Yy47Jvm7lacdSJAsc7gcFpcnkPY5V35YLNarV6/AXwsgN+jbyspKFxcX0NtBQUHp6ellZWVYLDYwMPCnn36yt7dX0N3S0nL37t2A9KDeCwsLwUMAeCCQ3occGxtbWFhYgv9s5KXFxfFR4YSQ19fdtjA9qvgp1U3sulgdUezwF2BguY6+UVcXu9zq6lzXaZ2OJHZ0pcus/umdOOi7dHWiq6zTUbfoCESXbtF1UPqyTOnvoKGOIHOZz6WBwrlq0IiOtiqHlLk6zlFZDu1zmCU5KsjlLF+QZcUgV6f4CkCu5DcEwiHzRjuicZDXs2MzY1zOyDDqxWlQUENDQ6CjRCIRk8mUPqmq2udDWodGZ7LY/KG+bnL6gzu+xged/nZ45z8ueH976+DqoKNrw39eF3vx+5TrG9MCNmYH6xHDNpMjDcpiDSsStlZitlcmgxhVpBhX4kxr08wbcqxaiTu6Shx7Klz6qjz7a38Yqj9EazzJaLnI6rzF630wOhg7TsNNMrNneWVjDFJfc0J13tWMmD2J9yzjArYl3TPCh5pnRdnkx9oVxtuTE4HVQas7FSY45cY4pYRYESK9QLFLVjEx7K4AUOy05jNdlcfaig91gG4v9GnJ9W5M312f6lWb7FkV514a6UZ84Jrm7/LkvHPYeTd8uHNi4KbBnmqBcFJR6dIDxA4qHVRxZ2enonsB2r29vS9fvhwdHV1UVASqOyoqCvwj+Jeg0hX1bmdnd/To0eDgYCB88Mfy8/MrKira29vB92JmZkb7SVXwbZoXzQKljwtGFqaF4KdO48dVw+0w+3Zd7sN8Uogd2u26if3r5w9TE6NfPut0+0Vb7HK3QyldeQeGr1C69lQR+6/j
*/