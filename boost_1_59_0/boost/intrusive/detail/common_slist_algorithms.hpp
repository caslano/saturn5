/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2007-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_COMMON_SLIST_ALGORITHMS_HPP
#define BOOST_INTRUSIVE_COMMON_SLIST_ALGORITHMS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/detail/assert.hpp>
#include <boost/intrusive/detail/algo_type.hpp>
#include <boost/core/no_exceptions_support.hpp>
#include <cstddef>

namespace boost {
namespace intrusive {
namespace detail {

template<class NodeTraits>
class common_slist_algorithms
{
   public:
   typedef typename NodeTraits::node            node;
   typedef typename NodeTraits::node_ptr        node_ptr;
   typedef typename NodeTraits::const_node_ptr  const_node_ptr;
   typedef NodeTraits                           node_traits;

   static node_ptr get_previous_node(node_ptr p, node_ptr this_node)
   {
      for( node_ptr p_next
         ; this_node != (p_next = NodeTraits::get_next(p))
         ; p = p_next){
         //Logic error: possible use of linear lists with
         //operations only permitted with circular lists
         BOOST_INTRUSIVE_INVARIANT_ASSERT(p);
      }
      return p;
   }

   BOOST_INTRUSIVE_FORCEINLINE static void init(node_ptr this_node) BOOST_NOEXCEPT
   {  NodeTraits::set_next(this_node, node_ptr());  }

   static bool unique(const_node_ptr this_node) BOOST_NOEXCEPT
   {
      node_ptr next = NodeTraits::get_next(this_node);
      return !next || next == this_node;
   }

   BOOST_INTRUSIVE_FORCEINLINE static bool inited(const_node_ptr this_node) BOOST_NOEXCEPT
   {  return !NodeTraits::get_next(this_node); }

   static void unlink_after(node_ptr prev_node) BOOST_NOEXCEPT
   {
      const_node_ptr this_node(NodeTraits::get_next(prev_node));
      NodeTraits::set_next(prev_node, NodeTraits::get_next(this_node));
   }

   BOOST_INTRUSIVE_FORCEINLINE static void unlink_after(node_ptr prev_node, node_ptr last_node) BOOST_NOEXCEPT
   {  NodeTraits::set_next(prev_node, last_node);  }

   static void link_after(node_ptr prev_node, node_ptr this_node) BOOST_NOEXCEPT
   {
      NodeTraits::set_next(this_node, NodeTraits::get_next(prev_node));
      NodeTraits::set_next(prev_node, this_node);
   }

   static void incorporate_after(node_ptr bp, node_ptr b, node_ptr be) BOOST_NOEXCEPT
   {
      node_ptr p(NodeTraits::get_next(bp));
      NodeTraits::set_next(bp, b);
      NodeTraits::set_next(be, p);
   }

   static void transfer_after(node_ptr bp, node_ptr bb, node_ptr be) BOOST_NOEXCEPT
   {
      if (bp != bb && bp != be && bb != be) {
         node_ptr next_b = NodeTraits::get_next(bb);
         node_ptr next_e = NodeTraits::get_next(be);
         node_ptr next_p = NodeTraits::get_next(bp);
         NodeTraits::set_next(bb, next_e);
         NodeTraits::set_next(be, next_p);
         NodeTraits::set_next(bp, next_b);
      }
   }

   struct stable_partition_info
   {
      std::size_t num_1st_partition;
      std::size_t num_2nd_partition;
      node_ptr    beg_2st_partition;
      node_ptr    new_last_node;
   };

   template<class Pred>
   static void stable_partition(node_ptr before_beg, node_ptr end, Pred pred, stable_partition_info &info)
   {
      node_ptr bcur = before_beg;
      node_ptr cur  = node_traits::get_next(bcur);
      node_ptr new_f = end;

      std::size_t num1 = 0, num2 = 0;
      while(cur != end){
         if(pred(cur)){
            ++num1;
            bcur = cur;
            cur  = node_traits::get_next(cur);
         }
         else{
            ++num2;
            node_ptr last_to_remove = bcur;
            new_f = cur;
            bcur = cur;
            cur  = node_traits::get_next(cur);
            BOOST_TRY{
               //Main loop
               while(cur != end){
                  if(pred(cur)){ //Might throw
                     ++num1;
                     //Process current node
                     node_traits::set_next(last_to_remove, cur);
                     last_to_remove = cur;
                     node_ptr nxt = node_traits::get_next(cur);
                     node_traits::set_next(bcur, nxt);
                     cur = nxt;
                  }
                  else{
                     ++num2;
                     bcur = cur;
                     cur  = node_traits::get_next(cur);
                  }
               }
            }
            BOOST_CATCH(...){
               node_traits::set_next(last_to_remove, new_f);
               BOOST_RETHROW;
            }
            BOOST_CATCH_END
            node_traits::set_next(last_to_remove, new_f);
            break;
         }
      }
      info.num_1st_partition = num1;
      info.num_2nd_partition = num2;
      info.beg_2st_partition = new_f;
      info.new_last_node = bcur;
   }

   //! <b>Requires</b>: f and l must be in a circular list.
   //!
   //! <b>Effects</b>: Returns the number of nodes in the range [f, l).
   //!
   //! <b>Complexity</b>: Linear
   //!
   //! <b>Throws</b>: Nothing.
   static std::size_t distance(const_node_ptr f, const_node_ptr l) BOOST_NOEXCEPT
   {
      const_node_ptr i(f);
      std::size_t result = 0;
      while(i != l){
         i = NodeTraits::get_next(i);
         ++result;
      }
      return result;
   }
};

/// @endcond

} //namespace detail

/// @cond

template<class NodeTraits>
struct get_algo<CommonSListAlgorithms, NodeTraits>
{
   typedef detail::common_slist_algorithms<NodeTraits> type;
};


} //namespace intrusive
} //namespace boost

#endif //BOOST_INTRUSIVE_COMMON_SLIST_ALGORITHMS_HPP

/* common_slist_algorithms.hpp
QbbinetxxYiaYQ+qzJ6IZmQecOha7Y6SZ6uY/AGTFBStbyJ+/7MM/FdRLaElWi2rjv4ST/zpn6J3u+zM9KJZXvPfvpG36HtGy26HKJ10v3tu1ZafdwsTSm1XUlW866QjRC4qYchej9Jp1HxtMaU/ylIYgpAoEEdP0V7/Rk6o0FPZD3PHhnxKUYjLmuDHRvXQgHk/vAEjqenTEIGm/Pz7rgM9gaN8GzSs0fk3zAx+O/NQJxGejS22/3zMknCu/A1TGa2BILkl5qPsROshPIEk5k/CCPYb/MxK9yQmHQZTuuM/6qAsM8dwNwW6BaXocYXEEw4Se1XKzS5yqut7Lh1CShghF0jpOdy1vX8wksIEGIV+x4WOu9CnU1CoJ+OGoly5AqITBi+y6P6XX4LlRAma96+C0hDTJsRuemZgTlESlSgPLcczJ6BidMbrOV7QvXC0NNxBB0Cf+qrQMcn7jhrivhq5XxCUOjJVgdJsLIX4dlMvbu9vVgtnJ5bRgXc8/Fl1R4LXRKEu73W6CJdGlOt58o519SZvzYKUuyN3BwZLdc2K9s8PtWnme7nTWeM+9h5mmAPJxAZM4ihjct6qi3M7laWwbnJH9ccuFOW9B+EF7unCnkz6HJQribkaT0fmxqCWF2tMnwUsxlAcPo1c+woIVwBSo+nW0URSb/PTarl0HR7iKYjy9Yq+ddc+43GsXwjct/6FTRJXqah0li6PmW0fijoXuvwbDxDaL906DEEDF1AAygqYqiuJ8pWu6cGSjUboxkFPx/6KsvUnLtcW3KhMpsOMZW4ZSW6ACdpRx/TKWCCEz75nOVYNK5lMTq3AU0rAcTqPF8Yr9SZETmaQvGGhRzGwfIlqS4gkeodnfHtJONbyIugb7gFtTwAYfa0WcDo/1CQBX2UL5XdopTKwIONisadJvIwxf9Wd6R+OkuEk2zDH12oVA7O36am/2KYRocWRM3wGtFZAlMQgZKN4/UsxAGSjQBoPSS576/6MTkNuMKyer0KspJZqaFb+bKEWijo4TalDHLFtMHC12mO/M1P6ZRbuEdL52bH6CW5tS6Yox4OMoFkGnDXFYjDglfrXBRpsbMgnqxYLLcHDTqSRrBUHbT9xsTQGEjrMHFYXXVJRzIon6/PU2HVLqOYQaq3zYi17lg45/837C8bqi2Sk+dmzhpY6H1h+61jPIOByYq4LXliwA5e9UhuXif++cf9av7FgE9mK8Vg3fihG+zXO7aBr0fD0/kFFQ0kP0ELAT0iwTUhAtxcH7Ew9tt/nDolIoeN6MnmIJDFUsEFzk+BCrW2FgaSlkwI6Va6BHzBzuzKvfagkYq2RxnMTSh/YhM5vR/wIeU9noJOHb84/6Ew+u8eCOO6qO8PAgokpni1mLf7Rbmq2X+vRABB9+RAG2qq7+9RNG2gG42O+mMqguEjoo443q9NoscAo66xoTZByScF7TWXSxSd373k4ixrErevsQ8llvJpmroCUK2zkWCT02We4FNzTdiAIEATQ2LadiW3btm3bmNi2bTsT27Zt29rsw/2CPqer+qXhYL/oRtrojsKya5H+bE90ebg+h1wLb7j4hhSsJXjaZCbkVeOHiIktGkrfwOm957xbMhPHvPnosHvMBuV/W4IOUBHdT1ckm61RH2Hwe7GGVuBvkDVAgqDKdZsKjNRZ/1UyEd4kAoCtotDnJ/Fvnp4Xni3pWBMposBZX8Y/xOAjdhT/covWXczRokzKk2/zXP97tTiMkTxjleYR66F7pP4lgcX0s8CdkQIorHIMGktR75ab1Yvnry2cqIy6VXuqxRiq1G72YVnpQsjMDFBA5qHL6tYl/CEKERzVl46Yat8aWTc2iZKdhxnkNtKQKCMqLH3I0gUgnjzt17mzaNo6jKTS3Pt/5m1UncJWRE3GA1tiC7hpkACZLw3Z2UgUy/iJgpar6KckZh0BvT+R/XtvMnc5g+hygeES5SRgQPc8rV4RcEzhmFtCTWqTyCAHgXLO2w0+UD+pZATvEES5m9NrNHFRHAYUhwiwMt3LTTh0nZ8lB5wVATWjhBbDcbj8u6CilmUUceBaqrPk69adrDLaVAkgEs6Opm+l9CCnzmKRtTNyl9F/r+9yXmA6kdazKKWRm1FCRFlfwGxaqAqdXQW+kMPQAWP6ubzvOriVb/wICTNZI2CbSeXMZI+VunRaS8s/JFh+6mgmrmtBXpwd+ISrjYPJg/AQblknfdOgxp3eS6ed2y3SB5l8MjxH8AJPm0NVYF5FUgs5AX3CsX/hk14Js74rA59gKs4eJs7CKDCwO1bI4liLYiubRh3jqjMvVF7qz8ghywgi1+ipIEBrv6omctcTwEUpYhlMcLv3RJQmzCZZZcUQ8lI6/M7NOjY3IQH8Rii9Ia5RDqmPzbzXoPxnibVXztK+vPNoSRbMrnFKTdiVWuhLUNlWJ1EI/p+2Z1mFBx/NBMvLlK+Talxt94HJtZhtib0f+YxYgHWhcjwPZnXvFdbLVFXcu+nKSqqtN1lPy4PKXxN0h65tETsVddFBOQnCtUoGjRRvMYqZmKP5P0kye4Nnems0rZMwdePL9zm1u7KreB6lSdkRasXUinCGDODS2VoGHItkBwb3N5mapiog9W5GkZAR1EWAzxnMaYQjhGw7WqmE4Rq3gX8/3nkHN8H8xIXf1tZe/qiQBMqWRvnKOYxtV3BMctgV+xKcDrSbjrXVqdB35TMC5QaiGmLtFgEwYR8IEoKtXW5+VZB1Cs9LpNfNzoWYizOputy/H508umABjuOn+MKmK7/OlfhS5OuOwdJtudiggpcLQaaU9QN9BkX+vTfftw2a/n4KTcGxJulQ4Q+1UESjuY2qMDX8AgBAuhfIgFHX/9OqbwDZ0cZo621haPGp9RpD+Y/Rwexr6/iOGdHpCf1M21O+xRt8NQagBmtNNPbNfZ7wJQCaD42I373Gbo1nKIFGSMdyexk66q4L21wRlvTLyXx+j8CBRotT1QZ2jwLaEheUIKSiIEZHQh7oLuDW+oWKOe5e0Z7i3LDP1Le0eReXO0Elt3kQhZqHKE4j8MopDLGWQkEv0q1Kj8b0OM9eUxrrMzoVNKX3eYaXyr96VSrOs8xT0J3g07xpFV+hxcuSY0EJzUZG17/HZ/Kjk4DrfbaU1ek6fHLb8HQ2PQYSp0Zxno1H8EJp57lHF+FF/lE6I8xSnRrWszb9QinKSTlbwrv1KXZDrrmeQa0T+tFjWBa1qjffGed8w9FcVws+VgNPF/2UL48s46zmq7Ka1Daus8y5qA7ABTeGkuS96aOb0PXk1tbYKG5dFCQ8o1DWdBGqTw7x4BXsJWL785mMZMcVK/qwdhbpw5AHFCinbAi1MmLEEwQdsH4TO/FHXbINZ4HovnLJPVWqwyBXP9jcoW92G6gdnT/rLJ4wnzScpjPFN/UBjn0C66J6FHsSK3VGhNgRIbFbMAXT4KLP5o63NsYHNre4v0VY/danl3gpVF/BI7AEtevcM/tnVZGeC+iZnB1+RFTRDaKCTyxxPyprK6kST8YzO4d2mBIizthSRcSXUF9sYnqXWINro025t5Pi0P/ac4VW3uf1NSPJdi9mVgzVrz+S3DzLp/qPPqJvmZL7z3DCw2x2Wr1V6htplOiYPpiWq1eITvLY282IlsROrAmFEcn4g4bu8qSKb+kQnXCJ5O5BmVPs2NuYiHRUyXMayaM6MPq++c/XvBuMi9GqLEYivTet1b5B21d9txWezZlh8yz2n8rScTgpsqo2ryr+3dRlsd40oQzg6qxlIX+npzlkIMKoxWhU+wY9osg3gDHCbZDvCC7BParn4uuckzHvaL4U0jus9fU2kEzUkCfxWV2JMa+ZMs+8SwwmgXRt7+rz2yLi7r6f6A6jOiypk+Z6UT6sYJyVV7pSMoRyLKDDMQGZAvPzpeKHh3K5BBD3ZlIoOB9GVjoT3+NU6WZO22dDbEpF7svK/XjPr0sPR59+2H73zFyHRUYx71GtjhjIyv35h8/lCtJ5n+f70ZTw2+tyh630JEVb697NjV3glQyVQY9Z/mya99Lm7GmTLwWkAjeeT554zTTcE0XgJUWOL9Gg8MaYBKMSC474f8zxuI7ji5wYJRUVYatT/uOmGiBgeT5UZdOtc0v/NEyeHhPazcNaVD6cZ4Cp2432UPt35wTN2IdnASmWSGStMChI2tc7ES6aOS4K1WTl+I/Fv3r4KuX0szaCPJsdt+693jXzBc1RmUbtpUhOJfTmk53nTPhyw/WeHP/87Fwa466LF/hhODCJv332qzajr7IrqU0aaaDSrTqIFzZTIGEveU0J9Mex771rKCvVZfLkTvk0C2KzGiGVkAK+pwMqEq7eH0Oy0vyVbwCNjJq2JvRckmClFzjgBcV/6UWNaQMPraQi/8c/mH+IddzBNeXh1FQZovwe2EL1olbxbjw8YUvDpSd4iBV3itFxonOVQKVHrSCbVfkTsfWFuNfhmb9B0kbFaST9gpURZm0mzOkjr+m8WMHDINxLrILnecTmWCx/Amhn4EE3rca3gJ65l6rzsXA6DkDIvrcYJwGKmSpjB08Km59ZSi+bhbCQvNi++f5jjJA1KWg9Ippuh2qodziDbsSAFDWmOuOe8wXk4GwZ8KgDQT8p+6g43hnk0MaxH7U4Hmxk+n4rpkaeH10xTI/HrctkKg6bFEw9k1a1OJPzyl06fsmbri1BXpVck+g06Za8Nj5s3B1fy0slGbKV81iEo8JNYJ+R5IzeenPW+qzh5TCmuOQcg+0D2b4URbw8K6DGjNA8iyyWn8b146a8BNhulUT6quytAMRoNwXZBoFnMFU55iYNWMHSeAg5z0531zIludhUSjOtPGUx9jTsPGL0oysUHvdaUMjBnHp/qRBhfTlOdLwdx0siS8Qmtq4nG3HIYuzK4GjzsONQOKtr5e3CNyuRbXEyUqQkqj1d+qWGzS1mebiSDc+tA/mpKMUvQ6uDjQHNQm1sZ2B1GyBZaovzNrPjQSPUO4HrUoCvzVM0atQGDm4ukFoA1HezPJiAKsQGCGtm1C0ZQwE2NkziqjK/NJMDzA2WXfxtXO7jAVKpeNbkVkrAw+a6AxHZOEMq09Bv84jyI5w32Kb1RmR3TI7iIPWY/Or/QrtK8TQh69BHlhgFN8LzMxR0F/2S74s3nBwDzJrk+U93Op76DYNhKOmFVcx5bZ2jJCbYHz7gDYdTE7K/T56oh7wKimzih88fERAg4Ffgr6Bfwb9CfoX+CvsV/iviV+SvqF/Rv2J+xf6K+xX/K+FX4q+kX8m/Un6l/kr7lf4r41fmr6xf2b9yfuX+yvuV/6vgV+Gvol/Fv0p+lf4q+1X+q+JX5a+qX9W/an7V/qr7Vf+r4Vfjr6Zfzb9afrX++ver7Vf7r45fnb+6fnX/6vnV+6vvV/+vgV+Dv4Z+Df8a+TX6a+zX+K+JX5O/pn5N/5r5Nftr7tf8r4Vfi7+Wfi3/Wvm1+mvt1/qvjV+bv7Z+bf/a+bX7a+/X/q+DX4e/jn4d/zr5dfrr7Nf5r4tfl7+ufl3/uvl1++vu1/2vh1+Pv55+Pf96+fX66+3X+6+PX5+/vn59//r5BYj0O6vXPQA7qV30m5AqnocKGb02sCYDQQZwXD6HKW2Xx25UoDN1J4pDl0ku/n996RW38TtdwjBYnMJQ1hT4X+6HwCS8xoBu5m3CPnNtf1im3ga+RX+sIz5g9rI8cmRBn4SISYQwn49wbkYy+53dk8BhmT8swzLoaJFX+UAKRj1PtFc1S5qF0hLcJBSDrWOspsDDPRhH9RO3Qw48TF2/wlKr63LCkiBNQX6EvaqebiytBIcdsHiLXjlAbWp3kjykkHIpdaTKbWqZ5X3veDPCfLes+D1vXX5j8GbopS7oECiQAfySyeTgfN37BwiV8TxehfgFGLqQ+UTc7b1FtmQMTfJLIkbhADIro5JaF5VNC16rjg8npwlgHa/n44ETVQU/u9tP5jK1cwHzJsNO6R+f6SUoewuQqfUKJa/RyUIVpEVkO8I24ICP+QWeWBxkhjRed3Q3vVnbW4PNRXwifUpDLOVkjXgBFlFSyPvBZosUCeU+XAMd1ZiZlqhXPrgkq44aleY/leEobCCT3nIA+uItDVkYaQ3oOMSPZApwaamwWz5MAN4tg5Re3L9nWzrJktN3wBKey5JUVBIpf2Z8E0BwVhJfGWmir7wgXIoS9BeCZDRM0C5eKAIUk83itJ9WJUf4YS5M0fEfZ7E1q9qrf9qP3gNWZYX2CQMze/1cGPjni3F3/zQqBiGKhKWG79DGDuVt/22UTQG0+RIy4lHSbG8RYJdBAYnrc94/EltuLEisAZnVHZEBRirgcyN1k23mejXQfAmP8qKksytWwRhdJxmvNwL4uQnO5YZbWuuoWzdsc4QDDOyjlqBEvW64amDDgB6u4bRmcP6XE5FOs2WxwsbQWAv2tEx8Z4NzUulFWPg4Hx9akVItJQzQFrB1IECbbD7IUo6VEE10WwY1CLUWxORNC48P5g4Gx8fUVl9jyBpGIZxBPre5zkMdZw7IjmZlzQmrg+Qv8TyQ06AE4dvJ/3Jt1XDpzYQWdsLfbJCzkYkdMQ3OqzJ+n6ilaW5/SRl2Yvcydo+x6IaWF2I389aUcH3VwPmn6jK8oY2v4pXcI6IG3zTXxMpZl/m6fSmzgJdsocmyqWIcGWzSSTK00hBu/E0C4o7dsOAvHhdf/2FBhFBBHe73p6gtUNNanTB/UOFRwFfT3wnKUaxdYrCzl4kkm6tGfTWJTC+zeIaIIZY/5ihmvvb1I9TQMyPeKs+MbZfeigmGuRfDASAUvkFiS+F/9ddZ8woM4DXnHjhsjpxYT+ijmBXzohjdkSMMzkvQdvrDcVdznJd3L6JwIzVCFxllai9OenL1KRzSUmlJXe1fgT9kwvxbI0t2DY4Hs9jDbe2HW8kvfDmAA3MU96TgkXQUHBuKfTj+EjKf13sdQmMqcKW8UW/haFDidCqd1SCqnA4RBq594Dfafoqvdw5523p2CyvtdIi4Es45fY9XDRbQinkPwy7fs0loWNATrDjxUJXyNI5VMHqgMbeifsuPRwYMcc2lv7dGFZmDWm1FM3LNbyxwYk+4Wdtnls4eFVgXfZ1M7qSe8F7U7SFlJprZ+6U83o+HATgY5PjZFac9Dx/p5FxLJhw0xcXNnRi4vPeOMpFyR/s0hDsIoQNosa6PaLLH7iFABhM3YC8Uj1+wPCSytmvd6p/agCJrmxgxEm1S8uiwPHAwIl/PIYMJR8/7qu1Ov+eoH3BqC0GrVEiyS0KrjSvALAkLMTaGlF/Z2rwN2Lq4RVjyUtKYhJ0Dhqcyr9R64UZy42L/2RbFXOrzlu/9izEfkfs9hrBd3fuD+U9+FGNdgBxKovXz00/RLQDHSbg1Od6tvbfvamLfkuv5RlIMdCXBog99934lQ4ivVPTt9iCGSigJMyK48+kuCTWD2L1rYEJMG38rcS2D1whx65Ne+Ee1mBx5pa1GVYDpB2Un3fUgaew4+Qyvjhfj68J1EBACwc6RunUOYg8q/fMqXlVP9WK44b7VBZ5y0knI8aMnAhlplk23VMFO4B+g/4Y0f13s2PIB0YxjOf17LEBrvrsesKxvBP5hZUwo15L5akkccV1ODaM+Anp7Ysnk
*/