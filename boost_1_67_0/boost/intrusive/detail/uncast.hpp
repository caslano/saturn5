/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2006-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_UNCAST_HPP
#define BOOST_INTRUSIVE_DETAIL_UNCAST_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/intrusive/detail/mpl.hpp>

namespace boost {
namespace intrusive {
namespace detail {

template<class ConstNodePtr>
struct uncast_types
{
   typedef typename pointer_traits<ConstNodePtr>::element_type element_type;
   typedef typename remove_const<element_type>::type           non_const_type;
   typedef typename pointer_traits<ConstNodePtr>::
      template rebind_pointer<non_const_type>::type            non_const_pointer;
   typedef pointer_traits<non_const_pointer>                   non_const_traits;
};

template<class ConstNodePtr>
static typename uncast_types<ConstNodePtr>::non_const_pointer
   uncast(const ConstNodePtr & ptr)
{
   return uncast_types<ConstNodePtr>::non_const_traits::const_cast_from(ptr);
}

} //namespace detail {
} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_DETAIL_UTILITIES_HPP

/* uncast.hpp
CZyFYtZDWq0VKlaSsgWKDHu9g+7Suw0Ic4noHbeJs23cfCPrUP+58A2zKnxpsFk6L6iJWuXRiMLc63Z83dYSDEdGYjYIautB0iijmz47aQQWVM9b08S/PJYcS+3JuttBxM/bM6vFsk7UXwV8hL7TkcWVBJJ3Z8l8J6JrUW3D6Owidgu9ptxuAoRPB+udfxKGymOFUJMgyiPnYHeVWIwY8VdwLHVWdekp3VYsQbAh3vrRz3yq1CNIy+0DWMGFV1HTk6PbsNs+kJOxHlTfxnPYR8OUG01U7QeMK0pRTMVo75TiGo/ZbbWYp6ZS6T6vmB1LcrW7iKbOpfBuVzFFu+LbrsTp9rmDMpjec3FVlXSg60pR8KHGVCunyDnhl7gLCIrKvJuhVQaOEmsxAr9fx2E/Xp52juLUcVrqv2g+s4V96YhyUB/z0xKbms13rMrF37ybifNPcTPeZuglYRTsbkQBh6KNJqH0ARUbEw4XEofplHaUIYkpKOxQJy6Aiw/4cj7HlQPrjaJ8i8iF6+lruShlkmVoiNXZ9AZue+I6FQeW6URJ8QQv/8C5dN6nTO66k7Nxqc3Nlu7MuP1Mi81vZcT02bWM7VXVKBVTofArCDN121wXspf30eqb/OKtXi5Xe8jXv9aHaVgv6qrhLiNXjKK/cdhRkqOnBQNzUuOjYnHzqAKvr03HOmn3347Za9wOnY3yuvI41dPSZgjY7a29i0960QQXs0odtcFKDXILqScv3gHUdFbst9s0kQRcW2GUDFrYvHYlzLhWAnwEJxBXaDIqTdQ1B956N+GV9dZfReeBlA1mgVrd1YtGQuCoh3D/Ka/d/a7B8+38uOnmyxbf3Z3ysPO5CPH9ir5gCZCtzqlEZ8tpMnUgyFluQ0h4pgstwAhCyYRNL7pgjDL1kz7smua72HjjRUZ/VEzJPmbk8d/uTQH99GOmZcljofSQEHbA92EgGfhwIFcssgSyrQb196dF/wd2xn6leMuMHcF0VxwhepSt1Um6oD+UGWgtmF0joNUJL6e0ltKsYv/DIhXjdTpMGF/KL788z0hZiSd9pemucVjqdR0KUDc6UlK7O0NsU/scoYOO38fuQT++H1syjwYSefNEtbplRwQ6lN+kiQLqB26Kd1eOyOZ7CBLxVuAd//sQglo93lK/Ag9M5bk57rd7KVvXPap3ElSmhVIqqD29TcWny7WS3ELfwGAIgvBbT32M01noinLpgwyDA7Bf+c/l3uNqo43G7DS2upHr8e4I8nVDINiamddop0w6jXhPHoS+CqLUVSM4/jccYCVvVptxQQG8bAypca0L/WXq/DIMthf9/cbKHmqg8ArFGJwllC6PEMOkyH0d2i0884cmWVQEfst7QeFrnw6ALP917qMYzYPaK1uBMDE1KT1aiMQReHrsMfCCz+q3fABIaejd+dUhp3NxShkc8Ak/25gyXyitM8Pbx6/RJS+lkQeZVBi2ZBgPPhPGj/LiL+MaFiiX/bJB8fkvfyUFtVhvfKiNHz0VQadCWMMXlOgbI9iMCmniV/URvT2eV2SC2cyWqTBlKgk/zbNlnZHsVtKK9+lgilX141FQ162KEp+0rLpZvb0rgPzEOn6F+FQnt7qnQRw0LcV73F3QPe/lOUDALBVpq23FJCGICHSSxUVRizbj35zq1Bu9wXEi6tuYnVB0sUrPTPEfkC9JotlIwHsXbXexXQBFKQBr9rU7tz7nOZSCgS9oXcWPP9ajp2tIB8Rw/n6UtY16KViPkx1S8AIaLAIAYr2so0zrr466Fz/jNFB7F+t+3PRTS2Urteo8y3j/JbqC7RfJ7UYv7NN7H0i0qBDvkgi8541UxDkeogCSaFz1xSkJbE2zWrK3dND2d4JV8U8V7rTIRxgCjG5dkxuG+4/qOZCuKQL5iZJbjCunqqohxpphkgaERzubsItR5t8syqa0XzgSndtToz5NRrb9Iah7ivnV3NVOTJjZoxHol0qhNCv218retOCEgHftPIAf0LeZROjym9hE3WyxxaupTFNtGAhLv2m0MwvVLHDpeykdSynKoWibcBy8Fa2ElR6Nu8UDN5cHCt3LwGVAx48NFlKIFvONDyefVDp7ldqWlLzcVTnvS2BPQSw+4AXEXF3H3nFHws/r0cXqauwvvXVKbecbpfjWE9nlrr07pgR1h1u7YhqP03XQstbhu/j0z04V+CpU8fE3Mm8KJVoUCX5myWzrdnzbW1G31epGWcwyfOt6hj3t/4jzR2CXGfRlTJilxaKTUiDRebO0xVmoVNp15MkJzjjjJVMNPjwJiAciTqg0sp55MCG3tZJtW/EqASrOWJaOldVhIULF7QdXmjLWTCcphTGkBiy8TIHlhNrV8FFD9EZy6Ua5n8cclQFZMHzKImkuL8Hc4vAelHjZY5zRmpYnhVJl1v99BjLZShy9bSWz8tOSbqsVfGahDAzbJSfIZyW3SBftelQpRHgKvfypTKWTuDXxipjEBxWxAPyVs4QpSDajVJscf37MHgKJRbDMCYvpAQzcWwhUHT5IPAke1TvHtWme5QJrSSFK2J/jg3W1yOjsJxiPXFjIrhQQwciL0ljmGcWevmSnn+EdjhFBUnqfj4udB6qAct1qfECUAhMODaJTtJUrf4AdSl6ttKbMZdGMz2PdP1gSb/CNcdmshU+SvDNjD/L9R91CuCDHNNLhlGcxpO8Yy5TD4IsvA501AAmpynxcK7i0Y8iYmeOPMbVfTwuFgEnKYoRelh9zcYF150zxjjh1mDBZNAee412pb+i4ULhruL2ijCMJzsYLxDVIaYbT4MQLcK6tlzZoUiu/jwNg/n310auEvfDmiq3lXWVZWfccjnfjeFrC8ToL+Fh9wbCJxzDsyukFmSFowXkW43ZKWCd++dLIvSZahVZoiD2mF1xUFx9qs1MaBRdK2fHWLmfX7iI2nWlnckdKOaDjbVjLrScXfXAhhF9hCdwHxBV/xxhnrKCcXCKuVt2McrHZ3qgconmqY4/W1KtmuotU7pJ54OF9p3wUgT84gwU4XDvREOdlCQKRzbSu6+K9twDVGs/qJocAACQNRNDeiwNJQd0a74e8q4AdTNf53cnaX5edNWlrsS+DYRSS1NEKndDxDvtaIdOUQ5UFwqt8lqcvjYCLe9ijJKbI518TQzG/oPs02eX3RJaJclARw22MPTOOCnR8zlPCvG3htFaijJ3ssv2I9VGzvxyq0r9YMnRwiBBOtlA5NIQ7qZV8NWWaZULWzx7WCXS4js8Zw1uPjc0WzglA/0ZmOyzejNnyYqLGsax4InTkgVdag4Czkm11xDdch2pMyL5WrocHSapFP60qd8FBx6eOgNubwEtzSD0DSB6nj7s8N+OwjCm/FyusXB8rCR77agUGOb9ilnxmZgpWk9vEbRHC7qS3yefNChsGLogiWBLZEplGwJnwRHvTcgvQLPDKLUwsWvSQ4i5ixlYpPEbcE/MaR3TzlBMUZZeuu1RYkKtGqkqj/tSNNjlvkXWvby/uKXbMEtnbZy5hEjvMDrUJpCGZB5Nbcm+KiuRclxtw667HcM3vDEltPro5NzNczVx+8kk1CXUyU0bHOVPO9CqugFaya17WxrGSLZnuwsRlZ60htSRppEmEpsA3nsaCXG2FjuWfIb/Y6E/OPuOFwm5tRTJHp4ePHK3qb+yWHkJf4DFEMEeSz27rgtSWYz9CGA69ZmbnmCpBvb779ElO1QTmhbMm9x0f6kod6xXNFlIhirBgua1WVqpMEvnid+NMk3tZTK813cHi7kaamQTe5Kq8LGuJVPYDyP4KocjOjFQnyrQftpGX3I58t7N6VSPLcxX1BnHY1nTMY27Ds54Plz49GNdFEfcDtBpMJfPv/jcfv7PVvx4JD49mTmydFzM99uyzJ2IuDUG1E4cGj+IY1bbv78aLQDcxoUMi9i7MJcTZHzjEHFnZK/AM41gEKUzDvr5UcUDDIE+NHWYSMg6wekQZ45nHqfDSpiZavTaphPhykCPaAHfYuhW7HCC8Bg04Q0kXVX1GUh5+faO6CvwdhnsAMemJToWapjQC9NrNwdp94tMMevZFssakzNzWU1zR0miJbkIv6GLXRbyj17mj1Eas5C1sBLIAnzi/ZqmSDdnTYUPc9Cc8UO8EyrJUciwSKkZ3E/ZpHROCZ+LoVAWycHTRwlC0DyNulLlWNH345XLYBOZaABV/CvACusftp4QXJShCRUeHGreHXdRb+Lbkhox1F7yjnJhtw5YjQl48ZNGy/+x6Yg8Kdl5p2rRe+jApIsSezF2EjR6Gf/bqtXKzzaQtuJy9yzsAPl48OMLFc7YSVB7rqg/idDwRbnTcJ554YzaMna6xjMpxnh5dvm1kVqz508EMU1MOzaoym36WqKuNc3JWmRoHH2VxP1pRjr9fmQ2gva29rMUoo8F9hd2ug5+Af4LaPuNn1iFiz2xXZjVIEGM26RSmIhEetGn79MkJlh70ORtJyNvK+Pdyd0lxSvQ1RzE29Zudd7ilIusNR/2cP8RUgNTD9WCnPWe1dWh7pXUTYeUl7/RUuvwmug+6r7kjcQKPuPy3SbHCYPzcILXZWnWg7Vgp+e083g/+MazS+I3wD+KQPeIBfxavFo513vsr6J8NuLmzy3ZEPYPTfFNrAlcHxcf46AX4lzxj+iWJYuzoFxY9zOhyMlJq5CWhtTaKdRtoLCwXi7lg7mNFp1+nuqQd5QxlaEHG6FomUT5Ietm9QIJ2Xu5GoW6kWhGzR2ms4mrLbh7aUMWeuDkCr55WHmq6jmx8Wm3yyF6Y2FpBsQmcCwrGO3Y1VZyVVgOIDQVFOvjRHo22FJOqi8tzGiQLJhZ83Dwd7EnVB/Nzj4PCzoo3jxd+UmM13tKTVte/Da/2xXqz/W7EpVMxktFRafGKyVX+G/PyagKOVrTFfCerMXJDxrFbXEXxNssDs2Omu3yQ8Uxlpzfo3JG29sPIFjRC1K6Qk6NWVS6OmAuogRd86hPzYppxkLu14C815VCvi/fWe3FICddV120dVridQJrxa2CTVLCToGQrEX7KPGFfvfVFHGV4t4dO5erxoJkycQwot9c1LQZlcjsYGKX57MrKouTCqoOaL1yNmmIJ/lzlcXyvh7WKLPSlUiUzcgeP3nWL047NREfHTtb1esqFVNJB7jLOWvF7bA6+pQRXFHZ3nT5Uhgusb44ugVRFN1DBL+omwQdoUPEZqJlmFQLLhXOe0NCuZVjMo1Ch5QR9D6kMO7U9K6ARRc+EXqHtwFVjaliO2+jnKfjUx29yoHqKWHiC3cdppMoGXFxz3ONGOWwnum2WNcb0G+nIFka4R/gZyTzp4PFdLlbdz+cqYvY6eUksOXm5W4ftVhiPR+KVQVSVRajHupIqkXx0ubNPTKK89TG0ATrPzbk92EKMZmljMuwk3bU351Hr57JPuZi50EjXP7nppha/zagvZ+hOBzdUzFQn6NnkbhwYt9jesdgbCj9mvVSD5datdLa7wi5t+yW/gTRZ3iQmf3Ysow1H7A7XhewtB/aipEvtVKxmD18XtyntePRbbTfaSzJyvCvaXUw9wFcRuBxUzaUTDhnBLlGqRIxcEY8FI3u+Wml1bCPUegC55sscuhsJ7G3Q9Hsm/elZgvFcrhHrfIm1sxGEXE0AKfqwPRktPqcZvHFvjkaJsdrCIh4SjeRUwiDpks3iQhQKmcWFdh23jh1bD3+KoJpsBkuGpda0jljizCr+qi67KHvJQG07XZRrMIG3Hf6ghNTU58asqNMFDURln8V/2DLmfEfiBuJi1tW4R8WyVgjX3JLsva4V/grtRJPa0wE56ge79rTbEkWSH+BN3bhyhfWZDhqpuzTOousZE4LrX+glrvyOVfN7/fypsYXBGSLU9TxD3Xk0UYnbIEInlXSFe6KnxiYmt3razOSC5dIzIlS4G/jYpjKzdD3FtOV2VRMSki4TFEzLGZdMijQVavJTC3pnm2+zGl2OgxHJuGRJkGH2jtZOXD9G221Z4txPYOPPXhnG+d3D/bSag40W9d0tQeqpjSn7/fqwQ28QoqbbRKV8qxoTE916o35lvJERwzPTQjL6ntlB6ER9VsmT3a52Jrz9RPbsDcbX/YPqU62heGWvvo2C6J1ePWXkhcLnMLISl6YBi5/j8E8uj4Ra5EV4eqs8qp2O5nYTNljBy1eeYJU5dMeT1Gm6JXvtXcvnBGTIBXVxTKnB7UVGJl/RZ1t6l+jvEou1k3ncqCCTVf1uTN9AFFyh4ZmsATNiZdMU8rjGmPn6jt2kxEKR8IkipYnNqQVl0RXbE2ZBMhbqw5aqXXIyBIsezb5h83naQSbNsTh8a1ytGYq6J4SgNWl9MfG7kdOAepTYUJi25LVy0ZMVzGaKi5L03PDypXOL1ddnzLjtTdsMqg5ByWeoqycLTspoIzCgpdr6x8AlEymkygxoOcQrIg9jq8MjM7EEOKT1Dvxr/dIQAlgdiCiImYvt0Zk3VqW764U1rpsHBFQtFKNTQz57w0Y3i0M3TbjZ+y9CudeyxEpweQm69g64MMY4521HYbYozcsnc7R39Zr8I7Zh5DE5KdEwjKaPSPtMkAuSXQzpXCBu66p1FGjuH7mTgH2DzU9GagsjNBpx18hIIs+Q4DtK/zq8A0b2YGkAoWua3NCZZwJ2MO8XKrsPP87AA5AfgzARvXnDTMezgTFKWJJ2RmjNhaem5SogymvsPo7zQPjuLEZbi7PMQs80GOfVL8PIYmrgaBIgMHQI9K8WN9NYUUUVR/xq7oonVEp7icCW3CdgHSo6OpMTmNPjc6ITGFeiJ4uR3qnOZnF4GFa3ujrph/3mCv+Umw8bqoXCWUqCPrqtddP4lZaGV5vPO5OlkmKkYfKOA8isoeIVLcPIceRv+LH78i5zYimeRSqXmEdGTjZZ6qoql2kjLw+BjRHNSFoJcdlbVsNeLLb2psaHG0U6IGA/nDk4xL+u/TA2i5ir0tcBUnHRmCA/jteoZy3KIVXX+uU/PoeGZkZlXICB6lGU4MC6fI3fcdmX6a66d2YplWxWX9c4r8E3h3TXt8FJvA2Ei3Wcs3YKOpdP3rpR1anEg1XXBPDuRQPZSFAbfJg9eUxd+pAl94tgsfalmXsDC/VxNx3yxPRnyZr1Xlh19Qziu5uBWc8WLGK2fsEuTLMOLX0EJmUqwiZk2nQi0kVYUDj4pRlMJlrZimne6glqoDJY7LAFhNl07UlpKmWOG/pgLoEMYOGY8xBkGk63efzq256IUi0wiR/GPEPeQzcN3HFL+Y0LIGXp32bdzL9RjuKHcCu3lnHAGk5edfW9q8kiQj1uoBFvHahovEPJ43KLxtbz/wBSwA6ilaez4AZQ9S9zYV9GR6ilmP+P/uJAiAr26qs9AZe00tV9XBJBEKNutfkzCR1vR2jm/DDoKyUECAfKGELMFg84RqyZjYfC+JyZEv57h4Te/GWrPMh7jQFxf2FG6O8jCHmPZanZRNqgLdOkwIE3hA2tL7ctujub+4uxCKmAfs9locm2dOS7/rYs9C4sPmvZO8lb5ciFJS/G3+JHfijXok+VX4oXZP/2C3g8yhG/LTmPHFIKPH30qf3tP9QVVi3SAmPGIaFQujaWkWFvEa0UxaWLR36N3VAkDJhFOxQ3ZA6Jw9JF7iglnGzPvybAZ9bTEcTKic/wmKoNSIZWa5vN6PVtjLeZswKKJLxudjsHEnH/GaeQq0N/uqVgzwFVY7wWBWL6or3gUdOam9alvL9K23rVQtgP3e6+tUA6E4qZ0lmeCewjSpCTMehxG3pMscYRIcKvl0ET3VgqoMxz6b9nHM/oxhCnlBDxwExDffofXBZpDCtVwOcDz7DY/wfcOjaaL3ziTn8viEbN/FAj+h/+8wv0rb4/22nLb9/3fRZjYvSzzxO9iN/7INh/9in8f4+03iwNAbpnJG+M0Y87pyCPbxfC73GSsVpGBui5aUe109tMXtDxsS6ZLgYNH9Lt2nauT58BCQp/yqUGH8eM+m9bsgTIG4D4U2F2tZ4R42rBTrpeCXeeGlfR96WtXBhOsa4clc0rf8eJ0O+04hImqVHfYzRf0N434jAyRad0JoIYbC+YUlDj5b0i8lvgfZ0SzjarvKnWbc1yWGZk5Q8CgAgDormzF0OZoKpcB7Eqx1mfLWrE4kWsM74nPkrTs/Mzn99OGyms24hpVy07X5/ISBHHEmT3khs+Luvn5Ib/InPPtIR+Q1r1bGtzbJPuW3/VIq3aRnqpPS5riRc0et9wPgZsK3qS1PO2VE4onXRgXSsozG2YToAsIY6TLUpLvZXNHV7GxZCOz70db1JJZ247Heo5KFVei3FOzJSpL/BLLxFVKO9Ky55b9hV7ejcrGta9QxWta4oFVjy35FLYgcpOvS48qxTkIyR2R6I5fKiRtsXXqps+lYLDxp4Eb1uOrS7P3AiP2Ymn9W1ngZaPVW+Osu3E0iNRJat3XfSrnL04esRyIZkrYAzGIjxe/UWhgwLmDlwUoW/tuVVcE2jNeutuw7u4wwm3NtcITXP7JvE7NjWni5QFPG5aDbzL6zpT/RjyjSG35ogyvT5rXV9KScF28/D7xtcQGezECthtXjtuv6roUBMU8epfoJ7aNY043mXyjTasjMz9hVKIcIwxfJE4ivJlEGt1oPclzJnuuHgI3OYuBXFy6hQ9F2XGY4QjiNmdnBebW7QQkyyv67VAF4ewNzvoJGmDHau/xDO/OJznYsJlGWxenKbHcBke1Cx46QsoaMkV9JXjbbC9XKECTEL8KiHulUNb7M/CK2rLSNNXG7rYE51XkCpnNyK3tHz6lwJKPInXwGNNrurc7yPb+WncfmkDik4zfSlUx8JoFtehsii93V14BcwDDOVphcUJFIaP6tpi7Y1Gex256bFpm7Wf072Kq4HJdWpPuMdpbWSqIdRZl1eRsbxd2bGq21mfuCDbbGAVmpmH6L0wiFZvxbFGJ6KOqrllJJI3XFeyg4nevUsFsSKVO8BMULYkJ4KbV4K5lZUt6uIfuWnEqcs6n8rldW/VXuBodbWcGHZ7B28K5V6rzQWU3K7S3V2b1NRl8s1wxcPh/FhXNLcNwKt2J4rKo+TYUzo6S2T6tDllvKlHT4azrJAdv16/YSo4wfnG3V0hJu9DEWjzGRKSpwgD3XlNVRHXDxB78yhw0fa33u8rPmnjsxRtAe/5KR3moWE=
*/