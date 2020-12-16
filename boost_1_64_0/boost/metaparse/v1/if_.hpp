#ifndef BOOST_METAPARSE_V1_IF__HPP
#define BOOST_METAPARSE_V1_IF__HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/is_error.hpp>

#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class T, class F>
      struct if_
      {
        typedef if_ type;
        
        template <class S, class Pos>
        struct apply :
          accept<
            typename boost::mpl::if_<
              is_error<typename P::template apply<S, Pos> >,
              F,
              T
            >::type,
            S,
            Pos
          >
        {};
      };
    }
  }
}

#endif


/* if_.hpp
P3acSFpF6oGdmdghRd1mo4rUPe+seLWRjmjU0mby/4EqdG8fpe1NA/3aoNzkWy7Y62VO2uCFVKS4jLJZlIKPU1xDabUWIeK2dVdeml82yEv+skGujZcNNHVvefrC5TH7mWitvJUNNzQAC+/n8fIBv8X0SLXXYzEhK5veFYCXN736pdor1yk5/MfKi5oc0OdgJ6q1+qJgptMRhmZ6fEGLzbTVSPZj48NeuakF9twu2LbxAj7Wq7YdY5lAKcxXin6y1VqEhrL2eku1R/uzMiFKIVTVoQZMf8woCuKPmH6fKgriU2znxeJnVGIpam1vpGiTsG2u2XfmG0FsBJ6WO0F5x44F4m100T2BhzhT3SAY5Shn5Fj/VFvSb3hTotj4SAzvILVRppOyHAS/1gfO7K5TtmMmyxWkyBmyM2jatjN1YmVjPwZiZfNhBmFl8+EohOnlNhqA27LCAkS16UX0HMJbHbH9jqXVr4Pn2XgBkjcTrTS7C7MG4dC0gGUIu5QwKIm0RKR6hKbiz/1bhXjb3fro6T7BnK1vpoYP/2VTZUJTiWNEuMzuzRR9ydb3JZv3BV0x8RHFvNR2oIpqM9tzOgJB/CS6tddGGDldEZ+N9FxWmj5usB++ZLB/P1tgrxZh6Kx974ANkexy2Vgdx5uV5oVXenzpTmVGtwe1vRmYQBCfAEsxeEuCVKTV7Eu27Yp0n7S3LT0pfp8s6aoIc+zuptZZNb/LogZgaeW2BmFh4bZW3sLaZq28pWXbsjrX76yiZGan9PsiJsNXDkr/t5Lp0YPNkT1m/WEBZuWb2o1Qdt4LMhsdGOJGG35hgjEwG17Rd8aqGhz1slnnmgOowTqza6SiEB6zey5xgKB5QeIQ3oDfYh3wxSxwOkDof9aYldfjNhuLcIhqfDclYjbLymFkb03APGMDJIz/HZGwpbHXYMJzzS75FTCq0xJTUhh7m8fxJbAxdijRspERFsUs2iy/MsdyV9whs6mqRhh7byMmz1bZ+YiDaJRLsdEo019KtT3LZL2G1NM/WSbWV+akYyLZUhWp7ypoY2ejdC1RM7M01Xa/bFRB+2Uj08nEhZpJ29twmFjtbkg62RZqy5Y2DOsUVm0seba/qNVGv4LDLXcsONSh4tp0jjUKFKxW6s0m2ASMJXuA+8psSwCWe+/JcTmCEcsQljwOt0MNhzzW3DS3w/zrPxqAUh+0shmCBuPK8VjsPCAsdp7mvf229vFraoNPa6/CRRthmTiaKyabnmRshPGp4Wqv9d6mmNKNT9dmpeVbAVGEZlKt/4EqbC48FYMT8JhdldEIk8r2eNa2DElxEXY0G2XbVRAI4tNZKc5nJEGqy5HZFgHbFdHBSVceM3Uy6edg0kaShEjjyWRbW9iuSDceKeqRFDY7FAjid1W0HSeZQqrbqtF2Dt52Rbo9Jm3rnKSLo1N/f9hGFbRndgMY+h8Mv+3pm2xDqJXiZkMmUArpszY129hZC0sfGmHsfRzXzGr7PBvbZjU2y1KSm8L4lPB+/KqjsQ47e5Zz+sTnIOyrCxMoBZdZ2xuB9ddRr4Q8bktRmIyErHu4VQhn2MbiPBMvIqaYlLNeQ7o2A0z/6htOa6S+LQXugLDlNFtf5W7z06S8lYjL/R7X/hR+XoXp/fIFlNJgnX5JP0lCaZzai5k2qkj9SzZZ6dl9R+915qS49Z0JlJQSKW59Z68Wu1vfRZnPU2PDuP/HXjCzVEUjKay9BskpgYVrdna5iJ+My0vtxfOkCCkp0rFrtaUqBJtZ+1geJ27AGVYspTgBUj1LcdoYENZw25sb5sRPrqY2nkkRUvKnNp42qkjDd65T2XzFdtoqJy5HmJvais+kCBt7YTtfZKM=
*/