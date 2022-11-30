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

#ifndef BOOST_INTRUSIVE_DETAIL_IITERATOR_HPP
#define BOOST_INTRUSIVE_DETAIL_IITERATOR_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/detail/iterator.hpp>
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/detail/is_stateful_value_traits.hpp>

namespace boost {
namespace intrusive {

template<class ValueTraits>
struct value_traits_pointers
{
   typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_DEFAULT
      (boost::intrusive::detail::
      , ValueTraits, value_traits_ptr
      , typename boost::intrusive::pointer_traits<typename ValueTraits::node_traits::node_ptr>::template
         rebind_pointer<ValueTraits>::type)   value_traits_ptr;

   typedef typename boost::intrusive::pointer_traits<value_traits_ptr>::template
      rebind_pointer<ValueTraits const>::type const_value_traits_ptr;
};

template<class ValueTraits, bool IsConst, class Category>
struct iiterator
{
   typedef ValueTraits                                         value_traits;
   typedef typename value_traits::node_traits                  node_traits;
   typedef typename node_traits::node                          node;
   typedef typename node_traits::node_ptr                      node_ptr;
   typedef ::boost::intrusive::pointer_traits<node_ptr>        nodepointer_traits_t;
   typedef typename nodepointer_traits_t::template
      rebind_pointer<void>::type                               void_pointer;
   typedef typename ValueTraits::value_type                    value_type;
   typedef typename ValueTraits::pointer                       nonconst_pointer;
   typedef typename ValueTraits::const_pointer                 yesconst_pointer;
   typedef typename ::boost::intrusive::pointer_traits
      <nonconst_pointer>::reference                            nonconst_reference;
   typedef typename ::boost::intrusive::pointer_traits
      <yesconst_pointer>::reference                            yesconst_reference;
   typedef typename nodepointer_traits_t::difference_type      difference_type;
   typedef typename detail::if_c
      <IsConst, yesconst_pointer, nonconst_pointer>::type      pointer;
   typedef typename detail::if_c
      <IsConst, yesconst_reference, nonconst_reference>::type  reference;
   typedef iterator
         < Category
         , value_type
         , difference_type
         , pointer
         , reference
         > iterator_type;
   typedef typename value_traits_pointers
      <ValueTraits>::value_traits_ptr                          value_traits_ptr;
   typedef typename value_traits_pointers
      <ValueTraits>::const_value_traits_ptr                    const_value_traits_ptr;
   static const bool stateful_value_traits =
      detail::is_stateful_value_traits<value_traits>::value;
};

template<class NodePtr, class StoredPointer, bool StatefulValueTraits = true>
struct iiterator_members
{

   BOOST_INTRUSIVE_FORCEINLINE iiterator_members()
      : nodeptr_()//Value initialization to achieve "null iterators" (N3644)
   {}

   BOOST_INTRUSIVE_FORCEINLINE iiterator_members(const NodePtr &n_ptr, const StoredPointer &data)
      :  nodeptr_(n_ptr), ptr_(data)
   {}

   BOOST_INTRUSIVE_FORCEINLINE StoredPointer get_ptr() const
   {  return ptr_;  }

   NodePtr nodeptr_;
   StoredPointer ptr_;
};

template<class NodePtr, class StoredPointer>
struct iiterator_members<NodePtr, StoredPointer, false>
{
   BOOST_INTRUSIVE_FORCEINLINE iiterator_members()
      : nodeptr_()//Value initialization to achieve "null iterators" (N3644)
   {}

   BOOST_INTRUSIVE_FORCEINLINE iiterator_members(const NodePtr &n_ptr, const StoredPointer &)
      : nodeptr_(n_ptr)
   {}

   BOOST_INTRUSIVE_FORCEINLINE StoredPointer get_ptr() const
   {  return StoredPointer();  }

   NodePtr nodeptr_;
};

} //namespace intrusive
} //namespace boost

#endif //BOOST_INTRUSIVE_DETAIL_IITERATOR_HPP

/* iiterator.hpp
pF+Eos4/fjVO7KT7D1W/E/zmto8VrI+mJXkRSGcwvRhT2+N+wlaRNszR8oA0l5p+DX11s0/1TWHnEfmIzsrrBPtjnkrADeiKMj49iHdCCGS2hYpzdMCjw3v1sqP9xk7802Ksw9+PftNWSq0vSIgbfG9jkQt4mtdR6fHDwjuDa2C2bBmbfriNLCvJhVxGwUVWYE7ciEFUVsy4PK/a8bv8fhf5J+mcL3InIbHPdjM5KC6aAq9eL8GJBOnURyayIf9gvJz2UoNrygcvG3Eabgcaj1a9OwfcNdQC0r6AJrZNM55gaTKthqdPb8KDDkSI+GOPz26lU2YU2WOBxTHlCpmxPLz9mHbkx+JUCJwEqr/PQX0xaGVJEWdbaudroNwHeFEvJ8MGmRim9SEEqweLYDEceFrjseqC2jm7uhFPd1j3Tw80EHiGyzDh3pDsmsL64dzJruAAUpxLX4rsezvgrdvr0n9Ym3JWe0/nbL8fS4GB4qdg9A0fLvP8SjDuyXVpnFFi5yYYJCB8bsdXYLu2fsaGtUdIgtTfOcfSNUng6vfeJqhaPB8H3vxe3ZyotiJJkqRtkFpOghIaZgtlTF+bkdVTVoX5bBxOZGwz+P1oOBeI3P4uD9eiEU1NYjiX4pjOmEJ76gTZU2X6FyeiBilEAqvsCQ6f/iT+KSSx215UjNBDXqi+MiRfrpxniTEwLuMZUAHXCfZUXp6ZAzVSRy7u1K7LOBI2Il/pxHGo1ehGoWtY6UqA/Brf5hmDeR5Sl3hnZKcO3xdzeuCue9weioB/Xk3OEoD0FjbcQ7XMw7O93C/QtLcMxdO6hIh4gFdcWkBVwPIerEGqAz1/tZNCLxRdwmpLSV+D8q0Vv9CMf9p3qWKI8q6dt4cRcWKWoxxV+EA6tdbBw5t8SyJ3xx0NbbuBcAmO8DraWdrPrJUA6zlVsmGYketSs3X2L4lIjYhHMKkrkjfCstoIfKEBTMHLWxFY4FV2yvg6oRk5j+SIcBCrmwxbqj21778Fv0dO7vZRzXwCngqL6HEwhRa/HUVc65arj6sd8L7mELw++SEHw3cScqnWkxzQV8r0bEA9Dxo7TScuzOddolxIBQfpTcDai7vmnk4nmqHkMrbj9QRr/Ulf0aN4U19aLs8IJony2/TpFTmxdCP0v9zI/qNgowoU7jMFiPbRWQ7gFhJ4uorxr+mZrYqNf73cw7ev0/SBa7WDpLjmINzb+ajuvH7/XVwchi7Ot8NWqXC0cCmHHTfqIN93DhK3RYdvdg9aTAjDlcH74p47wq+67okfgXJ2VwrGmdI+isqEFErP1Z9x2iRHUFSecYdIkR0wh4DWUD8zEHuFe+fjeLyhxEhX03zJp61ssutnW0Yxeah+1jD9fkrecXRolySs6uVNB4qryxLqdQPF48ZA8wYm2ONwYwXHXITxNqvAknaggUikx928ndPfloL2XRQDHix9Neu27po5TI4NH3pnMr9mKmH0nqmi+q9WPBAW+Vf5zOIWZ6w9kJWAiC78jocbwxy9RKdHiLWrDE80zf4x1kqeS5SiU4Kk0cZhoAvYj8tgsUv/1+jOt/Zsov4wLsH0/HqjsMKzoYyQ+HxBqj2VIQ7gyBpjcBYtRborZdxH9CEmL8TLFezDn5kglRb+sz7ceagOgBzYeqipQwYFtiBTOEXKFxXHzGsksBL7Pue3RhS74byqznfpB0DzdBtcwVcmDcKDRlXK/tnNe7QmvhnPWOH4SFVXcTXexmU6i4hJ8NIqL+B9ejUWpybkLe36Sh5/BdIiVDEhtfQi6lh54XDSR55sOjzPT+OBEx8htYQi6brTUF+szrQBi2Y6rPKjjkBqSWbo79Z7Vu59kyE+Y4617VKT9GFuIUGyd97g0QKONscRGXNFXHtBzYcQ4hMerL9u0Ejo8CPDx30WXn6NRcvbs3iqD2BTZGzU8UFZ/pqMO4jbS1N1qlnHZgAoHWXl0cHVp/8A8qEGWy/rxALhU9gK0ng47XmsxwFis7mZYO0msspWqIYH+5nFe5zFDttEzsfBrajGJeDksFgDkVLQSV68Yj5wgdccZb54pn3/kYL1uz9KdrLVF9mZqo1+1+29euCKv1/0FnIW0k1rY3v03pfEtONuWMdMbVQR0CwmJ46IhqPc1ZyQnbJ9KUahkY8TeCYcofZYjRs30Tsq1g2u4/4L28tEep7WPMrlE0viuR6MIfxb4wBMp3pL3PXuFrKNi3TkK1E6dFnnAfEYv5WiFQLIzb5GfIkZxVKq3rIhCQR2Tf3zPIu7ND3XK8qgG2/KyUmXfPAHfUvlUk6XX8ok6uibR6bjNKntaZNy9YlKiXxHlfdwMpifeW/ULSFi3qCJWzoE2yT1dt9xpinkvu3CQJsT92LlL5rJThvVZQ2bXwz2ztuGfy6J5Xe06jFJvBpATabq4re7MsRIl4MJCVdjUF4ZEXc74XEjGmvYRLm+wIBEDZt8RVZ6PUR5Ew57cyllyP7UUrYs+WaB63AxKUIuFmVuT6dFBIkDF/MEXEgt0hqSDxQBYC0Mhb8aGj4OmEOLJ+AUCdZ2kqXdfjswoLCaehVjYeekvSj68P4ltKaVS91yS3dvwOyFNt2eb4eZo7FS3n4xTJUeNma16uHFNpsuBx31t/0QB6HTRyN+oRjf34kS6M2THW2GXoPQHmQFCLgED5UnXFbW4ZvK+c4f9+pRUNmB+bKqqQCpeDhvK9AhRXZbsoO4ooHZK9mMeQM3YcbjrLnkB/muKrVJHamiXju15Mvji5YiegD4kAIzGF0mNT6cf5UqlPg3OKZCtTrtkKhIXnzH3Ad+H7psw1Gm0QMci91xwj3r21dgPp/FWeoiZhPIh39JBjeY5IzQT4drd/H4varLodX7UHEzHGsxFOfonB+LozoOAEJe5ewHXoHFe10ET2kNAOF8EolDmsYNxugkJGOgHl+sPcxBfc2ITBhyEi3n8V1IkREyeQozDkKTlMS/+N2Iwa5R0OuRe8YLtsiHTx2f5g5LH1HsrcFMKNUDdLnf3IwQHDf5hDu6+94IY6BI2BOtvQ5arRYQXcu29PWG653Qc3cGXJ8lX0//UlF1zlOma3TYnN3nGhn3E8pkiW5aMKCumgRoVkFGELAZE6GAmIMnpRz0f6HaaikvSS3OkMoUB+wnmX87Wh6o12I4Wb/0WDxIujIXCGcBoseyq5HY14dQial0l+9YyrxuMKYBw7Jj4dKvXnZ8mWIpjQVOPvTR1SYFONy1zNNH59yX5DUue9BavpF0NRTdkdq3tHVbZnF/aeiUoapVaPKwYVkdGiMdMU0hSy8uXdzbSVBFujnkf05igKRIU4mGmbXbIIlixNkTqKKia8WLc4BwCbOYOvKzYNu9RD141FA6Xyhv6FdTjsuGup6z0WHJR2JMAJ/Jzk1+DwdCqdOOSxBTE1EWYUAdEfkXFKEgUTIExuJw0gW89WRKAS2WKgk0r32sqgOqSVIFrA9Z5aQaNeMvD4RUdoQPOmXOF2gHItOATQyF2oxwZ1xc2aOaWr4IEG+PlAnFMhqXfrulTwmEIgEHpXDGSHuGSW5nAlznWcck1xAxYccFUAVKICaQCIIgPxoCMPDgCtcQeqGsJBaBC0HhkgBplKTQqgHMI3BT8dSNkBAtnzjeb5mVROa08Xq6mxaSCAkLs5kZgQA2lcux79kCCMDoFE+dlkzLfGmZtUQSYiqkAgippyCd7KHiJHZvqAA9KydFYkgKV2nSxdRML2ImFXhiJ0QeVCxWuMs2YeLAT4Ak2ucHKaRz4FuUVEebFc6YHiZSdDRIM19CSSY76YPW7VmNvSUY1MXYx5u/KzO81C5MNkdM0cgjZSfEl9UkEjCdB5eFFwBCm+519WAyKNC6OXJppgxLApRHu3KhjAOhVG+iH7jsI8Lq1AMofh1CoXQq0yt+3+WsRAACLP3T9aLzm4xHTQFZc44CDELYEaa7fzFJiyxiCCJjVb+rkf6dijFR1KFOdfLCkcWIwrDoDRlDoxwDjIK9pECaEbH/M0AzqEYGADVoinUrJIAPAACI8L8GpaLadOpXskozBf6mTqb22dHKNnPCfcruIg0xBHvXwFrmj5XUw4DknZ6mFfKiAibADw80doc2hpGk821ya9nHPjImFynviHunP+l+4m+uXQ+RsGlXqTNw3aP5sV2zjPbpmVMYgnu8iPlZD5wu1alJTs6WEY7bSYt4862FHkLXY7nf5Z3uqpi12SsNIREYWxqW9zFMjDkpRXyEfO74r5uX4f2C+FqgxlA2J1QMHEBVASiytTRN6dsxzmuWOkmlDI5PnF2boXQh7wXMSo8GWG++1vacgwzOKEo1w4nCs2BZ9/udOq56onrSRBVvDGLoAdVB/KnRAqzEci7X+WxHWAv2PD/0ctDgenUZPNzSEIRYKL6lEVDGCMPFDDJRClNRREiBof4CxI/QVIbxEQjC7rklLjbkuO+C5jsvVRySQUsoX1hCYwRNIVcMC1JRdHykXQ6JXj8448I+MWq6XK2aFUWg9Xwy9nf25DHMnqztCLR/3c/dOCR6nDNM1cN+HNoKb6czv9ndrYHtGlsLoOtagqxlTthnd+et4bJo991GXjklGWCwlDm0IMQlwTq+VnCol7N9SXktvL9yostVDfKkEUOalBgNC1vCegjIVNm4EhwFI0HHFFkctGAsAhfQgIrqd4wRwADAAmcMAPOYr93gJLTHaxMkA6lNilHhs2lZ9Z2bAuasi9VyjBlRx0RkSzWZhbGPiTG0MpkjUanTtzYlCYcOaJ6eF28OlrknQe7KfKE2FRiV3ka5DbqNXU22xNoWn+TblYUWPZWPWexA/0L/GZ5Hl0IXAP74HUfTQnTBQEYEo3iMPahVLbQpjcJggYpQEcoTP8C3RgXVnIRFxiK6pjn7yJo+yqC2Bqi48D69EyowbRp3rA9LLLBtWEZ3PEp7qW7SKd+ubtkfJ0g9Hgq5JfOF2cqN7R12sZXSvfY+28SAgKLgE46aGicctXzF9CLOpTALttamqY4GpE7x0U9r8mmu7lhyAfXeJYZiIzJ1dIl/PzeLJ080fm6AzvpIj2RSY57JTmvKYHLIQtRaGD9ysZsHAOvJS4WLhn/0tCn50LIfaKG5cqFTaw4sKzCAiqklLAgVINhSoAXgAADA1x82+0jgwpG3CyoRSZqhQ8i13dfyIKwoz24v2ZnXErTLS1xFiK7DK6rErDr7kcasRjtumqjpl5F94aX6L292qtLPp0Nqn6WdGDI+qswmvnVVDVuuZhGqDPvL5iH0YO3YqhlWXYCOrTKl+wAAAN5/o4r5G1VAurH+sGNUuWVlQrksSgkCQ7OHqg6MIO7hOJGReKLCrhpNE4e3rAlo4LdzXYVaN0lo6qAzNBYVX51hKPB+IlVoIDyZ49dMcwHVw43yPS6wYi4gjvk6Oib9XRFhU/yP9Yj28c9gaaNk76Aeqwtz2JE7GC5ITxRAZhBZYBUlGNP0XVXXG1twGd0nRCHUdZJGt3lXJ/3U9PacWGJuPedCubvOsrjFYD70WqWBOR/JvJkJVIpZEtw14GcXFA0oU0xvU7OXwgpS61F2JzbJHO74SlIJbd6wBj/LNPrIOr7uKkYytURHaVLbnJ2GW6qV3dj9hD+whGH//eGtNHNYMH4ENHJfM0aBpEEAoJH0QBD7i0yiKGnsZ+uTiH/6yladHMU7m6YcVEyh5NiSik62NeDVlD50LfGfEZosOxqhZ287gPSkq4RR9KLgfSrw/qK59Y4AvYyvHkD+Liiv8njVaVVt5QehXPnXK/L1qGFLdem+Lyu9TzuyB3Phk2Z3mA3rn1AHGoni2yRVPEu7bJVXtkOBPaCF7SvzJ1NDSD5Rm+5hfV+HYtEpgjsfjsXkEpLihb3WWqWmKvcQXIiaYDkWUHFjwulgQQYYIZiU/KnkgH5F03A+/hHEQnkIA0aQG60QvBQSyGsdctWkHUreIMA4s/W8idikuTZ+ZsR4tqh2vkVcoxR3HXNaXW+KZ77AmZsZ+50/4+1xYoBK0g9x4mUQXCTpXzHeveW7wQ0T1smtDPT5XYqj/YPJe+41FCUlz//9Hq41dUgoEjTLkoSCpQbVUAwaEwJL+usM1ZqjlQS3al43Jus8bctw4nReAujkFo2Hi9N1JIHGQrFtUlsMVPCg6nbCFujquiywT62XdPqcZePVKKNOgKKPQpEeawxnn0t46MMnx/dDbEdYxL9YtCMszJ8p8mQi2SE9JPjlh9VqU519iOx0qUSlpNpnWG+dLLVCDzsyU1ur7/jV9A62P+QnDICRlc4Bv+7nNAyO+ueTt0cwHwAEol7gU1csrANO8VPm5mwUu2KIbessTeI+KgzO5y2Q9c1pXrbLZivCp6RMiOIWBW14jgjKX6RTy2xzWNA0uR6I6UevW7tztwWy7Ed+u+P0iC2d/9R3D9xewAuUnjSyrzgdxiYNuWLmbY8pWdFNFPsCKMqCQBttuPdfMKAiUHTjpE9joHrynypIDlJYRXvVY9BUA1zhoU43QtZcKKkLyCpYP+5FqcXj6gki5PuK4dUz/uybPAAA0RkNz9/FFfw3sbj/La4HL0wqBIczTnz/DvZdJkyixk2tx3uFKl+cOLXs0bSJ5LCxVXgshJ0lG5YGJQZ+YMsMpJGfG8sm9HHs9BqCGEZuRXvn/lFu/Wyl7wmjXZVku3PYrQI9NAt6P5dDyKASyQQuhkVi2g97mYfpXtAeJZKXtOzFqT3duQtHGU7Y0y7lQuTDNENTGNGDvCq6v/gVYu/PxaFVvkqwUOjfGEpNVISUFa1n5t3x0z1WTCDeAXWxbGe43mKHk75vAI5gHWfLyWX38KlGC6HrqYQOLDgGZ0mlt/pqoo7tVsqglcilMsg0HYEZJihWt+m2fKsrYHWdsq8WxhquJcOm0nnNLDLPowv8L76FoyiAygHKXmgV6GpS/cBDrLMhRc2tYJ/cA6zoQsq4HJcOnX1hwe8fvDhVlaXsgIIcjD3/7J3jGA0UEZsc4g4ooKpUpsntGYSyZ5HngZrVM2fQ0ONtNEetVc0bDQsmHIjSMzmG+ZEZIgBm8aQSSHEsPaQ07l1e5i1RZqTyGaZ4O58uLIqS+DHsIOUn8ytByoxveT+qyE73wvVlzKAzyDpItqlRIBJXDUlV+5n8OXZUlH3WX5lAEa17gTXCIQHyI+R27ctuae0W8wvPrgeS+iJw/uBpGKFPeBoE5nQ4HSOmyvTSM8jjOMBNTwlHCchUNgLsg/mjgeXq4kV668LLWqSlXMv4Yol0k9pLprp95BAZahrJDGOZWxEATArkj46V1Rxm6ng8sHKmXRROIrxEBXjlN43yUZlLBE1dCs7wkTT47/Wg/8Qg2w8HGmYDokSNeyKXAL2zJMtnrFJfDY7HI7SDnCA9+P/5L+KlaKNCkQIQWzKHwUJDEskNHSVPf/d1wZPS5UyY6GlF0tyNNTm7Ignu5YDsiZZzXWecIV+UhrZaZTb4SNbtPA1hbavgPBlM5OlGOEh2uEgtfaWY/tq0olHOe46ZbT0PDvcNZ7Z5adAQXXjRXJ9CSutzsSwZV+9KS3VGZ5QlUHlvapI8DoCGzgcj0BNgOGBkVJ8NJteUSKUAtl61aRHJH5CsH8BVyrtxyLE8nImhduWQTo+UXyV+sd8f4LNmWcRRjBW+
*/